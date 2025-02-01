/*
 * 3151. Special Array I
 *
 * An array is considered special if every pair of its adjacent elements contains two numbers with different parity.
 * You are given an array of integers nums. Return true if nums is a special array, otherwise, return false.
 *
 * Example 1:
 * Input: nums = [1]
 * Output: true
 * Explanation:
 * There is only one element. So the answer is true.
 *
 * Example 2:
 * Input: nums = [2,1,4]
 * Output: true
 * Explanation:
 * There is only two pairs: (2,1) and (1,4), and both of them contain numbers with different parity. So the answer is true.
 *
 * Example 3:
 * Input: nums = [4,3,1,6]
 * Output: false
 * Explanation:
 * nums[1] and nums[2] are both odd. So the answer is false.
 *
 * Constraints:
 * 1 <= nums.length <= 100
 * 1 <= nums[i] <= 100
 */

// Approach 1: Iterate through the array and check each pair of adjacent elements for differing parity.
// Time Complexity: O(n) because we iterate through the array once (n-1 comparisons).
// Space Complexity: O(1) because we use only a few extra variables regardless of input size.
class Solution {
public:
   bool isArraySpecial(vector<int>& nums) {
      int n = nums.size();   // Get the number of elements in the array

      // Loop through the array until the second last element
      for (int i = 0; i <= n - 2; i++) {
         // Check if the current element and the next element have the same parity
         // If so, the condition for a special array is violated.
         if (nums[i] % 2 == nums[i + 1] % 2) {
            return false;     // Return false immediately if two adjacent numbers share the same parity
         }
      }
      // Return true if no adjacent elements have the same parity, meaning the array is special
      return true;
   }
};

// Approach 2: Iterate over the array and use bitwise operations to check if every pair of adjacent elements has different parity.
// Time Complexity: O(n) - We traverse the array once, checking each adjacent pair.
// Space Complexity: O(1) - Only a few extra variables are used regardless of the array size.
class Solution {
public:
   bool isArraySpecial(vector<int>& nums) {
      int n = nums.size();   // Get the number of elements in the array

      // Loop through the array until the second last element
      for (int i = 0; i <= n - 2; i++) {
         // Use bitwise AND to check parity: (num & 1) is 0 for even and 1 for odd.
         // If two adjacent numbers have the same parity, return false.
         if ((nums[i] & 1) == (nums[i + 1] & 1)) {
            return false;
         }
      }
      // If all adjacent pairs have different parity, return true.
      return true;
   }
};
