/*
 * 2616. Minimize the Maximum Difference of Pairs
 *
 * Medium
 *
 * You are given a 0-indexed integer array nums and an integer p. Find p pairs of indices of nums such that the maximum difference amongst all the pairs is minimized. Also, ensure no index appears more than once amongst the p pairs.
 * Note that for a pair of elements at the index i and j, the difference of this pair is |nums[i] - nums[j]|, where |x| represents the absolute value of x.
 * Return the minimum maximum difference among all p pairs. We define the maximum of an empty set to be zero.
 *
 * Example 1:
 * Input: nums = [10,1,2,7,1,3], p = 2
 * Output: 1
 * Explanation: The first pair is formed from the indices 1 and 4, and the second pair is formed from the indices 2 and 5.
 * The maximum difference is max(|nums[1] - nums[4]|, |nums[2] - nums[5]|) = max(0, 1) = 1. Therefore, we return 1.
 *
 * Example 2:
 * Input: nums = [4,2,1,2], p = 1
 * Output: 0
 * Explanation: Let the indices 1 and 3 form a pair. The difference of that pair is |2 - 2| = 0, which is the minimum we can attain.
 *
 * Constraints:
 *
 * 1 <= nums.length <= 10^5
 * 0 <= nums[i] <= 10^9
 * 0 <= p <= (nums.length)/2
 */

// Approach: Binary Search on answer + Greedy. Sort the array, and binary search on the maximum allowed difference. Use a greedy method to try to form p pairs with difference <= mid.
// Time Complexity: O(n log n), due to sorting and binary search on range of differences.
// Space Complexity: O(1), no extra space apart from input.
class Solution {
public:
    int n;

    // Helper function to check if we can form at least p pairs with max difference <= mid
    bool isValid(vector<int>& nums, int mid, int p) {
        int i     = 0;
        int pairs = 0;

        // Iterate greedily to form pairs
        while (i < n - 1) {
            // If the adjacent elements have difference <= mid, count it as a pair
            if (nums[i + 1] - nums[i] <= mid) {
                pairs++;
                i += 2; // move past both indices since no index can be reused
            } else {
                i++;    // skip only one index and check again
            }
        }

        // Return whether we could form at least p valid pairs
        return pairs >= p;
    }
    
    int minimizeMax(vector<int>& nums, int p) {
        n = nums.size();

        // Sort to pair closer numbers together
        sort(begin(nums), end(nums));

        int l      = 0;                     // minimum possible max difference
        int r      = nums[n - 1] - nums[0]; // maximum possible max difference
        int result = INT_MAX;

        // Binary search to minimize the max difference
        while (l <= r) {
            int mid = l + (r - l) / 2;

            // If mid is a valid max diff, try smaller value
            if (isValid(nums, mid, p)) {
                result = mid;
                r      = mid - 1;
            } else {
                // Else, we need to allow a bigger difference
                l = mid + 1;
            }
        }

        return result;
    }
};
