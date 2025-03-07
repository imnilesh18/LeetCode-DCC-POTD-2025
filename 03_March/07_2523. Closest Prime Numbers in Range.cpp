/*
 * 2523. Closest Prime Numbers in Range
 *
 * Given two positive integers left and right, find the two integers num1 and num2 such that:
 *
 * left <= num1 < num2 <= right .
 * Both num1 and num2 are prime numbers.
 * num2 - num1 is the minimum amongst all other pairs satisfying the above conditions.
 * Return the positive integer array ans = [num1, num2]. If there are multiple pairs satisfying these conditions, return the one with the smallest num1 value. If no such numbers exist, return [-1, -1].
 *
 * Example 1:
 * Input: left = 10, right = 19
 * Output: [11,13]
 * Explanation: The prime numbers between 10 and 19 are 11, 13, 17, and 19.
 * The closest gap between any pair is 2, which can be achieved by [11,13] or [17,19].
 * Since 11 is smaller than 17, we return the first pair.
 *
 * Example 2:
 * Input: left = 4, right = 6
 * Output: [-1,-1]
 * Explanation: There exists only one prime number in the given range, so the conditions cannot be satisfied.
 *
 * Constraints:
 * 1 <= left <= right <= 10^6
 */

// Approach 1: Use the Sieve of Eratosthenes to generate all primes up to 'right' and then iterate over the primes within [left, right] to find the closest pair.
// Time Complexity: O(n log log n) for the sieve (where n = right) plus O(n) for scanning the range, overall approximately O(n log log n).
// Space Complexity: O(n) for the boolean sieve array and the list of primes.
class Solution {
public:
    vector<bool> sieveHelper(int right) {
        vector<bool> isPrime(right + 1, true);     // Initialize all numbers as prime

        // 0 and 1 are not prime numbers
        isPrime[0] = false;
        isPrime[1] = false;

        // Sieve algorithm: For each number i, mark its multiples as non-prime.
        for (int i = 2; i* i <= right; i++) {
            if (isPrime[i] == true) {
                for (int j = 2; i* j <= right; j++) {
                    isPrime[i * j] = false;     // Mark the multiple as composite
                }
            }
        }
        return isPrime;
    }
    vector<int> closestPrimes(int left, int right) {
        // Generate prime flags for numbers up to 'right'
        vector<bool> isPrime = sieveHelper(right);

        // Collect all prime numbers in the range [left, right]
        vector<int> primes;

        for (int num = left; num <= right; num++) {
            if (isPrime[num] == true) {
                primes.push_back(num);
            }
        }

        int         minDiff = INT_MAX;     // Initialize the minimum difference as maximum possible integer
        vector<int> result  = { -1, -1 };  // Default result if no pair of primes is found

        // Iterate over the collected primes to find the pair with the smallest difference
        for (int i = 1; i < primes.size(); i++) {
            int diff = primes[i] - primes[i - 1];
            if (diff < minDiff) {
                minDiff = diff;
                result  = { primes[i - 1], primes[i] };
            }
        }
        return result;
    }
};

/*
 * Dry Run:
 * Input: left = 10, right = 19
 *
 * Step 1: Generate prime flags using sieveHelper(19)
 *  isPrime = [false, false, true, true, false, true, false, true, false, false, false, true, false, true, false, false, false, true, false, true]
 *
 * Step 2: Collect primes between 10 and 19:
 *  primes = [11, 13, 17, 19]
 *
 * Step 3: Find the closest prime pair:
 *  - Compare pair (11, 13): diff = 2, update result to [11, 13] and minDiff = 2.
 *  - Compare pair (13, 17): diff = 4, no update since 4 > 2.
 *  - Compare pair (17, 19): diff = 2, no update since diff equals current minDiff and [11, 13] has the smaller first element.
 *
 * Output: [11, 13]
 */

// Approach 2: For each number in the range [left, right], check if it's prime using trial division (up to sqrt(num)).
//            If a prime is found and the gap with the previous prime is <= 2 (the smallest possible gap), return that pair immediately.
//            Otherwise, store all primes and then scan through them to find the closest pair.
// Time Complexity: O((right - left + 1) * sqrt(right)) since each number in the range is checked for primality in O(sqrt(num)) worst-case.
// Space Complexity: O(k) where k is the number of primes in the range [left, right].
class Solution {
public:
    bool isPrime(int num) {
        if (num == 1) {
            return false;
        }
        for (int div = 2; div* div <= num; div++) {
            if (num % div == 0) {
                return false;
            }
        }
        return true;
    }
    vector<int> closestPrimes(int left, int right) {
        vector<int> primes;

        // Iterate through numbers in [left, right] and collect primes.
        for (int num = left; num <= right; num++) {
            if (isPrime(num) == true) {
                // Early return if the current prime and the previous prime have a gap <= 2 (minimum possible gap).
                if (!primes.empty() && num - primes.back() <= 2) {
                    return { primes.back(), num };
                }
                primes.push_back(num);
            }
        }

        int         minDiff = INT_MAX;
        vector<int> result  = { -1, -1 };

        // Find the pair of primes with the smallest difference.
        for (int i = 1; i < primes.size(); i++) {
            int diff = primes[i] - primes[i - 1];
            if (diff < minDiff) {
                minDiff = diff;
                result  = { primes[i - 1], primes[i] };
            }
        }
        return result;
    }
};

/*
 * Dry Run:
 * Input: left = 10, right = 19
 *
 * Step 1: Initialize an empty vector 'primes'.
 * Step 2: Iterate num from 10 to 19:
 *  - num = 10: isPrime(10) returns false.
 *  - num = 11: isPrime(11) returns true, add 11 to primes => primes = [11].
 *  - num = 12: isPrime(12) returns false.
 *  - num = 13: isPrime(13) returns true, check gap: 13 - 11 = 2 <= 2, early return {11, 13}.
 *
 * Output: [11, 13]
 */
