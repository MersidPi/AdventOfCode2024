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

std::map<std::pair<int,int>, int> coordsMap;
int part1result = 0, part2result = 0;

void climb (const std::vector<std::string> &m, int i, int j) {
    if (m[i][j] == '9') {
        coordsMap[{i, j}]++;
        return;
    }
    if (j < m[i].size() - 1 && m[i][j + 1] == m[i][j] + 1)
        climb(m, i, j + 1);
    if (j > 0 && m[i][j - 1] == m[i][j] + 1)
        climb(m, i, j - 1);
    if (i < m.size() - 1 && m[i + 1][j] == m[i][j] + 1)
        climb(m, i + 1, j);
    if (i > 0 && m[i - 1][j] == m[i][j] + 1)
        climb(m, i - 1, j);
}

void part1And2 (std::vector<std::string> m) {
    for (int i = 0; i < m.size(); i++)
        for (int j = 0; j < m[i].size(); j++)
            if (m[i][j] == '0') {
                climb(m, i, j);
                part1result += coordsMap.size();
                for (auto [key, val] : coordsMap)
                    part2result += val;
                coordsMap.clear();
            }
}

int main () {
    part1And2(extractLinesFromInputFile("input.txt"));
    std::cout << "\nPart 1: " << part1result << "\n";
    std::cout << "Part 2: " << part2result << "\n\n";
    return 0;
}
