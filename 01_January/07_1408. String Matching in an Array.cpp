/*
 * 1408. String Matching in an Array
 *
 * Given an array of string words, return all strings in words that is a substring of another word. You can return the answer in any order.
 * A substring is a contiguous sequence of characters within a string
 *
 * Example 1:
 * Input: words = ["mass","as","hero","superhero"]
 * Output: ["as","hero"]
 * Explanation: "as" is substring of "mass" and "hero" is substring of "superhero".
 * ["hero","as"] is also a valid answer.
 *
 * Example 2:
 * Input: words = ["leetcode","et","code"]
 * Output: ["et","code"]
 * Explanation: "et", "code" are substring of "leetcode".
 *
 * Example 3:
 * Input: words = ["blue","green","bu"]
 * Output: []
 * Explanation: No string of words is substring of another string.
 *
 * Constraints:
 * 1 <= words.length <= 100
 * 1 <= words[i].length <= 30
 * words[i] contains only lowercase English letters.
 * All the strings of words are unique.
 */

// Approach: Use two nested loops to check if each word is a substring of any other word in the array and store the matching substrings.
// Time Complexity: O(n^2 * m), where n is the number of words and m is the average word length, due to pairwise comparisons and substring checks.
// Space Complexity: O(k), where k is the number of matching substrings stored in the result.
class Solution {
public:
   vector<string> stringMatching(vector<string>& words){
      int            n = words.size(); // Get the size of the input array `words`
      vector<string> result;           // Initialize a vector to store the result strings

      // Iterate over each word in the array
      for (int i = 0; i < n; i++) {
         // Compare the current word with all other words
         for (int j = 0; j < n; j++) {
            // Skip comparing the word with itself
            if (i == j) {
               continue;
            }

            // Check if the current word `words[i]` is a substring of `words[j]`
            if (words[j].find(words[i]) != string::npos) {
               result.push_back(words[i]); // Add the word to the result vector
               break;                      // Break the inner loop as we only need to add the word once
            }
         }
      }

      return result;   // Return the result vector containing substrings
   }
};
