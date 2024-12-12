#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <set>
#define ull unsigned long long int 

std::vector<std::string> extractLinesFromInputFile (std::string fileName) {
    std::ifstream inputFile(fileName);
    std::vector<std::string> lines;
    std::string inputLine;
    while(std::getline(inputFile, inputLine))
        lines.push_back(inputLine);
    return lines;
}

std::map<std::pair<ull,ull>, ull> coordsMap, edg;
ull edges = 0;

void calculate (const std::vector<std::string> &m, ull i, ull j) {
    char c = m[i][j];
    if (coordsMap.count({i,j}) == 1) {
        return;
    }
    coordsMap[{i, j}]++;
    if (m[i][j + 1] == c) {
        calculate(m, i, j + 1);
    }
    else {
        edges++;
        edg[{i, j + 1}]++;
    }
    if (m[i][j - 1] == c) {
        calculate(m, i, j - 1);
    }
    else {
        edges++;
        edg[{i, j - 1}]++;
    }
    if (m[i + 1][j] == c) {
        calculate(m, i + 1, j);
    }
    else {
        edges++;
        edg[{i + 1, j}]++;
    }
    if (m[i - 1][j] == c) {
        calculate(m, i - 1, j);
    }
    else {
        edges++;
        edg[{i - 1, j}]++;
    }
    
}

ull part1 (std::vector<std::string> m) {
    ull sum = 0, M = m.size(), N = m[0].size();
    std::vector<std::string> map(M+2, std::string(N+2, ' '));
    for (ull i = 0; i < M+2; i++) {
        for (ull j = 0; j < N+2; j++)
            if (i == 0 || i == M+1 || j == 0 || j == N+1)
                map[i][j] = '.';
            else
                map[i][j] = m[i-1][j-1];
    }
    for (ull i = 0; i < M+2; i++) {
        for (ull j = 0; j < N+2; j++) {
            if (map[i][j] == '.')
                continue;
            edges = 0;
            calculate(map, i, j);
            sum += edges * coordsMap.size();
            for (auto [key, val] : coordsMap)
                map[key.first][key.second] = '.';
            coordsMap.clear();
            edg.clear();
        }
    }
    return sum;
}

ull part2 (std::vector<std::string> m) {
    ull sum = 0, M = m.size(), N = m[0].size();
    std::vector<std::string> map(M+2, std::string(N+2, ' '));
    // std::multimap<char, std::set<ull, ull>> multimap;
    for (ull i = 0; i < M+2; i++) {
        for (ull j = 0; j < N+2; j++)
            if (i == 0 || i == M+1 || j == 0 || j == N+1)
                map[i][j] = '.';
            else
                map[i][j] = m[i-1][j-1];
    }
    std::ofstream fs("output1.txt");
    for (auto x : map) {
        for (auto y : x){
            fs << y ;
        }
        fs << '\n';
    }

    for (ull i = 0; i < M+2; i++) {
        for (ull j = 0; j < N+2; j++) {
            if (map[i][j] == '.')
                continue;
            edges = 0;
            calculate(map, i, j);
            for (auto [key, val] : coordsMap)
                map[key.first][key.second] = '#';
            
            ull k = i, l = j;
            // do {
            //     std::cout << k << ' ' << l << '\n';
            //     while (edg.count({k + 1, l}) == 1 /*map[k + 1][l] == '#'*/) {
            //         edges--;
            //         k++;
            //     }
            //     if (k == i && l == j)
            //         break;
            //     while (edg.count({k, l + 1}) == 1 /*map[k][l + 1] == '#'*/) {
            //         edges--;
            //         l++;
            //     }
            //     if (k == i && l == j)
            //         break;
            //     while (edg.count({k - 1, l}) == 1 /*map[k - 1][l] == '#'*/) {
            //         edges--;
            //         k--;
            //     }
            //     if (k == i && l == j)
            //         break;
            //     while (edg.count({k, l - 1}) == 1 /*map[k][l - 1] == '#'*/) {
            //         edges--;
            //         l--;
            //     }
            //     if (k == i && l == j)
            //         break;
            // }
            // while (!(k == i && l == j));
            auto mapCopy = map;
            for (auto [key, val] : edg) {
                // std::cout << key.first << ' ' << key.second << '\n';
                mapCopy[key.first][key.second] = '$';
            }

            // fs << " prva mapcopy \n";
            // for (auto x : mapCopy) {
            //     for (auto y : x){
            //         fs << y ;
            //     }
            //     fs << '\n';
            // }
            // fs << '\n';

            auto mapPrull = mapCopy;
            edges = 0;
            ull tmp = 0;
                for (ull k = 0; k < M+2; k++) {
                    for (ull l = 0; l < N+2; l++) {
                        if (mapCopy[k][l] == '#') {
                            if (mapCopy[k+1][l+0] == '$') {
                                edges++;
                                tmp++;
                                while (mapCopy[k][l] == '#' && mapCopy[k+1][l+0] == '$') {
                                    l++;
                                }
                            }
                        }
                    }
                }
                fs << " DONJA "<< tmp << '\n';
                tmp = 0;
                for (ull k = 0; k < M+2; k++) {
                    for (ull l = 0; l < N+2; l++) {
                        if (mapCopy[k][l] == '#') {
                            if (mapCopy[k-1][l+0] == '$') {
                                tmp++;
                                edges++;
                                while (mapCopy[k][l] == '#' && mapCopy[k-1][l+0] == '$') {
                                    l++;
                                }
                            }
                        }
                    }
                }
                fs << " GORNJA "<< tmp << '\n';
                tmp = 0;

                for (ull l = 0; l < N+2; l++) {
                    for (ull k = 0; k < M+2; k++) {
                        if (mapCopy[k][l] == '#') {
                            fs << " usao za " << k << " " << l << '\n';
                            if (mapCopy[k + 0][l + 1] == '$') {
                                mapPrull[k + 0][l + 1] = '0';
                                tmp++;
                                edges++;
                                while (mapCopy[k][l] == '#' && mapCopy[k + 0][l + 1] == '$') {
                                mapPrull[k + 0][l + 1] = '0';
                                    k++;
                                }
                            }
                        }
                    }
                }
                fs << " DESNA "<< tmp << '\n';
                tmp = 0;

                for (ull l = 0; l < N+2; l++) {
                    for (ull k = 0; k < M+2; k++) {
                        if (mapCopy[k][l] == '#') {
                            if (mapCopy[k][l] == '#' && mapCopy[k + 0][l - 1] == '$') {

                                tmp++;
                                edges++;
                                while (mapCopy[k][l] == '#' &&  mapCopy[k + 0][l - 1] == '$') {
                                    k++;
                                }
                            }
                        }
                    }
                }
                fs << " LIJEVA "<< tmp << '\n';
                tmp = 0;

            fs << "finalno " << edges << '\n';
            for (auto x : mapPrull) {
                for (auto y : x){
                    fs << y ;
                }
                fs << '\n';
            }
            
            sum += edges * coordsMap.size();
            fs << "dodajemo " << edges * coordsMap.size() << '\n';
            for (auto [key, val] : coordsMap)
                map[key.first][key.second] = '.';
            coordsMap.clear();
            edg.clear();
        }
    }
    return sum;
}
// 851300 TOO LOW



int main () {
    std::vector<std::string> m = extractLinesFromInputFile("input.txt");

    ull sum = 0, M = m.size(), N = m[0].size();
    std::vector<std::string> map(M+2, std::string(N+2, ' '));
    // std::multimap<char, std::set<ull, ull>> multimap;
    for (ull i = 0; i < M+2; i++) {
        for (ull j = 0; j < N+2; j++)
            if (i == 0 || i == M+1 || j == 0 || j == N+1)
                map[i][j] = '.';
            else
                map[i][j] = m[i-1][j-1];
    }
    auto linesFromInputFile = map;
    ull part1result = part1(linesFromInputFile); std::cout << "\nPart 1: " << part1result << "\n";
    ull part2result = part2(linesFromInputFile); std::cout << "Part 2: " << part2result << "\n\n";
    return 0;
}
