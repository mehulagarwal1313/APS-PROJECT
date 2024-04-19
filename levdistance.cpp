#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
//#include<bits/stdc++.h>

using namespace std;

int minDistance(const string& word1, const string& word2) {
    int m = word1.length();
    int n = word2.length();

    // Create a 2D DP array to store the edit distances
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    // Initialize the DP array
    for (int i = 0; i <= m; ++i) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= n; ++j) {
        dp[0][j] = j;
    }

    // Calculate edit distances
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
            }
        }
    }

    // Return the edit distance between the two words
    return dp[m][n];
}
int main() {
    // Test the minDistance function
    string word1 = "aman";
    string word2 = "mehul";
    int distance = minDistance(word1, word2);
    cout << "Edit distance between " << word1 << " and " << word2 << " is: " << distance << endl;

    // Test with more words if needed...

    return 0;
}