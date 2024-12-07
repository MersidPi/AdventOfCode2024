#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

std::vector<std::string> extractLinesFromInputFile (std::string fileName) {
    std::ifstream inputFile(fileName);
    std::vector<std::string> lines;
    std::string inputLine;
    while(std::getline(inputFile, inputLine))
        lines.push_back(inputLine);
    return lines;
}

int part1 (const std::vector<std::string>& linesFromInputFile) {
    int sum = 0;
    auto mat = linesFromInputFile;
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[i].size(); j++) {
            if (mat[i][j] == 'X') {
                if (mat[i].substr(j, 4).compare("XMAS") == 0)
                    sum++;
                if (j >= 3 && mat[i].substr(j - 3, 4).compare("SAMX") == 0)
                    sum++;
                if (i < mat.size() - 3 
                        && mat[i + 1][j] == 'M' 
                        && mat[i + 2][j] == 'A' 
                        && mat[i + 3][j] == 'S')
                    sum++;
                if (i >= 3 
                        && mat[i - 1][j] == 'M' 
                        && mat[i - 2][j] == 'A' 
                        && mat[i - 3][j] == 'S')
                    sum++;
                if (i < mat.size() - 3 
                        && j < mat[i].size() - 3
                        && mat[i + 1][j + 1] == 'M' 
                        && mat[i + 2][j + 2] == 'A' 
                        && mat[i + 3][j + 3] == 'S')
                    sum++; // right down
                if (i < mat.size() - 3 
                        && j >= 3 
                        && mat[i + 1][j - 1] == 'M' 
                        && mat[i + 2][j - 2] == 'A' 
                        && mat[i + 3][j - 3] == 'S')
                    sum++; //left down
                if (i >= 3 
                        && j < mat[i].size() - 3 
                        && mat[i - 1][j + 1] == 'M' 
                        && mat[i - 2][j + 2] == 'A' 
                        && mat[i - 3][j + 3] == 'S')
                    sum++; // right up
                if (i >= 3 && j >= 3 
                        && mat[i - 1][j - 1] == 'M' 
                        && mat[i - 2][j - 2] == 'A' 
                        && mat[i - 3][j - 3] == 'S')
                    sum++;
            }//XMAS
        }
    }
    return sum;
}

int part2 (const std::vector<std::string>& linesFromInputFile) {
    int sum = 0;
    auto mat = linesFromInputFile;
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[i].size(); j++) {
            if (i >= 1 && i < mat.size() - 1 && j >= 1 && j < mat[i].size() - 1 && mat[i][j] == 'A') {
                if ((mat[i + 1][j + 1] == 'S' && mat[i - 1][j - 1] == 'M'
                        || mat[i + 1][j + 1] == 'M' && mat[i - 1][j - 1] == 'S')
                            &&
                    (mat[i - 1][j + 1] == 'S' && mat[i + 1][j - 1] == 'M'
                        || mat[i - 1][j + 1] == 'M' && mat[i + 1][j - 1] == 'S'))
                    sum++; 
            }//XMAS
        }
    }
    return sum;
}

int main () {
    std::vector<std::string> linesFromInputFile = extractLinesFromInputFile("input.txt");
    int part1result = part1(linesFromInputFile); std::cout << "\nPart 1: " << part1result << "\n";
    int part2result = part2(linesFromInputFile); std::cout << "Part 2: " << part2result << "\n\n";
    return 0;
}