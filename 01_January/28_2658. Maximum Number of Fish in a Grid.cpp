/*
 * 2658. Maximum Number of Fish in a Grid
 *
 * You are given a 0-indexed 2D matrix grid of size m x n, where (r, c) represents:
 * A land cell if grid[r][c] = 0, or
 * A water cell containing grid[r][c] fish, if grid[r][c] > 0.
 * A fisher can start at any water cell (r, c) and can do the following operations any number of times:
 * Catch all the fish at cell (r, c), or
 * Move to any adjacent water cell.
 * Return the maximum number of fish the fisher can catch if he chooses his starting cell optimally, or 0 if no water cell exists.
 * An adjacent cell of the cell (r, c), is one of the cells (r, c + 1), (r, c - 1), (r + 1, c) or (r - 1, c) if it exists.
 *
 * Example 1:
 * Input: grid = [[0,2,1,0],[4,0,0,3],[1,0,0,4],[0,3,2,0]]
 * Output: 7
 * Explanation: The fisher can start at cell (1,3) and collect 3 fish, then move to cell (2,3) and collect 4 fish.
 *
 * Example 2:
 * Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,1]]
 * Output: 1
 * Explanation: The fisher can start at cells (0,0) or (3,3) and collect a single fish.
 *
 * Constraints:
 * m == grid.length
 * n == grid[i].length
 * 1 <= m, n <= 10
 * 0 <= grid[i][j] <= 10
 */

// Approach 1: DFS to explore connected water regions, summing fish and marking visited cells.
// TC: O(m*n) – Each cell is processed once.
// SC: O(m*n) – Worst-case recursion depth for fully connected grid.
class Solution {
public:
   int m, n;  // Grid dimensions (rows m, columns n)
   // Directions for movement: up, down, left, right
   vector<vector<int> > directions = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

   // DFS helper to calculate the total fish in the current connected water region
   int dfs(int i, int j, vector<vector<int> >& grid) {
      // Check if current cell is out of bounds or a land cell (0)
      if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == 0) {
         return 0;
      }

      // Collect fish from current cell and mark it as visited (set to 0)
      int fishCount = grid[i][j];
      grid[i][j] = 0;

      // Explore all four adjacent cells recursively and accumulate fish count
      for (vector<int>& dir : directions) {
         int i_ = i + dir[0];
         int j_ = j + dir[1];
         fishCount += dfs(i_, j_, grid);
      }

      // Return total fish in the current connected region
      return fishCount;
   }

   int findMaxFish(vector<vector<int> >& grid) {
      m = grid.size();      // Number of rows
      n = grid[0].size();   // Number of columns
      int maxFish = 0;      // Track the maximum fish found in any region

      // Iterate through each cell in the grid
      for (int i = 0; i < m; i++) {
         for (int j = 0; j < n; j++) {
            // Start DFS from cells with fish to find connected regions
            if (grid[i][j] > 0) {
               // Update maxFish with the maximum value found
               maxFish = max(maxFish, dfs(i, j, grid));
            }
         }
      }

      return maxFish;
   }
};

// Approach 2: BFS to explore connected water regions and sum fish
// TC: O(m*n) → Each cell processed exactly once
// SC: O(m*n) → Queue stores all cells in worst case (full grid)
class Solution {
public:
   int m, n;                                                                       // Stores grid dimensions (rows m, columns n)
   vector<vector<int> > directions = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } }; // Movement directions (up, down, left, right)

   // BFS to calculate total fish in connected water region starting at (i,j)
   int bfs(int i, int j, vector<vector<int> >& grid) {
      queue<pair<int, int> > que; // Queue for BFS traversal

      que.push({ i, j });         // Start BFS from initial cell
      int fishCount = grid[i][j]; // Track fish collected
      grid[i][j] = 0;             // Mark cell as visited by setting to 0

      while (!que.empty()) {
         i = que.front().first;        // Current cell's row
         j = que.front().second;       // Current cell's column
         que.pop();                    // Remove processed cell from queue

         for (auto&dir : directions) { // Check all 4 adjacent cells
            int i_ = i + dir[0];       // New row index
            int j_ = j + dir[1];       // New column index

            // Check if adjacent cell is valid and has fish
            if (i_ >= 0 && j_ >= 0 && i_ < m && j_ < n && grid[i_][j_] > 0) {
               que.push({ i_, j_ });        // Add to queue for processing
               fishCount   += grid[i_][j_]; // Collect fish from this cell
               grid[i_][j_] = 0;            // Mark cell as visited
            }
         }
      }

      return fishCount;   // Total fish in this connected region
   }

   int findMaxFish(vector<vector<int> >& grid) {
      m = grid.size();    // Get number of rows
      n = grid[0].size(); // Get number of columns

      int maxFish = 0;    // Track maximum fish found

      // Iterate through every cell in the grid
      for (int i = 0; i < m; i++) {
         for (int j = 0; j < n; j++) {
            if (grid[i][j] > 0) {                       // Start BFS only if cell has fish
               maxFish = max(maxFish, bfs(i, j, grid)); // Update maximum
            }
         }
      }

      return maxFish;   // Final answer
   }
};
