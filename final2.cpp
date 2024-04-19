#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include<algorithm>
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
    // Load dictionary from file
    Dictionary dict("dictionary.txt"); // Replace "dictionary.txt" with the path to your dictionary file

    // Prompt user to input text
    cout << "Enter text to spell check (press Enter to finish):\n";

    // Read input text from the user
    string inputText;
    getline(cin, inputText);

    // Process the input text
    stringstream ss(inputText);
    string correctedText;
    string word;
    while (ss >> word) {
        // Check if word is in dictionary
        if (dict.contains(word)) {
            correctedText += word + " ";
        } else {
            // Generate candidate corrections
            vector<string> candidates = generateCandidates(word, dict, 2); // Adjust maxDistance as needed

            // Rank suggestions
            vector<string> suggestions = rankSuggestions(word, candidates);

            // Append the best suggestion (or original word if no suggestions)
            correctedText += suggestions.empty() ? word : suggestions.front();
            correctedText += " ";
        }
    }

    // Print the corrected text
    cout << "Corrected text:\n" << correctedText << endl;

    return 0;
}