/*
 * 3330. Find the Original Typed String I
 *
 * Easy
 *
 * Alice is attempting to type a specific string on her computer. However, she tends to be clumsy and may press a key for too long, resulting in a character being typed multiple times.
 * Although Alice tried to focus on her typing, she is aware that she may still have done this at most once.
 * You are given a string word, which represents the final output displayed on Alice's screen.
 * Return the total number of possible original strings that Alice might have intended to type.
 *
 * Example 1:
 * Input: word = "abbcccc"
 * Output: 5
 * Explanation:
 * The possible strings are: "abbcccc", "abbccc", "abbcc", "abbc", and "abcccc".
 *
 * Example 2:
 * Input: word = "abcd"
 * Output: 1
 * Explanation:
 * The only possible string is "abcd".
 *
 * Example 3:
 * Input: word = "aaaa"
 * Output: 4
 *
 * Constraints:
 * 1 <= word.length <= 100
 * word consists only of lowercase English letters.
 */

// Approach: Count positions where the current character equals the previous one. Each such group can have at most one long press removed. Total possible original strings = number of such positions + 1 (including the original).
// Time Complexity: O(n) - We iterate through the string once.
// Space Complexity: O(1) - We use only constant extra space.
class Solution {
public:
    int possibleStringCount(string word) {
        int n     = word.length(); // Get the length of the string
        int count = 0;             // Initialize count of duplicate positions

        for (int i = 1; i < n; i++) {
            // If current character is same as previous, it's a candidate for being the result of long press
            if (word[i] == word[i - 1]) {
                count++;
            }
        }

        return count + 1; // Add 1 to include the original string itself
    }
};

/*
 *
 * Dry Run
 * Input: word = "abbcccc"
 *
 * Step 1: Initialize count = 0
 * Step 2: Loop from i = 1 to i = 6:
 *     i = 1: word[1] = 'b', word[0] = 'a' => Not same => count = 0
 *     i = 2: word[2] = 'b', word[1] = 'b' => Same => count = 1
 *     i = 3: word[3] = 'c', word[2] = 'b' => Not same => count = 1
 *     i = 4: word[4] = 'c', word[3] = 'c' => Same => count = 2
 *     i = 5: word[5] = 'c', word[4] = 'c' => Same => count = 3
 *     i = 6: word[6] = 'c', word[5] = 'c' => Same => count = 4
 * Step 3: Return count + 1 = 4 + 1 = 5
 *
 * Output: 5
 *
 */
