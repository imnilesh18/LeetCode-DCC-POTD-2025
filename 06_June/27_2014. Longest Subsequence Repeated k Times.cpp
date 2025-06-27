/*
 * 2014. Longest Subsequence Repeated k Times
 *
 * Hard
 *
 * You are given a string s of length n, and an integer k. You are tasked to find the longest subsequence repeated k times in string s.
 *
 * A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
 *
 * A subsequence seq is repeated k times in the string s if seq * k is a subsequence of s, where seq * k represents a string constructed by concatenating seq k times.
 *
 * For example, "bba" is repeated 2 times in the string "bababcba", because the string "bbabba", constructed by concatenating "bba" 2 times, is a subsequence of the string "bababcba".
 * Return the longest subsequence repeated k times in string s. If multiple such subsequences are found, return the lexicographically largest one. If there is no such subsequence, return an empty string.
 *
 *
 * Example 1:
 * example 1
 * Input: s = "letsleetcode", k = 2
 * Output: "let"
 * Explanation: There are two longest subsequences repeated 2 times: "let" and "ete".
 * "let" is the lexicographically largest one.
 *
 * Example 2:
 * Input: s = "bb", k = 2
 * Output: "b"
 * Explanation: The longest subsequence repeated 2 times is "b".
 *
 * Example 3:
 * Input: s = "ab", k = 2
 * Output: ""
 * Explanation: There is no subsequence repeated 2 times. Empty string is returned.
 *
 * Constraints:
 * n == s.length
 * 2 <= n, k <= 2000
 * 2 <= n < k * 8
 */

// Approach: Use backtracking to build candidate subsequences up to max length (n/k) by trying each usable character in lexicographical order, checking via isSubsequence if repeating it k times fits into s, and keeping the best (longest, then lexicographically largest) result.
// Time Complexity: O(n * ((n/k)!)) – worst case explores all permutations of length up to n/k with an O(n) subsequence check each.
// Space Complexity: O(n/k) – recursion depth and current string length bounded by maxLen = n/k.
class Solution {
public:
    string result = "";  // stores the best subsequence found

    // checks if curr repeated k times is a subsequence of s
    bool isSubsequence(string& s, string& sub, int k) {
        int i = 0, j = 0;
        int L = sub.length(), n = s.length();

        while (i < n && j < k * L) {
            if (s[i] == sub[j % L]) {
                j++;
            }
            i++;
        }
        return j == k * L;
    }
    // backtracking helper to build subsequences
    void backtracking(string& s, string& curr, vector<bool>& canUse,
                      vector<int>& requiredFreq, int k, int maxLen) {
        // if we hit the max possible length, no need to go deeper
        if (curr.length() > maxLen) {
            return;
        }

        // if curr is a valid candidate and better than result, update
        if ((curr.length() > result.length() ||
             (curr.length() == result.length() && curr > result)) &&
            isSubsequence(s, curr, k)) {
            result = curr;
        }

        // try adding each character 'a' to 'z'
        for (int i = 0; i < 26; i++) {
            if (!canUse[i] || requiredFreq[i] == 0) {
                continue;
            }
            // choose
            char ch = 'a' + i;
            curr.push_back(ch);
            requiredFreq[i]--;
            // explore
            backtracking(s, curr, canUse, requiredFreq, k, maxLen);
            // undo
            curr.pop_back();
            requiredFreq[i]++;
        }
    }
    string longestSubsequenceRepeatedK(string s, int k) {
        int n        = s.length();
        int freq[26] = {};

        // count frequency of each char in s
        for (char& ch : s) {
            freq[ch - 'a']++;
        }

        vector<bool> canUse(26, false);
        vector<int>  requiredFreq(26, 0);
        // determine which chars appear at least k times and how many times they can appear in subsequence
        for (int i = 0; i < 26; ++i) {
            if (freq[i] >= k) {
                canUse[i]       = true;
                requiredFreq[i] = freq[i] / k;
            }
        }

        int    maxLen = n / k; // maximum possible length of subsequence
        string curr   = "";
        backtracking(s, curr, canUse, requiredFreq, k, maxLen);
        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Example: s = "letsleetcode", k = 2
 * n = 12, maxLen = 6
 * freq: {c:1,e:4,l:2,t:2,s:1,o:1,d:1}
 * canUse chars: l,e,t (others freq<2)
 * requiredFreq: l→1, e→2, t→1
 *
 * backtracking("", ...):
 *  try 'e': curr="e", requiredFreq e→1; isSubseq? "ee" in s? yes → result="e"
 *    then try 'e' again: curr="ee", e→0; "eeee"? no; backtrack.
 *    try 'l': curr="el", l→0; "elel"? yes → result="el"
 *      then 't': curr="elt", t→0; "eltelt"? yes → result="elt"
 *      ...
 *    backtrack; try 't': curr="et", t→0; "et et"? yes → but "elt" > "et"
 * backtracking continues exploring all combos up to length 3; final result="let"
 */
