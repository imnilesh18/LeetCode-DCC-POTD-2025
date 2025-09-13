# 3541. Find Most Frequent Vowel and Consonant

##  Difficulty: Easy

[![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen.svg)](https://leetcode.com/problems/find-most-frequent-vowel-and-consonant/description/) [![Category](https://img.shields.io/badge/Category-String-blue.svg)](https://leetcode.com/problems/find-most-frequent-vowel-and-consonant/description/) [![Category](https://img.shields.io/badge/Category-Hash%20Table-blue.svg)](https://leetcode.com/problems/find-most-frequent-vowel-and-consonant/description/) [![Category](https://img.shields.io/badge/Category-Counting-blue.svg)](https://leetcode.com/problems/find-most-frequent-vowel-and-consonant/description/)

---

### 📝 Problem Statement

You are given a string `s` consisting of lowercase English letters ('a' to 'z').

Your task is to:
1. Find the vowel (one of 'a', 'e', 'i', 'o', or 'u') with the **maximum** frequency.
2. Find the consonant (all other letters excluding vowels) with the **maximum** frequency.

Return the sum of the two frequencies.

**Note:** If multiple vowels or consonants have the same maximum frequency, you may choose any one of them. If there are no vowels or no consonants in the string, consider their frequency as 0.

The **frequency** of a letter `x` is the number of times it occurs in the string.

---

### 📊 Examples

Here are the provided examples formatted for clarity:

| Input | Output | Explanation |
| :--- | :--- | :--- |
| `s = "successes"` | 6 | **Vowels:** 'u' (freq 1), 'e' (freq 2). Max Freq = 2.<br>**Consonants:** 's' (freq 4), 'c' (freq 2). Max Freq = 4.<br>Result: 2 + 4 = 6. |
| `s = "aeiaeia"` | 3 | **Vowels:** 'a' (freq 3), 'e' (freq 2), 'i' (freq 2). Max Freq = 3.<br>**Consonants:** None. Max Freq = 0.<br>Result: 3 + 0 = 3. |

---

### 📋 Constraints

- `1 <= s.length <= 100`
- `s` consists of lowercase English letters only.

---

### 🧠 Approach (Explanation)

The problem requires us to find the single most frequent vowel and the single most frequent consonant and sum their counts.

The most efficient way to handle this is to first count the frequency of *all* characters in the input string `s`. Since the string only contains lowercase English letters, we can use a hash map (like `std::unordered_map` in C++) or even a simple 26-element array to store these counts. We populate this frequency map by iterating through the string `s` one time.

Once the map is built, we initialize two variables: `max_vowel_count = 0` and `max_consonant_count = 0`.

We then iterate through all 26 letters of the alphabet (from 'a' to 'z'). For each letter:
1.  We check if it is a vowel (using a helper function or a check against 'a', 'e', 'i', 'o', 'u').
2.  If it's a vowel, we update `max_vowel_count = max(max_vowel_count, frequency_map[letter])`.
3.  If it's a consonant, we update `max_consonant_count = max(max_consonant_count, frequency_map[letter])`.

Crucially, if a letter from 'a'-'z' was not in the original string, its count in the hash map (or array) will be 0, which correctly won't affect the maximums.

Finally, we return the sum `max_vowel_count + max_consonant_count`.

---

### 💻 Solution Code

#### 1. Brute-force Solution (Multi-Pass Counting)

A "brute-force" method would involve iterating through the entire input string `s` (length N) for *each* of the 26 letters of the alphabet, calculating the count for each one individually using `std::count` or a nested loop. This results in an O(26 * N) time complexity, which simplifies to O(N), but is much less efficient in practice than the single-pass O(N) optimized solution.

```cpp
// Intuition: Instead of one pass, make 26 passes over the string.
// Approach:
// 1. Create a loop for the 5 vowels. For each vowel, use std::count(s.begin(), s.end(), vowel_char) to count its frequency. Find the max.
// 2. Create a loop for the 21 consonants. For each consonant, use std::count() to find its frequency. Find the max.
// 3. Return the sum of the two maximums.
// Time Complexity: O(26 * N) which simplifies to O(N).
// Space Complexity: O(1)
// (Note: This approach is inefficient. The optimized solution below achieves the same result in O(N + 26) time, which is superior.)

/*
*
* Dry Run
* (See Optimized Solution Dry Run. This approach simply performs that counting logic 26 separate times over the full string.)
*
*/
```

#### 2. Optimized Solution (Single-Pass Hash Map)

This approach counts all character frequencies in a single pass (O(N)) and then checks those stored frequencies in a constant-time loop (O(26)).

```cpp
// Intuition: We need to find the max frequency of a vowel and the max frequency of a consonant. The simplest way is to count every character first in a single pass.
// Approach:
// 1. Create an unordered_map (hash map) to store the frequency of each character in the string 's'.
// 2. Iterate through the string 's' and populate the map (O(N) time).
// 3. Initialize max_vowel_freq and max_consonant_freq to 0.
// 4. Iterate through all 26 lowercase English letters (from 'a' to 'z'). This is a constant O(26) loop.
// 5. For each letter, check if it's a vowel using the helper function.
// 6. If it is a vowel, update max_vowel_freq = max(max_vowel_freq, map[letter]).
// 7. If it is a consonant, update max_consonant_freq = max(max_consonant_freq, map[letter]).
// 8. Return the sum of max_vowel_freq and max_consonant_freq.
// Time Complexity: O(N + 26) which simplifies to O(N), where N is the length of 's'. O(N) to build the map, and O(26) (constant) to check the frequencies.
// Space Complexity: O(K) where K is unique characters in 's'. Since K <= 26, this is O(26) or O(1) (constant space).

class Solution {
public:
    // Helper function to check if a character is a vowel.
    bool is_vowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }

    int maxFreqSum(string s) {
        unordered_map<char, int> mp; // Frequency map for characters
        for (auto ch : s) { // Iterate through the input string (O(N))
            mp[ch]++; // Increment the count for the character
        }
        
        int vowel = 0, consonant = 0; // Initialize max frequencies
        
        // Iterate through all 26 lowercase alphabet letters (Constant time loop)
        for (char ch = 'a'; ch <= 'z'; ch++) { 
            if (is_vowel(ch)) { // Check if the current letter is a vowel
                vowel = max(vowel, mp[ch]); // Update max vowel (mp[ch] defaults to 0 if 'ch' not in map)
            } else { // Otherwise, it's a consonant
                consonant = max(consonant, mp[ch]); // Update max consonant frequency
            }
        }
        return vowel + consonant; // Return the sum of the two maximums
    }
};

/*
*
* Dry Run
* Example: s = "successes"
* 1. Build Frequency Map (mp):
* mp['s'] = 4
* mp['u'] = 1
* mp['c'] = 2
* mp['e'] = 2
*
* 2. Initialize: vowel = 0, consonant = 0.
*
* 3. Loop 'a' to 'z':
* - ch = 'a' (vowel): mp['a'] = 0. vowel = max(0, 0) = 0.
* - ch = 'b' (consonant): mp['b'] = 0. consonant = max(0, 0) = 0.
* - ch = 'c' (consonant): mp['c'] = 2. consonant = max(0, 2) = 2.
* - ch = 'd' (consonant): mp['d'] = 0. consonant remains 2.
* - ch = 'e' (vowel): mp['e'] = 2. vowel = max(0, 2) = 2.
* - ... (skip letters not in map) ...
* - ch = 's' (consonant): mp['s'] = 4. consonant = max(2, 4) = 4.
* - ...
* - ch = 'u' (vowel): mp['u'] = 1. vowel = max(2, 1) = 2.
* - ... (Loop finishes)
*
* 4. Final values: vowel = 2, consonant = 4.
* 5. Return: 2 + 4 = 6.
*
*/
```

---

### 💡 Key Insights & Notes

* **Fixed-Size Array vs. Map:** Since we are guaranteed that inputs are only lowercase English letters, we could have used a fixed-size array (`int freq[26]`) instead of an `unordered_map`. We would map characters using `freq[ch - 'a']++`. This removes the overhead of hashing and is technically O(1) space, whereas the map is O(K) space (where K is unique chars, K <= 26). Both are perfectly acceptable given the constraints.
* **Default Map Value:** The C++ `unordered_map` (when accessed using `[]`) automatically inserts a key with a default value (0 for `int`) if the key doesn't exist. This behavior is extremely useful here, as our O(26) loop from 'a' to 'z' doesn't need to check `if (mp.count(ch))` before accessing `mp[ch]`.

---

### 🚀 Further Exploration

* **Handling Case Insensitivity:** How would the solution change if the input string contained both uppercase and lowercase letters, but the definition of vowels and consonants remained case-insensitive (e.g., 'A' counts toward the total for 'a')? (You would likely convert every character to lowercase during the counting phase).
* **Generalizing the Character Set:** What if the string contained numbers, symbols, or extended ASCII/Unicode characters? How would you define "vowel" and "consonant" then, and how would you adapt the counting mechanism?

---

### 📚 References

* [C++ std::unordered_map Documentation](https://en.cppreference.com/w/cpp/container/unordered_map)
* [LeetCode Article: Hash Map Overview](https://leetcode.com/explore/learn/card/hash-table/)

---

### 🏷️ Tags

`String` | `Hash Table` | `Counting` | `Easy`

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/find-most-frequent-vowel-and-consonant/description/) for original content and copyright.**

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)