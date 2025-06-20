/*
 * 3443. Maximum Manhattan Distance After K Changes
 *
 * Medium
 *
 * You are given a string s consisting of the characters 'N', 'S', 'E', and 'W', where s[i] indicates movements in an infinite grid:
 *
 * 'N' : Move north by 1 unit.
 * 'S' : Move south by 1 unit.
 * 'E' : Move east by 1 unit.
 * 'W' : Move west by 1 unit.
 * Initially, you are at the origin (0, 0). You can change at most k characters to any of the four directions.
 * Find the maximum Manhattan distance from the origin that can be achieved at any time while performing the movements in order.
 * The Manhattan Distance between two cells (xi, yi) and (xj, yj) is |xi - xj| + |yi - yj|.
 *
 * Example 1:
 * Input: s = "NWSE", k = 1
 * Output: 3
 * Explanation:
 * Change s[2] from 'S' to 'N'. The string s becomes "NWNE".
 * Movement	Position (x, y)	Manhattan Distance	Maximum
 * s[0] == 'N'	(0, 1)	0 + 1 = 1	1
 * s[1] == 'W'	(-1, 1)	1 + 1 = 2	2
 * s[2] == 'N'	(-1, 2)	1 + 2 = 3	3
 * s[3] == 'E'	(0, 2)	0 + 2 = 2	3
 * The maximum Manhattan distance from the origin that can be achieved is 3. Hence, 3 is the output.
 *
 * Example 2:
 * Input: s = "NSWWEW", k = 3
 * Output: 6
 * Explanation:
 * Change s[1] from 'S' to 'N', and s[4] from 'E' to 'W'. The string s becomes "NNWWWW".
 * The maximum Manhattan distance from the origin that can be achieved is 6. Hence, 6 is the output.
 *
 * Constraints:
 * 1 <= s.length <= 10^5
 * 0 <= k <= s.length
 * s consists of only 'N', 'S', 'E', and 'W'.
 */

/*
 * Intuition:
 *
 * 4 Key Observations from the Problem
 *
 * 1. **East - West → Horizontal Displacement**
 *
 * The difference `east - west` gives the **net movement along the X-axis** (horizontal direction).
 * E.g., if `east = 3` and `west = 2`, then net horizontal movement = `|3 - 2| = 1`.
 *
 * 2. **North - South → Vertical Displacement**
 *
 * The difference `north - south` gives the **net movement along the Y-axis** (vertical direction).
 * E.g., if `north = 4` and `south = 1`, then net vertical movement = `|4 - 1| = 3`.
 *
 * 3. **Wasted Steps = Total Steps - Manhattan Distance**
 *
 * Total steps so far = `i + 1`.
 * Manhattan Distance = `|east - west| + |north - south|`.
 * So, `wasted = steps - MD`. These are the steps that cancel each other out (like moving E then W or N then S).
 *
 * 4. **At most 2\*k wasted steps can be converted to improve distance**
 *
 * Each change can fix **1 wasted step**, and each fixed step can boost MD by 2 (changing a canceling step to go in a useful direction).
 * Hence, max boost from `k` changes = `2 * k`.
 * So, extra distance we can add = `min(wasted, 2 * k)`.
 */

/*
 * How These Are Used in the Code
 *
 * int currMD = abs(east - west) + abs(north - south);  // Combines observation 1 and 2
 * int steps = i + 1;
 * int wasted = steps - currMD;                         // Observation 3
 * int extra = min(2*k, wasted);                        // Observation 4
 * int finalCurrentMD = currMD + extra;
 *
 * All four observations are **efficiently baked into these few lines**, making the logic compact but powerful.
 */

// Approach: Count net movement in x (E-W) and y (N-S) directions; use up to 2*k wasted steps to increase distance.
// Time Complexity: O(n), where n = s.length(), since we traverse the string once.
// Space Complexity: O(1), as we use only constant extra space.
class Solution {
public:
    int maxDistance(string s, int k) {
        int maxMD = 0;

        int east  = 0;  // Track total steps east
        int west  = 0;  // Track total steps west
        int north = 0;  // Track total steps north
        int south = 0;  // Track total steps south

        for (int i = 0; i < s.length(); i++) {
            // Count movement in respective directions
            if (s[i] == 'E') {
                east++;
            }else if (s[i] == 'W') {
                west++;
            }else if (s[i] == 'N') {
                north++;
            }else if (s[i] == 'S') {
                south++;
            }

            // Manhattan distance at current step
            int currMD = abs(east - west) + abs(north - south);

            // Total steps taken so far
            int steps = i + 1;

            // Wasted steps are those that cancel each other out (e.g., E followed by W)
            int wasted = steps - currMD;

            int extra = 0;

            // We can convert at most 2*k of these wasted steps to help MD
            if (wasted != 0) {
                extra = min(2 * k, wasted);
            }

            // Final distance including max possible benefit from k changes
            int finalCurrentMD = currMD + extra;

            // Track maximum Manhattan distance
            maxMD = max(maxMD, finalCurrentMD);
        }

        return maxMD;
    }
};

/*
 *
 * Dry Run
 * Input: s = "NWSE", k = 1
 * Let’s go step-by-step:
 *
 * Step 0: s[0] = 'N'
 * north = 1, position = (0,1), currMD = |0-0| + |1-0| = 1
 * steps = 1, wasted = 0 → extra = 0 → finalCurrentMD = 1 → maxMD = 1
 *
 * Step 1: s[1] = 'W'
 * west = 1, position = (-1,1), currMD = |0-1| + |1-0| = 2
 * steps = 2, wasted = 0 → extra = 0 → finalCurrentMD = 2 → maxMD = 2
 *
 * Step 2: s[2] = 'S'
 * south = 1, position = (-1,0), currMD = |0-1| + |1-1| = 1
 * steps = 3, wasted = 2 → extra = min(2*k=2, wasted=2) = 2
 * finalCurrentMD = 1+2 = 3 → maxMD = 3
 *
 * Step 3: s[3] = 'E'
 * east = 1, position = (0,0), currMD = |1-1| + |1-1| = 0
 * steps = 4, wasted = 4 → extra = min(2*k=2, wasted=4) = 2
 * finalCurrentMD = 0+2 = 2 → maxMD stays 3
 *
 * Final Answer = 3
 */
