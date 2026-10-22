import { mkdtempSync, readFileSync, writeFileSync, rmSync, readdirSync } from 'node:fs';
import { tmpdir } from 'node:os';
import { dirname, resolve, join } from 'node:path';
import { fileURLToPath } from 'node:url';
import { spawnSync } from 'node:child_process';

const support=dirname(fileURLToPath(import.meta.url));
const root=resolve(support,'../..');
const problems=join(root,'systems/rtos/problems');
const repeat=Number(process.argv.find(x=>x.startsWith('--repeat='))?.split('=')[1] ?? 2);
if(!Number.isInteger(repeat)||repeat<1||repeat>50) throw Error('repeat must be 1..50');
const mutations={
  base:['schedule_record(s, 2);','schedule_record(s, 99);'],
  periodic_tasks:['return previous + period;','return previous;'],
  safe_task_startup:['int local = *s->input;','int local = 123;'],
  queue_command_response:['xQueueSend(reply ? c->replies : c->requests, m, wait)','xQueueSend(c->replies, m, wait)'],
  shared_state_mutex:['s->inverse = -s->value;','s->inverse = s->value;'],
  task_notifications:['ulTaskNotifyTake(clear ? pdTRUE : pdFALSE, wait)','ulTaskNotifyTake(pdTRUE, wait)'],
  counting_semaphore_pool:['xSemaphoreGive(p->permits) == pdTRUE','xSemaphoreGive(p->permits) != pdTRUE'],
  producer_consumer:['s->closed = true;','s->closed = false;'],
  dining_philosophers:['xSemaphoreGive(forks[a]);','/* bug: omit partial release */'],
  priority_inversion:['if (inherit)','if (false && inherit)'],
  event_groups:['all ? pdTRUE : pdFALSE','pdFALSE'],
  software_timers:['xQueueSend(p->events, &p->id, 0);','xQueueSend(p->events, &p->id, portMAX_DELAY);'],
  fixed_block_memory_pool:['block == (void *)p->blocks[i] && p->used[i]','block == (void *)p->blocks[i]'],
  watchdog_supervision:['i < w->tasks','i < 1'],
  initialization_shutdown:['s->sum += v;','s->sum += 0;'],
};
const build=mkdtempSync(join(tmpdir(),'interview-rtos-verify-'));
let total=0;
function compile(test,source,binary,allowWarnings=false){
  const result=spawnSync('sh',[join(support,'compile.sh'),root,test,source,binary],{encoding:'utf8',timeout:20000});
  if(result.status!==0)throw Error('Compilation failed: '+source+'\n'+result.stderr);
  if(!allowWarnings && result.stderr.trim())throw Error('Unexpected compiler warnings: '+result.stderr);
}
function run(binary){return spawnSync(binary,[],{encoding:'utf8',timeout:5000,killSignal:'SIGKILL'});}
function summary(result){
  const line=result.stdout?.split('\n').find(x=>x.startsWith('DSA_RESULT '));
  return line ? JSON.parse(line.slice(11)) : null;
}
try {
  for(const id of readdirSync(problems).sort()){
    const path=join(problems,id),test=join(path,'tests/test.c');
    const binary=join(build,id),reference=join(path,'implementation.c');
    compile(test,reference,binary);
    for(let i=0;i<repeat;++i){
      const result=run(binary),s=summary(result);
      if(result.status!==0||!s||!s.total||s.passed!==s.total)
        throw Error(id+' reference failed\n'+result.stdout+'\n'+result.stderr);
      if(i===0)total+=s.total;
    }
    compile(test,join(path,'starter.c'),binary);
    const starter=run(binary);
    if(starter.error || starter.signal) throw Error(id+' untouched starter must fail cleanly, not hang or crash');
    if(starter.status===0)throw Error(id+' untouched starter unexpectedly passes');
    const [before,after]=mutations[id];
    const text=readFileSync(reference,'utf8');
    if(!text.includes(before))throw Error(id+' mutation anchor missing');
    const mutant=join(build,id+'-mutant.c');writeFileSync(mutant,text.replace(before,after));
    compile(test,mutant,binary,true);
    if(run(binary).status===0)throw Error(id+' known incorrect implementation unexpectedly passes');
    console.log(id+': reference x'+repeat+' passed; starter and mutant rejected');
  }
  console.log('All 15 RTOS exercises passed: '+total+' checks per full reference run.');
} finally {
  rmSync(build,{recursive:true,force:true});
}
