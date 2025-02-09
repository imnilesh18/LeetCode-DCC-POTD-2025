/*
 * 2364. Count Number of Bad Pairs
 *
 * You are given a 0-indexed integer array nums. A pair of indices (i, j) is a bad pair if i < j and j - i != nums[j] - nums[i].
 * Return the total number of bad pairs in nums.
 *
 * Example 1:
 * Input: nums = [4,1,3,3]
 * Output: 5
 * Explanation: The pair (0, 1) is a bad pair since 1 - 0 != 1 - 4.
 * The pair (0, 2) is a bad pair since 2 - 0 != 3 - 4, 2 != -1.
 * The pair (0, 3) is a bad pair since 3 - 0 != 3 - 4, 3 != -1.
 * The pair (1, 2) is a bad pair since 2 - 1 != 3 - 1, 1 != 2.
 * The pair (2, 3) is a bad pair since 3 - 2 != 3 - 3, 1 != 0.
 * There are a total of 5 bad pairs, so we return 5.
 *
 * Example 2:
 * Input: nums = [1,2,3,4,5]
 * Output: 0
 * Explanation: There are no bad pairs.
 *
 * Constraints:
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^9
 */

// Approach 1: Transform nums by subtracting the index and use a frequency map to count good pairs, then derive bad pairs.
// TC: O(n) since we iterate through the array once.
// SC: O(n) due to the frequency map.
class Solution {
public:
   long long countBadPairs(vector<int>& nums) {
      int       n      = nums.size();
      long long result = 0;    // Variable to store the total number of bad pairs

      // Transform each element by subtracting its index.
      // This makes it easier to count "good pairs" where (j - i) equals (nums[j] - nums[i]).
      for (int i = 0; i < n; i++) {
         nums[i] = nums[i] - i;
      }

      unordered_map<int, int> mp; // Map to store the frequency of each transformed value
      mp[nums[0]] = 1;            // Initialize the map with the first element

      // Iterate through the array starting from the second element.
      for (int j = 1; j < n; j++) {
         // The frequency of nums[j] in the map represents the number of "good pairs" seen so far.
         int countOfNumsj = mp[nums[j]];

         // Total pairs with indices less than j is j.
         // Subtracting the good pairs gives the count of bad pairs for this index.
         int totalNumsBeforej = j;
         int badPairs         = totalNumsBeforej - countOfNumsj;

         result += badPairs; // Accumulate the bad pairs count
         mp[nums[j]]++;      // Update the frequency of the current transformed value
      }
      return result;         // Return the total number of bad pairs
   }
};

/*
 * Dry Run:
 * For nums = [4, 1, 3, 3]:
 * After transformation: nums becomes [4, 0, 1, 0] because:
 *   index 0: 4 - 0 = 4
 *   index 1: 1 - 1 = 0
 *   index 2: 3 - 2 = 1
 *   index 3: 3 - 3 = 0
 * Map processing:
 *   Start with mp = {4:1}
 *   For index 1 (value 0): count = 0, bad pairs = 1 - 0 = 1, update mp to {4:1, 0:1}
 *   For index 2 (value 1): count = 0, bad pairs = 2 - 0 = 2, update mp to {4:1, 0:1, 1:1}
 *   For index 3 (value 0): count = 1, bad pairs = 3 - 1 = 2, update mp to {4:1, 0:2, 1:1}
 * Total bad pairs = 1 + 2 + 2 = 5.
 */

// Approach 2: Use a frequency map to track (nums[j]-j) occurrences to count good pairs and subtract from total pairs.
// TC: O(n) - Iterate through the array once.
// SC: O(n) - In the worst-case, the frequency map stores n unique differences.
class Solution {
public:
   long long countBadPairs(vector<int>& nums) {
      int       n      = nums.size(); // Get the number of elements in the array
      long long result = 0;           // Initialize the result to store the total count of bad pairs
      unordered_map<int, int> mp;     // Map to store the frequency of (nums[j] - j)

      // Iterate through each element in the array
      for (int j = 0; j < n; j++) {
         int diff             = nums[j] - j;     // Calculate the difference between the element and its index
         int goodPairs        = mp[diff];        // Number of good pairs found so far with the same diff
         int totalPairsInPast = j;               // Total number of pairs with indices less than j

         result += totalPairsInPast - goodPairs; // Bad pairs = total pairs so far - good pairs
         mp[diff]++;                             // Increment the frequency for the current diff
      }
      return result;                             // Return the total count of bad pairs
   }
};

/*
 * Dry Run:
 * For nums = [4, 1, 3, 3]:
 * j = 0: diff = 4 - 0 = 4, goodPairs = 0, totalPairsInPast = 0, result = 0; mp becomes {4: 1}
 * j = 1: diff = 1 - 1 = 0, goodPairs = 0, totalPairsInPast = 1, result = 1; mp becomes {4: 1, 0: 1}
 * j = 2: diff = 3 - 2 = 1, goodPairs = 0, totalPairsInPast = 2, result = 3; mp becomes {4: 1, 0: 1, 1: 1}
 * j = 3: diff = 3 - 3 = 0, goodPairs = 1, totalPairsInPast = 3, result = 5; mp becomes {4: 1, 0: 2, 1: 1}
 * Total bad pairs = 5.
 */
