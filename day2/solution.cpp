#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>

std::vector<std::string> extractLinesFromInputFile (std::string fileName) {
    std::ifstream inputFile(fileName);
    std::vector<std::string> lines;
    std::string inputLine;
    while(std::getline(inputFile, inputLine))
        lines.push_back(inputLine);
    return lines;
}

bool isAsc(std::vector<int> v) {
    std::vector<int> diff;
    int sum = 0;
    for (int i = 0; i < v.size() - 1; i++) {
        diff.push_back(v[i] - v[i + 1]);
        if (v[i + 1] - v[i] > 0)
            sum += 1;
        else sum--;
    }
    return sum > 0;
}


int part1 (std::vector<std::string> linesFromInputFile) {
    int sum = 0;
    std::vector<std::vector<int>> vec;
    for (std::string line : linesFromInputFile) {
        std::istringstream lineStream(line);
        int num = -1;
        lineStream >> num;
        if (num != -1) {
            vec.push_back(std::vector<int>());
            while (lineStream.peek() == ' ') {
                vec.at(vec.size() - 1).push_back(num);
                lineStream >> num;
            }
            vec.at(vec.size() - 1).push_back(num);
        }
    }
    // for (auto x : vec) {
    //     for (auto s : x) std::cout << s << ' ';
    //     std::cout << '\n';
    // }

    auto vec2 = vec;
    std::vector<int> unsafe, SAFE;

    for (int i = 0; i < vec.size(); i++) {
        bool safe = true;
        bool asc = vec.at(i).at(0) < vec.at(i)[1];
        int counter = 0;
        for (int j = 0; j < vec.at(i).size() - 1; j++) {
            if (!asc && (vec.at(i).at(j) - vec.at(i)[j + 1] == 1 || 
                        vec.at(i).at(j) - vec.at(i)[j + 1] == 2 || 
                        vec.at(i).at(j) - vec.at(i)[j + 1] == 3)) {
                continue;
            } else if (asc && (vec.at(i).at(j) - vec.at(i)[j + 1] == -1 || 
                        vec.at(i).at(j) - vec.at(i)[j + 1] == -2 || 
                        vec.at(i).at(j) - vec.at(i)[j + 1] == -3)) {
                continue;
            } 
            safe = false;
            break;
        }



        

        if (safe) {
            sum++;
            // std::cout << i << '\n';
            }
    }
    return sum;
}

int part2 (const std::vector<std::string>& linesFromInputFile) {
    int sum = 0;
    std::vector<std::vector<int>> vec;
    for (std::string line : linesFromInputFile) {
        std::istringstream lineStream(line);
        int num = -1;
        lineStream >> num;
        if (num != -1) {
            vec.push_back(std::vector<int>());
            while (lineStream.peek() == ' ') {
                vec.at(vec.size() - 1).push_back(num);
                lineStream >> num;
            }
            vec.at(vec.size() - 1).push_back(num);
        }
    }
    /*for (auto x : vec) {
        for (auto s : x) std::cout << s << ' ';
        std::cout << '\n';
    }*/

    auto vec2 = vec;
    std::vector<int> unsafe, SAFE;

    for (int i = 0; i < vec.size(); i++) {
        bool safe = true;
        bool asc = vec.at(i).at(0) < vec.at(i)[1];
        int counter = 0;
        for (int j = 0; j < vec.at(i).size() - 1; j++) {
            if (!asc && (vec.at(i).at(j) - vec.at(i)[j + 1] == 1 || 
                        vec.at(i).at(j) - vec.at(i)[j + 1] == 2 || 
                        vec.at(i).at(j) - vec.at(i)[j + 1] == 3)) {
                continue;
            } else if (asc && (vec.at(i).at(j) - vec.at(i)[j + 1] == -1 || 
                        vec.at(i).at(j) - vec.at(i)[j + 1] == -2 || 
                        vec.at(i).at(j) - vec.at(i)[j + 1] == -3)) {
                continue;
            } 
            safe = false;
            break;
        }

        if (!safe) {
            // std::cout << i << " uklanjamo '\n";
            for (int k = 0; k < vec.at(i).size(); k++) {
                auto temp = vec.at(i);
                temp.erase(temp.begin() + k);
                safe = true;
                bool asc = temp[0] < temp[1];
                int counter = 0;
                for (int j = 0; j < temp.size() - 1; j++) {
                    if (!asc && (temp.at(j) - temp[j + 1] == 1 || 
                                temp.at(j) - temp[j + 1] == 2 || 
                                temp.at(j) - temp[j + 1] == 3)) {
                        continue;
                    } else if (asc && (temp.at(j) - temp[j + 1] == -1 || 
                                temp.at(j) - temp[j + 1] == -2 || 
                                temp.at(j) - temp[j + 1] == -3)) {
                        continue;
                    } 
                    safe = false;
                    break;
                }
                if (safe) {
                    // std::cout<<"ispravljeni je ok\n";
                    break;}
            }
        }

        

        if (safe) 
            sum++;
    }
    return sum;
}

int main () {
    std::vector<std::string> linesFromInputFile = extractLinesFromInputFile("input.txt");
    int part1result = part1(linesFromInputFile);std::cout << "\nPart 1: " << part1result << "\n";
    int part2result = part2(linesFromInputFile);std::cout << "Part 2: " << part2result << "\n\n";
    std::cout<<isAsc({3,2,0,-1,-2});
    return 0;
}