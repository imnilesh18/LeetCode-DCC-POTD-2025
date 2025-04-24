/*
 * 2799. Count Complete Subarrays in an Array
 *
 * Medium
 *
 * You are given an array nums consisting of positive integers.
 * We call a subarray of an array complete if the following condition is satisfied:
 * The number of distinct elements in the subarray is equal to the number of distinct elements in the whole array.
 * Return the number of complete subarrays.
 * A subarray is a contiguous non-empty part of an array.
 *
 * Example 1:
 * Input: nums = [1,3,1,2,2]
 * Output: 4
 * Explanation: The complete subarrays are the following: [1,3,1,2], [1,3,1,2,2], [3,1,2] and [3,1,2,2].
 *
 * Example 2:
 * Input: nums = [5,5,5,5]
 * Output: 10
 * Explanation: The array consists only of the integer 5, so any subarray is complete. The number of subarrays that we can choose is 10.
 *
 * Constraints:
 * 1 <= nums.length <= 1000
 * 1 <= nums[i] <= 2000
 */

// Approach: Use sliding window technique with two pointers. First, count the number of distinct elements in the array. Then use a window to track when we hit the same number of distinct elements in a subarray and count all such valid subarrays.
// Time Complexity: O(n^2) in the worst case, as for every window we might shrink the left pointer n times.
// Space Complexity: O(n) for the hashmap and set used to track counts and distinct elements.
class Solution {
public:
    int countCompleteSubarrays(vector<int>& nums) {
        int n = nums.size();

        // Create a set of unique elements to get the total number of distinct elements in the array
        unordered_set<int> st(begin(nums), end(nums));
        int c = st.size();     // 'c' is the number of distinct elements in the whole array

        int i   = 0;
        int j   = 0;
        int res = 0;

        unordered_map<int, int> mp;     // hashmap to count frequency of elements in current window

        while (j < n) {
            mp[nums[j]]++;     // add current element to map and update frequency

            // When window has same number of distinct elements as the entire array
            while (mp.size() == c) {
                res += (n - j);     // all subarrays starting from i and ending at j to n-1 are valid

                // shrink window from left
                mp[nums[i]]--;
                if (mp[nums[i]] == 0) {
                    mp.erase(nums[i]); // remove element if its count becomes 0
                }
                i++;                   // move left pointer
            }
            j++;                       // move right pointer
        }
        return res;
    }
};

/*
 *
 * Dry Run
 * Input: nums = [1,3,1,2,2]
 * Step 1: Count total distinct elements = 3 => {1,2,3}
 * Initialize i = 0, j = 0, res = 0, mp = {}
 *
 * Iteration 1: j = 0, nums[j] = 1 → mp = {1:1}
 * Iteration 2: j = 1, nums[j] = 3 → mp = {1:1, 3:1}
 * Iteration 3: j = 2, nums[j] = 1 → mp = {1:2, 3:1}
 * Iteration 4: j = 3, nums[j] = 2 → mp = {1:2, 3:1, 2:1}
 *  mp.size() == c → res += (5 - 3) = 2 → res = 2
 *  Shrink from i=0: mp[1]-- → mp = {1:1, 3:1, 2:1}
 *  Still valid: res += (5 - 3) = 2 → res = 4
 *  Shrink from i=1: mp[3]-- → mp = {1:1, 3:0, 2:1} → remove 3
 *  mp.size() < c → break
 *
 * Iteration 5: j = 4, nums[j] = 2 → mp = {1:1, 2:2}
 *  mp.size() = 2 < c → do nothing
 *
 * Final result = 4
 *
 */
