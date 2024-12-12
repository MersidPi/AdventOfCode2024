#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <set>
#define ull unsigned long long int 

std::vector<std::string> extractLinesFromInputFile (std::string fileName) {
    std::ifstream inputFile(fileName);
    std::vector<std::string> lines;
    std::string inputLine;
    while(std::getline(inputFile, inputLine))
        lines.push_back(inputLine);
    return lines;
}

std::vector<std::string> putBoundaries (std::vector<std::string> matrix, char c) {
    ull sum = 0, M = matrix.size(), N = matrix[0].size();
    std::vector<std::string> result(M+2, std::string(N+2, ' '));
    for (ull i = 0; i < M+2; i++) {
        for (ull j = 0; j < N+2; j++)
            if (i == 0 || i == M+1 || j == 0 || j == N+1)
                result[i][j] = c;
            else
                result[i][j] = matrix[i-1][j-1];
    }
    return result;
}

std::map<std::pair<ull,ull>, ull> coordsInnerPoints, coordsEdges;
ull numOfEdges = 0;

void calculate (const std::vector<std::string> &m, ull i, ull j) {
    char c = m[i][j];
    if (coordsInnerPoints.count({i,j}) == 1) {
        return;
    }
    coordsInnerPoints[{i, j}]++;
    if (m[i][j + 1] == c) {
        calculate(m, i, j + 1);
    }
    else {
        numOfEdges++;
        coordsEdges[{i, j + 1}]++;
    }
    if (m[i][j - 1] == c) {
        calculate(m, i, j - 1);
    }
    else {
        numOfEdges++;
        coordsEdges[{i, j - 1}]++;
    }
    if (m[i + 1][j] == c) {
        calculate(m, i + 1, j);
    }
    else {
        numOfEdges++;
        coordsEdges[{i + 1, j}]++;
    }
    if (m[i - 1][j] == c) {
        calculate(m, i - 1, j);
    }
    else {
        numOfEdges++;
        coordsEdges[{i - 1, j}]++;
    }
}

ull part1 (std::vector<std::string> m) {
    std::vector<std::string> map = putBoundaries(m, '.');
    ull sum = 0, M = map.size(), N = map[0].size();
    for (ull i = 0; i < M; i++) {
        for (ull j = 0; j < N; j++) {
            if (map[i][j] == '.')
                continue;
            numOfEdges = 0;
            calculate(map, i, j);
            sum += numOfEdges * coordsInnerPoints.size();
            for (auto [key, val] : coordsInnerPoints)
                map[key.first][key.second] = '.';
            coordsInnerPoints.clear();
            coordsEdges.clear();
        }
    }
    return sum;
}

ull part2 (std::vector<std::string> m) {
    std::vector<std::string> map = putBoundaries(m, '.');
    ull sum = 0, M = map.size(), N = map[0].size();
    for (ull i = 0; i < M; i++) {
        for (ull j = 0; j < N; j++) {
            if (map[i][j] == '.')
                continue;
            calculate(map, i, j);
            for (auto [key, val] : coordsInnerPoints)
                map[key.first][key.second] = '#';
            auto mapCopy = map;
            for (auto [key, val] : coordsEdges)
                mapCopy[key.first][key.second] = '$';
            numOfEdges = 0;
            for (ull k = 0; k < M; k++)
                for (ull l = 0; l < N; l++)
                    if (mapCopy[k][l] == '#' && mapCopy[k+1][l+0] == '$') {
                        numOfEdges++;
                        while (mapCopy[k][l] == '#' && mapCopy[k+1][l+0] == '$')
                            l++;
                    }
            for (ull k = 0; k < M; k++)
                for (ull l = 0; l < N; l++)
                    if (mapCopy[k][l] == '#' && mapCopy[k-1][l+0] == '$') {
                        numOfEdges++;
                        while (mapCopy[k][l] == '#' && mapCopy[k-1][l+0] == '$')
                            l++;
                    }
            for (ull l = 0; l < N; l++)
                for (ull k = 0; k < M; k++)
                    if (mapCopy[k][l] == '#' && mapCopy[k + 0][l + 1] == '$') {
                        numOfEdges++;
                        while (mapCopy[k][l] == '#' && mapCopy[k + 0][l + 1] == '$')
                            k++;
                    }
            for (ull l = 0; l < N; l++)
                for (ull k = 0; k < M; k++)
                    if (mapCopy[k][l] == '#' && mapCopy[k + 0][l - 1] == '$') {
                        numOfEdges++;
                        while (mapCopy[k][l] == '#' &&  mapCopy[k + 0][l - 1] == '$')
                            k++;
                    }
            sum += numOfEdges * coordsInnerPoints.size();
            for (auto [key, val] : coordsInnerPoints)
                map[key.first][key.second] = '.';
            coordsInnerPoints.clear();
            coordsEdges.clear();
        }
    }
    return sum;
}

int main () {
    std::vector<std::string> linesFromInputFile = extractLinesFromInputFile("input.txt");
    linesFromInputFile = putBoundaries(linesFromInputFile, '.');
    ull part1result = part1(linesFromInputFile); std::cout << "\nPart 1: " << part1result << "\n";
    ull part2result = part2(linesFromInputFile); std::cout << "Part 2: " << part2result << "\n\n";
    return 0;
}
