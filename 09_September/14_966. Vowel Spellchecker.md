<div align="center">

# 966. Vowel Spellchecker

✨ **Medium** ✨

</div>

---

### Problem Link 🔗

[https://leetcode.com/problems/vowel-spellchecker/description/](https://leetcode.com/problems/vowel-spellchecker/description/)

---

### Problem Statement 📝

Given a `wordlist`, we want to implement a spellchecker that converts a query word into a correct word. For a given `query` word, the spell checker handles two categories of spelling mistakes:

1.  **Capitalization**: If the query matches a word in the wordlist (case-insensitive), then the query word is returned with the same case as the case in the wordlist.
    * **Example**: `wordlist = ["yellow"]`, `query = "YellOw"`: `correct = "yellow"`
    * **Example**: `wordlist = ["Yellow"]`, `query = "yellow"`: `correct = "Yellow"`
    * **Example**: `wordlist = ["yellow"]`, `query = "yellow"`: `correct = "yellow"`

2.  **Vowel Errors**: If after replacing the vowels (`'a'`, `'e'`, `'i'`, `'o'`, `'u'`) of the query word with any vowel individually, it matches a word in the wordlist (case-insensitive), then the query word is returned with the same case as the match in the wordlist.
    * **Example**: `wordlist = ["YellOw"]`, `query = "yollow"`: `correct = "YellOw"`
    * **Example**: `wordlist = ["YellOw"]`, `query = "yeellow"`: `correct = ""` (no match)
    * **Example**: `wordlist = ["YellOw"]`, `query = "yllw"`: `correct = ""` (no match)

In addition, the spell checker operates under the following **precedence rules**:

1.  When the query **exactly** matches a word in the wordlist (case-sensitive), you should return the same word back.
2.  When the query matches a word up to **capitalization**, you should return the **first** such match in the wordlist.
3.  When the query matches a word up to **vowel errors**, you should return the **first** such match in the wordlist.
4.  If the query has no matches in the wordlist, you should return the empty string.

Given some `queries`, return a list of words `answer`, where `answer[i]` is the correct word for `query = queries[i]`.

---

### Constraints 📏

* `1 <= wordlist.length, queries.length <= 5000`
* `1 <= wordlist[i].length, queries[i].length <= 7`
* `wordlist[i]` and `queries[i]` consist only of English letters.

---

### Examples 📊

| Input | Output |
| :--- | :--- |
| `wordlist = ["KiTe","kite","hare","Hare"]`<br>`queries = ["kite","Kite","KiTe","Hare","HARE","Hear","hear","keti","keet","keto"]` | `["kite","KiTe","KiTe","Hare","hare","","","KiTe","","KiTe"]` |
| `wordlist = ["yellow"]`<br>`queries = ["YellOw"]` | `["yellow"]` |

<br>

<details>
  <summary><b>Example 1 Walkthrough</b></summary>
  
* `query = "kite"`: Exact match found: `"kite"`. (Rule 1)
* `query = "Kite"`: No exact match. Case-insensitive match found. First in wordlist is `"KiTe"`. (Rule 2)
* `query = "KiTe"`: Exact match found: `"KiTe"`. (Rule 1)
* `query = "Hare"`: Exact match found: `"Hare"`. (Rule 1)
* `query = "HARE"`: No exact match. Case-insensitive match found. First in wordlist is `"hare"`. (Rule 2)
* `query = "Hear"`: No exact match. No case-insensitive match. No vowel-error match (consonant 'H' vs 'h' is fine, but 'r' vs 'r' is also fine, but "Hear" is not in the vowel-masked map). Result: `""`.
* `query = "hear"`: Same as above. Result: `""`.
* `query = "keti"`: No exact/case match. Check vowel error. `k*t*` (from `keti`) matches `k*t*` (from `"KiTe"`). First match is `"KiTe"`. (Rule 3)
* `query = "keet"`: No match. Consonant 't' vs 'e' error. Result: `""`.
* `query = "keto"`: No exact/case match. Check vowel error. `k*t*` (from `keto`) matches `k*t*` (from `"KiTe"`). First match is `"KiTe"`. (Rule 3)
</details>

---

### Approach 💡

The problem requires us to check queries against a wordlist based on three distinct rules with strict precedence. Iterating the entire `wordlist` for every query would be too slow (O(Q \* W) where Q is num queries, W is num words), given the constraints.

The key is to **pre-process** the `wordlist` into data structures (Hash Maps and a Set) that allow for O(1) average-time lookups. We need to store matches for all three rules. Since rules 2 and 3 require returning the *first* match from the original list, our processing logic must honor this.

We will use three data structures:

1.  **`exactWords` (Set)**: An `unordered_set<string>` to store all original words from the `wordlist`. This allows for a perfect O(1) average lookup for Rule 1 (Exact Match).
2.  **`caseMap` (Map)**: An `unordered_map<string, string>` to handle Rule 2 (Capitalization).
    * **Key**: The word converted to *lowercase*.
    * **Value**: The *original word* (with its original casing).
    * When populating this map, we only add a key-value pair if the lowercase key *does not already exist*. This correctly ensures that only the *first* word in the `wordlist` that maps to a given lowercase version is stored.
3.  **`vowelMap` (Map)**: An `unordered_map<string, string>` to handle Rule 3 (Vowel Errors).
    * **Key**: The word converted to lowercase, with all vowels (`a, e, i, o, u`) replaced by a placeholder character (like `*`). For example, "yellow" becomes "y\*ll\*w".
    * **Value**: The *original word*.
    * Similar to `caseMap`, we only add this key-value pair if the vowel-masked key *does not already exist*, satisfying the "first match" requirement.

**Querying Process:**
For each query, we check our data structures *in the order of precedence*:

1.  Check if the query exists in `exactWords`. If yes, return it.
2.  If not, convert the query to lowercase. Check if this lowercase version exists as a key in `caseMap`. If yes, return the corresponding value (the original-cased first match).
3.  If not, convert the lowercase query into its vowel-masked version. Check if this masked version exists as a key in `vowelMap`. If yes, return the corresponding value.
4.  If none of these checks pass, return an empty string `""`.

---

### Solution Code 👨‍💻

#### 🚀 Optimized Solution (C++)

```cpp
// Intuition:
// We need to check each query against three matching rules in strict order of precedence.
// To do this efficiently without re-scanning the wordlist for every query (which would be O(N*M)),
// we can pre-process the wordlist into data structures (hash maps and a set) that allow for
// O(1) average-case lookups for each rule. We need one data structure for each rule.

// Approach:
// 1. Create three data structures:
//    - `exactWords` (unordered_set): To store all original words for Rule 1 (Exact Match).
//    - `caseMap` (unordered_map): To store mappings from lowercase words to the *first* original word (Rule 2).
//    - `vowelMap` (unordered_map): To store mappings from vowel-masked lowercase words to the *first* original word (Rule 3).
// 2. Iterate through the `wordlist` ONCE to populate these data structures.
// 3. For each `word`:
//    - Add the original `word` to `exactWords`.
//    - Convert the `word` to lowercase (`lowerWord`).
//    - If `lowerWord` is NOT in `caseMap`, add it: `caseMap[lowerWord] = word`. This ensures only the FIRST occurrence is stored.
//    - Create a vowel-masked version of `lowerWord` (`maskedWord`) by replacing all vowels with '*'.
//    - If `maskedWord` is NOT in `vowelMap`, add it: `vowelMap[maskedWord] = word`. This also stores only the FIRST occurrence.
// 4. Create a `result` vector to store answers.
// 5. Iterate through each `query` in the `queries` list.
// 6. For each `query`, call a helper function `checkForMatch` that applies the precedence rules.
// 7. The `checkForMatch` helper function:
//    - (Rule 1): Check if the original `query` is in `exactWords`. If yes, return it.
//    - (Rule 2): Convert the `query` to lowercase (`lowerQuery`). Check if `lowerQuery` is in `caseMap`. If yes, return the mapped value.
//    - (Rule 3): Create a vowel-masked version of `lowerQuery` (`maskedQuery`). Check if `maskedQuery` is in `vowelMap`. If yes, return the mapped value.
//    - (Rule 4): If no match is found after all checks, return an empty string "".
// 8. Add the string returned by the helper to the `result` vector.
// 9. Return the final `result` vector.

// Time Complexity: O(C + Q), where C is the total number of characters in the wordlist and Q is the total number of characters in the queries.
// Pre-processing the wordlist takes O(C) time, as we iterate each word and its characters to lowercase/mask them (word length is small and constant-bounded, <= 7).
// Processing each query takes O(L) time (where L is the query length, also <= 7) to lowercase/mask it and perform O(1) average-case map/set lookups.
// Total time is dominated by iterating all characters once for processing and once for querying.

// Space Complexity: O(C), where C is the total number of characters in the wordlist.
// In the worst case, we store every word (or a transformation of it) in our three data structures.

//Approach - Using map and set (Provided in prompt, enhanced with comments)
//T.C : O(N), N = total length of all the input strings (wordlist + queries). This matches our O(C+Q) analysis.
//S.C : O(N), N = total length of all strings in the wordlist, to store in the maps/set.
class Solution {
public:
    unordered_set<string> exactWords;       // Rule 1: Stores original words for exact match.
    unordered_map<string, string> caseMap;    // Rule 2: lowercase key -> original word (first occurrence)
    unordered_map<string, string> vowelMap;   // Rule 3: vowel-masked lowercase key -> original word (first occurrence)
    
    // Helper function to convert a string to lowercase
    string toLower(const string& s) {
        string res = s; // Create a copy of the string
        for (char& c : res) {
            c = tolower(c); // Convert each character to lowercase
        }
        return res;
    }

    // Helper function to convert a string to its vowel-masked form (vowels replaced with '*')
    // Note: Assumes input string 's' is already lowercase.
    string maskVowels(const string& s) {
        string res = s; // Create a copy
        for (char& c : res) {
            // Check if the character is any vowel
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                c = '*'; // Replace vowel with a placeholder mask
            }
        }
        return res;
    }

    // Main query checking function that respects precedence rules
    string checkForMatch(const string& query) {
        // Rule 1: Exact match (case-sensitive)
        if (exactWords.count(query)) {
            return query; // Found an exact match
        }

        // Rule 2: Case error match (case-insensitive)
        string lowerQuery = toLower(query); // Convert query to lowercase
        if (caseMap.count(lowerQuery)) {
            return caseMap[lowerQuery]; // Return the first matching original word from the wordlist
        }

        // Rule 3: Vowel error match (case-insensitive AND vowel-insensitive)
        string maskedQuery = maskVowels(lowerQuery); // Mask vowels on the lowercase query
        if (vowelMap.count(maskedQuery)) {
            return vowelMap[maskedQuery]; // Return the first matching original word
        }

        // 4. No match found after all checks
        return ""; // Return empty string
    }

    // Main function to drive the spellchecker
    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
        // Clear maps/set to handle multiple test cases if this class is reused
        exactWords.clear();
        caseMap.clear();
        vowelMap.clear();

        // --- Pre-processing Step ---
        // Iterate through the wordlist once to build our lookup data structures
        for (string word : wordlist) {
            // Rule 1: Add every original word to the exact set
            exactWords.insert(word); 

            string lowerWord = toLower(word);
            
            // Rule 2: Populate the case-insensitive map
            // Only add if the lowercase version doesn't exist yet, preserving the "first occurrence" rule
            if (caseMap.find(lowerWord) == caseMap.end()) { 
                caseMap[lowerWord] = word;
            }

            string maskedWord = maskVowels(lowerWord);
            
            // Rule 3: Populate the vowel-error map
            // Only add if the masked version doesn't exist yet, preserving the "first occurrence" rule
            if (vowelMap.find(maskedWord) == vowelMap.end()) { 
                vowelMap[maskedWord] = word;
            }
        }

        // --- Querying Step ---
        vector<string> result; // Vector to store final answers
        for (string query : queries) {
            // Process each query against the pre-built maps using the precedence rules
            result.push_back(checkForMatch(query));
        }
        return result; // Return the list of corrected words
    }
};

/*
*
* Dry Run
*
* wordlist = ["KiTe","kite","hare","Hare"], queries = ["kite","Kite","keto"]
*
* --- Pre-processing ---
* 1. word = "KiTe":
* - exactWords: {"KiTe"}
* - lowerWord = "kite"
* - caseMap: {"kite" -> "KiTe"}
* - maskedWord = "k*t*"
* - vowelMap: {"k*t*" -> "KiTe"}
*
* 2. word = "kite":
* - exactWords: {"KiTe", "kite"}
* - lowerWord = "kite". key "kite" already in caseMap. Skip.
* - maskedWord = "k*t*". key "k*t*" already in vowelMap. Skip.
*
* 3. word = "hare":
* - exactWords: {"KiTe", "kite", "hare"}
* - lowerWord = "hare"
* - caseMap: {"kite"->"KiTe", "hare"->"hare"}
* - maskedWord = "h*r*"
* - vowelMap: {"k*t*"->"KiTe", "h*r*"->"hare"}
*
* 4. word = "Hare":
* - exactWords: {"KiTe", "kite", "hare", "Hare"}
* - lowerWord = "hare". key "hare" already in caseMap. Skip.
* - maskedWord = "h*r*". key "h*r*" already in vowelMap. Skip.
*
* Final Data Structures:
* exactWords: {"KiTe", "kite", "hare", "Hare"}
* caseMap:    {"kite" -> "KiTe", "hare" -> "hare"}
* vowelMap:   {"k*t*" -> "KiTe", "h*r*" -> "hare"}
*
* --- Querying ---
* 1. query = "kite":
* - Check exactWords: "kite" exists.
* - Return "kite".
* - result: ["kite"]
*
* 2. query = "Kite":
* - Check exactWords: "Kite" NOT found.
* - lowerQuery = "kite". Check caseMap: "kite" exists.
* - Return caseMap["kite"] -> "KiTe".
* - result: ["kite", "KiTe"]
*
* 3. query = "keto":
* - Check exactWords: "keto" NOT found.
* - lowerQuery = "keto". Check caseMap: "keto" NOT found.
* - maskedQuery = "k*t*". Check vowelMap: "k*t*" exists.
* - Return vowelMap["k*t*"] -> "KiTe".
* - result: ["kite", "KiTe", "KiTe"]
*
* Final Answer: ["kite", "KiTe", "KiTe"] (matching subset of Example 1)
*/
```

---

### Key Insights 🧠

1.  **Precedence is Critical**: The problem explicitly defines a strict order of rules (Exact > Case-Insensitive > Vowel-Error). Your solution *must* check for matches in this specific sequence.
2.  **"First Match" Rule**: Rules 2 and 3 require returning the *first* word from the original `wordlist` that satisfies the condition. This is why, during our map population, we only insert a key (`lowerWord` or `maskedWord`) if it's not already present. This cleverly "locks in" the very first original word we encounter for each transformed key.
3.  **Use the Right Data Structure**:
    * An `unordered_set` is perfect for Rule 1 (Exact Match) due to its O(1) average lookup time.
    * `unordered_map` is the ideal choice for Rules 2 and 3. It provides an O(1) average-time bridge from a *transformed key* (lowercase or vowel-masked) back to the *original value* we need to return.
4.  **Vowel Masking**: The simplest way to handle the vowel error (Rule 3) is to "de-vowel" the words. By converting all vowels to a single placeholder (like `*`) *after* making the string lowercase, we create a common key. For example, `keto`, `kAti`, `kIte`, and `kuti` all become `k*t*`, allowing them to match the same entry in the `vowelMap`.

---

### Further Exploration 🧭

* What if consonants could also be mistaken, but only for "similar-sounding" ones (e.g., 'f' vs 'ph')? How would you design a map for that?
* This problem uses maps to store the *first* valid match. What if you needed to return *all* valid matches for a query? You would change the map values from `string` to `vector<string>`, but this would significantly change the logic.

---

### References 📚

* [LeetCode Discussion: C++ using Set and Maps](https://leetcode.com/problems/vowel-spellchecker/solutions/211189/c-0ms-unordered_set-unordered_map/)
* [Data Structures: Unordered Map (Hash Map)](https://en.cppreference.com/w/cpp/container/unordered_map)
* [Data Structures: Unordered Set (Hash Set)](https://en.cppreference.com/w/cpp/container/unordered_set)

---

### Tags 🏷️

![String](https://img.shields.io/badge/String-blue?style=for-the-badge&logo=probot)
![Hash Table](https://img.shields.io/badge/Hash_Table-orange?style=for-the-badge&logo=postman)
![Set](https://img.shields.io/badge/Set-green?style=for-the-badge)
![Map](https://img.shields.io/badge/Map-purple?style=for-the-badge)

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/vowel-spellchecker/description/) for original content and copyright.**

---

## 👨‍💻 Author

-   [imnilesh18](https://github.com/imnilesh18)