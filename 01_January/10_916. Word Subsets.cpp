/*
 * 916. Word Subsets
 *
 * You are given two string arrays words1 and words2.
 * A string b is a subset of string a if every letter in b occurs in a including multiplicity.
 * For example, "wrr" is a subset of "warrior" but is not a subset of "world".
 * A string a from words1 is universal if for every string b in words2, b is a subset of a.
 * Return an array of all the universal strings in words1. You may return the answer in any order.
 *
 * Example 1:
 * Input: words1 = ["amazon","apple","facebook","google","leetcode"], words2 = ["e","o"]
 * Output: ["facebook","google","leetcode"]
 *
 * Example 2:
 * Input: words1 = ["amazon","apple","facebook","google","leetcode"], words2 = ["l","e"]
 * Output: ["apple","google","leetcode"]
 *
 * Constraints:
 * 1 <= words1.length, words2.length <= 10^4
 * 1 <= words1[i].length, words2[i].length <= 10
 * words1[i] and words2[i] consist only of lowercase English letters.
 * All the strings of words1 are unique.
 */

// Approach: Create a frequency array for maximum required occurrences from words2, then check each word in words1 if it satisfies these requirements.
// T.C : O(n*l1 + m*l2) where n,m = size of words1,words2 & l1,l2 = avg length of words in words1,words2 respectively
// S.C O(1) as we only use fixed-size vectors of size 26 for character frequencies.
class Solution {
public:
   // Helper function to check if freq2 (combined frequencies of words2) is a subset of temp (frequency of current word1)
   bool isSubset(vector<int>& freq2, vector<int>& temp){
      // Check for each character if the required frequency is available in word1
      for (int i = 0; i < 26; i++) {
         if (temp[i] < freq2[i]) {
            return false;
         }
      }
      return true;
   }

   vector<string> wordSubsets(vector<string>& words1, vector<string>& words2){
      vector<string> result;

      // Store the maximum frequency required for each character from words2
      vector<int> freq2(26);

      for (string&word : words2) {
         // Temporary vector to store frequency of current word
         vector<int> temp(26, 0);

         // Calculate frequency of each character in current word
         for (char&ch : word) {
            temp[ch - 'a']++;
            // Update the maximum frequency required for each character
            freq2[ch - 'a'] = max(freq2[ch - 'a'], temp[ch - 'a']);
         }
      }

      // Check each word in words1 if it contains required frequencies
      for (string&word: words1) {
         // Calculate frequency of characters in current word
         vector<int> temp(26, 0);
         for (char&ch : word) {
            temp[ch - 'a']++;
         }

         // If current word has all required characters with sufficient frequency, add to result
         if (isSubset(freq2, temp)) {
            result.push_back(word);
         }
      }

      return result;
   }
};
