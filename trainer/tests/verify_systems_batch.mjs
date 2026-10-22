import assert from 'node:assert/strict';
import {mkdtempSync,readFileSync,writeFileSync,rmSync} from 'node:fs';
import {tmpdir} from 'node:os';
import {dirname,join,resolve} from 'node:path';
import {fileURLToPath} from 'node:url';
import {spawnSync} from 'node:child_process';

const root=resolve(dirname(fileURLToPath(import.meta.url)),'../..');
const mutations={
 checked_arithmetic:[
  ['b > SIZE_MAX - a','b >= SIZE_MAX - a'],
  ['*out = a * b;','*out = a + b;'],
 ],
 arena_allocator:[
  ['mark.epoch != a->epoch ||','false ||'],
  ['a->used = offset + bytes;','a->used = offset;'],
 ],
 posix_io_adapter:[
  ['if (error == EINTR)\n      continue;','if (error == EINTR)\n      return io_result(IO_ERROR, done, error);'],
  ['if (now >= deadline)','if (now > deadline)'],
 ],
 recoverable_record_log:[
  ['if (crc != log_get32(p + 8))','if (false && crc != log_get32(p + 8))'],
  ['{LOG_TRUNCATED, offset, records}','{LOG_TRUNCATED, offset + 1, records}'],
 ],
};
const temp=mkdtempSync(join(tmpdir(),'interview-systems-batch-'));
function compile(test,source,binary,strict=true){
 const args=['-std=c17','-Wall','-Wextra','-Wpedantic','-pthread',...(strict?['-Werror']:[]),'-DDSA_IMPLEMENTATION="'+source+'"',test,'-o',binary];
 const result=spawnSync('gcc',args,{encoding:'utf8',timeout:15000});
 assert.equal(result.status,0,result.stderr);
}
function run(binary){return spawnSync(binary,[],{encoding:'utf8',timeout:5000,killSignal:'SIGKILL'});}
let count=0,mutantCount=0;
try {
 for(const [id,changes] of Object.entries(mutations)){
  const folder=join(root,'systems/programming/problems',id),test=join(folder,'tests/test.c'),binary=join(temp,id),reference=join(folder,'implementation.c');
  const metadata=JSON.parse(readFileSync(join(folder,'topic.json'),'utf8'));assert.deepEqual(metadata.languages,['c']);
  compile(test,reference,binary);
  for(let i=0;i<5;++i){
   const result=run(binary);assert.equal(result.status,0,result.stdout+'\n'+result.stderr);
   const summary=JSON.parse(result.stdout.split('\n').find(l=>l.startsWith('DSA_RESULT ')).slice(11));
   assert.equal(summary.passed,summary.total);assert.ok(summary.total>0);if(i===0)count+=summary.total;
  }
  compile(test,join(folder,'starter.c'),binary);const starter=run(binary);assert.equal(starter.status,1,id+' starter must fail cleanly');
  const original=readFileSync(reference,'utf8');
  for(const [before,after] of changes){
   assert.ok(original.includes(before),id+' missing mutation anchor');
   const source=join(temp,id+'-mutant.c');writeFileSync(source,original.replace(before,after));
   compile(test,source,binary,false);
   const result=run(binary);assert.notEqual(result.status,0,id+' mutation escaped');++mutantCount;
  }
  console.log(id+': 5 reference runs passed; starter and 2 mutants rejected');
 }
 for(const id of ['persistent_configuration','local_rpc_service']){
  const folder=join(root,'systems/design/problems',id);
  const metadata=JSON.parse(readFileSync(join(folder,'topic.json'),'utf8'));
  assert.deepEqual(metadata.languages,['md']);assert.equal(metadata.difficulty,'hard');
  assert.equal(metadata.green_seconds,900);assert.equal(metadata.yellow_seconds,1500);
  for(const name of ['prompt.md','starter.md','review.md','implementation.md'])assert.ok(readFileSync(join(folder,name),'utf8').trim());
  console.log(id+': design package validated');
 }
 console.log(count+' reference checks per run; '+mutantCount+' mutants rejected; both designs validated.');
} finally { rmSync(temp,{recursive:true,force:true}); }
