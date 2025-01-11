/*
 * 1400. Construct K Palindrome Strings
 *
 * Given a string s and an integer k, return true if you can use all the characters in s to construct k palindrome strings or false otherwise.
 *
 * Example 1:
 * Input: s = "annabelle", k = 2
 * Output: true
 * Explanation: You can construct two palindromes using all characters in s.
 * Some possible constructions "anna" + "elble", "anbna" + "elle", "anellena" + "b"
 *
 * Example 2:
 * Input: s = "leetcode", k = 3
 * Output: false
 * Explanation: It is impossible to construct 3 palindromes using all the characters of s.
 *
 * Example 3:
 * Input: s = "true", k = 4
 * Output: true
 * Explanation: The only possible solution is to put each character in a separate string.
 *
 * Constraints:
 * 1 <= s.length <= 10^5
 * s consists of lowercase English letters.
 * 1 <= k <= 10^5
 */

// Approach: Count characters with odd frequencies - these must be centers of different palindromes, so their count should not exceed k.
// TC: O(n) where n is length of string for counting frequencies
// SC: O(1) as we use fixed size vector of 26 characters
class Solution {
public:
   bool canConstruct(string s, int k){
      // Get length of input string
      int n = s.length();

      // If length is less than k, we cannot form k palindromes
      // as each palindrome needs at least one character
      if (n < k) {
         return false;
      }

      // If length equals k, we can form k palindromes
      // by putting each character in separate string
      if (n == k) {
         return true;
      }

      // Array to store frequency of each character
      vector<int> freq(26, 0);
      // Count frequency of each character
      for (char&ch : s) {
         freq[ch - 'a']++;
      }

      // Count characters with odd frequencies
      // Characters with odd frequencies need to be in middle of different palindromes
      int oddFreqCount = 0;
      for (int i = 0; i < 26; i++) {
         if (freq[i] % 2 != 0) {
            oddFreqCount++;
         }
      }

      // If odd frequency count is more than k,
      // we cannot construct k palindromes
      return oddFreqCount <= k;
   }
};
