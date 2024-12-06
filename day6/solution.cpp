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

int part1 (std::vector<std::string> m, std::vector<int>& x, std::vector<int>& y) {
    int i, j, sum = 0;
    bool br = false;
    for (i = 0; i < m.size(); i++) {
        for (j = 0; j < m.size(); j++) {
            if (m[i][j] == '^') {
                br = true;
                m[i][j] = 'O';
                break;
            }
        }
        if (br) break;
    }
    try {
        while (1) {
            while (m.at(i - 1).at(j) != '#') {
                m.at(i).at(j) = 'O';
                i--;
            }
            while (m.at(i).at(j + 1) != '#') {
                m.at(i).at(j) = 'O';
                j++;
            }
            while (m.at(i + 1).at(j) != '#') {
                m.at(i).at(j) = 'O';
                i++;
            }
            while (m.at(i).at(j - 1) != '#') {
                m.at(i).at(j) = 'O';
                j--;
            }
        }
    }
    catch (...) {
        m.at(i).at(j) = 'O';
    }
    for (int i = 0;   i < m.size(); i++) {
        for (int j = 0; j < m.size(); j++) {
            if (m[i][j] == 'O') {
                sum++;
                x.push_back(i);
                y.push_back(j);
            }
        }
    }
    return sum;
}

int part2 (std::vector<std::string> mm) {
    int i, j, sum = 0;
    bool br = false;
    for ( i = 0; i < mm.size(); i++) {
        for ( j = 0; j < mm.size(); j++) {
            if (mm[i][j] == '^') {
                br = true;
                break;
            }
        }
        if (br) break;
    }
    int posI = i, posJ = j;
    std::vector<int> x, y;
    int numOfPos = part1(mm, x, y);
    for (int a = 0; a < numOfPos; a++) {
        int I = x[a], J = y[a];
        auto m = mm;
        if (m[I][J] == '#' || m[I][J] == '^')
            continue;
        else
            m[I][J] = 'O';
        m[posI][posJ] = '.';
        try {
            bool loop = false;
            i = posI;
            j = posJ;
            while (!loop) {
                while (m.at(i - 1).at(j) != '#' && m.at(i - 1).at(j) != 'O') {
                    if (m.at(i).at(j) == '^') {
                        loop = true;
                        sum++;
                        break;
                    }
                    m.at(i).at(j) = '^';
                    i--;
                }
                while (!loop && m.at(i).at(j + 1) != '#' && m.at(i).at(j + 1) != 'O') {
                    if (m.at(i).at(j) == '>') {
                        loop = true;
                        sum++;
                        break;
                    }
                    m.at(i).at(j) = '>';
                    j++;
                }
                while (!loop && m.at(i + 1).at(j) != '#' && m.at(i + 1).at(j) != 'O') {
                    if (m.at(i).at(j) == 'v') {
                        loop = true;
                        sum++;
                        break;
                    }
                    m.at(i).at(j) = 'v';
                    i++;
                }
                while (!loop && m.at(i).at(j - 1) != '#' && m.at(i).at(j - 1) != 'O') {
                    if (m.at(i).at(j) == '<') {
                        loop = true;
                        sum++;
                        break;
                    }
                    m.at(i).at(j) = '<';
                    j--;
                }
            }
        }
        catch (...) { }
        m[I][J] = '.';
    }
    return sum;
}

int main () {
    std::vector<std::string> linesFromInputFile = extractLinesFromInputFile("input.txt");
    std::vector<int> a, b;
    int part1result = part1(linesFromInputFile, a, b); std::cout << "\nPart 1: " << part1result << "\n";
    int part2result = part2(linesFromInputFile); std::cout << "Part 2: " << part2result << "\n\n";
    return 0;
}
