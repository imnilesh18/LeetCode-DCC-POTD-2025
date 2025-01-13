/*
 * 3223. Minimum Length of String After Operations
 *
 * You are given a string s.
 * You can perform the following process on s any number of times:
 * Choose an index i in the string such that there is at least one character to the left of index i that is equal to s[i], and at least one character to the right that is also equal to s[i].
 * Delete the closest character to the left of index i that is equal to s[i].
 * Delete the closest character to the right of index i that is equal to s[i].
 * Return the minimum length of the final string s that you can achieve.
 *
 * Example 1:
 * Input: s = "abaacbcbb"
 * Output: 5
 * Explanation:
 * We do the following operations:
 * Choose index 2, then remove the characters at indices 0 and 3. The resulting string is s = "bacbcbb".
 * Choose index 3, then remove the characters at indices 0 and 5. The resulting string is s = "acbcb".
 *
 * Example 2:
 * Input: s = "aa"
 * Output: 2
 * Explanation:
 * We cannot perform any operations, so we return the length of the original string.
 *
 * Constraints:
 * 1 <= s.length <= 2 * 10^5
 * s consists only of lowercase English letters.
 */

// Approach 1: Count frequency of characters and handle triplets by reducing frequency by 2 when it reaches 3
// TC: O(n) where n is length of string as we traverse it once
// SC: O(1) as we use fixed size array of 26 characters
class Solution {
public:
   int minimumLength(string s){
      // Length of input string
      int n = s.length();

      // Array to store frequency of each character (a-z)
      vector<int> freq(26, 0);

      // Count frequency of each character
      for (int i = 0; i < n; i++) {
         // Increment frequency of current character
         freq[s[i] - 'a']++;

         // If frequency reaches 3, reduce by 2 to handle triplets
         if (freq[s[i] - 'a'] == 3) {
            freq[s[i] - 'a'] -= 2;
         }
      }

      // Calculate final string length by summing remaining frequencies
      int result = 0;
      for (int i = 0; i < 26; i++) {
         if (freq[i] == 0) {
            continue;
         }
         result += freq[i];
      }
      return result;
   }
};

// Approach 1 (Little Optimised): Count character frequencies and track deletions - when frequency reaches 3, delete 2 occurrences
// TC: O(n) where n is length of string as we traverse it once
// SC: O(1) as we use fixed size array of 26 characters
class Solution {
public:
   int minimumLength(string s){
      // Length of input string
      int n = s.length();

      // Array to store frequency of each character (a-z)
      vector<int> freq(26, 0);

      // Track number of characters deleted
      int deleted = 0;

      // Process each character in string
      for (int i = 0; i < n; i++) {
         // Increment frequency of current character
         freq[s[i] - 'a']++;

         // If frequency is 3, reduce it by 2 and increment deleted count
         if (freq[s[i] - 'a'] == 3) {
            freq[s[i] - 'a'] -= 2;
            deleted          += 2;
         }
      }

      // Return remaining length after deletions
      return n - deleted;
   }
};

// Approach 2: Count frequencies and for each character add 2 to result if frequency is even, 1 if odd
// TC: O(n) where n is length of string for counting frequencies
// SC: O(1) as we use fixed size array of 26 characters
class Solution {
public:
   int minimumLength(string s) {
       // Array to store frequency of each character (a-z)
       vector<int> freq(26, 0);
       
       // Count frequency of each character using range-based for loop
       for(char& ch: s) {
           freq[ch - 'a']++;
       }

       // Calculate result based on character frequencies
       int result = 0;
       for(int i = 0; i < 26; i++) {
           // Skip if character doesn't exist
           if(freq[i] == 0) {
               continue;
           }

           // Add 2 if frequency is even, 1 if odd
           if(freq[i] % 2 == 0) {
               result += 2;
           } else {
               result += 1;
           }
       }

       return result;
   }
};