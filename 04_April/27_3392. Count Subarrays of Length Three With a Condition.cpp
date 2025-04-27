/*
 * 3392. Count Subarrays of Length Three With a Condition
 *
 * Easy
 *
 * Given an integer array nums, return the number of subarrays of length 3 such that the sum of the first and third numbers equals exactly half of the second number.
 *
 * Example 1:
 * Input: nums = [1,2,1,4,1]
 * Output: 1
 * Explanation:
 * Only the subarray [1,4,1] contains exactly 3 elements where the sum of the first and third numbers equals half the middle number.
 *
 * Example 2:
 * Input: nums = [1,1,1]
 * Output: 0
 * Explanation:
 * [1,1,1] is the only subarray of length 3. However, its first and third numbers do not add to half the middle number.
 *
 * Constraints:
 * 3 <= nums.length <= 100
 * -100 <= nums[i] <= 100
 */

// Approach: Slide a window of size 3 and for each middle element check if twice it equals the sum of its neighbors, incrementing a counter when it does.
// Time Complexity: O(n) – single pass through the array of length n.
// Space Complexity: O(1) – only a few integer variables used.
class Solution {
public:
    int countSubarrays(vector<int>& nums) {
        int n     = nums.size();
        int count = 0;

        // iterate from the second element to the second-last element
        for (int i = 1; i < n - 1; i++) {
            // if current middle element equals twice the sum of its immediate neighbors
            if (nums[i] == (nums[i - 1] + nums[i + 1]) * 2) {
                count++;     // condition met, increment counter
            }
        }
        return count;     // return total count of valid subarrays
    }
};

/*
 *
 * Dry Run 1
 *
 * Example: nums = [1, 2, 1, 4, 1]
 *
 * i = 1: window = [1, 2, 1]
 *       (nums[0] + nums[2]) * 2 = (1 + 1) * 2 = 4
 *       nums[1] = 2 → 2 != 4 → count = 0
 *
 * i = 2: window = [2, 1, 4]
 *       (nums[1] + nums[3]) * 2 = (2 + 4) * 2 = 12
 *       nums[2] = 1 → 1 != 12 → count = 0
 *
 * i = 3: window = [1, 4, 1]
 *       (nums[2] + nums[4]) * 2 = (1 + 1) * 2 = 4
 *       nums[3] = 4 → 4 == 4 → count = 1
 *
 * End loop → return 1
 *
 * Dry Run 2
 *
 * Example: nums = [2, 8, 2, 10, 3]
 *
 * i = 1: window = [2, 8, 2]
 *       (nums[0] + nums[2]) * 2 = (2 + 2) * 2 = 8
 *       nums[1] = 8 → 8 == 8 → count = 1
 *
 * i = 2: window = [8, 2, 10]
 *       (nums[1] + nums[3]) * 2 = (8 + 10) * 2 = 36
 *       nums[2] = 2 → 2 != 36 → count = 1
 *
 * i = 3: window = [2, 10, 3]
 *       (nums[2] + nums[4]) * 2 = (2 + 3) * 2 = 10
 *       nums[3] = 10 → 10 == 10 → count = 2
 *
 * End loop → return 2
 */
