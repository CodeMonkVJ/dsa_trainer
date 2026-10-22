import test from 'node:test';
import assert from 'node:assert/strict';
import { matchesProblemFilters } from './problem-filters.mjs';

test('difficulty and attempt filters combine across every option', () => {
  for (const difficulty of ['easy', 'medium', 'hard']) {
    for (const attempted of [false, true]) {
      const problem = { difficulty, attempted };
      for (const selected of ['all', 'easy', 'medium', 'hard']) {
        for (const status of ['all', 'attempted', 'unattempted']) {
          assert.equal(matchesProblemFilters(problem, selected, status),
            (selected === 'all' || selected === difficulty)
              && (status === 'all' || attempted === (status === 'attempted')));
        }
      }
    }
  }
});

test('solved implies attempted, while an untouched problem is unattempted', () => {
  assert.equal(matchesProblemFilters({ solved: true }, 'all', 'attempted'), true);
  assert.equal(matchesProblemFilters({ attempted: true, solved: false }, 'all', 'attempted'), true);
  assert.equal(matchesProblemFilters({}, 'all', 'unattempted'), true);
  assert.equal(matchesProblemFilters({ attempted: true }, 'all', 'unattempted'), false);
});
