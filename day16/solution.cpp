#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <numeric>
#include <queue>
#define ull unsigned long long int 
#define ll long long int 
#define node std::tuple<int,int,int,char>

std::vector<std::string> extractLinesFromInputFile (std::string fileName) {
    std::ifstream inputFile(fileName);
    std::vector<std::string> lines;
    std::string inputLine;
    while(std::getline(inputFile, inputLine))
        lines.push_back(inputLine);
    return lines;
}

int goalI, goalJ;

std::map<node, std::vector<node>> visited;
ll part1 (std::vector<std::string> m) {
    ll sum = 0, M = m.size(), N = m[0].size();
    int I, J;
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            if (m[i][j] == 'S')
                I = i, J = j;
            else if (m[i][j] == 'E')
                goalI = i, goalJ = j;
    m[goalI][goalJ] = '.';
    std::map<node, int> costs;
    std::priority_queue<node,std::vector<node>,std::greater<node>> red;
    red.push({0, I, J, '>'});
    while (!red.empty()) {
        node top = red.top();
        red.pop();
        int costOld = std::get<0>(top);
        int cost = costOld;
        int i = std::get<1>(top);
        int j = std::get<2>(top);
        char direction = std::get<3>(top);
        if (i == goalI && j == goalJ)
            return cost;
        if (m[i][j + 1] != '#') {
            if (direction == '>')
                cost += 1;
            else cost += 1001;
            node sljedeci = {0, i, j + 1, '>'};
            if (costs.count(sljedeci) == 0 || costs[sljedeci] > cost) {
                costs[sljedeci] = cost;
                red.push({cost, i, j + 1, '>'});
                visited[sljedeci].clear();
                visited[sljedeci].push_back({0, i, j, direction});
            }
            else if (costs[sljedeci] == cost) {
                visited[sljedeci].push_back({0, i, j, direction});
            }
        }
        cost = costOld;
         if (m[i][j - 1] != '#') {
            if (direction == '<')
                cost += 1;
            else cost += 1001;
            node sljedeci = {0, i, j - 1, '<'};
            if (costs.count(sljedeci) == 0 || costs[sljedeci] > cost) {
                costs[sljedeci] = cost;
                red.push({cost, i, j - 1, '<'});
                visited[sljedeci].clear();
                visited[sljedeci].push_back({0, i, j, direction});
            }
            else if (costs[sljedeci] == cost) {
                visited[sljedeci].push_back({0, i, j, direction});
            }
        }
        cost = costOld;
         if (m[i + 1][j] != '#') {
            if (direction == 'v')
                cost += 1;
            else cost += 1001;
            node sljedeci = {0, i + 1, j, 'v'};
            if (costs.count(sljedeci) == 0 || costs[sljedeci] > cost) {
                costs[sljedeci] = cost;
                red.push({cost, i + 1, j, 'v'});
                visited[sljedeci].clear();
                visited[sljedeci].push_back({0, i, j, direction});
            }
            else if (costs[sljedeci] == cost) {
                visited[sljedeci].push_back({0, i, j, direction});
            }
        }
        cost = costOld;
         if (m[i - 1][j] != '#') {
            if (direction == '^')
                cost += 1;
            else cost += 1001;
            node sljedeci = {0, i - 1, j, '^'};
            if (costs.count(sljedeci) == 0 || costs[sljedeci] > cost) {
                costs[sljedeci] = cost;
                red.push({cost, i - 1, j, '^'});
                visited[sljedeci].clear();
                visited[sljedeci].push_back({0, i, j, direction});
            }
            else if (costs[sljedeci] == cost) {
                visited[sljedeci].push_back({0, i, j, direction});
            }
        }
    }
    return sum;
}

ll part2 (std::vector<std::string> lines) {
    ll sum = 0;
    std::set<std::pair<int,int>> coords;
    std::queue<node> red;
    red.push({0, goalI, goalJ, '>'});
    red.push({0, goalI, goalJ, 'v'});
    red.push({0, goalI, goalJ, '<'});
    red.push({0, goalI, goalJ, '^'});
    while (red.size() != 0) {
        int i = std::get<1>(red.front());
        int j = std::get<2>(red.front());
        int direction = std::get<3>(red.front());
        for (auto x : visited[{0, i, j, direction}]) {
            coords.insert({i,j});
            red.push(x);
        }
        red.pop();
    }
    sum = coords.size() + 1;
    return sum;
}

int main () {
    std::vector<std::string> linesFromInputFile = extractLinesFromInputFile("input.txt");
    ll part1result = part1(linesFromInputFile); std::cout << "\nPart 1: " << part1result << "\n";
    ll part2result = part2(linesFromInputFile); std::cout << "Part 2: " << part2result << "\n\n";
    return 0;
}
