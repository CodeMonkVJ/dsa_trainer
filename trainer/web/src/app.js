import { Terminal } from '@xterm/xterm';
import { FitAddon } from '@xterm/addon-fit';
import DOMPurify from 'dompurify';
import { marked } from 'marked';

marked.setOptions({ gfm: true });

const elements = {
  status: document.querySelector('#status'),
  catalog: document.querySelector('#catalog'),
  dashboard: document.querySelector('#dashboard-view'),
  practice: document.querySelector('#practice-view'),
  home: document.querySelector('#home-button'),
  timer: document.querySelector('#timer'),
  topicCategory: document.querySelector('#topic-category'),
  topicName: document.querySelector('#topic-name'),
  topicPrompt: document.querySelector('#topic-prompt'),
  terminal: document.querySelector('#terminal'),
  terminalOverlay: document.querySelector('#terminal-overlay'),
  start: document.querySelector('#start-button'),
  run: document.querySelector('#run-button'),
  submit: document.querySelector('#submit-button'),
  reveal: document.querySelector('#reveal-button'),
  cancel: document.querySelector('#cancel-button'),
  testOutput: document.querySelector('#test-output'),
  testSummary: document.querySelector('#test-summary'),
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
  referenceImplementation: null,
};

async function api(path, options = {}) {
  const response = await fetch(path, options);
  const payload = await response.json().catch(() => ({}));
  if (!response.ok) throw new Error(payload.error ?? `Request failed (${response.status})`);
  return payload;
}

async function loadCatalog() {
  const catalog = await api('/api/catalog');
  elements.catalog.replaceChildren(...catalog.categories.map(renderCategory));
  elements.status.textContent = 'Choose a topic to begin.';
}

function renderCategory(category) {
  const section = document.createElement('section');
  section.className = 'category';
  const heading = document.createElement('h2');
  heading.textContent = category.name;
  const topics = document.createElement('div');
  topics.className = 'topics';
  topics.replaceChildren(...category.topics.map((topic) => renderTopic(category, topic)));
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
  if (!topic.invalid) card.addEventListener('click', () => openTopic(category.id, topic.id));
  return card;
}

async function openTopic(category, topic) {
  const details = await api(`/api/topics/${category}/${topic}`);
  state.selectedTopic = details;
  elements.topicCategory.textContent = category;
  elements.topicName.textContent = details.metadata.name;
  elements.topicPrompt.innerHTML = DOMPurify.sanitize(marked.parse(details.prompt));
  renderHistory(details.history ?? []);
  elements.dashboard.classList.add('hidden');
  elements.practice.classList.remove('hidden');
  elements.start.disabled = details.active_attempt != null;
  state.testsPassed = false;
  resetHelp();
  setAttemptControls(false);
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
  elements.historySummary.textContent = attempts.length
    ? `${passes} solved · ${attempts.length} submitted`
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
    result.textContent = attempt.result === 'passed' ? 'Solved' : 'Failed';

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
  localStorage.setItem('dsa-active-topic', JSON.stringify({ category, topic: id }));
  elements.start.disabled = true;
  setAttemptControls(true);
  startTimer();
  connectTerminal();
  startPolling();
}

function startAttempt() {
  const { category, id } = state.selectedTopic;
  return beginAttempt(`/api/topics/${category}/${id}/attempts`);
}

function loadPreviousAttempt(attemptId) {
  const { category, id } = state.selectedTopic;
  return beginAttempt(`/api/topics/${category}/${id}/attempts/from/${encodeURIComponent(attemptId)}`);
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
  elements.timer.classList.toggle('yellow', seconds > state.attempt.target_seconds && seconds <= state.attempt.warning_seconds);
  elements.timer.classList.toggle('red', seconds > state.attempt.warning_seconds);
  const revealAvailable = seconds >= 15 * 60;
  elements.reveal.classList.toggle('hidden', !revealAvailable);
  elements.reveal.disabled = !revealAvailable;
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
  if (submit && !state.testsPassed) return;
  if (!submit) {
    state.testsPassed = false;
    setAttemptControls(true);
  }
  elements.testOutput.textContent = submit ? 'Submitting…' : 'Running tests…';
  elements.testSummary.textContent = '';
  elements.testSummary.className = 'test-summary hidden';
  elements.resultBadge.textContent = '';
  try {
    const result = await api(`/api/attempts/${state.attempt.id}/${submit ? 'submit' : 'run'}`, { method: 'POST' });
    renderTestOutput(result);
    elements.resultBadge.textContent = result.passed ? `${result.status} · passed` : `${result.status} · failed`;
    elements.resultBadge.className = result.status;
    if (!submit) {
      state.testsPassed = result.passed;
      setAttemptControls(true);
    }
    if (submit) {
      finishAttempt();
      const { category, id } = state.selectedTopic;
      const [details] = await Promise.all([
        api(`/api/topics/${category}/${id}`),
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
  const stdoutLines = String(result.stdout ?? '').split('\n');
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

  const remainingLines = [];
  for (const line of stdoutLines) {
    const match = line.trim().match(/^(PASS|FAIL)\s+(.+)$/);
    if (match) continue;
    else if (line.trim()) remainingLines.push(line);
  }

  if (testSummary && Number.isFinite(testSummary.passed) && Number.isFinite(testSummary.total)) {
    const allPassed = testSummary.passed === testSummary.total;
    elements.testSummary.textContent = `${testSummary.passed} / ${testSummary.total} tests ${allPassed ? 'passed' : 'passed'}`;
    elements.testSummary.className = `test-summary ${allPassed ? 'green' : 'red'}`;
  }

  const output = [remainingLines.join('\n').trim(), String(result.stderr ?? '').trim()]
    .filter(Boolean)
    .join('\n');
  elements.testOutput.textContent = output || 'No compiler output.';
}

async function cancelAttempt() {
  await api(`/api/attempts/${state.attempt.id}/cancel`, { method: 'POST' });
  finishAttempt();
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
  if (!window.confirm('Reveal the reference implementation? This attempt will be marked as reference-viewed.')) return;
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
}

function setAttemptControls(active) {
  elements.run.disabled = !active;
  elements.submit.disabled = !active || !state.testsPassed;
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
    await openTopic(topic.category, topic.topic);
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
  elements.practice.classList.add('hidden');
  elements.dashboard.classList.remove('hidden');
});
elements.start.addEventListener('click', () => startAttempt().catch((error) => showTerminalOverlay(error.message, true)));
elements.run.addEventListener('click', () => runTests(false));
elements.submit.addEventListener('click', () => runTests(true));
elements.reveal.addEventListener('click', () => revealReference());
elements.answer.addEventListener('click', revealImplementation);
elements.cancel.addEventListener('click', () => cancelAttempt().catch((error) => showTerminalOverlay(error.message, true)));

loadCatalog()
  .then(() => restoreAttempt())
  .catch((error) => { elements.status.textContent = error.message; });
