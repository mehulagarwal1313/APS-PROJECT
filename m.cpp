#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>

using namespace std;

class Dictionary {
private:
    unordered_set<string> words;

public:
    // Constructor to initialize the dictionary with words from a file
    Dictionary(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Unable to open dictionary file." << endl;
            exit(1);
        }
        string word;
        while (file >> word) {
            words.insert(word);
        }
        file.close();
    }

    // Check if a word is in the dictionary
    bool contains(const string& word) const {
        return words.find(word) != words.end();
    }
};

int main() {
    // Test the Dictionary class
    Dictionary dict("dictionary.txt");

    // Test word lookup
    string word;
    cout << "Enter a word to check if it's in the dictionary: ";
    cin >> word;
    if (dict.contains(word)) {
        cout << word << " is in the dictionary." << endl;
    } else {
        cout << word << " is not in the dictionary." << endl;
    }

    return 0;
}