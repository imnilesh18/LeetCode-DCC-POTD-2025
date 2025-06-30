/*
 * 594. Longest Harmonious Subsequence
 *
 * Easy
 *
 * We define a harmonious array as an array where the difference between its maximum value and its minimum value is exactly 1.
 * Given an integer array nums, return the length of its longest harmonious subsequence among all its possible subsequences.
 *
 * Example 1:
 * Input: nums = [1,3,2,2,5,2,3,7]
 * Output: 5
 * Explanation:
 * The longest harmonious subsequence is [3,2,2,2,3].
 *
 * Example 2:
 * Input: nums = [1,2,3,4]
 * Output: 2
 * Explanation:
 * The longest harmonious subsequences are [1,2], [2,3], and [3,4], all of which have a length of 2.
 *
 * Example 3:
 * Input: nums = [1,1,1,1]
 * Output: 0
 * Explanation:
 * No harmonic subsequence exists.
 *
 * Constraints:
 * 1 <= nums.length <= 2 * 10^4
 * -109 <= nums[i] <= 10^9
 */

// Approach: Use a hashmap to count occurrences of each number, then for each number check if num+1 exists and update result with the sum of their counts.
// Time Complexity: O(n), where n is the size of nums, as we traverse the array twice and hashmap operations are O(1) on average.
// Space Complexity: O(n), for storing the frequency of each number in the hashmap.
class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> mp; // Store frequency of each number
        int result = 0;

        // Count occurrences of each number
        for (int& num : nums) {
            mp[num]++;
        }

        // For each number, check if num + 1 exists
        for (int& num : nums) {
            int minNum = num;
            int maxNum = num + 1;

            if (mp.count(maxNum)) { // If num+1 exists in map
                // Update result if this pair forms a longer harmonious subsequence
                result = max(result, mp[minNum] + mp[maxNum]);
            }
        }
        return result; // Return length of the longest harmonious subsequence
    }
};

/*
 *
 * Dry Run
 *
 * Input: nums = [1,3,2,2,5,2,3,7]
 *
 * 1. Build the frequency map:
 *    mp = {1:1, 2:3, 3:2, 5:1, 7:1}
 *
 * 2. Iterate over each number:
 *    For num = 1:
 *       maxNum = 2
 *       mp[1]=1, mp[2]=3 => sum = 4   (result = 4)
 *    For num = 3:
 *       maxNum = 4
 *       mp[4] doesn't exist => skip
 *    For num = 2:
 *       maxNum = 3
 *       mp[2]=3, mp[3]=2 => sum = 5   (result = 5)
 *    (Other numbers either don't have num+1 or don't give higher result)
 *
 * Final result = 5
 * The longest harmonious subsequence is any group with three 2's and two 3's (e.g., [3,2,2,2,3])
 *
 */
