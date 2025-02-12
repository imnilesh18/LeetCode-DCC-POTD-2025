/*
 * 2342. Max Sum of a Pair With Equal Sum of Digits
 *
 * You are given a 0-indexed array nums consisting of positive integers. You can choose two indices i and j, such that i != j, and the sum of digits of the number nums[i] is equal to that of nums[j].
 *
 * Return the maximum value of nums[i] + nums[j] that you can obtain over all possible indices i and j that satisfy the conditions.
 *
 * Example 1:
 * Input: nums = [18,43,36,13,7]
 * Output: 54
 * Explanation: The pairs (i, j) that satisfy the conditions are:
 * - (0, 2), both numbers have a sum of digits equal to 9, and their sum is 18 + 36 = 54.
 * - (1, 4), both numbers have a sum of digits equal to 7, and their sum is 43 + 7 = 50.
 * So the maximum sum that we can obtain is 54.
 *
 * Example 2:
 * Input: nums = [10,12,19,14]
 * Output: -1
 * Explanation: There are no two numbers that satisfy the conditions, so we return -1.
 *
 * Constraints:
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^9
 */

//  Approach 1 (Brute Force): Iterate through all pairs in the array, calculate each number's digit sum, and update the maximum sum for pairs with equal digit sums.
//  Time Complexity: O(n^2 * log(num)) where n is the number of elements and log(num) is the time to compute digit sum of each number.
//  Space Complexity: O(1) as only constant extra space is used.
class Solution {
public:
   // Helper function to calculate the sum of digits of a given number
   int getDigitSum(int num) {
      int sum = 0;

      // Loop until num becomes 0
      while (num > 0) {
         sum += (num % 10); // Add the last digit to sum
         num /= 10;         // Remove the last digit from num
      }
      return sum;           // Return the total sum of digits
   }

   // Function to find the maximum sum of a pair with equal digit sum
   int maximumSum(vector<int>& nums) {
      int n      = nums.size();
      int result = -1;     // Initialize result to -1 (default if no valid pair is found)

      // Iterate through each element in the array
      for (int i = 0; i < n; i++) {
         int digitSumi = getDigitSum(nums[i]);      // Compute digit sum for nums[i]
         // Check pairs with all elements coming after the current element
         for (int j = i + 1; j < n; j++) {
            int digitSumj = getDigitSum(nums[j]);       // Compute digit sum for nums[j]

            // If both numbers have the same digit sum, update the result if their sum is higher
            if (digitSumi == digitSumj) {
               result = max(result, nums[i] + nums[j]);
            }
         }
      }

      return result;     // Return the maximum sum found (or -1 if no pair satisfies the condition)
   }
};

/*
 * Dry Run:
 * Input: nums = [18, 43, 36, 13, 7]
 *
 * Step-by-step:
 * 1. i = 0, nums[0] = 18, getDigitSum(18) = 1 + 8 = 9
 * - j = 1, nums[1] = 43, getDigitSum(43) = 4 + 3 = 7 -> Not equal.
 * - j = 2, nums[2] = 36, getDigitSum(36) = 3 + 6 = 9 -> Equal, update result = max(-1, 18 + 36) = 54.
 * - j = 3, nums[3] = 13, getDigitSum(13) = 1 + 3 = 4 -> Not equal.
 * - j = 4, nums[4] = 7,  getDigitSum(7)  = 7 -> Not equal.
 *
 * 2. i = 1, nums[1] = 43, getDigitSum(43) = 7
 * - j = 2, nums[2] = 36, getDigitSum(36) = 9 -> Not equal.
 * - j = 3, nums[3] = 13, getDigitSum(13) = 4 -> Not equal.
 * - j = 4, nums[4] = 7,  getDigitSum(7)  = 7 -> Equal, update result = max(54, 43 + 7) = 54.
 *
 * 3. i = 2, nums[2] = 36, getDigitSum(36) = 9
 * - j = 3, nums[3] = 13, getDigitSum(13) = 4 -> Not equal.
 * - j = 4, nums[4] = 7,  getDigitSum(7)  = 7 -> Not equal.
 *
 * 4. i = 3, nums[3] = 13, getDigitSum(13) = 4
 * - j = 4, nums[4] = 7,  getDigitSum(7)  = 7 -> Not equal.
 *
 * Final result = 54
 *** End Dry Run.
 */

// Approach 2 (Optimized): Use an unordered_map to track the maximum number for each digit sum encountered.
// For each number, compute its digit sum, check if a number with the same digit sum was seen before and update the result accordingly.
// Then update the mapping with the maximum number for that digit sum.
// Time Complexity: O(n * log(num)) where n is the number of elements and log(num) is the time to compute the digit sum for each number.
// Space Complexity: O(n) in the worst-case scenario.
class Solution {
public:
   // Helper function to calculate the sum of digits of a given number.
   int getDigitSum(int num) {
      int sum = 0;

      // Loop until num becomes 0
      while (num > 0) {
         sum += (num % 10); // Add the last digit to sum
         num /= 10;         // Remove the last digit from num
      }
      return sum;           // Return the total sum of digits
   }

   // Function to find the maximum sum of a pair with equal digit sum.
   int maximumSum(vector<int>& nums) {
      int n      = nums.size();
      int result = -1;            // Initialize result to -1 (default if no valid pair is found)
      unordered_map<int, int> mp; // Map to store the maximum number for each digit sum

      // Iterate through each number in the array
      for (int i = 0; i < n; i++) {
         int digitSum = getDigitSum(nums[i]);        // Compute digit sum for the current number

         // If a number with the same digit sum exists, update the result with the sum of the two numbers
         if (mp.count(digitSum)) {
            result = max(result, nums[i] + mp[digitSum]);
         }

         // Update the map with the maximum number for this digit sum
         mp[digitSum] = max(mp[digitSum], nums[i]);
      }

      return result;       // Return the maximum sum found (or -1 if no pair satisfies the condition)
   }
};

/*
 * Dry Run:
 * Input: nums = [18, 43, 36, 13, 7]
 *
 * Step-by-step:
 * 1. i = 0, nums[0] = 18, getDigitSum(18) = 1 + 8 = 9
 *    - mp does not contain key 9, so add: mp[9] = 18.
 *
 * 2. i = 1, nums[1] = 43, getDigitSum(43) = 4 + 3 = 7
 *    - mp does not contain key 7, so add: mp[7] = 43.
 *
 * 3. i = 2, nums[2] = 36, getDigitSum(36) = 3 + 6 = 9
 *    - mp contains key 9 with value 18, update result = max(-1, 36 + 18) = 54.
 *    - Update mp[9] = max(18, 36) = 36.
 *
 * 4. i = 3, nums[3] = 13, getDigitSum(13) = 1 + 3 = 4
 *    - mp does not contain key 4, so add: mp[4] = 13.
 *
 * 5. i = 4, nums[4] = 7, getDigitSum(7) = 7
 *    - mp contains key 7 with value 43, update result = max(54, 7 + 43) = 54.
 *    - Update mp[7] = max(43, 7) = 43.
 *
 * Final result = 54
 * End Dry Run.
 */

// Approach 3 (Optimized with Fixed Array): Use a fixed size array of length 82 (since the maximum digit sum for any number up to 10^9 is 81)
// to track the maximum number for each digit sum. For each number, compute its digit sum, check if a number with the same digit sum exists,
// update the maximum sum accordingly, and update the array with the maximum number for that digit sum.
// Time Complexity: O(n * log(num)) where n is the number of elements and log(num) is the time to compute the digit sum of each number.
// Space Complexity: O(1) as the array size is fixed.
class Solution {
public:
   // Helper function to calculate the sum of digits of a given number.
   int getDigitSum(int num) {
      int sum = 0;

      // Loop until num becomes 0
      while (num > 0) {
         sum += (num % 10); // Add the last digit to sum
         num /= 10;         // Remove the last digit from num
      }
      return sum;           // Return the total sum of digits
   }

   // Function to find the maximum sum of a pair with equal digit sum.
   int maximumSum(vector<int>& nums) {
      int n      = nums.size();
      int result = -1;    // Initialize result to -1 (default if no valid pair is found)

      int mp[82] = { 0 }; // Fixed size array to store the maximum number for each digit sum (0 to 81)

      // Iterate through each number in the array
      for (int i = 0; i < n; i++) {
         int digitSum = getDigitSum(nums[i]);     // Compute digit sum for the current number

         // If a number with the same digit sum has been seen, update the result with the sum of the two numbers
         if (mp[digitSum]) {
            result = max(result, nums[i] + mp[digitSum]);
         }

         // Update the array with the maximum number for this digit sum
         mp[digitSum] = max(mp[digitSum], nums[i]);
      }

      return result;    // Return the maximum sum found (or -1 if no pair satisfies the condition)
   }
};

/*
 * Dry Run:
 * Input: nums = [18, 43, 36, 13, 7]
 *
 * Step-by-step:
 * 1. i = 0, nums[0] = 18, getDigitSum(18) = 1 + 8 = 9
 *    - mp[9] is 0, so set mp[9] = 18.
 *
 * 2. i = 1, nums[1] = 43, getDigitSum(43) = 4 + 3 = 7
 *    - mp[7] is 0, so set mp[7] = 43.
 *
 * 3. i = 2, nums[2] = 36, getDigitSum(36) = 3 + 6 = 9
 *    - mp[9] is 18, update result = max(-1, 36 + 18) = 54.
 *    - Set mp[9] = max(18, 36) = 36.
 *
 * 4. i = 3, nums[3] = 13, getDigitSum(13) = 1 + 3 = 4
 *    - mp[4] is 0, so set mp[4] = 13.
 *
 * 5. i = 4, nums[4] = 7, getDigitSum(7) = 7
 *    - mp[7] is 43, update result = max(54, 7 + 43) = 54.
 *    - Set mp[7] = max(43, 7) = 43.
 *
 * Final result = 54
 * End Dry Run.
 */
