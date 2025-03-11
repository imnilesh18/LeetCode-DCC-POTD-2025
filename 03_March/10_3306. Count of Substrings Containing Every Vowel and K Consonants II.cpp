/*
 * 3306. Count of Substrings Containing Every Vowel and K Consonants II
 * Solve - 1358. Number of Substrings Containing All Three Characters
 *
 * You are given a string word and a non-negative integer k.
 * Return the total number of substrings of word that contain every vowel ('a', 'e', 'i', 'o', and 'u') at least once and exactly k consonants.
 *
 * Example 1:
 * Input: word = "aeioqq", k = 1
 * Output: 0
 * Explanation:
 * There is no substring with every vowel.
 *
 * Example 2:
 * Input: word = "aeiou", k = 0
 * Output: 1
 * Explanation:
 * The only substring with every vowel and zero consonants is word[0..4], which is "aeiou".
 *
 * Example 3:
 * Input: word = "ieaouqqieaouqq", k = 1
 * Output: 3
 * Explanation:
 *
 * The substrings with every vowel and one consonant are:
 * word[0..5], which is "ieaouq".
 * word[6..11], which is "qieaou".
 * word[7..12], which is "ieaouq".
 *
 * Constraints:
 * 5 <= word.length <= 2 * 10^5
 * word consists only of lowercase English letters.
 * 0 <= k <= word.length - 5
 */

// Approach: Use a sliding window with two pointers and a preprocessed next-consonant index array.
//             The window is expanded with pointer j, and contracted with pointer i to maintain exactly k consonants.
//             When the window is valid (all vowels present and consonant count equals k), count the additional valid substrings
//             using the next consonant index.
// Time Complexity: O(n) - each element is processed at most twice in the sliding window.
// Space Complexity: O(n) - due to the nextCons vector (vowel map uses constant space, O(5)).
class Solution {
public:
    // Helper function to check if a character is a vowel.
    bool isVowel(char& ch) {
        return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
    }
    long long countOfSubstrings(string word, int k) {
        int n = word.length();

        unordered_map<char, int> mp;     // to keep the count of vowels in the current window (max 5 vowels)

        // Preprocessing: Build nextCons vector to find the index of the next consonant for each index.
        vector<int> nextCons(n);
        int         lastConsIdx = n; // Initialize to n (beyond the last index)

        for (int i = n - 1; i >= 0; i--) {
            nextCons[i] = lastConsIdx;
            if (!isVowel(word[i])) {
                lastConsIdx = i;
            }
        }

        int       i     = 0;
        int       j     = 0;
        long long count = 0;
        int       cons  = 0; // current number of consonants in the window

        // Iterate over the string using pointer j to expand the window.
        while (j < n) {
            char ch = word[j];
            if (isVowel(ch)) {
                mp[ch]++;
            } else {
                cons++;
            }

            // If the consonant count exceeds k, shrink the window from the left.
            while (i < n && cons > k) {
                char ch = word[i];
                if (isVowel(ch)) {
                    mp[ch]--;
                    if (mp[ch] == 0) {
                        mp.erase(ch);
                    }
                } else {
                    cons--;
                }
                i++;
            }

            // When the window is valid (all vowels are present and consonant count equals k)
            // count all substrings ending at indices from j to nextConsonant - 1.
            while (i < n && mp.size() == 5 && cons == k) { // valid window
                int idx = nextCons[j];                     // index of next consonant after j; substrings [i, j...idx-1] are valid.
                count += idx - j;
                // Slide the window from the left and update counts.
                char ch = word[i];
                if (isVowel(ch)) {
                    mp[ch]--;
                    if (mp[ch] == 0) {
                        mp.erase(ch);
                    }
                } else {
                    cons--;
                }
                i++;
            }
            j++;
        }

        return count;
    }
};

/*
 * Dry Run:
 * -----------
 * Example: word = "ieaouq", k = 1
 *
 * 1. Preprocessing nextCons:
 * - n = 6, lastConsIdx = 6 initially.
 * - i = 5: word[5] = 'q' (consonant)
 *       nextCons[5] = 6, update lastConsIdx = 5.
 * - i = 4: word[4] = 'u' (vowel)
 *       nextCons[4] = 5.
 * - i = 3: word[3] = 'o' (vowel)
 *       nextCons[3] = 5.
 * - i = 2: word[2] = 'a' (vowel)
 *       nextCons[2] = 5.
 * - i = 1: word[1] = 'e' (vowel)
 *       nextCons[1] = 5.
 * - i = 0: word[0] = 'i' (vowel)
 *       nextCons[0] = 5.
 *
 * 2. Sliding window process:
 * - Initialize i = 0, j = 0, cons = 0, mp = {}.
 * - j = 0: word[0] = 'i' → vowel, mp = {'i':1}, cons = 0.
 * - j = 1: word[1] = 'e' → vowel, mp = {'i':1, 'e':1}, cons = 0.
 * - j = 2: word[2] = 'a' → vowel, mp = {'i':1, 'e':1, 'a':1}, cons = 0.
 * - j = 3: word[3] = 'o' → vowel, mp = {'i':1, 'e':1, 'a':1, 'o':1}, cons = 0.
 * - j = 4: word[4] = 'u' → vowel, mp = {'i':1, 'e':1, 'a':1, 'o':1, 'u':1}, cons = 0.
 * - j = 5: word[5] = 'q' → consonant, mp unchanged, cons becomes 1.
 *   Now window [i=0, j=5] is valid because mp.size() == 5 and cons == 1.
 *   - nextCons[5] = 6, so count += (6 - 5) = 1.
 *   - Then, slide window by moving i:
 * i = 0: Remove word[0] = 'i' (vowel), update mp; now mp.size() becomes 4.
 * The inner loop stops as window is no longer valid.
 * 3. Final count = 1.
 * -----------
 */
