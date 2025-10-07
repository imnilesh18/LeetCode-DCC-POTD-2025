# 🌊 1488. Avoid Flood in The City

| [Medium] |
| :---: |

[![C++](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)](https://isocpp.org/)
[![Data Structures](https://img.shields.io/badge/Data%20Structures-Map,%20Set-orange.svg)](https://en.cppreference.com/w/cpp/container)
[![Algorithms](https://img.shields.io/badge/Algorithms-Greedy,%20Binary%20Search-yellow.svg)](https://en.wikipedia.org/wiki/Greedy_algorithm)

## 🔗 Problem Link

[https://leetcode.com/problems/avoid-flood-in-the-city/](https://leetcode.com/problems/avoid-flood-in-the-city/)

---

## 📝 Problem Statement

Your country has an infinite number of lakes. Initially, all lakes are empty, but when it rains over the nth lake, the nth lake becomes full of water. If it rains over a lake that is already full, there will be a flood. Your goal is to avoid floods in any lake.

Given an integer array `rains` where:

- `rains[i] > 0` means there will be rain over the `rains[i]` lake.
- `rains[i] == 0` means there are no rains this day, and you can choose one lake to dry.

Return an array `ans` where:
- `ans.length == rains.length`
- `ans[i] == -1` if `rains[i] > 0`.
- `ans[i]` is the lake you choose to dry on the `i-th` day if `rains[i] == 0`.

If there are multiple valid answers, return any of them. If it is impossible to avoid a flood, return an empty array.

---

## ⛓️ Constraints

- `1 <= rains.length <= 10^5`
- `0 <= rains[i] <= 10^9`

---

##  উদাহরণ Examples

| Input | Output | Explanation |
| :--- | :--- | :--- |
| `rains = [1,2,3,4]` | `[-1,-1,-1,-1]` | No dry days are available, and no floods occur. |
| `rains = [1,2,0,0,2,1]` | `[-1,-1,2,1,-1,-1]` | On day 2, we dry lake 2. On day 3, we dry lake 1. This prevents floods on days 4 and 5. |
| `rains = [1,2,0,1,2]` | `[]` | After day 1, lakes {1, 2} are full. On day 2, we can only dry one. On day 3 or 4, the other will flood. |

---

## 🧠 Approach

The problem asks us to decide which lake to dry on days with no rain to prevent future floods. A greedy approach is the most intuitive way to solve this.

The core challenge arises when it rains on a lake that is already full. To prevent a flood, we must have used a previous dry day to empty that lake. The crucial decision is: *which* dry day should we use?

To maximize our chances of preventing future floods, we should be efficient with our dry days. When we need to dry a lake, it's always optimal to use the **earliest available dry day that occurred after the lake was last filled**. This greedy choice leaves later dry days free for more recent rainfalls, giving us maximum flexibility.

We can implement this with the following data structures:
1.  An `unordered_map` to track the last day a specific lake became full (`lake -> day`).
2.  A `set` to store the indices of all available dry days. A `set` is ideal because it keeps the days sorted and allows for efficient searching using `lower_bound`.

**Algorithm:**
1.  Initialize an answer array `ans`, a map `last_rain_day`, and a set `dry_days`.
2.  Iterate through the `rains` array day by day.
3.  If `rains[day]` is `0`, it's a dry day. Add the `day` to `dry_days`. We can set `ans[day] = 1` as a default, which might be overwritten later.
4.  If `rains[day]` is greater than `0`, it's a rainy day on a specific `lake`.
    -   Set `ans[day] = -1`.
    -   Check if the `lake` is already in our `last_rain_day` map.
        -   If yes, this lake is full. We must find a dry day between the last time it rained (`last_rain_day[lake]`) and the current `day`.
        -   Using `dry_days.lower_bound()`, we search for the first available dry day *after* `last_rain_day[lake]`.
        -   If `lower_bound` returns the end of the set, no suitable dry day exists. A flood is inevitable, so return an empty array.
        -   Otherwise, we've found the optimal dry day. We "use" it by setting `ans[*it] = lake` and removing it from `dry_days`.
    -   Update the map with the current day for this lake: `last_rain_day[lake] = day`.
5.  After iterating through all days, return the `ans` array.

This approach ensures that we always make the most short-sighted, optimal decision, which collectively leads to a globally valid solution if one exists.

---

## 💻 Solution Code

```cpp
// Intuition:
// The core idea is to be greedy. When it rains on a full lake, we must have dried it on a previous dry day.
// To give ourselves the best chance for future rains, we should use the *earliest possible* dry day that comes
// *after* the last time the lake was filled. This leaves later dry days available for more urgent situations.
// A `set` (or a sorted data structure) is perfect for finding the earliest available dry day.

// Approach:
// 1. Iterate through the `rains` array day by day.
// 2. Use a map `map` to store the last day a lake was filled (`lake -> day`).
// 3. Use a set `dryDays` to store the indices of available dry days (`rains[i] == 0`).
// 4. When `rains[i] > 0` (it's a rainy day):
//    - Mark `ans[i] = -1`.
//    - If this lake has been filled before (exists in the map), we must dry it.
//    - Find the smallest dry day index in `dryDays` that is *greater than* the last day the lake was filled.
//    - `lower_bound` on the set helps find this efficiently.
//    - If no such dry day exists, a flood is inevitable, so return {}.
//    - If found, use it: set `ans[dry_day_index] = lake` and remove it from `dryDays`.
//    - Update the map with the current day for this lake: `map[lake] = day`.
// 5. When `rains[i] == 0` (it's a dry day):
//    - Add the current day `i` to the `dryDays` set.
//    - We can set a default value like `ans[i] = 1`, which may be updated later.

// Time Complexity: O(n*log(n))
// The main loop runs 'n' times. Inside the loop, the dominant operation is `lower_bound` on the `dryDays` set,
// which takes O(log k) time, where 'k' is the number of dry days. In the worst case, k can be up to 'n'.
// Therefore, the total time complexity is O(n*log(n)).

// Space Complexity: O(n)
// The `map` and `dryDays` set can store up to 'n' elements in the worst-case scenario
// (e.g., all rains are on different lakes, or all days are dry days).

class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        int n = rains.size(); // Total number of days

        unordered_map<int, int> map; // Stores {lake_number -> last_day_it_rained}
        set<int> dryDays;            // Stores indices of available dry days
        vector<int> ans(n, 1);       // Initialize answer array, default dry day action is to dry lake 1

        for (int day = 0; day < n; day++) {
            int lake = rains[day]; // Get the lake for the current day

            if (lake == 0) {
                dryDays.insert(day); // It's a dry day, add its index to our set of available dry days
            } else {
                ans[day] = -1; // It's a rainy day, so we can't dry any lake. Mark with -1.

                if (map.count(lake)) { // Check if this lake has rained on before (is it full?)
                    // Lake is full, we must find a dry day to empty it
                    int last_rain_day = map[lake]; // Get the last day it rained on this lake
                    
                    // Find the first available dry day *after* the last rain day
                    auto it = dryDays.lower_bound(last_rain_day + 1);

                    if (it == dryDays.end()) {
                        // No available dry day found after the last rain event for this lake
                        // A flood is unavoidable.
                        return {};
                    }
                    
                    // We found a suitable dry day. Let's use it.
                    int dry_day_to_use = *it; // Get the index of the dry day
                    ans[dry_day_to_use] = lake; // On that dry day, we dry the current lake
                    dryDays.erase(it); // This dry day is now used, remove it from the set
                }

                map[lake] = day; // Update the last rain day for this lake to the current day
            }
        }
        return ans; // Return the schedule of drying actions
    }
};

/*
*
* Dry Run
* Example: rains = [1, 2, 0, 0, 2, 1]
*
* Initial state:
* n = 6
* map = {}
* dryDays = {}
* ans = [1, 1, 1, 1, 1, 1]
*
* day = 0, lake = 1:
* - ans[0] = -1
* - map does not contain 1.
* - map[1] = 0
* - State: map = {1:0}, dryDays = {}, ans = [-1, 1, 1, 1, 1, 1]
*
* day = 1, lake = 2:
* - ans[1] = -1
* - map does not contain 2.
* - map[2] = 1
* - State: map = {1:0, 2:1}, dryDays = {}, ans = [-1, -1, 1, 1, 1, 1]
*
* day = 2, lake = 0:
* - It's a dry day.
* - dryDays.insert(2)
* - State: map = {1:0, 2:1}, dryDays = {2}, ans = [-1, -1, 1, 1, 1, 1]
*
* day = 3, lake = 0:
* - It's a dry day.
* - dryDays.insert(3)
* - State: map = {1:0, 2:1}, dryDays = {2, 3}, ans = [-1, -1, 1, 1, 1, 1]
*
* day = 4, lake = 2:
* - ans[4] = -1
* - map contains 2. last_rain_day = map[2] = 1.
* - Find dry day in {2, 3} > 1. lower_bound(1+1) points to 2.
* - it = pointer to 2.
* - ans[2] = 2 (Use day 2 to dry lake 2).
* - dryDays.erase(2).
* - map[2] = 4
* - State: map = {1:0, 2:4}, dryDays = {3}, ans = [-1, -1, 2, 1, -1, 1]
*
* day = 5, lake = 1:
* - ans[5] = -1
* - map contains 1. last_rain_day = map[1] = 0.
* - Find dry day in {3} > 0. lower_bound(0+1) points to 3.
* - it = pointer to 3.
* - ans[3] = 1 (Use day 3 to dry lake 1).
* - dryDays.erase(3).
* - map[1] = 5
* - State: map = {1:5, 2:4}, dryDays = {}, ans = [-1, -1, 2, 1, -1, -1]
*
* Final Result: [-1, -1, 2, 1, -1, -1]
*
*/
```

---

## 💡 Key Insights

- **Greedy Choice**: The heart of the solution lies in the greedy decision to always use the earliest possible dry day after a lake has been filled. This preserves later dry days for future needs, which is a more flexible and robust strategy.
- **Data Structure Choice**: Using a `set` for `dryDays` is crucial. It automatically keeps the available dry days sorted, making the `lower_bound` operation (which is effectively a binary search) very efficient (O(log N)). This is much faster than searching through a vector or list.
- **Handling Impossibility**: The condition `it == dryDays.end()` elegantly captures the scenario where a flood is unavoidable. If we need to dry a lake but there are no available dry days between its last rain and the current one, no solution is possible.

---

## 🚀 Further Exploration

- **What if we could dry multiple lakes on a dry day?** How would the strategy change if `rains[i] == 0` allowed you to dry `k` lakes?
- **Cost to Dry**: What if drying certain lakes had different costs, and we had a budget for drying? This would turn the problem into a more complex optimization problem, possibly requiring dynamic programming or more advanced graph algorithms.
- **Varying Rain Amounts**: What if lakes had a capacity, and rain filled them partially? The problem would then involve tracking the water level of each lake.

---

## 📚 References

- [std::set::lower_bound](https://en.cppreference.com/w/cpp/container/set/lower_bound)
- [Greedy Algorithms](https://en.wikipedia.org/wiki/Greedy_algorithm)

---

## 🏷️ Tags

`Array`, `Greedy`, `Binary Search`, `Hash Table`, `Set`

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/avoid-flood-in-the-city/) for original content and copyright.**

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)