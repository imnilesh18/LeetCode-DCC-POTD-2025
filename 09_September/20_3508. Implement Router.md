# 🚀 3508. Implement Router

---

### <p align="center">Difficulty: <strong style="color: orange;">Medium</strong></p>

### <p align="center"><a href="https://leetcode.com/problems/implement-router/description/" target="_blank">🔗 Problem Link</a></p>

---

## 📝 Problem Statement

Design a data structure that can efficiently manage data packets in a network router. Each data packet consists of the following attributes:

- `source`: A unique identifier for the machine that generated the packet.
- `destination`: A unique identifier for the target machine.
- `timestamp`: The time at which the packet arrived at the router.

Implement the `Router` class:

- `Router(int memoryLimit)`: Initializes the Router object with a fixed `memoryLimit`. This is the maximum number of packets the router can store. If adding a new packet would exceed this limit, the **oldest** packet must be removed.
- `bool addPacket(int source, int destination, int timestamp)`: Adds a packet. Returns `true` if the packet is successfully added (i.e., not a duplicate), otherwise returns `false`. A packet is a duplicate if another packet with the same `source`, `destination`, and `timestamp` already exists.
- `int[] forwardPacket()`: Forwards the next packet in FIFO (First-In, First-Out) order, removing it from storage. Returns `[source, destination, timestamp]` or an empty array if no packets are available.
- `int getCount(int destination, int startTime, int endTime)`: Returns the number of stored packets with the specified `destination` and a `timestamp` within the inclusive range `[startTime, endTime]`.

**Note:** Queries for `addPacket` will be made in increasing order of `timestamp`.

---

## Constraints

- `2 <= memoryLimit <= 10^5`
- `1 <= source, destination <= 2 * 10^5`
- `1 <= timestamp <= 10^9`
- `1 <= startTime <= endTime <= 10^9`
- At most `10^5` calls will be made to `addPacket`, `forwardPacket`, and `getCount` combined.

---

## 🧪 Examples

<details>
<summary><strong>Example 1</strong></summary>

| Method          | Arguments       | Output       | Explanation                                          |
| --------------- | --------------- | ------------ | ---------------------------------------------------- |
| `Router`        | `[3]`           | `null`       | Initialize Router with `memoryLimit` of 3.           |
| `addPacket`     | `[1, 4, 90]`    | `true`       | Packet added.                                        |
| `addPacket`     | `[2, 5, 90]`    | `true`       | Packet added.                                        |
| `addPacket`     | `[1, 4, 90]`    | `false`      | Duplicate packet.                                    |
| `addPacket`     | `[3, 5, 95]`    | `true`       | Packet added.                                        |
| `addPacket`     | `[4, 5, 105]`   | `true`       | Packet added, oldest packet `[1, 4, 90]` is removed. |
| `forwardPacket` | `[]`            | `[2, 5, 90]` | Forwards and removes the next packet.                |
| `addPacket`     | `[5, 2, 110]`   | `true`       | Packet added.                                        |
| `getCount`      | `[5, 100, 110]` | `1`          | Only packet `[4, 5, 105]` matches the criteria.      |

</details>

<details>
<summary><strong>Example 2</strong></summary>

| Method          | Arguments    | Output       | Explanation                                |
| --------------- | ------------ | ------------ | ------------------------------------------ |
| `Router`        | `[2]`        | `null`       | Initialize Router with `memoryLimit` of 2. |
| `addPacket`     | `[7, 4, 90]` | `true`       | Packet added.                              |
| `forwardPacket` | `[]`         | `[7, 4, 90]` | Forwards the packet.                       |
| `forwardPacket` | `[]`         | `[]`         | No packets left, returns an empty array.   |

</details>

---

## 💡 Approach

To design this router efficiently, we need to select data structures that optimize each operation:

1.  **`addPacket` & `forwardPacket` (FIFO Order)**: A **`std::queue`** is the natural choice for maintaining the First-In, First-Out order of packets. It provides O(1) for push and pop operations.
2.  **Duplicate Check & Packet Storage**: To quickly check for duplicates and retrieve packet data, an **`std::unordered_map<string, vector<int>>`** is ideal. We can create a unique string key from the packet's `source`, `destination`, and `timestamp`. This gives us O(1) average time complexity for lookups, insertions, and deletions.
3.  **`getCount` (Range Query)**: This is the most challenging part. We need to count packets for a specific destination within a time range. A simple iteration over all packets would be too slow (O(N)). Since the timestamps for incoming packets are always increasing, if we store timestamps for each destination in a separate sorted list (a `vector`), we can perform a **binary search** (`std::lower_bound` and `std::upper_bound`) to find the number of packets in the given time range. This reduces the complexity to O(log k), where k is the number of packets for that specific destination.

Therefore, the overall design combines three data structures:

- `queue<string>`: To track the FIFO order of packet keys.
- `unordered_map<string, vector<int>> packetStore`: To store packet details for fast access.
- `unordered_map<int, vector<int>> destTimestamps`: To store sorted timestamps for each destination, enabling fast range queries with binary search.

---

## 💻 Solution Code

```cpp
// Intuition: To handle the router's requirements efficiently, we need a combination of data structures. A queue ensures FIFO ordering for forwarding packets. A hash map (unordered_map) provides fast O(1) average time lookups for duplicate checks and packet data retrieval. For the getCount operation, which involves range queries on timestamps, storing sorted timestamps per destination in another map allows us to use binary search for O(log k) efficiency.

// Approach:
// 1. `packetStore` (unordered_map<string, vector<int>>): Stores packet details `[source, dest, timestamp]` using a unique string key generated from these three attributes. This is for quick O(1) access and duplicate checks.
// 2. `que` (queue<string>): Stores the unique keys of packets in the order they arrive to maintain the FIFO logic for `forwardPacket`.
// 3. `destTimestamps` (unordered_map<int, vector<int>>): Maps each destination to a vector of timestamps. Since packets arrive in increasing timestamp order, these vectors are naturally sorted, making them perfect for binary search.
// 4. `addPacket()`: Checks for duplicates in `packetStore`. If the router is full, it calls `forwardPacket()` to evict the oldest element. Then, it adds the new packet's info to all three data structures.
// 5. `forwardPacket()`: Removes the oldest packet key from the front of the `que`, erases the corresponding entries from `packetStore` and `destTimestamps`. The `erase` at the beginning of the vector is O(k) but is an acceptable trade-off.
// 6. `getCount()`: Finds the destination in `destTimestamps` and uses `lower_bound` and `upper_bound` (binary search) to count timestamps within the specified `[startTime, endTime]` range.

// Time Complexity:
// - addPacket(): O(k) worst-case due to `forwardPacket()` which can trigger a vector erase. `k` is the number of packets for a specific destination.
// - forwardPacket(): O(k) worst-case because erasing from the front of a vector is a linear operation.
// - getCount(): O(log k) per query due to binary search in the sorted timestamp vector.

// Space Complexity:
// O(MAX_SIZE) total, as each data structure will store information related to at most `MAX_SIZE` packets.
class Router {
private:
    int MAX_SIZE; // The maximum number of packets the router can store.
    unordered_map<string, vector<int>> packetStore; // Maps a unique key to packet details [source, dest, timestamp].
    unordered_map<int, vector<int>> destTimestamps; // Maps a destination to its sorted list of timestamps.
    queue<string> que; // Maintains the FIFO order of packets using their unique keys.

    // Helper function to create a unique string key for each packet.
    string makeKey(int source, int destination, int timestamp) {
        return to_string(source) + "#" + to_string(destination) + "#" + to_string(timestamp);
    }

public:
    // Constructor to initialize the router with a given memory limit.
    Router(int memoryLimit) {
        MAX_SIZE = memoryLimit;
    }

    // Adds a packet to the router.
    bool addPacket(int source, int destination, int timestamp) {
        string key = makeKey(source, destination, timestamp);

        // Check for duplicate packets.
        if (packetStore.find(key) != packetStore.end()) {
            return false; // Packet is a duplicate, do not add.
        }

        // If memory limit is reached, remove the oldest packet.
        if ((int)packetStore.size() >= MAX_SIZE) {
            forwardPacket(); // Evict the oldest packet.
        }

        // Store the packet information in all data structures.
        packetStore[key] = {source, destination, timestamp};
        que.push(key);
        destTimestamps[destination].push_back(timestamp);

        return true; // Packet successfully added.
    }

    // Forwards the oldest packet in the queue.
    vector<int> forwardPacket() {
        if (packetStore.empty())
            return {}; // Return empty array if no packets are available.

        // Get the key of the oldest packet from the front of the queue.
        string key = que.front();
        que.pop();

        // Retrieve packet details and remove it from the store.
        vector<int> packet = packetStore[key];
        packetStore.erase(key);

        // Remove the corresponding timestamp from the destination's list.
        int dest = packet[1];
        destTimestamps[dest].erase(destTimestamps[dest].begin()); // This is an O(k) operation.

        return packet; // Return the forwarded packet.
    }

    // Counts packets for a specific destination within a time range.
    int getCount(int destination, int startTime, int endTime) {
        auto it = destTimestamps.find(destination);
        // If destination not found or has no timestamps, return 0.
        if (it == destTimestamps.end() || it->second.empty())
            return 0;

        // Use binary search to find the range of timestamps.
        // `lower_bound` finds the first element not less than startTime.
        int i = lower_bound(begin(it->second), end(it->second), startTime) - begin(it->second);
        // `upper_bound` finds the first element greater than endTime.
        int j = upper_bound(begin(it->second), end(it->second), endTime) - begin(it->second);

        // The difference (j - i) gives the count of elements in the range.
        return j - i;
    }
};

/*
*
* Dry Run
*
* Let's trace Example 1: Router(3)
*
* 1. addPacket(1, 4, 90):
* - key = "1#4#90"
* - Not a duplicate. Size < 3.
* - packetStore["1#4#90"] = {1, 4, 90}
* - que.push("1#4#90") -> que: ["1#4#90"]
* - destTimestamps[4] = {90}
* - Returns: true
*
* 2. addPacket(2, 5, 90):
* - key = "2#5#90"
* - Not a duplicate. Size < 3.
* - packetStore["2#5#90"] = {2, 5, 90}
* - que.push("2#5#90") -> que: ["1#4#90", "2#5#90"]
* - destTimestamps[5] = {90}
* - Returns: true
*
* 3. addPacket(1, 4, 90):
* - key = "1#4#90"
* - Duplicate found in packetStore.
* - Returns: false
*
* 4. addPacket(3, 5, 95):
* - key = "3#5#95"
* - Not a duplicate. Size < 3.
* - packetStore["3#5#95"] = {3, 5, 95}
* - que.push("3#5#95") -> que: ["1#4#90", "2#5#90", "3#5#95"]
* - destTimestamps[5] = {90, 95}
* - Returns: true
*
* 5. addPacket(4, 5, 105):
* - key = "4#5#105"
* - Not a duplicate. Size is 3 (full).
* - Call forwardPacket():
* - Oldest key "1#4#90" is popped from queue.
* - packetStore["1#4#90"] is erased.
* - destTimestamps[4] = {} after erasing 90.
* - Now, add the new packet:
* - packetStore["4#5#105"] = {4, 5, 105}
* - que.push("4#5#105") -> que: ["2#5#90", "3#5#95", "4#5#105"]
* - destTimestamps[5] = {90, 95, 105}
* - Returns: true
*
* 6. forwardPacket():
* - key = "2#5#90" (from front of queue).
* - que becomes: ["3#5#95", "4#5#105"]
* - packetStore["2#5#90"] erased.
* - destTimestamps[5] becomes {95, 105} after erasing 90.
* - Returns: {2, 5, 90}
*
* 7. getCount(5, 100, 110):
* - Look at destTimestamps[5] which is {95, 105}.
* - lower_bound for 100 points to 105 (index 1).
* - upper_bound for 110 points past 105 (index 2).
* - Result is 2 - 1 = 1.
* - Returns: 1
*
*/
```

---

## 🔑 Key Insights

- **Choosing the Right Data Structures**: The efficiency of the solution hinges on selecting the right tools for each task. The problem's requirements (FIFO, fast lookup, and efficient range queries) naturally point to a combination of a queue, a hash map, and a map of sorted vectors.
- **Leveraging Constraints**: The constraint that `addPacket` calls are made in increasing order of `timestamp` is crucial. It guarantees that when we `push_back` a timestamp to our `destTimestamps` vectors, they remain sorted without needing an explicit sort operation, which is a significant performance gain.
- **Trade-offs**: The `forwardPacket` operation has a linear time complexity (`O(k)`) in the worst case because of `vector::erase` at the beginning. While not ideal, it's a reasonable trade-off given that `getCount` is optimized to logarithmic time, which is likely to be a more frequent or performance-critical operation in a real-world scenario.

---

## 🌐 Further Exploration

- **Alternative for `destTimestamps`**: Instead of a `vector`, a balanced binary search tree or a skip list could be used to store timestamps for each destination. This would make the removal of the oldest element an O(log k) operation, improving the worst-case time complexity of `forwardPacket` and `addPacket`. However, this would increase implementation complexity and might have higher constant overhead than the vector-based approach.
- **Memory Optimization**: The `makeKey` function creates strings, which can consume significant memory. For a highly optimized system, one could use a `std::tuple<int, int, int>` as the key in the hash map, provided a custom hash function is implemented.

---

## 🔗 References

- [std::queue](https://en.cppreference.com/w/cpp/container/queue)
- [std::unordered_map](https://en.cppreference.com/w/cpp/container/unordered_map)
- [std::lower_bound](https://en.cppreference.com/w/cpp/algorithm/lower_bound)
- [std::upper_bound](https://en.cppreference.com/w/cpp/algorithm/upper_bound)

---

## 🏷️ Tags

`Data Structure`, `Design`, `Hash Table`, `Queue`, `Binary Search`

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/implement-router/description/) for original content and copyright.**

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)
