/*
 * 3487. Maximum Unique Subarray Sum After Deletion
 *
 * Easy
 *
 * You are given an integer array nums.
 * You are allowed to delete any number of elements from nums without making it empty. After performing the deletions, select a subarray of nums such that:
 * All elements in the subarray are unique.
 * The sum of the elements in the subarray is maximized.
 * Return the maximum sum of such a subarray.
 *
 * Example 1:
 * Input: nums = [1,2,3,4,5]
 * Output: 1
 * Explanation:
 * Select the entire array without deleting any element to obtain the maximum sum.
 *
 * Example 2:
 * Input: nums = [1,1,0,1,1]
 * Output: 1
 * Explanation:
 * Delete the element nums[0] == 1, nums[1] == 1, nums[2] == 0, and nums[3] == 1. Select the entire array [1] to obtain the maximum sum.
 *
 * Example 3:
 * Input: nums = [1,2,-1,-2,1,0,-1]
 * Output: 3
 * Explanation:
 * Delete the elements nums[2] == -1 and nums[3] == -2, and select the subarray [2, 1] from [1, 2, 1, 0, -1] to obtain the maximum sum.
 *
 * Constraints:
 * 1 <= nums.length <= 100
 * -100 <= nums[i] <= 100
 */

// Approach 1: Iterate through the array, summing up all unique positive numbers using a hash set to track uniqueness. Keep a separate variable for the maximum non-positive number. If the sum of positives is zero, return the max non-positive number; otherwise, return the sum.
// Time Complexity: O(n) because we traverse the input array once, and set operations take average O(1) time.
// Space Complexity: O(k) where k is the number of unique positive elements, which can be up to O(n) in the worst case.
class Solution {
public:
    int maxSum(vector<int>& nums) {
        // Use a hash set to store unique positive numbers we have seen.
        unordered_set<int> st;

        // 'sum' will store the sum of all unique positive numbers.
        int sum = 0;

        // 'maxNeg' will store the largest non-positive number encountered.
        // Initialized to the smallest possible integer.
        int maxNeg = INT_MIN;

        // Iterate through each number in the input array.
        for (int& num : nums) {
            // If the number is non-positive (<= 0).
            if (num <= 0) {
                // Update maxNeg if the current number is larger than the current maxNeg.
                maxNeg = max(maxNeg, num);
            }
            // If the number is positive and has not been seen before.
            else if (!st.count(num)) {
                // Add the number to our running sum.
                sum += num;
                // Add the number to the set to mark it as seen.
                st.insert(num);
            }
        }

        // If 'sum' is 0, it means there were no positive numbers in the array.
        // In this case, the answer is the largest single non-positive number.
        // Otherwise, the answer is the sum of all unique positive numbers.
        return sum == 0 ? maxNeg : sum;
    }
};

/* * Dry Run for Approach-1 with Input: nums = [1, 2, -1, -2, 1, 0, -1]
 *
 * Initial State:
 * sum = 0
 * maxNeg = -2147483648 (INT_MIN)
 * st = {} (empty set)
 *
 * --- Loop Start ---
 *
 * 1. num = 1
 * - Condition `num <= 0` is false.
 * - Condition `!st.count(1)` is true.
 * - sum = 0 + 1 = 1
 * - st.insert(1) -> st = {1}
 *
 * 2. num = 2
 * - Condition `num <= 0` is false.
 * - Condition `!st.count(2)` is true.
 * - sum = 1 + 2 = 3
 * - st.insert(2) -> st = {1, 2}
 *
 * 3. num = -1
 * - Condition `num <= 0` is true.
 * - maxNeg = max(INT_MIN, -1) = -1
 *
 * 4. num = -2
 * - Condition `num <= 0` is true.
 * - maxNeg = max(-1, -2) = -1
 *
 * 5. num = 1
 * - Condition `num <= 0` is false.
 * - Condition `!st.count(1)` is false (1 is already in the set).
 * - No changes.
 *
 * 6. num = 0
 * - Condition `num <= 0` is true.
 * - maxNeg = max(-1, 0) = 0
 *
 * 7. num = -1
 * - Condition `num <= 0` is true.
 * - maxNeg = max(0, -1) = 0
 *
 * --- Loop End ---
 *
 * Final values:
 * sum = 3
 * maxNeg = 0
 *
 * Return statement: `return sum == 0 ? maxNeg : sum;`
 * - `sum` (3) is not equal to 0.
 * - The statement returns `sum`.
 *
 * Final Output: 3
 */

// Approach 2: Similar to the set-based approach, but uses a fixed-size array as a hash table because the values of positive numbers are constrained (1 to 100). This optimizes space.
// Time Complexity: O(n) because we traverse the input array once, and array access is O(1).
// Space Complexity: O(1) because the size of the tracking array 'st' is constant (101) and does not depend on the input size 'n'.
class Solution {
public:
    int maxSum(vector<int>& nums) {
        // Use a vector of size 101 as a frequency map/set for positive numbers (1 to 100).
        // Initialize with -1 to indicate that no number has been seen yet.
        vector<int> st(101, -1);

        // 'sum' will store the sum of all unique positive numbers.
        int sum = 0;

        // 'maxNeg' will store the largest non-positive number encountered.
        int maxNeg = INT_MIN;

        // Iterate through each number in the input array.
        for (int& num : nums) {
            // If the number is non-positive.
            if (num <= 0) {
                // Update maxNeg if the current number is larger.
                maxNeg = max(maxNeg, num);
            }
            // If the number is positive and has not been seen before (st[num] is still -1).
            else if (st[num] == -1) {
                // Add the number to our running sum.
                sum += num;
                // Mark this number as seen by changing its value in the 'st' array.
                st[num] = 1;
            }
        }

        // If 'sum' is 0 (no positive numbers found), return the largest non-positive number.
        // Otherwise, return the sum of unique positive numbers.
        return sum == 0 ? maxNeg : sum;
    }
};

/* * Dry Run for Approach-2 with Input: nums = [1, 2, -1, -2, 1, 0, -1]
 *
 * Initial State:
 * sum = 0
 * maxNeg = -2147483648 (INT_MIN)
 * st = a vector of size 101, all initialized to -1.
 *
 * --- Loop Start ---
 *
 * 1. num = 1
 * - Condition `num <= 0` is false.
 * - Condition `st[1] == -1` is true.
 * - sum = 0 + 1 = 1
 * - st[1] is set to 1.
 *
 * 2. num = 2
 * - Condition `num <= 0` is false.
 * - Condition `st[2] == -1` is true.
 * - sum = 1 + 2 = 3
 * - st[2] is set to 1.
 *
 * 3. num = -1
 * - Condition `num <= 0` is true.
 * - maxNeg = max(INT_MIN, -1) = -1
 *
 * 4. num = -2
 * - Condition `num <= 0` is true.
 * - maxNeg = max(-1, -2) = -1
 *
 * 5. num = 1
 * - Condition `num <= 0` is false.
 * - Condition `st[1] == -1` is false (since st[1] is now 1).
 * - No changes.
 *
 * 6. num = 0
 * - Condition `num <= 0` is true.
 * - maxNeg = max(-1, 0) = 0
 *
 * 7. num = -1
 * - Condition `num <= 0` is true.
 * - maxNeg = max(0, -1) = 0
 *
 * --- Loop End ---
 *
 * Final values:
 * sum = 3
 * maxNeg = 0
 *
 * Return statement: `return sum == 0 ? maxNeg : sum;`
 * - `sum` (3) is not equal to 0.
 * - The statement returns `sum`.
 *
 * Final Output: 3
 */
