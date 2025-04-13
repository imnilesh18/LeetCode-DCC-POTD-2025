/*
 * 1922. Count Good Numbers
 *
 * Medium
 *
 * A digit string is good if the digits (0-indexed) at even indices are even and the digits at odd indices are prime (2, 3, 5, or 7).
 * For example, "2582" is good because the digits (2 and 8) at even positions are even and the digits (5 and 2) at odd positions are prime. However, "3245" is not good because 3 is at an even index but is not even.
 * Given an integer n, return the total number of good digit strings of length n. Since the answer may be large, return it modulo 10^9 + 7.
 * A digit string is a string consisting of digits 0 through 9 that may contain leading zeros.
 *
 * Example 1:
 * Input: n = 1
 * Output: 5
 * Explanation: The good numbers of length 1 are "0", "2", "4", "6", "8".
 *
 * Example 2:
 * Input: n = 4
 * Output: 400
 *
 * Example 3:
 * Input: n = 50
 * Output: 564908303
 *
 * Constraints:
 * 1 <= n <= 10^15
 */

/*
 * INTUITION:
 *
 * n = 5, 5 length digit string
 *
 * _   _   _   _   _
 * 0   1   2   3   4
 *
 * so,
 * even indices count = 3
 * odd indices count = 2
 *
 * similarly if n = 6
 *
 * _   _   _   _   _   _
 * 0   1   2   3   4   5
 *
 * so,
 * even indices count = 3
 * odd indices count = 3
 *
 * so we can deduce that
 * no. of even indices = (n + 1) / 2
 * no. of odd indices = n / 2
 *
 * let's verify this:
 *
 * n = 5
 *
 * n = 5, 5 length digit string
 *
 * _   _   _   _   _
 * 0   1   2   3   4
 *
 * so,
 * even indices count = (n + 1) / 2 = (5 + 1) / 2 = 3
 * odd indices count = n / 2 = 5 /2 = 2
 *
 * n = 6
 * _   _   _   _   _   _
 * 0   1   2   3   4   5
 *
 * so,
 * even indices count = (n + 1) / 2 = (6 + 1) / 2 = 3
 * odd indices count = n / 2 = 6 / 2 = 3
 *
 * hence, this is correct
 *
 * no. of even indices = (n + 1) / 2
 * no. of odd indices = n / 2
 *
 * so, we now know if n is given then how many are even indices and how many are odd indices
 *
 *    __ even indices
 *  /
 * n
 *  \ __ odd indices
 *
 *
 * n = 6
 *
 * _   _   _   _   _   _
 * 0   1   2   3   4   5
 *
 * so at even indices like 0, 2, 4 we can put even numbers
 * hence, there are 5 possiblities (0, 2, 4, 6, 8)
 *
 * and at odd indices like 1, 3, 5 we can put prime numbers
 * hence, there are 4 possiblities(2, 3, 5, 7)
 *
 * hence, our 11th class maths permutation combination
 *
 * _   _   _   _   _   _
 * 0   1   2   3   4   5
 *
 * 5 * 4 * 5 * 4 * 5 * 4
 * = 5³ * 4³
 *
 * hence we can say that,
 * Pow(5, no. of even indices) * Pow(4, no. of odd indices)
 * Pow(5, (n + 1) / 2) * Pow(4, n / 2)
 *
 * now this number in the power can be a very big number
 *
 * so to find aᵇ we will use Binary exponentiation
 * which can be done in T.C = log(b)
 *
 * int findPower(a, b) {
 *
 *  if(b == 0) {
 *      return 1;
 *  }
 *
 *  half = findPower(a, b / 2);
 *  result = (half * half) % M; // where M is 10^9 + 7
 *
 *  if(b % 2 == 1) {
 *      result = (result * a) % M;
 *  }
 *
 *  return result;
 * }
 *
 * It can have very big value, so use so will use long long
 */

// Approach: Use combinatorial analysis: For even indices there are 5 choices (0,2,4,6,8) and for odd indices there are 4 choices (2,3,5,7). Hence the total number of good numbers is 5^((n+1)/2) * 4^(n/2) mod 10^9+7.
// Time Complexity: O(log n) per exponentiation using binary exponentiation.
// Space Complexity: O(log n) due to the recursion stack during binary exponentiation.
class Solution {
public:
    const int M = 1e9 + 7;  // Modulo value as per problem constraints

    // Binary exponentiation function to compute (a^b) % M efficiently.
    int findPower(long long a, long long b) {
        // Base case: any number raised to the power 0 is 1.
        if (b == 0) {
            return 1;
        }

        // Recursively compute half power (a^(b/2)).
        long long half = findPower(a, b / 2);

        // Combine the result of two half powers while taking modulo.
        long long result = (half * half) % M;

        // If b is odd, multiply the extra factor a.
        if (b % 2 == 1) {
            result = (result * a) % M;
        }
        return result;
    }
    // Main function to count good numbers of length n.
    int countGoodNumbers(long long n) {
        // Number of even indices = (n+1)/2, odd indices = n/2.
        // Each even index can have 5 choices, each odd index can have 4 choices.
        // Multiply the results from both using modular arithmetic.
        return ((long long)findPower(5, (n + 1) / 2) * findPower(4, n / 2)) % M;
    }
};

/*
 * Dry Run:
 * For n = 6:
 *   Indices:          0   1   2   3   4   5
 *   Even indices:     0, 2, 4      -> Count = (6 + 1) / 2 = 3
 *   Odd indices:         1, 3, 5   -> Count = 6 / 2 = 3
 *
 *   Calculation:
 *       - Compute findPower(5, 3):
 *           findPower(5, 3) finds:
 *             • 3 is odd, so compute half = findPower(5, 1)
 *             • findPower(5, 1):
 *                   - 1 is odd, so compute half = findPower(5, 0) => returns 1
 *                   - result = (1 * 1) % M = 1, then result = (1 * 5) % M = 5
 *             • Back in findPower(5, 3): half = 5, result = (5 * 5) % M = 25, since 3 is odd, result = (25 * 5) % M = 125
 *       - Compute findPower(4, 3) similarly:
 *           It results in 4^3 = 64.
 *       - Final result = (125 * 64) % M = 8000 % 1e9+7 = 8000.
 *
 * The function returns 8000 for n = 6, which is the total number of good digit strings of length 6.
 */
