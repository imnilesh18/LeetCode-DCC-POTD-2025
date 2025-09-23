# 🪙 165. Compare Version Numbers

<p align="center">
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow" alt="Difficulty: Medium" />
  <img src="https://img.shields.io/badge/Tags-String-blue" alt="Tags: String" />
  <img src="https://img.shields.io/badge/Tags-Two%20Pointers-blue" alt="Tags: Two Pointers" />
</p>

---

## 📝 Problem Statement

Given two version strings, `version1` and `version2`, compare them. A version string consists of **revisions** separated by dots `.`. The value of the revision is its integer conversion ignoring leading zeros.

To compare version strings, compare their revision values in **left-to-right order**. If one of the version strings has fewer revisions, treat the missing revision values as `0`.

Return the following:
- If `version1 < version2`, return `-1`.
- If `version1 > version2`, return `1`.
- Otherwise, return `0`.

---

## ⚙️ Constraints

- `1 <= version1.length, version2.length <= 500`
- `version1` and `version2` only contain digits and `.`.
- `version1` and `version2` are **valid** version numbers.
- All the given revisions in `version1` and `version2` can be stored in a **32-bit integer**.

---

##  illustrative Examples

| Input | Output | Explanation |
| :--- | :--- | :--- |
| `version1 = "1.2"`, `version2 = "1.10"` | `-1` | version1's second revision is "2" and version2's second revision is "10": 2 < 10, so `version1 < version2`. |
| `version1 = "1.01"`, `version2 = "1.001"` | `0` | Ignoring leading zeroes, both "01" and "001" represent the same integer "1". |
| `version1 = "1.0"`, `version2 = "1.0.0.0"`| `0` | version1 has fewer revisions, so missing revisions are treated as "0". |
| `version1 = "0.1"`, `version2 = "1.1"` | `-1` | version1's first revision is "0" and version2's is "1". 0 < 1, so `version1 < version2`. |

---

## 💡 Approach

The problem requires comparing two version strings by their revision numbers. A straightforward approach is to split each version string into its constituent revisions based on the `.` delimiter. This process is often called **tokenization**.

Once we have the lists of revisions (tokens) for both version strings, we can iterate through them from left to right. At each position, we compare the integer values of the corresponding revisions.

**Key considerations:**
1.  **Tokenization**: We can use built-in utilities like `stringstream` in C++ or the `split()` method in Java to easily break the strings into a list of revision numbers.
2.  **Integer Conversion**: The revision strings need to be converted to integers for numerical comparison. Standard library functions like `stoi` (C++) or `Integer.parseInt` (Java) handle this, automatically ignoring leading zeros.
3.  **Unequal Lengths**: If one version string has more revisions than the other (e.g., `"1.0"` vs. `"1.0.0"`), we must treat the missing revisions of the shorter version as `0`. We can handle this by iterating up to the length of the longer list of tokens and defaulting to `0` for any index that is out of bounds for the shorter list.

The comparison proceeds revision by revision. If at any point the integer value of a revision in `version1` is greater than `version2`, we return `1`. If it's less, we return `-1`. If we iterate through all revisions and find them all to be equal, we return `0`.

<details>
<summary>Click for a step-by-step walkthrough</summary>

Let's take `version1 = "1.2.3"` and `version2 = "1.2"`.

1.  **Tokenize `version1`**: The tokens are `["1", "2", "3"]`.
2.  **Tokenize `version2`**: The tokens are `["1", "2"]`.
3.  **Start Comparison**:
    * **Index 0**: `v1[0]` is "1", `v2[0]` is "1". `Integer("1") == Integer("1")`. They are equal, so we continue.
    * **Index 1**: `v1[1]` is "2", `v2[1]` is "2". `Integer("2") == Integer("2")`. They are equal, continue.
    * **Index 2**: `v1[2]` is "3". `v2` has no token at index 2, so we treat it as `0`. `Integer("3") > 0`. Since `version1`'s revision is greater, we immediately return `1`.

This approach correctly handles all specified constraints and examples.
</details>

---

## 🖥️ Solution Code

### C++ Solution

```cpp
// Intuition:
// The problem requires a revision-by-revision comparison of two version strings. The most direct way to handle this is to parse each string, separating it into a sequence of revision numbers, and then comparing these numbers sequentially from left to right.

// Approach:
// 1. Create a helper function `getTokens` that takes a version string and splits it by the '.' delimiter using a `stringstream`. This function returns a vector of strings, where each string is a revision number.
// 2. In the main `compareVersion` function, call `getTokens` for both `version1` and `version2` to get two vectors of revision strings, `v1` and `v2`.
// 3. Iterate from index `i = 0` up to the maximum length of the two token vectors. This ensures we cover all revisions from both versions.
// 4. Inside the loop, for each index `i`, get the integer value of the revision.
//    - If `i` is within the bounds of `v1`, convert `v1[i]` to an integer using `stoi`. Otherwise, use `0` as the default value.
//    - Do the same for `v2`.
// 5. Compare the two integer values (`a` and `b`).
//    - If `a > b`, `version1` is greater, so return 1.
//    - If `b > a`, `version2` is greater, so return -1.
//    - If they are equal, continue to the next revision by incrementing `i`.
// 6. If the loop completes without returning, it means all compared revisions were equal. In this case, the versions are identical, so return 0.

// Time Complexity: O(M + N), where M and N are the lengths of the version strings. The tokenization process iterates through each string once, and the comparison loop iterates up to max(num_revisions1, num_revisions2). In the worst case, the number of revisions is proportional to the string length.
// Space Complexity: O(M + N) to store the tokens (revisions) in vectors.

class Solution {
public:
    // Helper function to split a string by a delimiter into tokens.
    vector<string> getTokens(string version) {
        stringstream v(version); // Create a stringstream from the version string.
        string token_v = "";
        vector<string> version_tokens; // Vector to store the revision tokens.
        // Use getline to extract tokens separated by '.'.
        while(getline(v, token_v, '.')) {
            version_tokens.push_back(token_v); // Add token to the vector.
        }
        return version_tokens;
    }

    int compareVersion(string version1, string version2) {
        // Tokenize both version strings.
        vector<string> v1 = getTokens(version1);
        vector<string> v2 = getTokens(version2);  
        
        int m = v1.size(); // Number of revisions in version1.
        int n = v2.size(); // Number of revisions in version2.
            
        int i = 0;
        // Loop until we have processed all revisions from both versions.
        while(i < m || i < n) {
            
            // Get the integer value of the current revision for version1, or 0 if it doesn't exist.
            int a = i < m ? stoi(v1[i]) : 0 ;
            // Get the integer value for version2, or 0 if it doesn't exist.
            int b = i < n ? stoi(v2[i])  : 0 ;
            
            // Compare the revision numbers.
            if(a > b)
                return 1; // version1 is greater.
            else if(b > a)
                return -1; // version2 is greater.
            else
                i++; // Revisions are equal, move to the next.
        }
        return 0; // Both versions are equal.
    }
};

/*
*
* Dry Run
*
* Example: version1 = "1.2", version2 = "1.10"
*
* 1. getTokens("1.2") -> v1 = {"1", "2"} -> m = 2
* 2. getTokens("1.10") -> v2 = {"1", "10"} -> n = 2
*
* 3. Start while loop (i < 2 || i < 2):
* - i = 0:
* - a = stoi(v1[0]) = stoi("1") = 1
* - b = stoi(v2[0]) = stoi("1") = 1
* - a == b (1 == 1), so increment i to 1.
*
* - i = 1:
* - a = stoi(v1[1]) = stoi("2") = 2
* - b = stoi(v2[1]) = stoi("10") = 10
* - b > a (10 > 2), so return -1.
*
* Final Output: -1
*/
```

### Java Solution

```java
// Intuition:
// The problem is to compare two version strings by breaking them into parts (revisions) and comparing these parts numerically from left to right. This suggests a parsing and iterative comparison approach.

// Approach:
// 1. A helper function `getTokens` is defined to simplify parsing. It takes a version string and uses the built-in `split("\\.")` method to divide the string into an array of revision strings based on the dot delimiter. The result is returned as a List of strings.
// 2. The main `compareVersion` function calls `getTokens` on both input strings `version1` and `version2`.
// 3. It then initializes an index `i` to 0 and enters a `while` loop that continues as long as `i` is less than the number of revisions in either version string. This ensures all parts of the longer version string are considered.
// 4. Inside the loop, it safely retrieves the integer value for the current revision `i` from both lists.
//    - It uses a ternary operator: if `i` is a valid index for the list, it parses the string at that index to an integer. If `i` is out of bounds (meaning the version has no more revisions), it defaults to 0.
// 5. It compares the two integer values (`a` and `b`).
//    - If `a > b`, `version1` is greater, so it returns 1.
//    - If `b > a`, `version2` is greater, so it returns -1.
//    - If they are equal, it increments `i` to check the next pair of revisions.
// 6. If the loop finishes, it means all revisions were equal, so the function returns 0.

// Time Complexity: O(M + N), where M and N are the lengths of `version1` and `version2`. The `split` operation takes linear time, and the subsequent loop over the tokens also takes linear time relative to the number of revisions.
// Space Complexity: O(M + N) because the `split` method creates new arrays/lists to store the revision strings.

class Solution {
    public int compareVersion(String version1, String version2) {
        // Tokenize both version strings into lists of revisions.
        List<String> v1 = getTokens(version1);
        List<String> v2 = getTokens(version2);
        
        int m = v1.size(); // Number of revisions in version1.
        int n = v2.size(); // Number of revisions in version2.
        
        int i = 0;
        // Loop until all revisions from the longer version are checked.
        while (i < m || i < n) {
            // Get current revision number for version1, or 0 if not present.
            int a = i < m ? Integer.parseInt(v1.get(i)) : 0;
            // Get current revision number for version2, or 0 if not present.
            int b = i < n ? Integer.parseInt(v2.get(i)) : 0;
            
            // Perform comparison.
            if (a > b)
                return 1; // version1 is greater.
            else if (b > a)
                return -1; // version2 is greater.
            else
                i++; // Revisions are equal, advance to the next.
        }
        return 0; // Both versions are identical.
    }
    
    // Helper function to split the version string into tokens.
    private List<String> getTokens(String version) {
        // Use split with "\\." to split by the dot character.
        String[] tokens = version.split("\\.");
        List<String> versionTokens = new ArrayList<>();
        // Add all tokens to an ArrayList for easy access.
        for (String token : tokens) {
            versionTokens.add(token);
        }
        return versionTokens;
    }
}
/*
*
* Dry Run
*
* Example: version1 = "1.01", version2 = "1.001"
*
* 1. getTokens("1.01") -> v1 = ["1", "01"] -> m = 2
* 2. getTokens("1.001") -> v2 = ["1", "001"] -> n = 2
*
* 3. Start while loop (i < 2 || i < 2):
* - i = 0:
* - a = Integer.parseInt(v1.get(0)) = Integer.parseInt("1") = 1
* - b = Integer.parseInt(v2.get(0)) = Integer.parseInt("1") = 1
* - a == b (1 == 1), so increment i to 1.
*
* - i = 1:
* - a = Integer.parseInt(v1.get(1)) = Integer.parseInt("01") = 1
* - b = Integer.parseInt(v2.get(1)) = Integer.parseInt("001") = 1
* - a == b (1 == 1), so increment i to 2.
*
* 4. Loop condition `i < 2 || i < 2` (i.e., `2 < 2 || 2 < 2`) is now false. The loop terminates.
*
* 5. Return 0.
*
* Final Output: 0
*/
```

---

## 🔑 Key Insights

-   **Tokenization is Key**: The core of this problem is parsing the string. Using built-in tools like C++ `stringstream` or Java's `String.split()` simplifies the logic significantly compared to manual parsing.
-   **Implicit Zeros**: The rule to treat missing revisions as zero is crucial. A single loop that iterates up to the maximum number of revisions and uses a default value of `0` for out-of-bounds access is an elegant way to handle this.
-   **Leading Zeros Handled by Conversion**: The requirement to ignore leading zeros (e.g., treating `"01"` as `1`) is automatically handled by standard string-to-integer conversion functions (`stoi`, `Integer.parseInt`), which simplifies the code.

---

## 🔗 Further Exploration

-   **Without Built-in Split Functions**: How would you implement the tokenization logic manually, character by character? This could be a good exercise in string manipulation.
-   **Handling Alphanumeric Revisions**: How would you adapt the solution if revisions could contain letters (e.g., `"1.2.a"`, `"1.2.b"`)? This would require a more complex comparison logic than simple integer conversion.
-   **Performance Optimization**: For extremely long version strings, the space complexity of storing all tokens might be a concern. Could this problem be solved with O(1) extra space by parsing the strings on the fly? (Hint: Use two pointers for each string to find the next `.`.)

---

## 📚 References

-   [LeetCode Problem Link](https://leetcode.com/problems/compare-version-numbers/description/)
-   [C++ `stringstream`](https://cplusplus.com/reference/sstream/stringstream/)
-   [Java `String.split()`](https://docs.oracle.com/javase/8/docs/api/java/lang/String.html#split-java.lang.String-)

---

## 🏷️ Tags

`String`, `Two Pointers`

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/compare-version-numbers/description/) for original content and copyright.**

---

## 👨‍💻 Author

-   [imnilesh18](https://github.com/imnilesh18)