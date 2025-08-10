# 🔢 869. Reordered Power of 2

<p align="center">
  <a href="https://leetcode.com/problems/reordered-power-of-2/" target="_blank">
    <img src="https://img.shields.io/badge/LeetCode-Problem-orange?style=for-the-badge&logo=leetcode" alt="LeetCode Problem">
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty: Medium">
  <img src="https://img.shields.io/badge/License-MIT-green?style=for-the-badge" alt="License: MIT">
</p>

> ⚡️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> The problem statement and test cases are based on the [LeetCode problem](https://leetcode.com/problems/reordered-power-of-2/).

---

## 📄 Problem Statement

You are given an integer `n`. We reorder the digits in any order (including the original order) such that the leading digit is not zero.

Return `true` if and only if we can do this so that the resulting number is a power of two.

---

## 🧪 Examples

| Input    | Output  | Explanation                                                      |
| :------- | :------ | :--------------------------------------------------------------- |
| `n = 1`  | `true`  | 1 is 2<sup>0</sup>.                                              |
| `n = 10` | `false` | Reordering `10` gives `01` (invalid) or `10` (not a power of 2). |
| `n = 46` | `true`  | Reordering `46` can give `64`, which is 2<sup>6</sup>.           |

<details>
<summary><strong>Example Walkthrough (n = 215)</strong></summary>

Let's take the input `n = 215`. The digits are `1`, `2`, and `5`.
We can reorder these digits to form various numbers:

- `125`
- `152`
- `215`
- `251`
- `512`
- `521`

Among these permutations, `512` is a power of two (2<sup>9</sup>). Therefore, the function should return `true`.

</details>

---

## 🛑 Constraints

- `1 <= n <= 10^9`

---

## 🛠️ Approach

The core idea behind solving this problem efficiently is to understand that **if a number `n` can be reordered to form a power of two, it must have the exact same digits (and the same count of each digit) as that power of two**.

For example, `46` can be reordered to `64`.

- Digits of `46`: one `4`, one `6`.
- Digits of `64`: one `6`, one `4`.
  The digit counts match.

Instead of generating all `d!` permutations of the digits of `n` (which is computationally expensive), we can transform both the input `n` and all relevant powers of two into a canonical representation based on their digit counts. If any of these canonical forms match, we have found a valid reordering.

The four solutions below explore different ways to create and compare these canonical representations:

1.  **Sorting:** Sort the digits of the numbers. If the sorted strings are the same, the original numbers are permutations of each other.
2.  **Preprocessing with a Set:** Pre-calculate the sorted-digit strings of all powers of two (within the `10^9` constraint) and store them in a set for O(1) lookups.
3.  **Digit Frequency Vector:** Count the frequency of each digit (0-9) and store it in a 10-element vector. Two numbers are permutations if their frequency vectors are identical.
4.  **Digit Frequency Number:** Encode the digit frequencies into a single integer. For example, if a number has two `1`s and one `3`, the encoded number could be formed by `10^1 + 10^1 + 10^3`.

Since `n` is at most `10^9`, we only need to check powers of two up to `2^29`, as `2^30` exceeds `10^9`. This makes checking against all relevant powers of two very fast.

---

## 🧑‍💻 Solution Code (C++)

### Approach 1: Using Sorting

```cpp
// Intuition:
// If a number can be reordered to form a power of two, then its digits must be a permutation of the digits of that power of two.
// A canonical way to check for permutation is to sort the digits. If the sorted digit strings of two numbers are identical, they are permutations of each other.
//
// Approach:
// 1. Convert the input number `n` into a string.
// 2. Sort the characters of the string representation of `n`.
// 3. Iterate through all relevant powers of two (from 2^0 to 2^29, since 2^30 > 10^9).
// 4. For each power of two, convert it to its sorted string representation.
// 5. Compare the sorted string of `n` with the sorted string of the current power of two.
// 6. If a match is found, it means `n` can be reordered to form that power of two, so return true.
// 7. If the loop finishes without a match, return false.
//
// Time Complexity: O(d log d), where d is the number of digits in n.
// The loop runs a constant number of times (~30). The dominant operation is sorting the digits of n. For a number up to 10^9, d is at most 10, so d*log(d) is very small.
//
// Space Complexity: O(d), for storing the string representation of the numbers.
class Solution {
public:
    // Helper function to get the sorted string representation of a number
    string getSortedStr(int n) {
        string s = to_string(n); // Convert number to string
        sort(begin(s), end(s));  // Sort the string
        return s;
    }

    bool reorderedPowerOf2(int n) {
        // Get the canonical (sorted) representation of the input n
        string s = getSortedStr(n);

        // check all 2 powers and see if it matches with s
        // 2^29 is the largest power of 2 less than 10^9
        for(int p = 0; p <= 29; p++) {
            // Check if the sorted string of n matches the sorted string of any power of 2
            if(s == getSortedStr(1 << p)) { // (1 << p) is a fast way to calculate 2^p
                return true; // Found a match
            }
        }

        return false; // No power of 2 matches
    }
};

/*
*
* Dry Run (n = 46)
*
* 1. reorderedPowerOf2(46) is called.
* 2. `getSortedStr(46)` is called.
* - `to_string(46)` -> "46"
* - `sort("46")` -> "46"
* - Returns "46". So, `s` = "46".
* 3. Loop starts for `p` from 0 to 29.
* - p = 0, power = 1. `getSortedStr(1)` -> "1". "46" != "1".
* - p = 1, power = 2. `getSortedStr(2)` -> "2". "46" != "2".
* - ...
* - p = 5, power = 32. `getSortedStr(32)` -> "23". "46" != "23".
* - p = 6, power = 64. `getSortedStr(64)` is called.
* - `to_string(64)` -> "64"
* - `sort("64")` -> "46"
* - Returns "46".
* - The condition `s == getSortedStr(1 << p)` becomes `"46" == "46"`, which is true.
* 4. The function returns `true`.
*
*/
```

### Approach 2: Using Preprocessing and a Set

```cpp
// Intuition:
// The process of generating and sorting strings for powers of two is repetitive for every call to `reorderedPowerOf2`.
// We can optimize this by pre-calculating the sorted string representations of all relevant powers of two and storing them in a hash set for fast lookups.
//
// Approach:
// 1. Create a global or static `unordered_set` to store the canonical forms of powers of two.
// 2. Implement a `buildSet` function that runs only once.
// 3. Inside `buildSet`, iterate from p = 0 to 29. For each power `2^p`:
//    a. Convert it to a string.
//    b. Sort the string.
//    c. Insert the sorted string into the set.
// 4. In the main function `reorderedPowerOf2`:
//    a. Ensure the set is built (call `buildSet` if it's empty).
//    b. Convert the input `n` to its sorted string representation.
//    c. Check if this sorted string exists in the pre-computed set.
//    d. Return the result of the check.
//
// Time Complexity: O(d log d), where d is the number of digits.
// The pre-computation runs once. Each subsequent call to `reorderedPowerOf2` takes O(d log d) to sort the input string and O(d) for the hash set lookup.
//
// Space Complexity: O(d), technically O(30 * d) for the set, but this is a constant factor.
// The space is dominated by the storage of ~30 sorted strings, each with at most 10 digits.
class Solution {
public:
    unordered_set<string> st; // Set to store pre-computed sorted strings of powers of 2

    // Function to build the set of sorted power-of-2 strings
    void buildSet() {
        // 2^p from p = 0 to 29
        // convert to string
        // sort it
        // store it in st
        for(int p = 0; p <= 29; p++) {
            string s = to_string(1 << p); // Convert power of 2 to string
            sort(begin(s), end(s));       // Sort its digits
            st.insert(s);                 // Store the canonical form in the set
        }
    }

    bool reorderedPowerOf2(int n) {
        // Build the set only once upon the first call
        if(st.empty()) {
            buildSet(); // call only once (static-like behavior)
        }

        // Convert the input number to its sorted string form
        string s = to_string(n);
        sort(begin(s), end(s));

        // Check if the sorted string of n exists in our set of power-of-2 strings
        return st.count(s); // .count() returns 1 if found, 0 otherwise
    }
};

/*
*
* Dry Run (n = 46)
*
* 1. reorderedPowerOf2(46) is called.
* 2. `st.empty()` is true (on the first run). `buildSet()` is called.
* 3. `buildSet()` populates `st` with sorted strings of powers of two: "1", "2", "4", "8", "16", "23", "46" (from 64), ...
* 4. The function continues. `to_string(46)` -> "46".
* 5. `sort("46")` -> "46". `s` becomes "46".
* 6. `st.count("46")` is called. The set `st` contains "46" (from the number 64). The count is 1.
* 7. The function returns `true` (since 1 is treated as true in a boolean context).
*
*/
```

### Approach 3: Count and Store Digits in a Vector

```cpp
// Intuition:
// Sorting strings works, but comparing digit frequency counts is a more direct way to check for permutations.
// We can represent the digit composition of a number using a frequency array (or vector) of size 10, where each index from 0-9 stores the count of that digit.
//
// Approach:
// 1. Create a helper function `getVectorCountFormat(int n)` that:
//    a. Initializes a vector of size 10 with all zeros.
//    b. Extracts each digit of `n` using the modulo (`% 10`) and division (`/ 10`) operators.
//    c. Increments the count for the extracted digit at the corresponding index in the vector.
//    d. Returns the final frequency vector.
// 2. In `reorderedPowerOf2(int n)`, first get the frequency vector for the input `n`.
// 3. Iterate from `p = 0` to `29`.
// 4. In each iteration, get the frequency vector for the power of two, `1 << p`.
// 5. Compare the input number's vector with the power of two's vector.
// 6. If the vectors are identical, return `true`.
// 7. If the loop completes, return `false`.
//
// Time Complexity: O(d), where d is the number of digits in n.
// The loop is constant time (~30 iterations). Getting the vector count takes O(d) time. Vector comparison also takes constant time (10 elements).
//
// Space Complexity: O(1). The space used for the vectors is constant (size 10).
class Solution {
public:
    // Helper to convert a number to its digit frequency vector
    vector<int> getVectorCountFormat(int n) {
        vector<int> vec(10, 0); // Vector to store counts of digits 0-9

        // Example: n = 256
        // Iteration 1: vec[6]++, n = 25
        // Iteration 2: vec[5]++, n = 2
        // Iteration 3: vec[2]++, n = 0
        while(n) {
            vec[n % 10]++; // Increment count for the last digit
            n /= 10;       // Remove the last digit
        }

        return vec;
    }

    bool reorderedPowerOf2(int n) {
        // Get the frequency count vector for the input number
        vector<int> input = getVectorCountFormat(n);

        // Iterate through powers of 2
        for(int p = 0; p <= 29; p++) {
            // If the frequency vector of n matches the vector of a power of 2
            if(input == getVectorCountFormat(1 << p)) {
                return true; // It's a valid reordering
            }
        }

        return false;
    }
};

/*
*
* Dry Run (n = 46)
*
* 1. reorderedPowerOf2(46) is called.
* 2. `getVectorCountFormat(46)` is called.
* - `vec` = [0,0,0,0,0,0,0,0,0,0]
* - n = 46. `vec[6]++`. `vec` is now [0,0,0,0,0,0,1,0,0,0]. n becomes 4.
* - n = 4. `vec[4]++`. `vec` is now [0,0,0,0,1,0,1,0,0,0]. n becomes 0.
* - Loop ends. Returns the vector. `input` = [0,0,0,0,1,0,1,0,0,0].
* 3. Loop for `p` from 0 to 29 starts.
* - ... (no matches for p=0 to 5)
* - p = 6, power = 64. `getVectorCountFormat(64)` is called.
* - It similarly produces the vector [0,0,0,0,1,0,1,0,0,0].
* - The condition `input == getVectorCountFormat(1 << p)` is true.
* 4. The function returns `true`.
*
*/
```

### Approach 4: Count and Store Digits in a Number

```cpp
// Intuition:
// Instead of a vector, we can encode the digit frequency into a single number.
// This is a clever trick to create a unique signature for the digit counts. We can use powers of 10 as "bins" for each digit.
// For a digit `d`, we add `10^d` to our signature number.
//
// Approach:
// 1. Create a helper function `getCountFormat(int n)` that returns a number signature (long long to be safe, though int works here).
// 2. Initialize a signature number `num` to 0.
// 3. Extract each digit of `n`. For each digit `d`, add `pow(10, d)` to `num`.
// 4. This results in a number where the digit at the 10^k place represents the frequency of digit k. Example: For 225, signature = 10^2 + 10^2 + 10^5 = 200 + 100000 = 100200.
// 5. In `reorderedPowerOf2`, get the signature for the input `n`.
// 6. Iterate through powers of two from `p = 0` to `29`.
// 7. Get the signature for each power of two and compare it with the input's signature.
// 8. If they match, return `true`.
// 9. If the loop finishes, return `false`.
//
// Time Complexity: O(d), where d is the number of digits. The logic is very similar to the vector approach.
//
// Space Complexity: O(1), as we only use a few variables to store numbers.
class Solution {
public:
    // Helper to convert a number to its digit frequency signature number
    long long getCountFormat(int n) {
        long long num = 0; // Use long long for safety, though int may pass

        // Example: n = 256
        // Iteration 1: num += pow(10, 6), n = 25
        // Iteration 2: num += pow(10, 5), n = 2
        // Iteration 3: num += pow(10, 2), n = 0
        while(n) {
            // For each digit (n % 10), add 10 to the power of that digit to our signature
            num += pow(10, n % 10);
            n /= 10; // Move to the next digit
        }

        return num;
    }

    bool reorderedPowerOf2(int n) {
        // Get the signature for the input number
        long long input = getCountFormat(n);

        // Iterate through powers of 2
        for(int p = 0; p <= 29; p++) {
            // If the signature of n matches the signature of a power of 2
            if(input == getCountFormat(1 << p)) {
                return true; // Match found
            }
        }

        return false;
    }
};

/*
*
* Dry Run (n = 46)
*
* 1. reorderedPowerOf2(46) is called.
* 2. `getCountFormat(46)` is called.
* - `num` = 0
* - n = 46. digit is 6. `num += pow(10, 6)` -> `num` = 1000000. n becomes 4.
* - n = 4. digit is 4. `num += pow(10, 4)` -> `num` = 1000000 + 10000 = 1010000. n becomes 0.
* - Returns 1010000. `input` = 1010000.
* 3. Loop for `p` from 0 to 29 starts.
* - ... (no matches for p=0 to 5)
* - p = 6, power = 64. `getCountFormat(64)` is called.
* - It similarly produces the number 1010000.
* - The condition `input == getCountFormat(1 << p)` becomes `1010000 == 1010000`, which is true.
* 4. The function returns `true`.
*
*/
```

---

## 💡 Key Insights

- **Permutation as Anagrams:** The problem is equivalent to checking if the input number `n` is an anagram of any power of two.
- **Canonical Representation:** The key to solving anagram-style problems efficiently is to convert strings/numbers into a canonical (standard) form. Sorting and frequency counting are two standard methods for this.
- **Constraint-based Optimization:** The constraint `n <= 10^9` is crucial. It limits the search space of powers of two to a very small, manageable number (only 30 values), allowing for solutions that iterate through all possibilities without timing out.

---

## 🚀 Further Exploration

If you found this problem interesting, you might also like these related problems that use similar concepts of frequency counting and anagrams:

- [**49. Group Anagrams**](https://leetcode.com/problems/group-anagrams/): A classic problem where you group words that are anagrams of each other. The sorted string or frequency map approach is directly applicable here.
- [**242. Valid Anagram**](https://leetcode.com/problems/valid-anagram/): The simplest form of this concept, checking if two strings are anagrams of each other.

---

## 🔗 References

- **Original Problem:** [https://leetcode.com/problems/reordered-power-of-2/](https://leetcode.com/problems/reordered-power-of-2/)

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

<p>
  <img src="https://img.shields.io/badge/Tag-Math-blue?style=for-the-badge" alt="Math Tag">
  <img src="https://img.shields.io/badge/Tag-Sorting-lightgrey?style=for-the-badge" alt="Sorting Tag">
  <img src="https://img.shields.io/badge/Tag-Counting-yellow?style=for-the-badge" alt="Counting Tag">
</p>

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/reordered-power-of-2/) for original content and copyright.**
