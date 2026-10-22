export function matchesProblemFilters(problem, difficulty = 'all', attemptStatus = 'all') {
  const attempted = problem.attempted === true || problem.solved === true;
  return (difficulty === 'all' || problem.difficulty === difficulty)
    && (attemptStatus === 'all' || (attemptStatus === 'attempted' ? attempted : !attempted));
}
