#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <set>

std::vector<std::string> extractLinesFromInputFile (std::string fileName) {
    std::ifstream inputFile(fileName);
    std::vector<std::string> lines;
    std::string inputLine;
    while(std::getline(inputFile, inputLine))
        lines.push_back(inputLine);
    return lines;
}

int part1 (const std::vector<std::string>& linesFromInputFile) {
    int sum = 0, rulesSize = 0;
    std::map<int, std::set<int>> rules;
    for (auto line : linesFromInputFile) {
        if (line.compare("") == 0)
            break;
        std::istringstream lineStream(line);
        int num1, num2;
        char c;
        lineStream >> num1 >> c >> num2;
        rules[num1].insert(num2);
        rulesSize++;
    }
    std::vector<std::vector<int>> order;
    for (int i = rulesSize; i < linesFromInputFile.size(); i++) {
        std::istringstream lineStream(linesFromInputFile[i]);
        int num1, num2;
        char c;
        order.push_back({});
        while (!lineStream.eof()) {
            lineStream >> num1 >> c;
            order.at(order.size() - 1).push_back(num1);
        }
    }
    for (int i = 0; i < order.size(); i++) {
        bool correct = true;
        for (int j = 0; j < order[i].size(); j++) {
            for (int k = j; k < order[i].size(); k++) {
                if (rules[order[i][k]].count(order[i][j]) == 1) {
                    correct = false;
                    break;
                }
            }
            if (!correct)
                break;
        }
        if (correct)
            sum += order[i][order[i].size() / 2];
    }
    return sum;
}

int part2 (const std::vector<std::string>& linesFromInputFile) {
    int sum = 0, rulesSize = 0;
    std::map<int, std::set<int>> rules;
    for (auto line : linesFromInputFile) {
        if (line.compare("") == 0)
            break;
        std::istringstream lineStream(line);
        int num1, num2;
        char c;
        lineStream >> num1 >> c >> num2;
        rules[num1].insert(num2);
        rulesSize++;
    }
    std::vector<std::vector<int>> order;
    for (int i = rulesSize; i < linesFromInputFile.size(); i++) {
        std::istringstream lineStream(linesFromInputFile[i]);
        int num1, num2;
        char c;
        order.push_back({});
        while (!lineStream.eof()) {
            lineStream >> num1 >> c;
            order.at(order.size() - 1).push_back(num1);
        }
    }
    for (int i = 0; i < order.size(); i++) {
        bool correct = true;
        for (int j = 0; j < order[i].size(); j++) {
            for (int k = j; k < order[i].size(); k++) {
                if (rules[order[i][k]].count( order[i][j] ) == 1) {
                    correct = false;
                    int temp = order[i][k];
                    order[i][k] = order[i][j];
                    order[i][j] = temp;
                    j = -1;
                    break;
                }
            }
        }
        if (!correct)
            sum += order[i][order[i].size() / 2];
    }
    return sum;
}

int main () {
    std::vector<std::string> linesFromInputFile = extractLinesFromInputFile("input.txt");
    int part1result = part1(linesFromInputFile); std::cout << "\nPart 1: " << part1result << "\n";
    int part2result = part2(linesFromInputFile); std::cout << "Part 2: " << part2result << "\n\n";
    return 0;
}
