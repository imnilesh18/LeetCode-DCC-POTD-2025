/*
 * 1910. Remove All Occurrences of a Substring
 *
 * Given two strings s and part, perform the following operation on s until all occurrences of the substring part are removed:
 * Find the leftmost occurrence of the substring part and remove it from s.
 * Return s after removing all occurrences of part.
 * A substring is a contiguous sequence of characters in a string.
 *
 * Example 1:
 * Input: s = "daabcbaabcbc", part = "abc"
 * Output: "dab"
 * Explanation: The following operations are done:
 * - s = "daabcbaabcbc", remove "abc" starting at index 2, so s = "dabaabcbc".
 * - s = "dabaabcbc", remove "abc" starting at index 4, so s = "dababc".
 * - s = "dababc", remove "abc" starting at index 3, so s = "dab".
 * Now s has no occurrences of "abc".
 *
 * Example 2:
 * Input: s = "axxxxyyyyb", part = "xy"
 * Output: "ab"
 * Explanation: The following operations are done:
 * - s = "axxxxyyyyb", remove "xy" starting at index 4 so s = "axxxyyyb".
 * - s = "axxxyyyb", remove "xy" starting at index 3 so s = "axxyyb".
 * - s = "axxyyb", remove "xy" starting at index 2 so s = "axyb".
 * - s = "axyb", remove "xy" starting at index 1 so s = "ab".
 * Now s has no occurrences of "xy".
 *
 * Constraints:
 * 1 <= s.length <= 1000
 * 1 <= part.length <= 1000
 * s​​​​​​ and part consists of lowercase English letters.
 */

// Approach 1 (Brute Force): Repeatedly locate and remove the leftmost occurrence of 'part' in 's' until it no longer exists.
// Time Complexity: O(n * m) in the worst case, where n is the length of s and m is the length of part.
// Space Complexity: O(n), as the string is modified in-place.
class Solution {
public:
   string removeOccurrences(string s, string part) {
      // Loop until no occurrence of 'part' is found in 's'
      while (true) {
         // Find the index of the leftmost occurrence of 'part'
         int idx = s.find(part);

         // If 'part' is not found, exit the loop
         if (idx == string::npos) {
            break;
         }

         // Remove the occurrence of 'part' starting from index 'idx'
         s.erase(idx, part.length());
      }
      // Return the modified string after all occurrences are removed
      return s;
   }
};

/*
 * Dry Run
 * Example: s = "daabcbaabcbc", part = "abc"
 * Iteration 1:
 *  s.find("abc") returns index 2
 *  s.erase(2, 3) transforms s into "dabaabcbc"
 * Iteration 2:
 *  s.find("abc") in "dabaabcbc" returns index 4
 *  s.erase(4, 3) transforms s into "dababc"
 * Iteration 3:
 *  s.find("abc") in "dababc" returns index 3
 *  s.erase(3, 3) transforms s into "dab"
 * Iteration 4:
 *  s.find("abc") in "dab" returns npos (not found)
 *  Loop terminates
 * Final output: "dab"
 */

// Approach 2 (Using Stack): Build the result using a stack and remove the occurrence of 'part' when the top of the stack matches it.
// Time Complexity: O(n * m) in worst-case due to checking the top m characters for every character insertion (n = length of s, m = length of part).
// Space Complexity: O(n), as we use a stack to store characters from s.
class Solution {
public:
   // Helper function to check if the top 'n' characters in the stack match the substring 'part'
   bool check(stack<char>& st, string& part, int n) {
      // Create a temporary copy of the stack to compare without modifying the original
      stack<char> tempSt = st;

      // Compare characters in reverse order (from the end of 'part' to the beginning)
      for (int idx = n - 1; idx >= 0; idx--) {
         if (tempSt.top() != part[idx]) {
            return false;
         }
         tempSt.pop();
      }
      return true;
   }

   string removeOccurrences(string s, string part) {
      stack<char> st;
      int         m = s.length();
      int         n = part.length();

      // Iterate over each character in s
      for (int i = 0; i < m; i++) {
         // Push the current character onto the stack
         st.push(s[i]);

         // If the stack has enough characters and the top n characters match 'part', remove them
         if (st.size() >= n && check(st, part, n)) {
            for (int j = 0; j < n; j++) {
               st.pop();
            }
         }
      }

      // Build the result string from the remaining characters in the stack
      string result = "";
      while (!st.empty()) {
         result.push_back(st.top());
         st.pop();
      }

      // Reverse the result since characters were added in reverse order from the stack
      reverse(begin(result), end(result));
      return result;
   }
};

/*
 * Dry Run
 * Example: s = "daabcbaabcbc", part = "abc"
 * Iteration 1:
 *  Push 'd' -> stack: [d]
 * Iteration 2:
 *  Push 'a' -> stack: [d, a]
 * Iteration 3:
 *  Push 'a' -> stack: [d, a, a]
 *  Check fails since top 3 (a, a, d) != "abc"
 * Iteration 4:
 *  Push 'b' -> stack: [d, a, a, b]
 *  Check fails since top 3 (a, b, a) != "abc"
 * Iteration 5:
 *  Push 'c' -> stack: [d, a, a, b, c]
 *  Check: top 3 are 'a', 'b', 'c' matching "abc"
 *  Remove top 3 -> stack becomes: [d, a]
 * Iteration 6:
 *  Push 'b' -> stack: [d, a, b]
 *  Check fails since (d, a, b) != "abc"
 * Iteration 7:
 *  Push 'a' -> stack: [d, a, b, a]
 *  Check fails
 * Iteration 8:
 *  Push 'a' -> stack: [d, a, b, a, a]
 *  Check fails
 * Iteration 9:
 *  Push 'b' -> stack: [d, a, b, a, a, b]
 *  Check fails
 * Iteration 10:
 *  Push 'c' -> stack: [d, a, b, a, a, b, c]
 *  Check: top 3 are 'a', 'b', 'c' matching "abc"
 *  Remove top 3 -> stack becomes: [d, a, b, a]
 * Iteration 11:
 *  Push 'b' -> stack: [d, a, b, a, b]
 *  Check fails
 * Iteration 12:
 *  Push 'c' -> stack: [d, a, b, a, b, c]
 *  Check: top 3 are 'a', 'b', 'c' matching "abc"
 *  Remove top 3 -> stack becomes: [d, a, b]
 * Final stack: [d, a, b]
 * Result string after reversing: "dab"
 */

// Approach 3: Treat the string 'result' as a stack. For each character in 's', push it onto 'result'.
//           When the end of 'result' matches 'part', remove that substring from 'result'.
// Time Complexity: O(n * m) in the worst-case, where n is the length of s and m is the length of part (due to substring extraction and comparison).
// Space Complexity: O(n), since 'result' stores characters from s.
class Solution {
public:
   string removeOccurrences(string s, string part) {
      string result = "";
      int    n      = part.length();

      // Process each character in s and treat result as a stack
      for (char&ch : s) {
         // Push the current character onto the result (acting as a stack)
         result.push_back(ch);

         // If the result's length is at least n, check if the last n characters match 'part'
         if (result.length() >= n && result.substr(result.length() - n) == part) {
            // Remove the last n characters, effectively deleting the occurrence of 'part'
            result.erase(result.length() - n);
         }
      }

      return result;
   }
};

/*
 * Dry Run
 * Example: s = "daabcbaabcbc", part = "abc"
 * Iteration 1:
 *  result = "d"
 * Iteration 2:
 *  result = "da"
 * Iteration 3:
 *  result = "daa"   (No match with "abc")
 * Iteration 4:
 *  result = "daab"  (No match with "abc")
 * Iteration 5:
 *  result = "daabc" -> Last 3 characters "abc" match part, so erase them -> result becomes "da"
 * Iteration 6:
 *  result = "dab"   (No match with "abc")
 * Iteration 7:
 *  result = "daba"  (No match with "abc")
 * Iteration 8:
 *  result = "dabaa" (No match with "abc")
 * Iteration 9:
 *  result = "dabaab" (No match with "abc")
 * Iteration 10:
 *  result = "dabaabc" -> Last 3 characters "abc" match part, so erase them -> result becomes "daba"
 * Iteration 11:
 *  result = "dabab" (No match with "abc")
 * Iteration 12:
 *  result = "dababc" -> Last 3 characters "abc" match part, so erase them -> result becomes "dab"
 * Final result: "dab"
 */
