/*
 * 2131. Longest Palindrome by Concatenating Two Letter Words
 *
 * Medium
 *
 * You are given an array of strings words. Each element of words consists of two lowercase English letters.
 * Create the longest possible palindrome by selecting some elements from words and concatenating them in any order. Each element can be selected at most once.
 * Return the length of the longest palindrome that you can create. If it is impossible to create any palindrome, return 0.
 * A palindrome is a string that reads the same forward and backward.
 *
 * Example 1:
 * Input: words = ["lc","cl","gg"]
 * Output: 6
 * Explanation: One longest palindrome is "lc" + "gg" + "cl" = "lcggcl", of length 6.
 * Note that "clgglc" is another longest palindrome that can be created.
 *
 * Example 2:
 * Input: words = ["ab","ty","yt","lc","cl","ab"]
 * Output: 8
 * Explanation: One longest palindrome is "ty" + "lc" + "cl" + "yt" = "tylcclyt", of length 8.
 * Note that "lcyttycl" is another longest palindrome that can be created.
 *
 * Example 3:
 * Input: words = ["cc","ll","xx"]
 * Output: 2
 * Explanation: One longest palindrome is "cc", of length 2.
 * Note that "ll" is another longest palindrome that can be created, and so is "xx".
 *
 * Constraints:
 * 1 <= words.length <= 10^5
 * words[i].length == 2
 * words[i] consists of lowercase English letters.
 */

// Approach: Use a hash map to count word occurrences and check for reverse pairs. For each reverse pair (e.g., "lc" and "cl"), add 4 to the result. Handle special case of identical pairs like "gg" which can sit in the center.
// Time Complexity: O(n), where n is the number of words — we iterate through the list once and then through the map.
// Space Complexity: O(n), for storing the frequencies of words in an unordered_map.
class Solution {
public:
    int longestPalindrome(vector<string>& words) {
        unordered_map<string, int> mp; // stores the count of each word

        int result = 0;

        for (string& word : words) {
            string reversedWord = word;             // create a reversed version of the word
            swap(reversedWord[0], reversedWord[1]); // swap the characters to reverse it

            if (mp[reversedWord] > 0) {             // if the reverse word exists in map
                result += 4;                        // they form a valid palindrome pair
                mp[reversedWord]--;                 // use one occurrence of the reverse word
            } else {
                mp[word]++;                         // store the current word for future reverse matches
            }
        }

        for (auto& it : mp) {
            string word  = it.first;
            int    count = it.second;

            if (word[0] == word[1] && count > 0) { // check for a word like "gg", "cc", "ll"
                result += 2;                       // can be placed in the center of the palindrome
                break;                             // only one such center word can be used
            }
        }

        return result; // return total length of longest possible palindrome
    }
};

/*
 *
 * Dry Run
 *
 * Input: words = ["lc","cl","gg"]
 *
 * 1. Initialize map: {}
 * 2. Process "lc":
 * - reversedWord = "cl"
 * - "cl" not in map -> mp["lc"] = 1
 * 3. Process "cl":
 * - reversedWord = "lc"
 * - "lc" found in map -> result += 4 -> result = 4, mp["lc"] = 0
 * 4. Process "gg":
 * - reversedWord = "gg" (same)
 * - not found in map -> mp["gg"] = 1
 *
 * Now map = { "gg": 1 }
 * Loop through map:
 * - "gg" has count > 0 and both letters are same -> result += 2 -> result = 6
 *
 * Final result: 6
 */
