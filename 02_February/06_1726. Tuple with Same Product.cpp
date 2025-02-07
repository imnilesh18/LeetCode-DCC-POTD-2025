/*
 * 1726. Tuple with Same Product
 *
 * Given an array nums of distinct positive integers, return the number of tuples (a, b, c, d) such that a * b = c * d where a, b, c, and d are elements of nums, and a != b != c != d.
 *
 * Example 1:
 * Input: nums = [2,3,4,6]
 * Output: 8
 * Explanation: There are 8 valid tuples:
 * (2,6,3,4) , (2,6,4,3) , (6,2,3,4) , (6,2,4,3)
 * (3,4,2,6) , (4,3,2,6) , (3,4,6,2) , (4,3,6,2)
 *
 * Example 2:
 * Input: nums = [1,2,4,5,10]
 * Output: 16
 * Explanation: There are 16 valid tuples:
 * (1,10,2,5) , (1,10,5,2) , (10,1,2,5) , (10,1,5,2)
 * (2,5,1,10) , (2,5,10,1) , (5,2,1,10) , (5,2,10,1)
 * (2,10,4,5) , (2,10,5,4) , (10,2,4,5) , (10,2,5,4)
 * (4,5,2,10) , (4,5,10,2) , (5,4,2,10) , (5,4,10,2)
 *
 * Constraints:
 * 1 <= nums.length <= 1000
 * 1 <= nums[i] <= 104
 * All elements in nums are distinct.
 */

// Approach (Optimal): Use a hash map to count the frequency of each product obtained by multiplying every unique pair in the array.
//           For each product with frequency 'freq', the number of valid pairs is (freq choose 2) = (freq * (freq - 1)) / 2.
//           Multiply the result by 8 because each pair of pairs can form 8 different valid tuples.
// Time Complexity: O(n^2) - We traverse all unique pairs of the array.
// Space Complexity: O(n^2) - In the worst case, all pairs have unique products and are stored in the map.
class Solution {
public:
   int tupleSameProduct(vector<int>& nums) {
      int n      = nums.size();
      int tuples = 0;        // This will store the count of valid tuple pairs before multiplying by 8

      // Hash map to store the frequency of each product obtained from any two numbers in nums.
      unordered_map<int, int> mp;

      // Loop through each unique pair of elements in nums
      for (int i = 0; i < n; i++) {
         for (int j = i + 1; j < n; j++) {
            int p = nums[i] * nums[j]; // Calculate the product of the current pair
            mp[p]++;                   // Increment the count for this product in the map
         }
      }

      // Iterate through each product in the map to calculate the number of valid tuples
      for (auto&it : mp) {
         int freq = it.second;         // Frequency of the current product
         // For each product, the number of ways to choose two pairs is given by combination formula (freq choose 2)
         tuples += (freq * (freq - 1)) / 2;
      }

      // Each valid pair of pairs can form 8 distinct tuples, so multiply by 8 before returning.
      return tuples * 8;
   }
};

/*
 * Dry Run:
 * Example: nums = [2,3,4,6]
 *   - i = 0, j = 1: p = 2*3 = 6   -> map[6] becomes 1.
 *   - i = 0, j = 2: p = 2*4 = 8   -> map[8] becomes 1.
 *   - i = 0, j = 3: p = 2*6 = 12  -> map[12] becomes 1.
 *   - i = 1, j = 2: p = 3*4 = 12  -> map[12] becomes 2.
 *   - i = 1, j = 3: p = 3*6 = 18  -> map[18] becomes 1.
 *   - i = 2, j = 3: p = 4*6 = 24  -> map[24] becomes 1.
 *
 *   Map after processing pairs: {6: 1, 8: 1, 12: 2, 18: 1, 24: 1}
 *   Only product 12 has more than one occurrence (freq = 2).
 *   Number of valid pairs for product 12 = (2 * (2 - 1)) / 2 = 1.
 *   Total tuples = 1 * 8 = 8.
 */
