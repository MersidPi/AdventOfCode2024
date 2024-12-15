#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <cmath>
#define ull unsigned long long

std::vector<std::string> extractLinesFromInputFile (std::string fileName) {
    std::ifstream inputFile(fileName);
    std::vector<std::string> lines;
    std::string inputLine;
    while(std::getline(inputFile, inputLine))
        lines.push_back(inputLine);
    return lines;
}

ull powInt(ull x, ull y) {
    ull result = 1;
    while (y != 0) {
        result *= x;
        y--;
    }
    return result;
}

std::vector<ull> pt1ValidRowsIndexes;
ull part1 (std::vector<std::string> m) {
    ull sum = 0;
    std::vector<std::vector<ull>> v;
    for (auto line : m) {
        std::istringstream iss(line);
        ull num;
        char c;
        iss >> num >> c;
        v.push_back({num});
        while (!iss.eof()) {
            iss >> num;
            v.at(v.size() - 1).push_back(num);
        }
    }
    for (int i = 0; i < v.size(); i++) {
        int upperBound = powInt(2, v[i].size());
        for (int k = 0; k < upperBound; k++) {
            ull sumTemp = v[i][1];
            int pow = 1;
            for (int j = 2; j < v.at(i).size(); j++) {
                if ((k & pow) == pow)
                    sumTemp += v[i][j];
                else
                    sumTemp *= v[i][j];
                pow *= 2;
            }
            if (sumTemp == v[i][0]){
                sum += sumTemp;
                pt1ValidRowsIndexes.push_back(i);
                break;
            }
        }
    }
    return sum;
}

ull concat (ull a, ull b) {
    ull bb = b;
    if (b == 0)
        return a * 10;
    while (bb != 0) {
        a *= 10; 
        bb /= 10;
    }
    return a + b;
}

int bitcount(ull x) {
    int count = 0;
    while (x > 0) {
        count++;
        x &= x-1;
    }
    return count;
}

ull part2 (std::vector<std::string> m) {
    ull sum = 0;
    std::vector<std::vector<ull>> v;
    int j = 0;
    for (int i = 0; i < m.size(); i++) {
        if (pt1ValidRowsIndexes.size() != 0 && pt1ValidRowsIndexes[j] == i) {
            j++;
            continue;
        }
        std::istringstream iss(m[i]);
        ull num;
        char c;
        iss >> num >> c;
        v.push_back({num});
        while (!iss.eof()) {
            iss >> num;
            v.at(v.size() - 1).push_back(num);
        }
    }
    for (int i = 0; i < v.size(); i++) {
        ull upperBoundL = powInt(2, v[i].size() - 2);
        for (int l = 1; l < upperBoundL; l++) {
            bool valid = false;
            auto row = v[i];
            int upperBoundK = powInt(2, row.size() - 2 - bitcount(l));
                // for first version brute force, change upperBoundK to upperBoundL in the next line
            for (int k = 0; k < upperBoundK; k++) { 
                ull sumTemp = row[1];
                int pow = 1, kk = k;
                for (int j = 2; j < row.size(); j++) {
                    if ((l & pow) == pow) {
                        sumTemp = concat(sumTemp, row[j]);
                        kk <<= 1;
                    }
                        // for first version brute force, change kk to k in the next line
                    else if ((kk & pow) == pow)
                        sumTemp += row[j];
                    else
                        sumTemp *= row[j]; 
                    pow *= 2;
                }
                if (sumTemp == row[0]) {
                    sum += sumTemp;
                    valid = true;
                    break;
                }
            }
            if (valid)
                break;
        }
    }
    return sum + part1(m);
}

int main () {
    std::vector<std::string> linesFromInputFile = extractLinesFromInputFile("input.txt");
    ull part1result = part1(linesFromInputFile); std::cout << "\nPart 1: " << part1result << "\n";
    ull part2result = part2(linesFromInputFile); std::cout << "Part 2: " << part2result << "\n\n";
    return 0;
}
