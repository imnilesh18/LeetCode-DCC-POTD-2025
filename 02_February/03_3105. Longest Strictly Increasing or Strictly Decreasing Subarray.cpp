/*
 * 3105. Longest Strictly Increasing or Strictly Decreasing Subarray
 *
 * You are given an array of integers nums. Return the length of the longest subarray of nums which is either strictly increasing or strictly decreasing.
 *
 * Example 1:
 * Input: nums = [1,4,3,3,2]
 * Output: 2
 * Explanation:
 * The strictly increasing subarrays of nums are [1], [2], [3], [3], [4], and [1,4].
 * The strictly decreasing subarrays of nums are [1], [2], [3], [3], [4], [3,2], and [4,3].
 * Hence, we return 2.
 *
 * Example 2:
 * Input: nums = [3,3,3,3]
 * Output: 1
 * Explanation:
 * The strictly increasing subarrays of nums are [3], [3], [3], and [3].
 * The strictly decreasing subarrays of nums are [3], [3], [3], and [3].
 * Hence, we return 1.
 *
 * Example 3:
 * Input: nums = [3,2,1]
 * Output: 3
 * Explanation:
 * The strictly increasing subarrays of nums are [3], [2], and [1].
 * The strictly decreasing subarrays of nums are [3], [2], [1], [3,2], [2,1], and [3,2,1].
 * Hence, we return 3.
 *
 * Constraints:
 * 1 <= nums.length <= 50
 * 1 <= nums[i] <= 50
 */

// Approach 1 (Brute Force): For each starting index, expand in both increasing and decreasing directions while comparing adjacent elements; record the maximum subarray length found.
// TC: O(n^2) in worst case, where n is the number of elements.
// SC: O(1) extra space.
class Solution {
public:
   int longestMonotonicSubarray(vector<int>& nums) {
      int n      = nums.size();
      int result = 0;

      // Iterate through each index as the starting point of a subarray.
      for (int i = 0; i < n; i++) {
         // Check for strictly increasing subarray starting at index i.
         int incr = 1;     // At minimum, the subarray includes nums[i].
         int j    = i + 1;
         // Continue while the current element is greater than the previous one.
         while (j < n && nums[j] > nums[j - 1]) {
            j++;
            incr++;
         }

         // Reset j to check for strictly decreasing subarray starting at index i.
         j = i + 1;
         int decr = 1;     // At minimum, the subarray includes nums[i].
         // Continue while the current element is less than the previous one.
         while (j < n && nums[j] < nums[j - 1]) {
            j++;
            decr++;
         }

         // Update the result with the maximum length among the current increasing and decreasing subarrays.
         result = max({ result, incr, decr });
      }
      return result;
   }
};

/*
 * Dry Run:
 * Input: nums = [1, 4, 3, 3, 2]
 *
 * Iteration i = 0:
 *  - Increasing:
 *      start at index 0 (value 1), then index 1 (value 4) -> valid because 4 > 1; incr becomes 2.
 *      index 2 (value 3) -> stops because 3 is not greater than 4.
 *      incr = 2.
 *  - Decreasing:
 *      start at index 0 (value 1), then index 1 (value 4) -> stops because 4 is not less than 1.
 *      decr = 1.
 *  - result = max(0, 2, 1) = 2.
 *
 * Iteration i = 1:
 *  - Increasing:
 *      start at index 1 (value 4), then index 2 (value 3) -> stops because 3 is not greater than 4.
 *      incr = 1.
 *  - Decreasing:
 *      start at index 1 (value 4), then index 2 (value 3) -> valid because 3 < 4; decr becomes 2.
 *      index 3 (value 3) -> stops because 3 is not less than 3.
 *      decr = 2.
 *  - result = max(2, 1, 2) = 2.
 *
 * Iteration i = 2:
 *  - Increasing:
 *      start at index 2 (value 3), then index 3 (value 3) -> stops because 3 is not greater than 3.
 *      incr = 1.
 *  - Decreasing:
 *      start at index 2 (value 3), then index 3 (value 3) -> stops because 3 is not less than 3.
 *      decr = 1.
 *  - result remains 2.
 *
 * Iteration i = 3:
 *  - Increasing:
 *      start at index 3 (value 3), then index 4 (value 2) -> stops because 2 is not greater than 3.
 *      incr = 1.
 *  - Decreasing:
 *      start at index 3 (value 3), then index 4 (value 2) -> valid because 2 < 3; decr becomes 2.
 *      decr = 2.
 *  - result remains 2.
 *
 * Iteration i = 4:
 *  - Increasing:
 *      Only index 4 is considered, so incr = 1.
 *  - Decreasing:
 *      Only index 4 is considered, so decr = 1.
 *  - result remains 2.
 *
 * Final output: 2
 *
 */

// Approach 2: Traverse the array once while maintaining two counters (incr for increasing and decr for decreasing sequences), resetting the other counter when the current comparison doesn't match; update the result with the maximum counter value encountered.
// TC: O(n), where n is the number of elements in nums.
// SC: O(1) extra space.
class Solution {
public:
   int longestMonotonicSubarray(vector<int>& nums) {
      int n = nums.size();

      // Initialize counters for increasing and decreasing subarrays.
      int incr = 1;    // Counter for strictly increasing sequence.
      int decr = 1;    // Counter for strictly decreasing sequence.

      int result = 1;  // At minimum, a single element is a valid subarray.

      // Start traversing from the second element.
      for (int i = 1; i < n; i++) {
         if (nums[i] > nums[i - 1]) {        // Check for an increasing pattern.
            incr++;                          // Increment the increasing counter.
            decr   = 1;                      // Reset the decreasing counter.
            result = max(result, incr);      // Update result with the maximum length.
         } else if (nums[i] < nums[i - 1]) { // Check for a decreasing pattern.
            decr++;                          // Increment the decreasing counter.
            incr   = 1;                      // Reset the increasing counter.
            result = max(result, decr);      // Update result with the maximum length.
         } else {
            // When equal, neither increasing nor decreasing continues.
            incr = 1;
            decr = 1;
         }
      }
      return result;
   }
};

/*
 * Dry Run:
 * Input: nums = [1, 4, 3, 3, 2]
 *
 * Initial state: incr = 1, decr = 1, result = 1
 *
 * Iteration i = 1 (nums[1]=4, nums[0]=1):
 *  - 4 > 1: increasing pattern.
 *  - Update incr = 2, reset decr = 1.
 *  - result = max(1, 2) = 2.
 *
 * Iteration i = 2 (nums[2]=3, nums[1]=4):
 *  - 3 < 4: decreasing pattern.
 *  - Update decr = 2, reset incr = 1.
 *  - result = max(2, 2) = 2.
 *
 * Iteration i = 3 (nums[3]=3, nums[2]=3):
 *  - 3 == 3: neither increasing nor decreasing.
 *  - Reset both incr = 1, decr = 1.
 *  - result remains 2.
 *
 * Iteration i = 4 (nums[4]=2, nums[3]=3):
 *  - 2 < 3: decreasing pattern.
 *  - Update decr = 2, reset incr = 1.
 *  - result = max(2, 2) = 2.
 *
 * Final output: 2
 *
 */
