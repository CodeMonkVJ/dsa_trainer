# Job Sequencing

Implement `std::pair<int,int> jobScheduling(const std::vector<int>& deadline, const std::vector<int>& profit)`.

Each job takes one unit of time, earns its profit only if completed by its deadline, and at most one job runs per slot. Return `{jobs_completed, total_profit}` for a maximum-profit schedule. Ignore non-positive deadlines and mismatched trailing values. Aim for greedy scheduling by profit.
