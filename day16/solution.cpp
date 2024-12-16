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
std::set<ll> pathPrices;
std::set<ll> costs;


// takestep al da ide prvo ondje gdje je najjeftinije skrooz, pa kad ne moze tek onda se vraca nazad
void takeStep2 (const std::vector<std::string> &m, int i, int j, char direction, std::set<std::pair<int,int>> visited, ll cost) {
    // std::cout << "usao u takestep " << i << ' ' << j << "\n";
    if (cost > *costs.begin()) {
        
    }
    if (cost > *pathPrices.begin())
        return;
    std::cout << i << ' ' << j << '\n';
    visited.insert({i,j});
    if (i == goalI && j == goalJ) {
        pathPrices.insert(cost);
        std::cout << cost << " ubaceno\n";
        return;
    }
    if (m[i + 1][j] == '.' && direction == 'v' && visited.find({i + 1, j}) == visited.end()) {
        takeStep2(m, i + 1, j, 'v', visited, cost + 1);
    }
    else if (m[i - 1][j] == '.' && direction == '^' && visited.find({i - 1, j}) == visited.end()) {
        takeStep2(m, i - 1, j, '^', visited, cost + 1);
    }
    else if (m[i][j + 1] == '.' && direction == '>' && visited.find({i, j + 1}) == visited.end()) {
        takeStep2(m, i, j + 1, '>', visited, cost + 1);
    }
    else if (m[i][j - 1] == '.' && direction == '<' && visited.find({i, j - 1}) == visited.end()) {
        takeStep2(m, i, j - 1, '<', visited, cost + 1);
    }

    if (m[i + 1][j] == '.' && direction != 'v' && direction != '^' && visited.find({i + 1, j}) == visited.end()) {
        takeStep2(m, i + 1, j, 'v', visited, cost + 1001);
    }
    else if (m[i - 1][j] == '.' && direction != '^' && direction != 'v' && visited.find({i - 1, j}) == visited.end()) {
        takeStep2(m, i - 1, j, '^', visited, cost + 1001);
    }
    else if (m[i][j + 1] == '.' && direction != '>' && direction != '<' && visited.find({i, j + 1}) == visited.end()) {
        takeStep2(m, i, j + 1, '>', visited, cost + 1001);
    }
    else if (m[i][j - 1] == '.' && direction != '<' && direction != '>' && visited.find({i, j - 1}) == visited.end()) {
        takeStep2(m, i, j - 1, '<', visited, cost + 1001);
    }
    
}

int counter = 0;
void takeStep (const std::vector<std::string> &m, int i, int j, char direction, std::set<std::pair<int,int>> visited, ll cost) {
    // prima trenutnu poziciju i direction, gleda okolo gdje moze ici, i poziva opet take step u svaku tacku koju moze ici
    // kad naidje na dead end vraca -1, kad naidje na goal vraca koliko kosta
    //
    // std::cout << " usao u take step coords " << i << ' ' << j << '\n';
    if (cost > *pathPrices.begin())
        return;
    visited.insert({i,j});
    if (i == goalI && j == goalJ) {
        pathPrices.insert(cost);
        std::cout << cost << " ubaceno\n";
        return;
    }
    // counter++;
    // std::cout << counter <<'\n';
    if (m[i + 1][j] == '.' && direction != '^' && visited.find({i + 1, j}) == visited.end()) {
        // std::cout << " 1 IF usao " << i << ' ' << j << '\n';
        // ovdje ce uci samo ><v, za v je cost 1, za >< je cost 1000 jer skrecu tu
        if (direction == 'v') {
            takeStep(m, i + 1, j, 'v', visited, cost + 1);
        }
        else {
            // ovdje ce uci > i <
            takeStep(m, i + 1, j, 'v', visited, cost + 1001);
        }
    }
    if (m[i - 1][j] == '.' && direction != 'v' && visited.find({i - 1, j}) == visited.end()) {
        // std::cout << " 2 IF usao " << i << ' ' << j << '\n';
        // ovdje ce uci samo ><v, za v je cost 1, za >< je cost 1000 jer skrecu tu
        if (direction == '^') {
            takeStep(m, i - 1, j, '^', visited, cost + 1);
        }
        else {
            // ovdje ce uci > i <
            takeStep(m, i - 1, j, '^', visited, cost + 1001);
        }
    }
    if (m[i][j + 1] == '.' && direction != '<' && visited.find({i, j + 1}) == visited.end()) {
        // std::cout << " 3 IF usao " << i << ' ' << j << '\n';
        // ovdje ce uci samo ><v, za v je cost 1, za >< je cost 1000 jer skrecu tu
        if (direction == '>') {
            takeStep(m, i, j + 1, '>', visited, cost + 1);
        }
        else {
            // ovdje ce uci > i <
            takeStep(m, i, j + 1, '>', visited, cost + 1001);
        }
    }
    if (m[i][j - 1] == '.' && direction != '>' && visited.find({i, j - 1}) == visited.end()) {
        // std::cout << " 4 IF usao " << i << ' ' << j << '\n';
        if (direction == '<') {
            takeStep(m, i, j - 1, '<', visited, cost + 1);
        }
        else {
            takeStep(m, i, j - 1, '<', visited, cost + 1001);
        }
    }
    // std::cout << "\n ovdje izasao" << counter << ' ' << i << ' ' << j << '\n';
    // counter--;
}

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
    //std::cout << m[I][J] << " je na poziciji " << I << ' ' << J << '\n';
    //std::cout << m[goalI][goalJ] << " je na poziciji " << goalI << ' ' << goalJ << '\n';
    m[goalI][goalJ] = '.';
    
    // node: cost, pa koordinate i, j, pa direction
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
        //std::cout << cost << ' ' << i << ' ' << j << ' '<< direction << '\n';
        if (i == goalI && j == goalJ){
            //std::cout << red.size() << " size\n";
            
            // for (auto [key, val] : visited) {
                // for (auto x : val)
                    // std::cout << std::get<1>(x) << ' ' << std::get<2>(x) << '\n';
                // std::cout << '\n';
                // m[std::get<1>(x)][std::get<2>(x)] = 'O';
            // }
            // for (auto [key, val] : visited) {
            //     std::cout << std::get<1>(key) << ' ' << std::get<2>(key) << '\n';
            //     m[std::get<1>(key)][std::get<2>(key)] = 'O';
                
            // }
            // for (auto x : m) {
            //         for (auto y : x) {
            //             std::cout << y << ' ';
            //         }
            //         std::cout << '\n';
            //     }
            sum = cost;
            break;
        }
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

    
    // pathPrices.insert(10000000000);
    // takeStep2(m, I, J, '>', {}, 0);
    // sum = *pathPrices.begin();
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
