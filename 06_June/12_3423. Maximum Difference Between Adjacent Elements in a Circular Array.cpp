/*
 * 3423. Maximum Difference Between Adjacent Elements in a Circular Array
 *
 * Easy
 *
 * Given a circular array nums, find the maximum absolute difference between adjacent elements.
 * Note: In a circular array, the first and last elements are adjacent.
 *
 * Example 1:
 * Input: nums = [1,2,4]
 * Output: 3
 * Explanation:
 * Because nums is circular, nums[0] and nums[2] are adjacent. They have the maximum absolute difference of |4 - 1| = 3.
 *
 * Example 2:
 * Input: nums = [-5,-10,-5]
 * Output: 5
 * Explanation:
 * The adjacent elements nums[0] and nums[1] have the maximum absolute difference of |-5 - (-10)| = 5.
 *
 * Constraints:
 * 2 <= nums.length <= 100
 * -100 <= nums[i] <= 100
 */

// Approach: Loop through each element and compute the absolute difference with its next adjacent (considering circular nature using modulo).
// Time Complexity: O(n), where n is the length of the array, since we traverse it once.
// Space Complexity: O(1), as we use constant extra space.
class Solution {
public:
    int maxAdjacentDistance(vector<int>& nums) {
        int n       = nums.size(); // Get the size of the array
        int maxDiff = 0;           // Initialize maxDiff to store the maximum absolute difference

        for (int i = 0; i < n; i++) {
            // Use modulo to handle circular adjacency (last element to first)
            maxDiff = max(maxDiff, abs(nums[i] - nums[(i + 1) % n]));
        }

        return maxDiff; // Return the maximum found difference
    }
};

/*
 *
 * Dry Run
 *
 * Input: nums = [1, 2, 4]
 * n = 3
 * Initialize maxDiff = 0
 *
 * i = 0:
 *   Compare nums[0] = 1 and nums[1] = 2
 *   abs(1 - 2) = 1 → maxDiff = max(0, 1) = 1
 *
 * i = 1:
 *   Compare nums[1] = 2 and nums[2] = 4
 *   abs(2 - 4) = 2 → maxDiff = max(1, 2) = 2
 *
 * i = 2:
 *   Compare nums[2] = 4 and nums[0] = 1 (circular adjacency)
 *   abs(4 - 1) = 3 → maxDiff = max(2, 3) = 3
 *
 * Final Output: 3
 *
 */
