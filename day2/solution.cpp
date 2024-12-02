#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

std::vector<std::string> extractLinesFromInputFile (std::string fileName) {
    std::ifstream inputFile(fileName);
    std::vector<std::string> lines;
    std::string inputLine;
    while(std::getline(inputFile, inputLine))
        lines.push_back(inputLine);
    return lines;
}

bool isSafe(std::vector<int> v) {
    bool asc = v[0] < v[1];
    int counter = 0;
    for (int j = 0; j < v.size() - 1; j++) {
        if (!asc && (v[j] - v[j + 1] == 1 || 
                    v[j] - v[j + 1] == 2 || 
                    v[j] - v[j + 1] == 3)) {
            continue;
        } else if (asc && (v[j] - v[j + 1] == -1 || 
                    v[j] - v[j + 1] == -2 || 
                    v[j] - v[j + 1] == -3)) {
            continue;
        } 
        return false;
    }
    return true;
}

int part1 (const std::vector<std::string>& linesFromInputFile) {
    int sum = 0;
    std::vector<int> vec;
    for (std::string line : linesFromInputFile) {
        std::istringstream lineStream(line);
        int num;
        while (!lineStream.eof()) {
            lineStream >> num;
            vec.push_back(num);
        }
        if (isSafe(vec))
            sum++;
        vec.resize(0);
    }
    return sum;
}

int part2 (const std::vector<std::string>& linesFromInputFile) {
    int sum = 0;
    std::vector<int> vec;
    for (std::string line : linesFromInputFile) {
        std::istringstream lineStream(line);
        int num;
        while (!lineStream.eof()) {
            lineStream >> num;
            vec.push_back(num);
        }
        if (isSafe(vec))
            sum++;
        else {
            auto temp = vec;
            for (int i = 0; i < vec.size(); i++) {
                temp = vec;
                temp.erase(temp.begin() + i);
                if (isSafe(temp)) {
                    sum++;
                    break;
                }
            }
        }
        vec.resize(0);
    }
    return sum;
}

int main () {
    std::vector<std::string> linesFromInputFile = extractLinesFromInputFile("input.txt");
    int part1result = part1(linesFromInputFile);std::cout << "\nPart 1: " << part1result << "\n";
    int part2result = part2(linesFromInputFile);std::cout << "Part 2: " << part2result << "\n\n";
    return 0;
}