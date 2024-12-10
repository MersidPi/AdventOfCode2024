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

std::set<std::pair<int,int>> coords;
std::map<std::pair<int,int>, int> coordsMap;
int M, N;

void climb (const std::vector<std::vector<int>> &m, int i, int j, bool part1) {
    if (m[i][j] == 9) {
        if (part1)
            coords.insert({i, j});
        else
            coordsMap[{i, j}]++;
        return;
    }
    if (j < N - 1 && m[i][j + 1] == m[i][j] + 1)
        climb(m, i, j + 1, part1);
    if (j > 0 && m[i][j - 1] == m[i][j] + 1)
        climb(m, i, j - 1, part1);
    if (i < M - 1 && m[i + 1][j] == m[i][j] + 1)
        climb(m, i + 1, j, part1);
    if (i > 0 && m[i - 1][j] == m[i][j] + 1)
        climb(m, i - 1, j, part1);
}

int part1 (std::vector<std::string> m) {
    int sum = 0;
    M = m.size(), N = m[0].size();
    std::vector<std::vector<int>> mInt(M, std::vector<int>(N));
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            mInt[i][j] = m[i][j] - '0';
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            if (mInt[i][j] == 0) {
                climb(mInt, i, j, true);
                sum += coords.size();
                coords.clear();
            }
    return sum;
}

int part2 (std::vector<std::string> m) {
    int sum = 0;
    M = m.size(), N = m[0].size();
    std::vector<std::vector<int>> mInt(M, std::vector<int>(N));
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            mInt[i][j] = m[i][j] - '0';
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            if (mInt[i][j] == 0) {
                climb(mInt, i, j, false);
                for (auto [key, val] : coordsMap)
                    sum += val;
                coordsMap.clear();
            }
    return sum;
}

int main () {
    std::vector<std::string> linesFromInputFile = extractLinesFromInputFile("input.txt");
    int part1result = part1(linesFromInputFile); std::cout << "\nPart 1: " << part1result << "\n";
    int part2result = part2(linesFromInputFile); std::cout << "Part 2: " << part2result << "\n\n";
    return 0;
}
