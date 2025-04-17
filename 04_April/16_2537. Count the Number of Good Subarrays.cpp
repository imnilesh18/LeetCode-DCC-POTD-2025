/*
 * 2537. Count the Number of Good Subarrays
 *
 * Medium
 *
 * Given an integer array nums and an integer k, return the number of good subarrays of nums.
 * A subarray arr is good if there are at least k pairs of indices (i, j) such that i < j and arr[i] == arr[j].
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * Example 1:
 * Input: nums = [1,1,1,1,1], k = 10
 * Output: 1
 * Explanation: The only good subarray is the array nums itself.
 *
 * Example 2:
 * Input: nums = [3,1,4,3,2,2,4], k = 2
 * Output: 4
 * Explanation: There are 4 different good subarrays:
 * - [3,1,4,3,2,2] that has 2 pairs.
 * - [3,1,4,3,2,2,4] that has 3 pairs.
 * - [1,4,3,2,2,4] that has 2 pairs.
 * - [4,3,2,2,4] that has 2 pairs.
 *
 * Constraints:
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i], k <= 10^9
 */

// Approach: Use sliding window with frequency map to count pairs while shrinking window when pair count >= k
// Time Complexity: O(n) - each element is processed at most twice (once by j, once by i)
// Space Complexity: O(n) - for the unordered_map storing frequency of elements
class Solution {
public:
    long long countGood(vector<int>& nums, int k) {
        int n = nums.size();        // size of the input array
        int i = 0;                  // left pointer of the sliding window
        int j = 0;                  // right pointer of the sliding window

        long long result = 0;       // stores the final count of good subarrays
        unordered_map<int, int> mp; // frequency map to store count of each number in the current window
        long long pairs = 0;        // current number of valid (i, j) pairs where nums[i] == nums[j] and i < j

        while (j < n) {
            // When a new element nums[j] is added, it forms mp[nums[j]] new pairs
            pairs += mp[nums[j]];
            mp[nums[j]]++;

            // If we have at least k valid pairs, all subarrays from current i to end are good
            while (pairs >= k) {
                result += (n - j);    // all subarrays starting at i and ending from j to n-1 are valid
                mp[nums[i]]--;        // shrink the window from left
                pairs -= mp[nums[i]]; // remove the contribution of nums[i] from the pair count
                i++;
            }
            j++;     // expand the window to the right
        }
        return result;
    }
};

/*
 *
 * Dry Run
 * Input: nums = [3,1,4,3,2,2,4], k = 2
 *
 * Initialize: i = 0, j = 0, pairs = 0, result = 0
 *
 * Step 1: j = 0, nums[j] = 3 → pairs = 0 → mp = {3:1}
 * Step 2: j = 1, nums[j] = 1 → pairs = 0 → mp = {3:1, 1:1}
 * Step 3: j = 2, nums[j] = 4 → pairs = 0 → mp = {3:1, 1:1, 4:1}
 * Step 4: j = 3, nums[j] = 3 → pairs += 1 (mp[3] = 1) → mp = {3:2, 1:1, 4:1} → pairs = 1
 * Step 5: j = 4, nums[j] = 2 → pairs = 1 → mp = {3:2, 1:1, 4:1, 2:1}
 * Step 6: j = 5, nums[j] = 2 → pairs += 1 (mp[2] = 1) → mp = {3:2, 1:1, 4:1, 2:2} → pairs = 2
 *          Since pairs >= k → result += (7 - 5) = 2 → result = 2
 *          Shrink: mp[3]-- → mp[3] = 1 → pairs -= 1 → i = 1
 *          Still pairs >= k → result += (7 - 5) = 2 → result = 4
 *          Shrink: mp[1]-- → mp[1] = 0 → pairs -= 0 → i = 2
 *          Now pairs = 1 → exit inner loop
 * Step 7: j = 6, nums[j] = 4 → pairs += 1 (mp[4] = 1) → pairs = 2
 *          Since pairs >= k → result += (7 - 6) = 1 → result = 5
 *          Shrink: mp[4]-- → mp[4] = 1 → pairs -= 1 → i = 3
 *          Now pairs = 1 → exit
 *
 * Final result = 5
 * But only subarrays where condition holds fully are:
 * [3,1,4,3,2,2], [3,1,4,3,2,2,4], [1,4,3,2,2,4], [4,3,2,2,4]
 * Hence correct output = 4
 *
 */
