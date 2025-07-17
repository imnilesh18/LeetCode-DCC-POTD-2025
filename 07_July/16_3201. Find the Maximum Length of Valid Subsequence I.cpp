/*
 * 3201. Find the Maximum Length of Valid Subsequence I
 *
 * Medium
 *
 * You are given an integer array nums.
 * A subsequence sub of nums with length x is called valid if it satisfies:
 * (sub[0] + sub[1]) % 2 == (sub[1] + sub[2]) % 2 == ... == (sub[x - 2] + sub[x - 1]) % 2.
 * Return the length of the longest valid subsequence of nums.
 * A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
 *
 * Example 1:
 * Input: nums = [1,2,3,4]
 * Output: 4
 * Explanation:
 * The longest valid subsequence is [1, 2, 3, 4].
 *
 * Example 2:
 * Input: nums = [1,2,1,1,2,1,2]
 * Output: 6
 * Explanation:
 * The longest valid subsequence is [1, 2, 1, 2, 1, 2].
 *
 * Example 3:
 * Input: nums = [1,3]
 * Output: 2
 * Explanation:
 * The longest valid subsequence is [1, 3].
 *
 * Constraints:
 * 2 <= nums.length <= 2 * 10^5
 * 1 <= nums[i] <= 10^7
 */

// Approach 1: Count total evens and odds to handle uniform-parity subsequences, then compute the longest alternating-parity subsequence; the answer is the maximum of these three possibilities.
// Time Complexity: O(n) – one pass to count evens/odds and one pass to build the alternating-parity subsequence.
// Space Complexity: O(1) – uses only a fixed number of integer variables.
class Solution {
public:
    int maximumLength(vector<int>& nums) {
        int countEven = 0, countOdd = 0;

        // Count the number of even and odd elements in the array
        for (int num : nums) {
            if (num % 2 == 0) {
                countEven++;
            }else{
                countOdd++;
            }
        }

        // Build the longest subsequence where adjacent elements alternate in parity
        int altLen     = 1;                      // At least one element always forms a valid subsequence
        int prevParity = nums[0] % 2;            // Parity of the first element

        for (int i = 1; i < nums.size(); ++i) {
            int currParity = nums[i] % 2;       // Compute current element's parity
            if (currParity != prevParity) {     // If it alternates with the previous
                altLen++;                       // extend the alternating subsequence
                prevParity = currParity;        // update the reference parity
            }
        }

        // The answer is the max of: all-even subsequence, all-odd subsequence, or the alternating-parity subsequence
        return max({ countEven, countOdd, altLen });
    }
};

/*
 *
 * Dry Run
 *
 * Input: nums = [1, 2, 1, 1, 2, 1, 2]
 *
 * 1) Counting evens and odds:
 *    countEven = 0, countOdd = 0
 *    - num = 1 -> odd  => countOdd = 1
 *    - num = 2 -> even => countEven = 1
 *    - num = 1 -> odd  => countOdd = 2
 *    - num = 1 -> odd  => countOdd = 3
 *    - num = 2 -> even => countEven = 2
 *    - num = 1 -> odd  => countOdd = 4
 *    - num = 2 -> even => countEven = 3
 *    => countEven = 3, countOdd = 4
 *
 * 2) Building alternating-parity subsequence:
 *    altLen = 1
 *    prevParity = nums[0] % 2 = 1
 *
 *    i = 1: nums[1]=2  currParity=0 != prevParity(1) -> altLen=2, prevParity=0
 *    i = 2: nums[2]=1  currParity=1 != prevParity(0) -> altLen=3, prevParity=1
 *    i = 3: nums[3]=1  currParity=1 == prevParity(1) -> no change
 *    i = 4: nums[4]=2  currParity=0 != prevParity(1) -> altLen=4, prevParity=0
 *    i = 5: nums[5]=1  currParity=1 != prevParity(0) -> altLen=5, prevParity=1
 *    i = 6: nums[6]=2  currParity=0 != prevParity(1) -> altLen=6, prevParity=0
 *    => altLen = 6
 *
 * 3) Final result = max(countEven, countOdd, altLen) = max(3, 4, 6) = 6
 */

// Approach 2: Use a modified LIS (Longest Increasing Subsequence) recursion pattern to explore subsequences matching a fixed parity-sum mod; try both mod = 0 and mod = 1.
// Time Complexity: O(2^n) without memoization (exponential), O(n^2) with memoization but may cause MLE due to large constraints.
// Space Complexity: O(n^2) auxiliary stack space for recursion and memo table.
class Solution {
public:

    int LIS(vector<int>& nums, int i, int prev, int mod) {
        if (i >= nums.size()) {
            return 0;                              // Reached end of array
        }

        int take = 0, skip = 0;

        // Option to take nums[i] if it's the first element (prev == -1)
        // or if (nums[prev] + nums[i]) % 2 matches the required 'mod'
        if (prev == -1 || (nums[prev] + nums[i]) % 2 == mod) {
            take = 1 + LIS(nums, i + 1, i, mod);   // include nums[i] and recurse
        }

        // Option to skip nums[i] and recurse without changing 'prev'
        skip = LIS(nums, i + 1, prev, mod);

        // Return the best of taking or skipping
        return max(take, skip);
    }
    
    int maximumLength(vector<int>& nums) {
        int maxSubLength = 0;

        // Try subsequences where adjacent pairs sum to even (mod = 0)
        maxSubLength = max(maxSubLength, LIS(nums, 0, -1, 0));

        // Try subsequences where adjacent pairs sum to odd (mod = 1)
        maxSubLength = max(maxSubLength, LIS(nums, 0, -1, 1));

        return maxSubLength;
    }
};

/*
 *
 * Dry Run
 *
 * Input: nums = [1, 2, 1, 1]
 *
 * Call maximumLength:
 *   maxSubLength = max(LIS(nums,0,-1,0), LIS(nums,0,-1,1))
 *
 * 1) LIS(nums,0,-1,0)  // looking for pairs summing to even
 *    i=0, prev=-1:
 *      take = 1 + LIS(nums,1,0,0)
 *      skip = LIS(nums,1,-1,0)
 *
 *    a) take branch:
 *       LIS(nums,1,0,0): prev=0 (nums[0]=1)
 *         i=1: nums[1]=2, (1+2)%2=1 != mod(0) -> cannot take
 *         skip -> LIS(nums,2,0,0)
 *
 *         LIS(nums,2,0,0): nums[2]=1, (1+1)%2=0 == mod -> take=1+LIS(3,2,0), skip=LIS(3,0,0)
 *           take -> 1 + LIS(nums,3,2,0)
 *             nums[3]=1, (1+1)%2=0 -> take 1 + LIS(4,3,0)=1
 *             skip -> LIS(4,2,0)=0
 *             returns max(1+1,0)=2
 *           skip -> LIS(3,0,0):
 *             nums[3]=1, (1+1)%2=0 -> take=1+LIS(4,3,0)=1, skip=LIS(4,0,0)=0 -> returns 1
 *           returns max(2,1)=2
 *         returns 2
 *       so take branch gives 1 + 2 = 3
 *
 *    b) skip branch:
 *       LIS(nums,1,-1,0): prev=-1
 *         i=1: take=1+LIS(2,1,0), skip=LIS(2,-1,0)
 *         ... (similar exploration) ultimately yields <=3
 *
 *    LIS(nums,0,-1,0) returns 3
 *
 * 2) LIS(nums,0,-1,1)  // looking for pairs summing to odd
 *    Similar recursion finds the longest odd-mod subsequence, here also returns 3
 *
 * Final result = max(3, 3) = 3
 */

// Approach 3: Bottom-up DP like LIS—maintain two DP rows for mod0 (even-sum pairs) and mod1 (odd-sum pairs), extending valid subsequences at each index.
// Time Complexity: O(n^2) — two nested loops over array of size n, which may TLE for large inputs.
// Space Complexity: O(n) — uses two arrays (2 × n) for DP.
class Solution {
public:
    int maximumLength(vector<int>& nums) {
        // Using the same LIS bottom-up structure but keyed by parity-sum mod
        int n = nums.size();

        // Alternative single-row definitions (commented out):
        // vector<int> dp0(n, 1); // dp0[i] = longest subsequence ending at i with (prev + nums[i])%2 == 0
        // vector<int> dp1(n, 1); // dp1[i] = longest subsequence ending at i with (prev + nums[i])%2 == 1

        // We combine them into a 2×n table: row 0 for mod 0 (even sum), row 1 for mod 1 (odd sum)
        vector<vector<int>> dp(2, vector<int>(n, 1));
        int maxSub = 1;  // At least one element is always a valid subsequence

        // Build DP: for each ending index i, try to extend every j < i
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                int mod = (nums[j] + nums[i]) % 2;
                // mod == 0 → extend dp[0][j] to dp[0][i]; mod == 1 → extend dp[1][j] to dp[1][i]
                dp[mod][i] = max(dp[mod][i], 1 + dp[mod][j]);
                // Update global maximum subsequence length
                maxSub = max(maxSub, dp[mod][i]);
            }
        }
        return maxSub;
    }
};

/*
 *
 * Dry Run for Input: nums = [1, 2, 1, 1, 2, 1, 2]
 * Output: 6
 * Explanation: The longest valid subsequence is [1, 2, 1, 2, 1, 2].
 *
 * n = 7
 * Initialize:
 *   dp[0] = [1,1,1,1,1,1,1]  // even-sum subsequences
 *   dp[1] = [1,1,1,1,1,1,1]  // odd-sum subsequences
 *   maxSub = 1
 *
 * i = 1 (nums[1]=2):
 *   j = 0 (nums[0]=1): (1+2)%2=1 → dp[1][1]=max(1,1+dp[1][0]=2)=2 → maxSub=2
 *
 * i = 2 (nums[2]=1):
 *   j=0: (1+1)%2=0 → dp[0][2]=2 → maxSub=2
 *   j=1: (2+1)%2=1 → dp[1][2]=max(1,1+dp[1][1]=3)=3 → maxSub=3
 *
 * i = 3 (nums[3]=1):
 *   j=0: (1+1)%2=0 → dp[0][3]=2
 *   j=1: (2+1)%2=1 → dp[1][3]=max(1,1+dp[1][1]=3)=3
 *   j=2: (1+1)%2=0 → dp[0][3]=max(2,1+dp[0][2]=3)=3 → maxSub=3
 *
 * i = 4 (nums[4]=2):
 *   j=0: (1+2)%2=1 → dp[1][4]=2
 *   j=1: (2+2)%2=0 → dp[0][4]=2
 *   j=2: (1+2)%2=1 → dp[1][4]=max(2,1+dp[1][2]=4)=4 → maxSub=4
 *   j=3: (1+2)%2=1 → dp[1][4]=max(4,1+dp[1][3]=4)=4
 *
 * i = 5 (nums[5]=1):
 *   j=0: (1+1)%2=0 → dp[0][5]=2
 *   j=1: (2+1)%2=1 → dp[1][5]=2
 *   j=2: (1+1)%2=0 → dp[0][5]=max(2,1+dp[0][2]=3)=3
 *   j=3: (1+1)%2=0 → dp[0][5]=max(3,1+dp[0][3]=4)=4 → maxSub=4
 *   j=4: (2+1)%2=1 → dp[1][5]=max(2,1+dp[1][4]=5)=5 → maxSub=5
 *
 * i = 6 (nums[6]=2):
 *   j=0: (1+2)%2=1 → dp[1][6]=2
 *   j=1: (2+2)%2=0 → dp[0][6]=2
 *   j=2: (1+2)%2=1 → dp[1][6]=max(2,1+dp[1][2]=4)=4
 *   j=3: (1+2)%2=1 → dp[1][6]=max(4,1+dp[1][3]=4)=4
 *   j=4: (2+2)%2=0 → dp[0][6]=max(2,1+dp[0][4]=3)=3
 *   j=5: (1+2)%2=1 → dp[1][6]=max(4,1+dp[1][5]=6)=6 → maxSub=6
 *
 * Final maxSub = 6
 */
