/*
 * 2411. Smallest Subarrays With Maximum Bitwise OR
 *
 * Medium
 *
 * You are given a 0-indexed array nums of length n, consisting of non-negative integers. For each index i from 0 to n - 1, you must determine the size of the minimum sized non-empty subarray of nums starting at i (inclusive) that has the maximum possible bitwise OR.
 *
 * In other words, let Bij be the bitwise OR of the subarray nums[i...j]. You need to find the smallest subarray starting at i, such that bitwise OR of this subarray is equal to max(Bik) where i <= k <= n - 1.
 * The bitwise OR of an array is the bitwise OR of all the numbers in it.
 *
 * Return an integer array answer of size n where answer[i] is the length of the minimum sized subarray starting at i with maximum bitwise OR.
 *
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * Example 1:
 * Input: nums = [1,0,2,1,3]
 * Output: [3,3,2,2,1]
 * Explanation:
 * The maximum possible bitwise OR starting at any index is 3.
 * - Starting at index 0, the shortest subarray that yields it is [1,0,2].
 * - Starting at index 1, the shortest subarray that yields the maximum bitwise OR is [0,2,1].
 * - Starting at index 2, the shortest subarray that yields the maximum bitwise OR is [2,1].
 * - Starting at index 3, the shortest subarray that yields the maximum bitwise OR is [1,3].
 * - Starting at index 4, the shortest subarray that yields the maximum bitwise OR is [3].
 * Therefore, we return [3,3,2,2,1].
 *
 * Example 2:
 * Input: nums = [1,2]
 * Output: [2,1]
 * Explanation:
 * Starting at index 0, the shortest subarray that yields the maximum bitwise OR is of length 2.
 * Starting at index 1, the shortest subarray that yields the maximum bitwise OR is of length 1.
 * Therefore, we return [2,1].
 *
 * Constraints:
 * n == nums.length
 * 1 <= n <= 10^5
 * 0 <= nums[i] <= 10^9
 */

// Intuition: The bitwise OR of a subarray is monotonically increasing as we add more elements from right to left. This means the maximum possible OR for any subarray starting at index `i` is the OR of the entire suffix `nums[i...n-1]`. The problem is to find the shortest subarray `nums[i...j]` that achieves this maximum OR value. We can solve this efficiently by iterating backward and keeping track of the nearest future index for each bit.
// Approach:
// 1. We iterate backward from the end of the array (`i = n-1` to `0`).
// 2. We use an array `setBitIndex` of size 32. `setBitIndex[j]` will store the index of the rightmost number we have seen so far that has the `j`-th bit set.
// 3. For each index `i`, we need to find the smallest `j >= i` such that the bitwise OR of `nums[i...j]` is maximized.
// 4. The current number `nums[i]` contributes certain bits. For any bit `b` that `nums[i]` is missing, we must extend our subarray to the right to include a number that has bit `b`. The closest such number is at index `setBitIndex[b]`.
// 5. Therefore, the required end index `j` for our subarray is the maximum of `i` and all the `setBitIndex[b]` for the bits `b` that `nums[i]` lacks.
// 6. After calculating the length for `i`, we update `setBitIndex` for all the bits that are present in `nums[i]`, setting their last seen position to `i`.
// Time Complexity: O(N * 32) -> O(N), where N is the number of elements in `nums`. We iterate through the array once, and for each element, we perform a constant number of operations (iterating through 32 bits).
// Space Complexity: O(1). We use an auxiliary array `setBitIndex` of fixed size 32, which is constant space. The output array `result` is not counted in auxiliary space complexity.
class Solution {
public:
    vector<int> smallestSubarrays(vector<int>& nums) {
        int n = nums.size();   // Get the size of the input array

        vector<int> result(n); // Initialize the result array to store the lengths

        // This array stores the most recent (rightmost) index where a specific bit was set.
        vector<int> setBitIndex(32, -1);

        //setBitIndex[j] = k means that as of our current position `i`, the j-th bit can be set by the element at index `k` where k >= i.

        // Iterate backwards from the end of the array to leverage previously computed information.
        for (int i = n - 1; i >= 0; i--) {
            // The required subarray must at least include the current element, so the end index is at least `i`.
            int endIndex = i;
            // Iterate through all 32 possible bits for a non-negative integer.
            for (int j = 0; j < 32; j++) {
                // Check if the j-th bit is NOT set in the current number nums[i].
                if (!(nums[i] & (1 << j))) {
                    // If the j-th bit is not set, we need to extend our subarray to include a number that has this bit.
                    // `setBitIndex[j]` holds the closest index to the right (>= i) with the j-th bit set.
                    if (setBitIndex[j] != -1) { // Check if we have seen such an index.
                        // The subarray must extend to at least this index. We take the maximum needed end index.
                        endIndex = max(endIndex, setBitIndex[j]);
                    }
                } else {
                    // If the j-th bit IS set in nums[i], update the last seen index for this bit to the current index `i`.
                    setBitIndex[j] = i;
                }
            }

            // The length of the smallest subarray is the distance from i to the calculated furthest required index.
            result[i] = endIndex - i + 1;
        }

        return result; // Return the final array of lengths.
    }
};

/*
 * Dry Run with nums = [1, 0, 2, 1, 3]
 * n = 5
 * result = vector of size 5
 * setBitIndex = vector of size 32, all initialized to -1
 *
 * i = 4 (nums[4] = 3, binary 011):
 * endIndex = 4
 * nums[4] has bits 0 and 1 set.
 * Update setBitIndex: setBitIndex[0] = 4, setBitIndex[1] = 4.
 * endIndex remains 4.
 * result[4] = 4 - 4 + 1 = 1.
 *
 * i = 3 (nums[3] = 1, binary 001):
 * endIndex = 3
 * nums[3] lacks bit 1. The closest index for bit 1 is setBitIndex[1] = 4.
 * endIndex = max(3, 4) = 4.
 * Update setBitIndex for bit 0: setBitIndex[0] = 3. (setBitIndex[1] is still 4).
 * result[3] = 4 - 3 + 1 = 2.
 *
 * i = 2 (nums[2] = 2, binary 010):
 * endIndex = 2
 * nums[2] lacks bit 0. The closest index for bit 0 is setBitIndex[0] = 3.
 * endIndex = max(2, 3) = 3.
 * Update setBitIndex for bit 1: setBitIndex[1] = 2. (setBitIndex[0] is still 3).
 * result[2] = 3 - 2 + 1 = 2.
 *
 * i = 1 (nums[1] = 0, binary 000):
 * endIndex = 1
 * nums[1] lacks bit 0 (closest at setBitIndex[0] = 3) and bit 1 (closest at setBitIndex[1] = 2).
 * endIndex = max(1, 3) = 3.
 * endIndex = max(3, 2) = 3.
 * No bits in nums[1] to update setBitIndex with.
 * result[1] = 3 - 1 + 1 = 3.
 *
 * i = 0 (nums[0] = 1, binary 001):
 * endIndex = 0
 * nums[0] lacks bit 1. The closest index for bit 1 is setBitIndex[1] = 2.
 * endIndex = max(0, 2) = 2.
 * Update setBitIndex for bit 0: setBitIndex[0] = 0.
 * result[0] = 2 - 0 + 1 = 3.
 *
 * Final Result: [3, 3, 2, 2, 1]
 */
