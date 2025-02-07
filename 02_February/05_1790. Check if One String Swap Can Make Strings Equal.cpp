/*
 * 1790. Check if One String Swap Can Make Strings Equal
 *
 * You are given two strings s1 and s2 of equal length. A string swap is an operation where you choose two indices in a string (not necessarily different) and swap the characters at these indices.
 * Return true if it is possible to make both strings equal by performing at most one string swap on exactly one of the strings. Otherwise, return false.
 *
 * Example 1:
 * Input: s1 = "bank", s2 = "kanb"
 * Output: true
 * Explanation: For example, swap the first character with the last character of s2 to make "bank".
 *
 * Example 2:
 * Input: s1 = "attack", s2 = "defend"
 * Output: false
 * Explanation: It is impossible to make them equal with one string swap.
 *
 * Example 3:
 * Input: s1 = "kelb", s2 = "kelb"
 * Output: true
 * Explanation: The two strings are already equal, so no string swap operation is required.
 *
 * Constraints:
 * 1 <= s1.length, s2.length <= 100
 * s1.length == s2.length
 * s1 and s2 consist of only lowercase English letters.
 */


// Approach: Traverse both strings to record indices where characters differ. If the strings are identical (0 differences), return true.
//           If there are exactly 2 differences, check if swapping the mismatched characters makes the strings equal.
//           Otherwise (1 or >2 differences), return false.
// Time Complexity: O(n) - where n is the length of the strings, since we iterate through the strings once.
// Space Complexity: O(1) - only a few extra variables are used, regardless of the input size.
class Solution {
public:
   bool areAlmostEqual(string s1, string s2) {
      int firstIndexDiff  = 0;        // Stores the index of the first mismatched character.
      int secondIndexDiff = 0;        // Stores the index of the second mismatched character.
      int numDiffs        = 0;        // Counts the number of differences between s1 and s2.

      // Iterate through each character in the strings.
      for (int i = 0; i < s1.size(); i++) {
         if (s1[i] != s2[i]) {   // When characters differ at index i.
            numDiffs++;          // Increment the count of differences.

            // If more than 2 differences are found, one swap cannot fix the strings.
            if (numDiffs > 2) {
               return false;
            }else if (numDiffs == 1) {
               // Record the index of the first difference.
               firstIndexDiff = i;
            } else {          // numDiffs == 2
               // Record the index of the second difference.
               secondIndexDiff = i;
            }
         }
      }

      // If strings are already equal (numDiffs == 0), then s1[0]==s2[0] holds true.
      // For exactly 2 differences, check if swapping the mismatched characters makes the strings equal.
      return s1[firstIndexDiff] == s2[secondIndexDiff] &&
             s1[secondIndexDiff] == s2[firstIndexDiff];
   }
};

/*
 * Dry Run:
 * Example: s1 = "bank", s2 = "kanb"
 *  i = 0: s1[0]='b', s2[0]='k'  -> first difference found; firstIndexDiff = 0, numDiffs = 1.
 *  i = 1: s1[1]='a', s2[1]='a'  -> characters are same; no action.
 *  i = 2: s1[2]='n', s2[2]='n'  -> characters are same; no action.
 *  i = 3: s1[3]='k', s2[3]='b'  -> second difference found; secondIndexDiff = 3, numDiffs = 2.
 *  After the loop, check if swapping the characters at indices 0 and 3 in one of the strings would match the other:
 *  Compare: s1[0] ('b') with s2[3] ('b') and s1[3] ('k') with s2[0] ('k').
 *  Since both conditions are satisfied, the function returns true.
 */
