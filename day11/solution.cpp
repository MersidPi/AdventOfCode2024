#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <cmath>
#include <list>
#include <unordered_map>

#define ull unsigned long long int 

std::vector<std::string> extractLinesFromInputFile (std::string fileName) {
    std::ifstream inputFile(fileName);
    std::vector<std::string> lines;
    std::string inputLine;
    while(std::getline(inputFile, inputLine))
        lines.push_back(inputLine);
    return lines;
}

void numberInHalf(ull x, ull &y1, ull &y2, ull &digits) {
    ull d = 0, dec = 1, temp = x;
    while (temp != 0) {
        d++;
        temp /= 10;
    }
    for (ull j = 0; j < d / 2; j++)
        dec *= 10;
    y1 = x / dec;
    y2 = x % dec;
    digits = d;
}

std::unordered_map<ull, std::unordered_map<ull, ull>> history;

ull calc (ull number, ull numOfIterations) {
    if (numOfIterations == 0) {
        history[number][numOfIterations] = 1;
        return 1;
    }
    if (history.count(number) != 0 && history[number].count(numOfIterations) != 0) {
        return history[number][numOfIterations];
    }
    if (number == 0) {
        history[1][numOfIterations - 1] = calc(1, numOfIterations - 1);
        return history[1][numOfIterations - 1];
    }
    ull y1, y2, numOfDigits;
    numberInHalf(number, y1, y2, numOfDigits);
    if (numOfDigits % 2 == 0) {
        history[y1][numOfIterations - 1] = calc(y1, numOfIterations - 1);
        history[y2][numOfIterations - 1] = calc(y2, numOfIterations - 1);
        return history[y1][numOfIterations - 1] + history[y2][numOfIterations - 1];
    }
    else {
        history[number * 2024][numOfIterations - 1] = calc(number * 2024, numOfIterations - 1);
        return history[number * 2024][numOfIterations - 1];
    }
}

ull part1 (std::vector<std::string> m) {
    std::vector<ull> vec;
    std::istringstream lineStream(m[0]);
    ull l;
    while (!lineStream.eof()) {
        lineStream >> l;
        vec.push_back(l);
    }
    for (ull c = 0; c < 25; c++)
        for (ull i = 0; i < vec.size(); i++) {
            ull num = vec[i], firstHalf, secondHalf, numOfDigits;
            numberInHalf(vec[i], firstHalf, secondHalf, numOfDigits);
            if (vec[i] == 0)
                vec[i] = 1;
            else if (numOfDigits % 2 == 0) {
                vec[i] = secondHalf;
                vec.insert(vec.begin() + i, firstHalf);
                i++;
            }
            else 
                vec[i] *= 2024;
        }
    return vec.size();
}

ull part2 (std::vector<std::string> m) {
    ull sum = 0;
    std::vector<ull> vec;
    std::istringstream lineStream(m[0]);
    ull l;
    while (!lineStream.eof()) {
        lineStream >> l;
        vec.push_back(l);
    }
    for (auto x : vec)
        sum += calc(x, 75);
    return sum;
}

int main () {
    std::vector<std::string> linesFromInputFile = extractLinesFromInputFile("input.txt");
    ull part1result = part1(linesFromInputFile); std::cout << "\nPart 1: " << part1result << "\n";
    ull part2result = part2(linesFromInputFile); std::cout << "Part 2: " << part2result << "\n\n";
    return 0;
}
