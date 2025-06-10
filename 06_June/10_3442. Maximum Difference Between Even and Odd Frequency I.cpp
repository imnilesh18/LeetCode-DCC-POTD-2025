/*
 * 3442. Maximum Difference Between Even and Odd Frequency I
 *
 * Easy
 *
 * You are given a string s consisting of lowercase English letters.
 * Your task is to find the maximum difference diff = freq(a1) - freq(a2) between the frequency of characters a1 and a2 in the string such that:
 * a1 has an odd frequency in the string.
 * a2 has an even frequency in the string.
 * Return this maximum difference.
 *
 * Example 1:
 * Input: s = "aaaaabbc"
 * Output: 3
 * Explanation:
 * The character 'a' has an odd frequency of 5, and 'b' has an even frequency of 2.
 * The maximum difference is 5 - 2 = 3.
 *
 * Example 2:
 * Input: s = "abcabcab"
 * Output: 1
 * Explanation:
 * The character 'a' has an odd frequency of 3, and 'c' has an even frequency of 2.
 * The maximum difference is 3 - 2 = 1.
 *
 * Constraints:
 * 3 <= s.length <= 100
 * s consists only of lowercase English letters.
 * s contains at least one character with an odd frequency and one with an even frequency.
 */

// Approach: Count frequency of each character, then find max frequency among odd counts and min among even counts. Return their difference.
// Time Complexity: O(n + 26) = O(n), where n is the length of the string.
// Space Complexity: O(1), since we use a fixed-size array of 26 elements.
class Solution {
public:
    int maxDifference(string s) {
        int n = s.length();

        vector<int> freq(26, 0); // Frequency array to store count of each character

        for (char& ch : s) {
            freq[ch - 'a']++; // Count frequency of each character
        }

        int maxOdd  = 0;       // To track maximum odd frequency
        int minEven = n + 1;   // To track minimum even frequency (initialized to max possible + 1)

        for (int i = 0; i < 26; i++) {
            if (freq[i] == 0) {
                continue; // Skip characters not present in the string
            }

            if (freq[i] % 2 == 0) {
                minEven = min(minEven, freq[i]); // Update minEven if frequency is even
            } else {
                maxOdd = max(maxOdd, freq[i]);   // Update maxOdd if frequency is odd
            }
        }

        return maxOdd - minEven; // Return the maximum difference between odd and even frequencies
    }
};

/*
 *
 * Dry Run
 *
 * Input: "aaaaabbc"
 * Frequencies:
 * a → 5 (odd)
 * b → 2 (even)
 * c → 1 (odd)
 *
 * Loop through freq[0..25]:
 * freq[a] = 5 → odd → maxOdd = max(0, 5) = 5
 * freq[b] = 2 → even → minEven = min(8, 2) = 2
 * freq[c] = 1 → odd → maxOdd = max(5, 1) = 5
 *
 * Final values:
 * maxOdd = 5
 * minEven = 2
 *
 * Result = 5 - 2 = 3
 *
 */
