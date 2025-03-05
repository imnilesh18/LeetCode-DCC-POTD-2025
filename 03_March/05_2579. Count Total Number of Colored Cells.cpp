/*
 * 2579. Count Total Number of Colored Cells
 *
 * There exists an infinitely large two-dimensional grid of uncolored unit cells. You are given a positive integer n, indicating that you must do the following routine for n minutes:
 *
 * At the first minute, color any arbitrary unit cell blue.
 * Every minute thereafter, color blue every uncolored cell that touches a blue cell.
 * Below is a pictorial representation of the state of the grid after minutes 1, 2, and 3.
 *
 * Return the number of colored cells at the end of n minutes.
 *
 * Example 1:
 * Input: n = 1
 * Output: 1
 * Explanation: After 1 minute, there is only 1 blue cell, so we return 1.
 *
 * Example 2:
 *
 * Input: n = 2
 * Output: 5
 * Explanation: After 2 minutes, there are 4 colored cells on the boundary and 1 in the center, so we return 5.
 *
 * Constraints:
 * 1 <= n <= 10^5
 */

// Approach 1: Start with one blue cell and then for each minute t (from 1 to n), add 4*(t-1) cells that form the boundary.
// Time Complexity: O(n) - We loop n times.
// Space Complexity: O(1) - Only constant extra space is used.
class Solution {
public:
    long long coloredCells(int n) {
        int       t     = 1;
        long long cells = 1;     // Initially, one cell is colored at minute 1.

        while (t <= n) {
            cells += (4 * (t - 1));     // For each minute t, add 4*(t-1) new colored cells.
            t++;
        }

        return cells;
    }
};

/*
 * Dry Run:
 * For n = 3:
 * 1. t = 1, cells = 1
 * - Loop iteration: cells += 4*(1-1) = 4*0 = 0
 * - cells remains 1, then t becomes 2.
 *
 * 2. t = 2, cells = 1
 * - Loop iteration: cells += 4*(2-1) = 4*1 = 4
 * - cells becomes 1 + 4 = 5, then t becomes 3.
 *
 * 3. t = 3, cells = 5
 * - Loop iteration: cells += 4*(3-1) = 4*2 = 8
 * - cells becomes 5 + 8 = 13, then t becomes 4.
 *
 * Final result for n = 3: 13 colored cells.
 */

// Approach 2: Use the derived formula 1 + 2*(n-1)*n to compute the total number of colored cells.
// Time Complexity: O(1) - The calculation is done using a constant number of arithmetic operations.
// Space Complexity: O(1) - No additional space is required apart from a few variables.
class Solution {
public:
    long long coloredCells(int n) {
        return 1 + (2 * (long long)(n - 1) * n);
    }
};

/*
 * Dry Run:
 * Example: n = 3
 * Step 1: Compute (n - 1) = 2.
 * Step 2: Multiply 2 * (n - 1) * n = 2 * 2 * 3 = 12.
 * Step 3: Add 1 to the result: 1 + 12 = 13.
 * Thus, for n = 3, the function returns 13.
 */
