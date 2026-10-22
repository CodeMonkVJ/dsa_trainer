import { Terminal } from '@xterm/xterm';
import { FitAddon } from '@xterm/addon-fit';
import DOMPurify from 'dompurify';
import { marked } from 'marked';
import { matchesProblemFilters } from './problem-filters.mjs';

marked.setOptions({ gfm: true });

const elements = {
  status: document.querySelector('#status'),
  catalog: document.querySelector('#catalog'),
  difficultyFilter: document.querySelector('#difficulty-filter'),
  attemptFilter: document.querySelector('#attempt-filter'),
  dashboard: document.querySelector('#dashboard-view'),
  practice: document.querySelector('#practice-view'),
  home: document.querySelector('#home-button'),
  timer: document.querySelector('#timer'),
  topicCategory: document.querySelector('#topic-category'),
  topicName: document.querySelector('#topic-name'),
  topicDifficulty: document.querySelector('#topic-difficulty'),
  topicPrompt: document.querySelector('#topic-prompt'),
  problemPicker: document.querySelector('#problem-picker'),
  topicProblemSummary: document.querySelector('#topic-problem-summary'),
  terminal: document.querySelector('#terminal'),
  terminalOverlay: document.querySelector('#terminal-overlay'),
  start: document.querySelector('#start-button'),
  run: document.querySelector('#run-button'),
  submit: document.querySelector('#submit-button'),
  reveal: document.querySelector('#reveal-button'),
  cancel: document.querySelector('#cancel-button'),
  testOutput: document.querySelector('#test-output'),
  testSummary: document.querySelector('#test-summary'),
  testCaseViewer: document.querySelector('#test-case-viewer'),
  testCaseTitle: document.querySelector('#test-case-title'),
  testCasePosition: document.querySelector('#test-case-position'),
  testCaseStatus: document.querySelector('#test-case-status'),
  testCaseInput: document.querySelector('#test-case-input'),
  testCaseExpected: document.querySelector('#test-case-expected'),
  testCaseActual: document.querySelector('#test-case-actual'),
  testCaseDetails: document.querySelector('#test-case-details'),
  testCasePrev: document.querySelector('#test-case-prev'),
  testCaseNext: document.querySelector('#test-case-next'),
  resultBadge: document.querySelector('#result-badge'),
  historyList: document.querySelector('#history-list'),
  historySummary: document.querySelector('#history-summary'),
  helpPanel: document.querySelector('#help-panel'),
  answer: document.querySelector('#answer-button'),
  hint: document.querySelector('#hint-text'),
  reference: document.querySelector('#reference-code'),
};

const state = {
  selectedTopic: null,
  attempt: null,
  terminal: null,
  fitAddon: null,
  socket: null,
  timerInterval: null,
  pollInterval: null,
  testsPassed: false,
  testCases: [],
  testCaseIndex: 0,
  referenceImplementation: null,
  catalog: null,
};

async function api(path, options = {}) {
  const response = await fetch(path, options);
  const payload = await response.json().catch(() => ({}));
  if (!response.ok) throw new Error(payload.error ?? `Request failed (${response.status})`);
  return payload;
}

async function loadCatalog() {
  const catalog = await api('/api/catalog');
  state.catalog = catalog;
  renderCatalog();
  if (state.selectedTopic) renderProblemPicker(state.selectedTopic.category, state.selectedTopic.id);
}

function filteredProblems(topic) {
  return (topic.problems ?? []).filter((problem) => matchesProblemFilters(
    problem, elements.difficultyFilter.value, elements.attemptFilter.value,
  ));
}

function renderCatalog() {
  const categories = (state.catalog?.categories ?? []).map(renderCategory).filter(Boolean);
  elements.catalog.replaceChildren(...categories);
  elements.status.textContent = categories.length ? 'Choose a topic to begin.' : 'No problems match these filters.';
}

function renderCategory(category) {
  const visibleTopics = category.topics.filter((topic) => !topic.invalid && filteredProblems(topic).length);
  if (!visibleTopics.length) return null;
  const section = document.createElement('section');
  section.className = 'category';
  const heading = document.createElement('h2');
  heading.textContent = category.name;
  const topics = document.createElement('div');
  topics.className = 'topics';
  topics.replaceChildren(...visibleTopics.map((topic) => renderTopic(category, topic)));
  section.append(heading, topics);
  return section;
}

function renderTopic(category, topic) {
  const card = document.createElement('article');
  card.className = `topic${topic.invalid ? ' invalid' : ''}`;
  const heading = document.createElement('h3');
  const dot = document.createElement('span');
  dot.className = `topic-status ${topic.status ?? 'gray'}`;
  heading.append(dot, topic.name ?? topic.id);
  const details = document.createElement('p');
  details.textContent = topic.invalid ? `Not configured: ${topic.error}` : topic.description;
  card.append(heading, details);
  if (!topic.invalid && topic.problem_count != null) {
    const problemSummary = document.createElement('span');
    problemSummary.className = 'topic-problem-summary';
    problemSummary.textContent = `${topic.solved_count ?? 0} / ${topic.problem_count} solved`;
    card.append(problemSummary);
  }
  if (!topic.invalid && topic.elapsed_ms != null) {
    const progress = document.createElement('div');
    progress.className = `topic-progress ${topic.status ?? 'gray'}`;
    const outcome = document.createElement('strong');
    outcome.textContent = topic.passed ? 'Solved' : 'Last attempt failed';
    const metrics = document.createElement('span');
    metrics.textContent = `Submit ${formatDuration(topic.elapsed_ms)} · Run ${formatRuntime(topic.runtime_ms)} · ${formatMemory(topic.peak_memory_bytes)}`;
    progress.append(outcome, metrics);
    card.append(progress);

  }
  if (!topic.invalid) card.addEventListener('click', () => openTopic(category.id, topic.id, filteredProblems(topic)[0]?.id ?? 'base'));
  return card;
}

function topicApiPath(category, group, problem = 'base') {
  return problem === 'base'
    ? `/api/topics/${category}/${group}`
    : `/api/topics/${category}/${group}/problems/${problem}`;
}

async function openTopic(category, topic, problem = 'base') {
  if (hasActiveAttempt() && !isSelectedTopic(category, topic, problem)) {
    showTerminalOverlay(`Finish or cancel ${state.attempt.topic} before opening another problem.`, true);
    return;
  }
  const details = await api(topicApiPath(category, topic, problem));
  state.selectedTopic = details;
  renderProblemPicker(category, topic);
  elements.topicCategory.textContent = category;
  elements.topicName.textContent = details.metadata.name;
  elements.topicDifficulty.textContent = details.metadata.difficulty;
  elements.topicDifficulty.className = `difficulty-badge ${details.metadata.difficulty}`;
  elements.topicPrompt.innerHTML = DOMPurify.sanitize(marked.parse(details.prompt));
  renderHistory(details.history ?? []);
  elements.dashboard.classList.add('hidden');
  elements.practice.classList.remove('hidden');
  elements.start.disabled = details.active_attempt != null;
  state.testsPassed = false;
  resetHelp();
  setAttemptControls(false);
}

function renderProblemPicker(category, group) {
  const categoryEntry = state.catalog?.categories.find((entry) => entry.id === category);
  const topic = categoryEntry?.topics.find((entry) => entry.id === group);
  const problems = topic ? filteredProblems(topic) : [];
  elements.topicProblemSummary.textContent = topic
    ? `· ${topic.solved_count ?? 0} / ${topic.problem_count ?? problems.length} solved`
    : '';
  elements.problemPicker.replaceChildren();
  if (!problems.length) {
    const empty = document.createElement('p');
    empty.className = 'filter-empty';
    empty.textContent = 'No problems match these filters.';
    elements.problemPicker.append(empty);
  }
  for (const problem of problems) {
    const button = document.createElement('button');
    button.type = 'button';
    button.className = 'problem-link';
    const blockedByAttempt = hasActiveAttempt() && !isSelectedTopic(category, group, problem.id);
    button.disabled = blockedByAttempt;
    if (blockedByAttempt) button.title = 'Cancel the active problem before opening another problem.';
    const name = document.createElement('span');
    name.textContent = problem.name;
    const difficulty = document.createElement('small');
    difficulty.textContent = `${problem.difficulty ?? ''}${problem.languages?.includes('md') ? ' · Design' : ''}`;
    difficulty.className = `problem-difficulty ${problem.difficulty ?? ''}`;
    if (problem.solved) {
      const solved = document.createElement('small');
      solved.className = `problem-solved ${problem.status ?? 'gray'}`;
      solved.textContent = problem.languages?.includes('md') ? '✓ Self-reviewed' : '✓ Solved';
      solved.title = `${problem.languages?.includes('md') ? 'Self-reviewed' : 'Solved'} in ${problem.status ?? 'unknown'} time`;
      button.append(name, difficulty, solved);
    } else {
      button.append(name, difficulty);
    }
    button.classList.toggle('selected', problem.id === (state.selectedTopic.problem ?? 'base'));
    button.addEventListener('click', () => openTopic(category, group, problem.id));
    elements.problemPicker.append(button);
  }
}

function isDesignExercise() {
  return state.selectedTopic?.metadata.languages.includes('md') ?? false;
}

function resetHelp() {
  state.referenceImplementation = null;
  elements.reveal.classList.add('hidden');
  elements.reveal.disabled = true;
  elements.helpPanel.classList.add('hidden');
  elements.answer.classList.add('hidden');
  elements.answer.disabled = false;
  elements.hint.textContent = '';
  elements.reference.textContent = '';
  elements.reference.classList.add('hidden');
}

function renderHistory(history) {
  const attempts = [...history].reverse();
  const passes = attempts.filter((attempt) => attempt.result === 'passed').length;
  const reviews = attempts.filter((attempt) => attempt.result === 'self_reviewed').length;
  elements.historySummary.textContent = attempts.length
    ? `${passes} solved${reviews ? ` · ${reviews} self-reviewed` : ''} · ${attempts.length} submitted`
    : '';

  if (!attempts.length) {
    const empty = document.createElement('p');
    empty.className = 'history-empty';
    empty.textContent = 'No submitted attempts yet.';
    elements.historyList.replaceChildren(empty);
    return;
  }

  elements.historyList.replaceChildren(...attempts.map((attempt) => {
    const row = document.createElement('article');
    row.className = `history-entry ${attempt.status ?? 'red'}`;

    const result = document.createElement('strong');
    result.textContent = attempt.result === 'self_reviewed' ? 'Self-reviewed' : attempt.result === 'passed' ? 'Solved' : 'Failed';

    const meta = document.createElement('span');
    meta.textContent = `Submit ${formatDuration(attempt.elapsed_ms)} · Run ${formatRuntime(attempt.runtime_ms)} · ${formatMemory(attempt.peak_memory_bytes)} · ${String(attempt.language ?? '').toUpperCase()}`;

    row.append(result, meta);
    if (attempt.source_saved) {
      const load = document.createElement('button');
      load.type = 'button';
      load.className = 'history-load';
      load.textContent = 'Load into fresh attempt';
      load.addEventListener('click', (event) => {
        event.stopPropagation();
        loadPreviousAttempt(attempt.id).catch((error) => showTerminalOverlay(error.message, true));
      });
      row.append(load);
    } else {
      const unavailable = document.createElement('span');
      unavailable.className = 'history-source-unavailable';
      unavailable.textContent = 'Source snapshot unavailable';
      row.append(unavailable);
    }
    return row;
  }));
}

function formatDuration(milliseconds) {
  const totalSeconds = Math.max(0, Math.floor(Number(milliseconds) / 1000));
  const minutes = Math.floor(totalSeconds / 60);
  const seconds = totalSeconds % 60;
  return `${minutes}:${String(seconds).padStart(2, '0')}`;
}

function formatRuntime(milliseconds) {
  if (milliseconds == null) return 'not recorded';
  const runtime = Number(milliseconds);
  if (runtime < 1) return '<1 ms';
  if (runtime < 1000) return `${Math.round(runtime)} ms`;
  return `${(runtime / 1000).toFixed(2)} s`;
}

function formatMemory(bytes) {
  if (bytes == null) return 'Memory not recorded';
  const value = Number(bytes);
  if (value < 1024 * 1024) return `${Math.max(1, Math.round(value / 1024))} KiB`;
  return `${(value / (1024 * 1024)).toFixed(1)} MiB`;
}

async function beginAttempt(path) {
  const { category, id } = state.selectedTopic;
  state.attempt = {
    ...(await api(path, { method: 'POST' })),
    loaded_at: Date.now(),
  };
  state.testsPassed = false;
  resetHelp();
  localStorage.setItem('dsa-active-attempt', state.attempt.id);
  const topic = state.catalog?.categories.find((entry) => entry.id === category)?.topics.find((entry) => entry.id === id);
  const problem = topic?.problems.find((entry) => entry.id === state.selectedTopic.problem);
  if (problem) problem.attempted = true;
  renderCatalog();
  localStorage.setItem('dsa-active-topic', JSON.stringify({ category, topic: id, problem: state.selectedTopic.problem }));
  elements.start.disabled = true;
  setAttemptControls(true);
  startTimer();
  connectTerminal();
  startPolling();
  renderProblemPicker(category, id);
}

function startAttempt() {
  const { category, id, problem } = state.selectedTopic;
  return beginAttempt(`${topicApiPath(category, id, problem)}/attempts`);
}

function loadPreviousAttempt(attemptId) {
  const { category, id, problem } = state.selectedTopic;
  return beginAttempt(`${topicApiPath(category, id, problem)}/attempts/from/${encodeURIComponent(attemptId)}`);
}

function createTerminal() {
  if (state.terminal) return;
  state.terminal = new Terminal({
    cursorBlink: true,
    fontFamily: '"JetBrainsMono Nerd Font", "JetBrains Mono", monospace',
    fontSize: 14,
    lineHeight: 1.15,
    scrollback: 3000,
    theme: {
      background: '#080b10',
      foreground: '#d8dee9',
      cursor: '#82aaff',
      selectionBackground: '#264f78',
    },
  });
  state.fitAddon = new FitAddon();
  state.terminal.loadAddon(state.fitAddon);
  state.terminal.open(elements.terminal);
  state.terminal.onData((data) => sendTerminalInput(data));
  new ResizeObserver(() => fitTerminal()).observe(elements.terminal);
}

function connectTerminal() {
  createTerminal();
  showTerminalOverlay('Connecting to local Neovim…');
  const protocol = location.protocol === 'https:' ? 'wss:' : 'ws:';
  const socket = new WebSocket(`${protocol}//${location.host}/ws/attempts/${state.attempt.id}`);
  socket.binaryType = 'arraybuffer';
  state.socket = socket;
  socket.addEventListener('open', () => {
    hideTerminalOverlay();
    fitTerminal();
    state.terminal.focus();
  });
  socket.addEventListener('message', (event) => {
    if (event.data instanceof ArrayBuffer) state.terminal.write(new Uint8Array(event.data));
    else state.terminal.write(event.data);
  });
  socket.addEventListener('close', () => {
    if (state.attempt?.state === 'active' && !elements.terminalOverlay.classList.contains('error')) {
      showTerminalOverlay('Terminal disconnected. Refresh the page to reconnect.', true);
    }
  });
  socket.addEventListener('error', () => showTerminalOverlay('Unable to open Neovim. Refresh the page to retry.', true));
}

function sendTerminalInput(data) {
  if (state.socket?.readyState !== WebSocket.OPEN) return;
  const bytes = new TextEncoder().encode(data);
  for (let offset = 0; offset < bytes.length; offset += 8192) {
    state.socket.send(bytes.slice(offset, offset + 8192));
  }
}

function fitTerminal() {
  if (!state.terminal || state.socket?.readyState !== WebSocket.OPEN) return;
  state.fitAddon.fit();
  state.socket.send(`resize:${state.terminal.cols}:${state.terminal.rows}`);
}

function startTimer() {
  clearInterval(state.timerInterval);
  elements.timer.classList.remove('hidden');
  updateTimer();
  state.timerInterval = setInterval(updateTimer, 250);
}

function updateTimer() {
  if (!state.attempt) return;
  const elapsed = state.attempt.elapsed_ms + (Date.now() - state.attempt.loaded_at);
  const seconds = Math.max(0, Math.floor(elapsed / 1000));
  elements.timer.textContent = `${String(Math.floor(seconds / 60)).padStart(2, '0')}:${String(seconds % 60).padStart(2, '0')}`;
  elements.timer.classList.toggle('yellow', seconds > state.attempt.green_seconds && seconds <= state.attempt.yellow_seconds);
  elements.timer.classList.toggle('red', seconds > state.attempt.yellow_seconds);
  const revealAvailable = seconds > state.attempt.yellow_seconds;
  elements.reveal.classList.toggle('hidden', !revealAvailable);
  elements.reveal.disabled = !revealAvailable;
  elements.reveal.textContent = revealAvailable ? 'Show hint' : `Hint after ${formatSeconds(state.attempt.yellow_seconds)}`;
}

function formatSeconds(seconds) {
  const minutes = Math.floor(Number(seconds) / 60);
  const remainder = Number(seconds) % 60;
  return `${minutes}:${String(remainder).padStart(2, '0')}`;
}

function hasActiveAttempt() {
  return state.attempt?.state === 'active';
}

function isSelectedTopic(category, topic, problem = 'base') {
  return state.selectedTopic?.category === category && state.selectedTopic?.id === topic && (state.selectedTopic?.problem ?? 'base') === problem;
}

function startPolling() {
  clearInterval(state.pollInterval);
  state.pollInterval = setInterval(pollAttempt, 1000);
}

async function pollAttempt() {
  if (!state.attempt) return;
  try {
    const latest = await api(`/api/attempts/${state.attempt.id}`);
    state.attempt = { ...latest, loaded_at: Date.now() };
    if (latest.editor_state === 'exited') {
      state.socket?.close();
      showTerminalOverlay('Editor exited — refresh the page to reopen it.', true);
    }
  } catch (error) {
    console.error(error);
  }
}

async function runTests(submit) {
  const design = isDesignExercise();
  if (submit && !design && !state.testsPassed) return;
  if (submit && design && !window.confirm('Save your design as self-reviewed? This records your own assessment, not an automated correctness grade. Save your editor changes first.')) return;
  if (!submit) {
    state.testsPassed = false;
    setAttemptControls(true);
  }
  elements.testOutput.textContent = submit ? 'Saving…' : design ? 'Loading checklist…' : 'Running tests…';
  elements.testSummary.textContent = '';
  elements.testSummary.className = 'test-summary hidden';
  clearTestCases();
  elements.resultBadge.textContent = '';
  try {
    const result = await api(`/api/attempts/${state.attempt.id}/${submit ? 'submit' : 'run'}`, { method: 'POST' });
    renderTestOutput(result);
    const outcome = result.outcome ?? (result.passed ? 'passed' : result.phase === 'compilation' ? 'compiler_error' : 'test_failed');
    elements.resultBadge.textContent = design ? (submit ? 'Self-reviewed' : 'Manual review required') : result.passed ? `${result.status} · passed` : outcomeLabel(outcome);
    elements.resultBadge.className = design ? (submit ? result.status : '') : result.passed ? result.status : outcomeClass(outcome);
    if (!submit) {
      state.testsPassed = result.passed;
      setAttemptControls(true);
    }
    if (submit) {
      finishAttempt();
      const { category, id, problem } = state.selectedTopic;
      const [details] = await Promise.all([
        api(topicApiPath(category, id, problem)),
        loadCatalog(),
      ]);
      state.selectedTopic = details;
      renderHistory(details.history ?? []);
    }
  } catch (error) {
    elements.testOutput.textContent = error.message;
    elements.resultBadge.textContent = 'error';
    elements.resultBadge.className = 'red';
  }
}

function renderTestOutput(result) {
  if (result.phase === 'review') {
    clearTestCases();
    elements.testOutput.textContent = result.stdout;
    elements.testSummary.textContent = 'Design practice: assess your answer against this checklist. No automated grading.';
    elements.testSummary.className = 'test-summary';
    return;
  }
  const stdoutLines = String(result.stdout ?? '').replaceAll('\\n', '\n').split('\n');
  const markerIndex = stdoutLines.findIndex((line) => line.trimStart().startsWith('DSA_RESULT '));
  let testSummary = null;
  if (markerIndex >= 0) {
    const marker = stdoutLines[markerIndex].trim().slice('DSA_RESULT '.length);
    try {
      testSummary = JSON.parse(marker);
      stdoutLines.splice(markerIndex, 1);
    } catch {
      // Keep malformed output visible instead of hiding useful test information.
    }
  }

  const outcome = result.outcome ?? (result.passed ? 'passed' : result.phase === 'compilation' ? 'compiler_error' : 'test_failed');
  const testCases = [];
  const remainingLines = [];
  for (const line of stdoutLines) {
    const trimmed = line.trim();
    const structured = trimmed.match(/^DSA_CASE\s+(\{.*\})$/);
    if (structured) {
      try {
        const testCase = JSON.parse(structured[1]);
        testCases.push({
          source: 'structured',
          status: testCase.passed === true || testCase.status === 'pass' ? 'pass' : 'fail',
          input: testCase.input,
          expected: stringifyCaseValue(testCase.expected),
          actual: stringifyCaseValue(testCase.actual),
          details: testCase.details ?? '',
        });
        continue;
      } catch {
        // Keep malformed markers visible below.
      }
    }
    const match = trimmed.match(/^(PASS|FAIL)\s+(.+)$/);
    if (match) {
      const status = match[1].toLowerCase();
      const assertion = match[2].match(/^(.+?)\s*:\s*expected\s+(.+?),\s*got\s+(.+)$/);
      testCases.push({
        source: 'legacy',
        status,
        input: '',
        expected: assertion ? assertion[2] : 'true',
        actual: assertion ? assertion[3] : status === 'pass' ? 'true' : 'false',
        details: assertion ? 'The test harness reports expected and actual values, but does not emit the original input.' : 'This legacy test harness reports only PASS/FAIL and does not emit input or result values.',
      });
    }
    else if (trimmed) remainingLines.push(line);
  }

  const stderr = String(result.stderr ?? '').trim();
  const structuredCases = testCases.filter((testCase) => testCase.source === 'structured');
  if (structuredCases.length) {
    testCases.splice(0, testCases.length, ...structuredCases);
  }
  if (outcome === 'compiler_error' || outcome === 'time_limit_exceeded' || outcome === 'runtime_error') {
    testCases.length = 0;
    testCases.push({
      status: outcome === 'time_limit_exceeded' ? 'timeout' : 'error',
      input: 'Test harness completed without a structured case result',
      expected: 'true',
      actual: 'false',
      details: [remainingLines.join('\n').trim(), stderr].filter(Boolean).join('\n\n'),
    });
  } else if (!testCases.length && (remainingLines.length || stderr)) {
    testCases.push({
      status: result.passed ? 'pass' : 'fail',
      input: '',
      expected: '',
      actual: '',
      details: [remainingLines.join('\n').trim(), stderr].filter(Boolean).join('\n\n'),
    });
  }
  state.testCases = testCases;
  state.testCaseIndex = testCases.findIndex((testCase) => testCase.status === 'fail');
  if (state.testCaseIndex < 0) state.testCaseIndex = 0;
  renderTestCase();

  if (testSummary && Number.isFinite(testSummary.passed) && Number.isFinite(testSummary.total)) {
    const allPassed = testSummary.passed === testSummary.total;
    elements.testSummary.textContent = `${testSummary.passed} / ${testSummary.total} tests ${allPassed ? 'passed' : 'passed'}`;
    elements.testSummary.className = `test-summary ${allPassed ? 'green' : 'red'}`;
  }

  const output = [remainingLines.join('\n').trim(), stderr]
    .filter(Boolean)
    .join('\n');
  elements.testOutput.textContent = output || 'No compiler output.';
}

function clearTestCases() {
  state.testCases = [];
  state.testCaseIndex = 0;
  elements.testCaseViewer.classList.add('hidden');
  elements.testCaseTitle.textContent = '';
  elements.testCasePosition.textContent = '';
  elements.testCaseStatus.textContent = '';
  elements.testCaseInput.textContent = '';
  elements.testCaseExpected.textContent = '';
  elements.testCaseActual.textContent = '';
  elements.testCaseDetails.textContent = '';
}

function renderTestCase() {
  if (!state.testCases.length) {
    elements.testCaseViewer.classList.add('hidden');
    return;
  }
  const testCase = state.testCases[state.testCaseIndex];
  elements.testCaseViewer.classList.remove('hidden');
  elements.testCaseTitle.textContent = testCase.status === 'pass' ? 'Test passed' : testCase.status === 'fail' ? 'Test did not pass' : outcomeLabel(testCase.status === 'timeout' ? 'time_limit_exceeded' : 'runtime_error');
  elements.testCasePosition.textContent = `${state.testCaseIndex + 1} / ${state.testCases.length}`;
  elements.testCaseStatus.textContent = testCase.status === 'pass' ? 'Passed' : testCase.status === 'fail' ? 'Failed' : outcomeLabel(testCase.status === 'timeout' ? 'time_limit_exceeded' : 'runtime_error');
  elements.testCaseStatus.className = `test-case-status ${testCase.status}`;
  elements.testCaseInput.textContent = formatCaseInput(testCase.input);
  elements.testCaseExpected.textContent = testCase.expected || '—';
  elements.testCaseActual.textContent = testCase.actual || '—';
  elements.testCaseDetails.textContent = testCase.details || (testCase.status === 'pass' ? 'The implementation returned the expected result.' : 'This test did not pass.');
  elements.testCasePrev.disabled = state.testCaseIndex === 0;
  elements.testCaseNext.disabled = state.testCaseIndex === state.testCases.length - 1;
}

function stringifyCaseValue(value) {
  if (value == null) return '';
  if (typeof value === 'string') return value;
  try { return JSON.stringify(value, null, 2); } catch { return String(value); }
}

function formatCaseInput(input) {
  if (input == null || input === '') return 'Not emitted by this test';
  if (typeof input === 'object' && !Array.isArray(input)) {
    return Object.entries(input)
      .map(([key, value]) => `${key}: ${formatInlineCaseValue(value)}`)
      .join('\n');
  }
  return formatInlineCaseValue(input);
}

function formatInlineCaseValue(value) {
  if (typeof value === 'string') return value;
  try { return JSON.stringify(value); } catch { return String(value); }
}

function outcomeLabel(outcome) {
  return ({
    passed: 'Passed',
    test_failed: 'Tests did not pass',
    compiler_error: 'Compiler error',
    time_limit_exceeded: 'Time limit exceeded',
    runtime_error: 'Runtime error',
  })[outcome] ?? 'Test error';
}

function outcomeClass(outcome) {
  return outcome === 'time_limit_exceeded' ? 'yellow' : 'red';
}

async function cancelAttempt() {
  if (!state.attempt) return;
  elements.cancel.disabled = true;
  elements.cancel.textContent = 'Cancelling…';
  try {
    await api(`/api/attempts/${state.attempt.id}/cancel`, { method: 'POST' });
    finishAttempt();
  } finally {
    elements.cancel.textContent = 'Cancel';
    if (hasActiveAttempt()) elements.cancel.disabled = false;
  }
}

async function revealReference() {
  if (!state.attempt) return;
  elements.reveal.disabled = true;
  try {
    const result = await api(`/api/attempts/${state.attempt.id}/reveal`, { method: 'POST' });
    state.attempt.reference_viewed = result.reference_viewed;
    state.referenceImplementation = result.implementation;
    elements.helpPanel.classList.remove('hidden');
    elements.hint.textContent = result.hint;
    elements.answer.classList.remove('hidden');
  } catch (error) {
    elements.reveal.disabled = false;
    showTerminalOverlay(error.message, true);
  }
}

function revealImplementation() {
  if (!state.referenceImplementation) return;
  if (!window.confirm(`Reveal the reference ${isDesignExercise() ? 'design' : 'implementation'}? This attempt will be marked as reference-viewed.`)) return;
  elements.reference.textContent = state.referenceImplementation;
  elements.reference.classList.remove('hidden');
  elements.answer.disabled = true;
}

function finishAttempt() {
  state.attempt.state = 'finished';
  state.socket?.close();
  clearInterval(state.timerInterval);
  clearInterval(state.pollInterval);
  localStorage.removeItem('dsa-active-attempt');
  localStorage.removeItem('dsa-active-topic');
  setAttemptControls(false);
  elements.timer.classList.add('hidden');
  resetHelp();
  elements.start.disabled = false;
  state.testsPassed = false;
  if (state.selectedTopic) renderProblemPicker(state.selectedTopic.category, state.selectedTopic.id);
}

function setAttemptControls(active) {
  const design = isDesignExercise();
  elements.run.textContent = design ? 'Review checklist' : 'Run tests';
  elements.submit.textContent = design ? 'Save self-review' : 'Submit';
  elements.answer.textContent = design ? 'Reveal reference design' : 'Reveal implementation';
  elements.run.disabled = !active;
  elements.submit.disabled = !active || (!design && !state.testsPassed);
  elements.cancel.disabled = !active;
}

function showTerminalOverlay(message, error = false) {
  elements.terminalOverlay.textContent = message;
  elements.terminalOverlay.classList.toggle('error', error);
  elements.terminalOverlay.classList.remove('hidden');
}

function hideTerminalOverlay() {
  elements.terminalOverlay.classList.add('hidden');
  elements.terminalOverlay.classList.remove('error');
}

async function restoreAttempt() {
  const attemptId = localStorage.getItem('dsa-active-attempt');
  const topic = JSON.parse(localStorage.getItem('dsa-active-topic') ?? 'null');
  if (!attemptId || !topic) return false;
  try {
    await openTopic(topic.category, topic.topic, topic.problem ?? 'base');
    const attempt = await api(`/api/attempts/${attemptId}`);
    if (attempt.state !== 'active') return false;
    state.attempt = { ...attempt, loaded_at: Date.now() };
    resetHelp();
    elements.start.disabled = true;
    setAttemptControls(true);
    startTimer();
    connectTerminal();
    startPolling();
    return true;
  } catch {
    localStorage.removeItem('dsa-active-attempt');
    localStorage.removeItem('dsa-active-topic');
    return false;
  }
}

elements.home.addEventListener('click', () => {
  if (hasActiveAttempt()) {
    showTerminalOverlay('Finish or cancel the active problem before navigating away.', true);
    return;
  }
  elements.practice.classList.add('hidden');
  elements.dashboard.classList.remove('hidden');
});
for (const filter of [elements.difficultyFilter, elements.attemptFilter]) {
  filter.addEventListener('change', () => {
    renderCatalog();
    if (state.selectedTopic) renderProblemPicker(state.selectedTopic.category, state.selectedTopic.id);
  });
}
elements.start.addEventListener('click', () => startAttempt().catch((error) => showTerminalOverlay(error.message, true)));
elements.run.addEventListener('click', () => runTests(false));
elements.submit.addEventListener('click', () => runTests(true));
elements.reveal.addEventListener('click', () => revealReference());
elements.answer.addEventListener('click', revealImplementation);
elements.cancel.addEventListener('click', () => cancelAttempt().catch((error) => showTerminalOverlay(error.message, true)));
elements.testCasePrev.addEventListener('click', () => {
  if (state.testCaseIndex > 0) { state.testCaseIndex -= 1; renderTestCase(); }
});
elements.testCaseNext.addEventListener('click', () => {
  if (state.testCaseIndex < state.testCases.length - 1) { state.testCaseIndex += 1; renderTestCase(); }
});

loadCatalog()
  .then(() => restoreAttempt())
  .catch((error) => { elements.status.textContent = error.message; });
