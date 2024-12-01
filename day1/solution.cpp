#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>

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
        std::istringstream lineStream(line);
        int l, r;
        lineStream >> l >> r;
        left.push_back(l);
        right.push_back(r);
    }
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    for (int i = 0; i < left.size(); i++)
        sum += std::abs(left[i] - right[i]);
    return sum;
}

int part2 (const std::vector<std::string>& linesFromInputFile) {
    int sum = 0;
    std::map<int, int> left, right;
    for (std::string line : linesFromInputFile) {
        std::istringstream lineStream(line);
        int l, r;
        lineStream >> l >> r;
        if (left.count(l))
            left[l]++;
        else left[l] = 1;
        if (right.count(r))
            right[r]++;
        else right[r] = 1;
    }
    for (const auto& [key, value] : left)
        sum += value * key * right[key];
    return sum;
}

int main () {
    std::vector<std::string> linesFromInputFile = extractLinesFromInputFile("input.txt");
    int part1result = part1(linesFromInputFile);std::cout << "\nPart 1: " << part1result << "\n";
    int part2result = part2(linesFromInputFile);std::cout << "Part 2: " << part2result << "\n\n";
    return 0;
}