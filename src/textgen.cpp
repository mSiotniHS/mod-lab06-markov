#include <stdexcept>
#include <iostream>
#include "textgen.h"

TextGenerator::TextGenerator(unsigned int prefixLength, unsigned int seed) : prefixSuffixTable(), random(seed) {
    this->prefixLength = prefixLength;
}

std::string nextToken(std::string& text, char delimiter, bool& isLastToken) {
    size_t position;
    std::string token;

    if ((position = text.find(delimiter)) != std::string::npos) {
        isLastToken = false;
        token = text.substr(0, position);
        text.erase(0, position + 1);
    } else {
        isLastToken = true;
        return text;
    }

    return token;
}

void TextGenerator::analyze(const std::string& learningText) {
    this->prefixSuffixTable.clear();
    std::string text = learningText;

    const char delimiter = ' ';

    prefix currentPrefix;
    std::string currentSuffix;
    bool isLastToken = false;

    while (not isLastToken) {
        if (currentPrefix.empty()) {
            for (size_t i = 0; i < prefixLength; i++) {
                currentPrefix.push_back(nextToken(text, delimiter, isLastToken));
            }
        } else {
            currentPrefix.pop_front();
            currentPrefix.push_back(currentSuffix);
        }

        currentSuffix = nextToken(text, delimiter, isLastToken);

        prefixSuffixTable[currentPrefix].push_back(currentSuffix);
    }

    /*for (auto const& [key, value] : prefixSuffixTable) {
        std::cout << '[';
        for (auto const& prefix : key) {
            std::cout << prefix << ", ";
        }
        std::cout << "] -> {";
        for (auto const& oneOfSuffixes : value) {
            std::cout << oneOfSuffixes << ", ";
        }
        std::cout << '}' << std::endl;
    }*/
}

std::string TextGenerator::generateText(unsigned int wordCount, const prefix& startingPrefix) {
    std::string text;
//    prefix currentPrefix = prefixSuffixTable.begin()->first;
    prefix currentPrefix = startingPrefix;

    for (size_t i = 0; i < wordCount; i++) {
        if (prefixSuffixTable.count(currentPrefix) == 0) break;

        auto suffixes = prefixSuffixTable[currentPrefix];
        std::string nextToken = suffixes[random() % suffixes.size()];
        currentPrefix.push_back(nextToken);

        text.append(currentPrefix.front() + ' ');
        currentPrefix.pop_front();
    }

    while (!currentPrefix.empty()) {
        text.append(currentPrefix.front() + ' ');
        currentPrefix.pop_front();
    }

    return text;
}

