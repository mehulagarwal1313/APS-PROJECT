#include "Dictionary.h"
#include <fstream>
#include <iostream>

Dictionary::Dictionary(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open dictionary file." << std::endl;
        exit(1);
    }
    std::string word;
    while (file >> word) {
        words.insert(word);
    }
    file.close();
}

bool Dictionary::contains(const std::string& word) const {
    return words.find(word) != words.end();
}

const std::unordered_set<std::string>& Dictionary::getWords() const {
    return words;
}