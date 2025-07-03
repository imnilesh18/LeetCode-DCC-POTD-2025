/*
 * 3304. Find the K-th Character in String Game I
 *
 * Easy
 *
 * Alice and Bob are playing a game. Initially, Alice has a string word = "a".
 * You are given a positive integer k.
 * Now Bob will ask Alice to perform the following operation forever:
 * Generate a new string by changing each character in word to its next character in the English alphabet, and append it to the original word.
 * For example, performing the operation on "c" generates "cd" and performing the operation on "zb" generates "zbac".
 * Return the value of the kth character in word, after enough operations have been done for word to have at least k characters.
 * Note that the character 'z' can be changed to 'a' in the operation.
 *
 * Example 1:
 * Input: k = 5
 * Output: "b"
 * Explanation:
 * Initially, word = "a". We need to do the operation three times:
 * Generated string is "b", word becomes "ab".
 * Generated string is "bc", word becomes "abbc".
 * Generated string is "bccd", word becomes "abbcbccd".
 *
 * Example 2:
 * Input: k = 10
 * Output: "c"
 *
 * Constraints:
 * 1 <= k <= 500
 */

// Intuition: Every position k in the growing string comes from a series of "copies" and "shifts".
// Each operation doubles the string by adding a shifted copy. The position k traces back through
// these splits: the number of 1-bits in (k-1) is how many times the character has been shifted forward
// in the alphabet. This lets us compute the answer without actually building the giant string!

// Approach: Find the number of set bits in (k-1) to determine how many times the character is incremented.
// Intuition: Each position in the final string comes from a particular sequence of transformations; the number of bit shifts needed to reach position (k-1) tells us how many times we "wrap" through the alphabet.
// Time Complexity: O(1), since popcount is a hardware operation and all operations are constant time for k <= 500.
// Space Complexity: O(1), no extra space is used.
class Solution {
public:
    char kthCharacter(int k) {
        // Count number of set bits in (k-1) to determine character shifts
        int shift = __builtin_popcount(k - 1);

        // Return the shifted character from 'a'
        return 'a' + shift;
    }
};

/*
 *
 * Dry Run
 *
 * Input: k = 10
 *
 * Step 1: Calculate (k-1) = 9 -> binary: 1001
 * Step 2: Count set bits in 1001 → 2 set bits
 * Step 3: The answer is 'a' + 2 = 'c'
 * Output: 'c'
 *
 * Input: k = 5
 * (k-1) = 4 -> binary: 100
 * 1 set bit
 * 'a' + 1 = 'b'
 * Output: 'b'
 *
 */
