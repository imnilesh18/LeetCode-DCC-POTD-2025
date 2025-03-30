/*
 * 763. Partition Labels
 *
 * Medium
 *
 * You are given a string s. We want to partition the string into as many parts as possible so that each letter appears in at most one part. For example, the string "ababcc" can be partitioned into ["abab", "cc"], but partitions such as ["aba", "bcc"] or ["ab", "ab", "cc"] are invalid.
 *
 * Note that the partition is done so that after concatenating all the parts in order, the resultant string should be s.
 *
 * Return a list of integers representing the size of these parts.
 *
 * Example 1:
 * Input: s = "ababcbacadefegdehijhklij"
 * Output: [9,7,8]
 * Explanation:
 * The partition is "ababcbaca", "defegde", "hijhklij".
 * This is a partition so that each letter appears in at most one part.
 * A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits s into less parts.
 *
 * Example 2:
 * Input: s = "eccbbbbdec"
 * Output: [10]
 *
 * Constraints:
 * 1 <= s.length <= 500
 * s consists of lowercase English letters.
 */

// Approach: Use greedy scanning by first recording the last occurrence of each character, then expanding each partition to the farthest index any character within it appears.
// Time Complexity: O(n) - one pass to record last indices and another pass to form partitions.
// Space Complexity: O(1) - uses a fixed-size array (26 elements) regardless of input size.

class Solution {
public:
    vector<int> partitionLabels(string s) {
        int         n = s.size(); // Total number of characters in the string.
        vector<int> result;       // To store the size of each partition.

        // Array to store the last occurrence index for each letter (a to z).
        vector<int> mp(26, -1);

        // Record the last index at which each character appears.
        for (int i = 0; i < n; i++) {
            int idx = s[i] - 'a';
            mp[idx] = i;     // Update the last occurrence for the current character.
        }

        int i = 0;     // Start index for the current partition.
        while (i < n) {
            // Set the initial partition end as the last occurrence of the starting character.
            int end = mp[s[i] - 'a'];
            int j   = i;   // Pointer to traverse the current partition.

            // Expand the partition: continue until the pointer j reaches the current partition's end.
            while (j < end) {
                // Update the partition end to be the farthest last occurrence among the characters seen so far.
                end = max(end, mp[s[j] - 'a']);
                j++;     // Move to the next character within the partition.
            }
            // After the loop, j == end. The partition size is (j - i + 1).
            result.push_back(j - i + 1);
            // Move i to the index right after the current partition.
            i = j + 1;
        }

        return result;
    }
};

/*
 * Dry Run for input: "ababcbacadefegdehijhklij"
 *
 * Full string with indices and characters:
 * ---------------------------------------------------------------------------------------------
 * |  0:'a' |  1:'b' |  2:'a' |  3:'b' |  4:'c' |  5:'b' |  6:'a' |  7:'c' |  8:'a' |  9:'d' | 10:'e' | 11:'f' | 12:'e' | 13:'g' | 14:'e' | 15:'d' | 16:'h' | 17:'i' | 18:'j' | 19:'h' | 20:'k' | 21:'l' | 22:'i' | 23:'j' |
 * ---------------------------------------------------------------------------------------------
 *
 * Last Occurrence Mapping:
 *   a -> 8
 *   b -> 5
 *   c -> 7
 *   d -> 15
 *   e -> 14
 *   f -> 11
 *   g -> 13
 *   h -> 19
 *   i -> 22
 *   j -> 23
 *   k -> 20
 *   l -> 21
 *
 * ----------------------------------------------------
 * Partition 1: Expected indices [0,8] → "ababcbaca"
 *
 * Initial state:
 *   i = 0, j = 0, s[0] = 'a'
 *   Last occurrence of 'a' is 8 → end = 8.
 *
 * Visual Representation:
 *  ---------------------------------------------------------------------------------
 * | 0:'a' | 1:'b' | 2:'a' | 3:'b' | 4:'c' | 5:'b' | 6:'a' | 7:'c' | 8:'a' |
 *  ---------------------------------------------------------------------------------
 *   i,j                                                           end → index 8
 *
 * Iterations:
 * 1. j = 0 (char 'a'):
 *    - mp['a'] = 8 → end remains 8.
 *    - Move j to 1.
 *
 *    Visual:
 *  ---------------------------------------------------------------------------------
 * | 0:'a' | 1:'b' | ...                                               8:'a' |
 *  ---------------------------------------------------------------------------------
 * i → index 0
 *         j → index 1
 *                                                                    end → index 8
 *
 * 2. j = 1 (char 'b'):
 *    - mp['b'] = 5 → end = max(8,5) = 8.
 *    - Move j to 2.
 *
 *    Visual:
 *  ---------------------------------------------------------------------------------
 * | 0:'a' | 1:'b' | 2:'a' | ...                                       8:'a' |
 *  ---------------------------------------------------------------------------------
 *  i → index 0
 *                  j → index 2
 *                                                                     end → index 8
 *
 * 3. j = 2 (char 'a'):
 *    - mp['a'] = 8 → end remains 8.
 *    - Move j to 3.
 *
 *    Visual:
 *  ---------------------------------------------------------------------------------
 * | 0:'a' | 1:'b' | 2:'a' | 3:'b' | ...                                8:'a' |
 *  ---------------------------------------------------------------------------------
 *  i → index 0
 *                          j → index 3
 *                                                                     end → index 8
 *
 * 4. j = 3 (char 'b'):
 *    - mp['b'] = 5 → end remains 8.
 *    - Move j to 4.
 *
 *    Visual:
 *  ---------------------------------------------------------------------------------
 * | 0:'a' | 1:'b' | 2:'a' | 3:'b' | 4:'c' | ...                         8:'a' |
 *  ---------------------------------------------------------------------------------
 * i → index 0
 *                                 j → index 4
 *                                                                       end → index 8
 *
 * 5. j = 4 (char 'c'):
 *    - mp['c'] = 7 → end = max(8,7) = 8.
 *    - Move j to 5.
 *
 *    Visual:
 *  ---------------------------------------------------------------------------------
 * | 0:'a' | 1:'b' | 2:'a' | 3:'b' | 4:'c' | 5:'b' | ...                  8:'a' |
 *  ---------------------------------------------------------------------------------
 *  i → index 0
 *                                          j → index 5
 *                                                                        end → index 8
 *
 * 6. j = 5 (char 'b'):
 *    - mp['b'] = 5 → end remains 8.
 *    - Move j to 6.
 *
 *    Visual:
 *  ---------------------------------------------------------------------------------
 * | 0:'a' | 1:'b' | 2:'a' | 3:'b' | 4:'c' | 5:'b' | 6:'a' | ...             8:'a' |
 *  ---------------------------------------------------------------------------------
 *  i → index 0
 *                                                 j → index 6
 *                                                                          end → index 8
 *
 * 7. j = 6 (char 'a'):
 *    - mp['a'] = 8 → end remains 8.
 *    - Move j to 7.
 *
 *    Visual:
 *  ---------------------------------------------------------------------------------
 * | 0:'a' | 1:'b' | 2:'a' | 3:'b' | 4:'c' | 5:'b' | 6:'a' | 7:'c' | 8:'a' |
 *  ---------------------------------------------------------------------------------
 * i → index 0
 *                                                         j → index 7
 *                                                                 end → index 8
 *
 * 8. j = 7 (char 'c'):
 *    - mp['c'] = 7 → end remains 8.
 *    - Move j to 8.
 *
 *    Visual:
 *  ---------------------------------------------------------------------------------
 * | 0:'a' | 1:'b' | 2:'a' | 3:'b' | 4:'c' | 5:'b' | 6:'a' | 7:'c' | 8:'a' |
 *  ---------------------------------------------------------------------------------
 *  i → index 0
 *                                                                  j → index 8
 *                                                                end → index 8
 *
 * 9. j = 8 (char 'a'):
 *    - j equals end. Partition ends here.
 *    - Partition 1 covers indices [0,8] → "ababcbaca", size = 9.
 *    - Update i = j + 1 = 9.
 *
 * ----------------------------------------------------
 * Partition 2: Expected indices [9,15] → "defegde"
 *
 * Initial state:
 *   i = 9, j = 9, s[9] = 'd'
 *   Last occurrence of 'd' is 15 → end = 15.
 *
 * Visual Representation:
 *  ---------------------------------------------------------------------
 * | 9:'d' | 10:'e' | 11:'f' | 12:'e' | 13:'g' | 14:'e' | 15:'d' |
 *  ---------------------------------------------------------------------
 *  i,j                                                 end → index 15
 *
 * Iterations:
 * 1. j = 9 (char 'd'):
 *    - mp['d'] = 15 → end remains 15.
 *    - Move j to 10.
 *
 *    Visual:
 *  ---------------------------------------------------------------------
 * | 9:'d' | 10:'e' | 11:'f' | ...                               15:'d' |
 *  ---------------------------------------------------------------------
 * i → index 9
 *         j → index 10
 *                                                                 end → index 15
 *
 * 2. j = 10 (char 'e'):
 *    - mp['e'] = 14 → end = max(15,14) = 15.
 *    - Move j to 11.
 *
 *    Visual:
 *  ---------------------------------------------------------------------
 * | 9:'d' | 10:'e' | 11:'f' | 12:'e' | ...                      15:'d' |
 *  ---------------------------------------------------------------------
 *  i → index 9
 *                  j → index 11
 *                                                              end → index 15
 *
 * 3. j = 11 (char 'f'):
 *    - mp['f'] = 11 → end remains 15.
 *    - Move j to 12.
 *
 *    Visual:
 *  ---------------------------------------------------------------------
 * | 9:'d' | 10:'e' | 11:'f' | 12:'e' | ...                     15:'d' |
 *  ---------------------------------------------------------------------
 *  i → index 9
 *                           j → index 12
 *                                                             end → index 15
 *
 * 4. j = 12 (char 'e'):
 *    - mp['e'] = 14 → end remains 15.
 *    - Move j to 13.
 *
 *    Visual:
 *  ---------------------------------------------------------------------
 * | 9:'d' | 10:'e' | 11:'f' | 12:'e' | 13:'g' | 14:'e' | 15:'d' |
 *  ---------------------------------------------------------------------
 *  i → index 9
 *                                    j → index 13
 *                                                      end → index 15
 *
 * 5. j = 13 (char 'g'):
 *    - mp['g'] = 13 → end remains 15.
 *    - Move j to 14.
 *
 *    Visual:
 *  ---------------------------------------------------------------------
 * | 9:'d' | 10:'e' | 11:'f' | 12:'e' | 13:'g' | 14:'e' | 15:'d' |
 *  ---------------------------------------------------------------------
 *  i → index 9
 *                                              j → index 14
 *                                                       end → index 15
 *
 * 6. j = 14 (char 'e'):
 *    - mp['e'] = 14 → end remains 15.
 *    - Move j to 15.
 *
 *    Visual:
 *  ---------------------------------------------------------------------
 * | 9:'d' | 10:'e' | 11:'f' | 12:'e' | 13:'g' | 14:'e' | 15:'d' |
 *  ---------------------------------------------------------------------
 *  i → index 9
 *                                                        j → index 15
 *                                                      end → index 15
 *
 * 7. j = 15 (char 'd'):
 *    - j equals end. Partition ends here.
 *    - Partition 2 covers indices [9,15] → "defegde", size = 7.
 *    - Update i = j + 1 = 16.
 *
 * ----------------------------------------------------
 * Partition 3: Expected indices [16,23] → "hijhklij"
 *
 * Initial state:
 *   i = 16, j = 16, s[16] = 'h'
 *   Last occurrence of 'h' is 19 → end = 19.
 *
 * Visual Representation:
 *  -----------------------------------------------------------------------------------------
 * | 16:'h' | 17:'i' | 18:'j' | 19:'h' | 20:'k' | 21:'l' | 22:'i' | 23:'j' |
 *  -----------------------------------------------------------------------------------------
 *   i,j                       end initially → index 19
 *
 * Iterations:
 * 1. j = 16 (char 'h'):
 *    - Last occurrence: mp['h'] = 19 → end = max(19, 19) = 19.
 *    - Move j to 17.
 *
 *    Visual:
 *  -----------------------------------------------------------------------------------------
 * | 16:'h' | 17:'i' | 18:'j' | 19:'h' | 20:'k' | 21:'l' | 22:'i' | 23:'j' |
 *  -----------------------------------------------------------------------------------------
 *  i → index 16
 *          j → index 17
 *                            end → index 19 (from mp['h'])
 *
 * 2. j = 17 (char 'i'):
 *    - Last occurrence: mp['i'] = 22 → end = max(19, 22) = 22.
 *    - Move j to 18.
 *
 *    Visual:
 *  -----------------------------------------------------------------------------------------
 * | 16:'h' | 17:'i' | 18:'j' | 19:'h' | 20:'k' | 21:'l' | 22:'i' | 23:'j' |
 *  -----------------------------------------------------------------------------------------
 *  i → index 16
 *                   j → index 18
 *                                                        end → index 22 (updated from mp['i'])
 *
 * 3. j = 18 (char 'j'):
 *    - Last occurrence: mp['j'] = 23 → end = max(22, 23) = 23.
 *    - Move j to 19.
 *
 *    Visual:
 *  -----------------------------------------------------------------------------------------
 * | 16:'h' | 17:'i' | 18:'j' | 19:'h' | 20:'k' | 21:'l' | 22:'i' | 23:'j' |
 *  -----------------------------------------------------------------------------------------
 *  i → index 16
 *                             j → index 19
 *                                                                 end → index 23 (updated from mp['j'])
 *
 * 4. j = 19 (char 'h'):
 *    - Last occurrence: mp['h'] = 19 → end = max(23, 19) = 23.
 *    - Move j to 20.
 *
 *    Visual:
 *  -----------------------------------------------------------------------------------------
 * | 16:'h' | 17:'i' | 18:'j' | 19:'h' | 20:'k' | 21:'l' | 22:'i' | 23:'j' |
 *  -----------------------------------------------------------------------------------------
 *   i → index 16
 *                                     j → index 20
 *                                                                end → index 23 (remains unchanged)
 *
 * 5. j = 20 (char 'k'):
 *    - Last occurrence: mp['k'] = 20 → end = max(23, 20) = 23.
 *    - Move j to 21.
 *
 *    Visual:
 *  -----------------------------------------------------------------------------------------
 * | 16:'h' | 17:'i' | 18:'j' | 19:'h' | 20:'k' | 21:'l' | 22:'i' | 23:'j' |
 *  -----------------------------------------------------------------------------------------
 *   i → index 16
 *                                               j → index 21
 *                                                                end → index 23 (remains unchanged)
 *
 * 6. j = 21 (char 'l'):
 *    - Last occurrence: mp['l'] = 21 → end = max(23, 21) = 23.
 *    - Move j to 22.
 *
 *    Visual:
 *  -----------------------------------------------------------------------------------------
 * | 16:'h' | 17:'i' | 18:'j' | 19:'h' | 20:'k' | 21:'l' | 22:'i' | 23:'j' |
 *  -----------------------------------------------------------------------------------------
 *   i → index 16
 *                                                        j → index 22
 *                                                                 end → index 23 (remains unchanged)
 *
 * 7. j = 22 (char 'i'):
 *    - Last occurrence: mp['i'] = 22 → end = max(23, 22) = 23.
 *    - Move j to 23.
 *
 *    Visual:
 *  -----------------------------------------------------------------------------------------
 * | 16:'h' | 17:'i' | 18:'j' | 19:'h' | 20:'k' | 21:'l' | 22:'i' | 23:'j' |
 *  -----------------------------------------------------------------------------------------
 *   i → index 16
 *                                                                  j → index 23
 *                                                                end → index 23 (remains unchanged)
 *
 * 8. j = 23 (char 'j'):
 *    - Last occurrence: mp['j'] = 23, and j equals end.
 *    - Partition ends here.
 *    - Partition 3 covers indices [16,23] → "hijhklij", size = 8.
 *
 * Final Partitions:
 *   Partition 1: "ababcbaca" → size 9
 *   Partition 2: "defegde"   → size 7
 *   Partition 3: "hijhklij"  → size 8
 *
 * Output: [9, 7, 8]
 */
