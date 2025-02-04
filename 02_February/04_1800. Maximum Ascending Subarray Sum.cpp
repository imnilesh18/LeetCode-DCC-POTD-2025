/*
 * 1800. Maximum Ascending Subarray Sum
 *
 * Given an array of positive integers nums, return the maximum possible sum of an ascending subarray in nums.
 * A subarray is defined as a contiguous sequence of numbers in an array.
 * A subarray [numsl, numsl+1, ..., numsr-1, numsr] is ascending if for all i where l <= i < r, numsi  < numsi+1. Note that a subarray of size 1 is ascending.
 *
 * Example 1:
 * Input: nums = [10,20,30,5,10,50]
 * Output: 65
 * Explanation: [5,10,50] is the ascending subarray with the maximum sum of 65.
 *
 * Example 2:
 * Input: nums = [10,20,30,40,50]
 * Output: 150
 * Explanation: [10,20,30,40,50] is the ascending subarray with the maximum sum of 150.
 *
 * Example 3:
 * Input: nums = [12,17,15,13,10,11,12]
 * Output: 33
 * Explanation: [10,11,12] is the ascending subarray with the maximum sum of 33.
 *
 * Constraints:
 * 1 <= nums.length <= 100
 * 1 <= nums[i] <= 100
 */

// Approach: Iterate through the array while maintaining a running sum for the current ascending subarray, and reset it when the order is broken.
// TC: O(n) - Only one pass through the array is required.
// SC: O(1) - Only a few extra variables are used, regardless of input size.
class Solution {
public:
   int maxAscendingSum(vector<int>& nums) {
      int n = nums.size();

      // Initialize the current ascending subarray sum with the first element.
      int sum = nums[0];
      // Initialize the result with the first element's value.
      int result = sum;

      // Iterate through the array starting from the second element.
      for (int i = 1; i < n; i++) {
         // Check if the current number is greater than the previous number,
         // which indicates that the ascending order continues.
         if (nums[i] > nums[i - 1]) {
            // Add the current number to the current ascending subarray sum.
            sum += nums[i];
            // Update the result if the current sum is greater than the previous maximum.
            result = max(result, sum);
         } else {
            // If the ascending order is broken, reset the current sum to the current number.
            sum = nums[i];
         }
      }

      // Return the maximum ascending subarray sum found.
      return result;
   }
};

/*
 * Dry Run:
 * Input: nums = [10, 20, 30, 5, 10, 50]
 * Step 1: Initialize sum = 10, result = 10.
 * Step 2: i = 1, nums[1]=20 > nums[0]=10 -> sum = 10+20=30, result = max(10, 30)=30.
 * Step 3: i = 2, nums[2]=30 > nums[1]=20 -> sum = 30+30=60, result = max(30, 60)=60.
 * Step 4: i = 3, nums[3]=5 is not > nums[2]=30 -> reset sum = 5.
 * Step 5: i = 4, nums[4]=10 > nums[3]=5 -> sum = 5+10=15, result = max(60, 15)=60.
 * Step 6: i = 5, nums[5]=50 > nums[4]=10 -> sum = 15+50=65, result = max(60, 65)=65.
 * Output: 65
 */
