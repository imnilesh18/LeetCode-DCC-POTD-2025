/*
 * 368. Largest Divisible Subset
 *
 * First Solve- LeetCode: 300. Longest Increasing Subsequence
 *
 * Medium
 *
 * Given a set of distinct positive integers nums, return the largest subset answer such that every pair (answer[i], answer[j]) of elements in this subset satisfies:
 *
 * answer[i] % answer[j] == 0, or answer[j] % answer[i] == 0
 * If there are multiple solutions, return any of them.
 *
 * Example 1:
 * Input: nums = [1,2,3]
 * Output: [1,2]
 * Explanation: [1,3] is also accepted.
 *
 * Example 2:
 * Input: nums = [1,2,4,8]
 * Output: [1,2,4,8]
 *
 * Constraints:
 * 1 <= nums.length <= 1000
 * 1 <= nums[i] <= 2 * 10^9
 * All the integers in nums are unique.
 */

// Approach 1 (TLE: 47 / 49 testcases passed): Use recursion with backtracking to explore all subsets and update the largest subset that satisfies the divisibility condition. Sorting the array simplifies divisibility checks by ensuring that each number only needs to be compared with its immediate predecessor.
// Time Complexity: O(2^n) in the worst case due to the recursive exploration of each element’s inclusion/exclusion.
// Space Complexity: O(n) due to the recursion stack and temporary vector storage.
class Solution {
public:
    // Parameters:
    //   idx    : current index in nums
    //   nums   : sorted list of numbers
    //   result : the best (largest) divisible subset found so far
    //   temp   : current subset being built
    //   prev   : the last number included in temp (or -1 if none)
    void solve(int idx, vector<int>& nums, vector<int>& result, vector<int>& temp, int prev) {
        // Base case: if we have processed all elements
        if (idx == nums.size()) {
            // Update result if the current subset is larger than the best found so far.
            if (temp.size() > result.size()) {
                result = temp;
            }
            return;
        }

        // ------------------------------------------
        // Decision 1: Try to INCLUDE nums[idx] if valid.
        // Condition: Either no previous number was selected (prev == -1)
        //            or nums[idx] is divisible by prev.
        // ------------------------------------------
        if (prev == -1 || nums[idx] % prev == 0) {
            // Reason: Valid to include since either it's the first element,
            //         or nums[idx] divides evenly by prev.
            temp.push_back(nums[idx]);                     // Include current number
            solve(idx + 1, nums, result, temp, nums[idx]); // Recurse with current number as the new previous element
            temp.pop_back();                               // Backtrack: remove the current number to explore other possibilities
        }

        // Reason: Skipped including nums[idx] because nums[idx] % prev != 0.

        // ------------------------------------------
        // Decision 2: SKIP nums[idx]
        // ------------------------------------------
        // Reason: We always explore the possibility of not including the current number.
        solve(idx + 1, nums, result, temp, prev);
    }
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        // Sorting is done so that each number only needs to be checked against its immediate predecessor.
        // For example, without sorting, for {32, 64, 4} we might repeatedly check 4 against 32 and 64.
        // With sorting, we get {4, 32, 64} and each number naturally builds on the previous valid divisible number.
        sort(begin(nums), end(nums));
        vector<int> result;
        vector<int> temp;

        int prev = -1;     // -1 indicates that no number has been selected yet.
        solve(0, nums, result, temp, prev);

        return result;
    }
};

/*
 * Dry Run for input: {32, 3, 15, 64, 4}
 * After sorting, nums becomes: {3, 4, 15, 32, 64}
 *
 * Complete Vertical Tree Visualization:
 *
 *                                    (idx=0, prev=-1, temp=[])
 *                                              │
 *              ────────────────────────────────┼───────────────────────────────
 *              │                                                               │
 *        [Include 3]                                                   [Skip 3]
 * (Reason: No previous element; valid to include)                (Reason: Explore exclusion)
 *    (temp=[3], prev=3, idx=1)                                     (temp=[], prev=-1, idx=1)
 *              │                                                               │
 *  ────────────┼───────────────                                   ─────────────┼────────────
 *              │                                                               │
 *  Evaluate num=4 at idx=1:                                         Evaluate num=4 at idx=1:
 *        4 % 3 != 0 → cannot include                              (Since prev == -1, valid to include)
 * (Reason: 4 is not divisible by 3)                                      │
 *              │                                               ┌─────────┴─────────┐
 *              │                                               │                   │
 *       [Skip 4]                                  [Include 4]                   [Skip 4]
 *  (temp remains [3], prev=3, idx=2)           (temp=[4], prev=4, idx=2)      (temp=[], prev=-1, idx=2)
 *              │                                               │
 *              │                                     ──────────┼─────────
 *              │                                               │
 *   ───────────┼─────────────                                   Evaluate num=15 at idx=2:
 *              │                                               (For branch from [Include 4]: 15 % 4 != 0)
 *  Evaluate num=15 at idx=2 (Branch A):
 *         15 % 3 == 0 → valid to include
 *              │
 *    ┌─────────┴─────────┐
 *    │                   │
 * [Include 15]      [Skip 15]
 * (temp=[3,15],      (temp=[3], prev=3, idx=3)
 *  prev=15, idx=3)
 *    │                   │
 * Evaluate num=32 at idx=3:      Evaluate num=32 at idx=3:
 *    32 % 15 != 0 → skip         32 % 3 != 0 → skip
 * (Reason: 32 not divisible         (Reason: 32 is not divisible
 *  by 15)                          by 3)
 *    │                   │
 * [Skip 32]         [Skip 32]
 * (temp=[3,15],      (temp=[3], prev=3, idx=4)
 *  prev=15, idx=4)
 *    │                   │
 * Evaluate num=64 at idx=4:      Evaluate num=64 at idx=4:
 *    64 % 15 != 0 → skip         64 % 3 != 0 → skip
 * (Reason: 64 not divisible         (Reason: 64 is not divisible)
 *  by 15)                          by 3)
 *    │                   │
 * [Skip 64]         [Skip 64]
 * (idx=5, temp=[3,15],           (idx=5, temp=[3], Base Case)
 *  prev=15)
 *    │
 *  Base Case reached → Subset = [3,15] (size = 2)
 *
 * ─────────────────────────────────────────────────────────────────────────────────────────────
 *
 *                         Branch B (from [Skip 3]):
 *
 *              (idx=1, prev=-1, temp=[])
 *                          │
 *               Evaluate num=4 at idx=1:
 *                  (prev == -1 → valid to include)
 *                          │
 *              ┌───────────┴───────────┐
 *      [Include 4]               [Skip 4]
 * (temp=[4], prev=4, idx=2)   (temp=[], prev=-1, idx=2)
 *                          │
 *         Evaluate num=15 at idx=2 for branch [Include 4]:
 *             15 % 4 != 0 → must skip
 *                          │
 *                   [Skip 15]
 *              (temp=[4], prev=4, idx=3)
 *                          │
 *         Evaluate num=32 at idx=3:
 *             32 % 4 == 0 → valid to include
 *                          │
 *              ┌───────────┴───────────┐
 *       [Include 32]               [Skip 32]
 * (temp=[4,32], prev=32, idx=4)  (temp=[4], prev=4, idx=4)
 *                          │
 *         Evaluate num=64 at idx=4 for branch [Include 32]:
 *             64 % 32 == 0 → valid to include
 *                          │
 *              ┌───────────┴───────────┐
 *       [Include 64]               [Skip 64]
 * (temp=[4,32,64], prev=64,    (temp=[4,32], prev=32, idx=5)
 *      idx=5)                         (Base Case)
 *          │
 *   Base Case reached → Subset = [4,32,64] (size = 3)
 *
 *  (Branch from [Skip 4] in Branch B yields subsets smaller than size 3)
 *
 *  Best from Branch B: [4,32,64] (size = 3)
 *
 * ─────────────────────────────────────────────────────────────────────────────────────────────
 *
 * Final Comparison:
 *      Best from Branch A: [3,15] (size = 2)
 *      Best from Branch B: [4,32,64] (size = 3)
 *
 * Conclusion:
 *      The largest divisible subset is [4,32,64].
 *
 * Note:
 *  - Each node is represented as (idx, prev, temp).
 *  - At every decision point, the reason for including or skipping the current number is stated.
 *  - Base cases are reached when idx equals nums.size(), and the subset is evaluated.
 */

// Approach 2 (Bottom-up): Sort the array and then use dynamic programming (dp) to compute the size of the largest divisible subset ending at each element.
//           For each element, we check if it can extend any previous subset (by verifying divisibility) and store the subset length in dp array 't'
//           and the predecessor index in 'prev_idx'. Finally, backtrack from the element with the maximum dp value to form the result.
// Time Complexity: O(n^2) - Two nested loops iterating over the array elements.
// Space Complexity: O(n) - Additional arrays for dp (t), predecessor (prev_idx), and the result vector.
class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        // Sort the input array to ease divisibility checks.
        sort(nums.begin(), nums.end());

        int         n = nums.size();
        vector<int> t(n, 1);             // dp array: t[i] is the size of the largest divisible subset ending at nums[i]
        vector<int> prev_idx(n, -1);     // prev_idx array: tracks the previous index in the subset

        // Global trackers for the maximum subset length and the index where this subset ends.
        int last_chosen_index = 0;
        int maxL = 1;

        // Iterate over each element in the sorted nums array.
        for (int i = 0; i < n; i++) {
            // For each element nums[i], check all previous elements nums[j] where j < i.
            for (int j = 0; j < i; j++) {
                // If nums[i] is divisible by nums[j], then nums[i] can extend the subset ending at nums[j].
                if (nums[i] % nums[j] == 0) {
                    if (t[i] < t[j] + 1) {       // If extending the subset ending at j yields a larger subset for i.
                        t[i]        = t[j] + 1;  // Update dp value for nums[i].
                        prev_idx[i] = j;         // Record j as the previous index for nums[i].
                    }
                    // Update global max if a new larger subset is found.
                    if (t[i] > maxL) {
                        maxL = t[i];
                        last_chosen_index = i;
                    }
                }
            }
        }

        // Backtrack from last_chosen_index to reconstruct the largest divisible subset.
        vector<int> result;
        while (last_chosen_index >= 0) {
            result.push_back(nums[last_chosen_index]);
            last_chosen_index = prev_idx[last_chosen_index];
        }

        return result;
    }
};

/*
 *
 * Dry Run for Input: nums = {3, 4, 15, 32, 64}
 *
 * Step 1: Initial Setup
 *
 * Original nums array:
 *   Indices:   0     1     2     3     4
 *            +-----+-----+-----+-----+-----+
 *            |  3  |  4  | 15  | 32  | 64  |
 *            +-----+-----+-----+-----+-----+
 *   (Pointers: i starts at index 0, then moves as i increases)
 *
 * Sorted nums array (already sorted in this case):
 *   Indices:   0     1     2     3     4
 *            +-----+-----+-----+-----+-----+
 *            |  3  |  4  | 15  | 32  | 64  |
 *            +-----+-----+-----+-----+-----+
 *
 * dp array (t):
 *   Indices:   0     1     2     3     4
 *            +-----+-----+-----+-----+-----+
 *            |  1  |  1  |  1  |  1  |  1  |
 *            +-----+-----+-----+-----+-----+
 *
 * prev_idx array:
 *   Indices:    0      1      2      3      4
 *            +------+------+------+------+------+
 *            | -1   | -1   | -1   | -1   | -1   |
 *            +------+------+------+------+------+
 *
 * Global Variables: maxL = 1, last_chosen_index = 0
 *
 *----------------------------------------------------------------
 * Iteration i = 0, nums[0] = 3
 *   - No inner loop (no j < i).
 *   State remains unchanged.
 *
 *----------------------------------------------------------------
 * Iteration i = 1, nums[1] = 4
 *
 *   i pointer at index 1 (value 4):
 *
 *   nums array visualization:
 *   Indices:   0     1     2     3     4
 *            +-----+-----+-----+-----+-----+
 *            |  3  |  4  | 15  | 32  | 64  |
 *            +-----+-----+-----+-----+-----+
 *                     ^
 *                 (i pointer)
 *
 *   Inner loop: j = 0, nums[0] = 3
 *   Visualization:
 *   Indices:   0     1     2     3     4
 *            +-----+-----+-----+-----+-----+
 *            |  3  |  4  | 15  | 32  | 64  |
 *            +-----+-----+-----+-----+-----+
 *               ^
 *         (j pointer at index 0)
 *
 *   Check: 4 % 3 = 1 (not 0) → no update.
 *
 *   After iteration i = 1:
 *   dp array (t):
 *   Indices:   0     1     2     3     4
 *            +-----+-----+-----+-----+-----+
 *            |  1  |  1  |  1  |  1  |  1  |
 *            +-----+-----+-----+-----+-----+
 *
 *   prev_idx array:
 *   Indices:    0      1      2      3      4
 *            +------+------+------+------+------+
 *            | -1   | -1   | -1   | -1   | -1   |
 *            +------+------+------+------+------+
 *
 *   Global remains: maxL = 1, last_chosen_index = 0
 *
 *----------------------------------------------------------------
 * Iteration i = 2, nums[2] = 15
 *
 *   i pointer at index 2 (value 15):
 *
 *   nums array visualization:
 *   Indices:   0     1     2     3     4
 *            +-----+-----+-----+-----+-----+
 *            |  3  |  4  | 15  | 32  | 64  |
 *            +-----+-----+-----+-----+-----+
 *                           ^
 *                     (i pointer)
 *
 *   Inner loop:
 *     a) j = 0, nums[0] = 3
 *        Visualization:
 *        Indices:   0     1     2     3     4
 *                 +-----+-----+-----+-----+-----+
 *                 |  3  |  4  | 15  | 32  | 64  |
 *                 +-----+-----+-----+-----+-----+
 *                    ^
 *              (j pointer at index 0)
 *
 *        Check: 15 % 3 == 0 → true.
 *        Condition: t[2] < t[0] + 1 → 1 < 1+1 → true.
 *        Update:
 *            t[2] becomes 2.
 *            prev_idx[2] becomes 0.
 *            Global update: maxL becomes 2, last_chosen_index becomes 2.
 *
 *        Updated dp array (t):
 *        Indices:   0     1     2     3     4
 *                 +-----+-----+-----+-----+-----+
 *                 |  1  |  1  |  2  |  1  |  1  |
 *                 +-----+-----+-----+-----+-----+
 *
 *        Updated prev_idx array:
 *        Indices:    0      1      2      3      4
 *                 +------+------+------+------+------+
 *                 | -1   | -1   |  0   | -1   | -1   |
 *                 +------+------+------+------+------+
 *
 *     b) j = 1, nums[1] = 4
 *        Visualization:
 *        Indices:   0     1     2     3     4
 *                 +-----+-----+-----+-----+-----+
 *                 |  3  |  4  | 15  | 32  | 64  |
 *                 +-----+-----+-----+-----+-----+
 *                          ^
 *                    (j pointer at index 1)
 *
 *        Check: 15 % 4 = 3 (not 0) → no update.
 *
 *   After iteration i = 2:
 *   dp array (t):
 *   Indices:   0     1     2     3     4
 *            +-----+-----+-----+-----+-----+
 *            |  1  |  1  |  2  |  1  |  1  |
 *            +-----+-----+-----+-----+-----+
 *
 *   prev_idx array:
 *   Indices:    0      1      2      3      4
 *            +------+------+------+------+------+
 *            | -1   | -1   |  0   | -1   | -1   |
 *            +------+------+------+------+------+
 *
 *   Global: maxL = 2, last_chosen_index = 2
 *
 *----------------------------------------------------------------
 * Iteration i = 3, nums[3] = 32
 *
 *   i pointer at index 3 (value 32):
 *
 *   nums array visualization:
 *   Indices:   0     1     2     3     4
 *            +-----+-----+-----+-----+-----+
 *            |  3  |  4  | 15  | 32  | 64  |
 *            +-----+-----+-----+-----+-----+
 *                                 ^
 *                            (i pointer)
 *
 *   Inner loop:
 *     a) j = 0, nums[0] = 3
 *        Visualization:
 *        Indices:   0     1     2     3     4
 *                 +-----+-----+-----+-----+-----+
 *                 |  3  |  4  | 15  | 32  | 64  |
 *                 +-----+-----+-----+-----+-----+
 *                    ^
 *              (j pointer at index 0)
 *
 *        Check: 32 % 3 = 2 (not 0) → no update.
 *
 *     b) j = 1, nums[1] = 4
 *        Visualization:
 *        Indices:   0     1     2     3     4
 *                 +-----+-----+-----+-----+-----+
 *                 |  3  |  4  | 15  | 32  | 64  |
 *                 +-----+-----+-----+-----+-----+
 *                          ^
 *                   (j pointer at index 1)
 *
 *        Check: 32 % 4 == 0 → true.
 *        Condition: t[3] < t[1] + 1 → 1 < 1+1 → true.
 *        Update:
 *            t[3] becomes 2.
 *            prev_idx[3] becomes 1.
 *            Global: maxL remains 2.
 *
 *        Updated dp array (t):
 *        Indices:   0     1     2     3     4
 *                 +-----+-----+-----+-----+-----+
 *                 |  1  |  1  |  2  |  2  |  1  |
 *                 +-----+-----+-----+-----+-----+
 *
 *        Updated prev_idx array:
 *        Indices:    0      1      2      3      4
 *                 +------+------+------+------+------+
 *                 | -1   | -1   |  0   |  1   | -1   |
 *                 +------+------+------+------+------+
 *
 *     c) j = 2, nums[2] = 15
 *        Visualization:
 *        Indices:   0     1     2     3     4
 *                 +-----+-----+-----+-----+-----+
 *                 |  3  |  4  | 15  | 32  | 64  |
 *                 +-----+-----+-----+-----+-----+
 *                                ^
 *                     (j pointer at index 2)
 *
 *        Check: 32 % 15 = 2 (not 0) → no update.
 *
 *   After iteration i = 3:
 *   dp array (t):
 *   Indices:   0     1     2     3     4
 *            +-----+-----+-----+-----+-----+
 *            |  1  |  1  |  2  |  2  |  1  |
 *            +-----+-----+-----+-----+-----+
 *
 *   prev_idx array:
 *   Indices:    0      1      2      3      4
 *            +------+------+------+------+------+
 *            | -1   | -1   |  0   |  1   | -1   |
 *            +------+------+------+------+------+
 *
 *   Global remains: maxL = 2, last_chosen_index = 2
 *
 *----------------------------------------------------------------
 * Iteration i = 4, nums[4] = 64
 *
 *   i pointer at index 4 (value 64):
 *
 *   nums array visualization:
 *   Indices:   0     1     2     3     4
 *            +-----+-----+-----+-----+-----+
 *            |  3  |  4  | 15  | 32  | 64  |
 *            +-----+-----+-----+-----+-----+
 *                                       ^
 *                                    (i pointer)
 *
 *   Inner loop:
 *     a) j = 0, nums[0] = 3
 *        Visualization:
 *        Indices:   0     1     2     3     4
 *                 +-----+-----+-----+-----+-----+
 *                 |  3  |  4  | 15  | 32  | 64  |
 *                 +-----+-----+-----+-----+-----+
 *                    ^
 *              (j pointer at index 0)
 *
 *        Check: 64 % 3 = 1 (not 0) → no update.
 *
 *     b) j = 1, nums[1] = 4
 *        Visualization:
 *        Indices:   0     1     2     3     4
 *                 +-----+-----+-----+-----+-----+
 *                 |  3  |  4  | 15  | 32  | 64  |
 *                 +-----+-----+-----+-----+-----+
 *                          ^
 *                   (j pointer at index 1)
 *
 *        Check: 64 % 4 == 0 → true.
 *        Condition: t[4] < t[1] + 1 → 1 < 1+1 → true.
 *        Update:
 *            t[4] becomes 2.
 *            prev_idx[4] becomes 1.
 *            Global: maxL remains 2.
 *
 *        Updated dp array (t):
 *        Indices:   0     1     2     3     4
 *                 +-----+-----+-----+-----+-----+
 *                 |  1  |  1  |  2  |  2  |  2  |
 *                 +-----+-----+-----+-----+-----+
 *
 *        Updated prev_idx array:
 *        Indices:    0      1      2      3      4
 *                 +------+------+------+------+------+
 *                 | -1   | -1   |  0   |  1   |  1   |
 *                 +------+------+------+------+------+
 *
 *     c) j = 2, nums[2] = 15
 *        Visualization:
 *        Indices:   0     1     2     3     4
 *                 +-----+-----+-----+-----+-----+
 *                 |  3  |  4  | 15  | 32  | 64  |
 *                 +-----+-----+-----+-----+-----+
 *                                ^
 *                   (j pointer at index 2)
 *
 *        Check: 64 % 15 = 4 (not 0) → no update.
 *
 *     d) j = 3, nums[3] = 32
 *        Visualization:
 *        Indices:   0     1     2     3     4
 *                 +-----+-----+-----+-----+-----+
 *                 |  3  |  4  | 15  | 32  | 64  |
 *                 +-----+-----+-----+-----+-----+
 *                                      ^
 *                           (j pointer at index 3)
 *
 *        Check: 64 % 32 == 0 → true.
 *        Condition: t[4] < t[3] + 1 → 2 < 2+1 → true.
 *        Update:
 *            t[4] becomes 3.
 *            prev_idx[4] becomes 3.
 *            Global update: maxL becomes 3, last_chosen_index becomes 4.
 *
 *        Final dp array (t):
 *        Indices:   0     1     2     3     4
 *                 +-----+-----+-----+-----+-----+
 *                 |  1  |  1  |  2  |  2  |  3  |
 *                 +-----+-----+-----+-----+-----+
 *
 *        Final prev_idx array:
 *        Indices:    0      1      2      3      4
 *                 +------+------+------+------+------+
 *                 | -1   | -1   |  0   |  1   |  3   |
 *                 +------+------+------+------+------+
 *
 *   Global: maxL = 3, last_chosen_index = 4
 *
 *----------------------------------------------------------------
 * Result Reconstruction:
 *
 * Start with last_chosen_index = 4.
 *
 *   Step 1:
 *       Index = 4 → nums[4] = 64
 *       Result becomes: [64]
 *       Update pointer: last_chosen_index = prev_idx[4] = 3
 *
 *   Step 2:
 *       Index = 3 → nums[3] = 32
 *       Result becomes: [64, 32]
 *       Update pointer: last_chosen_index = prev_idx[3] = 1
 *
 *   Step 3:
 *       Index = 1 → nums[1] = 4
 *       Result becomes: [64, 32, 4]
 *       Update pointer: last_chosen_index = prev_idx[1] = -1  (termination)
 *
 * Visual Box Representation for Result Array:
 *   Indices:   0     1     2
 *            +-----+-----+-----+
 *            | 64  | 32  |  4  |
 *            +-----+-----+-----+
 *
 * Final Largest Divisible Subset: [64, 32, 4]
 *
 */
