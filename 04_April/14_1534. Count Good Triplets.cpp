/*
 * 1534. Count Good Triplets
 *
 * Easy
 *
 * Given an array of integers arr, and three integers a, b and c. You need to find the number of good triplets.
 * A triplet (arr[i], arr[j], arr[k]) is good if the following conditions are true:
 * 0 <= i < j < k < arr.length
 |arr[i] - arr[j]| <= a
 |arr[j] - arr[k]| <= b
 |arr[i] - arr[k]| <= c
 * Where |x| denotes the absolute value of x.
 * Return the number of good triplets.
 *
 * Example 1:
 * Input: arr = [3,0,1,1,9,7], a = 7, b = 2, c = 3
 * Output: 4
 * Explanation: There are 4 good triplets: [(3,0,1), (3,0,1), (3,1,1), (0,1,1)].
 *
 * Example 2:
 * Input: arr = [1,1,2,2,3], a = 0, b = 0, c = 1
 * Output: 0
 * Explanation: No triplet satisfies all conditions.
 *
 * Constraints:
 * 3 <= arr.length <= 100
 * 0 <= arr[i] <= 1000
 * 0 <= a, b, c <= 1000
 */

// Approach (Brute Force with slight improvement): Triple nested loops to check every possible triplet and count those that satisfy the given conditions.
// Time Complexity: O(n^3) - due to three nested loops iterating over the array.
// Space Complexity: O(1) - only constant extra space is used.
class Solution {
public:
    int countGoodTriplets(vector<int>& arr, int a, int b, int c) {
        int cnt = 0;                                                                  // Counter for good triplets
        int n   = arr.size();                                                         // Get the size of the array

        for (int i = 0; i <= n - 3; i++) {                                            // Loop for first element (i)
            // Pointer i set at index i
            for (int j = i + 1; j <= n - 2; j++) {                                    // Loop for second element (j)
                // Pointer j set at index j, must be greater than i
                if (abs(arr[i] - arr[j]) <= a) {                                      // Check condition between arr[i] and arr[j]
                    for (int k = j + 1; k <= n - 1; k++) {                            // Loop for third element (k)
                        // Pointer k set at index k, must be greater than j
                        if (abs(arr[j] - arr[k]) <= b && abs(arr[i] - arr[k]) <= c) { // Check conditions for k
                            cnt++;                                                    // If all conditions are met, increment counter
                        }
                    }
                }
            }
        }
        return cnt;     // Return the total count of good triplets
    }
};

/*
 * Dry Run Example with Array: [3, 0, 1, 1, 9, 7] and a = 7, b = 2, c = 3
 *
 * Initial array representation:
 *           Indices:   0   1   2   3   4   5
 *                    +---+---+---+---+---+---+
 *           Array:   | 3 | 0 | 1 | 1 | 9 | 7 |
 *                    +---+---+---+---+---+---+
 *
 * ----------------------------------------------------------
 * Step 1: i = 0, j = 1, k = 2
 *           Indices:   0   1   2   3   4   5
 *                    +---+---+---+---+---+---+
 *           Array:   | 3 | 0 | 1 | 1 | 9 | 7 |
 *                    +---+---+---+---+---+---+
 *                     ^   ^   ^
 *                     i   j   k
 *       Check:
 *           |arr[0]-arr[1]| = |3 - 0| = 3   <= a (7)  --> valid
 *           |arr[1]-arr[2]| = |0 - 1| = 1   <= b (2)  --> valid
 *           |arr[0]-arr[2]| = |3 - 1| = 2   <= c (3)  --> valid
 *       Result: Triplet (3, 0, 1) is good. (Count becomes 1)
 *       Move k to next index.
 *
 * ----------------------------------------------------------
 * Step 2: i = 0, j = 1, k = 3
 *           Indices:   0   1   2   3   4   5
 *                    +---+---+---+---+---+---+
 *           Array:   | 3 | 0 | 1 | 1 | 9 | 7 |
 *                    +---+---+---+---+---+---+
 *                     ^   ^       ^
 *                     i   j       k
 *       Check:
 *           |arr[0]-arr[1]| = |3 - 0| = 3   <= a (7)  --> valid
 *           |arr[1]-arr[3]| = |0 - 1| = 1   <= b (2)  --> valid
 *           |arr[0]-arr[3]| = |3 - 1| = 2   <= c (3)  --> valid
 *       Result: Triplet (3, 0, 1) is good. (Count becomes 2)
 *       Move k to next index.
 *
 * ----------------------------------------------------------
 * Step 3: i = 0, j = 1, k = 4
 *           Indices:   0   1   2   3   4   5
 *                    +---+---+---+---+---+---+
 *           Array:   | 3 | 0 | 1 | 1 | 9 | 7 |
 *                    +---+---+---+---+---+---+
 *                     ^   ^           ^
 *                     i   j           k
 *       Check:
 *           |arr[0]-arr[1]| = |3 - 0| = 3   <= a (7)   --> valid
 *           |arr[1]-arr[4]| = |0 - 9| = 9   > b (2)    --> invalid
 *       Result: Triplet (3, 0, 9) fails the condition. (Count remains 2)
 *       Move k to next index.
 *
 * ----------------------------------------------------------
 * Step 4: i = 0, j = 1, k = 5
 *           Indices:   0   1   2   3   4   5
 *                    +---+---+---+---+---+---+
 *           Array:   | 3 | 0 | 1 | 1 | 9 | 7 |
 *                    +---+---+---+---+---+---+
 *                     ^   ^               ^
 *                     i   j               k
 *       Check:
 *           |arr[0]-arr[1]| = |3 - 0| = 3   <= a (7)  --> valid
 *           |arr[1]-arr[5]| = |0 - 7| = 7   > b (2)   --> invalid
 *       Result: Triplet (3, 0, 7) fails the condition. (Count remains 2)
 *       End inner loop for j = 1.
 *
 * ----------------------------------------------------------
 * Now increment j: i = 0, j = 2
 *
 * Step 5: i = 0, j = 2, k = 3
 *           Indices:   0   1   2   3   4   5
 *                    +---+---+---+---+---+---+
 *           Array:   | 3 | 0 | 1 | 1 | 9 | 7 |
 *                    +---+---+---+---+---+---+
 *                     ^       ^   ^
 *                     i       j   k
 *       Check:
 *           |arr[0]-arr[2]| = |3 - 1| = 2   <= a (7)  --> valid
 *           |arr[2]-arr[3]| = |1 - 1| = 0   <= b (2)  --> valid
 *           |arr[0]-arr[3]| = |3 - 1| = 2   <= c (3)  --> valid
 *       Result: Triplet (3, 1, 1) is good. (Count becomes 3)
 *       Move k to next index.
 *
 * ----------------------------------------------------------
 * Step 6: i = 0, j = 2, k = 4
 *           Indices:   0   1   2   3   4   5
 *                    +---+---+---+---+---+---+
 *           Array:   | 3 | 0 | 1 | 1 | 9 | 7 |
 *                    +---+---+---+---+---+---+
 *                     ^       ^       ^
 *                     i       j       k
 *       Check:
 *           |arr[0]-arr[2]| = |3 - 1| = 2   <= a (7)  --> valid
 *           |arr[2]-arr[4]| = |1 - 9| = 8   > b (2)   --> invalid
 *       Result: Triplet (3, 1, 9) fails the condition. (Count remains 3)
 *       Move k to next index.
 *
 * ----------------------------------------------------------
 * Step 7: i = 0, j = 2, k = 5
 *           Indices:   0   1   2   3   4   5
 *                    +---+---+---+---+---+---+
 *           Array:   | 3 | 0 | 1 | 1 | 9 | 7 |
 *                    +---+---+---+---+---+---+
 *                     ^       ^           ^
 *                     i       j           k
 *       Check:
 *           |arr[0]-arr[2]| = |3 - 1| = 2   <= a (7)  --> valid
 *           |arr[2]-arr[5]| = |1 - 7| = 6   > b (2)   --> invalid
 *       Result: Triplet (3, 1, 7) fails the condition. (Count remains 3)
 *       End inner loop for j = 2.
 *
 * ----------------------------------------------------------
 * Now increment j: i = 0, j = 3
 *
 * Step 8: i = 0, j = 3, k = 4
 *           Indices:   0   1   2   3   4   5
 *                    +---+---+---+---+---+---+
 *           Array:   | 3 | 0 | 1 | 1 | 9 | 7 |
 *                    +---+---+---+---+---+---+
 *                     ^           ^   ^
 *                     i           j   k
 *       Check:
 *           |arr[0]-arr[3]| = |3 - 1| = 2   <= a (7)  --> valid
 *           |arr[3]-arr[4]| = |1 - 9| = 8   > b (2)   --> invalid
 *       Result: Triplet (3, 1, 9) fails the condition. (Count remains 3)
 *       Move k to next index.
 *
 * ----------------------------------------------------------
 * Step 9: i = 0, j = 3, k = 5
 *           Indices:   0   1   2   3   4   5
 *                    +---+---+---+---+---+---+
 *           Array:   | 3 | 0 | 1 | 1 | 9 | 7 |
 *                    +---+---+---+---+---+---+
 *                     ^           ^       ^
 *                     i           j       k
 *       Check:
 *           |arr[0]-arr[3]| = |3 - 1| = 2   <= a (7)  --> valid
 *           |arr[3]-arr[5]| = |1 - 7| = 6   > b (2)   --> invalid
 *       Result: Triplet (3, 1, 7) fails the condition. (Count remains 3)
 *       End inner loop for j = 3.
 *
 * ----------------------------------------------------------
 * Now increment j: i = 0, j = 4
 *
 * Step 10: i = 0, j = 4, k = 5
 *           Indices:   0   1   2   3   4   5
 *                    +---+---+---+---+---+---+
 *           Array:   | 3 | 0 | 1 | 1 | 9 | 7 |
 *                    +---+---+---+---+---+---+
 *                     ^               ^   ^
 *                     i               j   k
 *       Check:
 *           |arr[0]-arr[4]| = |3 - 9| = 6   <= a (7)  --> valid
 *           |arr[4]-arr[5]| = |9 - 7| = 2   <= b (2)  --> valid
 *           |arr[0]-arr[5]| = |3 - 7| = 4   > c (3)   --> invalid
 *       Result: Triplet (3, 9, 7) fails the condition. (Count remains 3)
 *       End inner loop for j = 4.
 *       End loop for i = 0.
 *
 * ----------------------------------------------------------
 * Now increment i: i = 1 (arr[1] = 0)
 *
 * For i = 1, the array remains the same.
 *           Indices:   0   1   2   3   4   5
 *                    +---+---+---+---+---+---+
 *           Array:   | 3 | 0 | 1 | 1 | 9 | 7 |
 *                    +---+---+---+---+---+---+
 *
 * j now runs from i+1 = 2 to 4.
 *
 * Step 11: i = 1, j = 2, k = 3
 *           Representation:
 *                        (i=1, j=2, k=3)
 *           Indices:   0   1   2   3   4   5
 *                    +---+---+---+---+---+---+
 *           Array:   | 3 | 0 | 1 | 1 | 9 | 7 |
 *                    +---+---+---+---+---+---+
 *                          ^   ^   ^
 *                          i   j   k   (Note: i now at index 1 points to 0, j at 2 points to 1, k at 3 points to 1)
 *       Check:
 *           |arr[1]-arr[2]| = |0 - 1| = 1   <= a (7)  --> valid
 *           |arr[2]-arr[3]| = |1 - 1| = 0   <= b (2)  --> valid
 *           |arr[1]-arr[3]| = |0 - 1| = 1   <= c (3)  --> valid
 *       Result: Triplet (0, 1, 1) is good. (Count becomes 4)
 *       Move k to next index.
 *
 * ----------------------------------------------------------
 * Step 12: i = 1, j = 2, k = 4
 *           Indices:   0   1   2   3   4   5
 *                    +---+---+---+---+---+---+
 *           Array:   | 3 | 0 | 1 | 1 | 9 | 7 |
 *                    +---+---+---+---+---+---+
 *                         ^   ^       ^
 *                         i   j       k
 *       Check:
 *           |arr[1]-arr[2]| = |0 - 1| = 1   <= a (7)  --> valid
 *           |arr[2]-arr[4]| = |1 - 9| = 8   > b (2)   --> invalid
 *       Result: Triplet (0, 1, 9) fails. (Count remains 4)
 *       Move k to next index.
 *
 * ----------------------------------------------------------
 * Step 13: i = 1, j = 2, k = 5
 *           Indices:   0   1   2   3   4   5
 *                    +---+---+---+---+---+---+
 *           Array:   | 3 | 0 | 1 | 1 | 9 | 7 |
 *                    +---+---+---+---+---+---+
 *                         ^   ^           ^
 *                         i   j           k
 *       Check:
 *           |arr[1]-arr[2]| = |0 - 1| = 1   <= a (7)  --> valid
 *           |arr[2]-arr[5]| = |1 - 7| = 6   > b (2)   --> invalid
 *       Result: Triplet (0, 1, 7) fails. (Count remains 4)
 *       End inner loop for j = 2.
 *
 * ----------------------------------------------------------
 * Now increment j: i = 1, j = 3
 *
 * Step 14: i = 1, j = 3, k = 4
 *           Indices:   0   1   2   3   4   5
 *                    +---+---+---+---+---+---+
 *           Array:   | 3 | 0 | 1 | 1 | 9 | 7 |
 *                    +---+---+---+---+---+---+
 *                         ^       ^   ^
 *                         i       j   k   (i=1 (0), j=3 (1), k=4 (9))
 *       Check:
 *           |arr[1]-arr[3]| = |0 - 1| = 1   <= a (7)  --> valid
 *           |arr[3]-arr[4]| = |1 - 9| = 8   > b (2)   --> invalid
 *       Result: Triplet (0, 1, 9) fails. (Count remains 4)
 *       Move k to next index.
 *
 * ----------------------------------------------------------
 * Step 15: i = 1, j = 3, k = 5
 *           Indices:   0   1   2   3   4   5
 *                    +---+---+---+---+---+---+
 *           Array:   | 3 | 0 | 1 | 1 | 9 | 7 |
 *                    +---+---+---+---+---+---+
 *                         ^       ^       ^
 *                         i       j       k   (i=1 (0), j=3 (1), k=5 (7))
 *       Check:
 *           |arr[1]-arr[3]| = |0 - 1| = 1   <= a (7)  --> valid
 *           |arr[3]-arr[5]| = |1 - 7| = 6   > b (2)   --> invalid
 *       Result: Triplet (0, 1, 7) fails. (Count remains 4)
 *       End inner loop for j = 3.
 *
 * ----------------------------------------------------------
 * Now increment j: i = 1, j = 4
 *       For i = 1, j = 4, check:
 *           |arr[1]-arr[4]| = |0 - 9| = 9   > a (7)  --> condition fails
 *       Skip inner k loop.
 *       End loop for i = 1.
 *
 * ----------------------------------------------------------
 * Now increment i: i = 2 (arr[2] = 1)
 *
 * For i = 2, j runs from 3 to 4.
 *
 * Step 16: i = 2, j = 3, k = 4
 *           Indices:   0   1   2   3   4   5
 *                    +---+---+---+---+---+---+
 *           Array:   | 3 | 0 | 1 | 1 | 9 | 7 |
 *                    +---+---+---+---+---+---+
 *                             ^   ^   ^
 *                         (i=2) -->   j=3, now show k=4:
 *                              (i=2: 1, j=3: 1, k=4: 9)
 *           Representation:
 *                                    Indices:   0   1   2   3   4   5
 *                                             +---+---+---+---+---+---+
 *                                    Array:   | 3 | 0 | 1 | 1 | 9 | 7 |
 *                                             +---+---+---+---+---+---+
 *                                                       ^   ^       ^
 *                                                       i   j       k
 *       Check:
 *           |arr[2]-arr[3]| = |1 - 1| = 0   <= a (7)  --> valid
 *           |arr[3]-arr[4]| = |1 - 9| = 8   > b (2)   --> invalid
 *       Result: Triplet (1, 1, 9) fails. (Count remains 4)
 *       Move k to next index.
 *
 * ----------------------------------------------------------
 * Step 17: i = 2, j = 3, k = 5
 *           Indices:   0   1   2   3   4   5
 *                    +---+---+---+---+---+---+
 *           Array:   | 3 | 0 | 1 | 1 | 9 | 7 |
 *                    +---+---+---+---+---+---+
 *                              ^   ^       ^
 *                              i   j       k
 *       Check:
 *           |arr[2]-arr[3]| = |1 - 1| = 0   <= a (7)  --> valid
 *           |arr[3]-arr[5]| = |1 - 7| = 6   > b (2)   --> invalid
 *       Result: Triplet (1, 1, 7) fails. (Count remains 4)
 *       End inner loop for j = 3.
 *
 * ----------------------------------------------------------
 * Now increment j: i = 2, j = 4
 *       Check for i = 2, j = 4:
 *           |arr[2]-arr[4]| = |1 - 9| = 8   > a (7)  --> fails
 *       Skip inner k loop.
 *       End loop for i = 2.
 *
 * ----------------------------------------------------------
 * Now increment i: i = 3 (arr[3] = 1)
 *
 * For i = 3, j runs from 4 to 4.
 *
 * Step 18: i = 3, j = 4, k = 5
 *           Indices:   0   1   2   3   4   5
 *                    +---+---+---+---+---+---+
 *           Array:   | 3 | 0 | 1 | 1 | 9 | 7 |
 *                    +---+---+---+---+---+---+
 *                                  ^  ^   ^
 *                                  i  j   k
 *       Check:
 *           |arr[3]-arr[4]| = |1 - 9| = 8   > a (7)  --> fails
 *       Result: Condition for (i, j) fails, so no k is checked.
 *       End loop for i = 3.
 *
 * ----------------------------------------------------------
 * Final Count of Good Triplets = 4
 */
