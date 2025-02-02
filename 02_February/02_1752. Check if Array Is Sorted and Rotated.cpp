/*
 * 1752. Check if Array Is Sorted and Rotated
 *
 * Given an array nums, return true if the array was originally sorted in non-decreasing order, then rotated some number of positions (including zero). Otherwise, return false.
 * There may be duplicates in the original array.
 * Note: An array A rotated by x positions results in an array B of the same length such that A[i] == B[(i+x) % A.length], where % is the modulo operation.
 *
 * Example 1:
 * Input: nums = [3,4,5,1,2]
 * Output: true
 * Explanation: [1,2,3,4,5] is the original sorted array.
 * You can rotate the array by x = 3 positions to begin on the the element of value 3: [3,4,5,1,2].
 *
 * Example 2:
 * Input: nums = [2,1,3,4]
 * Output: false
 * Explanation: There is no sorted array once rotated that can make nums.
 *
 * Example 3:
 * Input: nums = [1,2,3]
 * Output: true
 * Explanation: [1,2,3] is the original sorted array.
 * You can rotate the array by x = 0 positions (i.e. no rotation) to make nums.
 *
 * Constraints:
 * 1 <= nums.length <= 100
 * 1 <= nums[i] <= 100
 */


// Approach 1: Brue Force

/*
 * Given an array nums, the task is to check if the array was originally sorted in
 * non-decreasing order and then rotated some number of positions (including zero).
 *
 * Approach 1: Brue Force
 * For each possible rotation index r (from 0 to n-1), construct a rotated array
 * by concatenating the subarray nums[r...n-1] with nums[0...r-1]. Then check if
 * this constructed array is sorted in non-decreasing order.
 *
 * Time Complexity (TC): O(n^2) - For each of the n possible rotations, we traverse
 * the array (n elements) to check if it's sorted.
 *
 * Space Complexity (SC): O(n) - We use an extra vector of size n to construct the rotated array.
 */
class Solution {
public:
   bool check(vector<int>& nums) {
      int         n = nums.size();
      vector<int> sorted(n);    // temporary vector to store the rotated version

      // Try each possible rotation index r (including 0 which is no rotation)
      for (int r = 0; r < n; r++) {
         int idx = 0;

         // Append the segment from index r to the end of the array
         for (int i = r; i < n; i++) {
            sorted[idx] = nums[i];
            idx++;
         }

         // Append the segment from index 0 to r-1 (wrap-around)
         for (int i = 0; i < r; i++) {
            sorted[idx] = nums[i];
            idx++;
         }

         // Check if the constructed rotated array is sorted in non-decreasing order
         bool isSorted = true;
         for (int i = 0; i < n - 1; i++) {
            if (sorted[i] > sorted[i + 1]) {     // if any adjacent pair is in descending order
               isSorted = false;
               break;
            }
         }

         // If we found a rotation that makes the array sorted, return true
         if (isSorted) {
            return true;
         }
      }

      // If no rotation results in a sorted array, return false
      return false;
   }
};

/*
 * Dry Run Example: nums = [3,4,5,1,2]
 *
 * Iteration 1: r = 0
 *  - Rotated array 'sorted': [3, 4, 5, 1, 2]
 *  - Check: 3 <= 4 (true), 4 <= 5 (true), 5 <= 1 (false) --> Not sorted
 *
 * Iteration 2: r = 1
 *  - Rotated array 'sorted': [4, 5, 1, 2, 3]
 *  - Check: 4 <= 5 (true), 5 <= 1 (false) --> Not sorted
 *
 * Iteration 3: r = 2
 *  - Rotated array 'sorted': [5, 1, 2, 3, 4]
 *  - Check: 5 <= 1 (false) --> Not sorted
 *
 * Iteration 4: r = 3
 *  - Rotated array 'sorted': [1, 2, 3, 4, 5]
 *  - Check: 1 <= 2 (true), 2 <= 3 (true), 3 <= 4 (true), 4 <= 5 (true) --> Sorted!
 *  - Return true since the array is sorted after this rotation.
 */


// Approach 2: Better Brute Force

/*
 * Given an array nums, the goal is to determine if nums can be obtained by rotating
 * a sorted (non-decreasing) version of itself.
 *
 * Approach 2: Better Brute Force
 * 1. Create a sorted copy of nums, which represents the original sorted order.
 * 2. For every possible rotation (from 0 to n-1), check if rotating nums by that
 *    amount yields the sorted array.
 * 3. If a match is found for any rotation, return true; otherwise, return false.
 *
 * Time Complexity (TC): O(n^2) - For each of the n rotations, we perform an O(n)
 * comparison.
 *
 * Space Complexity (SC): O(n) - A copy of the array is stored and sorted.
 */

class Solution {
public:
   bool check(vector<int>& nums) {
      int n = nums.size();
      // Create a sorted copy of the input array
      vector<int> sorted = nums;

      sort(begin(sorted), end(sorted));    // sorted now holds the array in non-decreasing order

      // Try each possible rotation offset 'r'
      for (int r = 0; r < n; r++) {
         bool isSorted = true;
         // Check if rotating nums by 'r' positions results in the sorted array
         for (int i = 0; i < n; i++) {
            // (i + r) % n simulates rotation with wrap-around.
            if (sorted[i] != nums[(i + r) % n]) {
               isSorted = false;
               break;
            }
         }

         // If the rotated array matches the sorted array, return true.
         if (isSorted) {
            return true;
         }
      }
      // If no rotation results in the sorted array, return false.
      return false;
   }
};

/*
 * Dry Run Example: nums = [3,4,5,1,2]
 *
 * 1. After sorting:
 * sorted = [1,2,3,4,5]
 *
 * 2. Rotation checks:
 * - For r = 0:
 *   Compare sorted[0] (1) with nums[(0+0)%5] (nums[0] = 3) -> mismatch.
 *
 * - For r = 1:
 *   Compare sorted[0] (1) with nums[(0+1)%5] (nums[1] = 4) -> mismatch.
 *
 * - For r = 2:
 *   Compare sorted[0] (1) with nums[(0+2)%5] (nums[2] = 5) -> mismatch.
 *
 * - For r = 3:
 *   Compare sorted[0] (1) with nums[(0+3)%5] (nums[3] = 1) -> match.
 *   Compare sorted[1] (2) with nums[(1+3)%5] (nums[4] = 2) -> match.
 *   Compare sorted[2] (3) with nums[(2+3)%5] (nums[0] = 3) -> match.
 *   Compare sorted[3] (4) with nums[(3+3)%5] (nums[1] = 4) -> match.
 *   Compare sorted[4] (5) with nums[(4+3)%5] (nums[2] = 5) -> match.
 *   All elements match, so the rotated array is sorted.
 *
 * 3. Since a valid rotation was found, the function returns true.
 */

// Approach 3: Optimal

/*
 * Given an array nums, the goal is to determine if it can be obtained by rotating
 * a sorted (non-decreasing) array. The idea is to count the number of times the
 * order "resets" (i.e., when a number is greater than the next number, considering
 * the array circularly). If there is more than one such "peak" or "drop", then it
 * is not a rotation of a sorted array.
 *
 * Approach 3: Optimal
 * Traverse the array and count the number of positions where nums[i] > nums[(i + 1) % n].
 * For a valid rotated sorted array, this count must be at most 1.
 *
 * Time Complexity (TC): O(n) - We make a single pass through the array.
 * Space Complexity (SC): O(1) - Only a few extra variables are used.
 */

class Solution {
public:
   bool check(vector<int>& nums) {
      int n = nums.size();

      int peak = 0;   // Counts the number of times the order "resets" (nums[i] > nums[i+1])

      for (int i = 0; i < n; i++) {
         // Compare current element with the next element, using modulo for circular comparison
         if (nums[i] > nums[(i + 1) % n]) {
            peak++;
         }
      }

      // If there is more than one drop, the array is not a rotation of a sorted array.
      return peak <= 1;
   }
};

/*
 * Dry Run Example: nums = [3, 4, 5, 1, 2]
 *
 * Iteration details:
 * - i = 0: Compare nums[0] = 3 with nums[1] = 4 -> 3 <= 4, no peak.
 * - i = 1: Compare nums[1] = 4 with nums[2] = 5 -> 4 <= 5, no peak.
 * - i = 2: Compare nums[2] = 5 with nums[3] = 1 -> 5 > 1, peak count becomes 1.
 * - i = 3: Compare nums[3] = 1 with nums[4] = 2 -> 1 <= 2, no peak.
 * - i = 4: Compare nums[4] = 2 with nums[(4+1)%5] = nums[0] = 3 -> 2 <= 3, no peak.
 *
 * Final peak count = 1, which is <= 1, so the function returns true.
 */
