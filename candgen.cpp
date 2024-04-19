#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Dictionary.h"

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

// Function to generate candidate corrections for a misspelled word
vector<string> generateCandidates(const string& word, const Dictionary& dict, int maxDistance) {
    vector<string> candidates;
    for (const string& dictWord : dict.getWords()) {
        int distance = minDistance(word, dictWord);
        if (distance <= maxDistance) {
            candidates.push_back(dictWord);
        }
    }
    return candidates;
}

int main() {
    // Example usage
    Dictionary dict("dictionary.txt"); // Provide the path to your dictionary file
    string misspelledWord = "kitten";
    int maxDistance = 2;
    vector<string> suggestions = generateCandidates(misspelledWord, dict, maxDistance);
    cout << "Candidate corrections for '" << misspelledWord << "':" << endl;
    for (const string& suggestion : suggestions) {
        cout << suggestion << endl;
    }
    return 0;
}