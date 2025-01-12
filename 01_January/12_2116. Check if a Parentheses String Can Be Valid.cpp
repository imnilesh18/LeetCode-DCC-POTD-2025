/*
 * 2116. Check if a Parentheses String Can Be Valid
 *
 * A parentheses string is a non-empty string consisting only of '(' and ')'. It is valid if any of the following conditions is true:
 *
 * It is ().
 * It can be written as AB (A concatenated with B), where A and B are valid parentheses strings.
 * It can be written as (A), where A is a valid parentheses string.
 * You are given a parentheses string s and a string locked, both of length n. locked is a binary string consisting only of '0's and '1's. For each index i of locked,
 *
 * If locked[i] is '1', you cannot change s[i].
 * But if locked[i] is '0', you can change s[i] to either '(' or ')'.
 * Return true if you can make s a valid parentheses string. Otherwise, return false.
 *
 * Example 1:
 * Input: s = "))()))", locked = "010100"
 * Output: true
 * Explanation: locked[1] == '1' and locked[3] == '1', so we cannot change s[1] or s[3].
 * We change s[0] and s[4] to '(' while leaving s[2] and s[5] unchanged to make s valid.
 *
 * Example 2:
 * Input: s = "()()", locked = "0000"
 * Output: true
 * Explanation: We do not need to make any changes because s is already valid.
 *
 * Example 3:
 * Input: s = ")", locked = "0"
 * Output: false
 * Explanation: locked permits us to change s[0].
 * Changing s[0] to either '(' or ')' will not make s valid.
 *
 * Constraints:
 * n == s.length == locked.length
 * 1 <= n <= 10^5
 * s[i] is either '(' or ')'.
 * locked[i] is either '0' or '1'.
 */

// Approach 1 (Using Stack): Use two stacks - one for tracking fixed opening brackets and another for unlocked positions, process string left to right handling closing brackets, then match remaining opening brackets with unlocked positions.
// TC: O(n) where n is the length of the string
// SC: O(n) for storing indices in the stacks
class Solution {
public:
   bool canBeValid(string s, string locked){
      // Get length of string
      int n = s.length();

      // If length is odd, it can't be valid parentheses string
      if (n % 2 != 0) {
         return false;
      }

      // Stack to store indices of fixed opening brackets '('
      stack<int> open;
      // Stack to store indices of unlocked positions (where locked[i] = '0')
      stack<int> openClose;

      // First pass: Process the string from left to right
      for (int i = 0; i < n ; i++) {
         if (locked[i] == '0') {
            // If position is unlocked, we can use it as either '(' or ')'
            openClose.push(i);
         } else if (s[i] == '(') {
            // If we find a locked opening bracket
            open.push(i);
         } else if (s[i] == ')') {
            // For a closing bracket, try to match with:
            // 1. Available opening bracket
            if (!open.empty()) {
               open.pop();
            }
            // 2. Or use an unlocked position
            else if (!openClose.empty()) {
               openClose.pop();
            }
            // If neither available, string can't be valid
            else {
               return false;
            }
         }
      }

      // Second pass: Try to match remaining opening brackets with unlocked positions
      // Only valid if unlocked position comes after the opening bracket
      while (!open.empty() && !openClose.empty() && open.top() < openClose.top()) {
         open.pop();
         openClose.pop();
      }

      // String can only be valid if all opening brackets are matched
      return open.empty();
   }
};

// Approach 2 (Constant Extra Space): Use two passes - left to right to ensure closing brackets don't exceed opening ones, and right to left to ensure opening brackets don't exceed closing ones.
// TC: O(n) where n is the length of the string
// SC: O(1) as we only use constant extra space
class Solution {
public:
   bool canBeValid(string s, string locked){
      // Get string length
      int n = s.length();

      // If length is odd, it can't be valid parentheses string
      if (n % 2 != 0) {
         return false;
      }

      // Left to Right scan:
      // Track available opening brackets (including unlocked positions)
      int open = 0;
      for (int i = 0; i < n; i++) {
         // Count fixed '(' and unlocked positions as potential opening brackets
         if (s[i] == '(' || locked[i] == '0') {
            open++;
         }
         // Count fixed ')' as closing brackets
         else {
            open--;
         }

         // At any point if closing brackets exceed opening ones, string can't be valid
         if (open < 0) {
            return false;
         }
      }

      // Right to Left scan:
      // Track available closing brackets (including unlocked positions)
      int close = 0;
      for (int i = n - 1; i >= 0; i--) {
         // Count fixed ')' and unlocked positions as potential closing brackets
         if (s[i] == ')' || locked[i] == '0') {
            close++;
         }
         // Count fixed '(' as opening brackets
         else {
            close--;
         }

         // At any point if opening brackets exceed closing ones, string can't be valid
         if (close < 0) {
            return false;
         }
      }

      // If both scans pass, string can be made valid
      return true;
   }
};
