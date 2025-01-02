/*
 * 2559. Count Vowel Strings in Ranges
 *
 * You are given a 0-indexed array of strings words and a 2D array of integers queries.
 * Each query queries[i] = [li, ri] asks us to find the number of strings present in the range li to ri (both inclusive) of words that start and end with a vowel.
 * Return an array ans of size queries.length, where ans[i] is the answer to the ith query.
 * Note that the vowel letters are 'a', 'e', 'i', 'o', and 'u'.
 *
 * Example 1:
 * Input: words = ["aba","bcb","ece","aa","e"], queries = [[0,2],[1,4],[1,1]]
 * Output: [2,3,0]
 * Explanation: The strings starting and ending with a vowel are "aba", "ece", "aa" and "e".
 * The answer to the query [0,2] is 2 (strings "aba" and "ece").
 * to query [1,4] is 3 (strings "ece", "aa", "e").
 * to query [1,1] is 0.
 * We return [2,3,0].
 *
 * Example 2:
 * Input: words = ["a","e","i"], queries = [[0,2],[0,1],[2,2]]
 * Output: [3,2,1]
 * Explanation: Every string satisfies the conditions, so we return [3,2,1].
 *
 * Constraints:
 * 1 <= words.length <= 10^5
 * 1 <= words[i].length <= 40
 * words[i] consists only of lowercase English letters.
 * sum(words[i].length) <= 3 * 10^5
 * 1 <= queries.length <= 10^5
 * 0 <= li <= ri < words.length
 */

// Approach: Use cumulative sum array to store count of valid words (words starting and ending with vowels) up to each index.
// For each query [l,r], result = cumSum[r] - cumSum[l-1] (if l > 0)
// Time Complexity: O(N + Q), where N is size of words array and Q is number of queries
// Space Complexity: O(N) for cumulative sum array
class Solution {
public:
   // Helper function to check if a character is a vowel
   bool isVowel(char&ch){
      if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
         return true;
      }
      return false;
   }

   vector<int> vowelStrings(vector<string>& words, vector<vector<int> >& queries){
      int Q = queries.size();    // Number of queries
      int N = words.size();      // Number of words

      // Vector to store result for each query
      vector<int> result(Q);

      // Vector to store cumulative sum of words that start and end with vowels
      vector<int> cumSum(N);
      int         sum = 0;

      // Build cumulative sum array
      for (int i = 0; i < N; i++) {
         // Check if current word starts and ends with vowel
         if (isVowel(words[i][0]) && isVowel(words[i].back())) {
            sum++;
         }
         cumSum[i] = sum;     // Store running sum at current index
      }

      // Process each query using cumulative sum array
      for (int i = 0; i < Q; i++) {
         int l = queries[i][0];     // Left boundary of current query
         int r = queries[i][1];     // Right boundary of current query

         // Calculate result using cumulative sum
         // If l > 0, subtract cumSum[l-1] to get count in range [l,r]
         // If l = 0, just take cumSum[r] as no subtraction needed
         result[i] = cumSum[r] - ((l > 0) ? cumSum[l - 1] : 0);
      }

      return result;
   }
};
