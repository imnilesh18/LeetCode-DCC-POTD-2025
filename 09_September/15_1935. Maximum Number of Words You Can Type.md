# 🚀 1935. Maximum Number of Words You Can Type

<div align="center">
  <img src="https://img.shields.io/badge/Difficulty-Easy-brightgreen" alt="Difficulty: Easy" />
  <img src="https://img.shields.io/badge/Topics-Hash%20Table-blue" alt="Topic: Hash Table" />
  <img src="https://img.shields.io/badge/Topics-String-orange" alt="Topic: String" />
</div>

🔗 **Problem Link:** [https://leetcode.com/problems/maximum-number-of-words-you-can-type/](https://leetcode.com/problems/maximum-number-of-words-you-can-type/)

---

## 📝 Problem Statement

There is a malfunctioning keyboard where some letter keys do not work. All other keys on the keyboard work properly.

Given a string `text` of words separated by a single space (no leading or trailing spaces) and a string `brokenLetters` of all **distinct** letter keys that are broken, return *the number of words* in `text` you can fully type using this keyboard.

---

## Constraints

-   `1 <= text.length <= 10^4`
-   `0 <= brokenLetters.length <= 26`
-   `text` consists of words separated by a single space without any leading or trailing spaces.
-   Each word only consists of lowercase English letters.
-   `brokenLetters` consists of **distinct** lowercase English letters.

---

## Examples

Below are the examples provided to illustrate the problem:

| Input | Output | Explanation |
| :--- | :--- | :--- |
| `text = "hello world"`, `brokenLetters = "ad"` | `1` | We cannot type "world" because the 'd' key is broken. |
| `text = "leet code"`, `brokenLetters = "lt"` | `1` | We cannot type "leet" because the 'l' and 't' keys are broken. |
| `text = "leet code"`, `brokenLetters = "e"` | `0` | We cannot type either word because the 'e' key is broken. |

---

## 🤔 Approach: Using a Boolean Map (Hash Set)

The problem asks us to count how many words from the `text` can be typed, given a set of `brokenLetters`. A word is "untypable" if even one of its characters is present in the `brokenLetters` string.

The most straightforward approach is to:
1.  **Efficiently Store Broken Letters:** Iterating through the `brokenLetters` string for every single character of every word in `text` would be inefficient (O(M * N) where M is text length and N is brokenLetters length). Since we are only dealing with 26 lowercase English letters, we can use a simple boolean array (acting as a hash set) of size 26. Let's call it `brokenMap`.
2.  **Populate the Map:** We iterate through the `brokenLetters` string once. For each character `ch`, we mark its corresponding position in our array as `true`. The index can be found using `ch - 'a'`. This operation takes O(k) time, where `k` is the length of `brokenLetters`.
3.  **Iterate and Check Words:** We will iterate through the `text` string character by character. We need two main variables:
    * `result`: An integer to count the number of typable words, initialized to 0.
    * `canTypeThisWord`: A boolean flag, which we will reset to `true` at the start of every new word.
4.  **Word-by-Word Logic:**
    * As we scan the `text` string:
        * If we encounter a letter, we check our `brokenMap`. If `brokenMap[letter - 'a']` is `true`, it means this letter is broken. We immediately set the `canTypeThisWord` flag to `false`. Once this flag is false for a given word, it stays false; there's no need to check other letters in that same word.
        * If we encounter a **space (`' '`)**, it signifies the end of a word. At this point, we check our `canTypeThisWord` flag. If it is still `true` (meaning no broken letters were found in the word we just finished), we increment our `result` counter. After the check, we **must reset `canTypeThisWord = true`** to prepare for the next word.
5.  **Handling the Last Word:** The loop will finish after processing the last character of the last word. However, since there is no trailing space, our "space" logic never runs for this final word. Therefore, after the loop concludes, we must perform one final check: if `canTypeThisWord` is still `true`, we increment `result` one last time.

This approach ensures we check each character of `text` and `brokenLetters` only once.

-   **Time Complexity:** O(N + M), where N is the length of `brokenLetters` (to build the map) and M is the length of `text` (to scan all words).
-   **Space Complexity:** O(26), which simplifies to **O(1)**, as the boolean array's size is constant and does not depend on the input size.

---

## 💻 Optimized Solution Code (C++)

Here is the C++ solution implementing the described approach.

```cpp
// Intuition:
// We need to count words that don't contain any broken letters. To do this efficiently,
// we can first store all broken letters in a boolean array (or hash set) for O(1) lookup.
// Then, we iterate through the text word by word, using a flag to track if the current word
// contains any broken letters.

// Approach:
// 1. Create a boolean array `mp` (acting as a map) of size 26, initialized to false.
// 2. Iterate through the `brokenLetters` string. For each char 'ch', set mp[ch - 'a'] = true.
// 3. Initialize `result = 0` and a boolean flag `canType = true`.
// 4. Iterate through each character 'ch' of the `text` string.
// 5. If `ch == ' '`:
//    - This is the end of a word. Check if `canType` is still true.
//    - If yes, increment `result` (this word was typable).
//    - Reset `canType = true` for the next word.
// 6. Else (if 'ch' is a letter):
//    - Check if this letter is broken by looking up `mp[ch - 'a']`.
//    - If it's true (broken), set `canType = false`. This word is now marked as untypable.
// 7. After the loop finishes, the last word hasn't been counted (no trailing space).
// 8. We perform one final check: if `canType` is still true, increment `result` for the last word.
// 9. Return the final `result`.

// Time Complexity: O(n + m)
// - O(n) to iterate `brokenLetters` (where n = brokenLetters.length()) and build the map.
// - O(m) to iterate the entire `text` string once (where m = text.length()).

// Space Complexity: O(26) => O(1)
// - We only use a fixed-size boolean array of 26 elements, regardless of input size.

class Solution {
public:
    int canBeTypedWords(string text, string brokenLetters) {
        int n = text.length();

        bool mp[26] = {false}; // Initialize a boolean map of size 26 (all false)
        
        // Populate the map with broken letters for O(1) lookup
        for(char &ch : brokenLetters) {
            mp[ch-'a'] = true; // Mark the index corresponding to the char as true
        }

        int result    = 0;    // Counter for typable words
        bool canType  = true; // Flag: true if the current word is typable so far
        
        // Iterate through every character in the text
        for(char &ch : text) {
            if(ch == ' ') {
                // Space marks the end of a word
                if(canType) {
                    result++; // If the word was typable, increment count
                }
                canType = true; // Reset the flag for the *next* word
            } else if (mp[ch - 'a']) {
                // This is a letter. Check if it's in our broken map.
                // If mp[ch-'a'] is true, the letter is broken.
                canType = false; // Mark this entire word as untypable
            }
        }
        
        // After the loop, we must account for the very last word (since there's no trailing space)
        if(canType)
            result++; // If the last word was typable, count it.

        return result;
    }
};

/*
*
* Dry Run
*
* Example 1: text = "hello world", brokenLetters = "ad"
*
* 1. mp[26] is created. 
* - Loop brokenLetters:
* - ch = 'a': mp[0] = true
* - ch = 'd': mp[3] = true
* - Map: [true, false, false, true, false, ...]
*
* 2. result = 0, canType = true
*
* 3. Loop text:
* - ch = 'h': mp['h'-'a'] (mp[7]) is false. canType remains true.
* - ch = 'e': mp[4] is false. canType remains true.
* - ch = 'l': mp[11] is false. canType remains true.
* - ch = 'l': mp[11] is false. canType remains true.
* - ch = 'o': mp[14] is false. canType remains true.
* - ch = ' ': Is a space. 
* - if(canType) -> if(true) -> result becomes 1.
* - Reset canType = true.
* - ch = 'w': mp[22] is false. canType remains true.
* - ch = 'o': mp[14] is false. canType remains true.
* - ch = 'r': mp[17] is false. canType remains true.
* - ch = 'l': mp[11] is false. canType remains true.
* - ch = 'd': mp['d'-'a'] (mp[3]) is TRUE. 
* - Set canType = false.
*
* 4. End of loop.
*
* 5. Final check: if(canType) -> if(false). Result is NOT incremented.
*
* 6. Return result (which is 1). This is correct.
*
*/
```

---

## 🔑 Key Insights

-   The core constraint is that all characters are lowercase English letters, allowing the use of a simple, fixed-size boolean array (size 26) instead of a more complex hash map. This simplifies the space complexity to O(1).
-   The "state" (whether a word is typable or not) only needs to be tracked per-word and should be reset every time a space is encountered.
-   The edge case of the "last word" is crucial. Since the input string does not have a trailing space, the check-and-increment logic that runs inside the loop (when a space is found) will not run for the final word. A separate check is required immediately after the loop terminates.

---

## 🧭 Further Exploration

-   **What if letters could be uppercase or lowercase?** We would either need a boolean array of a larger size (e.g., 128 for ASCII) or convert every character to lowercase (e.g., using `tolower()`) before checking our size-26 map.
-   **What if `brokenLetters` was not guaranteed to be distinct?** It wouldn't matter. Our approach of marking `mp[ch-'a'] = true` is idempotent; marking it `true` multiple times has the same effect as marking it once.
-   **Alternative Solution (Splitting String):** One could also split the `text` string by spaces into a vector of words. Then, iterate through this vector. For each `word`, have a nested loop to check if any of its characters exist in the `brokenLetters` set. This might be slightly cleaner to read but could use more space (to store the vector of words) and might be slightly slower due to the overhead of string splitting, depending on the language.

---

## 🏷️ Tags

`Hash Table` `String` `Easy`

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/maximum-number-of-words-you-can-type/) for original content and copyright.**

---

## 👨‍💻 Author

-   [imnilesh18](https://github.com/imnilesh18)