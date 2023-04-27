// Copyright 2023 mSiotniHS

#include <iostream>
#include <fstream>
#include "textgen.h"

int main() {
    std::random_device rd;
    TextGenerator generator(2, rd());

    std::string input;
    std::ifstream inputFile("input.txt");
    std::string fileLine;
    while (inputFile >> fileLine) {
        input.append(fileLine + ' ');
    }
    inputFile.close();

    generator.analyze(input);
    std::string text = generator.generateText(1000, { "Одна", "девочка" });

    std::ofstream outputFile("output.txt");
    outputFile << text;
    outputFile.close();

    return 0;
}
