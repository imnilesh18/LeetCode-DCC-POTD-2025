/*
 * 416. Partition Equal Subset Sum
 *
 * Medium
 *
 * Given an integer array nums, return true if you can partition the array into two subsets such that the sum of the elements in both subsets is equal or false otherwise.
 *
 * Example 1:
 * Input: nums = [1,5,11,5]
 * Output: true
 * Explanation: The array can be partitioned as [1, 5, 5] and [11].
 *
 * Example 2:
 * Input: nums = [1,2,3,5]
 * Output: false
 * Explanation: The array cannot be partitioned into equal sum subsets.
 *
 * Constraints:
 * 1 <= nums.length <= 200
 * 1 <= nums[i] <= 100
 */

// Approach: Calculate the total sum of the array; if it's odd, partitioning is impossible. Otherwise, use recursion with memoization to determine if a subset exists with a sum equal to half of the total sum.
// Time Complexity: O(n * target) where target = totalSum/2, since each state (index, currentSum) is computed once.
// Space Complexity: O(n * target) due to the memoization table storing states.
class Solution {
public:
    int t[201][10001];     // Memoization table: t[index][currentSum]

    // Recursive helper to determine if a subset with sum equal to 'target' can be formed.
    bool solve(vector<int>& nums, int target, int currentSum, int idx) {
        // If current subset sum equals target, partition is possible.
        if (currentSum == target) {
            return true;
        }
        // If current sum exceeds target or we've exhausted the list, return false.
        if (currentSum > target || idx >= nums.size()) {
            return false;
        }
        // Return memoized result if available.
        if (t[idx][currentSum] != -1) {
            return t[idx][currentSum];
        }
        // Option 1: Include the current element.
        bool take = solve(nums, target, currentSum + nums[idx], idx + 1);
        // Option 2: Exclude the current element.
        bool skip = solve(nums, target, currentSum, idx + 1);

        // Store and return the result.
        return t[idx][currentSum] = (take || skip);
    }
    
    bool canPartition(vector<int>& nums) {
        int n        = nums.size();
        int totalSum = 0;

        // Calculate total sum of the array.
        for (int i = 0; i < n; i++) {
            totalSum += nums[i];
        }
        // If total sum is odd, equal partitioning is impossible.
        if (totalSum % 2 != 0) {
            return false;
        }
        // Initialize memoization table with -1 (indicating uncomputed states).
        memset(t, -1, sizeof(t));
        // Check if there's a subset with sum equal to totalSum/2.
        return solve(nums, totalSum / 2, 0, 0);
    }
};

/*
 * Dry Run:
 * For nums = [1, 5, 11, 5]:
 * 1. Total sum = 22, so target = 11.
 * 2. Initial call: solve(nums, 11, 0, 0)
 * - At idx = 0, currentSum = 0:
 *   a. Include nums[0] (1) -> new currentSum = 1, call solve(nums, 11, 1, 1)
 * - At idx = 1, currentSum = 1:
 *   a. Include nums[1] (5) -> new currentSum = 6, call solve(nums, 11, 6, 2)
 * - At idx = 2, currentSum = 6:
 *   a. Include nums[2] (11) -> new currentSum = 17 (exceeds target) => returns false.
 *   b. Exclude nums[2] -> currentSum remains 6, call solve(nums, 11, 6, 3)
 * - At idx = 3, currentSum = 6:
 *   a. Include nums[3] (5) -> new currentSum = 11, which equals target => returns true.
 * Since one branch returns true, the final answer is true.
 */
