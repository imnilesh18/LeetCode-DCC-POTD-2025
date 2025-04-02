/*
 * 2873. Maximum Value of an Ordered Triplet I
 *
 * You are given a 0-indexed integer array nums.
 * Return the maximum value over all triplets of indices (i, j, k) such that i < j < k. If all such triplets have a negative value, return 0.
 * The value of a triplet of indices (i, j, k) is equal to (nums[i] - nums[j]) * nums[k].
 *
 * Example 1:
 * Input: nums = [12,6,1,2,7]
 * Output: 77
 * Explanation: The value of the triplet (0, 2, 4) is (nums[0] - nums[2]) * nums[4] = 77.
 * It can be shown that there are no ordered triplets of indices with a value greater than 77.
 *
 * Example 2:
 * Input: nums = [1,10,3,4,19]
 * Output: 133
 * Explanation: The value of the triplet (1, 2, 4) is (nums[1] - nums[2]) * nums[4] = 133.
 * It can be shown that there are no ordered triplets of indices with a value greater than 133.
 *
 * Example 3:
 * Input: nums = [1,2,3]
 * Output: 0
 * Explanation: The only ordered triplet of indices (0, 1, 2) has a negative value of (nums[0] - nums[1]) * nums[2] = -3. Hence, the answer would be 0.
 *
 * Constraints:
 * 3 <= nums.length <= 100
 * 1 <= nums[i] <= 10^6
 */

// Approach 1 (Brute Force): Use brute force with three nested loops to evaluate all ordered triplets (i, j, k) where i < j < k and compute (nums[i] - nums[j]) * nums[k] to find the maximum triplet value.
// Time Complexity: O(n^3) since we check every possible triplet in the array.
// Space Complexity: O(1) as only a constant amount of extra space is used.
class Solution {
public:
    long long maximumTripletValue(vector<int>& nums) {
        long long result = 0;           // Initialize result to 0 (if all computed values are negative, result remains 0).
        int       n      = nums.size(); // Total number of elements in the array.

        // Iterate over the first element of the triplet.
        for (int i = 0; i < n; i++) {             // Pointer i moves from 0 to n-3.
            // Iterate over the second element, ensuring j > i.
            for (int j = i + 1; j < n; j++) {     // Pointer j moves from i+1 to n-2.
                // Iterate over the third element, ensuring k > j.
                for (int k = j + 1; k < n; k++) { // Pointer k moves from j+1 to n-1.
                    // Update the maximum triplet value.
                    result = max(result, (long long)(nums[i] - nums[j]) * nums[k]);
                }
            }
        }
        return result;     // Return the maximum value computed.
    }
};

/*
 *
 * Dry Run:
 * Given array: [12, 6, 1, 2, 7]
 *
 * Initial Array Visualization:
 * +-----+-----+-----+-----+-----+
 * | 12  |  6  |  1  |  2  |  7  |
 * +-----+-----+-----+-----+-----+
 *
 * Iteration Details:
 *
 * Step 1: i = 0, j = 1, k = 2
 * Array with pointers:
 * +-----+-----+-----+-----+-----+
 * | 12  |  6  |  1  |  2  |  7  |
 * +-----+-----+-----+-----+-----+
 *   i     j     k
 * Calculation: (12 - 6) * 1 = 6
 * Current max result = 6
 *
 * Step 2: i = 0, j = 1, k = 3
 * +-----+-----+-----+-----+-----+
 * | 12  |  6  |  1  |  2  |  7  |
 * +-----+-----+-----+-----+-----+
 *   i     j           k
 * Calculation: (12 - 6) * 2 = 12
 * Current max result = 12
 *
 * Step 3: i = 0, j = 1, k = 4
 * +-----+-----+-----+-----+-----+
 * | 12  |  6  |  1  |  2  |  7  |
 * +-----+-----+-----+-----+-----+
 *   i     j                 k
 * Calculation: (12 - 6) * 7 = 42
 * Current max result = 42
 *
 * Step 4: i = 0, j = 2, k = 3
 * +-----+-----+-----+-----+-----+
 * | 12  |  6  |  1  |  2  |  7  |
 * +-----+-----+-----+-----+-----+
 *   i           j     k
 * Calculation: (12 - 1) * 2 = 22
 * Current max result remains = 42
 *
 * Step 5: i = 0, j = 2, k = 4
 * +-----+-----+-----+-----+-----+
 * | 12  |  6  |  1  |  2  |  7  |
 * +-----+-----+-----+-----+-----+
 *   i           j             k
 * Calculation: (12 - 1) * 7 = 77
 * Updated max result = 77
 *
 * Step 6: i = 0, j = 3, k = 4
 * +-----+-----+-----+-----+-----+
 * | 12  |  6  |  1  |  2  |  7  |
 * +-----+-----+-----+-----+-----+
 *   i                 j     k
 * Calculation: (12 - 2) * 7 = 70
 * Current max result remains = 77
 *
 * Step 7: i = 0, j = 4 -> No valid k (pointer k cannot be > index 4)
 *
 * Step 8: i = 1, j = 2, k = 3
 * +-----+-----+-----+-----+-----+
 * | 12  |  6  |  1  |  2  |  7  |
 * +-----+-----+-----+-----+-----+
 *         i     j     k
 * Calculation: (6 - 1) * 2 = 10
 * Current max result remains = 77
 *
 * Step 9: i = 1, j = 2, k = 4
 * +-----+-----+-----+-----+-----+
 * | 12  |  6  |  1  |  2  |  7  |
 * +-----+-----+-----+-----+-----+
 *         i     j             k
 * Calculation: (6 - 1) * 7 = 35
 * Current max result remains = 77
 *
 * Step 10: i = 1, j = 3, k = 4
 * +-----+-----+-----+-----+-----+
 * | 12  |  6  |  1  |  2  |  7  |
 * +-----+-----+-----+-----+-----+
 *         i           j     k
 * Calculation: (6 - 2) * 7 = 28
 * Current max result remains = 77
 *
 * Step 11: i = 1, j = 4 -> No valid k
 *
 * Step 12: i = 2, j = 3, k = 4
 * +-----+-----+-----+-----+-----+
 * | 12  |  6  |  1  |  2  |  7  |
 * +-----+-----+-----+-----+-----+
 *               i     j     k
 * Calculation: (1 - 2) * 7 = -7
 * Current max result remains = 77
 *
 * Step 13: i = 2, j = 4 -> No valid k
 *
 * Step 14: i = 3, j = 4 -> No valid k
 *
 * Final maximum triplet value computed = 77
 *
 */

// Approach 2: Precompute leftMaxi and rightMaxk arrays where leftMaxi[j] holds the maximum element to the left of index j and rightMaxk[j] holds the maximum element to the right of index j. Then, for each j, calculate (leftMaxi[j] - nums[j]) * rightMaxk[j] to update the maximum result.
// Time Complexity: O(n) because we traverse the array a constant number of times.
// Space Complexity: O(n) due to the additional leftMaxi and rightMaxk arrays.
class Solution {
public:
    long long maximumTripletValue(vector<int>& nums) {
        int n = nums.size();

        vector<int> leftMaxi(n);
        vector<int> rightMaxk(n);

        // Precompute leftMaxi for each index j: maximum element in nums[0..j-1]
        for (int j = 1; j < n; j++) {
            leftMaxi[j] = max(leftMaxi[j - 1], nums[j - 1]);
        }

        // Precompute rightMaxk for each index j: maximum element in nums[j+1..n-1]
        for (int k = n - 2; k >= 0; k--) {
            rightMaxk[k] = max(rightMaxk[k + 1], nums[k + 1]);
        }

        long long result = 0;
        // For each valid index j, calculate the triplet value and update the maximum result.
        for (int j = 1; j < n; j++) {
            result = max(result, (long long)(leftMaxi[j] - nums[j]) * rightMaxk[j]);
        }
        return result;
    }
};

/*
 *
 * Dry Run:
 * Given array: [12, 6, 1, 2, 7]
 *
 * Initial Array Visualization:
 * +-----+-----+-----+-----+-----+
 * | 12  |  6  |  1  |  2  |  7  |
 * +-----+-----+-----+-----+-----+
 *
 * Step 1: Compute leftMaxi array:
 * (Note: leftMaxi[0] is not used; default value 0)
 *
 * For j = 1:
 *   leftMaxi[1] = max(leftMaxi[0], nums[0]) = max(0, 12) = 12
 *   Visualization:
 *   +--------+--------+--------+--------+--------+
 *   |   0    |   12   |        |        |        |
 *   +--------+--------+--------+--------+--------+
 *                ^
 *                j = 1 computed
 *
 * For j = 2:
 *   leftMaxi[2] = max(leftMaxi[1], nums[1]) = max(12, 6) = 12
 *   Visualization:
 *   +--------+--------+--------+--------+--------+
 *   |   0    |   12   |   12   |        |        |
 *   +--------+--------+--------+--------+--------+
 *                         ^
 *                         j = 2 computed
 *
 * For j = 3:
 *   leftMaxi[3] = max(leftMaxi[2], nums[2]) = max(12, 1) = 12
 *   Visualization:
 *   +--------+--------+--------+--------+--------+
 *   |   0    |   12   |   12   |   12   |        |
 *   +--------+--------+--------+--------+--------+
 *                                  ^
 *                                  j = 3 computed
 *
 * For j = 4:
 *   leftMaxi[4] = max(leftMaxi[3], nums[3]) = max(12, 2) = 12
 *   Visualization:
 *   +--------+--------+--------+--------+--------+
 *   |   0    |   12   |   12   |   12   |   12   |
 *   +--------+--------+--------+--------+--------+
 *                                           ^
 *                                           j = 4 computed
 *
 * Step 2: Compute rightMaxk array:
 * (Note: rightMaxk[n-1] is not used; default value 0)
 *
 * For k = 3:
 *   rightMaxk[3] = max(rightMaxk[4], nums[4]) = max(0, 7) = 7
 *   Visualization:
 *   +--------+--------+--------+--------+--------+
 *   |        |        |        |   7    |   0    |
 *   +--------+--------+--------+--------+--------+
 *                                  ^
 *                                  k = 3 computed
 *
 * For k = 2:
 *   rightMaxk[2] = max(rightMaxk[3], nums[3]) = max(7, 2) = 7
 *   Visualization:
 *   +--------+--------+--------+--------+--------+
 *   |        |        |   7    |   7    |   0    |
 *   +--------+--------+--------+--------+--------+
 *                         ^
 *                         k = 2 computed
 *
 * For k = 1:
 *   rightMaxk[1] = max(rightMaxk[2], nums[2]) = max(7, 1) = 7
 *   Visualization:
 *   +--------+--------+--------+--------+--------+
 *   |        |   7    |   7    |   7    |   0    |
 *   +--------+--------+--------+--------+--------+
 *               ^
 *               k = 1 computed
 *
 * For k = 0:
 *   rightMaxk[0] = max(rightMaxk[1], nums[1]) = max(7, 6) = 7
 *   Visualization:
 *   +--------+--------+--------+--------+--------+
 *   |   7    |   7    |   7    |   7    |   0    |
 *   +--------+--------+--------+--------+--------+
 *       ^
 *       k = 0 computed
 *
 * Step 3: Iterate over each index j (from 1 to 4) to compute the maximum triplet value:
 *
 * For j = 1:
 *   leftMaxi[1] = 12, nums[1] = 6, rightMaxk[1] = 7
 *   Calculation: (12 - 6) * 7 = 42
 *   Visualization:
 *   Array with pointer at j = 1:
 *   +-----+-----+-----+-----+-----+
 *   | 12  |  6  |  1  |  2  |  7  |
 *   +-----+-----+-----+-----+-----+
 *            ^
 *   Current max result = 42
 *
 * For j = 2:
 *   leftMaxi[2] = 12, nums[2] = 1, rightMaxk[2] = 7
 *   Calculation: (12 - 1) * 7 = 77
 *   Visualization:
 *   Array with pointer at j = 2:
 *   +-----+-----+-----+-----+-----+
 *   | 12  |  6  |  1  |  2  |  7  |
 *   +-----+-----+-----+-----+-----+
 *                  ^
 *   Updated max result = 77
 *
 * For j = 3:
 *   leftMaxi[3] = 12, nums[3] = 2, rightMaxk[3] = 7
 *   Calculation: (12 - 2) * 7 = 70
 *   Visualization:
 *   Array with pointer at j = 3:
 *   +-----+-----+-----+-----+-----+
 *   | 12  |  6  |  1  |  2  |  7  |
 *   +-----+-----+-----+-----+-----+
 *                        ^
 *   Max result remains = 77
 *
 * For j = 4:
 *   leftMaxi[4] = 12, nums[4] = 7, rightMaxk[4] = 0
 *   Calculation: (12 - 7) * 0 = 0
 *   Visualization:
 *   Array with pointer at j = 4:
 *   +-----+-----+-----+-----+-----+
 *   | 12  |  6  |  1  |  2  |  7  |
 *   +-----+-----+-----+-----+-----+
 *                              ^
 *   Max result remains = 77
 *
 * Final maximum triplet value = 77
 *
 */

// Approach: Single pass through the array. Maintain two variables:
//           - maxi: the maximum element encountered so far (potential nums[i]).
//           - maxDiff: the maximum difference (nums[i] - nums[j]) observed so far when treating the current element as a potential nums[j].
//           For each element (as potential nums[k]), update the result as maxDiff * nums[k].
// Time Complexity: O(n) - Single pass through the array.
// Space Complexity: O(1) - Only constant extra space is used.
class Solution {
public:
    long long maximumTripletValue(vector<int>& nums) {
        int       n       = nums.size();
        long long result  = 0;       // Maximum triplet value found so far.
        long long maxDiff = 0;       // Maximum difference (nums[i] - nums[j]) for valid i, j.
        long long maxi    = 0;       // Maximum number encountered so far (for potential nums[i]).

        // Iterate through the array, considering each element as the third element (nums[k]) of the triplet.
        for (int k = 0; k < n; k++) {
            result  = max(result, maxDiff * nums[k]);     // Update result with current potential triplet value.
            maxDiff = max(maxDiff, maxi - nums[k]);       // Update maxDiff considering current element as potential nums[j].
            maxi    = max(maxi, (long long)nums[k]);      // Update maxi with the current element.
        }

        return result;
    }
};

/*
 *
 * Dry Run:
 *
 * Given Array: [12, 6, 1, 2, 7]
 *
 * Initial State:
 *   result = 0, maxDiff = 0, maxi = 0
 *
 * Iteration k = 0:
 *   Current element (nums[0]) = 12
 *   Before:
 *       Array with pointer at k = 0:
 *       +-----+-----+-----+-----+-----+
 *       | 12  |  6  |  1  |  2  |  7  |
 *       +-----+-----+-----+-----+-----+
 *         ^
 *       State: result = 0, maxDiff = 0, maxi = 0
 *   Updates:
 *       result = max(0, 0 * 12) = 0
 *       maxDiff = max(0, 0 - 12) = 0
 *       maxi = max(0, 12) = 12
 *   After:
 *       Array with pointer at k = 0:
 *       +-----+-----+-----+-----+-----+
 *       | 12  |  6  |  1  |  2  |  7  |
 *       +-----+-----+-----+-----+-----+
 *         ^
 *       State: result = 0, maxDiff = 0, maxi = 12
 *
 * Iteration k = 1:
 *   Current element (nums[1]) = 6
 *   Before:
 *       Array with pointer at k = 1:
 *       +-----+-----+-----+-----+-----+
 *       | 12  |  6  |  1  |  2  |  7  |
 *       +-----+-----+-----+-----+-----+
 *               ^
 *       State: result = 0, maxDiff = 0, maxi = 12
 *   Updates:
 *       result = max(0, 0 * 6) = 0
 *       maxDiff = max(0, 12 - 6) = 6
 *       maxi = max(12, 6) = 12
 *   After:
 *       Array with pointer at k = 1:
 *       +-----+-----+-----+-----+-----+
 *       | 12  |  6  |  1  |  2  |  7  |
 *       +-----+-----+-----+-----+-----+
 *               ^
 *       State: result = 0, maxDiff = 6, maxi = 12
 *
 * Iteration k = 2:
 *   Current element (nums[2]) = 1
 *   Before:
 *       Array with pointer at k = 2:
 *       +-----+-----+-----+-----+-----+
 *       | 12  |  6  |  1  |  2  |  7  |
 *       +-----+-----+-----+-----+-----+
 *                     ^
 *       State: result = 0, maxDiff = 6, maxi = 12
 *   Updates:
 *       result = max(0, 6 * 1) = 6
 *       maxDiff = max(6, 12 - 1) = 11
 *       maxi = max(12, 1) = 12
 *   After:
 *       Array with pointer at k = 2:
 *       +-----+-----+-----+-----+-----+
 *       | 12  |  6  |  1  |  2  |  7  |
 *       +-----+-----+-----+-----+-----+
 *                     ^
 *       State: result = 6, maxDiff = 11, maxi = 12
 *
 * Iteration k = 3:
 *   Current element (nums[3]) = 2
 *   Before:
 *       Array with pointer at k = 3:
 *       +-----+-----+-----+-----+-----+
 *       | 12  |  6  |  1  |  2  |  7  |
 *       +-----+-----+-----+-----+-----+
 *                           ^
 *       State: result = 6, maxDiff = 11, maxi = 12
 *   Updates:
 *       result = max(6, 11 * 2) = 22
 *       maxDiff = max(11, 12 - 2) = 11   // (12 - 2 = 10, so maxDiff remains 11)
 *       maxi = max(12, 2) = 12
 *   After:
 *       Array with pointer at k = 3:
 *       +-----+-----+-----+-----+-----+
 *       | 12  |  6  |  1  |  2  |  7  |
 *       +-----+-----+-----+-----+-----+
 *                           ^
 *       State: result = 22, maxDiff = 11, maxi = 12
 *
 * Iteration k = 4:
 *   Current element (nums[4]) = 7
 *   Before:
 *       Array with pointer at k = 4:
 *       +-----+-----+-----+-----+-----+
 *       | 12  |  6  |  1  |  2  |  7  |
 *       +-----+-----+-----+-----+-----+
 *                                  ^
 *       State: result = 22, maxDiff = 11, maxi = 12
 *   Updates:
 *       result = max(22, 11 * 7) = 77
 *       maxDiff = max(11, 12 - 7) = 11   // (12 - 7 = 5, so maxDiff remains 11)
 *       maxi = max(12, 7) = 12
 *   After:
 *       Array with pointer at k = 4:
 *       +-----+-----+-----+-----+-----+
 *       | 12  |  6  |  1  |  2  |  7  |
 *       +-----+-----+-----+-----+-----+
 *                                  ^
 *       State: result = 77, maxDiff = 11, maxi = 12
 *
 * Final Maximum Triplet Value: 77
 *
 */
