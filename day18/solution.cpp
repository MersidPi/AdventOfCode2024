#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <numeric>
#include <queue>
#define ull long long int 
#define node std::tuple<int,int,int>

std::vector<std::string> extractLinesFromInputFile (std::string fileName) {
    std::ifstream inputFile(fileName);
    std::vector<std::string> lines;
    std::string inputLine;
    while(std::getline(inputFile, inputLine))
        lines.push_back(inputLine);
    return lines;
}

std::vector<std::string> putBoundaries (std::vector<std::string> matrix, char c) {
    ull sum = 0, M = matrix.size(), N = matrix[0].size();
    std::vector<std::string> result(M + 2, std::string(N + 2, ' '));
    for (ull i = 0; i < M + 2; i++)
        for (ull j = 0; j < N + 2; j++)
            if (i == 0 || i == M + 1 || j == 0 || j == N + 1)
                result[i][j] = c;
            else result[i][j] = matrix[i - 1][j - 1];
    return result;
}

ull part1 (std::vector<std::string> lines) {
    ull sum = 0, SIZE = 71, NUMOFBYTES = 1024;
    std::vector<std::string> m(SIZE, std::string(SIZE, '.'));
    for (int i = 0; i < lines.size(); i++) {
        if (i == NUMOFBYTES)
            break;
        std::istringstream iss(lines[i]);
        int num1, num2;
        char c;
        iss >> num1 >> c >> num2;
        m[num2][num1] = '#';
    }
    m = putBoundaries(m, '#');
    for (int i = NUMOFBYTES; i < lines.size(); i++) {
        std::istringstream iss(lines[i]);
        int num1, num2;
        char c;
        iss >> num1 >> c >> num2;
        m[num2 + 1][num1 + 1] = '#';
        bool terminira = false;
        std::map<node, std::vector<node>> visited;
        std::map<node, int> costs;
        std::priority_queue<node,std::vector<node>,std::greater<node>> red;
        red.push({0,1,1});
        while (!red.empty()) {
            node top = red.top();
            red.pop();
            int costOld = std::get<0>(top);
            int cost = costOld;
            int i = std::get<1>(top);
            int j = std::get<2>(top);
            if (i == SIZE  && j == SIZE )
                return cost;
            if (m[i][j + 1] != '#') {
                cost += 1;
                node sljedeci = {0, i, j + 1};
                if (costs.count(sljedeci) == 0 || costs[sljedeci] > cost) {
                    costs[sljedeci] = cost;
                    red.push({cost, i, j + 1});
                    visited[sljedeci].clear();
                    visited[sljedeci].push_back({0, i, j});
                }
                else if (costs[sljedeci] == cost) {
                    visited[sljedeci].push_back({0, i, j});
                }
            }
            cost = costOld;
             if (m[i][j - 1] != '#') {
                    cost += 1;
                node sljedeci = {0, i, j - 1};
                if (costs.count(sljedeci) == 0 || costs[sljedeci] > cost) {
                    costs[sljedeci] = cost;
                    red.push({cost, i, j - 1});
                    visited[sljedeci].clear();
                    visited[sljedeci].push_back({0, i, j});
                }
                else if (costs[sljedeci] == cost) {
                    visited[sljedeci].push_back({0, i, j});
                }
            }
            cost = costOld;
             if (m[i + 1][j] != '#') {
                    cost += 1;
                node sljedeci = {0, i + 1, j};
                if (costs.count(sljedeci) == 0 || costs[sljedeci] > cost) {
                    costs[sljedeci] = cost;
                    red.push({cost, i + 1, j});
                    visited[sljedeci].clear();
                    visited[sljedeci].push_back({0, i, j});
                }
                else if (costs[sljedeci] == cost) {
                    visited[sljedeci].push_back({0, i, j});
                }
            }
            cost = costOld;
             if (m[i - 1][j] != '#') {
                    cost += 1;
                node sljedeci = {0, i - 1, j};
                if (costs.count(sljedeci) == 0 || costs[sljedeci] > cost) {
                    costs[sljedeci] = cost;
                    red.push({cost, i - 1, j});
                    visited[sljedeci].clear();
                    visited[sljedeci].push_back({0, i, j});
                }
                else if (costs[sljedeci] == cost) {
                    visited[sljedeci].push_back({0, i, j});
                }
            }
        }
    }
    return sum;
}

std::string part2 (std::vector<std::string> lines) {
    ull sum = 0, SIZE = 71, NUMOFBYTES = 1024;
    std::vector<std::string> m(SIZE, std::string(SIZE, '.'));
    for (int i = 0; i < lines.size(); i++) {
        if (i == NUMOFBYTES)
            break;
        std::istringstream iss(lines[i]);
        int num1, num2;
        char c;
        iss >> num1 >> c >> num2;
        m[num2][num1] = '#';
    }
    m = putBoundaries(m, '#');
    for (int i = NUMOFBYTES; i < lines.size(); i++) {
        std::istringstream iss(lines[i]);
        int num1, num2;
        char c;
        iss >> num1 >> c >> num2;
        m[num2 + 1][num1 + 1] = '#';
        bool terminira = false;
        std::map<node, std::vector<node>> visited;
        std::map<node, int> costs;
        std::priority_queue<node,std::vector<node>,std::greater<node>> red;
        red.push({0,1,1});
        while (!red.empty()) {
            node top = red.top();
            red.pop();
            int costOld = std::get<0>(top);
            int cost = costOld;
            int i = std::get<1>(top);
            int j = std::get<2>(top);
            if (i == SIZE && j == SIZE - 0)
                terminira = true;
            if (m[i][j + 1] != '#') {
                cost += 1;
                node sljedeci = {0, i, j + 1};
                if (costs.count(sljedeci) == 0 || costs[sljedeci] > cost) {
                    costs[sljedeci] = cost;
                    red.push({cost, i, j + 1});
                    visited[sljedeci].clear();
                    visited[sljedeci].push_back({0, i, j});
                }
                else if (costs[sljedeci] == cost) {
                    visited[sljedeci].push_back({0, i, j});
                }
            }
            cost = costOld;
             if (m[i][j - 1] != '#') {
                    cost += 1;
                node sljedeci = {0, i, j - 1};
                if (costs.count(sljedeci) == 0 || costs[sljedeci] > cost) {
                    costs[sljedeci] = cost;
                    red.push({cost, i, j - 1});
                    visited[sljedeci].clear();
                    visited[sljedeci].push_back({0, i, j});
                }
                else if (costs[sljedeci] == cost) {
                    visited[sljedeci].push_back({0, i, j});
                }
            }
            cost = costOld;
             if (m[i + 1][j] != '#') {
                    cost += 1;
                node sljedeci = {0, i + 1, j};
                if (costs.count(sljedeci) == 0 || costs[sljedeci] > cost) {
                    costs[sljedeci] = cost;
                    red.push({cost, i + 1, j});
                    visited[sljedeci].clear();
                    visited[sljedeci].push_back({0, i, j});
                }
                else if (costs[sljedeci] == cost) {
                    visited[sljedeci].push_back({0, i, j});
                }
            }
            cost = costOld;
             if (m[i - 1][j] != '#') {
                    cost += 1;
                node sljedeci = {0, i - 1, j};
                if (costs.count(sljedeci) == 0 || costs[sljedeci] > cost) {
                    costs[sljedeci] = cost;
                    red.push({cost, i - 1, j});
                    visited[sljedeci].clear();
                    visited[sljedeci].push_back({0, i, j});
                }
                else if (costs[sljedeci] == cost) {
                    visited[sljedeci].push_back({0, i, j});
                }
            }
        }
        if (terminira == false) {
            std::stringstream oss;
            oss << num1 << ',' << num2;
            return oss.str();
        }
    }
    return "";
}

int main () {
    std::vector<std::string> linesFromInputFile = extractLinesFromInputFile("input.txt");
    ull part1result = part1(linesFromInputFile); std::cout << "\nPart 1: " << part1result << "\n";
    std::string part2result = part2(linesFromInputFile); std::cout << "Part 2: " << part2result << "\n\n";
    return 0;
}
