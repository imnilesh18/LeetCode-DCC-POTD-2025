/*
 * 2401. Longest Nice Subarray
 *
 * You are given an array nums consisting of positive integers.
 * We call a subarray of nums nice if the bitwise AND of every pair of elements that are in different positions in the subarray is equal to 0.
 * Return the length of the longest nice subarray.
 * A subarray is a contiguous part of an array.
 * Note that subarrays of length 1 are always considered nice.
 *
 * Example 1:
 * Input: nums = [1,3,8,48,10]
 * Output: 3
 * Explanation: The longest nice subarray is [3,8,48]. This subarray satisfies the conditions:
 * - 3 AND 8 = 0.
 * - 3 AND 48 = 0.
 * - 8 AND 48 = 0.
 * It can be proven that no longer nice subarray can be obtained, so we return 3.
 *
 * Example 2:
 * Input: nums = [3,1,5,11,13]
 * Output: 1
 * Explanation: The length of the longest nice subarray is 1. Any subarray of length 1 can be chosen.
 *
 * Constraints:
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^9
 */

// Approach 1: Use two nested loops to explore all possible subarrays; maintain a bitmask for the current subarray, and break if a new element shares a common set bit, ensuring the subarray remains "nice".
// Time Complexity: O(n^2) in the worst-case due to the nested loops, though early breaks often reduce the average complexity.
// Space Complexity: O(1) since only a fixed number of extra variables are used regardless of input size.
class Solution {
public:
    int longestNiceSubarray(vector<int>& nums) {
        int n      = nums.size(); // Total number of elements in nums
        int result = 0;           // Stores the maximum length of a nice subarray found so far

        // Iterate over every possible starting index for the subarray
        for (int i = 0; i < n; i++) {
            int mask = 0;     // Bitmask to record the bits present in the current subarray

            // Try to extend the subarray starting at index i
            for (int j = i; j < n; j++) {
                // If the current number shares any common set bits with the subarray (mask), break out
                if ((mask & nums[j]) != 0) {
                    break;
                }
                // Update the result with the current subarray length (j - i + 1)
                result = max(result, j - i + 1);
                // Include the current number's bits in the mask
                mask |= nums[j];
            }
        }
        return result;     // Return the maximum length of a nice subarray
    }
};

/*
 * Dry Run:
 * For nums = [1, 3, 8, 48, 10]:
 * - i = 0: mask = 0
 *  j = 0: mask becomes 1 (binary 0001); subarray = [1], result = 1.
 *  j = 1: (mask & 3) = (0001 & 0011) = 0001 (non-zero); break.
 * - i = 1: mask = 0
 *  j = 1: mask becomes 3 (binary 0011); subarray = [3], result = 1.
 *  j = 2: (mask & 8) = (0011 & 1000) = 0000; mask becomes 11 (binary 1011); subarray = [3,8], result = 2.
 *  j = 3: (mask & 48) = (1011 & 110000) = 0; mask becomes 59 (binary 111011); subarray = [3,8,48], result = 3.
 *  j = 4: (mask & 10) != 0; break.
 * - i = 2, 3, 4: Subsequent subarrays will not exceed the length of 3.
 * Final result is 3.
 */

// Approach 2: Use a sliding window with two pointers (i and j) to maintain a "nice" subarray where the bitwise AND of any two distinct elements is 0.
//            Expand the window by moving j and, if a conflict is found (mask & nums[j] != 0), shrink the window from the left by moving i until the conflict is resolved.
// Time Complexity: O(n) because each element is processed at most twice (once when added and once when removed).
// Space Complexity: O(1) since only a few extra variables are used.
class Solution {
public:
    int longestNiceSubarray(vector<int>& nums) {
        int n = nums.size();   // Total number of elements in nums

        int i = 0;             // Left pointer for the sliding window
        int j = 0;             // Right pointer for the sliding window

        int result = 1;        // Stores the maximum length of a nice subarray found so far; at least 1 since single element is always nice
        int mask   = 0;        // Bitmask to keep track of bits present in the current window

        // Expand the window with j until we've processed all elements
        while (j < n) {
            // If adding nums[j] causes a conflict (common set bit with the current mask), shrink the window from the left
            while ((mask & nums[j]) != 0) {
                mask = mask ^ nums[i];     // Remove the contribution of nums[i] from the mask
                i++;                       // Move the left pointer to the right
            }

            // Update the result with the size of the current valid window
            result = max(result, j - i + 1);
            // Add the current element's bits to the mask
            mask = mask | nums[j];
            // Move the right pointer to expand the window
            j++;
        }

        return result;     // Return the length of the longest nice subarray
    }
};

/*
 * Dry Run:
 * For nums = [1, 3, 8, 48, 10]:
 * - Initialize: i = 0, j = 0, result = 1, mask = 0.
 * - j = 0:
 *  (mask & nums[0]) = (0 & 1) = 0 → no conflict.
 *  Update result: max(1, 0-0+1) = 1.
 *  Update mask: 0 | 1 = 1.
 *  Increment j to 1.
 * - j = 1:
 *  (mask & nums[1]) = (1 & 3) = 1 (conflict detected).
 *  Enter inner loop:
 *      Remove nums[0] (1) from mask: mask = 1 ^ 1 = 0.
 *      Increment i to 1.
 *  Now (mask & nums[1]) = (0 & 3) = 0 → conflict resolved.
 *  Update result: max(1, 1-1+1) = 1.
 *  Update mask: 0 | 3 = 3.
 *  Increment j to 2.
 * - j = 2:
 *  (mask & nums[2]) = (3 & 8) = 0 → no conflict.
 *  Update result: max(1, 2-1+1) = 2.
 *  Update mask: 3 | 8 = 11.
 *  Increment j to 3.
 * - j = 3:
 *  (mask & nums[3]) = (11 & 48) = 0 → no conflict.
 *  Update result: max(2, 3-1+1) = 3.
 *  Update mask: 11 | 48 = 59.
 *  Increment j to 4.
 * - j = 4:
 *  (mask & nums[4]) = (59 & 10) ≠ 0 (conflict detected).
 *  Enter inner loop:
 *      Remove nums[1] (3) from mask: mask = 59 ^ 3 = 56.
 *      Increment i to 2.
 *  Check conflict: (mask & nums[4]) = (56 & 10) ≠ 0.
 *  Continue inner loop:
 *      Remove nums[2] (8) from mask: mask = 56 ^ 8 = 48.
 *      Increment i to 3.
 *  Check conflict: (mask & nums[4]) = (48 & 10) = 0 → conflict resolved.
 *  Update result: max(3, 4-3+1) = 3.
 *  Update mask: 48 | 10 = 58.
 *  Increment j to 5.
 * - j = 5: j equals n, so exit the loop.
 * Final result is 3.
 */
