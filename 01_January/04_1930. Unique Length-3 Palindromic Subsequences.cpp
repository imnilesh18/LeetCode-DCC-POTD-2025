/*
 * 1930. Unique Length-3 Palindromic Subsequences
 *
 * Given a string s, return the number of unique palindromes of length three that are a subsequence of s.
 * Note that even if there are multiple ways to obtain the same subsequence, it is still only counted once.
 * A palindrome is a string that reads the same forwards and backwards.
 * A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.
 * For example, "ace" is a subsequence of "abcde".
 *
 * Example 1:
 * Input: s = "aabca"
 * Output: 3
 * Explanation: The 3 palindromic subsequences of length 3 are:
 * - "aba" (subsequence of "aabca")
 * - "aaa" (subsequence of "aabca")
 * - "aca" (subsequence of "aabca")
 *
 * Example 2:
 * Input: s = "adc"
 * Output: 0
 * Explanation: There are no palindromic subsequences of length 3 in "adc".
 *
 * Example 3:
 * Input: s = "bbcbaba"
 * Output: 4
 * Explanation: The 4 palindromic subsequences of length 3 are:
 * - "bbb" (subsequence of "bbcbaba")
 * - "bcb" (subsequence of "bbcbaba")
 * - "bab" (subsequence of "bbcbaba")
 * - "aba" (subsequence of "bbcbaba")
 *
 * Constraints:
 * 3 <= s.length <= 10^5
 * s consists of only lowercase English letters.
 */

// Approach 1: For each unique character, find its first and last occurrence and count unique characters between them as each will form a palindrome.
// TC: O(n) since k is bounded by 26 (lowercase English letters), making the actual complexity O(26n) ≈ O(n)
// SC: O(1) since we store at most 26 characters in the sets, making the space usage constant
class Solution {
public:
   int countPalindromicSubsequence(string s){
      int n = s.length();

      // Store all unique characters from string (max 26 lowercase letters)
      unordered_set<char> letters;

      for (int i = 0; i < n; i++) {
         letters.insert(s[i]);
      }

      int result = 0;

      // For each unique character (max 26), try to form palindrome with it as first and last character
      for (char letter : letters) {
         // Track leftmost and rightmost occurrence of current character
         int left_idx  = -1;
         int right_idx = -1;

         // Find leftmost and rightmost positions of current character
         for (int i = 0; i < n; i++) {
            if (s[i] == letter) {
               if (left_idx == -1) {
                  left_idx = i;        // First occurrence
               }
               right_idx = i;          // Last occurrence
            }
         }

         // Store all unique characters that appear between left_idx and right_idx (max 26)
         unordered_set<char> st;
         for (int middle = left_idx + 1; middle <= right_idx - 1; middle++) {
            st.insert(s[middle]);
         }

         // Add count of unique middle characters to result
         // Each middle character forms a unique palindrome with current letter
         result += st.size();
      }
      return result;
   }
};

// Approach 2: Store first and last indices of each character in one pass, then for each character count unique characters between its first and last occurrence.
// TC: O(n) where n is string length since we make two passes through string (first for finding ranges, second for counting unique chars).
// SC: O(1) since we use fixed size array for indices and set stores at most 26 characters.
class Solution {
public:
   int countPalindromicSubsequence(string s){
      int n = s.length();

      // Store first and last occurrence of each character (26 lowercase letters)
      // indices[0] stores range for 'a', indices[1] for 'b' and so on
      vector<pair<int, int> > indices(26, { -1, -1 });

      // Find first and last occurrence of each character in one pass
      for (int i = 0; i < n; i++) {
         char ch  = s[i];
         int  idx = ch - 'a';  // Convert character to 0-25 index

         if (indices[idx].first == -1) {
            indices[idx].first = i;    // First occurrence
         }

         indices[idx].second = i;   // Keep updating last occurrence
      }

      int result = 0;

      // For each character (a to z)
      for (int i = 0; i < 26; i++) {
         int left_idx  = indices[i].first;
         int right_idx = indices[i].second;

         // Skip if character doesn't exist in string
         if (left_idx == -1) {
            continue;
         }

         // Find unique characters between first and last occurrence
         unordered_set<char> st;
         for (int middle = left_idx + 1; middle <= right_idx - 1; middle++) {
            st.insert(s[middle]);
         }

         // Each unique middle character forms a palindrome
         result += st.size();
      }
      return result;
   }
};
