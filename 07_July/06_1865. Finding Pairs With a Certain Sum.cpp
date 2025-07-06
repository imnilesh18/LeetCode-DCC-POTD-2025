/*
 * 1865. Finding Pairs With a Certain Sum
 *
 * Medium
 *
 * You are given two integer arrays nums1 and nums2. You are tasked to implement a data structure that supports queries of two types:
 * Add a positive integer to an element of a given index in the array nums2.
 * Count the number of pairs (i, j) such that nums1[i] + nums2[j] equals a given value (0 <= i < nums1.length and 0 <= j < nums2.length).
 * Implement the FindSumPairs class:
 * FindSumPairs(int[] nums1, int[] nums2) Initializes the FindSumPairs object with two integer arrays nums1 and nums2.
 * void add(int index, int val) Adds val to nums2[index], i.e., apply nums2[index] += val.
 * int count(int tot) Returns the number of pairs (i, j) such that nums1[i] + nums2[j] == tot.
 *
 * Example 1:
 * Input
 * ["FindSumPairs", "count", "add", "count", "count", "add", "add", "count"]
 * [[[1, 1, 2, 2, 2, 3], [1, 4, 5, 2, 5, 4]], [7], [3, 2], [8], [4], [0, 1], [1, 1], [7]]
 * Output
 * [null, 8, null, 2, 1, null, null, 11]
 * Explanation
 * FindSumPairs findSumPairs = new FindSumPairs([1, 1, 2, 2, 2, 3], [1, 4, 5, 2, 5, 4]);
 * findSumPairs.count(7);  // return 8; pairs (2,2), (3,2), (4,2), (2,4), (3,4), (4,4) make 2 + 5 and pairs (5,1), (5,5) make 3 + 4
 * findSumPairs.add(3, 2); // now nums2 = [1,4,5,4,5,4]
 * findSumPairs.count(8);  // return 2; pairs (5,2), (5,4) make 3 + 5
 * findSumPairs.count(4);  // return 1; pair (5,0) makes 3 + 1
 * findSumPairs.add(0, 1); // now nums2 = [2,4,5,4,5,4]
 * findSumPairs.add(1, 1); // now nums2 = [2,5,5,4,5,4]
 * findSumPairs.count(7);  // return 11; pairs (2,1), (2,2), (2,4), (3,1), (3,2), (3,4), (4,1), (4,2), (4,4) make 2 + 5 and pairs (5,3), (5,5) make 3 + 4
 *
 * Constraints:
 * 1 <= nums1.length <= 1000
 * 1 <= nums2.length <= 10^5
 * 1 <= nums1[i] <= 10^9
 * 1 <= nums2[i] <= 10^5
 * 0 <= index < nums2.length
 * 1 <= val <= 10^5
 * 1 <= tot <= 10^9
 * At most 1000 calls are made to add and count each.
 */

// Approach: Use a hash map to store frequencies of nums2 elements; on add, update map in O(1), and on count, for each x in nums1 add mp[tot - x] in O(n1)
// Time Complexity: add() is O(1), count() is O(n1) where n1 = nums1.size()
// Space Complexity: O(n2) for the hash map storing frequencies of nums2 values
class FindSumPairs {
public:
    vector<int> vec1;            // copy of nums1
    vector<int> vec2;            // copy of nums2
    unordered_map<int, int> mp;  // map from value to its frequency in nums2

    FindSumPairs(vector<int>& nums1, vector<int>& nums2) {
        vec1 = nums1;            // initialize nums1 copy
        vec2 = nums2;            // initialize nums2 copy
        for (int& x : vec2) {    // build frequency map for nums2
            mp[x]++;
        }
    }

    void add(int index, int val) {
        mp[vec2[index]]--;       // decrement count of the old value at nums2[index]
        vec2[index] += val;      // update nums2[index]
        mp[vec2[index]]++;       // increment count of the new value
    }
    
    int count(int tot) {
        int c = 0;

        for (int& x : vec1) {    // for each element in nums1
            c += mp[tot - x];    // add frequency of the complement in nums2
        }
        return c;
    }
};

/*
 *
 * Dry Run
 *
 * Initial:
 *   nums1 = [1,1,2,2,2,3]
 *   nums2 = [1,4,5,2,5,4]
 *   mp = {1:1, 4:2, 5:2, 2:1}
 *
 * Operation: count(7)
 *   For each x in nums1 compute tot-x:
 *     x=1 -> 6 (mp[6]=0)
 *     x=1 -> 6 (0)
 *     x=2 -> 5 (2)
 *     x=2 -> 5 (2)
 *     x=2 -> 5 (2)
 *     x=3 -> 4 (2)
 *   Sum = 0+0+2+2+2+2 = 8
 *
 * Operation: add(3,2)
 *   nums2[3]=2 -> 4
 *   mp: 2->0, 4->3
 *
 * Operation: count(8)
 *   Complements: 7,7,6,6,6,5 -> mp values 0+0+0+0+0+2 = 2
 *
 * Operation: count(4)
 *   Complements: 3,3,2,2,2,1 -> 0+0+0+0+0+1 = 1
 *
 * Operation: add(0,1)
 *   nums2[0]=1 -> 2
 *   mp: 1->0, 2->1
 *
 * Operation: add(1,1)
 *   nums2[1]=4 -> 5
 *   mp: 4->2, 5->3
 *
 * Operation: count(7)
 *   Complements: 6,6,5,5,5,4 -> 0+0+3+3+3+2 = 11
 *
 */
