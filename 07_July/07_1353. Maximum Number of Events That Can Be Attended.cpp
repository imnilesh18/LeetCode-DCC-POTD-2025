/*
 * 1353. Maximum Number of Events That Can Be Attended
 *
 * Medium
 *
 * You are given an array of events where events[i] = [startDayi, endDayi]. Every event i starts at startDayi and ends at endDayi.
 * You can attend an event i at any day d where startTimei <= d <= endTimei. You can only attend one event at any time d.
 * Return the maximum number of events you can attend.
 *
 * Example 1:
 * Input: events = [[1,2],[2,3],[3,4]]
 * Output: 3
 * Explanation: You can attend all the three events.
 * One way to attend them all is as shown.
 * Attend the first event on day 1.
 * Attend the second event on day 2.
 * Attend the third event on day 3.
 *
 * Example 2:
 * Input: events= [[1,2],[2,3],[3,4],[1,2]]
 * Output: 4
 *
 * Constraints:
 * 1 <= events.length <= 10^5
 * events[i].length == 2
 * 1 <= startDayi <= endDayi <= 10^5
 */

// Approach: Sort events by startDay, use a min-heap to track endDays, and greedily attend events ending earliest each day
// Time Complexity: O(n log n) – Sorting takes O(n log n), each event is pushed/popped from the heap once
// Space Complexity: O(n) – For storing events in the min-heap
class Solution {
public:
    int maxEvents(vector<vector<int> >& events) {
        int n = events.size();

        // Sort events by their start day
        sort(begin(events), end(events));

        // Min-heap to store event end days
        priority_queue<int, vector<int>, greater<int> > pq;

        int day   = events[0][0]; // Start from the first event's start day
        int i     = 0;            // Pointer to traverse through the events
        int count = 0;            // To keep count of how many events attended

        // Continue while there are events left or heap is not empty
        while (!pq.empty() || i < n) {
            // If heap is empty, move to the next available event's start day
            if (pq.empty()) {
                day = events[i][0];
            }

            // Add all events starting today to the heap (based on end day)
            while (i < n && events[i][0] == day) {
                pq.push(events[i][1]);
                i++;
            }

            // Attend the event that ends earliest (min end day)
            if (!pq.empty()) {
                pq.pop();    // Attend this event
                count++;     // Increase count of attended events
            }

            day++; // Move to the next day

            // Remove all events from heap that have already ended
            while (!pq.empty() && pq.top() < day) {
                pq.pop();
            }
        }

        return count;
    }
};

/*
 *
 * Dry Run
 *
 * Input: events = [[1,2],[2,3],[3,4],[1,2]]
 * After sorting: [[1,2],[1,2],[2,3],[3,4]]
 * i = 0, day = 1, count = 0
 *
 * Day 1:
 * - Add [1,2] → pq = [2]
 * - Add [1,2] → pq = [2,2]
 * - Attend event with end=2 → pq = [2], count = 1
 * - Increment day to 2
 * - Remove events with end < 2 → none removed
 *
 * Day 2:
 * - Add [2,3] → pq = [2,3]
 * - Attend event with end=2 → pq = [3], count = 2
 * - Increment day to 3
 * - Remove events with end < 3 → none removed
 *
 * Day 3:
 * - Add [3,4] → pq = [3,4]
 * - Attend event with end=3 → pq = [4], count = 3
 * - Increment day to 4
 * - Remove events with end < 4 → none removed
 *
 * Day 4:
 * - Attend event with end=4 → pq = [], count = 4
 * - Increment day to 5
 * - Loop ends as i = 4 (n = 4) and pq is empty
 *
 * Final Answer = 4
 */
