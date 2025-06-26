/*
 * 2311. Longest Binary Subsequence Less Than or Equal to K
 *
 * Medium
 *
 * You are given a binary string s and a positive integer k.
 * Return the length of the longest subsequence of s that makes up a binary number less than or equal to k.
 * Note:
 * The subsequence can contain leading zeroes.
 * The empty string is considered to be equal to 0.
 * A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
 *
 * Example 1:
 * Input: s = "1001010", k = 5
 * Output: 5
 * Explanation: The longest subsequence of s that makes up a binary number less than or equal to 5 is "00010", as this number is equal to 2 in decimal.
 * Note that "00100" and "00101" are also possible, which are equal to 4 and 5 in decimal, respectively.
 * The length of this subsequence is 5, so 5 is returned.
 *
 * Example 2:
 * Input: s = "00101001", k = 1
 * Output: 6
 * Explanation: "000001" is the longest subsequence of s that makes up a binary number less than or equal to 1, as this number is equal to 1 in decimal.
 * The length of this subsequence is 6, so 6 is returned.
 *
 * Constraints:
 * 1 <= s.length <= 1000
 * s[i] is either '0' or '1'.
 * 1 <= k <= 10^9
 */

// Approach: Greedy scan from least significant bit, always take '0's and take '1's if their power value fits into remaining k
// Time Complexity: O(n) – single pass through the string of length n
// Space Complexity: O(1) – only constant extra variables used
class Solution {
public:
    int longestSubsequence(string s, int k) {
        int       length     = 0;     // count of characters taken in subsequence
        long long powerValue = 1;     // current bit value, starting at 2^0 = 1

        // scan from rightmost bit (LSB) to leftmost (MSB)
        for (int i = s.size() - 1; i >= 0; --i) {
            if (s[i] == '0') {
                // always safe to take '0' since it contributes 0 to the sum
                length++;
            } else if (powerValue <= k) {
                // take '1' only if its value does not exceed remaining k
                length++;
                k -= powerValue;      // subtract its value from k
            }

            // prepare for next higher bit: double powerValue if it will still fit k
            if (powerValue <= k) {
                powerValue <<= 1;     // equivalent to powerValue *= 2
            }
        }

        return length;
    }
};

/*
 *
 * Dry Run
 *
 * Input: s = "1001010", k = 5
 *
 * Initialize:
 * length = 0, powerValue = 1
 *
 * i = 6 (s[6]='0'):
 *   '0' ⇒ length = 1
 *   powerValue (1) ≤ k (5) ⇒ powerValue = 2
 *
 * i = 5 (s[5]='1'):
 *   powerValue (2) ≤ k (5) ⇒ take '1': length = 2, k = 5 - 2 = 3
 *   powerValue (2) ≤ k (3) ⇒ powerValue = 4
 *
 * i = 4 (s[4]='0'):
 *   '0' ⇒ length = 3
 *   powerValue (4) > k (3) ⇒ powerValue stays 4
 *
 * i = 3 (s[3]='1'):
 *   powerValue (4) > k (3) ⇒ skip '1'
 *   powerValue (4) > k (3) ⇒ stays 4
 *
 * i = 2 (s[2]='0'):
 *   '0' ⇒ length = 4
 *   powerValue (4) > k (3) ⇒ stays 4
 *
 * i = 1 (s[1]='0'):
 *   '0' ⇒ length = 5
 *   powerValue (4) ≤ k (3)? No ⇒ stays 4
 *
 * i = 0 (s[0]='1'):
 *   powerValue (4) > k (3) ⇒ skip '1'
 *   powerValue (4) > k (3) ⇒ stays 4
 *
 * End for-loop. Return length = 5
 *
 */
