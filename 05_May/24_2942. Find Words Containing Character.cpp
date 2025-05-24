/*
 * 2942. Find Words Containing Character
 *
 * Easy
 *
 * You are given a 0-indexed array of strings words and a character x.
 * Return an array of indices representing the words that contain the character x.
 * Note that the returned array may be in any order.
 *
 * Example 1:
 * Input: words = ["leet","code"], x = "e"
 * Output: [0,1]
 * Explanation: "e" occurs in both words: "leet", and "code". Hence, we return indices 0 and 1.
 *
 * Example 2:
 * Input: words = ["abc","bcd","aaaa","cbc"], x = "a"
 * Output: [0,2]
 * Explanation: "a" occurs in "abc", and "aaaa". Hence, we return indices 0 and 2.
 *
 * Example 3:
 * Input: words = ["abc","bcd","aaaa","cbc"], x = "z"
 * Output: []
 * Explanation: "z" does not occur in any of the words. Hence, we return an empty array.
 *
 * Constraints:
 * 1 <= words.length <= 50
 * 1 <= words[i].length <= 50
 * x is a lowercase English letter.
 * words[i] consists only of lowercase English letters.
 */

// Approach: Traverse each word and check if the character 'x' exists using std::any_of and a lambda function.
// Time Complexity: O(N * M), where N is the number of words and M is the average length of each word.
// Space Complexity: O(1), excluding the space used by the output vector.
class Solution {
public:
    vector<int> findWordsContaining(vector<string>& words, char x) {
        vector<int> result;

        // Lambda function to check if a character is equal to x.
        // The [x] means we capture the variable x from the outer scope by value.
        // We can now use x inside the lambda, even though it's not a parameter.
        auto lambda = [x](char ch) {
                          return ch == x; // Returns true if character matches x
                      };

        for (int i = 0; i < words.size(); i++) {
            // any_of checks if any character in words[i] satisfies the lambda condition.
            // It returns true if at least one match is found.
            if (any_of(begin(words[i]), end(words[i]), lambda) == true) {
                result.push_back(i); // Store the index if the word contains the character x
            }
        }

        return result; // Return the result vector containing valid indices
    }
};

/*
 *
 * Dry Run
 *
 * Input: words = ["abc", "bcd", "aaaa", "cbc"], x = 'a'
 * Output: [0, 2]
 *
 * Step 1: Initialize result = []
 *
 * Step 2: i = 0 → word = "abc"
 *         any_of checks: 'a' == 'a' → true → push 0 into result
 *         result = [0]
 *
 * Step 3: i = 1 → word = "bcd"
 *         any_of checks: 'b' != 'a', 'c' != 'a', 'd' != 'a' → false → skip
 *         result = [0]
 *
 * Step 4: i = 2 → word = "aaaa"
 *         any_of checks: 'a' == 'a' → true → push 2 into result
 *         result = [0, 2]
 *
 * Step 5: i = 3 → word = "cbc"
 *         any_of checks: 'c' != 'a', 'b' != 'a', 'c' != 'a' → false → skip
 *         result = [0, 2]
 *
 * Final Output: [0, 2]
 *
 */
