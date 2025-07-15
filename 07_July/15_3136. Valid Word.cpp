/*
 * 3136. Valid Word
 *
 * Easy
 *
 * A word is considered valid if:
 * It contains a minimum of 3 characters.
 * It contains only digits (0-9), and English letters (uppercase and lowercase).
 * It includes at least one vowel.
 * It includes at least one consonant.
 * You are given a string word.
 * Return true if word is valid, otherwise, return false.
 *
 * Notes:
 * 'a', 'e', 'i', 'o', 'u', and their uppercases are vowels.
 * A consonant is an English letter that is not a vowel.
 *
 * Example 1:
 * Input: word = "234Adas"
 * Output: true
 * Explanation:
 * This word satisfies the conditions.
 *
 * Example 2:
 * Input: word = "b3"
 * Output: false
 * Explanation:
 * The length of this word is fewer than 3, and does not have a vowel.
 *
 * Example 3:
 * Input: word = "a3$e"
 * Output: false
 * Explanation:
 * This word contains a '$' character and does not have a consonant.
 *
 * Constraints:
 * 1 <= word.length <= 20
 * word consists of English uppercase and lowercase letters, digits, '@', '#', and '$'.
 */

// Approach: Simple traversal of the string, checking each character, tracking if there's at least one vowel and one consonant, and validating allowed characters.
// Time Complexity: O(n) where n is the length of the word, since we traverse the string once.
// Space Complexity: O(1) since we use a constant amount of extra space.
class Solution {
public:
    bool isValid(string word) {
        if (word.length() < 3) {
            return false; // If word has fewer than 3 characters, it's invalid
        }

        bool hasVowel     = false;  // Flag to track presence of a vowel
        bool hasConsonant = false;  // Flag to track presence of a consonant

        for (char ch : word) {
            if (isalpha(ch)) {               // If character is an alphabet letter
                ch = tolower(ch);            // Convert to lowercase for uniform vowel checking
                if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
                    hasVowel = true;         // Mark that we found a vowel
                } else {
                    hasConsonant = true;     // Otherwise, it's a consonant
                }
            } else if (!isdigit(ch)) {
                return false;                // If it's neither a letter nor a digit, invalid character found
            }
        }

        // Return true only if both a vowel and a consonant were found
        return hasVowel && hasConsonant;
    }
};

/*
 *
 * Dry Run
 *
 * Input: word = "234Adas"
 * Step 1: Check length: 7 >= 3, continue.
 * Step 2: Initialize hasVowel = false, hasConsonant = false.
 * Step 3: Iterate characters:
 *   '2': not letter, is digit -> continue.
 *   '3': digit -> continue.
 *   '4': digit -> continue.
 *   'A': letter -> tolower -> 'a' -> vowel -> hasVowel = true.
 *   'd': letter -> 'd' -> consonant -> hasConsonant = true.
 *   'a': letter -> 'a' -> vowel -> hasVowel remains true.
 *   's': letter -> 's' -> consonant -> hasConsonant remains true.
 * Step 4: End of string. hasVowel && hasConsonant = true && true -> true.
 * Output: true
 *
 * Input: word = "b3"
 * Step 1: Check length: 2 < 3 -> return false.
 * Output: false
 *
 * Input: word = "a3$e"
 * Step 1: Check length: 4 >= 3, continue.
 * Step 2: Initialize flags to false.
 * Step 3: Iterate:
 *   'a': letter -> vowel -> hasVowel = true.
 *   '3': digit -> continue.
 *   '$': not letter or digit -> return false.
 * Output: false
 *
 */
