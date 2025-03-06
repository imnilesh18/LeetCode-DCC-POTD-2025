/*
 * 2965. Find Missing and Repeated Values
 *
 * You are given a 0-indexed 2D integer matrix grid of size n * n with values in the range [1, n2]. Each integer appears exactly once except a which appears twice and b which is missing. The task is to find the repeating and missing numbers a and b.
 *
 * Return a 0-indexed integer array ans of size 2 where ans[0] equals to a and ans[1] equals to b.
 *
 * Example 1:
 * Input: grid = [[1,3],[2,2]]
 * Output: [2,4]
 * Explanation: Number 2 is repeated and number 4 is missing so the answer is [2,4].
 *
 * Example 2:
 * Input: grid = [[9,1,7],[8,9,2],[3,4,6]]
 * Output: [9,5]
 * Explanation: Number 9 is repeated and number 5 is missing so the answer is [9,5].
 *
 * Constraints:
 * 2 <= n == grid.length == grid[i].length <= 50
 * 1 <= grid[i][j] <= n * n
 * For all x that 1 <= x <= n * n there is exactly one x that is not equal to any of the grid members.
 * For all x that 1 <= x <= n * n there is exactly one x that is equal to exactly two of the grid members.
 * For all x that 1 <= x <= n * n except two of them there is exatly one pair of i, j that 0 <= i, j <= n - 1 and grid[i][j] == x.
 */

// Approach 1: Use a hash map to count frequencies of each number from the grid, then iterate through 1 to n^2 to find the number that appears twice (repeated) and the number that does not appear (missing).
// Time Complexity: O(n^2) since we iterate over all elements in the grid.
// Space Complexity: O(n^2) for the hash map storing counts of each number.
class Solution {
public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int> >& grid) {
        int n = grid.size();        // n is the number of rows (and columns) in the grid
        int N = n * n;              // Total numbers from 1 to n^2

        unordered_map<int, int> mp; // Hash map to count frequency of each number in the grid
        int a = -1;                 // Variable to store the repeated number (appears twice)
        int b = -1;                 // Variable to store the missing number (does not appear)

        // Count frequency of each number in the grid
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                mp[grid[i][j]]++;
            }
        }

        // Identify the repeated (a) and missing (b) numbers by checking counts for numbers from 1 to n^2
        for (int num = 1; num <= N; num++) {
            if (!mp.count(num)) {          // If the number is not present in the grid
                b = num;                   // This number is missing
            } else if (mp[num] == 2) {     // If the number appears twice
                a = num;                   // This number is repeated
            }
        }

        return { a, b };   // Return the repeated number and the missing number
    }
};

/*
 * Dry Run:
 * For grid = [[1, 3],
 *          [2, 2]]:
 * - n = 2, N = 4
 * - After counting frequencies, mp = {1:1, 3:1, 2:2}
 * - Iterating num from 1 to 4:
 *  num = 1: count is 1, so nothing happens.
 *  num = 2: count is 2, hence a = 2 (repeated).
 *  num = 3: count is 1, so nothing happens.
 *  num = 4: not found in mp, hence b = 4 (missing).
 * - The function returns {2, 4}
 */

// Approach 2: Use mathematical formulas for the sum and sum of squares of numbers from 1 to n^2.
//             Calculate the differences between the expected sums and the grid sums to form equations,
//             then solve the equations to find the repeated (a) and missing (b) numbers.
// Time Complexity: O(n^2) because we traverse all elements in the grid once.
// Space Complexity: O(1) as we use only a few extra variables.
class Solution {
public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int> >& grid) {
        int       n = grid.size();
        long long N = n * n;      // Total expected numbers from 1 to n^2

        long long gridSum   = 0;
        long long gridSqSum = 0;

        // Calculate the sum and sum of squares for the grid
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                gridSum   += grid[i][j];
                gridSqSum += grid[i][j] * grid[i][j];
            }
        }

        // Expected sum of numbers from 1 to n^2: S = N*(N+1)/2
        long long sum = (N * (N + 1)) / 2;
        // Expected sum of squares from 1 to n^2: S_sq = N*(N+1)*(2*N+1)/6
        long long sqSum = (N * (N + 1) * (2 * N + 1)) / 6;

        // Let a = repeated number and b = missing number.
        // Equation (1): gridSum = sum - b + a  =>  gridSum - sum = a - b
        int sumDiff = gridSum - sum;      // a - b

        // Equation (2): gridSqSum = sqSum - b^2 + a^2  =>  gridSqSum - sqSum = a^2 - b^2
        // And note: a^2 - b^2 = (a - b)(a + b)
        int sqDiff = gridSqSum - sqSum;     // (a - b)(a + b)

        // From the above, we get:
        // a - b = sumDiff
        // a + b = sqDiff / sumDiff
        // Solve these equations:
        // a = ( (a - b) + (a + b) ) / 2 = (sumDiff + (sqDiff/sumDiff)) / 2
        // b = ( (a + b) - (a - b) ) / 2 = ((sqDiff/sumDiff) - sumDiff) / 2
        int a = (sqDiff / sumDiff + sumDiff) / 2;
        int b = (sqDiff / sumDiff - sumDiff) / 2;

        return { a, b };
    }
};

/*
 * Derivation:
 * Let a = repeated number and b = missing number.
 *
 * 1. Sum Equation:
 * - Expected sum of numbers from 1 to N is:
 *   S = 1 + 2 + ... + N = N*(N+1)/2.
 * - Actual grid sum = S - b + a.
 * - Thus, gridSum - S = a - b.   ...(1)
 *
 * 2. Sum of Squares Equation:
 * - Expected sum of squares from 1 to N is:
 *   S_sq = 1^2 + 2^2 + ... + N^2 = N*(N+1)*(2*N+1)/6.
 * - Actual grid sum of squares = S_sq - b^2 + a^2.
 * - Therefore, gridSqSum - S_sq = a^2 - b^2.
 * - And note that a^2 - b^2 can be factored as (a - b)(a + b).   ...(2)
 *
 * 3. From (1): Let diff = a - b = gridSum - S.
 * Substitute diff into (2):
 * gridSqSum - S_sq = diff * (a + b)
 * => a + b = (gridSqSum - S_sq) / diff.
 *
 * 4. Now, we have the system of equations:
 * a - b = diff
 * a + b = (gridSqSum - S_sq) / diff
 *
 * 5. Solving the system:
 * - Add the two equations:
 *   2a = diff + (gridSqSum - S_sq) / diff
 *   => a = (diff + (gridSqSum - S_sq)/diff) / 2.
 * - Subtract the first equation from the second:
 *   2b = (gridSqSum - S_sq) / diff - diff
 *   => b = ((gridSqSum - S_sq)/diff - diff) / 2.
 */

/*
 * Dry Run:
 * For grid = [[1, 3],
 *          [2, 2]]:
 * - n = 2, N = 4.
 * - Expected sum, S = 4*5/2 = 10.
 * - Expected sum of squares, S_sq = 4*5*9/6 = 30.
 * - gridSum = 1 + 3 + 2 + 2 = 8.
 * - gridSqSum = 1^2 + 3^2 + 2^2 + 2^2 = 1 + 9 + 4 + 4 = 18.
 * - sumDiff = gridSum - S = 8 - 10 = -2.  (So, a - b = -2)
 * - sqDiff = gridSqSum - S_sq = 18 - 30 = -12.
 * - a + b = sqDiff / sumDiff = (-12) / (-2) = 6.
 * - Now, a = (sumDiff + (a+b)) / 2 = (-2 + 6) / 2 = 2.
 * - And, b = ((a+b) - sumDiff) / 2 = (6 - (-2)) / 2 = 4.
 * - The function returns {2, 4}.
 */
