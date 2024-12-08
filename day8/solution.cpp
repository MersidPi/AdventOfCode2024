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

int part1 (std::vector<std::string> m) {
    int sum = 0, M = m.size(), N = m[0].size();
    auto mprint = m;
    std::set<std::pair<int,int>> coords;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) { 
            if (m[i][j] == '.') 
                continue;
            for (int k = i, l = j; k < M; k++) {
                if (k != i)
                    l = 0;
                for (; l < N; l++) {
                    if (m[k][l] != m[i][j] || k == i && l == j) 
                        continue;
                    if (k + (k - i) < M && k + (k - i) >= 0 
                            && l + (l - j) < N && l + (l - j) >= 0) {
                        coords.insert({k + (k - i), l + (l - j)});
                    }
                    if (i - (k - i) < M && i - (k - i) >= 0 
                            && j - (l - j) < N && j - (l - j) >= 0) {
                        coords.insert({i - (k - i), j - (l - j)});
                    }
                }
            }
        }
    }
    sum = coords.size();
    return sum;
}

int part2 (std::vector<std::string> m) {
    int sum = 0, M = m.size(), N = m[0].size();
    std::set<std::pair<int,int>> coords;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) { 
            if (m[i][j] == '.') 
                continue;
            for (int k = i, l = j; k < M; k++) {
                if (k != i)
                    l = 0;
                for (int l = 0; l < N; l++) {
                    if (m[k][l] != m[i][j] || k == i && l == j) 
                        continue;
                    int p = 0;
                    while (k + p * (k - i) < M && k + p * (k - i) >= 0 
                            && l + p * (l - j) < N && l + p * (l - j) >= 0){
                        coords.insert({k + p * (k - i), l + p * (l - j)});
                        p++;
                    }
                    p = 0;
                    while (i - p * (k - i) < M && i - p * (k - i) >= 0 
                            && j - p * (l - j) < N && j - p * (l - j) >= 0){
                        coords.insert({i - p * (k - i), j - p * (l - j)});
                        p++;
                    }
                    if (k + (k - i) < M && k + (k - i) >= 0 
                            && l + (l - j) < N && l + (l - j) >= 0) {
                        coords.insert({k + (k - i), l + (l - j)});
                    }
                    if (i - (k - i) < M && i - (k - i) >= 0 
                            && j - (l - j) < N && j - (l - j) >= 0) {
                        coords.insert({i - (k - i), j - (l - j)});
                    }
                }
            }
        }
    }
    sum = coords.size();
    return sum;
}

int main () {
    std::vector<std::string> linesFromInputFile = extractLinesFromInputFile("input.txt");
    int part1result = part1(linesFromInputFile); std::cout << "\nPart 1: " << part1result << "\n";
    int part2result = part2(linesFromInputFile); std::cout << "Part 2: " << part2result << "\n\n";
    return 0;
}
