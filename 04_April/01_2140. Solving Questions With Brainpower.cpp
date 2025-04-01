/*
 * 2140. Solving Questions With Brainpower
 *
 * Medium
 *
 * You are given a 0-indexed 2D integer array questions where questions[i] = [pointsi, brainpoweri].
 *
 * The array describes the questions of an exam, where you have to process the questions in order (i.e., starting from question 0) and make a decision whether to solve or skip each question. Solving question i will earn you pointsi points but you will be unable to solve each of the next brainpoweri questions. If you skip question i, you get to make the decision on the next question.
 *
 * For example, given questions = [[3, 2], [4, 3], [4, 4], [2, 5]]:
 * If question 0 is solved, you will earn 3 points but you will be unable to solve questions 1 and 2.
 * If instead, question 0 is skipped and question 1 is solved, you will earn 4 points but you will be unable to solve questions 2 and 3.
 * Return the maximum points you can earn for the exam.
 *
 * Example 1:
 * Input: questions = [[3,2],[4,3],[4,4],[2,5]]
 * Output: 5
 * Explanation: The maximum points can be earned by solving questions 0 and 3.
 * - Solve question 0: Earn 3 points, will be unable to solve the next 2 questions
 * - Unable to solve questions 1 and 2
 * - Solve question 3: Earn 2 points
 * Total points earned: 3 + 2 = 5. There is no other way to earn 5 or more points.
 *
 * Example 2:
 * Input: questions = [[1,1],[2,2],[3,3],[4,4],[5,5]]
 * Output: 7
 * Explanation: The maximum points can be earned by solving questions 1 and 4.
 * - Skip question 0
 * - Solve question 1: Earn 2 points, will be unable to solve the next 2 questions
 * - Unable to solve questions 2 and 3
 * - Solve question 4: Earn 5 points
 * Total points earned: 2 + 5 = 7. There is no other way to earn 7 or more points.
 *
 * Constraints:
 * 1 <= questions.length <= 10^5
 * questions[i].length == 2
 * 1 <= pointsi, brainpoweri <= 10^5
 */

// Approach 1 (Recursion + Memoization): Use recursion with memoization (top-down DP) to decide for each question whether to solve it or skip it.
// Time Complexity: O(n) because each index is computed only once using memoization.
// Space Complexity: O(n) due to the memoization table and recursion call stack.
class Solution {
public:
    int n;

    // Recursive function to compute maximum points from question i onward.
    long long solve(int i, vector<vector<int> >& q, vector<long long>& t) {
        if (i >= n) {    // Base case: no more questions.
            return 0;
        }
        if (t[i] != -1) {    // Return memoized result if available.
            return t[i];
        }
        // Option 1: Solve the current question.
        long long taken = q[i][0] + solve(i + q[i][1] + 1, q, t);
        // Option 2: Skip the current question.
        long long not_taken = solve(i + 1, q, t);

        // Return the maximum points achievable from the current state.
        return t[i] = max(taken, not_taken);
    }
    // Main function to compute the maximum points for the exam.
    long long mostPoints(vector<vector<int> >& q) {
        n = q.size();
        vector<long long> t(n + 1, -1);      // Initialize memoization table.
        return solve(0, q, t);
    }
};

/*
 * Detailed Dry Run with a Vertical Tree Diagram
 * ------------------------------------------------------------
 * For questions = [[3,2], [4,3], [4,4], [2,5]]
 *
 * Let f(i) denote the maximum points obtainable starting from question i.
 * Each question is denoted as: Q[index]: [points, brainpower]
 *
 * Questions:
 *  Q0: [3,2]
 *  Q1: [4,3]
 *  Q2: [4,4]
 *  Q3: [2,5]
 *
 * Detailed Vertical Tree Diagram :
 *
 *                       f(0): Q0 [3,2]
 *                          /         \
 *               TAKE Q0: +3          SKIP Q0: → f(1)
 *                   |                        |
 *         f(0+2+1)=f(3)                 f(1): Q1 [4,3]
 *                   |                        /         \
 *            f(3): Q3 [2,5]       TAKE Q1: +4       SKIP Q1: → f(2)
 *                   |                  |                  |
 *        f(3+5+1)=f(9)=0       f(1+3+1)=f(5)=0       f(2): Q2 [4,4]
 *                   |                                    /       \
 *         TAKE Q3: +2                        TAKE Q2: +4     SKIP Q2: → f(3)
 *                   |                                |             |
 *              f(9)=0                         f(2+4+1)=f(7)=0   f(3)=2 (computed)
 *
 * Evaluations at the Leaves:
 *    f(3) = max( TAKE Q3: 2 + f(9)=2+0,  SKIP Q3: f(4)=0 ) = max(2, 0) = 2
 *    f(2) = max( TAKE Q2: 4 + f(7)=4+0,  SKIP Q2: f(3)=2 )   = max(4, 2) = 4
 *    f(1) = max( TAKE Q1: 4 + f(5)=4+0,  SKIP Q1: f(2)=4 )   = max(4, 4) = 4
 *    f(0) = max( TAKE Q0: 3 + f(3)=3+2,  SKIP Q0: f(1)=4 )   = max(5, 4) = 5
 *
 * Final Maximum Points: 5
 */

// Approach 2 (Bootom-Up): Bottom-up dynamic programming (tabulation) where dp[i] stores the maximum points obtainable from question i to the end.
// Time Complexity: O(n) because we process each question exactly once in reverse order.
// Space Complexity: O(n) due to the dp (t) array used to store intermediate results.
class Solution {
public:
    long long mostPoints(vector<vector<int> >& q) {
        int n = q.size();

        // If there's only one question, return its points.
        if (n == 1) {
            return q[0][0];
        }

        // Using a dp table 't' of size 200001 to handle index accesses safely.
        // t[i] represents the maximum points from question i to the end.
        vector<long long> t(200001, 0);

        // Build the dp table in a bottom-up manner (from the last question to the first).
        for (int i = n - 1; i >= 0; i--) {
            t[i] = max(q[i][0] + t[i + q[i][1] + 1], t[i + 1]);
        }

        return t[0];
    }
};

/*
 *
 * Dry Run:
 * For questions = [[3,2], [4,3], [4,4], [2,5]]
 * Let:
 *   Q0: [3,2]
 *   Q1: [4,3]
 *   Q2: [4,4]
 *   Q3: [2,5]
 *
 * Note: We will show dp array (t) for indices 0 to 9 (others remain 0).
 *
 * Initial dp array (t): (all values are 0)
 * +------+------+------+------+------+------+------+------+------+------+
 * | t[0] | t[1] | t[2] | t[3] | t[4] | t[5] | t[6] | t[7] | t[8] | t[9] |
 * +------+------+------+------+------+------+------+------+------+------+
 * |  0   |  0   |  0   |  0   |  0   |  0   |  0   |  0   |  0   |  0   |
 * +------+------+------+------+------+------+------+------+------+------+
 *
 * Iteration i = 3 (Processing Q3: [2,5]):
 *   Calculation:
 *     TAKE Q3: 2 + t[3+5+1] = 2 + t[9] = 2 + 0 = 2
 *     SKIP Q3: t[4] = 0
 *     t[3] = max(2, 0) = 2
 *
 * Updated dp array after i = 3:
 * +------+------+------+------+------+------+------+------+------+------+
 * | t[0] | t[1] | t[2] | t[3] | t[4] | t[5] | t[6] | t[7] | t[8] | t[9] |
 * +------+------+------+------+------+------+------+------+------+------+
 * |  0   |  0   |  0   |  2   |  0   |  0   |  0   |  0   |  0   |  0   |
 * +------+------+------+------+------+------+------+------+------+------+
 *
 * Iteration i = 2 (Processing Q2: [4,4]):
 *   Calculation:
 *     TAKE Q2: 4 + t[2+4+1] = 4 + t[7] = 4 + 0 = 4
 *     SKIP Q2: t[3] = 2
 *     t[2] = max(4, 2) = 4
 *
 * Updated dp array after i = 2:
 * +------+------+------+------+------+------+------+------+------+------+
 * | t[0] | t[1] | t[2] | t[3] | t[4] | t[5] | t[6] | t[7] | t[8] | t[9] |
 * +------+------+------+------+------+------+------+------+------+------+
 * |  0   |  0   |  4   |  2   |  0   |  0   |  0   |  0   |  0   |  0   |
 * +------+------+------+------+------+------+------+------+------+------+
 *
 * Iteration i = 1 (Processing Q1: [4,3]):
 *   Calculation:
 *     TAKE Q1: 4 + t[1+3+1] = 4 + t[5] = 4 + 0 = 4
 *     SKIP Q1: t[2] = 4
 *     t[1] = max(4, 4) = 4
 *
 * Updated dp array after i = 1:
 * +------+------+------+------+------+------+------+------+------+------+
 * | t[0] | t[1] | t[2] | t[3] | t[4] | t[5] | t[6] | t[7] | t[8] | t[9] |
 * +------+------+------+------+------+------+------+------+------+------+
 * |  0   |  4   |  4   |  2   |  0   |  0   |  0   |  0   |  0   |  0   |
 * +------+------+------+------+------+------+------+------+------+------+
 *
 * Iteration i = 0 (Processing Q0: [3,2]):
 *   Calculation:
 *     TAKE Q0: 3 + t[0+2+1] = 3 + t[3] = 3 + 2 = 5
 *     SKIP Q0: t[1] = 4
 *     t[0] = max(5, 4) = 5
 *
 * Updated dp array after i = 0 (final dp array):
 * +------+------+------+------+------+------+------+------+------+------+
 * | t[0] | t[1] | t[2] | t[3] | t[4] | t[5] | t[6] | t[7] | t[8] | t[9] |
 * +------+------+------+------+------+------+------+------+------+------+
 * |  5   |  4   |  4   |  2   |  0   |  0   |  0   |  0   |  0   |  0   |
 * +------+------+------+------+------+------+------+------+------+------+
 *
 * Final Maximum Points: t[0] = 5
 *
 */
