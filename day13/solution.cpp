#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <numeric>
#define ull long long int 

std::vector<std::string> extractLinesFromInputFile (std::string fileName) {
    std::ifstream inputFile(fileName);
    std::vector<std::string> lines;
    std::string inputLine;
    while(std::getline(inputFile, inputLine))
        lines.push_back(inputLine);
    return lines;
}

ull part1 (std::vector<std::string> lines) {
    ull sum = 0, M = lines.size();
    for (int i = 0; i < lines.size(); i += 4) {
        std::istringstream iss(lines[i].substr(12));
        int x1, x2, X, y1, y2, Y;
        char c;
        iss >> x1 >> c >> c >> c >> y1;
        std::istringstream iss2(lines[i + 1].substr(12));
        iss2 >> x2 >> c >> c >> c >> y2;
        std::istringstream iss3(lines[i + 2].substr(9));
        iss3 >> X >> c >> c >> c >> Y;
        bool end = false;
        for (int a = 0; a < 100; a++) {
            for (int b = 0; b < 100; b++) {
                if (a * x1 + b * x2 == X && a * y1 + b * y2 == Y) {
                    sum += 3 * a + b;
                    end = true;
                    break;
                }
            }
            if (end) 
                break;
        }
    }
    return sum;
}

ull part2 (std::vector<std::string> lines) {
    ull sum = 0, M = lines.size(); ull sum2 = 0, inkrement1, inkrement2;
    for (int i = 0; i < lines.size(); i += 4) {
        std::istringstream iss(lines[i].substr(12));
        ull x1, x2, X, y1, y2, Y;
        char c;
        iss >> x1 >> c >> c >> c >> y1;
        std::istringstream iss2(lines[i + 1].substr(12));
        iss2 >> x2 >> c >> c >> c >> y2;
        std::istringstream iss3(lines[i + 2].substr(9));
        iss3 >> X >> c >> c >> c >> Y;
        X += 10000000000000;
        Y += 10000000000000;
        ull a = (X * y2 - Y * x2) / (x1 * y2 - y1 * x2);
        ull b = (X - a * x1) / x2;
        if (a * x1 + b * x2 == X && a * y1 + b * y2 == Y)
            sum += 3 * a + b;
    }
    return sum;
}

int main () {
    std::vector<std::string> linesFromInputFile = extractLinesFromInputFile("input.txt");
    ull part1result = part1(linesFromInputFile); std::cout << "\nPart 1: " << part1result << "\n";
    ull part2result = part2(linesFromInputFile); std::cout << "Part 2: " << part2result << "\n\n";
    return 0;
}
