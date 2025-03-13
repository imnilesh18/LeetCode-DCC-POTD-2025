/*
 * 3356. Zero Array Transformation II
 *
 * You are given an integer array nums of length n and a 2D array queries where queries[i] = [li, ri, vali].
 * Each queries[i] represents the following action on nums:
 * Decrement the value at each index in the range [li, ri] in nums by at most vali.
 * The amount by which each value is decremented can be chosen independently for each index.
 * A Zero Array is an array with all its elements equal to 0.
 *
 * Return the minimum possible non-negative value of k, such that after processing the first k queries in sequence, nums becomes a Zero Array. If no such k exists, return -1.
 *
 * Example 1:
 * Input: nums = [2,0,2], queries = [[0,2,1],[0,2,1],[1,1,3]]
 * Output: 2
 * Explanation:
 * For i = 0 (l = 0, r = 2, val = 1):
 * Decrement values at indices [0, 1, 2] by [1, 0, 1] respectively.
 * The array will become [1, 0, 1].
 * For i = 1 (l = 0, r = 2, val = 1):
 * Decrement values at indices [0, 1, 2] by [1, 0, 1] respectively.
 * The array will become [0, 0, 0], which is a Zero Array. Therefore, the minimum value of k is 2.
 *
 * Example 2:
 * Input: nums = [4,3,2,1], queries = [[1,3,2],[0,2,1]]
 * Output: -1
 * Explanation:
 * For i = 0 (l = 1, r = 3, val = 2):
 * Decrement values at indices [1, 2, 3] by [2, 2, 1] respectively.
 * The array will become [4, 1, 0, 0].
 * For i = 1 (l = 0, r = 2, val = 1):
 * Decrement values at indices [0, 1, 2] by [1, 1, 0] respectively.
 * The array will become [3, 0, 0, 0], which is not a Zero Array.
 *
 * Constraints:
 * 1 <= nums.length <= 10^5
 * 0 <= nums[i] <= 5 * 10^5
 * 1 <= queries.length <= 10^5
 * queries[i].length == 3
 * 0 <= li <= ri < nums.length
 * 1 <= vali <= 5
 */

// Approach: Use difference array technique with binary search to determine the minimum number of queries needed to transform the nums array into a Zero Array.
// Time Complexity: O((Q + n) * log(Q)) - Each binary search iteration processes O(Q + n) operations.
// Space Complexity: O(n) - An additional difference array of size n is used.
class Solution {
public:
    int n;
    int Q;

    bool checkWithDifferenceArrayTeq(vector<int>& nums, vector<vector<int> >& queries, int k) {
        vector<int> diff(n, 0);

        //O(Q): Process each query from index 0 to k.
        for (int i = 0; i <= k; i++) {
            int l = queries[i][0];
            int r = queries[i][1];
            int x = queries[i][2];

            diff[l] += x;         // Apply the decrement starting at index l.
            if (r + 1 < n) {
                diff[r + 1] -= x; // End the decrement effect after index r.
            }
        }

        int cumSum = 0;
        //O(n): Build the cumulative sum from the difference array to apply all query effects.
        for (int i = 0; i < n; i++) {
            cumSum += diff[i];
            diff[i] = cumSum;            // diff[i] now holds the total decrement applied at index i.

            if (nums[i] - diff[i] > 0) { // If nums[i] is still positive after applying the decrement.
                return false;
            }
        }

        return true;
    }
    int minZeroArray(vector<int>& nums, vector<vector<int> >& queries) {
        n = nums.size();
        Q = queries.size();

        auto lambda = [](int x) {
                          return x == 0;
                      };

        if (all_of(begin(nums), end(nums), lambda)) {
            return 0;     // No query required because all elements are already zero.
        }

        int l = 0;
        int r = Q - 1;
        int k = -1;
        // Binary search to find the minimum number of queries required.
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (checkWithDifferenceArrayTeq(nums, queries, mid) == true) {
                k = mid + 1;     // Found a valid number of queries (convert 0-indexed mid to count).
                r = mid - 1;     // Try to find a smaller valid k.
            } else {
                l = mid + 1;     // Increase mid since current mid is insufficient.
            }
        }

        return k;
    }
};

/*
 * Dry Run:
 * For example, consider:
 * nums = [2, 0, 2]
 * queries = [[0, 2, 1], [0, 2, 1], [1, 1, 3]]
 *
 * Step 1: Check if nums is already a Zero Array → [2, 0, 2] is not a Zero Array.
 *
 * Step 2: Begin Binary Search:
 * Initialize: l = 0, r = 2, k = -1
 *
 * - First Iteration:
 *       mid = 1 (using queries[0] and queries[1])
 *       Process queries:
 *           Query 0: l=0, r=2, x=1 → diff[0] += 1; diff[3] not applied (index out of bounds).
 *           Query 1: l=0, r=2, x=1 → diff[0] += 1; diff[3] not applied.
 *       Build cumulative sum from diff:
 *           diff[0] = 2, diff[1] = 2, diff[2] = 2.
 *       Evaluate:
 *           index 0: nums[0] - diff[0] = 2 - 2 = 0
 *           index 1: nums[1] - diff[1] = 0 - 2 = -2
 *           index 2: nums[2] - diff[2] = 2 - 2 = 0
 *       All values are ≤ 0, so update k = mid + 1 = 2 and set r = mid - 1 = 0.
 *
 * - Second Iteration:
 *       mid = 0 (testing only query[0])
 *       Process query:
 *           Query 0: l=0, r=2, x=1 → diff[0] += 1; diff[3] not applied.
 *       Build cumulative sum from diff:
 *           diff[0] = 1, diff[1] = 1, diff[2] = 1.
 *       Evaluate:
 *           index 0: nums[0] - diff[0] = 2 - 1 = 1 (positive)
 *       Since condition fails, update l = mid + 1 = 1.
 *
 * Binary search ends with the minimum queries required: k = 2.
 */
