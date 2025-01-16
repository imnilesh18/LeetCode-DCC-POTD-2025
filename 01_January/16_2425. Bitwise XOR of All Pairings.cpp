/*
 * 2425. Bitwise XOR of All Pairings
 *
 * You are given two 0-indexed arrays, nums1 and nums2, consisting of non-negative integers. There exists another array, nums3, which contains the bitwise XOR of all pairings of integers between nums1 and nums2 (every integer in nums1 is paired with every integer in nums2 exactly once).
 * Return the bitwise XOR of all integers in nums3.
 *
 * Example 1:
 * Input: nums1 = [2,1,3], nums2 = [10,2,5,0]
 * Output: 13
 * Explanation:
 * A possible nums3 array is [8,0,7,2,11,3,4,1,9,1,6,3].
 * The bitwise XOR of all these numbers is 13, so we return 13.
 *
 * Example 2:
 * Input: nums1 = [1,2], nums2 = [3,4]
 * Output: 0
 * Explanation:
 * All possible pairs of bitwise XORs are nums1[0] ^ nums2[0], nums1[0] ^ nums2[1], nums1[1] ^ nums2[0],
 * and nums1[1] ^ nums2[1].
 * Thus, one possible nums3 array is [2,5,1,6].
 * 2 ^ 5 ^ 1 ^ 6 = 0, so we return 0.
 *
 * Constraints:
 * 1 <= nums1.length, nums2.length <= 10^5
 * 0 <= nums1[i], nums2[j] <= 10^9
 */

// Approach 1: Use a hashmap to track frequencies of numbers, XOR only numbers with odd frequencies since even occurrences cancel out in XOR operations.
// TC: O(n + m) where n and m are lengths of nums1 and nums2 respectively.
// SC: O(n + m) for storing numbers in hashmap in worst case.
class Solution {
public:
   int xorAllNums(vector<int>& nums1, vector<int>& nums2){
      // Get the sizes of both input arrays
      int m = nums1.size();
      int n = nums2.size();

      // Map to store frequency of each number
      // Each number from nums1 will appear n times (paired with every number in nums2)
      // Each number from nums2 will appear m times (paired with every number in nums1)
      unordered_map<int, long> mp;

      // Count frequencies for nums1 elements
      for (int&num : nums1) {
         mp[num] += n;     // Each number appears n times
      }

      // Count frequencies for nums2 elements
      for (int&num : nums2) {
         mp[num] += m;     // Each number appears m times
      }

      // Final result to store XOR
      int result = 0;

      // For each number in the map
      for (auto&it : mp) {
         int num  = it.first;
         int freq = it.second;

         // If frequency is odd, include in XOR
         // (even occurrences cancel out in XOR)
         if (freq % 2 != 0) {
            result ^= num;
         }
      }
      return result;
   }
};

// Approach 2: Each element appears m*n times, we only need elements that appear odd times since even occurrences cancel out in XOR.
// TC: O(n + m) where n and m are lengths of input arrays.
// SC: O(1) as we only use constant extra space.
class Solution {
public:
   int xorAllNums(vector<int>& nums1, vector<int>& nums2){
      // Get sizes of input arrays
      int m = nums1.size();
      int n = nums2.size();

      int XOR = 0;

      // If size of nums2 is odd, each element in nums1 will appear odd number of times
      // So include all nums1 elements in XOR
      if (n % 2 != 0) {
         for (int&num : nums1) {
            XOR ^= num;
         }
      }

      // If size of nums1 is odd, each element in nums2 will appear odd number of times
      // So include all nums2 elements in XOR
      if (m % 2 != 0) {
         for (int&num : nums2) {
            XOR ^= num;
         }
      }

      return XOR;
   }
};
