/*
 * 3160. Find the Number of Distinct Colors Among the Balls
 *
 * You are given an integer limit and a 2D array queries of size n x 2.
 * There are limit + 1 balls with distinct labels in the range [0, limit]. Initially, all balls are uncolored. For every query in queries that is of the form [x, y], you mark ball x with the color y. After each query, you need to find the number of distinct colors among the balls.
 * Return an array result of length n, where result[i] denotes the number of distinct colors after ith query.
 * Note that when answering a query, lack of a color will not be considered as a color.
 *
 * Example 1:
 * Input: limit = 4, queries = [[1,4],[2,5],[1,3],[3,4]]
 * Output: [1,2,2,3]
 * Explanation:
 * After query 0, ball 1 has color 4.
 * After query 1, ball 1 has color 4, and ball 2 has color 5.
 * After query 2, ball 1 has color 3, and ball 2 has color 5.
 * After query 3, ball 1 has color 3, ball 2 has color 5, and ball 3 has color 4.
 *
 * Example 2:
 * Input: limit = 4, queries = [[0,1],[1,2],[2,2],[3,4],[4,5]]
 * Output: [1,2,2,3,4]
 * Explanation:
 * After query 0, ball 0 has color 1.
 * After query 1, ball 0 has color 1, and ball 1 has color 2.
 * After query 2, ball 0 has color 1, and balls 1 and 2 have color 2.
 * After query 3, ball 0 has color 1, balls 1 and 2 have color 2, and ball 3 has color 4.
 * After query 4, ball 0 has color 1, balls 1 and 2 have color 2, ball 3 has color 4, and ball 4 has color 5.
 *
 * Constraints:
 * 1 <= limit <= 10^9
 * 1 <= n == queries.length <= 10^5
 * queries[i].length == 2
 * 0 <= queries[i][0] <= limit
 * 1 <= queries[i][1] <= 10^9
 */

// Approach: Use two hash maps—'ballmp' to track each ball's current color and 'colormp' to count the frequency of each color.
// For every query, update the ball's color by adjusting the counts in 'colormp' (decrement for the old color, increment for the new color),
// and then record the current number of distinct colors (the size of 'colormp').
// Time Complexity: O(n) - Each query is processed in constant time.
// Space Complexity: O(n) - In the worst case, each query colors a different ball or uses a different color.
class Solution {
public:
   vector<int> queryResults(int limit, vector<vector<int> >& queries) {
      int                     n = queries.size();
      vector<int>             result(n);         // Stores the number of distinct colors after each query.
      unordered_map<int, int> colormp;           // Maps each color to its frequency among the balls.
      unordered_map<int, int> ballmp;            // Maps each ball to its current color.

      for (int i = 0; i < n; i++) {
         int ball  = queries[i][0];                // The ball to be updated.
         int color = queries[i][1];                // The new color for the ball.

         // If the ball is already colored, update the frequency of its previous color.
         if (ballmp.count(ball)) {
            int prevColor = ballmp[ball];
            colormp[prevColor]--;                  // Decrement frequency of the previous color.
            if (colormp[prevColor] == 0) {         // Remove the color if its frequency becomes zero.
               colormp.erase(prevColor);
            }
         }

         // Update the ball's color and increment the frequency for the new color.
         ballmp[ball] = color;
         colormp[color]++;

         // Record the current number of distinct colors.
         result[i] = colormp.size();
      }

      return result;
   }
};

/*
 * Dry Run (Example: limit = 4, queries = [[1,4],[2,5],[1,3],[3,4]]):
 * Query 0: ball 1 gets color 4. ballmp = {1:4}, colormp = {4:1}. Distinct colors = 1.
 * Query 1: ball 2 gets color 5. ballmp = {1:4, 2:5}, colormp = {4:1, 5:1}. Distinct colors = 2.
 * Query 2: ball 1 gets color 3. Update: ballmp becomes {1:3, 2:5} and colormp updates from {4:1, 5:1} to {5:1, 3:1} (color 4 removed). Distinct colors = 2.
 * Query 3: ball 3 gets color 4. ballmp = {1:3, 2:5, 3:4}, colormp = {5:1, 3:1, 4:1}. Distinct colors = 3.
 */
