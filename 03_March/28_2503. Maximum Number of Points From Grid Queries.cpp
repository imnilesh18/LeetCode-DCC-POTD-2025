/*
 * 2503. Maximum Number of Points From Grid Queries
 *
 * You are given an m x n integer matrix grid and an array queries of size k.
 *
 * Find an array answer of size k such that for each integer queries[i] you start in the top left cell of the matrix and repeat the following process:
 *
 * If queries[i] is strictly greater than the value of the current cell that you are in, then you get one point if it is your first time visiting this cell, and you can move to any adjacent cell in all 4 directions: up, down, left, and right.
 * Otherwise, you do not get any points, and you end this process.
 * After the process, answer[i] is the maximum number of points you can get. Note that for each query you are allowed to visit the same cell multiple times.
 *
 * Return the resulting array answer.
 *
 * Example 1:
 * Input: grid = [[1,2,3],[2,5,7],[3,5,1]], queries = [5,6,2]
 * Output: [5,8,1]
 * Explanation: The diagrams above show which cells we visit to get points for each query.
 *
 * Example 2:
 * Input: grid = [[5,2,1],[1,1,2]], queries = [3]
 * Output: [0]
 * Explanation: We can not get any points because the value of the top left cell is already greater than or equal to 3.
 *
 * Constraints:
 * m == grid.length
 * n == grid[i].length
 * 2 <= m, n <= 1000
 * 4 <= m * n <= 10^5
 * k == queries.length
 * 1 <= k <= 10^4
 * 1 <= grid[i][j], queries[i] <= 10^6
 */

// Approach 1 (BFS): Use BFS starting from the top-left cell for each query; traverse adjacent cells that satisfy grid[i][j] < query value, counting each unique visit.
// Time Complexity: O(k * m * n) in the worst-case since each query may traverse all cells using BFS.
// Space Complexity: O(m * n) for the visited matrix and BFS queue during traversal.
class Solution {
public:
    // Directions for moving right, left, down, and up
    vector<vector<int>> directions = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };

    // Performs a BFS traversal from the starting cell (0,0) and counts the points (cells visited)
    // that have a grid value strictly less than the given query value.
    int bfs(vector<vector<int>>& grid, int val, int m, int n) {
        queue<pair<int, int>> que;

        que.push({ 0, 0 });
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        visited[0][0] = true;

        int points = 0;
        while (!que.empty()) {
            int N = que.size();

            while (N--) {
                auto [i, j] = que.front();
                que.pop();

                // If the current cell's value is not less than query value, skip further processing.
                if (grid[i][j] >= val) {
                    continue;
                }

                // Increment points as it's the first time visiting this valid cell.
                points++;

                // Explore all 4 adjacent directions.
                for (auto& dir : directions) {
                    int i_ = i + dir[0];
                    int j_ = j + dir[1];

                    // Check if the adjacent cell is within bounds, unvisited, and its value is less than the query value.
                    if (i_ >= 0 && i_ < m && j_ >= 0 && j_ < n && !visited[i_][j_] && grid[i_][j_] < val) {
                        que.push({ i_, j_ });
                        visited[i_][j_] = true;
                    }
                }
            }
        }
        return points;
    }
    // For each query, perform BFS to calculate the maximum points obtainable.
    vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {
        int         m = grid.size();
        int         n = grid[0].size();
        int         Q = queries.size();
        vector<int> result(Q, 0);

        // Process each query separately.
        for (int i = 0; i < Q; i++) {
            result[i] = bfs(grid, queries[i], m, n);
        }

        return result;
    }
};

/*
 * Dry Run
 * ----------
 * Example:
 * grid = [[1, 2, 3],
 *      [2, 5, 7],
 *      [3, 5, 1]]
 * query = 5
 *
 * Step 1: Start BFS from (0,0):
 *  - grid[0][0] = 1 < 5, so count 1 point.
 *  - Neighbors added: (0,1) [value 2] and (1,0) [value 2].
 *
 * Step 2: Process (0,1):
 *  - grid[0][1] = 2 < 5, count point.
 *  - Neighbors added if valid and not visited.
 *
 * Step 3: Process (1,0):
 *  - grid[1][0] = 2 < 5, count point.
 *  - Continue adding valid neighbors.
 *
 * Step 4: Continue BFS until no more cells with value < 5 can be visited.
 *  - Total points accumulated = 5.
 *
 * This dry run demonstrates the BFS traversal that collects points only from cells with values less than the query.
 */

// Approach 2 (DFS): Use DFS starting from the top-left cell for each query; recursively visit adjacent cells that have a value less than the query, marking visited cells and counting points.
// Time Complexity: O(k * m * n) in the worst-case since each query may traverse all cells using DFS.
// Space Complexity: O(m * n) for the recursion call stack and visited matrix in the worst-case.
class Solution {
public:
    // Directions for moving right, left, down, and up.
    vector<vector<int>> directions = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };

    // DFS function that returns the number of points from cell (i, j) where grid[i][j] < query value.
    int dfs(vector<vector<int>>& grid, int i, int j, int val, vector<vector<bool>>& visited, int m, int n) {
        // Check boundary conditions, visited status, and if the current cell's value is not less than query value.
        if (i < 0 || i >= m || j < 0 || j >= n || visited[i][j] || grid[i][j] >= val) {
            return 0;
        }

        // Mark the cell as visited and count it as a valid point.
        visited[i][j] = true;
        int points = 1;

        // Recursively explore all 4 adjacent directions.
        for (auto& dir : directions) {
            int i_ = i + dir[0];
            int j_ = j + dir[1];
            points += dfs(grid, i_, j_, val, visited, m, n);
        }

        return points;
    }
    // For each query, use DFS starting from (0, 0) to count how many points (cells) can be obtained.
    vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {
        int         m = grid.size();
        int         n = grid[0].size();
        int         Q = queries.size();
        vector<int> result(Q, 0);

        // Process each query separately.
        for (int i = 0; i < Q; i++) {
            // Create a fresh visited matrix for each query.
            vector<vector<bool>> visited(m, vector<bool>(n, false));
            result[i] = dfs(grid, 0, 0, queries[i], visited, m, n);
        }

        return result;
    }
};

/*
 * Dry Run
 * ----------
 * Example:
 * grid = [[1, 2, 3],
 *      [2, 5, 7],
 *      [3, 5, 1]]
 * query = 5
 *
 * Step 1: Call dfs(grid, 0, 0, 5, visited, 3, 3)
 *  - At (0,0): grid[0][0] = 1 < 5, mark visited, count = 1.
 *  - Explore neighbors:
 *       - (0,1): grid[0][1] = 2 < 5, mark visited, count = 1.
 *       - (1,0): grid[1][0] = 2 < 5, mark visited, count = 1.
 *       - Others are either out of bounds or already visited.
 *
 * Step 2: From (0,1):
 *  - Explore neighbors such as (0,2) and (1,1):
 *       - (0,2): grid[0][2] = 3 < 5, count and mark visited.
 *       - (1,1): grid[1][1] = 5, not valid as it is not less than 5.
 *
 * Step 3: From (1,0):
 *  - Explore neighbor (2,0): grid[2][0] = 3 < 5, count and mark visited.
 *  - Other neighbors are either out of bounds, visited, or not valid.
 *
 * Step 4: Continue DFS until all valid cells (with value < 5) are visited.
 *  - Total points accumulated = 5.
 *
 * This dry run demonstrates how DFS traverses all valid cells starting from (0,0) for a given query.
 */

// Approach: Sort the queries and use a min-heap (priority queue) to traverse the grid starting from (0,0);
//           for each query, pop and process cells with grid value less than the query, and count unique cells visited.
// Time Complexity: O((m*n + Q) * log(m*n)) since each cell is processed once in the heap and each query is handled in sorted order.
// Space Complexity: O(m*n) due to the visited matrix and the priority queue storage.

class Solution {
public:
    vector<vector<int>> directions = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };    // Directions: right, left, down, up

    vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {
        int         m = grid.size();                 // number of rows in grid
        int         n = grid[0].size();              // number of columns in grid
        int         Q = queries.size();              // number of queries
        vector<int> result(Q, 0);                    // result vector initialized with zeros

        vector<pair<int, int>> sortedQ;             // pair: (query value, original index)

        for (int i = 0; i < Q; i++) {
            sortedQ.push_back({ queries[i], i });    // pairing each query with its index
        }

        sort(begin(sortedQ), end(sortedQ));          // sort queries by query value

        // Priority queue (min-heap) where each element is a vector: {grid value, row index, col index}
        priority_queue<vector<int>, vector<vector<int>>, greater<>> pq;
        vector<vector<bool> > visited(m, vector<bool>(n, false)); // visited matrix to avoid reprocessing cells
        int points = 0;                                           // counter for points (cells visited with grid value < query)

        pq.push({ grid[0][0], 0, 0 });                            // start with the top-left cell
        visited[0][0] = true;                                     // mark the starting cell as visited

        // Process each query in increasing order of query value
        for (int i = 0; i < Q; i++) {
            int queryValue = sortedQ[i].first;       // current query value
            int idx        = sortedQ[i].second;      // original index of the current query

            // Process all cells with grid value less than the current query value
            while (!pq.empty() && pq.top()[0] < queryValue) {
                int i_curr = pq.top()[1];            // current cell row index
                int j_curr = pq.top()[2];            // current cell column index
                pq.pop();                            // remove the cell from the queue
                points++;                            // increment points since this cell's value is less than query

                // Explore all 4 adjacent directions from the current cell
                for (auto& dir : directions) {
                    int i_new = i_curr + dir[0];      // new row index
                    int j_new = j_curr + dir[1];      // new column index

                    // Check boundaries and if the cell has not been visited yet
                    if (i_new >= 0 && i_new < m && j_new >= 0 && j_new < n && !visited[i_new][j_new]) {
                        pq.push({ grid[i_new][j_new], i_new, j_new });    // push new cell with its grid value
                        visited[i_new][j_new] = true;                     // mark new cell as visited
                    }
                }
            }
            // Store the computed points for the query at its original index
            result[idx] = points;
        }
        return result;      // return the result for all queries
    }
};

/*
 * Dry Run (Detailed Visualization):
 *
 * Example Input:
 *    grid = [
 *             [1, 2, 3],
 *             [2, 5, 7],
 *             [3, 5, 1]
 *           ]
 *    queries = [5, 6, 2]
 *
 * Step 1: Preprocess Queries
 *    - Original query pairs:
 *          (5, 0), (6, 1), (2, 2)
 *    - After sorting by query value (ascending):
 *          sortedQ = [(2, 2), (5, 0), (6, 1)]
 *    - This means process queries in order: 2, then 5, then 6.
 *
 * Step 2: Initialization:
 *    - m = 3, n = 3, Q = 3.
 *    - result = [0, 0, 0]
 *    - visited matrix: all cells set to false initially.
 *    - points = 0.
 *    - Priority Queue (pq) starts with:
 *         pq = [ {1, 0, 0} ]   // (grid[0][0] = 1)
 *         Mark visited[0][0] = true.
 *
 *    Visual PQ:
 *         +----------+
 *         | [1,0,0]  |   <-- Top
 *         +----------+
 *
 * --------------------------------------------------
 * Iteration for sortedQ[0] (Query = 2, Original Index = 2):
 *    Query Value = 2
 *
 *    -- PQ State Before Processing --
 *         PQ:
 *             +----------+
 *             | [1,0,0]  |   <-- Top (value=1)
 *             +----------+
 *
 *    While Loop:
 *         Condition: pq.top()[0] = 1 < 2  → TRUE.
 *
 *    Iteration 1.1:
 *         - Pop: Remove [1,0,0] from pq.
 *         - Action: Increment points (points becomes 1).
 *         - Process neighbors of cell (0,0):
 *             • Right: (0,1) → grid[0][1] = 2, not visited, push [2,0,1], mark visited.
 *             • Left: (0,-1) → Out of bounds.
 *             • Down: (1,0) → grid[1][0] = 2, not visited, push [2,1,0], mark visited.
 *             • Up: (-1,0) → Out of bounds.
 *
 *    -- PQ State After Processing Neighbors --
 *         PQ now contains:
 *             +----------+
 *             | [2,0,1]  |   <-- Top (value=2)
 *             +----------+
 *             | [2,1,0]  |
 *             +----------+
 *
 *    While Loop Check:
 *         Condition: Top value = 2 is NOT less than query value (2) → Exit loop.
 *
 *    - Set result for original index 2:
 *         result[2] = 1
 *
 * --------------------------------------------------
 * Iteration for sortedQ[1] (Query = 5, Original Index = 0):
 *    Query Value = 5
 *
 *    -- PQ State Before Processing --
 *         PQ:
 *             +----------+
 *             | [2,0,1]  |   <-- Top (value=2)
 *             +----------+
 *             | [2,1,0]  |
 *             +----------+
 *
 *    While Loop (Process until top value is NOT less than 5):
 *
 *    Iteration 2.1:
 *         - Pop: Remove [2,0,1] (top element).
 *         - Action: Increment points (points becomes 2).
 *         - Process neighbors of cell (0,1):
 *             • Right: (0,2) → grid[0][2] = 3, not visited, push [3,0,2], mark visited.
 *             • Left: (0,0) → Already visited.
 *             • Down: (1,1) → grid[1][1] = 5, not visited, push [5,1,1], mark visited.
 *             • Up: (-1,1) → Out of bounds.
 *
 *         -- PQ State After Processing (Visual) --
 *             PQ now contains:
 *                 +----------+
 *                 | [2,1,0]  |   <-- Top (value=2)
 *                 +----------+
 *                 | [3,0,2]  |
 *                 +----------+
 *                 | [5,1,1]  |
 *                 +----------+
 *
 *    Iteration 2.2:
 *         -- PQ State Before Pop --
 *             PQ:
 *                 +----------+
 *                 | [2,1,0]  |   <-- Top (value=2)
 *                 +----------+
 *                 | [3,0,2]  |
 *                 +----------+
 *                 | [5,1,1]  |
 *                 +----------+
 *         - Pop: Remove [2,1,0].
 *         - Action: Increment points (points becomes 3).
 *         - Process neighbors of cell (1,0):
 *             • Right: (1,1) → Already visited.
 *             • Left: (1,-1) → Out of bounds.
 *             • Down: (2,0) → grid[2][0] = 3, not visited, push [3,2,0], mark visited.
 *             • Up: (0,0) → Already visited.
 *
 *         -- PQ After Processing --
 *             PQ now contains:
 *                 +----------+
 *                 | [3,0,2]  |   <-- Top (value=3)
 *                 +----------+
 *                 | [5,1,1]  |
 *                 +----------+
 *                 | [3,2,0]  |
 *                 +----------+
 *
 *    Iteration 2.3:
 *         -- PQ State Before Pop --
 *             PQ:
 *                 +----------+
 *                 | [3,0,2]  |   <-- Top (value=3)
 *                 +----------+
 *                 | [3,2,0]  |
 *                 +----------+
 *                 | [5,1,1]  |
 *                 +----------+
 *         - Pop: Remove [3,0,2].
 *         - Action: Increment points (points becomes 4).
 *         - Process neighbors of cell (0,2):
 *             • Right: (0,3) → Out of bounds.
 *             • Left: (0,1) → Already visited.
 *             • Down: (1,2) → grid[1][2] = 7, not visited, push [7,1,2], mark visited.
 *             • Up: (-1,2) → Out of bounds.
 *
 *         -- PQ After Processing --
 *             PQ now contains:
 *                 +----------+
 *                 | [3,2,0]  |   <-- Top (value=3)
 *                 +----------+
 *                 | [5,1,1]  |
 *                 +----------+
 *                 | [7,1,2]  |
 *                 +----------+
 *
 *    Iteration 2.4:
 *         -- PQ State Before Pop --
 *             PQ:
 *                 +----------+
 *                 | [3,2,0]  |   <-- Top (value=3)
 *                 +----------+
 *                 | [5,1,1]  |
 *                 +----------+
 *                 | [7,1,2]  |
 *                 +----------+
 *         - Pop: Remove [3,2,0].
 *         - Action: Increment points (points becomes 5).
 *         - Process neighbors of cell (2,0):
 *             • Right: (2,1) → grid[2][1] = 5, not visited, push [5,2,1], mark visited.
 *             • Left: (2,-1) → Out of bounds.
 *             • Down: (3,0) → Out of bounds.
 *             • Up: (1,0) → Already visited.
 *
 *         -- PQ After Processing --
 *             PQ now contains:
 *                 +----------+
 *                 | [5,1,1]  |   <-- Top (value=5)
 *                 +----------+
 *                 | [7,1,2]  |
 *                 +----------+
 *                 | [5,2,1]  |
 *                 +----------+
 *
 *    While Loop Check:
 *         Top element's value = 5, which is NOT less than query value 5 → Exit loop.
 *
 *    - Set result for original index 0:
 *         result[0] = points = 5
 *
 * --------------------------------------------------
 * Iteration for sortedQ[2] (Query = 6, Original Index = 1):
 *    Query Value = 6
 *
 *    -- PQ State Before Processing --
 *         PQ:
 *             +----------+
 *             | [5,1,1]  |   <-- Top (value=5)
 *             +----------+
 *             | [7,1,2]  |
 *             +----------+
 *             | [5,2,1]  |
 *             +----------+
 *
 *    While Loop (Process until top value is NOT less than 6):
 *
 *    Iteration 3.1:
 *         -- PQ State Before Pop --
 *             PQ:
 *                 +----------+
 *                 | [5,1,1]  |   <-- Top (value=5)
 *                 +----------+
 *                 | [7,1,2]  |
 *                 +----------+
 *                 | [5,2,1]  |
 *                 +----------+
 *         - Pop: Remove [5,1,1].
 *         - Action: Increment points (points becomes 6).
 *         - Process neighbors of cell (1,1):
 *             • Right: (1,2) → Already visited.
 *             • Left: (1,0) → Already visited.
 *             • Down: (2,1) → Already visited.
 *             • Up: (0,1) → Already visited.
 *
 *         -- PQ After Processing --
 *             PQ now contains:
 *                 +----------+
 *                 | [5,2,1]  |   <-- Top (value=5)
 *                 +----------+
 *                 | [7,1,2]  |
 *                 +----------+
 *
 *    Iteration 3.2:
 *         -- PQ State Before Pop --
 *             PQ:
 *                 +----------+
 *                 | [5,2,1]  |   <-- Top (value=5)
 *                 +----------+
 *                 | [7,1,2]  |
 *                 +----------+
 *         - Pop: Remove [5,2,1].
 *         - Action: Increment points (points becomes 7).
 *         - Process neighbors of cell (2,1):
 *             • Right: (2,2) → grid[2][2] = 1, not visited, push [1,2,2], mark visited.
 *             • Left: (2,0) → Already visited.
 *             • Down: (3,1) → Out of bounds.
 *             • Up: (1,1) → Already visited.
 *
 *         -- PQ After Processing (Reorder after push) --
 *             PQ now contains:
 *                 +----------+
 *                 | [1,2,2]  |   <-- Top (value=1 after reordering)
 *                 +----------+
 *                 | [7,1,2]  |
 *                 +----------+
 *
 *    Iteration 3.3:
 *         -- PQ State Before Pop --
 *             PQ:
 *                 +----------+
 *                 | [1,2,2]  |   <-- Top (value=1)
 *                 +----------+
 *                 | [7,1,2]  |
 *                 +----------+
 *         - Pop: Remove [1,2,2].
 *         - Action: Increment points (points becomes 8).
 *         - Process neighbors of cell (2,2):
 *             • Right: (2,3) → Out of bounds.
 *             • Left: (2,1) → Already visited.
 *             • Down: (3,2) → Out of bounds.
 *             • Up: (1,2) → Already visited.
 *
 *         -- PQ After Processing --
 *             PQ now contains:
 *                 +----------+
 *                 | [7,1,2]  |   <-- Top (value=7)
 *                 +----------+
 *
 *    While Loop Check:
 *         Top element's value = 7 is NOT less than query value 6 → Exit loop.
 *
 *    - Set result for original index 1:
 *         result[1] = points = 8
 *
 * --------------------------------------------------
 * Final Result Mapping:
 *    For query 5 (original index 0): 5 points
 *    For query 6 (original index 1): 8 points
 *    For query 2 (original index 2): 1 point
 *
 * Final Output:
 *    [5, 8, 1]
 */
