#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Function to calculate the Levenshtein distance between two words
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

// Function to rank suggested corrections based on edit distance and frequency
vector<string> rankSuggestions(const string& misspelledWord, const vector<string>& candidates) {
    // Define a custom comparator function to sort candidates based on edit distance
    auto compare = [&](const string& a, const string& b) {
        return minDistance(a, misspelledWord) < minDistance(b, misspelledWord);
    };

    // Sort candidates based on edit distance from misspelledWord
    vector<string> rankedSuggestions = candidates;
    sort(rankedSuggestions.begin(), rankedSuggestions.end(), compare);

    return rankedSuggestions;
}

int main() {
    // Example usage
    string misspelledWord = "kitten";
    vector<string> candidates = {"kitchen", "kitty", "kitten", "kittens", "sitting", "potato"};
    vector<string> suggestions = rankSuggestions(misspelledWord, candidates);

    cout << "Ranked suggestions for '" << misspelledWord << "':" << endl;
    for (const string& suggestion : suggestions) {
        cout << suggestion << endl;
    }

    return 0;
}