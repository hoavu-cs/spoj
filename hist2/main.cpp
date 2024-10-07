#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

const int MAXN = 15;
const int INF = 1e9;

using namespace std;

int main() {
    /*
        Treat this as a TSP problem where going from city i to city j has cost abs(hist[i] - hist[j]).
        Assume that the starting city is city -1  with height 0.
        dp[S, i] = minimum cost to go from city -1 to city i and visit all cities in set S exactly once.
    */

    while (true) {
        int n; 
        cin >> n;
        if (n == 0) {
            break;
        }
        vector<int> hist(n);

        // read input
        for (int i = 0; i < n; i++) {
            cin >> hist[i];
        }

        // initialize dp table which maps pairs of (set, city) to the minimum cost 
        // going from -1 to city and visiting all cities in set exactly once
        vector<vector<int>> dp((1 << n), vector<int>(n, -INF));
        vector<vector<int>> dp_count((1 << n), vector<int>(n, 0));

        // base case
        for (int i = 0; i < n; i++) {
            int bitmask = (1 << i); // set containing element i only
            dp[bitmask][i] = hist[i];
            dp_count[bitmask][i] = 1;
        }

        // fill dp table
        for (int set_size = 2; set_size <= n; set_size++) { // going through each subset size
            for (int j = 0; j < n; j++) { // going through each city
                for (int bitmask = 1; bitmask <= (1 << n) - 1; bitmask++) { // going through each subset
                    if (__builtin_popcount(bitmask) == set_size && bitmask & (1 << j)) { // skip if bitmask does not contain j or if it is not of size set_size
                        int set_without_j = bitmask & ~(1 << j);
                        dp[bitmask][j] = -INF;
                        dp_count[bitmask][j] = 0;

                        for (int i = 0; i < n; i++) { // dp[S, j] = min_{i in S} dp[S - {i}, i] + abs(hist[i] - hist[j])
                            if (bitmask & (1 << i)){
                                dp[bitmask][j] = max(dp[bitmask][j], dp[set_without_j][i] + abs(hist[j] - hist[i]));
                            }
                        }

                        for (int i = 0; i < n; i++) {
                            if (bitmask & (1 << i) && dp[bitmask][j] == dp[set_without_j][i] + abs(hist[j] - hist[i])) {
                                dp_count[bitmask][j] += dp_count[set_without_j][i];
                            }
                        }
                    }
                }
            }
        }
        // compute the answer
        int max_vertical_perimeter = 0, solution_count = 0;

        for (int i = 0; i < n; i++) {
            int full_set = (1 << n) - 1;
            max_vertical_perimeter = max(max_vertical_perimeter, dp[full_set][i] + hist[i]);
        }

        for (int i = 0; i < n; i++) {
            int full_set = (1 << n) - 1;
            if (dp[full_set][i] + hist[i] == max_vertical_perimeter) {
                solution_count += dp_count[full_set][i];
            }
        }

        int max_perimeter = max_vertical_perimeter + 2 * n;
        cout << max_perimeter << " " << solution_count << endl;
    }

    return 0;
}