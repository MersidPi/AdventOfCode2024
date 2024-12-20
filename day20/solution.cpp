#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <numeric>
#include <queue>
#include <limits>
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
    ull sum = 0;
    std::vector<std::string> m(lines);
    int startI, startJ, endI, endJ;
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m[0].size(); j++) {
            if (m[i][j] == 'S') {
                startI = i;
                startJ = j;
                m[i][j] = '.';
            }
            else if (m[i][j] == 'E') {
                endI = i;
                endJ = j;
                m[i][j] = '.';
            }
        }
    }
    ull costWithoutCheats = 0;
    std::map<node, std::vector<node>> visited;
    std::map<node, int> costs;
    std::priority_queue<node,std::vector<node>,std::greater<node>> red;
    red.push({0,startI,startJ});
    while (!red.empty()) {
        node top = red.top();
        red.pop();
        int costOld = std::get<0>(top);
        int cost = costOld;
        int i = std::get<1>(top);
        int j = std::get<2>(top);
        if (i == endI  && j == endJ) {
            costWithoutCheats = cost;
            break;
        }
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
    std::vector<std::vector<double>> costsMatrix(m.size(), std::vector<double>(m[0].size()));
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m[0].size(); j++) {
            if (m[i][j] == '#')
                costsMatrix[i][j] = std::numeric_limits<double>::quiet_NaN();
            else costsMatrix[i][j] = 0;
        }
    }
    for (auto [k, v] : costs)
        costsMatrix[std::get<1>(k)][std::get<2>(k)] = v;
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m[0].size(); j++) {
            if (i > 0 && i < m.size() - 1 && j > 0 && j < m[0].size() - 1 && m[i][j] == '#') {
                if (   std::abs(costsMatrix[i-1][j] - costsMatrix[i][j-1]) >= 102
                    || std::abs(costsMatrix[i-1][j] - costsMatrix[i][j+1]) >= 102 
                    || std::abs(costsMatrix[i-1][j] - costsMatrix[i+1][j]) >= 102
                    || std::abs(costsMatrix[i+1][j] - costsMatrix[i][j-1]) >= 102
                    || std::abs(costsMatrix[i+1][j] - costsMatrix[i][j+1]) >= 102                    
                    || std::abs(costsMatrix[i][j-1] - costsMatrix[i][j+1]) >= 102)
                sum++;
            }
        }
    }
    return sum;
}

ull part2 (std::vector<std::string> lines) {
    ull sum = 0;
    std::vector<std::string> m(lines);
    int startI, startJ, endI, endJ;
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m[0].size(); j++) {
            if (m[i][j] == 'S') {
                startI = i;
                startJ = j;
                m[i][j] = '.';
            }
            else if (m[i][j] == 'E') {
                endI = i;
                endJ = j;
                m[i][j] = '.';
            }
        }
    }
    ull costWithoutCheats = 0;
    std::map<node, std::vector<node>> visited;
    std::map<node, int> costs;
    std::priority_queue<node,std::vector<node>,std::greater<node>> red;
    red.push({0,startI,startJ});
    while (!red.empty()) {
        node top = red.top();
        red.pop();
        int costOld = std::get<0>(top);
        int cost = costOld;
        int i = std::get<1>(top);
        int j = std::get<2>(top);
        if (i == endI && j == endJ) {
            costWithoutCheats = cost;
            break;
        }
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
    std::vector<std::vector<double>> costsMatrix(m.size(), std::vector<double>(m[0].size()));
    for (int i = 0; i < m.size(); i++)
        for (int j = 0; j < m[0].size(); j++)
            if (m[i][j] == '#')
                costsMatrix[i][j] = std::numeric_limits<double>::quiet_NaN();
            else costsMatrix[i][j] = 0;
    for (auto [k, v] : costs)
        costsMatrix[std::get<1>(k)][std::get<2>(k)] = v;
    costsMatrix[startI][startJ] = 0;
    std::map<ull,ull> map;
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m[0].size(); j++) {
            if (i > 0 && i < m.size() - 1 && j > 0 && j < m[0].size() - 1 && m[i][j] == '.') {
                bool trebaBreak = false;
                if (i == 3 && j == 1)
                    trebaBreak = false;
                std::set<ull> costsWithCheat;
                for (int k = i - 20; k <= i + 20; k++) {
                    for (int l = j - 20; l <= j + 20; l++) {
                        if (k < 0 || k > m.size() - 1 || l < 0 || l > m[0].size() - 1)
                            continue;
                        if (std::abs(i - k) + std::abs(j - l) > 20)
                            continue;
                        if (m[k][l] == '#')
                            continue;
                        if (costsMatrix[i][j] < costsMatrix[k][l] &&
                            std::abs(costsMatrix[i][j] + std::abs(i - k) + std::abs(j - l) - costsMatrix[k][l]) >= 100)
                            sum++,
                            map[std::abs(costsMatrix[i][j] + std::abs(i - k) + std::abs(j - l) - costsMatrix[k][l])]++;
                            if (trebaBreak && std::abs(costsMatrix[i][j] + std::abs(i - k) + std::abs(j - l) - costsMatrix[k][l]) == 74){
                                std::cout << std::abs(costsMatrix[i][j] + std::abs(i - k) + std::abs(j - l) - costsMatrix[k][l]) << '\n';
                                std::cout << k << ' ' << l << '\n';
                            }
                    }
                }
                if (trebaBreak)
                    break;
                
            }
        }
    }
    return sum;
}

int main () {
    std::vector<std::string> linesFromInputFile = extractLinesFromInputFile("input.txt");
    ull part1result = part1(linesFromInputFile); std::cout << "\nPart 1: " << part1result << "\n";
    ull part2result = part2(linesFromInputFile); std::cout << "Part 2: " << part2result << "\n\n";
    return 0;
}
