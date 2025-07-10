/*
 * 3440. Reschedule Meetings for Maximum Free Time II
 *
 * Medium
 *
 * You are given an integer eventTime denoting the duration of an event. You are also given two integer arrays startTime and endTime, each of length n.
 * These represent the start and end times of n non-overlapping meetings that occur during the event between time t = 0 and time t = eventTime, where the ith meeting occurs during the time [startTime[i], endTime[i]].
 * You can reschedule at most one meeting by moving its start time while maintaining the same duration, such that the meetings remain non-overlapping, to maximize the longest continuous period of free time during the event.
 * Return the maximum amount of free time possible after rearranging the meetings.
 * Note that the meetings can not be rescheduled to a time outside the event and they should remain non-overlapping.
 * Note: In this version, it is valid for the relative ordering of the meetings to change after rescheduling one meeting.
 *
 * Example 1:
 * Input: eventTime = 5, startTime = [1,3], endTime = [2,5]
 * Output: 2
 * Explanation:
 * Reschedule the meeting at [1, 2] to [2, 3], leaving no meetings during the time [0, 2].
 *
 * Example 2:
 * Input: eventTime = 10, startTime = [0,7,9], endTime = [1,8,10]
 * Output: 7
 * Explanation:
 * Reschedule the meeting at [0, 1] to [8, 9], leaving no meetings during the time [0, 7].
 *
 * Example 3:
 * Input: eventTime = 10, startTime = [0,3,7,9], endTime = [1,4,8,10]
 * Output: 6
 * Explanation:
 * Reschedule the meeting at [3, 4] to [8, 9], leaving no meetings during the time [1, 7].
 *
 * Example 4:
 * Input: eventTime = 5, startTime = [0,1,2,3,4], endTime = [1,2,3,4,5]
 * Output: 0
 * Explanation:
 * There is no time during the event not occupied by meetings.
 *
 * Constraints:
 * 1 <= eventTime <= 10^9
 * n == startTime.length == endTime.length
 * 2 <= n <= 10^5
 * 0 <= startTime[i] < endTime[i] <= eventTime
 * endTime[i] <= startTime[i + 1] where i lies in the range [0, n - 2].
 */

// Approach: Greedy – compute all free gaps, then for each meeting consider removing it and merging adjacent gaps using prefix/suffix max arrays to maximize free time.
// Time Complexity: O(n) – we build arrays and scan through them linearly.
// Space Complexity: O(n) – we store freeArray, maxLeftFree, and maxRightFree arrays of size O(n).

class Solution {
public:
    int maxFreeTime(int eventTime, vector<int>& startTime, vector<int>& endTime) {
        int nMeetings = startTime.size();
        // freeArray[i] = duration of free gap before meeting i (0 ≤ i ≤ n)
        // index 0: before first meeting; index n: after last meeting
        vector<int> freeArray;

        freeArray.reserve(nMeetings + 1);

        // gap before first meeting
        freeArray.push_back(startTime[0]);

        // gaps between consecutive meetings
        for (int i = 1; i < nMeetings; ++i) {
            freeArray.push_back(startTime[i] - endTime[i - 1]);
        }

        // gap after last meeting
        freeArray.push_back(eventTime - endTime[nMeetings - 1]);

        int n = freeArray.size();  // n = nMeetings + 1

        // maxRightFree[i] = maximum free gap to the right of index i (excluding i)
        vector<int> maxRightFree(n, 0);
        for (int i = n - 2; i >= 0; --i) {
            maxRightFree[i] = max(maxRightFree[i + 1], freeArray[i + 1]);
        }

        // maxLeftFree[i] = maximum free gap to the left of index i (excluding i)
        vector<int> maxLeftFree(n, 0);
        for (int i = 1; i < n; ++i) {
            maxLeftFree[i] = max(maxLeftFree[i - 1], freeArray[i - 1]);
        }

        int result = 0;
        // Try removing (rescheduling) each meeting one by one
        for (int i = 1; i < n; ++i) {
            // duration of the (i-1)-th meeting
            int dur = endTime[i - 1] - startTime[i - 1];

            // Case 1: remove meeting completely into the largest gap elsewhere
            // We can merge its duration into the larger of left or right max gaps,
            // but the free time created at its original position is freeArray[i-1] + freeArray[i]
            // If dur <= one of those large gaps, we can slot it there and merge the original two gaps plus dur.
            int bestOutside = max(maxLeftFree[i - 1], maxRightFree[i]);
            if (dur <= bestOutside) {
                result = max(result, freeArray[i - 1] + dur + freeArray[i]);
            }

            // Case 2: simply remove it and keep the two adjacent gaps merged
            result = max(result, freeArray[i - 1] + freeArray[i]);
        }

        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Input: eventTime = 5, startTime = [1,3], endTime = [2,5]
 *
 * 1. Compute freeArray:
 *    freeArray[0] = startTime[0] = 1
 *    freeArray[1] = startTime[1] - endTime[0] = 3 - 2 = 1
 *    freeArray[2] = eventTime - endTime[1] = 5 - 5 = 0
 *    => freeArray = [1, 1, 0]
 *
 * 2. Build maxRightFree:
 *    maxRightFree[2] = 0
 *    maxRightFree[1] = max(0, freeArray[2]) = 0
 *    maxRightFree[0] = max(0, freeArray[1]) = 1
 *    => maxRightFree = [1, 0, 0]
 *
 * 3. Build maxLeftFree:
 *    maxLeftFree[0] = 0
 *    maxLeftFree[1] = max(0, freeArray[0]) = 1
 *    maxLeftFree[2] = max(1, freeArray[1]) = 1
 *    => maxLeftFree = [0, 1, 1]
 *
 * 4. Iterate i = 1..2:
 *    i = 1:
 *      dur = endTime[0] - startTime[0] = 2 - 1 = 1
 *      bestOutside = max(maxLeftFree[0], maxRightFree[1]) = max(0, 0) = 0
 *      dur > bestOutside, so skip Case 1.
 *      Case 2: freeArray[0] + freeArray[1] = 1 + 1 = 2 => result = 2
 *
 *    i = 2:
 *      dur = endTime[1] - startTime[1] = 5 - 3 = 2
 *      bestOutside = max(maxLeftFree[1], maxRightFree[2]) = max(1, 0) = 1
 *      dur > bestOutside, skip Case 1.
 *      Case 2: freeArray[1] + freeArray[2] = 1 + 0 = 1 => result remains 2
 *
 * Final result = 2
 *
 */
