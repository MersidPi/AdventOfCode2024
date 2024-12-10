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

void climb (const std::vector<std::vector<int>> &m, int i, int j) {
    if (m[i][j] == 9) {
        coords.insert({i, j});
        coordsMap[{i, j}]++;
        return;
    }
    if (j < N - 1 && m[i][j + 1] == m[i][j] + 1) {
        climb(m, i, j + 1);
    }
    if (j > 0 && m[i][j - 1] == m[i][j] + 1) {
        climb(m, i, j - 1);
    }
    if (i < M - 1 && m[i + 1][j] == m[i][j] + 1) {
        climb(m, i + 1, j);
    }
    if (i > 0 && m[i - 1][j] == m[i][j] + 1) {
        climb(m, i - 1, j);
    }
}

int part1 (std::vector<std::string> m) {
    int sum = 0;
    M = m.size(), N = m[0].size();
    std::vector<std::vector<int>> mm;
    for (auto x : m) {
        mm.push_back({});
        for (auto y : x)
            mm[mm.size() - 1].push_back(y - '0');
    }
    // for (auto x : m) {
        
    //     for (auto y : x)
    //         std::cout << y << ' ';
    //     std::cout << std::endl;
    // }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (mm[i][j] == 0) {
                climb(mm, i, j);
                sum += coords.size();
                // std::cout << coords.size() << " to je dodano\n";
                coords.clear();
            }
        }
    }
    // sum = coords.size();
    return sum;
}

int part2 (std::vector<std::string> m) {
    int sum = 0;
    M = m.size(), N = m[0].size();
    std::vector<std::vector<int>> mm;
    for (auto x : m) {
        mm.push_back({});
        for (auto y : x)
            mm[mm.size() - 1].push_back(y - '0');
    }
    // for (auto x : m) {
        
    //     for (auto y : x)
    //         std::cout << y << ' ';
    //     std::cout << std::endl;
    // }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (mm[i][j] == 0) {
                climb(mm, i, j);
                for (auto [key, val] : coordsMap){
                    sum += val;
                    // std::cout << val << " to je dodano\n";
                }

                coordsMap.clear();
            }
        }
    }
    // sum = coords.size();
    return sum;
}

int main () {
    std::vector<std::string> linesFromInputFile = extractLinesFromInputFile("input.txt");
    int part1result = part1(linesFromInputFile); std::cout << "\nPart 1: " << part1result << "\n";
    int part2result = part2(linesFromInputFile); std::cout << "Part 2: " << part2result << "\n\n";
    return 0;
}
