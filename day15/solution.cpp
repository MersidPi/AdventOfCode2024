#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <numeric>
#include <algorithm>
#define ull long long int 

std::vector<std::string> extractLinesFromInputFile (std::string fileName) {
    std::ifstream inputFile(fileName);
    std::vector<std::string> lines;
    std::string inputLine;
    while(std::getline(inputFile, inputLine))
        lines.push_back(inputLine);
    return lines;
}

bool canPush (const std::vector<std::string> &bigMap, std::vector<std::pair<int,int>> &boxes, int i, int j, char direction) {
    if (bigMap[i][j] == '.')
        return true;
    if (bigMap[i][j] == ']')
        j--;
    boxes.push_back({i,j});
    if (direction == '<')
        return bigMap[i][j - 1] == '.' || bigMap[i][j - 1] == ']' && canPush(bigMap, boxes, i, j - 1, direction);
    else if (direction == '>')     
        return bigMap[i][j + 2] == '.' || bigMap[i][j + 2] != '#' && canPush(bigMap, boxes, i, j + 2, direction);
    else if (direction == '^') 
        return bigMap[i - 1][j] == '.' && bigMap[i - 1][j + 1] == '.'
                ||  bigMap[i - 1][j] != '#' 
                    && bigMap[i - 1][j + 1] != '#'
                    && canPush(bigMap, boxes, i - 1, j, direction)
                    && canPush(bigMap, boxes, i - 1, j + 1, direction);
    else if (direction == 'v')
        return bigMap[i + 1][j] == '.'  && bigMap[i + 1][j + 1] == '.'
                || bigMap[i + 1][j] != '#' && bigMap[i + 1][j + 1] != '#'
                    && canPush(bigMap, boxes, i + 1, j, direction)
                    && canPush(bigMap, boxes, i + 1, j + 1, direction);
    return false;
}

void push (std::vector<std::string> &bigMap, std::vector<std::pair<int,int>> &boxes, char direction) {
    int i, j;
    if (direction == '>') {
        while (!boxes.empty()) {
            i = boxes.back().first;
            j = boxes.back().second;
            bigMap[i][j + 1] = '['; 
            bigMap[i][j + 2] = ']'; 
            bigMap[i][j] = '.';
            boxes.pop_back();
        }
    }
    else if (direction == '<') {
        while (!boxes.empty()) {
            i = boxes.back().first;
            j = boxes.back().second;
            bigMap[i][j - 1] = '['; 
            bigMap[i][j] = ']'; 
            bigMap[i][j + 1] = '.'; 
            boxes.pop_back();
        }
    }
    else if (direction == '^') {
        std::sort(boxes.begin(), boxes.end(), [](auto a, auto b) { return a.first > b.first; });
        while (!boxes.empty()) {
            i = boxes.back().first;
            j = boxes.back().second;
            bigMap[i - 1][j] = '['; 
            bigMap[i - 1][j + 1] = ']';
            bigMap[i][j] = '.'; 
            bigMap[i][j + 1] = '.';
            boxes.pop_back();
        }
    }
    else if (direction == 'v') {
        std::sort(boxes.begin(), boxes.end(), [](auto a, auto b) { return a.first < b.first; });
        while (!boxes.empty()) {
            i = boxes.back().first;
            j = boxes.back().second;
            bigMap[i + 1][j] = '['; 
            bigMap[i + 1][j + 1] = ']'; 
            bigMap[i][j] = '.'; 
            bigMap[i][j + 1] = '.';
            boxes.pop_back();
        }
    }
}

ull part1 (std::vector<std::string> lines) {
    ull sum = 0, I, J;
    std::vector<std::string> map;
    for (int i = 0; i < lines.size(); i++) {
        if (lines[i].size() == 0)
            break;
        if (lines[i].find('@') != std::string::npos) {
            J = lines[i].find('@');
            I = i;
        }
        map.push_back(lines[i]);
    }
    std::string moves;
    for (int i = map.size(); i < lines.size(); i++)
        moves.append(lines[i]);
    for (int k = 0; k < moves.size(); k++) {
        if (moves[k] == '>') {
            if (map[I][J + 1] == '.') {
                map[I][J + 1] = '@';
                map[I][J] = '.';
                    J++;
            }
            else if (map[I][J + 1] == 'O') {
                int j = J + 1;
                while (map[I][j] == 'O')
                    j++;
                if (map[I][j] == '.') {
                    while (map[I][j - 1] == 'O') {
                        map[I][j] = 'O';
                        j--;
                    }
                    map[I][j] = '@';
                    map[I][j - 1] = '.';
                    J++;
                }
            }
        }
        else if (moves[k] == '<') {
            if (map[I][J - 1] == '.') {
                map[I][J - 1] = '@';
                map[I][J] = '.';
                    J--;
            }
            else if (map[I][J - 1] == 'O') {
                int j = J - 1;
                while (map[I][j] == 'O')
                    j--;
                if (map[I][j] == '.') {
                    while (map[I][j + 1] == 'O') {
                        map[I][j] = 'O';
                        j++;
                    }
                    map[I][j] = '@';
                    map[I][j + 1] = '.';
                    J--;
                }
            }
        }
        else if (moves[k] == '^') {
            if (map[I - 1][J] == '.') {
                map[I - 1][J] = '@';
                map[I][J] = '.';
                    I--;
            }
            else if (map[I - 1][J] == 'O') {
                int i = I - 1;
                while (map[i][J] == 'O')
                    i--;
                if (map[i][J] == '.') {
                    while (map[i + 1][J] == 'O') {
                        map[i][J] = 'O';
                        i++;
                    }
                    map[i][J] = '@';
                    map[i + 1][J] = '.';
                    I--;
                }
            }
        }
        else if (moves[k] == 'v') {
            if (map[I + 1][J] == '.') {
                map[I + 1][J] = '@';
                map[I][J] = '.';
                I++;
            }
            else if (map[I + 1][J] == 'O') {
                int i = I + 1;
                while (map[i][J] == 'O')
                    i++;
                if (map[i][J] == '.') {
                    while (map[i - 1][J] == 'O') {
                        map[i][J] = 'O';
                        i--;
                    }
                    map[i][J] = '@';
                    map[i - 1][J] = '.';
                    I++;
                }
            }
        }
    }
    for (int i = 0; i < map.size(); i++)
        for (int j = 0; j < map[i].size(); j++)
            if (map[i][j] == 'O')
                sum += 100 * i + j;
    return sum;
}

ull part2 (std::vector<std::string> lines) {
    ull sum = 0, I, J;
    std::vector<std::string> map;
    for (int i = 0; i < lines.size(); i++) {
        if (lines[i].size() == 0)
            break;
        if (lines[i].find('@') != std::string::npos) {
            J = lines[i].find('@');
            I = i;
        }
        map.push_back(lines[i]);
    }
    std::string moves;
    for (int i = map.size(); i < lines.size(); i++)
        moves.append(lines[i]);
    std::vector<std::string> bigMap;
    for (int i = 0; i < map.size(); i++) {
        bigMap.push_back({});
        for (int j = 0; j < map[i].size(); j++) {
            switch(map[i][j]) {
                case '#': bigMap[i].append("##"); break;
                case 'O': bigMap[i].append("[]"); break;
                case '.': bigMap[i].append(".."); break;
                case '@': bigMap[i].append("@."); break;
            }
        }
    }
    J *= 2;
    std::vector<std::pair<int,int>> boxes;
    std::ofstream fs("output.txt");
    for (int k = 0; k < moves.size(); k++) {
        boxes.resize(0);
        if (moves[k] == '>') {
            if (bigMap[I][J + 1] == '.') {
                bigMap[I][J + 1] = '@';
                bigMap[I][J] = '.';
                J++;
            }
            else if (bigMap[I][J + 1] == '[' && canPush(bigMap, boxes, I, J + 1, moves[k])) {
                push(bigMap, boxes, moves[k]);
                bigMap[I][J + 1] = '@';
                bigMap[I][J] = '.';
                J++;
            }
        }
        else if (moves[k] == '<') {
            if (bigMap[I][J - 1] == '.') {
                bigMap[I][J - 1] = '@';
                bigMap[I][J] = '.';
                    J--;
            }
            else if (bigMap[I][J - 1] == ']' && canPush(bigMap, boxes, I, J - 1, moves[k])) {
                push(bigMap, boxes, moves[k]);
                bigMap[I][J - 1] = '@';
                bigMap[I][J] = '.';
                J--;
            }
        }
        else if (moves[k] == '^') {
            if (bigMap[I - 1][J] == '.') {
                bigMap[I - 1][J] = '@';
                bigMap[I][J] = '.';
                    I--;
            }
            else if ((bigMap[I - 1][J] == '[' || bigMap[I - 1][J] == ']') && canPush(bigMap, boxes, I - 1, J, moves[k])) {
                push(bigMap, boxes, moves[k]);
                bigMap[I - 1][J] = '@';
                bigMap[I][J] = '.';
                I--;
            }
        }
        else if (moves[k] == 'v') {
            if (bigMap[I + 1][J] == '.') {
                bigMap[I + 1][J] = '@';
                bigMap[I][J] = '.';
                I++;
            }
            else if ((bigMap[I + 1][J] == '[' || bigMap[I + 1][J] == ']') && canPush(bigMap, boxes, I + 1, J, moves[k])) {
                push(bigMap, boxes, moves[k]);
                bigMap[I + 1][J] = '@';
                bigMap[I][J] = '.';
                I++;
            }
        }
    }
    for (int i = 0; i < bigMap.size(); i++)
        for (int j = 0; j < bigMap[i].size(); j++)
            if (bigMap[i][j] == '[')
                sum += 100 * i + j;
    return sum;
}

int main () {
    std::vector<std::string> linesFromInputFile = extractLinesFromInputFile("input.txt");
    ull part1result = part1(linesFromInputFile); std::cout << "\nPart 1: " << part1result << "\n";
    ull part2result = part2(linesFromInputFile); std::cout << "Part 2: " << part2result << "\n\n";
    return 0;
}
