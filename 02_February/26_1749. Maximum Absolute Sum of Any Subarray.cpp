/*
 * 1749. Maximum Absolute Sum of Any Subarray
 * (Solve 53. Maximum Subarray)
 *
 * You are given an integer array nums. The absolute sum of a subarray [numsl, numsl+1, ..., numsr-1, numsr] is abs(numsl + numsl+1 + ... + numsr-1 + numsr).
 *
 * Return the maximum absolute sum of any (possibly empty) subarray of nums.
 *
 * Note that abs(x) is defined as follows:
 *
 * If x is a negative integer, then abs(x) = -x.
 * If x is a non-negative integer, then abs(x) = x.
 *
 * Example 1:
 * Input: nums = [1,-3,2,3,-4]
 * Output: 5
 * Explanation: The subarray [2,3] has absolute sum = abs(2+3) = abs(5) = 5.
 *
 * Example 2:
 * Input: nums = [2,-5,1,-4,3,-2]
 * Output: 8
 * Explanation: The subarray [-5,1,-4] has absolute sum = abs(-5+1-4) = abs(-8) = 8.
 *
 * Constraints:
 * 1 <= nums.length <= 10^5
 * -10^4 <= nums[i] <= 10^4
 */

// Approach: Use two variants of Kadane's algorithm—one to find the maximum subarray sum and one to find the minimum subarray sum—and return the maximum between the maximum sum and the absolute value of the minimum sum.
// TC: O(n) - We traverse the array twice, each in linear time.
// SC: O(1) - Only a few extra variables are used.
class Solution {
public:
   int maxAbsoluteSum(vector<int>& nums) {
      int n = nums.size();

      // Calculate maximum subarray sum using Kadane's algorithm
      int maxSum     = nums[0];
      int currSumMax = nums[0];

      for (int i = 1; i < n; i++) {
         // Update current max sum: either start fresh at nums[i] or extend the previous subarray sum
         currSumMax = max(nums[i], currSumMax + nums[i]);
         // Update global maximum subarray sum if needed
         maxSum = max(maxSum, currSumMax);
      }

      // Calculate minimum subarray sum using a similar approach
      int minSum     = nums[0];
      int currMinSum = nums[0];
      for (int i = 1; i < n; i++) {
         // Update current min sum: either start fresh at nums[i] or extend the previous subarray sum for min calculation
         currMinSum = min(nums[i], currMinSum + nums[i]);
         // Update global minimum subarray sum if needed
         minSum = min(minSum, currMinSum);
      }

      // The answer is the maximum between the maximum subarray sum and the absolute value of the minimum subarray sum
      return max(maxSum, abs(minSum));
   }
};

/*
 * Dry Run
 * Input: nums = [1, -3, 2, 3, -4]
 *
 * For maximum subarray sum:
 * i = 0: maxSum = 1, currSumMax = 1
 * i = 1: currSumMax = max(-3, 1 + (-3)) = -2, maxSum = max(1, -2) = 1
 * i = 2: currSumMax = max(2, -2 + 2) = 2, maxSum = max(1, 2) = 2
 * i = 3: currSumMax = max(3, 2 + 3) = 5, maxSum = max(2, 5) = 5
 * i = 4: currSumMax = max(-4, 5 + (-4)) = 1, maxSum = max(5, 1) = 5
 *
 * For minimum subarray sum:
 * i = 0: minSum = 1, currMinSum = 1
 * i = 1: currMinSum = min(-3, 1 + (-3)) = -3, minSum = min(1, -3) = -3
 * i = 2: currMinSum = min(2, -3 + 2) = -1, minSum = min(-3, -1) = -3
 * i = 3: currMinSum = min(3, -1 + 3) = 2, minSum = min(-3, 2) = -3
 * i = 4: currMinSum = min(-4, 2 + (-4)) = -4, minSum = min(-3, -4) = -4
 *
 * Final Answer: max(5, abs(-4)) = max(5, 4) = 5
 * End Dry Run
 */

// Approach (Same but clean code in one loop): Use Kadane's algorithm to compute both the maximum and minimum subarray sums, then return the larger between the maximum sum and the absolute value of the minimum sum.
// TC: O(n) - We iterate over the array once.
// SC: O(1) - Only a fixed number of extra variables are used.
class Solution {
public:
   int maxAbsoluteSum(vector<int>& nums) {
      int n = nums.size();       // Get the size of the input array

      int maxSum = nums[0];      // Initialize maximum sum with the first element
      int minSum = nums[0];      // Initialize minimum sum with the first element

      int currSumMax = nums[0];  // Current maximum subarray sum
      int currMinSum = nums[0];  // Current minimum subarray sum

      // Traverse the array starting from the second element
      for (int i = 1; i < n; i++) {
         // Update the current maximum subarray sum: either start a new subarray at nums[i] or extend the previous subarray sum
         currSumMax = max(nums[i], currSumMax + nums[i]);
         // Update the global maximum subarray sum if the new value is larger
         maxSum = max(maxSum, currSumMax);

         // Update the current minimum subarray sum: either start a new subarray at nums[i] or extend the previous subarray sum
         currMinSum = min(nums[i], currMinSum + nums[i]);
         // Update the global minimum subarray sum if the new value is smaller
         minSum = min(minSum, currMinSum);
      }
      // Return the maximum between the maximum subarray sum and the absolute value of the minimum subarray sum
      return max(maxSum, abs(minSum));
   }
};

/*
 * Dry Run
 * Input: nums = [1, -3, 2, 3, -4]
 *
 * For maximum subarray sum:
 * i = 0: maxSum = 1, currSumMax = 1
 * i = 1: currSumMax = max(-3, 1 + (-3)) = -2, maxSum = max(1, -2) = 1
 * i = 2: currSumMax = max(2, -2 + 2) = 2, maxSum = max(1, 2) = 2
 * i = 3: currSumMax = max(3, 2 + 3) = 5, maxSum = max(2, 5) = 5
 * i = 4: currSumMax = max(-4, 5 + (-4)) = 1, maxSum = max(5, 1) = 5
 *
 * For minimum subarray sum:
 * i = 0: minSum = 1, currMinSum = 1
 * i = 1: currMinSum = min(-3, 1 + (-3)) = -3, minSum = min(1, -3) = -3
 * i = 2: currMinSum = min(2, -3 + 2) = -1, minSum = min(-3, -1) = -3
 * i = 3: currMinSum = min(3, -1 + 3) = 2, minSum = min(-3, 2) = -3
 * i = 4: currMinSum = min(-4, 2 + (-4)) = -4, minSum = min(-3, -4) = -4
 *
 * Final Answer: max(5, abs(-4)) = max(5, 4) = 5
 * End Dry Run
 */
