/*
 * 2302. Count Subarrays With Score Less Than K
 *
 * Hard
 *
 * The score of an array is defined as the product of its sum and its length.
 * For example, the score of [1, 2, 3, 4, 5] is (1 + 2 + 3 + 4 + 5) * 5 = 75.
 * Given a positive integer array nums and an integer k, return the number of non-empty subarrays of nums whose score is strictly less than k.
 * A subarray is a contiguous sequence of elements within an array.
 *
 * Example 1:
 * Input: nums = [2,1,4,3,5], k = 10
 * Output: 6
 * Explanation:
 * The 6 subarrays having scores less than 10 are:
 * - [2] with score 2 * 1 = 2.
 * - [1] with score 1 * 1 = 1.
 * - [4] with score 4 * 1 = 4.
 * - [3] with score 3 * 1 = 3.
 * - [5] with score 5 * 1 = 5.
 * - [2,1] with score (2 + 1) * 2 = 6.
 * Note that subarrays such as [1,4] and [4,3,5] are not considered because their scores are 10 and 36 respectively, while we need scores strictly less than 10.
 *
 * Example 2:
 * Input: nums = [1,1,1], k = 5
 * Output: 5
 * Explanation:
 * Every subarray except [1,1,1] has a score less than 5.
 * [1,1,1] has a score (1 + 1 + 1) * 3 = 9, which is greater than 5.
 * Thus, there are 5 subarrays having scores less than 5.
 *
 * Constraints:
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^5
 * 1 <= k <= 10^15
 */

/// Approach: Use a sliding window with two pointers i and j to maintain a window [i..j] where (sum of window) * (window length) < k; for each j, shrink from the left until the score condition holds, then add (j - i + 1) to the result.
// Time Complexity: O(n) since each element is added and removed at most once by the two pointers.
// Space Complexity: O(1) additional space beyond the input array.
class Solution {
public:
    long long countSubarrays(vector<int>& nums, long long k) {
        int       n      = nums.size();     // Length of the input array
        long long result = 0;               // Count of valid subarrays
        long long sum    = 0;               // Sum of elements in current window
        int       i = 0, j = 0;             // Sliding window pointers: i = left, j = right

        while (j < n) {
            sum += nums[j];                 // Include nums[j] in the window sum

            // If current window's score >= k, shrink from the left until it becomes < k
            while (i <= j && sum * (j - i + 1) >= k) {
                sum -= nums[i];             // Remove nums[i] from sum
                i++;                        // Move left pointer right
            }

            result += (j - i + 1);          // All subarrays ending at j with start >= i are valid
            j++;                            // Expand window to the right
        }
        return result;
    }
};

/*
 *
 * Dry Run
 *
 * nums = {2, 1, 4, 3, 5}, k = 10
 *
 * Visual representation of nums:
 *  +-----+-----+-----+-----+-----+
 *  |  0  |  1  |  2  |  3  |  4  |
 *  +-----+-----+-----+-----+-----+
 *  |  2  |  1  |  4  |  3  |  5  |
 *  +-----+-----+-----+-----+-----+
 *
 * Step j = 0:
 * Before adding nums[0]:
 *   i = 0, j = 0, sum = 0, result = 0
 *   Window [i..j] is empty
 *   Representation:
 *    +-----+-----+-----+-----+-----+
 *    |  2  |  1  |  4  |  3  |  5  |
 *    +-----+-----+-----+-----+-----+
 *       ^
 *      i,j
 *
 * After sum += nums[0]:
 *   sum = 2
 *   Window [0..0], length = 1, score = 2 * 1 = 2 (< 10) → no shrink
 *   result += (0 - 0 + 1) = 1 → result = 1
 *   Representation:
 *    +-----+-----+-----+-----+-----+
 *    |  2  |  1  |  4  |  3  |  5  |
 *    +-----+-----+-----+-----+-----+
 *       ^
 *      i,j
 *
 * Step j = 1:
 * Before adding nums[1]:
 *   i = 0, j = 1, sum = 2, result = 1
 *   Window [0..0]
 *   Representation:
 *    +-----+-----+-----+-----+-----+
 *    |  2  |  1  |  4  |  3  |  5  |
 *    +-----+-----+-----+-----+-----+
 *       ^     ^
 *       i     j
 *
 * After sum += nums[1]:
 *   sum = 3
 *   Window [0..1], length = 2, score = 3 * 2 = 6 (< 10) → no shrink
 *   result += (1 - 0 + 1) = 2 → result = 3
 *   Representation:
 *    +-----+-----+-----+-----+-----+
 *    |  2  |  1  |  4  |  3  |  5  |
 *    +-----+-----+-----+-----+-----+
 *       ^     ^
 *       i     j
 *
 * Step j = 2:
 * Before adding nums[2]:
 *   i = 0, j = 2, sum = 3, result = 3
 *   Window [0..1]
 *   Representation:
 *    +-----+-----+-----+-----+-----+
 *    |  2  |  1  |  4  |  3  |  5  |
 *    +-----+-----+-----+-----+-----+
 *      ^            ^
 *      i            j
 *
 * After sum += nums[2]:
 *   sum = 7
 *   Window [0..2], length = 3, score = 7 * 3 = 21 (≥ 10) → shrink needed
 *
 *   -- Shrink iteration 1:
 *   Before shrinking:
 *     i = 0, j = 2, sum = 7, score = 21
 *     Representation:
 *      +-----+-----+-----+-----+-----+
 *      |  2  |  1  |  4  |  3  |  5  |
 *      +-----+-----+-----+-----+-----+
 *        ^            ^
 *        i            j
 *   sum -= nums[0] (2) → sum = 5; i = 1
 *   After shrinking:
 *     Window [1..2], length = 2, score = 5 * 2 = 10 (≥ 10) → continue
 *     Representation:
 *      +-----+-----+-----+-----+-----+
 *      |  2  |  1  |  4  |  3  |  5  |
 *      +-----+-----+-----+-----+-----+
 *              ^     ^
 *              i     j
 *
 *   -- Shrink iteration 2:
 *   Before shrinking:
 *     i = 1, j = 2, sum = 5, score = 10
 *     Representation:
 *      +-----+-----+-----+-----+-----+
 *      |  2  |  1  |  4  |  3  |  5  |
 *      +-----+-----+-----+-----+-----+
 *               ^     ^
 *               i     j
 *   sum -= nums[1] (1) → sum = 4; i = 2
 *   After shrinking:
 *     Window [2..2], length = 1, score = 4 * 1 = 4 (< 10) → stop shrinking
 *     Representation:
 *      +-----+-----+-----+-----+-----+
 *      |  2  |  1  |  4  |  3  |  5  |
 *      +-----+-----+-----+-----+-----+
 *                     ^
 *                    i,j
 *
 *   result += (2 - 2 + 1) = 1 → result = 4
 *
 * Step j = 3:
 * Before adding nums[3]:
 *   i = 2, j = 3, sum = 4, result = 4
 *   Window [2..2]
 *   Representation:
 *    +-----+-----+-----+-----+-----+
 *    |  2  |  1  |  4  |  3  |  5  |
 *    +-----+-----+-----+-----+-----+
 *                    ^    ^
 *                    i    j
 *
 * After sum += nums[3]:
 *   sum = 7
 *   Window [2..3], length = 2, score = 7 * 2 = 14 (≥ 10) → shrink needed
 *
 *   -- Shrink iteration:
 *   Before shrinking:
 *     i = 2, j = 3, sum = 7, score = 14
 *     Representation:
 *      +-----+-----+-----+-----+-----+
 *      |  2  |  1  |  4  |  3  |  5  |
 *      +-----+-----+-----+-----+-----+
 *                     ^    ^
 *                     i    j
 *   sum -= nums[2] (4) → sum = 3; i = 3
 *   After shrinking:
 *     Window [3..3], length = 1, score = 3 * 1 = 3 (< 10) → stop
 *     Representation:
 *      +-----+-----+-----+-----+-----+
 *      |  2  |  1  |  4  |  3  |  5  |
 *      +-----+-----+-----+-----+-----+
 *                           ^
 *                          i,j
 *
 *   result += (3 - 3 + 1) = 1 → result = 5
 *
 * Step j = 4:
 * Before adding nums[4]:
 *   i = 3, j = 4, sum = 3, result = 5
 *   Window [3..3]
 *   Representation:
 *    +-----+-----+-----+-----+-----+
 *    |  2  |  1  |  4  |  3  |  5  |
 *    +-----+-----+-----+-----+-----+
 *                         ^     ^
 *                         i     j
 *
 * After sum += nums[4]:
 *   sum = 8
 *   Window [3..4], length = 2, score = 8 * 2 = 16 (≥ 10) → shrink needed
 *
 *   -- Shrink iteration:
 *   Before shrinking:
 *     i = 3, j = 4, sum = 8, score = 16
 *     Representation:
 *      +-----+-----+-----+-----+-----+
 *      |  2  |  1  |  4  |  3  |  5  |
 *      +-----+-----+-----+-----+-----+
 *                            ^    ^
 *                            i    j
 *   sum -= nums[3] (3) → sum = 5; i = 4
 *   After shrinking:
 *     Window [4..4], length = 1, score = 5 * 1 = 5 (< 10) → stop
 *     Representation:
 *      +-----+-----+-----+-----+-----+
 *      |  2  |  1  |  4  |  3  |  5  |
 *      +-----+-----+-----+-----+-----+
 *                                 ^
 *                                i,j
 *
 *   result += (4 - 4 + 1) = 1 → result = 6
 *
 * Final result = 6
 */
