<div align="center">

# ✨ 3227. Vowels Game in a String ✨

| Difficulty | Tags                               |
| :--------: | :--------------------------------- |
|   Medium   | `Game Theory`, `String`, `Brain Teaser` |

</div>

🔗 **Problem Link:** [Vowels Game in a String on LeetCode](https://leetcode.com/problems/vowels-game-in-a-string/description/)

---

### 📝 Problem Statement

Alice and Bob are playing a game on a string `s`. They take turns, with Alice starting first.

-   On **Alice's turn**, she must remove a non-empty substring that contains an **odd** number of vowels.
-   On **Bob's turn**, he must remove a non-empty substring that contains an **even** number of vowels.

The first player who cannot make a move loses. Assuming both play optimally, return `true` if Alice wins, and `false` otherwise. The English vowels are 'a', 'e', 'i', 'o', and 'u'.

---

### 🛑 Constraints

-   `1 <= s.length <= 10^5`
-   `s` consists only of lowercase English letters.

---

### 📊 Examples

| Input `s`     | Output | Explanation                                                                                                                                                                                                                               |
| :------------ | :----: | :---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `"leetcoder"` | `true` | Alice can remove `"eetco"` (3 vowels), leaving `"lder"`. Bob can remove `"d"` (0 vowels), leaving `"ler"`. Alice can remove `"ler"` (1 vowel). Bob has no moves and loses.                                                                    |
| `"bbcd"`      | `false`| The string has no vowels. Alice needs to remove a substring with an odd number of vowels. Since no such substring exists, she cannot make a move and loses immediately.                                                                     |

---

### 🧠 Approach & Intuition

This problem seems complex due to the game theory nature, but it simplifies dramatically with a key observation about the winning and losing conditions.

1.  **Alice's Goal:** To win, Alice must always have a valid move available. A valid move for her is to find and remove any substring with an odd number of vowels.
2.  **Bob's Goal:** To win, Bob must force Alice into a state where she has no valid moves.
3.  **The Core Logic:**
    * **Case 1: The string contains at least one vowel.**
        If there's even one vowel, Alice can *always* make a move. She can simply choose the substring containing just that single vowel (which is an odd number: 1). By doing this, she can win the game. A more optimal move for her would be to remove the entire string if it has an odd number of vowels, winning in one turn. If the string has an even number of vowels, she can remove a prefix of the string ending just before the last vowel. This leaves just one vowel for Bob, who cannot make a move on a string with one vowel (he needs an even number of vowels). Therefore, if any vowel exists, Alice has a winning strategy.
    * **Case 2: The string contains zero vowels.**
        Alice's first turn requires her to remove a substring with an *odd* number of vowels. If the entire string has no vowels, no substring can possibly have an odd number of vowels. She is stuck and has no valid moves. Therefore, she loses on her very first turn.

**Conclusion:** The winner is determined before the first move is even made. Alice wins if and only if there is at least one vowel in the string. Otherwise, Bob wins. The problem reduces to simply checking for the existence of any vowel.

---

### 💻 Solution Code

<details>
<summary><strong>C++ Solution (Simple Iteration)</strong></summary>

```cpp
// Intuition: The game's outcome is determined by whether Alice can make the first move. She can only move if there is at least one vowel in the string. If a vowel exists, she can always select a substring with an odd number of vowels (e.g., a substring with just one vowel) and secure a win. If no vowels exist, she has no possible moves and loses immediately.

// Approach: We iterate through the string character by character. If we find any vowel ('a', 'e', 'i', 'o', 'u'), we know Alice has a winning move, so we can immediately return true. If the loop completes without finding any vowels, it means Alice cannot make a move, and we return false.

// Time Complexity: O(n), where n is the length of the string. In the worst case, we might scan the entire string once.
// Space Complexity: O(1), as we use no extra space proportional to the input size.

class Solution {
public:
    bool doesAliceWin(string s) {
        // Iterate over each character in the string.
        for(char &ch : s) {
            // Check if the character is a vowel.
            if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
                // If a vowel is found, Alice can make a move and wins.
                return true;
            }
        }
        // If no vowels are found after checking the whole string, Alice loses.
        return false;
    }
};

/*
*
* Dry Run
*
* Example 1: s = "leetcoder"
* 1. Loop starts. ch = 'l'. Not a vowel.
* 2. ch = 'e'. It's a vowel.
* 3. Condition (ch == 'e') is true.
* 4. Return true. Alice wins.
*
* Example 2: s = "bbcd"
* 1. Loop starts. ch = 'b'. Not a vowel.
* 2. ch = 'b'. Not a vowel.
* 3. ch = 'c'. Not a vowel.
* 4. ch = 'd'. Not a vowel.
* 5. Loop finishes. No vowels were found.
* 6. Return false. Alice loses.
*
*/
```

</details>

<details>
<summary><strong>C++ Solution (One-Liner STL)</strong></summary>

```cpp
// Intuition: Same as the iterative approach. The game hinges on the presence of at least one vowel. If a vowel exists, Alice wins; otherwise, she loses.

// Approach: This is a more concise version of the iterative approach using C++ Standard Template Library (STL). The `any_of` algorithm checks if a given predicate is true for at least one element in a range. We define a lambda function that serves as the predicate, checking if a character is a vowel. `any_of` applies this lambda to every character in the string `s`. If it finds any vowel, it returns true; otherwise, it returns false.

// Time Complexity: O(n), where n is the length of the string `s`. `any_of` inspects each element at most once.
// Space Complexity: O(1), as no significant extra space is used.

class Solution {
public:
    bool doesAliceWin(string s) {
        // Define a lambda function to check if a character is a vowel.
        auto is_vowel = [](char ch) {
            // The find method returns string::npos if the character is not found.
            return string("aeiou").find(ch) != string::npos;
        };
        // Use std::any_of to check if the lambda is true for any character in the string.
        return any_of(s.begin(), s.end(), is_vowel);
    }
};

/*
*
* Dry Run
*
* Example 1: s = "leetcoder"
* 1. `any_of` starts iterating through "leetcoder".
* 2. For 'l', is_vowel('l') is false.
* 3. For 'e', is_vowel('e') is true because "aeiou".find('e') is not string::npos.
* 4. `any_of` short-circuits and returns true immediately.
*
* Example 2: s = "bbcd"
* 1. `any_of` iterates through "bbcd".
* 2. is_vowel('b') -> false
* 3. is_vowel('b') -> false
* 4. is_vowel('c') -> false
* 5. is_vowel('d') -> false
* 6. `any_of` reaches the end of the string without the predicate returning true.
* 7. It returns false.
*
*/
```

</details>

<details>
<summary><strong>Java Solution (Simple Iteration)</strong></summary>

```java
// Intuition: The core logic remains the same: Alice's ability to win depends entirely on her being able to make a first move. This is only possible if the string contains at least one vowel. One vowel is enough for her to form a substring with an odd count of vowels (1) and guarantee a win.

// Approach: We iterate through the character array of the input string. For each character, we check if it matches any of the five vowels. If a match is found, we immediately know Alice can win and return true. If we iterate through the entire string without finding a single vowel, Alice has no moves, so we return false.

// Time Complexity: O(n), where n is the length of the string `s`, as we traverse the string at most once.
// Space Complexity: O(n) in Java because `s.toCharArray()` creates a copy of the string's characters. If iterating with `s.charAt(i)`, it would be O(1).

class Solution {
    public boolean doesAliceWin(String s) {
        // Convert string to character array for iteration.
        for (char ch : s.toCharArray()) {
            // Check if the current character is a vowel.
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
                // As soon as one vowel is found, Alice has a winning strategy.
                return true;
            }
        }
        // If the loop completes, no vowels were found. Alice loses.
        return false;
    }
}

/*
*
* Dry Run
*
* Example 1: s = "leetcoder"
* 1. Loop starts. ch = 'l'. Not a vowel.
* 2. ch = 'e'. It's a vowel. The condition is met.
* 3. Return true. Alice wins.
*
* Example 2: s = "bbcd"
* 1. Loop iterates through 'b', 'b', 'c', 'd'. None are vowels.
* 2. The loop finishes.
* 3. Return false. Alice loses.
*
*/
```

</details>

<details>
<summary><strong>Java Solution (One-Liner JCF)</strong></summary>

```java
// Intuition: Identical to the other solutions. The presence of a single vowel is a sufficient condition for Alice to win the game.

// Approach: This solution uses Java Streams for a functional and concise approach. `s.chars()` creates an IntStream of character values from the string. The `anyMatch` terminal operation checks if any element of the stream matches the provided predicate. The predicate is a lambda expression `ch -> "aeiou".indexOf(ch) >= 0`, which returns true if the character `ch` is found within the string "aeiou". If `anyMatch` finds such a character, it returns true and stops processing, otherwise it returns false after checking all characters.

// Time Complexity: O(n), where n is the length of `s`. The `anyMatch` operation will iterate through the characters until a vowel is found or the string ends.
// Space Complexity: O(1), as the stream operations are generally lazy and do not create intermediate collections of the size of the input.

class Solution {
    public boolean doesAliceWin(String s) {
        // Use a stream to check if any character in the string is a vowel.
        return s.chars().anyMatch(ch -> "aeiou".indexOf(ch) >= 0);
    }
}

/*
*
* Dry Run
*
* Example 1: s = "leetcoder"
* 1. s.chars() creates a stream of characters: 'l', 'e', 'e', 't', 'c', 'o', 'd', 'e', 'r'.
* 2. `anyMatch` tests the predicate `ch -> "aeiou".indexOf(ch) >= 0`.
* 3. For 'l', indexOf returns -1. Predicate is false.
* 4. For 'e', indexOf returns 1 (>= 0). Predicate is true.
* 5. `anyMatch` short-circuits and returns true.
*
* Example 2: s = "bbcd"
* 1. s.chars() creates a stream: 'b', 'b', 'c', 'd'.
* 2. `anyMatch` tests the predicate on each character. indexOf always returns -1.
* 3. The stream ends without the predicate ever being true.
* 4. `anyMatch` returns false.
*
*/
```

</details>

---

### 💡 Key Insights

-   The problem is a brain teaser disguised as a complex game theory question.
-   The optimal strategy for both players is irrelevant because the game's outcome is decided by the initial state of the string.
-   Alice's losing condition is the inability to make her first move. This only happens if there are zero vowels in the string.
-   If there is at least one vowel, Alice can always make a move that guarantees a win, regardless of Bob's actions.

---

### 🚀 Further Exploration

-   Consider how the game would change if the rules were reversed (Alice needs an even count, Bob needs an odd count).
-   What if the goal was not to win but to achieve the longest possible game? How would the strategy change?
-   Think about a variation where players can remove any substring, but they get points equal to the number of vowels removed.

---

### 📚 References

-   [Game Theory](https://en.wikipedia.org/wiki/Game_theory)
-   [Optimal Strategy](https://en.wikipedia.org/wiki/Optimal_strategy)

---

### #️⃣ Tags

`Game Theory`, `String`, `Brain Teaser`, `Observation`

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/vowels-game-in-a-string/) for original content and copyright.**

---

## 👨‍💻 Author

-   [imnilesh18](https://github.com/imnilesh18)