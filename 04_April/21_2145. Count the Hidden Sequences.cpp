/*
 * 2145. Count the Hidden Sequences
 *
 * Medium
 *
 * You are given a 0-indexed array of n integers differences, which describes the differences between each pair of consecutive integers of a hidden sequence of length (n + 1). More formally, call the hidden sequence hidden, then we have that differences[i] = hidden[i + 1] - hidden[i].
 *
 * You are further given two integers lower and upper that describe the inclusive range of values [lower, upper] that the hidden sequence can contain.
 *
 * For example, given differences = [1, -3, 4], lower = 1, upper = 6, the hidden sequence is a sequence of length 4 whose elements are in between 1 and 6 (inclusive).
 * [3, 4, 1, 5] and [4, 5, 2, 6] are possible hidden sequences.
 * [5, 6, 3, 7] is not possible since it contains an element greater than 6.
 * [1, 2, 3, 4] is not possible since the differences are not correct.
 * Return the number of possible hidden sequences there are. If there are no possible sequences, return 0.
 *
 * Example 1:
 * Input: differences = [1,-3,4], lower = 1, upper = 6
 * Output: 2
 * Explanation: The possible hidden sequences are:
 * - [3, 4, 1, 5]
 * - [4, 5, 2, 6]
 * Thus, we return 2.
 *
 * Example 2:
 * Input: differences = [3,-4,5,1,-2], lower = -4, upper = 5
 * Output: 4
 * Explanation: The possible hidden sequences are:
 * - [-3, 0, -4, 1, 2, 0]
 * - [-2, 1, -3, 2, 3, 1]
 * - [-1, 2, -2, 3, 4, 2]
 * - [0, 3, -1, 4, 5, 3]
 * Thus, we return 4.
 *
 * Example 3:
 * Input: differences = [4,-7,2], lower = 3, upper = 6
 * Output: 0
 * Explanation: There are no possible hidden sequences. Thus, we return 0.
 *
 * Constraints:
 * n == differences.length
 * 1 <= n <= 10^5
 * -10^5 <= differences[i] <= 10^5
 * -10^5 <= lower <= upper <= 10^5
 */

// Intuition: 

/*
 * differences = {a, b, c, d, ...}
 *
 * upper = U
 * lower = L
 *
 * arr = { a[0], a[1], a[2], ...}
 *
 * diff[0] = a[1] - a[0]
 * diff[1] = a[2] - a[1]
 * ...
 * if we are able to find a[0] then we will be able to get all the other elements like
 *
 * differences = {a, b, c, d, ...}
 *                ^ \
 *                |  \
 * arr =          {a[0], a[1], a[2], ...}
 *
 * diff[0] = a[1] - a[0]
 * a[1] = diff[0] + a[0]
 * if we know a[0] then add diff[0] we will be able to get a[1], similarly
 * diff[1] = a[2] - a[1]
 * a[2] = diff[1] + a[1]
 * and so on we will get all the elements
 *
 * first element : a[0]
 *
 * L <= a[0] <= U
 *
 * a[0] = 0
 * a[1] = diff[0] + a[0]
 * a[2] = diff[1] + a[1]
 *
 * arr = {a[0], a[1], a[2], a[3], ...}
 *          |     |     |     |
 *          α     α     α     α
 *
 * diff = [1, -3, 4]
 * arr  = [3,  4,  1,  5]
 *        |   |   |   |
 *        α=1 α=1 α=1 α=1
 *       =[4,  5,  2,  6]
 *
 * hence, adding alpha is giving the same difference
 * but we have to check lower and upper
 *
 * if α=2
 * [5, 6, 3, 7] {wrong}
 * L = 1, U = 6
 *
 * [4,  5,  2,  6] maxValue = 6
 *                    + α > U (This should not happen)
 * same if we take α = -2
 * [1, 2, -1, 3]   minValue = -1
 *                   - α < L (This should not happen)
 *                        (But here it's happening)
 * So basically whatever constant value we are adding or subtracting should be in the range [L, U]
 *
 * L <= a[i] + α <= U
 *
 * maxVal + α <= U
 * minVal + α >= L
 *
 * α <= U - maxVal
 * α >= L - minVal
 *
 * α ∈ [L - minVal, U - maxVal]
 *       a             b
 *
 * R ∈ [a, b]
 * then total elements = b - a + 1
 *
 * Total = b - a + 1
 *       = (U - maxVal) - (L - minVal) + 1
 * if Total <= 0 then invalid
 *
 * ----------------------
 * diff = [1, -3, 4]
 * L = 1
 * U = 6
 *
 * curr = 0          // arr[0]
 * curr + d[0] = a[1] = 0 + 1 = 1
 * minVal = min(minVal, curr)  // 0
 * maxVal = max(maxVal, curr)  // 1
 *
 * if ((U - maxVal) - (L - minVal) + 1 <= 0) {
 *     return 0;
 * }
 *
 * curr = 1
 * curr + d[1] = 1 + (-3) = -2
 * minVal = min(minVal, curr)  // -2
 * maxVal = max(maxVal, curr)  // 1
 *
 * if ((U - maxVal) - (L - minVal) + 1 <= 0) {
 *     return 0;
 * }
 *
 * similarly do the same for remaining differences
 * and at last return (U - maxVal) - (L - minVal) + 1;
 */

// Approach: Use prefix sums of differences to track minimum and maximum relative offsets; the count of valid starting values is the size of the intersection range [lower - minPrefix, upper - maxPrefix].
// Time Complexity: O(n), where n = differences.size(), since we process each difference exactly once.
// Space Complexity: O(1), using only a few integer variables.
class Solution {
public:
    int numberOfArrays(vector<int>& differences, int lower, int upper) {
        int curr   = 0;              // current prefix sum relative to hidden[0]
        int minVal = 0;              // minimum prefix sum seen so far
        int maxVal = 0;              // maximum prefix sum seen so far

        for (int& d : differences) {
            curr   = curr + d;                           // update prefix sum by adding the next difference
            minVal = min(minVal, curr);                  // update minimum prefix sum
            maxVal = max(maxVal, curr);                  // update maximum prefix sum

            // If the possible starting value range is empty, we can return 0 immediately
            if ((upper - maxVal) - (lower - minVal) + 1 <= 0) {
                return 0;
            }
        }
        // The number of valid starting values = size of [lower - minVal, upper - maxVal]
        return (upper - maxVal) - (lower - minVal) + 1;
    }
};

/*
 *
 * Dry Run
 *
 * differences = [1, -3, 4], lower = 1, upper = 6
 * Initialize: curr = 0, minVal = 0, maxVal = 0
 *
 * 1) d =  1
 *    curr   = 0 + 1 = 1
 *    minVal = min(0, 1) = 0
 *    maxVal = max(0, 1) = 1
 *    valid α range = [lower - minVal, upper - maxVal] = [1 - 0, 6 - 1] = [1, 5]  → size = 5 (>0)
 *
 * 2) d = -3
 *    curr   = 1 + (-3) = -2
 *    minVal = min(0, -2) = -2
 *    maxVal = max(1, -2) = 1
 *    valid α range = [1 - (-2), 6 - 1] = [3, 5]  → size = 3 (>0)
 *
 * 3) d =  4
 *    curr   = -2 + 4 = 2
 *    minVal = min(-2, 2) = -2
 *    maxVal = max(1, 2) = 2
 *    valid α range = [1 - (-2), 6 - 2] = [3, 4]  → size = 2 (>0)
 *
 * Return 2  // there are 2 valid starting values: hidden[0] = 3 or 4
 *
 */
