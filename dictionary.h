#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <unordered_set>

#include <string>

class Dictionary {
private:
    std::unordered_set<std::string> words;

public:
    Dictionary(const std::string& filename);

    bool contains(const std::string& word) const;

    const std::unordered_set<std::string>& getWords() const;
};

#endif // DICTIONARY_H