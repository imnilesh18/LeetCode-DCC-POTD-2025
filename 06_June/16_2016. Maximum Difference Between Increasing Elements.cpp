/*
 * 2016. Maximum Difference Between Increasing Elements
 *
 * Easy
 *
 * Given a 0-indexed integer array nums of size n, find the maximum difference between nums[i] and nums[j] (i.e., nums[j] - nums[i]), such that 0 <= i < j < n and nums[i] < nums[j].
 * Return the maximum difference. If no such i and j exists, return -1.
 *
 * Example 1:
 * Input: nums = [7,1,5,4]
 * Output: 4
 * Explanation:
 * The maximum difference occurs with i = 1 and j = 2, nums[j] - nums[i] = 5 - 1 = 4.
 * Note that with i = 1 and j = 0, the difference nums[j] - nums[i] = 7 - 1 = 6, but i > j, so it is not valid.
 *
 * Example 2:
 * Input: nums = [9,4,3,2]
 * Output: -1
 * Explanation:
 * There is no i and j such that i < j and nums[i] < nums[j].
 *
 * Example 3:
 * Input: nums = [1,5,2,10]
 * Output: 9
 * Explanation:
 * The maximum difference occurs with i = 0 and j = 3, nums[j] - nums[i] = 10 - 1 = 9.
 *
 * Constraints:
 * n == nums.length
 * 2 <= n <= 1000
 * 1 <= nums[i] <= 10^9
 */

// Approach: Traverse the array while keeping track of the minimum element so far. For each element, if it's greater than the minimum, compute the difference and update maxDiff.
// Time Complexity: O(n) – We traverse the array only once.
// Space Complexity: O(1) – We use only constant extra space.
class Solution {
public:
    int maximumDifference(vector<int>& nums) {
        int n       = nums.size();
        int minEl   = nums[0]; // Initialize the minimum element as the first element
        int maxDiff = -1;      // Start with -1 as per the problem requirement

        for (int j = 1; j < n; j++) {
            if (nums[j] > minEl) {
                // If current number is greater than the minimum seen so far,
                // calculate the difference and update maxDiff if it's larger
                maxDiff = max(maxDiff, nums[j] - minEl);
            } else {
                // If current number is smaller or equal, update minEl
                minEl = nums[j];
            }
        }

        return maxDiff; // Return the maximum difference found, or -1 if none
    }
};

/*
 *
 * Dry Run
 *
 * Input: nums = [1, 5, 2, 10]
 * --------------------------------
 * Initialize:
 *   minEl   = 1
 *   maxDiff = -1
 *
 * Iteration 1 (j = 1):
 *   nums[1] = 5
 *   5 > minEl (1)? Yes → diff = 5 - 1 = 4
 *   maxDiff = max(-1, 4) = 4
 *
 * Iteration 2 (j = 2):
 *   nums[2] = 2
 *   2 > minEl (1)? Yes → diff = 2 - 1 = 1
 *   maxDiff = max(4, 1) = 4 (no change)
 *
 * Iteration 3 (j = 3):
 *   nums[3] = 10
 *   10 > minEl (1)? Yes → diff = 10 - 1 = 9
 *   maxDiff = max(4, 9) = 9
 *
 * End of loop.
 * Return maxDiff = 9
 *
 */
