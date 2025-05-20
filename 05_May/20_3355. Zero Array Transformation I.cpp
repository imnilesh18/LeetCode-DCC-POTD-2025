/*
 * 3355. Zero Array Transformation I
 *
 * Medium
 *
 * You are given an integer array nums of length n and a 2D array queries, where queries[i] = [li, ri].
 * For each queries[i]:
 * Select a subset of indices within the range [li, ri] in nums.
 * Decrement the values at the selected indices by 1.
 * A Zero Array is an array where all elements are equal to 0.
 * Return true if it is possible to transform nums into a Zero Array after processing all the queries sequentially, otherwise return false.
 *
 * Example 1:
 * Input: nums = [1,0,1], queries = [[0,2]]
 * Output: true
 * Explanation:
 * For i = 0:
 * Select the subset of indices as [0, 2] and decrement the values at these indices by 1.
 * The array will become [0, 0, 0], which is a Zero Array.
 *
 * Example 2:
 * Input: nums = [4,3,2,1], queries = [[1,3],[0,2]]
 * Output: false
 * Explanation:
 * For i = 0:
 * Select the subset of indices as [1, 2, 3] and decrement the values at these indices by 1.
 * The array will become [4, 2, 1, 0].
 * For i = 1:
 * Select the subset of indices as [0, 1, 2] and decrement the values at these indices by 1.
 * The array will become [3, 1, 0, 0], which is not a Zero Array.
 *
 * Constraints:
 * 1 <= nums.length <= 10^5
 * 0 <= nums[i] <= 10^5
 * 1 <= queries.length <= 10^5
 * queries[i].length == 2
 * 0 <= li <= ri < nums.length
 */

// Approach: Use a difference array to simulate range decrements efficiently and check if total decrements at each index are enough to zero out the array.
// Time Complexity: O(n + q), where n is the size of nums and q is the number of queries (due to prefix sum and single pass checks).
// Space Complexity: O(n), for the difference array and result array.
class Solution {
public:
    bool isZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();

        // Step 1: Create a difference array to store range updates
        vector<int> diff(n, 0);

        // Step 2: For each query [li, ri], we mark +1 at li and -1 at ri+1
        for (auto& query : queries) {
            int start = query[0];
            int end   = query[1];
            int x     = 1; // Decrement each selected element by 1

            diff[start] += 1;
            if (end + 1 < n) {
                diff[end + 1] -= x;
            }
        }

        // Step 3: Build the actual number of decrements applied to each index using prefix sum
        vector<int> result(n, 0);
        int         cumSum = 0;
        for (int i = 0; i < n; i++) {
            cumSum   += diff[i];
            result[i] = cumSum;
        }

        // Step 4: Check if every element in nums can be zeroed out by the applied decrements
        for (int i = 0; i < n; i++) {
            if (result[i] < nums[i]) {
                return false; // Not enough decrements applied at index i
            }
        }

        return true; // All values can be transformed to 0
    }
};

/*
 *
 * Dry Run
 *
 * Input:
 * nums = [1, 0, 1], queries = [[0, 2]]
 *
 * Step 1: Initialize diff = [0, 0, 0]
 * Step 2: Apply query [0, 2]
 *         diff[0] += 1 -> [1, 0, 0]
 *         diff[3] -= 1 -> Out of bounds, so ignored
 *
 * Step 3: Prefix sum of diff -> result[]
 *         i = 0: cumSum = 1 -> result = [1, 0, 0]
 *         i = 1: cumSum = 1 -> result = [1, 1, 0]
 *         i = 2: cumSum = 1 -> result = [1, 1, 1]
 *
 * Step 4: Compare result[i] >= nums[i]
 *         i = 0: 1 >= 1 ✅
 *         i = 1: 1 >= 0 ✅
 *         i = 2: 1 >= 1 ✅
 *
 * All conditions satisfied → Return true
 *
 */
s
