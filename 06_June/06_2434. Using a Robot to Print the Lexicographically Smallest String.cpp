/*
 * 2434. Using a Robot to Print the Lexicographically Smallest String
 *
 * Medium
 *
 * You are given a string s and a robot that currently holds an empty string t. Apply one of the following operations until s and t are both empty:
 *
 * Remove the first character of a string s and give it to the robot. The robot will append this character to the string t.
 * Remove the last character of a string t and give it to the robot. The robot will write this character on paper.
 * Return the lexicographically smallest string that can be written on the paper.
 *
 * Example 1:
 * Input: s = "zza"
 * Output: "azz"
 * Explanation: Let p denote the written string.
 * Initially p="", s="zza", t="".
 * Perform first operation three times p="", s="", t="zza".
 * Perform second operation three times p="azz", s="", t="".
 *
 * Example 2:
 * Input: s = "bac"
 * Output: "abc"
 * Explanation: Let p denote the written string.
 * Perform first operation twice p="", s="c", t="ba".
 * Perform second operation twice p="ab", s="c", t="".
 * Perform first operation p="ab", s="", t="c".
 * Perform second operation p="abc", s="", t="".
 *
 * Example 3:
 * Input: s = "bdda"
 * Output: "addb"
 * Explanation: Let p denote the written string.
 * Initially p="", s="bdda", t="".
 * Perform first operation four times p="", s="", t="bdda".
 * Perform second operation four times p="addb", s="", t="".
 *
 * Constraints:
 * 1 <= s.length <= 10^5
 * s consists of only English lowercase letters.
 */

// Approach: Use a greedy strategy with a stack `t` and simulate the robot operations. Keep track of the smallest character to the right for decision making.
// Time Complexity: O(n), where n is the length of string s. Each character is pushed and popped at most once.
// Space Complexity: O(n), used for auxiliary stack `t` and minCharToRight array.
class Solution {
public:
    string robotWithString(string s) {
        int n = s.length();               // Length of the input string s

        string t     = "";                // Stack to simulate robot holding string t
        string paper = "";                // Result string written on paper

        vector<char> minCharToRight(n);   // To store the minimum character from i to end

        minCharToRight[n - 1] = s[n - 1]; // Last element is itself the minimum

        // Fill minCharToRight from end to start
        for (int i = n - 2; i >= 0; i--) {
            minCharToRight[i] = min(minCharToRight[i + 1], s[i]);
        }

        int i = 0;
        // Traverse each character in s
        while (i < n) {
            t.push_back(s[i]); // Push character from s to t

            // Get the minimum character to the right (or current if at end)
            char minChar = (i + 1) < n ? minCharToRight[i + 1] : s[i];

            // While stack is not empty and top of t is <= minChar, pop and write to paper
            while (!t.empty() && t.back() <= minChar) {
                paper += t.back();
                t.pop_back();
            }
            i++;
        }

        // Write remaining characters from t to paper
        while (!t.empty()) {
            paper += t.back();
            t.pop_back();
        }

        return paper; // Return the lexicographically smallest result
    }
};

/*
 * Dry Run
 * Input: s = "bac"
 *
 * Step 1: Initialize t = "", paper = ""
 * Step 2: Precompute minCharToRight = ['a', 'a', 'c']
 *       index:       0    1    2
 *
 * Step 3:
 * i=0: push 'b' -> t = "b"
 *    minCharToRight[1] = 'a', 'b' > 'a' => do not pop
 *
 * i=1: push 'a' -> t = "ba"
 *    minCharToRight[2] = 'c'
 *    'a' <= 'c' => pop 'a' => paper = "a", t = "b"
 *    'b' <= 'c' => pop 'b' => paper = "ab", t = ""
 *
 * i=2: push 'c' -> t = "c"
 *    no more chars => pop 'c' => paper = "abc", t = ""
 *
 * Final Result: "abc"
 *
 */
