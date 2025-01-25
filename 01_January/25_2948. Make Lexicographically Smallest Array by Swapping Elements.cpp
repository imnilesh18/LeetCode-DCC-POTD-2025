/*
 * 2948. Make Lexicographically Smallest Array by Swapping Elements
 *
 * You are given a 0-indexed array of positive integers nums and a positive integer limit.
 * In one operation, you can choose any two indices i and j and swap nums[i] and nums[j] if |nums[i] - nums[j]| <= limit.
 * Return the lexicographically smallest array that can be obtained by performing the operation any number of times.
 * An array a is lexicographically smaller than an array b if in the first position where a and b differ, array a has an element that is less than the corresponding element in b. For example, the array [2,10,3] is lexicographically smaller than the array [10,2,3] because they differ at index 0 and 2 < 10.
 *
 * Example 1:
 * Input: nums = [1,5,3,9,8], limit = 2
 * Output: [1,3,5,8,9]
 * Explanation: Apply the operation 2 times:
 * - Swap nums[1] with nums[2]. The array becomes [1,3,5,9,8]
 * - Swap nums[3] with nums[4]. The array becomes [1,3,5,8,9]
 * We cannot obtain a lexicographically smaller array by applying any more operations.
 * Note that it may be possible to get the same result by doing different operations.
 *
 * Example 2:
 * Input: nums = [1,7,6,18,2,1], limit = 3
 * Output: [1,6,7,18,1,2]
 * Explanation: Apply the operation 3 times:
 * - Swap nums[1] with nums[2]. The array becomes [1,6,7,18,2,1]
 * - Swap nums[0] with nums[4]. The array becomes [2,6,7,18,1,1]
 * - Swap nums[0] with nums[5]. The array becomes [1,6,7,18,1,2]
 * We cannot obtain a lexicographically smaller array by applying any more operations.
 *
 * Example 3:
 * Input: nums = [1,7,28,19,10], limit = 3
 * Output: [1,7,28,19,10]
 * Explanation: [1,7,28,19,10] is the lexicographically smallest array we can obtain because we cannot apply the operation on any two indices.
 *
 * Constraints:
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^9
 * 1 <= limit <= 10^9
 */

// Approach 1 (Brute Force): Greedy swapping with limit constraint (504 / 523 testcases passed)
// Time Complexity: O(n²)
// Space Complexity: O(1)
class Solution {
public:
   vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
      int n = nums.size();

      // For each element, try to swap with a smaller value within limit
      for (int i = 0; i < n; i++) {
         // Continuously attempt to find and swap with smallest possible value
         while (true) {
            int smallValue = nums[i];
            int idx        = -1;

            // Search for a swappable smaller value
            for (int j = i + 1; j < n; j++) {
               // Check if values are swappable based on limit
               if (abs(nums[i] - nums[j]) <= limit) {
                  // Update smallest value and its index if found
                  if (nums[j] < smallValue) {
                     smallValue = nums[j];
                     idx        = j;
                  }
               }
            }

            // If a smaller swappable value found, swap
            if (idx != -1) {
               swap(nums[i], nums[idx]);
            } else {
               break;
            }
         }
      }
      return nums;
   }
};

// Approach 2: Sort and group elements with limit-based connectivity
// Time Complexity: O(n log n)
// Space Complexity: O(n)
class Solution {
public:
   vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
      int         n   = nums.size();
      vector<int> vec = nums;

      // Sort the input array for grouping
      sort(begin(vec), end(vec));

      int groupNum = 0;
      // Map to track group number for each unique value
      unordered_map<int, int> numToGroup;
      numToGroup[vec[0]] = groupNum;

      // Map to store groups of swappable elements
      unordered_map<int, list<int> > groupToList;
      groupToList[groupNum].push_back(vec[0]);

      // Group elements based on limit constraint
      for (int i = 1; i < n; i++) {
         // Start new group if difference exceeds limit
         if (abs(vec[i] - vec[i - 1]) > limit) {
            groupNum += 1;
         }
         numToGroup[vec[i]] = groupNum;
         groupToList[groupNum].push_back(vec[i]);
      }

      // Rebuild array with lexicographically smallest arrangement
      vector<int> result(n);
      for (int i = 0; i < n; i++) {
         int num   = nums[i];
         int group = numToGroup[num];
         // Take smallest available number from the group
         result[i] = *groupToList[group].begin();
         // Remove used element from group
         groupToList[group].pop_front();
      }
      return result;
   }
};
