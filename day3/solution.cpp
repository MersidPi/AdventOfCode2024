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
            lineStream >> num1 >> c >> num2 >> c;
            if (c == ')')
                sum += num1 * num2;
        }
    }
    return sum;
}

int findNext(std::string str, int pos) {
    int posMul = str.find("mul(", pos + 1);
    int posDo = str.find("do()", pos + 1);
    int posDont = str.find("don't()", pos + 1);
    if (posMul == -1 && posDo == -1 && posDont == -1)
        return -1;
    if (posDo == -1)
        posDo = str.size();
    if (posDont == -1)
        posDont = str.size();
    return std::min(posMul, std::min(posDo, posDont));
}

int part2 (const std::vector<std::string>& linesFromInputFile) {
    int sum = 0;
    bool DO = true;
    for (std::string line : linesFromInputFile) {
        int pos = findNext(line, -1) - 1;
        while (findNext(line, pos) != -1) {
            pos = findNext(line, pos);
            if (line[pos] == 'm') {
                std::istringstream lineStream(line.substr(pos + 4));
                int num1, num2;
                char c;
                lineStream >> num1 >> c >> num2 >> c;
                int doPos, dontPos, i;
                if (c == ')' && DO)
                    sum += num1 * num2;
            } 
            else if (line[pos + 2] == 'n')
                DO = false;
            else 
                DO = true;
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