/*
 * 1780. Check if Number is a Sum of Powers of Three
 *
 * Given an integer n, return true if it is possible to represent n as the sum of distinct powers of three. Otherwise, return false.
 *
 * An integer y is a power of three if there exists an integer x such that y == 3x.
 *
 * Example 1:
 * Input: n = 12
 * Output: true
 * Explanation: 12 = 31 + 32
 *
 * Example 2:
 * Input: n = 91
 * Output: true
 * Explanation: 91 = 30 + 32 + 34
 *
 * Example 3:
 * Input: n = 21
 * Output: false
 *
 * Constraints:
 * 1 <= n <= 10^7
 */

// Approach 1: Find the smallest power p such that 3^p > n, then subtract the largest possible distinct powers of 3 from n.
// Time Complexity: O(log₃(n)) because we iterate over the powers of 3 until reaching n.
// Space Complexity: O(1) as only a constant amount of extra space is used.
class Solution {
public:
    bool checkPowersOfThree(int n) {
        int p = 0;

        // Find the smallest power p such that 3^p > n
        while (pow(3, p) <= n) {
            p++;
        }

        // Subtract powers of 3 from n starting from the highest power found
        while (n > 0) {
            // If the current power of 3 can be subtracted from n, do it
            if (pow(3, p) <= n) {
                n = n - pow(3, p);
            }
            // If after subtraction the same power can still be subtracted,
            // it means the same power would have to be used twice which is not allowed.
            if (pow(3, p) <= n) {
                return false;
            }
            p--;     // Move to the next lower power of 3
        }
        return true;
    }
};

/*
 * Dry Run:
 * For n = 12:
 * 1. Initialize p = 0.
 * 2. Find maximum power:
 * - p = 0: 3^0 = 1 <= 12, so p becomes 1.
 * - p = 1: 3^1 = 3 <= 12, so p becomes 2.
 * - p = 2: 3^2 = 9 <= 12, so p becomes 3.
 * - p = 3: 3^3 = 27 > 12, exit loop (p remains 3).
 * 3. Process subtraction:
 * - p = 3: 3^3 = 27 > 12, cannot subtract; decrement p to 2.
 * - p = 2: 3^2 = 9 <= 12, subtract: n = 12 - 9 = 3.
 *           Then, 3^2 = 9 > 3, so no duplicate subtraction; decrement p to 1.
 * - p = 1: 3^1 = 3 <= 3, subtract: n = 3 - 3 = 0.
 *           Then, 3^1 = 3 > 0; decrement p to 0.
 * 4. n becomes 0, so the function returns true.
 */
