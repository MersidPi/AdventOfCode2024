#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> extractLinesFromInputFile (std::string fileName) {
    std::ifstream inputFile(fileName);
    std::vector<std::string> lines;
    std::string inputLine;
    while(std::getline(inputFile, inputLine))
        lines.push_back(inputLine);
    return lines;
}

int part1 (std::vector<std::string> linesFromInputFile) {
    int sum = 0;
    std::vector<int> left;
    std::vector<int> right;
    for (std::string line : linesFromInputFile) {
        left.push_back(stoi(line));
        right.push_back(stoi(line.substr(6)));
    }
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    for (int i = 0; i < left.size(); i++)
        sum += std::abs(left[i] - right[i]);
    return sum;
}

int part2 (const std::vector<std::string>& linesFromInputFile) {
    int sum = 0;
    std::vector<int> left, right;
    for (std::string line : linesFromInputFile) {
        left.push_back(stoi(line));
        right.push_back(stoi(line.substr(6)));
    }
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    for (int i = 0; i < left.size(); i++) {
        int counter = 0;
        for (int j = 0; j < left.size(); j++)
            if (right[j] == left[i])
                counter++;
        sum += left[i] * counter;
    }
    return sum;
}

int main () {
    std::vector<std::string> linesFromInputFile = extractLinesFromInputFile("input.txt");
    int part1result = part1(linesFromInputFile);std::cout << "\nPart 1: " << part1result << "\n";
    int part2result = part2(linesFromInputFile);std::cout << "Part 2: " << part2result << "\n\n";
    return 0;
}