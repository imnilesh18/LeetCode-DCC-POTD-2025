/*
 * 1007. Minimum Domino Rotations For Equal Row
 *
 * Medium
 *
 * In a row of dominoes, tops[i] and bottoms[i] represent the top and bottom halves of the ith domino. (A domino is a tile with two numbers from 1 to 6 - one on each half of the tile.)
 * We may rotate the ith domino, so that tops[i] and bottoms[i] swap values.
 * Return the minimum number of rotations so that all the values in tops are the same, or all the values in bottoms are the same.
 * If it cannot be done, return -1.
 *
 * Example 1:
 * Input: tops = [2,1,2,4,2,2], bottoms = [5,2,6,2,3,2]
 * Output: 2
 * Explanation:
 * The first figure represents the dominoes as given by tops and bottoms: before we do any rotations.
 * If we rotate the second and fourth dominoes, we can make every value in the top row equal to 2, as indicated by the second figure.
 *
 * Example 2:
 * Input: tops = [3,5,1,2,3], bottoms = [3,6,3,3,4]
 * Output: -1
 * Explanation:
 * In this case, it is not possible to rotate the dominoes to make one row of values equal.
 *
 * Constraints:
 * 2 <= tops.length <= 2 * 10^4
 * bottoms.length == tops.length
 * 1 <= tops[i], bottoms[i] <= 6
 */

// Approach: Try all values from 1 to 6 and check if making all tops or all bottoms equal to that value is possible. Count the minimum rotations needed.
// Time Complexity: O(6 * N) = O(N), where N is the number of dominoes, because we iterate over each domino up to 6 times.
// Space Complexity: O(1), as we use only a constant amount of extra space.
class Solution {
public:

    // Helper function to check how many rotations needed to make all values equal to 'val'
    int find(vector<int>& tops, vector<int>& bottoms, int val) {
        int n = tops.size();

        int swapTop    = 0;      // count of rotations to bring 'val' to top
        int swapBottom = 0;      // count of rotations to bring 'val' to bottom

        for (int i = 0; i < n; i++) {
            // If val is not present in either top or bottom, it's impossible to make all equal to val
            if (tops[i] != val && bottoms[i] != val) {
                return -1;
            } else if (tops[i] != val) {
                // need to rotate to bring val to top
                swapTop++;
            } else if (bottoms[i] != val) {
                // need to rotate to bring val to bottom
                swapBottom++;
            }
        }

        return min(swapTop, swapBottom);     // return the minimal rotation needed
    }
    int minDominoRotations(vector<int>& tops, vector<int>& bottoms) {
        int result = INT_MAX;     // initialize result with max value

        // Try all values from 1 to 6 as possible candidates
        for (int val = 1; val <= 6; val++) {
            int swaps = find(tops, bottoms, val);     // get rotation count

            if (swaps != -1) {
                result = min(result, swaps);     // take the minimum over all valid results
            }
        }

        // If no valid value found, return -1
        return result == INT_MAX ? -1 : result;
    }
};

/*
 *
 * Dry Run
 * Input: tops = [2,1,2,4,2,2], bottoms = [5,2,6,2,3,2]
 * Trying all values from 1 to 6:
 * val = 1:
 * tops[0]=2, bottoms[0]=5 => neither is 1 => return -1
 * val = 2:
 * tops[0]=2 => ok
 * tops[1]=1, bottoms[1]=2 => rotate to top => swapTop++
 * tops[2]=2 => ok
 * tops[3]=4, bottoms[3]=2 => rotate to top => swapTop++
 * tops[4]=2 => ok
 * tops[5]=2 => ok
 * swapTop = 2, swapBottom = 1 => min = 1
 * val = 3:
 * tops[0]=2, bottoms[0]=5 => neither is 3 => return -1
 * val = 4:
 * tops[0]=2, bottoms[0]=5 => neither is 4 => return -1
 * val = 5:
 * tops[1]=1, bottoms[1]=2 => neither is 5 => return -1
 * val = 6:
 * tops[1]=1, bottoms[1]=2 => neither is 6 => return -1
 * Only val=2 is possible, and min rotation = 2
 * Output: 2
 */
