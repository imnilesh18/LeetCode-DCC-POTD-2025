/*
 * 2962. Count Subarrays Where Max Element Appears at Least K Times
 *
 * Medium
 *
 * You are given an integer array nums and a positive integer k.
 * Return the number of subarrays where the maximum element of nums appears at least k times in that subarray.
 * A subarray is a contiguous sequence of elements within an array.
 *
 * Example 1:
 * Input: nums = [1,3,2,3,3], k = 2
 * Output: 6
 * Explanation: The subarrays that contain the element 3 at least 2 times are: [1,3,2,3], [1,3,2,3,3], [3,2,3], [3,2,3,3], [2,3,3] and [3,3].
 *
 * Example 2:
 * Input: nums = [1,4,2,1], k = 3
 * Output: 0
 * Explanation: No subarray contains the element 4 at least 3 times.
 *
 * Constraints:
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^6
 * 1 <= k <= 10^5
 */

// Approach: Sliding window. Maintain a window [i, j] where we count how many times the max element appears. If it appears >= k times, then all subarrays starting from i to j and ending at j to n-1 are valid.
// Time Complexity: O(n), where n is the length of the array. Each element is processed at most twice (once by i and once by j).
// Space Complexity: O(1), no extra space used apart from variables.
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        int n      = nums.size();
        int maxEle = *max_element(begin(nums), end(nums));     // Find the maximum element in the array

        long long result = 0;

        int i     = 0; // Left pointer of the sliding window
        int j     = 0; // Right pointer of the sliding window
        int count = 0; // Count occurrences of maxEle in the current window

        while (j < n) {
            if (nums[j] == maxEle) {
                count++;     // Increase count if maxEle is found at j
            }

            // If count of maxEle >= k, all subarrays [i..j], [i+1..j], ... [j..j] are valid
            while (count >= k) {
                result += (n - j);     // All subarrays starting at i and ending at j to n-1 are valid

                if (nums[i] == maxEle) {
                    count--; // Decrease count if we're moving past a maxEle
                }
                i++;         // Shrink the window from the left
            }
            j++;             // Expand the window from the right
        }
        return result;
    }
};

/*
 *
 * Dry Run
 * Input: nums = [1,3,2,3,3], k = 2
 * maxEle = 3
 *
 * i = 0, j = 0: nums[0] = 1 → not max → count = 0
 * i = 0, j = 1: nums[1] = 3 → count = 1
 * i = 0, j = 2: nums[2] = 2 → count = 1
 * i = 0, j = 3: nums[3] = 3 → count = 2 (>=k), add (5-3)=2 to result → result = 2
 * nums[i]=1, not max → i=1 → still count=2, add (5-3)=2 → result = 4
 * nums[i]=3 → count=1 → i=2
 * j = 4: nums[4]=3 → count=2 again (>=k), add (5-4)=1 → result = 5
 * nums[i]=2, not max → i=3 → still count=2, add (5-4)=1 → result = 6
 * nums[i]=3 → count=1 → i=4
 *
 * Final result = 6
 *
 */
