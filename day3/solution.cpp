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
    for (std::string line : linesFromInputFile) {
        int pos = line.find("mul(") - 1;
        while (line.find("mul(", pos + 1) != std::string::npos) {
            pos = line.find("mul(", pos + 1);
            std::istringstream lineStream(line.substr(pos + 4));
            int num1, num2;
            char c;
            lineStream >> num1;
            lineStream >> c;
            lineStream >> num2;
            lineStream >> c;
            if (c == ')')
                sum += num1 * num2;
        }
    }
    return sum;
}

int part2 (const std::vector<std::string>& linesFromInputFile) {
    int sum = 0;
    std::string line;
    for (std::string lineX : linesFromInputFile)
        line = line + lineX;
    std::vector<int> posDO, posDONT;
    posDO.push_back(-1);
    posDONT.push_back(-2);
    int pos = line.find("do()") - 1;
    while (line.find("do()", pos + 1) != std::string::npos) {
        pos = line.find("do()", pos + 1);
        posDO.push_back(pos);
    }
    pos = line.find("don't()") - 1;
    while (line.find("don't()", pos + 1) != std::string::npos) {
        pos = line.find("don't()", pos + 1);
        posDONT.push_back(pos);
    }

    pos = line.find("mul(") - 1;
    while (line.find("mul(", pos + 1) != std::string::npos) {
        pos = line.find("mul(", pos + 1);
        std::istringstream lineStream(line.substr(pos + 4));
        int num1, num2;
        char c;
        lineStream >> num1;
        lineStream >> c;
        lineStream >> num2;
        lineStream >> c;
        int doPos, dontPos, i;
        for (i = posDO.size() - 1; i >= 0; i--) {
            if (posDO[i] < pos) {
                doPos = posDO[i];
                break;
            }
        }
        for (i = posDONT.size() - 1; i >= 0; i--) {
            if (posDONT[i] < pos) {
                dontPos = posDONT[i];
                break;
            }
        }
        if (c == ')' && doPos > dontPos)
            sum += num1 * num2;
    }
    return sum;
}

int main () {
    std::vector<std::string> linesFromInputFile = extractLinesFromInputFile("input.txt");
    int part1result = part1(linesFromInputFile); std::cout << "\nPart 1: " << part1result << "\n";
    int part2result = part2(linesFromInputFile); std::cout << "Part 2: " << part2result << "\n\n";
    return 0;
}