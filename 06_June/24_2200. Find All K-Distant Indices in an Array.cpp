/*
 * 2200. Find All K-Distant Indices in an Array
 *
 * Easy
 *
 * You are given a 0-indexed integer array nums and two integers key and k. A k-distant index is an index i of nums for which there exists at least one index j such that |i - j| <= k and nums[j] == key.
 *
 * Return a list of all k-distant indices sorted in increasing order.
 *
 * Example 1:
 * Input: nums = [3,4,9,1,3,9,5], key = 9, k = 1
 * Output: [1,2,3,4,5,6]
 * Explanation: Here, nums[2] == key and nums[5] == key.
 * - For index 0, |0 - 2| > k and |0 - 5| > k, so there is no j where |0 - j| <= k and nums[j] == key. Thus, 0 is not a k-distant index.
 * - For index 1, |1 - 2| <= k and nums[2] == key, so 1 is a k-distant index.
 * - For index 2, |2 - 2| <= k and nums[2] == key, so 2 is a k-distant index.
 * - For index 3, |3 - 2| <= k and nums[2] == key, so 3 is a k-distant index.
 * - For index 4, |4 - 5| <= k and nums[5] == key, so 4 is a k-distant index.
 * - For index 5, |5 - 5| <= k and nums[5] == key, so 5 is a k-distant index.
 * - For index 6, |6 - 5| <= k and nums[5] == key, so 6 is a k-distant index.
 * Thus, we return [1,2,3,4,5,6] which is sorted in increasing order.
 *
 * Example 2:
 * Input: nums = [2,2,2,2,2], key = 2, k = 2
 * Output: [0,1,2,3,4]
 * Explanation: For all indices i in nums, there exists some index j such that |i - j| <= k and nums[j] == key, so every index is a k-distant index.
 * Hence, we return [0,1,2,3,4].
 *
 * Constraints:
 * 1 <= nums.length <= 1000
 * 1 <= nums[i] <= 1000
 * key is an integer from the array nums.
 * 1 <= k <= nums.length
 */

// Approach: Iterate through the array and for every occurrence of `key`, mark the range [j-k, j+k] as valid indices and push them to the result. To avoid duplicates, adjust the start using result.back().
// Time Complexity: O(n), where n is the size of the array. Each element is visited at most twice.
// Space Complexity: O(1) extra space (excluding result vector).

class Solution {
public:
    vector<int> findKDistantIndices(vector<int>& nums, int key, int k) {
        int         n = nums.size();
        vector<int> result;

        for (int j = 0; j < n; j++) {
            // Check if the current element is equal to key
            if (nums[j] == key) {
                // Define the valid range [start, end] around index j
                int start = max(j - k, 0);
                int end   = min(j + k, n - 1);

                // Avoid pushing duplicate indices already in result
                if (result.size() > 0 && result.back() >= start) {
                    start = result.back() + 1;
                }

                // Add all valid indices in the range [start, end]
                for (int i = start; i <= end; i++) {
                    result.push_back(i);
                }
            }
        }
        return result;
    }
};

/*
 *
 * Dry Run
 * Input: nums = [3,4,9,1,3,9,5], key = 9, k = 1
 * Step 1: j = 0 to 6, find nums[j] == 9 → j = 2 and j = 5
 *
 * For j = 2:
 *   start = max(2 - 1, 0) = 1
 *   end = min(2 + 1, 6) = 3
 *   Push i from 1 to 3 → result = [1, 2, 3]
 *
 * For j = 5:
 *   start = max(5 - 1, 0) = 4
 *   end = min(5 + 1, 6) = 6
 *   result.back() = 3, so start remains 4
 *   Push i from 4 to 6 → result = [1, 2, 3, 4, 5, 6]
 *
 * Final Output: [1, 2, 3, 4, 5, 6]
 */
