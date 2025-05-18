/*
 * 1931. Painting a Grid With Three Different Colors
 *
 * Hard
 *
 * You are given two integers m and n. Consider an m x n grid where each cell is initially white. You can paint each cell red, green, or blue. All cells must be painted.
 *
 * Return the number of ways to color the grid with no two adjacent cells having the same color. Since the answer can be very large, return it modulo 109 + 7.
 *
 * Example 1:
 * Input: m = 1, n = 1
 * Output: 3
 * Explanation: The three possible colorings are shown in the image above.
 *
 * Example 2:
 * Input: m = 1, n = 2
 * Output: 6
 * Explanation: The six possible colorings are shown in the image above.
 *
 * Example 3:
 * Input: m = 5, n = 5
 * Output: 580986
 *
 * Constraints:
 * 1 <= m <= 5
 * 1 <= n <= 1000
 */

// Approach: Use recursion + memoization to calculate number of valid grid colorings. Generate valid column states (vertically valid), then recursively count valid color transitions (horizontally valid).
// Time Complexity: O(n * S * S * m), where S is the number of valid column states = O(3 * 2^(m-1)). Each of the n columns has up to S options, and we compare every pair (S * S) for horizontal validity.
// Space Complexity: O(n * S + S * m), where n * S is for the memoization table, and S * m is for storing columnStates.
class Solution {
public:
    vector<vector<int>> t;      // Memoization table
    vector<string> columnStates; // Stores all valid vertical column colorings
    const int MOD = 1e9 + 7;

    // Recursively generate all valid column colorings of height 'rows'
    // such that no two vertically adjacent cells have the same color
    void generateColumnStates(string currentColumn, int rowsRemaining, char prevColor) {
        if (rowsRemaining == 0) {
            columnStates.push_back(currentColumn); // Valid column complete
            return;
        }

        // Colors: 'R' = Red, 'G' = Green, 'B' = Blue
        for (char color : { 'R', 'G', 'B' }) {
            if (color == prevColor) {
                continue;  // adjacent vertical cells must be different
            }
            generateColumnStates(currentColumn + color, rowsRemaining - 1, color);
        }
    }
    // Recursive function to compute number of ways to color remainingCols columns
    // given that previous column was columnStates[prevColumnIdx]
    int solve(int remainingCols, int prevColumnIdx, int m) {
        if (remainingCols == 0) {
            return 1; // Base case: No columns left to fill
        }
        if (t[remainingCols][prevColumnIdx] != -1) {
            return t[remainingCols][prevColumnIdx]; // Return memoized value
        }
        int    totalWays  = 0;
        string prevColumn = columnStates[prevColumnIdx];

        // Try placing each valid column as the next column
        for (int nextColumnIdx = 0; nextColumnIdx < columnStates.size(); nextColumnIdx++) {
            string nextColumn = columnStates[nextColumnIdx];
            bool   valid      = true;

            // Check horizontal adjacency (same row in adjacent columns)
            for (int r = 0; r < m; r++) {
                if (prevColumn[r] == nextColumn[r]) {
                    valid = false;
                    break;
                }
            }

            // If valid horizontally, proceed recursively
            if (valid) {
                totalWays = (totalWays + solve(remainingCols - 1, nextColumnIdx, m)) % MOD;
            }
        }

        // Memoize and return
        return t[remainingCols][prevColumnIdx] = totalWays;
    }
    int colorTheGrid(int m, int n) {
        columnStates.clear();             // Clear old states
        generateColumnStates("", m, '#'); // '#' indicates no previous color

        int numColumnPatterns = columnStates.size();
        t.assign(n, vector<int>(numColumnPatterns, -1)); // Initialize memo table

        int result = 0;

        // Try starting with each valid column
        for (int i = 0; i < numColumnPatterns; i++) {
            result = (result + solve(n - 1, i, m)) % MOD;
        }

        return result;
    }
};

/*
 *
 * Dry Run:
 * Input: m = 2, n = 2
 * Step 1: Generate valid vertical columns of height 2 with no adjacent same colors.
 * - Possible valid columns: RG, RB, GR, GB, BR, BG => 6 total
 *
 * Step 2: For each column as starting column, recursively find valid next columns
 * that differ in all corresponding rows (horizontal check).
 * - For example, RG and GR: R ≠ G and G ≠ R → valid pair
 *
 * Step 3: For each pair (start, next), count paths using memoization.
 * For 2 columns, result = count of all valid adjacent column pairs:
 * - RG → GR, GB → valid
 * - RB → GR, GB
 * - GR → RG, RB
 * - GB → RG, RB
 * - BR → RG, GR
 * - BG → RG, GR
 * Final result = 12
 *
 */
