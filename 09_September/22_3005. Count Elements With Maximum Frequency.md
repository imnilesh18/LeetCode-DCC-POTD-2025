# ✨ 3005. Count Elements With Maximum Frequency

<div align="center">
    <img src="https://img.shields.io/badge/Difficulty-Easy-green?style=for-the-badge" alt="Difficulty: Easy" />
    <a href="https://leetcode.com/problems/count-elements-with-maximum-frequency/description/">
        <img src="https://img.shields.io/badge/View%20on%20LeetCode-000000?style=for-the-badge&logo=leetcode" alt="View on LeetCode" />
    </a>
</div>

---

## 📝 Problem Statement

You are given an array `nums` consisting of **positive** integers.

Return the **total frequencies** of elements in `nums` such that those elements all have the **maximum** frequency.

The **frequency** of an element is the number of occurrences of that element in the array.

---

## ⚙️ Constraints

- `1 <= nums.length <= 100`
- `1 <= nums[i] <= 100`

---

## 🧪 Examples

<div align="center">

| Input                  | Output | Explanation                                                                                                                            |
| :--------------------- | :----- | :------------------------------------------------------------------------------------------------------------------------------------- |
| `nums = [1,2,2,3,1,4]` | `4`    | The elements 1 and 2 both have a frequency of 2, which is the maximum. The total count is their frequencies added together: 2 + 2 = 4. |
| `nums = [1,2,3,4,5]`   | `5`    | All elements have a frequency of 1, which is the maximum. The total count is 1 + 1 + 1 + 1 + 1 = 5.                                    |

</div>

---

## 🧠 Approach

The core of the problem is to identify elements that appear most frequently and then sum up their counts.

1.  **Frequency Counting**: First, we need to count how many times each number appears in the input array. Since the numbers are constrained between 1 and 100, we can use a simple array (or a hash map) to store these frequencies.
2.  **Find Maximum Frequency**: While or after counting, we need to determine the highest frequency any element has. Let's call this `maxFreq`.
3.  **Calculate Total Frequencies**: Finally, we iterate through our frequency map/array. For every element whose frequency equals `maxFreq`, we add its frequency to a running total. This total sum is our final answer.

This can be implemented in two main ways:

- **Two-Pass Approach**:

  1.  First Pass: Iterate through `nums` to populate a frequency array and simultaneously find the `maxFreq`.
  2.  Second Pass: Iterate through the frequency array to count how many elements have a frequency equal to `maxFreq`. The result is this count multiplied by `maxFreq`.

- **One-Pass Approach**:
  1.  Iterate through `nums` once. Maintain the `maxFreq` seen so far and a `total` sum.
  2.  When a number's frequency increases:
      - If its new frequency is **greater than** the current `maxFreq`, we've found a new most frequent element. We reset our `total` to this new frequency and update `maxFreq`.
      - If its new frequency is **equal to** the current `maxFreq`, we've found another element that is also maximally frequent. We add its frequency (`maxFreq`) to our `total`.

The one-pass approach is slightly more efficient as it avoids a second iteration.

---

## 💻 Solution Code

### Method 1: Two-Pass Approach

```cpp
// Intuition:
// The problem asks for the sum of frequencies of all elements that have the highest frequency.
// A straightforward way to solve this is to first find the frequency of all elements, determine the maximum frequency,
// and then sum up the frequencies of all elements that match this maximum frequency.

// Approach:
// 1. Create a frequency array `arr` of size 101 (since numbers are from 1 to 100) to store counts.
// 2. Iterate through the input `nums` array. For each number, increment its corresponding count in `arr`.
// 3. During this iteration, also keep track of the maximum frequency (`maxFreq`) encountered so far.
// 4. After the first pass, `maxFreq` will hold the highest frequency of any element.
// 5. Use the `std::count` algorithm to find how many elements in the `arr` have a frequency equal to `maxFreq`.
// 6. The final result is the number of such elements multiplied by `maxFreq`.

// Time Complexity: O(N)
// We iterate through the `nums` array once (size N), which is O(N). The `count` function iterates through the frequency array, which has a constant size of 101 (O(1)). Thus, the total complexity is dominated by the initial iteration, making it O(N).

// Space Complexity: O(1)
// We use a frequency array `arr` of a fixed size (101), which does not depend on the input size N. Therefore, the space complexity is constant, O(1).

class Solution {
public:
    int maxFrequencyElements(vector<int>& nums) {
        // Frequency array for numbers 1-100.
        vector<int> arr(101);

        // Variable to store the maximum frequency found.
        int maxFreq = 0;

        // First pass: count frequencies and find the max frequency.
        for(int &num : nums) {
            // Increment the count for the current number.
            arr[num]++;
            // Update maxFreq if the current number's frequency is higher.
            maxFreq = max(maxFreq, arr[num]);
        }

        // Calculate the result:
        // Count how many elements have the max frequency and multiply by the max frequency itself.
        return count(arr.begin(), arr.end(), maxFreq) * maxFreq;
    }
};

/*
*
* Dry Run
*
* Input: nums = [1, 2, 2, 3, 1, 4]
*
* 1. Initialize `arr` of size 101 with all zeros, `maxFreq = 0`.
*
* 2. Loop through `nums`:
* - num = 1: arr[1] becomes 1. maxFreq = max(0, 1) -> 1.
* - num = 2: arr[2] becomes 1. maxFreq = max(1, 1) -> 1.
* - num = 2: arr[2] becomes 2. maxFreq = max(1, 2) -> 2.
* - num = 3: arr[3] becomes 1. maxFreq = max(2, 1) -> 2.
* - num = 1: arr[1] becomes 2. maxFreq = max(2, 2) -> 2.
* - num = 4: arr[4] becomes 1. maxFreq = max(2, 1) -> 2.
*
* 3. After the loop, `maxFreq` is 2.
* The frequency array `arr` has: arr[1]=2, arr[2]=2, arr[3]=1, arr[4]=1.
*
* 4. `count(arr.begin(), arr.end(), 2)`:
* This counts occurrences of the value 2 in `arr`. It finds it at index 1 and 2. So, the count is 2.
*
* 5. `return count * maxFreq;` -> `return 2 * 2;` -> `return 4;`
*
*/
```

### Method 2: One-Pass Approach

```cpp
// Intuition:
// We can optimize the two-pass approach into a single pass. By tracking the maximum frequency and the total count on the fly,
// we can avoid a second iteration. The key is to update the total sum dynamically whenever we find a new maximum frequency or another element that matches the current maximum.

// Approach:
// 1. Initialize a frequency array `arr` of size 101.
// 2. Initialize `maxFreq = 0` to track the maximum frequency and `total = 0` for the result.
// 3. Iterate through `nums` once. For each number:
//    a. Increment its frequency in `arr`.
//    b. Let the new frequency be `freq`.
//    c. If `freq > maxFreq`:
//       - We have a new highest frequency.
//       - Update `maxFreq = freq`.
//       - Reset `total` to `freq`, as this is now the only element contributing to the sum.
//    d. Else if `freq == maxFreq`:
//       - We found another element with the same maximum frequency.
//       - Add its frequency (`freq`) to the `total`.
// 4. After the loop, `total` will hold the final sum.

// Time Complexity: O(N)
// We iterate through the input `nums` array only once. All operations inside the loop are constant time.

// Space Complexity: O(1)
// We use a frequency array `arr` of a fixed size (101), making the space usage constant.

class Solution {
public:
    int maxFrequencyElements(vector<int>& nums) {
        // Frequency array for numbers 1-100.
        vector<int> arr(101);

        // To track the running max frequency.
        int maxFreq = 0;
        // To store the final result.
        int total   = 0;

        // Single pass through the numbers.
        for(int &num : nums) {
            // Increment the frequency of the current number.
            arr[num]++;

            // Get the updated frequency.
            int freq = arr[num];

            // Case 1: Found a new maximum frequency.
            if(freq > maxFreq) {
                // Update the max frequency.
                maxFreq = freq;
                // Reset the total, as previous elements are no longer max.
                total   = freq;
            // Case 2: Found another element with the same max frequency.
            } else if(freq == maxFreq) {
                // Add this element's frequency to the total.
                total += freq;
            }

        }

        // Return the accumulated total.
        return total;
    }
};

/*
*
* Dry Run
*
* Input: nums = [1, 2, 2, 3, 1, 4]
*
* 1. Initialize `arr` with zeros, `maxFreq = 0`, `total = 0`.
*
* 2. Loop through `nums`:
* - num = 1: arr[1]=1. freq=1. `freq > maxFreq` (1>0). Set `maxFreq=1`, `total=1`.
* - num = 2: arr[2]=1. freq=1. `freq == maxFreq` (1==1). `total += 1` -> total=2.
* - num = 2: arr[2]=2. freq=2. `freq > maxFreq` (2>1). Set `maxFreq=2`, `total=2`.
* - num = 3: arr[3]=1. freq=1. `freq < maxFreq` (1<2). No change.
* - num = 1: arr[1]=2. freq=2. `freq == maxFreq` (2==2). `total += 2` -> total=4.
* - num = 4: arr[4]=1. freq=1. `freq < maxFreq` (1<2). No change.
*
* 3. Loop ends.
*
* 4. `return total;` -> `return 4;`
*
*/
```

---

## 💡 Key Insights

- **Constraint-Driven Optimization**: The small constraint (`1 <= nums[i] <= 100`) is a huge hint. It allows us to use a simple fixed-size array for frequency counting instead of a more complex hash map, which is slightly more efficient in terms of constant factors and memory overhead.
- **Single-Pass Logic**: The transition from a two-pass to a one-pass solution is a common optimization pattern. By maintaining state (`maxFreq` and `total`) and updating it intelligently within a single loop, we can reduce redundant iterations. When the current element's frequency becomes the new maximum, we effectively "reset" our count. When it ties the maximum, we "add" to our group of maximum-frequency elements.

---

## 🚀 Further Exploration

- What if the numbers in `nums` were not limited to 100? How would the solution change? (Hint: Use a `std::unordered_map<int, int>` instead of a vector).
- What if you needed to return the elements themselves that have the maximum frequency, not their total count?
- Can you solve this problem if the input is a stream of numbers, and you cannot store all of them? (This would require a different approach, possibly using frequency estimation algorithms if memory is highly constrained).

---

## 📚 References

- [LeetCode Problem Link](https://leetcode.com/problems/count-elements-with-maximum-frequency/description/)
- [C++ `std::count`](https://en.cppreference.com/w/cpp/algorithm/count)

---

## 🏷️ Tags

<div>
  <a href="https://leetcode.com/tag/array/">
    <img src="https://img.shields.io/badge/Array-2081C6?style=for-the-badge" />
  </a>
  <a href="https://leetcode.com/tag/hash-table/">
    <img src="https://img.shields.io/badge/Hash%20Table-2081C6?style=for-the-badge" />
  </a>
  <a href="https://leetcode.com/tag/counting/">
    <img src="https://img.shields.io/badge/Counting-2081C6?style=for-the-badge" />
  </a>
</div>

---

## 📄 License

This repository is released under the [MIT License](https://www.google.com/search?q=./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/count-elements-with-maximum-frequency/description/) for original content and copyright.**

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)

<!-- end list -->
