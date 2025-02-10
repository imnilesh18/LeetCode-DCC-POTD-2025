/*
 * 3174. Clear Digits
 *
 * You are given a string s.
 * Your task is to remove all digits by doing this operation repeatedly:
 * Delete the first digit and the closest non-digit character to its left.
 * Return the resulting string after removing all digits.
 *
 * Example 1:
 * Input: s = "abc"
 * Output: "abc"
 * Explanation:
 * There is no digit in the string.
 *
 * Example 2:
 * Input: s = "cb34"
 * Output: ""
 *
 * Explanation:
 * First, we apply the operation on s[2], and s becomes "c4".
 * Then we apply the operation on s[1], and s becomes "".
 *
 * Constraints:
 * 1 <= s.length <= 100
 * s consists only of lowercase English letters and digits.
 * The input is generated such that it is possible to delete all digits.
 */

// Approach 1: Iterate over the string and whenever a digit is found, remove it along with its closest preceding non-digit character.
// TC: O(n^2) - Each erase operation can take O(n) time and in the worst-case scenario, it might be called O(n) times.
// SC: O(1) - The algorithm modifies the string in place using constant extra space.
class Solution {
public:
   string clearDigits(string s) {
      int i = 0;

      // Traverse the string until we reach its end.
      while (i < s.length()) {
         // If the current character is a digit...
         if (isdigit(s[i])) {
            // ...remove the digit at index i.
            s.erase(i, 1);
            // If there is a character to the left, remove it as well.
            if (i - 1 >= 0) {
               s.erase(i - 1, 1);
               // Adjust the index to account for the removed character.
               i--;
            }
         } else {
            // If it's not a digit, simply move to the next character.
            i++;
         }
      }
      return s;
   }
};

/*
 * Dry Run
 * Input: "cb34"
 *
 * Step-by-Step:
 * 1. Initial string: "cb34", i = 0
 * 2. i = 0: Character 'c' is not a digit → increment i to 1.
 * 3. i = 1: Character 'b' is not a digit → increment i to 2.
 * 4. i = 2: Character '3' is a digit → remove '3' and its preceding character 'b':
 * - String becomes "c4"
 * - Adjust i to 1.
 * 5. i = 1: Character '4' is a digit → remove '4' and its preceding character 'c':
 * - String becomes ""
 * - Adjust i to 0.
 * 6. i = 0: End of string reached → exit loop.
 *
 * Output: ""
 * End Dry Run
 */
