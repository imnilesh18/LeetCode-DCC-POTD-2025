/*
 * 1358. Number of Substrings Containing All Three Characters
 * After this solve: 306. Count of Substrings Containing Every Vowel and K Consonants II
 *
 * Given a string s consisting only of characters a, b and c.
 * Return the number of substrings containing at least one occurrence of all these characters a, b and c.
 *
 * Example 1:
 * Input: s = "abcabc"
 * Output: 10
 * Explanation: The substrings containing at least one occurrence of the characters a, b and c are "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again).
 *
 * Example 2:
 * Input: s = "aaacb"
 * Output: 3
 * Explanation: The substrings containing at least one occurrence of the characters a, b and c are "aaacb", "aacb" and "acb".
 *
 * Example 3:
 * Input: s = "abc"
 * Output: 1
 *
 * Constraints:
 * 3 <= s.length <= 5 x 10^4
 * s only consists of a, b or c characters.
 */

// Approach: Two-pointer sliding window technique. Expand the window using pointer j until it contains all three characters, then contract the window from pointer i while counting valid substrings by adding (n - j).
// Time Complexity: O(n) as each character is processed at most twice (once by j and once by i).
// Space Complexity: O(1) because only a fixed-size vector (size 3) is used.
class Solution {
public:
    int numberOfSubstrings(string s) {
        int n      = s.length();
        int result = 0;

        // vector to count frequency of characters 'a', 'b', and 'c'
        vector<int> mp(3, 0);

        int i = 0;
        int j = 0;

        // Expand the window with pointer j
        while (j < n) {
            // Include s[j] in the window
            char ch = s[j];
            mp[ch - 'a']++;

            // When the window contains at least one of each character, contract the window from the left (pointer i)
            while (mp[0] > 0 && mp[1] > 0 && mp[2] > 0) {
                // All substrings starting from index i to current j and extending to end are valid
                result += (n - j);
                // Remove the character at index i from the window and move i forward
                mp[s[i] - 'a']--;
                i++;
            }
            // Expand the window by moving j to the next character
            j++;
        }
        return result;
    }
};

/*
 * Dry Run:
 * Input: s = "abcabc"
 * Initial State: i = 0, j = 0, result = 0, mp = [0, 0, 0]
 *
 * j = 0: s[j] = 'a' -> mp becomes [1, 0, 0]
 * j = 1: s[j] = 'b' -> mp becomes [1, 1, 0]
 * j = 2: s[j] = 'c' -> mp becomes [1, 1, 1]
 *       -> Valid window "abc".
 *       -> Inner loop: result += (6 - 2) = 4; decrement mp for s[i] ('a'): mp becomes [0, 1, 1]; increment i to 1.
 *       -> Exit inner loop as window no longer has 'a'.
 * j = 3: s[j] = 'a' -> mp becomes [1, 1, 1] ("bca")
 *       -> Valid window "bca".
 *       -> Inner loop: result += (6 - 3) = 3; decrement mp for s[i] ('b'): mp becomes [1, 0, 1]; increment i to 2.
 *       -> Exit inner loop as window no longer has 'b'.
 * j = 4: s[j] = 'b' -> mp becomes [1, 1, 1] ("cab")
 *       -> Valid window "cab".
 *       -> Inner loop: result += (6 - 4) = 2; decrement mp for s[i] ('c'): mp becomes [1, 1, 0]; increment i to 3.
 *       -> Exit inner loop as window no longer has 'c'.
 * j = 5: s[j] = 'c' -> mp becomes [1, 1, 1] ("abc")
 *       -> Valid window "abc".
 *       -> Inner loop: result += (6 - 5) = 1; decrement mp for s[i] ('a'): mp becomes [0, 1, 1]; increment i to 4.
 *       -> Exit inner loop as window no longer has 'a'.
 * Final result = 4 + 3 + 2 + 1 = 10.
 */
