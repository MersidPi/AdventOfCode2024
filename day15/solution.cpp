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
    // std::cout << "usao u canpush sa i " << i << " j " << j << '\n';
    // if (bigMap[i][j] == '.' && bigMap[i][j+1] == '.')
        // return true;
    if (bigMap[i][j] == '.'){
        return true;
    }
    if (bigMap[i][j] == ']'){
        j--;
        // std::cout << "smanjio je j\n";
    }
    // else if (bigMap[i][j] == '[')
    // if (bigMap[i][j+1] == '['){
    //     std::cout << "pozvao ovdje \n";
    //     return canPush(bigMap, boxes, i, j + 1, direction);
    // }
    //if (bigMap[i][j] != '.' )
    boxes.push_back({i,j});
    //  std::cout << "\n ubacena kutija " << i << ' ' << j << bigMap[i][j] <<'\n';
    switch (direction) {
        case '<': 
            // std::cout << "usao u canpush <";
            return bigMap[i][j - 1] == '.' || bigMap[i][j - 1] == ']' && canPush(bigMap, boxes, i, j - 1, direction);
        case '>': 
            return bigMap[i][j + 2] == '.' || bigMap[i][j + 2] != '#' && canPush(bigMap, boxes, i, j + 2, direction);
        case '^':
            return bigMap[i - 1][j] == '.'  && bigMap[i - 1][j + 1] == '.'
                    || bigMap[i - 1][j] != '#' && bigMap[i - 1][j + 1] != '#'
                        && canPush(bigMap, boxes, i - 1, j, direction)
                        && canPush(bigMap, boxes, i - 1, j + 1, direction);
            // return bigMap[i - 1][j] == '.'  && bigMap[i - 1][j + 1] == '.'
                    // || bigMap[i - 1][j] != '#' && canPush(bigMap, boxes, i - 1, j, direction)
                        // && bigMap[i - 1][j + 1] != '#' && canPush(bigMap, boxes, i - 1, j + 1, direction);
        case 'v':
            return bigMap[i + 1][j] == '.'  && bigMap[i + 1][j + 1] == '.'
                    || bigMap[i + 1][j] != '#' && bigMap[i + 1][j + 1] != '#'
                        && canPush(bigMap, boxes, i + 1, j, direction)
                        && canPush(bigMap, boxes, i + 1, j + 1, direction);
            // return bigMap[i + 1][j] == '.'  && bigMap[i + 1][j + 1] == '.'
            //         || bigMap[i + 1][j] != '#' && canPush(bigMap, boxes, i + 1, j, direction)
            //             && bigMap[i + 1][j + 1] != '#' && canPush(bigMap, boxes, i + 1, j + 1, direction);
    }
    // std::cout << "returno false ";
    return false;
}

void push (std::vector<std::string> &bigMap, std::vector<std::pair<int,int>> &boxes, char direction) {
    int i, j;
    if (direction == '^') {
        std::sort(boxes.begin(), boxes.end(), [](std::pair<int,int> a, std::pair<int,int> b) {
            return a.first > b.first;
        });
        while (!boxes.empty()) {
            //std::cout << "guralo se";
            i = boxes.back().first;
            j = boxes.back().second;
            bigMap[i - 1][j] = '['; 
            bigMap[i - 1][j + 1] = ']';
            bigMap[i][j] = '.'; 
            bigMap[i][j + 1] = '.';
            boxes.pop_back();
        }
    }
    else if (direction == '>') {
        while (!boxes.empty()) {
            i = boxes.back().first;
            j = boxes.back().second;
            bigMap[i][j + 1] = '['; 
            bigMap[i][j + 2] = ']'; 
            bigMap[i][j] = '.';
            boxes.pop_back();
        }
    }
    else if (direction == 'v') {
        std::sort(boxes.begin(), boxes.end(), [](std::pair<int,int> a, std::pair<int,int> b) {
            return a.first < b.first;
        });
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
}


ull part1 (std::vector<std::string> lines) {
    ull sum = 0, I, J;
    std::vector<std::string> map;
    int i = 0;
    for (; i < lines.size(); i++) {
        if (lines[i].size() == 0)
            break;
        if (lines[i].find('@') != std::string::npos) {
            J = lines[i].find('@');
            I = i;
        }
        map.push_back(lines[i]);
    }
    std::string moves;
    for (; i < lines.size(); i++)
        moves.append(lines[i]);
    // std::cout << "robot je na " << I << ' ' << J << '\n';
    // for (auto x : map) {
    //     for (auto y : x )
    //         std::cout << y << ' ';
    //     std::cout << '\n';
    // }

    // for (auto x : moves)
    //     std::cout << x << ' ';
    int M = map.size(), N = map[0].size();
    
    for (int k = 0; k < moves.size(); k++) {
        
        // std::cout << k << " robot je na " << I << ' ' << J << " znak je " << moves[k] << '\n';
        // for (auto x : map) {
        //     for (auto y : x )
        //         std::cout << y << ' ';
        //     std::cout << '\n';
        // }
        if (k == 53232332323)
            break;
        if (moves[k] == '<') {
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
            else { // tu je zid # i ne radi nista

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
            else { // tu je zid # i ne radi nista

            }
        }
        else if (moves[k] == '>') {
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
            else { // tu je zid # i ne radi nista

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
            else { // tu je zid # i ne radi nista

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
    int i = 0;
    for (; i < lines.size(); i++) {
        if (lines[i].size() == 0)
            break;
        if (lines[i].find('@') != std::string::npos) {
            J = lines[i].find('@');
            I = i;
        }
        map.push_back(lines[i]);
    }
    std::string moves;
    for (; i < lines.size(); i++)
        moves.append(lines[i]);
    J *= 2;
    // std::cout << "robot je na " << I << ' ' << J << '\n';
    // for (auto x : map) {
    //     for (auto y : x )
    //         std::cout << y << ' ';
    //     std::cout << '\n';
    // }
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
                                        // bigMap = map;
                                        // J /= 2;
    // std::cout << "INICIJALNA BIGMAP: \n";
    // for (auto x : bigMap) {
    //     for (auto y : x )
    //         std::cout << y << ' ';
    //     std::cout << '\n';
    // }
    // std::cout << '\n';
    int M = bigMap.size(), N = bigMap[0].size();
    std::vector<std::pair<int,int>> boxes;
    std::ofstream fs("output.txt");
    for (int k = 0; k < moves.size(); k++) {
        // std::cout << k << " robot je na " << I << ' ' << J << " znak je " << moves[k] << '\n';
        boxes.resize(0);
        // if (k == 1222)
        //     break;
        if (moves[k] == '<') {
            if (bigMap[I][J - 1] == '.') {
                bigMap[I][J - 1] = '@';
                bigMap[I][J] = '.';
                    J--;
            }
            else if (bigMap[I][J - 1] == ']') {
                if (canPush(bigMap, boxes, I, J - 1, moves[k])){
                    push(bigMap, boxes, moves[k]);
                    bigMap[I][J - 1] = '@';
                    bigMap[I][J] = '.';
                    J--;
                }
            }
        }
        else if (moves[k] == '^') {
            if (bigMap[I - 1][J] == '.') {
                // std::cout << "ne treba gurat";
                bigMap[I - 1][J] = '@';
                bigMap[I][J] = '.';
                    I--;
            }
            else if (bigMap[I - 1][J] == '[' || bigMap[I - 1][J] == ']') {
                if (canPush(bigMap, boxes, I - 1, J, moves[k])){
                    push(bigMap, boxes, moves[k]);
                    // std::cout 
                    bigMap[I - 1][J] = '@';
                    bigMap[I][J] = '.';
                    I--;
                }
            }
            // std::cout << " za ^ provjera je " << (bigMap[I - 1][J] == '[') << ' ' << (bigMap[I - 1][J] == ']') << '\n';
        }
        else if (moves[k] == '>') {
            if (bigMap[I][J + 1] == '.') {
                bigMap[I][J + 1] = '@';
                bigMap[I][J] = '.';
                J++;
            }
            else if (bigMap[I][J + 1] == '[') {
                if (canPush(bigMap, boxes, I, J + 1, moves[k])) {
                    // std::cout << "\nprosaona push\n";
                    push(bigMap, boxes, moves[k]);
                    bigMap[I][J + 1] = '@';
                    bigMap[I][J] = '.';
                    J++;
                }
            }
            
        }
        else if (moves[k] == 'v') {
            if (bigMap[I + 1][J] == '.') {
                bigMap[I + 1][J] = '@';
                bigMap[I][J] = '.';
                I++;
            }
            else if (bigMap[I + 1][J] == '[' || bigMap[I + 1][J] == ']') {
                if (canPush(bigMap, boxes, I + 1, J, moves[k])) {
                    push(bigMap, boxes, moves[k]);
                    bigMap[I + 1][J] = '@';
                    bigMap[I][J] = '.';
                    I++;
                }
            }
        }
        if (k < 0){
            // fs << "nakon guranja:\n";
            for (auto x : bigMap) {
                for (auto y : x )
                    fs << y ;
                fs << '\n';
            }
            fs << '\n';
        }
        for (int i = 0; i < bigMap.size(); i++)
            for (int j = 0; j < bigMap[i].size(); j++)
                if (bigMap[i][j] == '[' && bigMap[i][j + 1] != ']'
                    || bigMap[i][j] == '.' && bigMap[i][j + 1] == ']'
                    || bigMap[i][j] == ']' && bigMap[i][j + 1] == ']' ){
                    
                    for (auto x : bigMap) {
                        for (auto y : x )
                            fs << y ;
                        fs << '\n';
                    }
                    fs << '\n';
                    fs << k;
                    std::cout << "ovdje gotov " << i << ' ' << j;
                    return j;
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
