/*
 * 1092. Shortest Common Supersequence
 * (Solve First : Shortest Common Supersequence GfG
 * GfG Link: https://www.geeksforgeeks.org/problems/shortest-common-supersequence0322/1)
 *
 * Given two strings str1 and str2, return the shortest string that has both str1 and str2 as subsequences. If there are multiple valid strings, return any of them.
 *
 * A string s is a subsequence of string t if deleting some number of characters from t (possibly 0) results in the string s.
 *
 * Example 1:
 * Input: str1 = "abac", str2 = "cab"
 * Output: "cabac"
 * Explanation:
 * str1 = "abac" is a subsequence of "cabac" because we can delete the first "c".
 * str2 = "cab" is a subsequence of "cabac" because we can delete the last "ac".
 * The answer provided is the shortest such string that satisfies these properties.
 *
 * Example 2:
 * Input: str1 = "aaaaaaaa", str2 = "aaaaaaaa"
 * Output: "aaaaaaaa"
 *
 * Constraints:
 * 1 <= str1.length, str2.length <= 1000
 * str1 and str2 consist of lowercase English letters.
 */

// Approach: Use dynamic programming to build a DP table that stores the length of the shortest common supersequence (SCS) for every substring pair of s1 and s2, then backtrack from dp[m][n] to construct the SCS.
// T.C: O(m*n) because we fill a DP table of size (m+1)x(n+1) with two nested loops.
// S.C: O(m*n) due to the storage required for the DP table.
class Solution {
public:
   string shortestCommonSupersequence(string s1, string s2) {
      int m = s1.length();
      int n = s2.length();

      // Create a DP table with dimensions (m+1) x (n+1)
      vector<vector<int> > t(m + 1, vector<int>(n + 1));

      // Fill the DP table: if one string is empty, SCS length is simply the sum of indices (i or j)
      for (int i = 0; i <= m; i++) {
         for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
               t[i][j] = i + j;
            }else if (s1[i - 1] == s2[j - 1]) {
               t[i][j] = 1 + t[i - 1][j - 1];
            }else{
               t[i][j] = 1 + min(t[i - 1][j], t[i][j - 1]);
            }
         }
      }

      string scs = "";
      int    i = m, j = n;
      // Backtrack from t[m][n] to build the SCS string
      while (i > 0 && j > 0) {
         if (s1[i - 1] == s2[j - 1]) {
            scs.push_back(s1[i - 1]);
            i--;
            j--;
         } else {
            if (t[i - 1][j] < t[i][j - 1]) {
               scs.push_back(s1[i - 1]);
               i--;
            } else {
               scs.push_back(s2[j - 1]);
               j--;
            }
         }
      }

      // Append remaining characters from s1, if any
      while (i > 0) {
         scs.push_back(s1[i - 1]);
         i--;
      }
      // Append remaining characters from s2, if any
      while (j > 0) {
         scs.push_back(s2[j - 1]);
         j--;
      }

      // Reverse the constructed string as it was built backwards
      reverse(scs.begin(), scs.end());

      return scs;
   }
};

/*
 * Dry Run:
 * Input: s1 = "abac", s2 = "cab"
 * DP Table Initialization:
 *   dp[0][0]=0, dp[0][1]=1, dp[0][2]=2, dp[0][3]=3
 *   dp[1][0]=1, dp[2][0]=2, dp[3][0]=3, dp[4][0]=4
 * DP Table Filling:
 *   For i=1 (s1[0]='a'):
 *       j=1: s2[0]='c' -> not equal -> dp[1][1]=1+min(1,1)=2
 *       j=2: s2[1]='a' -> equal -> dp[1][2]=1+dp[0][1]=2
 *       j=3: s2[2]='b' -> not equal -> dp[1][3]=1+min(3,2)=3
 *   For i=2 (s1[1]='b'):
 *       j=1: s2[0]='c' -> not equal -> dp[2][1]=1+min(2,2)=3
 *       j=2: s2[1]='a' -> not equal -> dp[2][2]=1+min(2,3)=3
 *       j=3: s2[2]='b' -> equal -> dp[2][3]=1+dp[1][2]=3
 *   For i=3 (s1[2]='a'):
 *       j=1: s2[0]='c' -> not equal -> dp[3][1]=1+min(3,3)=4
 *       j=2: s2[1]='a' -> equal -> dp[3][2]=1+dp[2][1]=4
 *       j=3: s2[2]='b' -> not equal -> dp[3][3]=1+min(3,4)=4
 *   For i=4 (s1[3]='c'):
 *       j=1: s2[0]='c' -> equal -> dp[4][1]=1+dp[3][0]=4
 *       j=2: s2[1]='a' -> not equal -> dp[4][2]=1+min(4,4)=5
 *       j=3: s2[2]='b' -> not equal -> dp[4][3]=1+min(4,5)=5
 * Backtracking to build SCS:
 *   Start at i=4, j=3: s1[3]='c', s2[2]='b' -> not equal, choose s1's character ('c') since dp[3][3] < dp[4][2] -> scs="c"
 *   i=3, j=3: s1[2]='a', s2[2]='b' -> not equal, choose s1's character ('a') since dp[2][3] < dp[3][2] -> scs="ca"
 *   i=2, j=3: s1[1]='b', s2[2]='b' -> equal -> add 'b' -> scs="cab", i=1, j=2
 *   i=1, j=2: s1[0]='a', s2[1]='a' -> equal -> add 'a' -> scs="caba", i=0, j=1
 *   i=0, j=1: Append remaining s2[0]='c' -> scs="cabac"
 * Reverse scs (currently built backwards) to get final SCS: "cabac"
 */
