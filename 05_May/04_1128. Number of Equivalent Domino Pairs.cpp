/*
 * 1128. Number of Equivalent Domino Pairs
 *
 * Easy
 *
 * Given a list of dominoes, dominoes[i] = [a, b] is equivalent to dominoes[j] = [c, d] if and only if either (a == c and b == d), or (a == d and b == c) - that is, one domino can be rotated to be equal to another domino.
 * Return the number of pairs (i, j) for which 0 <= i < j < dominoes.length, and dominoes[i] is equivalent to dominoes[j].
 *
 * Example 1:
 * Input: dominoes = [[1,2],[2,1],[3,4],[5,6]]
 * Output: 1
 *
 * Example 2:
 * Input: dominoes = [[1,2],[1,2],[1,1],[1,2],[2,2]]
 * Output: 3
 *
 * Constraints:
 * 1 <= dominoes.length <= 4 * 10^4
 * dominoes[i].length == 2
 * 1 <= dominoes[i][j] <= 9
 */

// Approach 1: Normalize each domino pair so that [a, b] and [b, a] are considered the same (by always storing the smaller value first), count occurrences using a map, and use the formula n*(n-1)/2 to count pairs.
// Time Complexity: O(n), where n is the number of dominoes — we loop over the list once and over the map once.
// Space Complexity: O(n), due to the extra space used by the map to count frequencies.
class Solution {
public:
    int numEquivDominoPairs(vector<vector<int> >& dominoes) {
        map<pair<int, int>, int> mp;      // map to store normalized domino pairs and their frequencies

        for (auto& d : dominoes) {
            if (d[0] > d[1]) {    // ensure the pair is ordered as (min, max)
                swap(d[0], d[1]);
            }
            mp[{ d[0], d[1] }]++;   // increment frequency of the normalized pair
        }

        int result = 0;

        for (auto& it : mp) {
            int freq = it.second;            // get frequency of each unique normalized pair

            result += freq * (freq - 1) / 2; // calculate number of unique pairs using combination formula C(n, 2)
        }

        return result;
    }
};

/*
 *
 * Dry Run 1:
 *
 * Input: dominoes = [[1,2],[1,2],[1,1],[2,1],[2,2]]
 *
 * Step 1: Normalize each domino pair so that the smaller number comes first:
 *   [1,2] -> [1,2]
 *   [1,2] -> [1,2]
 *   [1,1] -> [1,1]
 *   [2,1] -> [1,2] (swapped)
 *   [2,2] -> [2,2]
 *
 * Step 2: Count frequency of each normalized pair:
 *   (1,2): 3 times
 *   (1,1): 1 time
 *   (2,2): 1 time
 *
 * Step 3: Calculate the number of equivalent pairs using n*(n-1)/2:
 *   For (1,2): 3 * (3 - 1) / 2 = 3
 *   For (1,1): 1 * (1 - 1) / 2 = 0
 *   For (2,2): 1 * (1 - 1) / 2 = 0
 *
 * Result = 3
 * Output: 3
 *
 * Dry Run 2:
 *
 * Input: dominoes = [[1,2],[2,1],[3,4],[5,6]]
 * Step 1: Normalize pairs:
 *   [1,2] -> [1,2]
 *   [2,1] -> [1,2]
 *   [3,4] -> [3,4]
 *   [5,6] -> [5,6]
 * Normalized Map: {
 *   (1,2): 2,
 *   (3,4): 1,
 *   (5,6): 1
 *}
 * Step 2: For each frequency > 1, calculate pairs:
 *   (1,2): 2 -> 2 * (2 - 1) / 2 = 1
 * Result = 1
 * Output: 1
 *
 */

// Approach 2: Normalize each domino pair so that [a, b] and [b, a] are the same, encode it as a two-digit number (a*10 + b), count frequencies using a vector of size 100, and compute the result on the fly.
// Time Complexity: O(n), where n is the number of dominoes — single pass through the array.
// Space Complexity: O(1), since vector size is fixed at 100 irrespective of input size.
class Solution {
public:
    int numEquivDominoPairs(vector<vector<int> >& dominoes) {
        vector<int> vec(100);     // fixed-size vector to store frequency of encoded domino pairs

        int result = 0;

        for (auto& d : dominoes) {
            if (d[0] > d[1]) {
                swap(d[0], d[1]);     // ensure order (min, max)
            }

            int num = d[0] * 10 + d[1]; // encode pair as a unique number between 11 and 99

            result += vec[num];         // add current count to result (number of previous matches)

            vec[num]++;                 // increment count of this encoded pair
        }

        return result;
    }
};

/*
 *
 * Dry Run 1:
 *
 * Step 1: Normalize and encode domino pairs:
 *   [1,2] -> 12
 *   [1,2] -> 12
 *   [1,1] -> 11
 *   [2,1] -> [1,2] => 12
 *   [2,2] -> 22
 *
 * Step 2: Count matches while iterating:
 *   First [1,2] => count[12] = 0, result = 0
 *   Second [1,2] => count[12] = 1, result = 1
 *   [1,1] => count[11] = 0, result = 1
 *   [2,1] => count[12] = 2, result = 3 (previous two [1,2] pairs)
 *   [2,2] => count[22] = 0, result = 3
 *
 * Final result = 3
 * Output: 3
 *
 * Dry Run 2:
 *
 * Step 1: Normalize and encode domino pairs:
 *   [1,2] -> [1,2] => 12
 *   [2,1] -> [1,2] => 12
 *   [3,4] -> [3,4] => 34
 *   [5,6] -> [5,6] => 56
 *
 * Step 2: Count matches while iterating:
 *   First [1,2] => count[12] = 0, result = 0, then count[12]++
 *   Second [1,2] => count[12] = 1, result = 1, then count[12]++
 *   [3,4] => count[34] = 0, result = 1
 *   [5,6] => count[56] = 0, result = 1
 *
 * Final result = 1
 * Output: 1
 */
