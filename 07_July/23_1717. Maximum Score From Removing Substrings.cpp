/*
 * 1717. Maximum Score From Removing Substrings
 *
 * Medium
 *
 * You are given a string s and two integers x and y. You can perform two types of operations any number of times.
 * Remove substring "ab" and gain x points.
 * For example, when removing "ab" from "cabxbae" it becomes "cxbae".
 * Remove substring "ba" and gain y points.
 * For example, when removing "ba" from "cabxbae" it becomes "cabxe".
 * Return the maximum points you can gain after applying the above operations on s.
 *
 * Example 1:
 * Input: s = "cdbcbbaaabab", x = 4, y = 5
 * Output: 19
 * Explanation:
 * - Remove the "ba" underlined in "cdbcbbaaabab". Now, s = "cdbcbbaaab" and 5 points are added to the score.
 * - Remove the "ab" underlined in "cdbcbbaaab". Now, s = "cdbcbbaa" and 4 points are added to the score.
 * - Remove the "ba" underlined in "cdbcbbaa". Now, s = "cdbcba" and 5 points are added to the score.
 * - Remove the "ba" underlined in "cdbcba". Now, s = "cdbc" and 5 points are added to the score.
 * Total score = 5 + 4 + 5 + 5 = 19.
 *
 * Example 2:
 * Input: s = "aabbaaxybbaabb", x = 5, y = 4
 * Output: 20
 *
 * Constraints:
 * 1 <= s.length <= 10^5
 * 1 <= x, y <= 10^4
 * s consists of lowercase English letters.
 */

// Approach: Greedy. First, remove all higher-scoring pairs ("ab" or "ba"). Then, from the remaining string, remove all lower-scoring pairs. This two-pass method guarantees the maximum score.
// Time Complexity: O(n), because the string is scanned a constant number of times.
// Space Complexity: O(1), as the string is modified in-place, using no extra space that scales with input size.
class Solution {
public:
    int maximumGain(string s, int x, int y) {
        int n     = s.length();
        int score = 0;

        // Prioritize removing the substring with the higher score.
        string maxStr = (x > y) ? "ab" : "ba";
        string minStr = (x > y) ? "ba" : "ab";

        // First pass: remove the more valuable substring.
        string temp_first = removeSubstring(s, maxStr);
        int    L          = temp_first.length();
        // Count removed pairs by the change in string length.
        int removedPairsCount = (n - L) / 2;

        // Add the score from the first pass.
        score += removedPairsCount * max(x, y);

        // Second pass: remove the less valuable substring from the result.
        string temp_second = removeSubstring(temp_first, minStr);
        // Count pairs removed in the second pass.
        removedPairsCount = (L - temp_second.length()) / 2;
        // Add the score from the second pass.
        score += removedPairsCount * min(x, y);

        return score;
    }
    // Helper to remove all occurrences of `matchStr` using a two-pointer/stack simulation.
    string removeSubstring(string& inputString, string& matchStr) {
        int j = 0; // Write pointer for in-place modification (acts as stack top).

        // `i` is the read pointer.
        for (int i = 0; i < inputString.size(); i++) {
            // "Push" the current character to the valid part of the string.
            inputString[j++] = inputString[i];

            // If the last two characters form the target substring...
            if (j > 1 &&
                inputString[j - 2] == matchStr[0] &&
                inputString[j - 1] == matchStr[1]) {
                // ... "pop" them by moving the write pointer back.
                j -= 2;
            }
        }

        // Trim the string to its new, shorter size.
        inputString.erase(inputString.begin() + j, inputString.end());

        return inputString;
    }
    /*
     *
     * Dry Run for s = "cdbcbbaaabab", x = 4, y = 5
     *
     * 1. Setup:
     * - y (5) > x (4), so we remove "ba" first, then "ab".
     * - maxStr = "ba", minStr = "ab", score = 0.
     *
     * 2. First Pass (Remove "ba", score 5):
     * - String "cdbcbbaaabab" (len 12) is processed.
     * - After removing all "ba", the string becomes "cdbcab" (len 6).
     * - Pairs removed: (12 - 6) / 2 = 3.
     * - Score added: 3 * 5 = 15. Total score = 15.
     *
     * 3. Second Pass (Remove "ab", score 4):
     * - String "cdbcab" (len 6) is processed.
     * - After removing all "ab", the string becomes "cdbc" (len 4).
     * - Pairs removed: (6 - 4) / 2 = 1.
     * - Score added: 1 * 4 = 4. Total score = 15 + 4 = 19.
     *
     * 4. Result:
     * - Return 19.
     *
     */
};
