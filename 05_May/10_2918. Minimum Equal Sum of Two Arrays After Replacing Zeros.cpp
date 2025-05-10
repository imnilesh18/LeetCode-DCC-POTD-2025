/*
 * 2918. Minimum Equal Sum of Two Arrays After Replacing Zeros
 *
 * Medium
 *
 * You are given two arrays nums1 and nums2 consisting of positive integers.
 * You have to replace all the 0's in both arrays with strictly positive integers such that the sum of elements of both arrays becomes equal.
 * Return the minimum equal sum you can obtain, or -1 if it is impossible.
 *
 * Example 1:
 * Input: nums1 = [3,2,0,1,0], nums2 = [6,5,0]
 * Output: 12
 * Explanation: We can replace 0's in the following way:
 * - Replace the two 0's in nums1 with the values 2 and 4. The resulting array is nums1 = [3,2,2,1,4].
 * - Replace the 0 in nums2 with the value 1. The resulting array is nums2 = [6,5,1].
 * Both arrays have an equal sum of 12. It can be shown that it is the minimum sum we can obtain.
 *
 * Example 2:
 * Input: nums1 = [2,0,2,0], nums2 = [1,4]
 * Output: -1
 * Explanation: It is impossible to make the sum of both arrays equal.
 *
 * Constraints:
 * 1 <= nums1.length, nums2.length <= 10^5
 * 0 <= nums1[i], nums2[i] <= 10^6
 */

// Approach: Replace each 0 with 1 (minimum possible) to get initial sum1 and sum2. If one sum is smaller but its array has no zeros left to increase, return -1. Else, return the maximum of both sums.
// Time Complexity: O(n + m), where n = size of nums1 and m = size of nums2, as we iterate over both arrays once.
// Space Complexity: O(1), as only constant extra space is used.
class Solution {
public:
    long long minSum(vector<int>& nums1, vector<int>& nums2) {
        long long sum1 = 0;  // To store adjusted sum of nums1
        long long sum2 = 0;  // To store adjusted sum of nums2

        long long zero1 = 0; // To count zeros in nums1
        long long zero2 = 0; // To count zeros in nums2

        // Iterate through nums1
        for (int& num : nums1) {
            sum1  += num == 0 ? 1 : num; // Replace 0 with 1 for now
            zero1 += num == 0 ? 1 : 0;   // Count zero
        }

        // Iterate through nums2
        for (int& num : nums2) {
            sum2  += num == 0 ? 1 : num; // Replace 0 with 1 for now
            zero2 += num == 0 ? 1 : 0;   // Count zero
        }

        // If the smaller sum array has no zeros left to increase, return -1
        if ((sum1 < sum2 && zero1 == 0) || (sum2 < sum1 && zero2 == 0)) {
            return -1;
        }

        // Return the maximum of both sums (we can adjust 0s to reach this sum)
        return max(sum1, sum2);
    }
};

/*
 *
 * Dry Run
 *
 * Input: nums1 = [3,2,0,1,0], nums2 = [6,5,0]
 *
 * Step 1: Replace zeros with 1s temporarily
 * nums1 -> [3,2,1,1,1], sum1 = 3+2+1+1+1 = 8, zero1 = 2
 * nums2 -> [6,5,1], sum2 = 6+5+1 = 12, zero2 = 1
 *
 * Step 2: sum1 < sum2 and zero1 > 0 → OK, we can adjust
 * Return max(sum1, sum2) = 12
 *
 * This is correct because we can change the 2 zeros in nums1 from 1 to 2 and 4, making sum1 = 3+2+2+1+4 = 12
 * And nums2 already has 6+5+1 = 12
 *
 * Hence, output is 12
 *
 */
