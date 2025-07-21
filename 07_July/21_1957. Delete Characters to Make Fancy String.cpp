/*
 * 1957. Delete Characters to Make Fancy String
 *
 * Easy
 *
 * A fancy string is a string where no three consecutive characters are equal.
 * Given a string s, delete the minimum possible number of characters from s to make it fancy.
 * Return the final string after the deletion. It can be shown that the answer will always be unique.
 *
 * Example 1:
 * Input: s = "leeetcode"
 * Output: "leetcode"
 * Explanation:
 * Remove an 'e' from the first group of 'e's to create "leetcode".
 * No three consecutive characters are equal, so return "leetcode".
 *
 * Example 2:
 * Input: s = "aaabaaaa"
 * Output: "aabaa"
 * Explanation:
 * Remove an 'a' from the first group of 'a's to create "aabaaaa".
 * Remove two 'a's from the second group of 'a's to create "aabaa".
 * No three consecutive characters are equal, so return "aabaa".
 *
 * Example 3:
 * Input: s = "aab"
 * Output: "aab"
 * Explanation: No three consecutive characters are equal, so return "aab".
 *
 * Constraints:
 * 1 <= s.length <= 10^5
 * s consists only of lowercase English letters.
 */

// Approach: Iterate through the input string while building a new result string. Use a frequency counter to track consecutive characters. Only append a character to the result if it's different from the previous one, or if it's the same but its frequency is less than 3.
// Time Complexity: O(n), where n is the length of the string 's', because we iterate through the string once.
// Space Complexity: O(n) in the worst case for the result string, as it could potentially store all characters if no deletions are needed.
class Solution {
public:
    string makeFancyString(string s) {
        // Get the length of the input string.
        int n = s.length();

        // If the string is empty, return it as is.
        if (n == 0) {
            return "";
        }

        // Initialize an empty string to build the result.
        string result = "";
        // Append the first character of 's' to the result.
        result.push_back(s[0]);
        // Initialize frequency of the current character to 1.
        int freq = 1;

        // Loop through the string starting from the second character.
        for (int i = 1; i < n; i++) {
            // Check if the current character is the same as the last character added to the result.
            if (s[i] == result.back()) {
                // If it's the same, increment the frequency count.
                freq++;
                // Only append the character if its consecutive frequency is less than 3.
                if (freq < 3) {
                    result.push_back(s[i]);
                }
            } else {
                // If the character is different from the previous one.
                // Append the new character to the result.
                result.push_back(s[i]);
                // Reset the frequency counter to 1 for the new character.
                freq = 1;
            }
        }
        // Return the final fancy string.
        return result;
    }
};

/*
 *
 * Dry Run for Input: s = "leeetcode"
 *
 * 1. Initialization:
 * - n = 9
 * - result = ""
 * - result.push_back(s[0]) which is 'l'. So, result = "l".
 * - freq = 1
 *
 * 2. Loop starts from i = 1:
 *
 * - i = 1, s[1] = 'e':
 * - s[1] ('e') != result.back() ('l').
 * - result.push_back('e'). result becomes "le".
 * - freq is reset to 1.
 *
 * - i = 2, s[2] = 'e':
 * - s[2] ('e') == result.back() ('e').
 * - freq becomes 2.
 * - freq (2) < 3 is true.
 * - result.push_back('e'). result becomes "lee".
 *
 * - i = 3, s[3] = 'e':
 * - s[3] ('e') == result.back() ('e').
 * - freq becomes 3.
 * - freq (3) < 3 is false.
 * - Nothing is added to result. result remains "lee".
 *
 * - i = 4, s[4] = 't':
 * - s[4] ('t') != result.back() ('e').
 * - result.push_back('t'). result becomes "leet".
 * - freq is reset to 1.
 *
 * - i = 5, s[5] = 'c':
 * - s[5] ('c') != result.back() ('t').
 * - result.push_back('c'). result becomes "leetc".
 * - freq is reset to 1.
 *
 * - i = 6, s[6] = 'o':
 * - s[6] ('o') != result.back() ('c').
 * - result.push_back('o'). result becomes "leetco".
 * - freq is reset to 1.
 *
 * - i = 7, s[7] = 'd':
 * - s[7] ('d') != result.back() ('o').
 * - result.push_back('d'). result becomes "leetcod".
 * - freq is reset to 1.
 *
 * - i = 8, s[8] = 'e':
 * - s[8] ('e') != result.back() ('d').
 * - result.push_back('e'). result becomes "leetcode".
 * - freq is reset to 1.
 *
 * 3. Loop ends.
 *
 * 4. Final Return: The function returns the result string, which is "leetcode".
 *
 */
