/*
 * 2460. Apply Operations to an Array
 *
 * You are given a 0-indexed array nums of size n consisting of non-negative integers.
 * You need to apply n - 1 operations to this array where, in the ith operation (0-indexed), you will apply the following on the ith element of nums:
 * If nums[i] == nums[i + 1], then multiply nums[i] by 2 and set nums[i + 1] to 0. Otherwise, you skip this operation.
 * After performing all the operations, shift all the 0's to the end of the array.
 * For example, the array [1,0,2,0,0,1] after shifting all its 0's to the end, is [1,2,1,0,0,0].
 * Return the resulting array.
 * Note that the operations are applied sequentially, not all at once.
 *
 * Example 1:
 * Input: nums = [1,2,2,1,1,0]
 * Output: [1,4,2,0,0,0]
 * Explanation: We do the following operations:
 * - i = 0: nums[0] and nums[1] are not equal, so we skip this operation.
 * - i = 1: nums[1] and nums[2] are equal, we multiply nums[1] by 2 and change nums[2] to 0. The array becomes [1,4,0,1,1,0].
 * - i = 2: nums[2] and nums[3] are not equal, so we skip this operation.
 * - i = 3: nums[3] and nums[4] are equal, we multiply nums[3] by 2 and change nums[4] to 0. The array becomes [1,4,0,2,0,0].
 * - i = 4: nums[4] and nums[5] are equal, we multiply nums[4] by 2 and change nums[5] to 0. The array becomes [1,4,0,2,0,0].
 * After that, we shift the 0's to the end, which gives the array [1,4,2,0,0,0].
 *
 * Example 2:
 * Input: nums = [0,1]
 * Output: [1,0]
 * Explanation: No operation can be applied, we just shift the 0 to the end.
 *
 * Constraints:
 * 2 <= nums.length <= 2000
 * 0 <= nums[i] <= 1000
 */

// Approach 1 (Using Extra Space): Iterate through the array once to combine adjacent equal elements (doubling the left element and setting the right element to zero), then iterate again to collect non-zero elements into a new array while shifting all zeros to the end.
// TC: O(n) - We traverse the array twice, each in linear time.
// SC: O(n) - An extra array of the same size is used to store the result.
class Solution {
public:
   vector<int> applyOperations(vector<int>& nums) {
      int n = nums.size();

      // Step 1: Apply the doubling and set adjacent element to zero if equal
      for (int i = 0; i < n - 1; i++) {
         if (nums[i] == nums[i + 1]) {
            nums[i]    *= 2;
            nums[i + 1] = 0;
         }
      }

      // Step 2: Shift all non-zero numbers to the left by creating a new result vector initialized with zeros
      vector<int> result(n, 0);
      int         index = 0; // Index for placing the non-zero elements

      // Collect non-zero elements from nums into result
      for (int i = 0; i < n; i++) {
         if (nums[i] != 0) {
            result[index++] = nums[i];
         }
      }

      // Return the resulting vector with zeros shifted to the end
      return result;
   }
};

/*
 * Dry Run:
 * Example: nums = [1, 2, 2, 1, 1, 0]
 *
 * Step 1: Combine adjacent equal numbers
 * i = 0: Compare 1 and 2 -> not equal, no change.
 * i = 1: Compare 2 and 2 -> equal, update: nums[1] becomes 4, nums[2] becomes 0.
 *      Array now: [1, 4, 0, 1, 1, 0]
 * i = 2: Compare 0 and 1 -> not equal, no change.
 * i = 3: Compare 1 and 1 -> equal, update: nums[3] becomes 2, nums[4] becomes 0.
 *      Array now: [1, 4, 0, 2, 0, 0]
 * i = 4: Compare 0 and 0 -> equal, update: nums[4] becomes 0, nums[5] becomes 0.
 *      Array remains: [1, 4, 0, 2, 0, 0]
 *
 * Step 2: Shift non-zero elements to the left
 * Traverse the array and pick non-zero elements: [1, 4, 2]
 * Fill the remaining positions with zeros to form: [1, 4, 2, 0, 0, 0]
 * End Dry Run
 */

// Approach 2 (Two Pass): Iterate through the array once to combine adjacent equal non-zero elements (doubling the left element and setting the right element to zero), then shift non-zero elements in-place by overwriting the array.
// TC: O(n) - We traverse the array twice, each in linear time.
// SC: O(1) - In-place modifications are performed without using extra space (ignoring input modifications).
class Solution {
public:
   vector<int> applyOperations(vector<int>& nums) {
      int n = nums.size();

      // Step 1: Apply the doubling and set adjacent element to zero if equal and non-zero
      for (int i = 0; i < n - 1; i++) {
         if (nums[i] == nums[i + 1] && nums[i] != 0) {
            nums[i]    *= 2;
            nums[i + 1] = 0;
         }
      }

      // Step 2: Shift all non-zero numbers to the left in-place
      int j = 0;
      for (int i = 0; i < n; i++) {
         if (nums[i] != 0) {
            nums[j] = nums[i];
            j++;
         }
      }

      // Fill remaining positions with zeros
      while (j < n) {
         nums[j] = 0;
         j++;
      }

      return nums;
   }
};

/*
 * Dry Run:
 * Example: nums = [1, 2, 2, 1, 1, 0]
 *
 * Step 1: Combine adjacent equal non-zero numbers
 * i = 0: Compare 1 and 2 -> not equal, no change.
 * i = 1: Compare 2 and 2 -> equal and non-zero, update: nums[1] becomes 4, nums[2] becomes 0.
 *      Array now: [1, 4, 0, 1, 1, 0]
 * i = 2: Compare 0 and 1 -> not equal, no change.
 * i = 3: Compare 1 and 1 -> equal and non-zero, update: nums[3] becomes 2, nums[4] becomes 0.
 *      Array now: [1, 4, 0, 2, 0, 0]
 * i = 4: Compare 0 and 0 -> although equal, condition fails because nums[i] is 0, no change.
 *
 * Step 2: Shift non-zero elements to the left in-place
 * Traverse the array and place non-zero elements at the beginning:
 * i = 0: nums[0] = 1 (non-zero) -> place 1 at index 0, j becomes 1.
 * i = 1: nums[1] = 4 (non-zero) -> place 4 at index 1, j becomes 2.
 * i = 2: nums[2] = 0 -> skip.
 * i = 3: nums[3] = 2 (non-zero) -> place 2 at index 2, j becomes 3.
 * i = 4: nums[4] = 0 -> skip.
 * i = 5: nums[5] = 0 -> skip.
 * Fill the rest with zeros from index 3 to 5:
 * Final array: [1, 4, 2, 0, 0, 0]
 * End Dry Run
 */

// Approach 3 (One Pass): Iterate through the array once, performing doubling and zeroing while swapping non-zero elements to the front.
// TC: O(n) - We traverse the array once with constant-time operations per element.
// SC: O(1) - All operations are performed in-place without extra space.
class Solution {
public:
   vector<int> applyOperations(vector<int>& nums) {
      int n = nums.size();

      int j = 0;      // Pointer for the next position to place a non-zero element

      for (int i = 0; i < n; i++) {
         // If next element exists and is equal to the current element (and non-zero), double current and set next to zero
         if (i + 1 < n && nums[i] == nums[i + 1] && nums[i] != 0) {
            nums[i]    *= 2;
            nums[i + 1] = 0;
         }

         // If the current element is non-zero, swap it with element at index j if not already in position, then increment j
         if (nums[i] != 0) {
            if (i != j) {
               swap(nums[i], nums[j]);
            }
            j++;
         }
      }

      return nums;
   }
};

/*
 * Dry Run:
 * Example: nums = [1, 2, 2, 1, 1, 0]
 *
 * i = 0:
 *   - Check: i+1 < n is true, compare 1 and 2 -> not equal, so no doubling.
 *   - nums[0] is non-zero; since i (0) equals j (0), no swap; increment j to 1.
 *   - Array remains: [1, 2, 2, 1, 1, 0]
 *
 * i = 1:
 *   - Check: i+1 < n is true, compare 2 and 2 -> equal and non-zero, so double nums[1] to 4 and set nums[2] to 0.
 *   - Array becomes: [1, 4, 0, 1, 1, 0]
 *   - nums[1] is non-zero; i (1) equals j (1), no swap; increment j to 2.
 *
 * i = 2:
 *   - Check: i+1 < n is true, compare 0 and 1 -> not equal, so no doubling.
 *   - nums[2] is 0, so nothing happens; j remains 2.
 *
 * i = 3:
 *   - Check: i+1 < n is true, compare 1 and 1 -> equal and non-zero, so double nums[3] to 2 and set nums[4] to 0.
 *   - Array becomes: [1, 4, 0, 2, 0, 0]
 *   - nums[3] is non-zero; i (3) is not equal to j (2), swap nums[3] with nums[2].
 *   - Array becomes: [1, 4, 2, 0, 0, 0]; increment j to 3.
 *
 * i = 4:
 *   - Check: i+1 < n is true, compare 0 and 0 -> equal but condition fails because nums[i] is 0.
 *   - nums[4] is 0, so nothing happens; j remains 3.
 *
 * i = 5:
 *   - i+1 is out of bounds.
 *   - nums[5] is 0, so nothing happens.
 *
 * Final array: [1, 4, 2, 0, 0, 0]
 */
