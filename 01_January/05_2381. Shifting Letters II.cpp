/*
 * 2381. Shifting Letters II
 *
 * You are given a string s of lowercase English letters and a 2D integer array shifts where shifts[i] = [starti, endi, directioni]. For every i, shift the characters in s from the index starti to the index endi (inclusive) forward if directioni = 1, or shift the characters backward if directioni = 0.
 *
 * Shifting a character forward means replacing it with the next letter in the alphabet (wrapping around so that 'z' becomes 'a'). Similarly, shifting a character backward means replacing it with the previous letter in the alphabet (wrapping around so that 'a' becomes 'z').
 *
 * Return the final string after all such shifts to s are applied.
 *
 * Example 1:
 * Input: s = "abc", shifts = [[0,1,0],[1,2,1],[0,2,1]]
 * Output: "ace"
 * Explanation: Firstly, shift the characters from index 0 to index 1 backward. Now s = "zac".
 * Secondly, shift the characters from index 1 to index 2 forward. Now s = "zbd".
 * Finally, shift the characters from index 0 to index 2 forward. Now s = "ace".
 *
 * Example 2:
 * Input: s = "dztz", shifts = [[0,0,0],[1,1,1]]
 * Output: "catz"
 * Explanation: Firstly, shift the characters from index 0 to index 0 backward. Now s = "cztz".
 * Finally, shift the characters from index 1 to index 1 forward. Now s = "catz".
 *
 * Constraints:
 * 1 <= s.length, shifts.length <= 5 * 10^4
 * shifts[i].length == 3
 * 0 <= starti <= endi < s.length
 * 0 <= directioni <= 1
 * s consists of lowercase English letters.
 */

class Solution {
public:
   string shiftingLetters(string s, vector<vector<int> >& shifts){
      int         n = s.size();
      vector<int> diffArray(
         n, 0);     // Initialize a difference array with all elements set to 0.

      for (auto shift : shifts) {
         if (shift[2] == 1) {           // If direction is forward (1):
            diffArray[shift[0]]++;      // Increment at the start index to
                                        // indicate a forward shift.
            if (shift[1] + 1 < n) {
               diffArray[shift[1] +
                         1]--;       // Decrement at the end+1 index to stop the
                                     // effect of the shift.
            }
         } else {                    // If direction is backward (0):
            diffArray[shift[0]]--;   // Decrement at the start index to
                                     // indicate a backward shift.
            if (shift[1] + 1 < n) {
               diffArray[shift[1] +
                         1]++;       // Increment at the end+1 index to stop the
                                     // effect of the shift.
            }
         }
      }

      string result(n, ' ');
      int    numberOfShifts = 0;

      for (int i = 0; i < s.size(); i++) {
         numberOfShifts = (numberOfShifts + diffArray[i]) %
                          26;     // Update cumulative shifts, keeping within
                                  // the alphabet range.
         if (numberOfShifts < 0) {
            numberOfShifts +=
               26;       // Ensure `numberOfShifts` is non-negative.
         }
         // Calculate the new character by shifting `s[i]`
         result[i] = 'a' + (s[i] - 'a' + numberOfShifts) % 26;
      }

      return result;
   }
};
