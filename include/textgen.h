#pragma once

#include <string>
#include <deque>
#include <map>
#include <vector>
#include <random>

typedef std::deque<std::string> prefix;

class TextGenerator {
  public:
    TextGenerator(unsigned int prefixLength, unsigned int seed);

    std::string generateText(unsigned int wordCount, const prefix& startingPrefix);
    void analyze(const std::string& learningText);

    [[nodiscard]]
    const std::map<prefix, std::vector<std::string>>& getPrefixSuffixTable() const;

  private:
    std::map<prefix, std::vector<std::string>> prefixSuffixTable;
    unsigned int prefixLength;
    std::default_random_engine random;
};
