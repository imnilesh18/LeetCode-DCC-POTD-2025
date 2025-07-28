/*
 * 2044. Count Number of Maximum Bitwise-OR Subsets
 *
 * Medium
 *
 * Given an integer array nums, find the maximum possible bitwise OR of a subset of nums and return the number of different non-empty subsets with the maximum bitwise OR.
 *
 * An array a is a subset of an array b if a can be obtained from b by deleting some (possibly zero) elements of b. Two subsets are considered different if the indices of the elements chosen are different.
 *
 * The bitwise OR of an array a is equal to a[0] OR a[1] OR ... OR a[a.length - 1] (0-indexed).
 *
 * Example 1:
 * Input: nums = [3,1]
 * Output: 2
 * Explanation: The maximum possible bitwise OR of a subset is 3. There are 2 subsets with a bitwise OR of 3:
 * - [3]
 * - [3,1]
 *
 * Example 2:
 * Input: nums = [2,2,2]
 * Output: 7
 * Explanation: All non-empty subsets of [2,2,2] have a bitwise OR of 2. There are 23 - 1 = 7 total subsets.
 *
 * Example 3:
 * Input: nums = [3,2,1,5]
 * Output: 6
 * Explanation: The maximum possible bitwise OR of a subset is 7. There are 6 subsets with a bitwise OR of 7:
 * - [3,5]
 * - [3,1,5]
 * - [3,2,5]
 * - [3,2,1,5]
 * - [2,5]
 * - [2,1,5]
 *
 * Constraints:
 * 1 <= nums.length <= 16
 * 1 <= nums[i] <= 10^5
 */

// Intuition: The problem asks for the number of subsets that result in the maximum possible bitwise OR value. First, we determine this maximum OR value by OR-ing all numbers in the array. Then, we can use a recursive approach (backtracking) to explore every possible subset. For each subset, we calculate its bitwise OR and check if it equals the maximum OR. To optimize this, we use memoization to store the results of subproblems (defined by the current index and the current OR value) to avoid redundant calculations.
// Approach:
// 1. Calculate `maxOr`, the bitwise OR of all elements in `nums`. This is the target value we want to achieve.
// 2. Initialize a 2D memoization table `t` with dimensions `(nums.size() + 1) x (maxOr + 1)` and fill it with -1. `t[idx][currOr]` will store the count of subsets with OR `currOr` considering elements from `idx` onwards.
// 3. Create a recursive helper function `countSubsets(idx, currOr, ...)` which represents the core logic.
// 4. In the recursive function:
//    - Base Case: If `idx` reaches the end of the array, all elements have been considered. If `currOr` equals `maxOr`, we've found a valid subset, so we return 1. Otherwise, return 0.
//    - Memoization: Before computing, check if `t[idx][currOr]` already has a calculated value. If so, return it directly.
//    - Recursive Step: Explore two choices for `nums[idx]`:
//      a. Include `nums[idx]`: Make a recursive call with `idx + 1` and an updated `currOr` (`currOr | nums[idx]`).
//      b. Exclude `nums[idx]`: Make a recursive call with `idx + 1` and the same `currOr`.
//    - Combine Results: Sum the counts from both choices (include and exclude).
//    - Store & Return: Store the combined result in `t[idx][currOr]` and return it.
// 5. The main function initiates the process by calling `countSubsets` starting from index 0 with an initial OR of 0.
// Time Complexity: O(n * maxOr), where n is the number of elements and maxOr is the maximum possible bitwise OR. The state of our recursion is defined by (idx, currOr). There are n * maxOr possible states, and each state is computed only once due to memoization.
// Space Complexity: O(n * maxOr), primarily for the memoization table `t`. The recursion stack depth also contributes O(n).
class Solution {
public:
    // This is the recursive helper function with memoization.
    // The un-memoized version would be O(2^n).
    int countSubsets(int idx, int currOr, vector<int>& nums, int maxOr, vector<vector<int> >& t) {
        // Base case: If we've considered all elements.
        if (idx == nums.size()) {
            // Check if the OR of the current subset equals the maximum possible OR.
            if (currOr == maxOr) {
                return 1; // Found one valid subset.
            }
            return 0;     // This subset's OR is not the maximum.
        }

        // Memoization check: If we've already computed this state (idx, currOr), return the stored result.
        if (t[idx][currOr] != -1) {
            return t[idx][currOr];
        }

        // --- Recursive Step ---
        // Choice 1: Include nums[idx] in the subset.
        // The new OR value is currOr | nums[idx].
        int takeCount = countSubsets(idx + 1, currOr | nums[idx], nums, maxOr, t);

        // Choice 2: Exclude nums[idx] from the subset.
        // The OR value remains the same.
        int notTakeCount = countSubsets(idx + 1, currOr, nums, maxOr, t);

        // Store the total count for the current state and return it.
        return t[idx][currOr] = takeCount + notTakeCount;
    }
    
    int countMaxOrSubsets(vector<int>& nums) {
        int maxOr = 0;

        // First, find the maximum possible OR value by OR-ing all elements.
        for (int& num : nums) {
            maxOr |= num;
        }
        int n = nums.size();

        // Initialize memoization table with -1 (indicating not computed).
        // Dimensions: (number of elements + 1) x (maxOr value + 1).
        vector<vector<int> > t(n + 1, vector<int>(maxOr + 1, -1));

        // Start the recursion from the first element (index 0) with an initial OR of 0.
        int currOr = 0;
        return countSubsets(0, currOr, nums, maxOr, t);
    }
};

/*
 * Dry Run
 * Input: nums = [3, 1]
 *
 * 1. `countMaxOrSubsets([3, 1])` is called.
 * 2. Calculate `maxOr`: `maxOr = 3 | 1 = 3`.
 * 3. Initialize `t` as a `3x4` table of -1s.
 * 4. Call `countSubsets(0, 0, nums, 3, t)`.
 * - `idx=0`, `currOr=0`. Not memoized.
 * - `takeCount`: Call `countSubsets(1, 0 | 3, ...)` which is `countSubsets(1, 3, ...)`.
 * - `idx=1`, `currOr=3`. Not memoized.
 * - `takeCount`: Call `countSubsets(2, 3 | 1, ...)` which is `countSubsets(2, 3, ...)`.
 * - `idx=2`. Base case. `currOr` (3) == `maxOr` (3). Return 1. (Subset: [3, 1])
 * - `notTakeCount`: Call `countSubsets(2, 3, ...)`.
 * - `idx=2`. Base case. `currOr` (3) == `maxOr` (3). Return 1. (Subset: [3])
 * - Result for `(1, 3)` is `1 + 1 = 2`. Store `t[1][3] = 2`. Return 2.
 * - `notTakeCount`: Call `countSubsets(1, 0, ...)`.
 * - `idx=1`, `currOr=0`. Not memoized.
 * - `takeCount`: Call `countSubsets(2, 0 | 1, ...)` which is `countSubsets(2, 1, ...)`.
 * - `idx=2`. Base case. `currOr` (1) != `maxOr` (3). Return 0.
 * - `notTakeCount`: Call `countSubsets(2, 0, ...)`.
 * - `idx=2`. Base case. `currOr` (0) != `maxOr` (3). Return 0.
 * - Result for `(1, 0)` is `0 + 0 = 0`. Store `t[1][0] = 0`. Return 0.
 * - Final result for `(0, 0)` is `2 + 0 = 2`. Store `t[0][0] = 2`.
 * 5. Return 2.
 */
