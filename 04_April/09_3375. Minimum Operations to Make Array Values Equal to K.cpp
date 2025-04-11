/*
 * 3375. Minimum Operations to Make Array Values Equal to K
 *
 * Easy
 *
 * You are given an integer array nums and an integer k.
 * An integer h is called valid if all values in the array that are strictly greater than h are identical.
 * For example, if nums = [10, 8, 10, 8], a valid integer is h = 9 because all nums[i] > 9 are equal to 10, but 5 is not a valid integer.
 * You are allowed to perform the following operation on nums:
 * Select an integer h that is valid for the current values in nums.
 * For each index i where nums[i] > h, set nums[i] to h.
 * Return the minimum number of operations required to make every element in nums equal to k. If it is impossible to make all elements equal to k, return -1.
 *
 * Example 1:
 * Input: nums = [5,2,5,4,5], k = 2
 * Output: 2
 * Explanation:
 * The operations can be performed in order using valid integers 4 and then 2.
 *
 * Example 2:
 * Input: nums = [2,1,2], k = 2
 * Output: -1
 * Explanation:
 * It is impossible to make all the values equal to 2.
 *
 * Example 3:
 * Input: nums = [9,7,5,3], k = 1
 * Output: 4
 * Explanation:
 * The operations can be performed using valid integers in the order 7, 5, 3, and 1.
 *
 * Constraints:
 * 1 <= nums.length <= 100
 * 1 <= nums[i] <= 100
 * 1 <= k <= 100
 */

// Approach: For each number in the array, check if it is less than k (impossible to reduce to k) or greater than k;
// then count the unique numbers greater than k using a set, because each unique value greater than k represents one needed operation.
// Time Complexity: O(n) since we traverse the array once.
// Space Complexity: O(n) for storing distinct numbers in the set.
class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        unordered_set<int> st;      // Set to store unique numbers greater than k

        // Traverse each number in nums
        for (int& num : nums) {
            // If any element is less than k, it's impossible to convert to k, so return -1
            if (num < k) {
                return -1;
            }
            // If the element is strictly greater than k, add it to the set
            else if (num > k) {
                st.insert(num);
            }
            // If the element is equal to k, no operation is needed; simply skip it.
        }

        // The size of the set represents the minimum number of operations required.
        return st.size();
    }
};

/*
 *
 * Dry Run 1
 *
 * Example: nums = [5, 2, 5, 4, 5], k = 2
 *
 *   Visual Representation of Array:
 *         Indices:   0   1   2   3   4
 *                  +---+---+---+---+---+
 *         Array:    | 5 | 2 | 5 | 4 | 5 |
 *                  +---+---+---+---+---+
 *
 * Iteration Details:
 *  Iteration 1 (i = 0):
 *       Element = 5.
 *       5 is greater than 2.
 *       Set before insertion: {}
 *              Visual set:
 *              +-----+
 *              |     |
 *              +-----+
 *       Insert 5.
 *       Set after insertion: {5}
 *              Visual set:
 *              +-----+
 *              |  5  |
 *              +-----+
 *
 *  Iteration 2 (i = 1):
 *       Element = 2.
 *       2 is equal to k, so no operation is needed.
 *       Set remains: {5}
 *
 *  Iteration 3 (i = 2):
 *       Element = 5.
 *       5 is equal to the existing element in the set.
 *       Set remains: {5}
 *
 *  Iteration 4 (i = 3):
 *       Element = 4.
 *       4 is greater than 2.
 *       Set before insertion: {5}
 *              Visual set:
 *              +-----+
 *              |  5  |
 *              +-----+
 *       4 is not in the set. Insert 4.
 *       Set after insertion: {5, 4}
 *              Visual set:
 *              +-----+-----+
 *              |  5  |  4  |
 *              +-----+-----+
 *
 *  Iteration 5 (i = 4):
 *       Element = 5.
 *       5 is already in the set.
 *       Set remains: {5, 4}
 *
 * Final unique numbers greater than k: {5, 4} → Total operations = 2.
 *
 *--------------------------------------------------
 *
 * Dry Run 2
 *
 * Example: nums = [2, 1, 2], k = 2
 *
 *   Visual Representation of Array:
 *         Indices:   0   1   2
 *                  +---+---+---+
 *         Array:    | 2 | 1 | 2 |
 *                  +---+---+---+
 *
 * Iteration Details:
 *  Iteration 1 (i = 0):
 *       Element = 2.
 *       2 is equal to k, so skip.
 *       Set remains: {}
 *
 *  Iteration 2 (i = 1):
 *       Element = 1.
 *       1 is less than k (2), which makes it impossible to convert to 2.
 *       Immediately return -1.
 *
 * Final Result: -1 (impossible to convert all elements to k)
 *
 *--------------------------------------------------
 *
 * Dry Run 3
 *
 * Example: nums = [9, 7, 5, 3], k = 1
 *
 *   Visual Representation of Array:
 *         Indices:   0   1   2   3
 *                  +---+---+---+---+
 *         Array:    | 9 | 7 | 5 | 3 |
 *                  +---+---+---+---+
 *
 * Iteration Details:
 *  Iteration 1 (i = 0):
 *       Element = 9.
 *       9 is greater than 1.
 *       Set before insertion: {}
 *              Visual set:
 *              +-----+
 *              |     |
 *              +-----+
 *       Insert 9.
 *       Set after insertion: {9}
 *              Visual set:
 *              +-----+
 *              |  9  |
 *              +-----+
 *
 *  Iteration 2 (i = 1):
 *       Element = 7.
 *       7 is greater than 1.
 *       Set before insertion: {9}
 *              Visual set:
 *              +-----+
 *              |  9  |
 *              +-----+
 *       Insert 7.
 *       Set after insertion: {9, 7}
 *              Visual set:
 *              +-----+-----+
 *              |  9  |  7  |
 *              +-----+-----+
 *
 *  Iteration 3 (i = 2):
 *       Element = 5.
 *       5 is greater than 1.
 *       Set before insertion: {9, 7}
 *              Visual set:
 *              +-----+-----+
 *              |  9  |  7  |
 *              +-----+-----+
 *       Insert 5.
 *       Set after insertion: {9, 7, 5}
 *              Visual set:
 *              +-----+-----+-----+
 *              |  9  |  7  |  5  |
 *              +-----+-----+-----+
 *
 *  Iteration 4 (i = 3):
 *       Element = 3.
 *       3 is greater than 1.
 *       Set before insertion: {9, 7, 5}
 *              Visual set:
 *              +-----+-----+-----+
 *              |  9  |  7  |  5  |
 *              +-----+-----+-----+
 *       Insert 3.
 *       Set after insertion: {9, 7, 5, 3}
 *              Visual set:
 *              +-----+-----+-----+-----+
 *              |  9  |  7  |  5  |  3  |
 *              +-----+-----+-----+-----+
 *
 * Final unique numbers greater than k: {9, 7, 5, 3} → Total operations = 4.
 *
 * Reasoning:
 *   Only unique numbers that are greater than k are taken into account because reducing any number to k
 *   in one valid operation will set all numbers higher than a chosen valid h (where h is made equal to k eventually)
 *   to k in each distinct step. Therefore, each unique number above k requires a separate operation.
 */
