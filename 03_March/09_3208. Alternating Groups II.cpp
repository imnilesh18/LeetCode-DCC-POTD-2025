/*
 * 3208. Alternating Groups II
 *
 * There is a circle of red and blue tiles. You are given an array of integers colors and an integer k. The color of tile i is represented by colors[i]:
 * colors[i] == 0 means that tile i is red.
 * colors[i] == 1 means that tile i is blue.
 * An alternating group is every k contiguous tiles in the circle with alternating colors (each tile in the group except the first and last one has a different color from its left and right tiles).
 * Return the number of alternating groups.
 * Note that since colors represents a circle, the first and the last tiles are considered to be next to each other.
 *
 * Example 1:
 * Input: colors = [0,1,0,1,0], k = 3
 * Output: 3
 *
 * Example 2:
 * Input: colors = [0,1,0,0,1,0,1], k = 6
 * Output: 2
 *
 * Example 3:
 * Input: colors = [1,1,0,1], k = 4
 * Output: 0
 *
 * Constraints:
 * 3 <= colors.length <= 10^5
 * 0 <= colors[i] <= 1
 * 3 <= k <= colors.length
 */

// Approach: Use two passes to count the length of contiguous alternating segments, and then handle the wrap-around case for the circular array.
// Time Complexity: O(n) - we traverse the array twice at most.
// Space Complexity: O(1) - only a few extra variables are used.
class Solution {
public:
    int numberOfAlternatingGroups(vector<int>& colors, int k) {
        int n      = colors.size();
        int result = 0;
        int length = 1;         // Initialize length with the first element (index 0)
        int last   = colors[0]; // Set the last seen color to the first element

        // 1st pass: Process the array linearly to count alternating groups
        for (int i = 1; i < n; i++) {
            // If the current color is the same as the last, reset the alternating length
            if (colors[i] == last) {
                length = 1;
                last   = colors[i];
                continue;
            }
            // Otherwise, increase the length of the current alternating segment
            length++;
            // If the current segment's length is at least k, count it as a valid group
            if (length >= k) {
                result++;
            }
            last = colors[i];
        }

        // 2nd pass: Check the beginning of the array to account for circular wrap-around groups
        for (int i = 0; i < k - 1; i++) {     // Check the first k - 1 elements
            // If the current element breaks the alternation, reset and exit early
            if (colors[i] == last) {
                length = 1;
                last   = colors[i];
                break;     // Early break: if alternation is broken, no wrap-around group can be formed
            }
            // Increase the length for the wrap-around segment
            length++;
            // If the segment length reaches or exceeds k, count it as a valid group
            if (length >= k) {
                result++;
            }
            last = colors[i];
        }
        return result;
    }
};

/*
 * Dry Run:
 * Example: colors = [0,1,0,1,0], k = 3
 *
 * Initial State:
 * n = 5, result = 0, length = 1, last = 0
 *
 * First Pass:
 * i = 1:
 *  colors[1] = 1, last = 0 (different) → length becomes 2
 *  2 < 3 so result remains 0, update last = 1
 * i = 2:
 *  colors[2] = 0, last = 1 (different) → length becomes 3
 *  3 >= 3 so result increments to 1, update last = 0
 * i = 3:
 *  colors[3] = 1, last = 0 (different) → length becomes 4
 *  4 >= 3 so result increments to 2, update last = 1
 * i = 4:
 *  colors[4] = 0, last = 1 (different) → length becomes 5
 *  5 >= 3 so result increments to 3, update last = 0
 *
 * Second Pass (Wrap-around):
 * i = 0: (checking first k - 1 = 2 elements)
 *  colors[0] = 0, last = 0 (same) → reset length to 1, update last = 0, break out of loop
 *
 * Final result returned is 3.
 */
