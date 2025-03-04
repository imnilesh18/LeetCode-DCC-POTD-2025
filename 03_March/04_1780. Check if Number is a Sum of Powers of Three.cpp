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

// Approach 2: Convert n to its base-3 representation and ensure no digit equals 2, because a valid sum of distinct powers of three only uses 0s and 1s.
// Time Complexity: O(log₃(n)) since n is divided by 3 in every iteration.
// Space Complexity: O(1) as only a constant amount of extra space is used.
class Solution {
public:
    bool checkPowersOfThree(int n) {
        while (n > 0) {
            // If the current digit in base-3 is 2, n cannot be represented as a sum of distinct powers of three.
            if (n % 3 == 2) {
                return false;
            }
            // Move to the next digit by dividing n by 3.
            n = n / 3;
        }
        return true;
    }
};

/*
 * Dry Run:
 * Example 1: n = 12
 * 1. n = 12, 12 % 3 = 0 (valid), update n = 12 / 3 = 4.
 * 2. n = 4, 4 % 3 = 1 (valid), update n = 4 / 3 = 1.
 * 3. n = 1, 1 % 3 = 1 (valid), update n = 1 / 3 = 0.
 * 4. n becomes 0, function returns true.
 *
 * Example 2: n = 21
 * 1. n = 21, 21 % 3 = 0 (valid), update n = 21 / 3 = 7.
 * 2. n = 7, 7 % 3 = 1 (valid), update n = 7 / 3 = 2.
 * 3. n = 2, 2 % 3 = 2 (invalid), function returns false.
 */

// Approach 3: Use recursion to explore all combinations of distinct powers of three, either subtracting the current power (3^p) or skipping it, until n is reduced to 0.
// Time Complexity: O(2^(log₃(n))) in the worst case since at each power we make two recursive calls, where the number of powers is proportional to log₃(n).
// Space Complexity: O(log₃(n)) due to the recursion stack depth.
class Solution {
public:
    int solve(int n, int p) {
        // Base Case: If n becomes 0, we have successfully represented it as a sum of powers of three.
        if (n == 0) {
            return true;
        }

        // If the current power 3^p is greater than n, it's not possible to continue.
        if (pow(3, p) > n) {
            return false;
        }

        // Choose to subtract the current power of three and move to the next power.
        bool take = solve(n - pow(3, p), p + 1);
        // Or choose to skip the current power of three and move to the next power.
        bool not_take = solve(n, p + 1);

        // If either choice results in a valid representation, return true.
        return take || not_take;
    }
    bool checkPowersOfThree(int n) {
        return solve(n, 0);
    }
};

/*
 * Dry Run:
 * Example: n = 12
 * 1. Call solve(12, 0):
 * - Current power: 3^0 = 1, which is ≤ 12.
 * - Two recursive calls are made:
 *   a) take: solve(12 - 1, 1) => solve(11, 1)
 *   b) not_take: solve(12, 1)
 * 2. For solve(11, 1):
 * - Current power: 3^1 = 3, which is ≤ 11.
 * - Two recursive calls:
 *   a) take: solve(11 - 3, 2) => solve(8, 2)
 *   b) not_take: solve(11, 2)
 * 3. For solve(8, 2):
 * - Current power: 3^2 = 9, which is > 8, returns false.
 * 4. For solve(11, 2):
 * - Current power: 3^2 = 9, which is ≤ 11.
 * - Two recursive calls:
 *   a) take: solve(11 - 9, 3) => solve(2, 3)
 *   b) not_take: solve(11, 3)
 * 5. For solve(2, 3):
 * - Current power: 3^3 = 27, which is > 2, returns false.
 * 6. For solve(11, 3):
 * - Current power: 3^3 = 27, which is > 11, returns false.
 * - Thus, solve(11, 2) returns false.
 * 7. Thus, solve(11, 1) returns false (both branches false).
 * 8. Now, for solve(12, 1):
 * - Current power: 3^1 = 3, which is ≤ 12.
 * - Two recursive calls:
 *   a) take: solve(12 - 3, 2) => solve(9, 2)
 *   b) not_take: solve(12, 2)
 * 9. For solve(9, 2):
 * - Current power: 3^2 = 9, which is exactly 9.
 * - "take" branch: solve(9 - 9, 3) => solve(0, 3) returns true (base case reached).
 * - Hence, solve(9, 2) returns true.
 * 10. Since one branch returns true, solve(12, 1) returns true, leading to the final result true.
 */
