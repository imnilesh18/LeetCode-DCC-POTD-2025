/*
 * 3396. Minimum Number of Operations to Make Elements in Array Distinct
 *
 * Easy
 *
 * You are given an integer array nums. You need to ensure that the elements in the array are distinct. To achieve this, you can perform the following operation any number of times:
 * Remove 3 elements from the beginning of the array. If the array has fewer than 3 elements, remove all remaining elements.
 * Note that an empty array is considered to have distinct elements. Return the minimum number of operations needed to make the elements in the array distinct.
 *
 * Example 1:
 * Input: nums = [1,2,3,4,2,3,3,5,7]
 * Output: 2
 * Explanation:
 * In the first operation, the first 3 elements are removed, resulting in the array [4, 2, 3, 3, 5, 7].
 * In the second operation, the next 3 elements are removed, resulting in the array [3, 5, 7], which has distinct elements.
 * Therefore, the answer is 2.
 *
 * Example 2:
 * Input: nums = [4,5,6,4,4]
 * Output: 2
 * Explanation:
 * In the first operation, the first 3 elements are removed, resulting in the array [4, 4].
 * In the second operation, all remaining elements are removed, resulting in an empty array.
 * Therefore, the answer is 2.
 *
 * Example 3:
 * Input: nums = [6,7,8,9]
 * Output: 0
 * Explanation:
 * The array already contains distinct elements. Therefore, the answer is 0.
 *
 * Constraints:
 * 1 <= nums.length <= 100
 * 1 <= nums[i] <= 100
 */

// Approach 1 (Brute Force): For every operation, we remove the first 3 elements and check whether the remaining part of the array has all distinct elements by using an unordered_set.
// Time Complexity: O(n^2) in the worst-case, since for every step (with increment 3) we scan the remaining elements of the array.
// Space Complexity: O(n), as we use an unordered_set to store elements from the subarray.
class Solution {
public:
    int n;     // Global variable to store the size of the array

    // Function to check if all elements in the subarray from index 'start' to the end are distinct
    bool check(vector<int>& nums, int start) {
        unordered_set<int> st;     // Set to keep track of seen elements

        // Iterate from the start index to the end of the array
        for (int j = start; j < n; j++) {
            // If the element is already in the set, the subarray is not distinct
            if (st.count(nums[j])) {
                return false;   // Duplicate found, return false
            }
            st.insert(nums[j]); // Insert the element into the set
        }
        return true;            // All elements are distinct, return true
    }
    // Function to return the minimum number of operations required to make the array distinct
    int minimumOperations(vector<int>& nums) {
        n = nums.size();     // Store the size of the array in a global variable
        int ops = 0;         // Counter for the number of operations performed

        // Iterate in steps of 3 (simulate removing 3 elements in each operation)
        for (int i = 0; i < n; i += 3) {
            // If the subarray starting from index i is distinct, return the current number of operations
            if (check(nums, i) == true) {
                return ops;
            }
            ops++;     // Increment the operations count as we perform one removal operation
        }
        return ops;    // Return the total number of operations (covers the case when the array becomes empty)
    }
};

/*
 *
 * Dry Run
 *
 * Example: nums = [1, 2, 3, 4, 2, 3, 3, 5, 7]
 *
 *   Visual Representation of the original array:
 *         Indices:    0    1    2    3    4    5    6    7    8
 *                  +----+----+----+----+----+----+----+----+----+
 *         Array:    | 1  | 2  | 3  | 4  | 2  | 3  | 3  | 5  | 7  |
 *                  +----+----+----+----+----+----+----+----+----+
 *
 * Step 1:
 *---------
 * i = 0, ops = 0
 * Call check(nums, 0):
 *     - Initialize set: {}
 *     - j = 0 -> nums[0] = 1, set becomes {1}
 *           Visual for set:
 *           +-----+
 *           |  1  |
 *           +-----+
 *     - j = 1 -> nums[1] = 2, set becomes {1, 2}
 *           Visual for set:
 *           +-----+-----+
 *           |  1  |  2  |
 *           +-----+-----+
 *     - j = 2 -> nums[2] = 3, set becomes {1, 2, 3}
 *           Visual for set:
 *           +-----+-----+-----+
 *           |  1  |  2  |  3  |
 *           +-----+-----+-----+
 *     - j = 3 -> nums[3] = 4, set becomes {1, 2, 3, 4}
 *           Visual for set:
 *           +-----+-----+-----+-----+
 *           |  1  |  2  |  3  |  4  |
 *           +-----+-----+-----+-----+
 *     - j = 4 -> nums[4] = 2, duplicate detected (2 already in set).
 * Return false from check(nums, 0) as subarray [1,2,3,4,2,3,3,5,7] is not distinct.
 *
 * Step 2:
 *---------
 * Perform one operation (removing first 3 elements) -> i becomes 3, ops becomes 1.
 * Remaining array:
 *         Indices:    3    4    5    6    7    8
 *                  +----+----+----+----+----+----+
 *         Array:    | 4  | 2  | 3  | 3  | 5  | 7  |
 *                  +----+----+----+----+----+----+
 *
 * Call check(nums, 3):
 *     - Initialize set: {}
 *     - j = 3 -> nums[3] = 4, set becomes {4}
 *           Visual for set:
 *           +-----+
 *           |  4  |
 *           +-----+
 *     - j = 4 -> nums[4] = 2, set becomes {4, 2}
 *           Visual for set:
 *           +-----+-----+
 *           |  4  |  2  |
 *           +-----+-----+
 *     - j = 5 -> nums[5] = 3, set becomes {4, 2, 3}
 *           Visual for set:
 *           +-----+-----+-----+
 *           |  4  |  2  |  3  |
 *           +-----+-----+-----+
 *     - j = 6 -> nums[6] = 3, duplicate detected (3 already in set).
 * Return false from check(nums, 3) because subarray [4,2,3,3,5,7] is not distinct.
 *
 * Step 3:
 *---------
 * Perform second operation -> i becomes 6 (3 + 3), ops becomes 2.
 * Remaining array:
 *         Indices:    6    7    8
 *                  +----+----+----+
 *         Array:    | 3  | 5  | 7  |
 *                  +----+----+----+
 *
 * Call check(nums, 6):
 *     - Initialize set: {}
 *     - j = 6 -> nums[6] = 3, set becomes {3}
 *           Visual for set:
 *           +-----+
 *           |  3  |
 *           +-----+
 *     - j = 7 -> nums[7] = 5, set becomes {3, 5}
 *           Visual for set:
 *           +-----+-----+
 *           |  3  |  5  |
 *           +-----+-----+
 *     - j = 8 -> nums[8] = 7, set becomes {3, 5, 7}
 *           Visual for set:
 *           +-----+-----+-----+
 *           |  3  |  5  |  7  |
 *           +-----+-----+-----+
 *     No duplicates found, so check(nums, 6) returns true.
 *
 * Since check returns true at i = 6, the function returns ops = 2.
 *
 * Final Output: 2 (minimum operations required to make the array elements distinct)
 */

// Approach 2: Traverse the array in reverse, adding each element to an unordered_set until a duplicate is encountered; the first duplicate's index determines the minimum number of operations needed.
// Time Complexity: O(n) as we perform a single reverse traversal of the array.
// Space Complexity: O(n) for storing elements in the unordered_set.

/*
 * Explanation of the formula: ceil((i + 1) / 3.0)
 *
 * Here, i is the index where we detect the first duplicate during reverse traversal.
 * Since array indices start at 0, (i + 1) gives the total number of elements from the beginning
 * of the array up to and including index i.
 *
 * Dividing (i + 1) by 3.0 computes the number of groups of 3 elements that can be removed in a single operation,
 * because each operation removes 3 elements from the beginning of the array.
 *
 * If (i + 1) is not exactly divisible by 3, there will be a fractional part representing an incomplete group.
 * This incomplete group still requires a full operation to be removed, so we use the ceil function to round up.
 *
 * Example 1:
 *   Visual Representation:
 *         Indices:    0    1    2    3    4    5    6    7    8
 *                  +----+----+----+----+----+----+----+----+----+
 *         Array:    | 1  | 2  | 3  | 4  | 2  | 3  | 3  | 5  | 7  |
 *                  +----+----+----+----+----+----+----+----+----+
 *
 *   Suppose during the reverse traversal:
 *     - i = 8: Element = 7, add to set.
 *     - i = 7: Element = 5, add to set.
 *     - i = 6: Element = 3, add to set.
 *     - i = 5: Element = 3, duplicate found!
 *
 *   At i = 5, (i + 1) = 5 + 1 = 6.
 *   6 / 3.0 = 2.0 → This indicates exactly 2 groups (each of 3 elements), hence 2 removal operations.
 *
 * Example 2:
 *   Consider the array: {4, 5, 6, 4, 4}
 *         Indices:   0    1    2    3    4
 *                  +----+----+----+----+----+
 *         Array:    | 4  | 5  | 6  | 4  | 4  |
 *                  +----+----+----+----+----+
 *
 *   Reverse traversal steps:
 *     - i = 4: Element = 4, add to set.
 *     - i = 3: Element = 4, duplicate found!
 *
 *   At i = 3, (i + 1) = 3 + 1 = 4.
 *   4 / 3.0 ≈ 1.33, and ceil(1.33) = 2.
 *
 *   Observation:
 *     - Even though 4/3 suggests about 1.33 groups, this means there is one full group and a partial group.
 *     - The partial group (with only 1 or 2 elements) still requires a complete separate removal operation.
 *     - Thus, 2 operations are needed: one to remove the first group of 3 elements and another for the remaining group.
 *
 * Summary:
 *   ceil((i + 1) / 3.0) ensures that any leftover elements in a partial group are counted as a complete operation,
 *   thereby accurately calculating the minimum number of operations needed to remove all elements up to the duplicate.
 * *   Indices:   0   1   2   3   4
 *            +---+---+---+---+---+
 *   Array:    | 4 | 5 | 6 | 4 | 4 |
 *            +---+---+---+---+---+
 *
 * Reverse Traversal Process:
 *   - When i = 4: Element is 4, set becomes {4}.
 *   - When i = 3: Element is 4 again, so a duplicate is found.
 *
 * At that moment:
 *   (i + 1) = 3 + 1 = 4
 *   4 / 3.0 ≈ 1.33, and ceil(1.33) rounds it up to 2 operations.
 *
 * Explanation:
 *   Although dividing 4 by 3 suggests there is only one complete group plus a partial group,
 *   the partial group (even if it has just 1 or 2 elements) still requires a full separate operation.
 *   This corresponds to:
 *     - One operation removing the first group [4, 5, 6] (indices 0, 1, 2)
 *     - A second operation for the remaining group [4, 4] (indices 3, 4)
 *
 * Thus, ceil((i + 1) / 3.0) ensures that we always account for any remaining elements that must be cleared,
 * guaranteeing the correct count of operations to remove all elements up to the first duplicate.
 *
 *
 *   Indices:   0   1   2   3   4
 *            +---+---+---+---+---+
 *   Array:    | 4 | 5 | 6 | 4 | 4 |
 *            +---+---+---+---+---+
 *
 * Reverse Traversal Process:
 *   - When i = 4: Element is 4, set becomes {4}.
 *   - When i = 3: Element is 4 again, so a duplicate is found.
 *
 * At that moment:
 *   (i + 1) = 3 + 1 = 4
 *   4 / 3.0 ≈ 1.33, and ceil(1.33) rounds it up to 2 operations.
 *
 * Explanation:
 *   Although dividing 4 by 3 suggests there is only one complete group plus a partial group,
 *   the partial group (even if it has just 1 or 2 elements) still requires a full separate operation.
 *   This corresponds to:
 *     - One operation removing the first group [4, 5, 6] (indices 0, 1, 2)
 *     - A second operation for the remaining group [4, 4] (indices 3, 4)
 *
 * Thus, ceil((i + 1) / 3.0) ensures that we always account for any remaining elements that must be cleared,
 * guaranteeing the correct count of operations to remove all elements up to the first duplicate.
 *
 * -----------------------------------------------------------------------------------------------------
 *
 *   Indices:   0   1   2   3   4
 *            +---+---+---+---+---+
 *   Array:    | 4 | 5 | 6 | 4 | 4 |
 *            +---+---+---+---+---+
 *
 * Reverse Traversal Process:
 *   - When i = 4: Element is 4, set becomes {4}.
 *   - When i = 3: Element is 4 again, so a duplicate is found.
 *
 * At that moment:
 *   (i + 1) = 3 + 1 = 4
 *   4 / 3.0 ≈ 1.33, and ceil(1.33) rounds it up to 2 operations.
 *
 * Explanation:
 *   Although dividing 4 by 3 suggests there is only one complete group plus a partial group,
 *   the partial group (even if it has just 1 or 2 elements) still requires a full separate operation.
 *   This corresponds to:
 *     - One operation removing the first group [4, 5, 6] (indices 0, 1, 2)
 *     - A second operation for the remaining group [4, 4] (indices 3, 4)
 *
 * Thus, ceil((i + 1) / 3.0) ensures that we always account for any remaining elements that must be cleared,
 * guaranteeing the correct count of operations to remove all elements up to the first duplicate.
 */

class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int n = nums.size();     // Size of the input array
        unordered_set<int> st;   // Set to store unique elements during reverse traversal

        // Traverse the array from the end to the beginning
        for (int i = n - 1; i >= 0; i--) {
            // If the current element is already in the set, we found a duplicate
            if (st.count(nums[i])) {
                // Calculate the minimum number of removal operations needed.
                // Each operation removes 3 elements from the beginning, so we need ceil((i+1)/3.0) operations.
                return ceil((i + 1) / 3.0);
            }
            // Insert the current element in the set
            st.insert(nums[i]);
        }
        // If no duplicates are found, no operations are required
        return 0;
    }
};

/*
 *
 * Dry Run
 *
 * Example: nums = [1, 2, 3, 4, 2, 3, 3, 5, 7]
 *
 *   Visual Representation of the original array:
 *         Indices:    0    1    2    3    4    5    6    7    8
 *                  +----+----+----+----+----+----+----+----+----+
 *         Array:    | 1  | 2  | 3  | 4  | 2  | 3  | 3  | 5  | 7  |
 *                  +----+----+----+----+----+----+----+----+----+
 *
 * Start Reverse Traversal:
 *
 * Iteration 1:
 *   i = 8, nums[8] = 7
 *       Set before insertion: {}
 *       7 is not in the set.
 *       Insert 7 into the set.
 *       Set after insertion:
 *           +-----+
 *           |  7  |
 *           +-----+
 *
 * Iteration 2:
 *   i = 7, nums[7] = 5
 *       Set before insertion: {7}
 *           Visual set:
 *           +-----+
 *           |  7  |
 *           +-----+
 *       5 is not in the set.
 *       Insert 5 into the set.
 *       Set after insertion:
 *           +-----+-----+
 *           |  7  |  5  |
 *           +-----+-----+
 *
 * Iteration 3:
 *   i = 6, nums[6] = 3
 *       Set before insertion: {7, 5}
 *           Visual set:
 *           +-----+-----+
 *           |  7  |  5  |
 *           +-----+-----+
 *       3 is not in the set.
 *       Insert 3 into the set.
 *       Set after insertion:
 *           +-----+-----+-----+
 *           |  7  |  5  |  3  |
 *           +-----+-----+-----+
 *
 * Iteration 4:
 *   i = 5, nums[5] = 3
 *       Set before checking: {7, 5, 3}
 *           Visual set:
 *           +-----+-----+-----+
 *           |  7  |  5  |  3  |
 *           +-----+-----+-----+
 *       3 is already in the set. Duplicate found!
 *       Compute operations: ceil((i + 1)/3.0) = ceil((5 + 1)/3.0) = ceil(6/3.0) = ceil(2.0) = 2.
 *       Return 2.
 *
 * Final Output: 2 (minimum operations required to make the array distinct)
 */
