/*
 * 909. Snakes and Ladders
 *
 * Medium
 *
 * You are given an n x n integer matrix board where the cells are labeled from 1 to n2 in a Boustrophedon style starting from the bottom left of the board (i.e. board[n - 1][0]) and alternating direction each row.
 *
 * You start on square 1 of the board. In each move, starting from square curr, do the following:
 *
 * Choose a destination square next with a label in the range [curr + 1, min(curr + 6, n2)].
 * This choice simulates the result of a standard 6-sided die roll: i.e., there are always at most 6 destinations, regardless of the size of the board.
 * If next has a snake or ladder, you must move to the destination of that snake or ladder. Otherwise, you move to next.
 * The game ends when you reach the square n2.
 * A board square on row r and column c has a snake or ladder if board[r][c] != -1. The destination of that snake or ladder is board[r][c]. Squares 1 and n2 are not the starting points of any snake or ladder.
 *
 * Note that you only take a snake or ladder at most once per dice roll. If the destination to a snake or ladder is the start of another snake or ladder, you do not follow the subsequent snake or ladder.
 *
 * For example, suppose the board is [[-1,4],[-1,3]], and on the first move, your destination square is 2. You follow the ladder to square 3, but do not follow the subsequent ladder to 4.
 * Return the least number of dice rolls required to reach the square n2. If it is not possible to reach the square, return -1.
 *
 * Example 1:
 * Input: board = [[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,35,-1,-1,13,-1],[-1,-1,-1,-1,-1,-1],[-1,15,-1,-1,-1,-1]]
 * Output: 4
 * Explanation:
 * In the beginning, you start at square 1 (at row 5, column 0).
 * You decide to move to square 2 and must take the ladder to square 15.
 * You then decide to move to square 17 and must take the snake to square 13.
 * You then decide to move to square 14 and must take the ladder to square 35.
 * You then decide to move to square 36, ending the game.
 * This is the lowest possible number of moves to reach the last square, so return 4.
 *
 * Example 2:
 * Input: board = [[-1,-1],[-1,3]]
 * Output: 1
 *
 * Constraints:
 * n == board.length == board[i].length
 * 2 <= n <= 20
 * board[i][j] is either -1 or in the range [1, n2].
 * The squares labeled 1 and n2 are not the starting points of any snake or ladder.
 */

// Approach: Use BFS to simulate the shortest path from square 1 to n^2, where each dice roll gives 1-6 choices.
// Time Complexity: O(n^2), as each cell is visited at most once.
// Space Complexity: O(n^2), due to visited and queue storage.
class Solution {
public:
    int n;

    // Function to convert square number (1-indexed) to matrix coordinates.
    pair<int, int> getCoord(int s) {
        int row = n - 1 - (s - 1) / n; // Convert to matrix row from bottom to top.
        int col = (s - 1) % n;         // Column from left to right normally.

        // Flip column direction based on current row to match Boustrophedon order.
        if ((n % 2 == 1 && row % 2 == 1) || (n % 2 == 0 && row % 2 == 0)) {
            col = n - 1 - col;
        }

        return make_pair(row, col);
    }
    int snakesAndLadders(vector<vector<int> >& board) {
        n = board.size();

        int        steps = 0;
        queue<int> que;                                           // BFS queue to store next possible cells.

        vector<vector<bool> > visited(n, vector<bool>(n, false)); // To mark cells already visited.
        visited[n - 1][0] = true;                                 // Start from square 1, which is at (n-1, 0).

        que.push(1);                                              // Begin BFS from square 1.

        while (!que.empty()) {
            int N = que.size(); // Number of elements at current BFS level.

            while (N--) {
                int x = que.front(); // Current square number.
                que.pop();

                if (x == n * n) {
                    return steps; // If we reach the last square, return step count.
                }
                for (int k = 1; k <= 6; k++) {
                    if (x + k > n * n) {
                        break; // Dice roll can't exceed board.
                    }
                    pair<int, int> coord = getCoord(x + k);
                    int            r     = coord.first;
                    int            c     = coord.second;

                    if (visited[r][c]) {
                        continue; // Skip already visited.
                    }
                    visited[r][c] = true;

                    // If no snake or ladder, move to cell (x+k), else jump to destination.
                    if (board[r][c] == -1) {
                        que.push(x + k);
                    }else{
                        que.push(board[r][c]);
                    }
                }
            }
            steps++; // Increment level = one dice roll.
        }

        return -1; // If target square is unreachable.
    }
};

/*
 *
 * Dry Run
 *
 * Input:
 * board = [[-1,-1,-1,-1,-1,-1],
 *       [-1,-1,-1,-1,-1,-1],
 *       [-1,-1,-1,-1,-1,-1],
 *       [-1,35,-1,-1,13,-1],
 *       [-1,-1,-1,-1,-1,-1],
 *       [-1,15,-1,-1,-1,-1]]
 *
 * Initial State:
 * n = 6, Target square = 36
 *
 * Step 0:
 * Start at square 1 → Push 2 to 7 into queue
 *
 * Step 1:
 * - Square 2 has ladder to 15 → push 15
 * - Square 3 → push 3
 * - Square 4 → push 4
 * - Square 5 → push 5
 * - Square 6 → push 6
 * - Square 7 → push 7
 *
 * Queue: [15, 3, 4, 5, 6, 7]
 *
 * Step 2:
 * - From 15 → push 16 to 21
 * - From 17 → snake to 13 → push 13
 * - Others follow similarly
 *
 * Eventually:
 * - Reach 14 → ladder to 35 → push 35
 * - From 35, push 36
 *
 * Total steps: 4
 *
 * Output: 4
 *
 */
