#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <numeric>
#define ull long long int 

std::vector<std::string> extractLinesFromInputFile (std::string fileName) {
    std::ifstream inputFile(fileName);
    std::vector<std::string> lines;
    std::string inputLine;
    while(std::getline(inputFile, inputLine))
        lines.push_back(inputLine);
    return lines;
}
ull X = 101, Y = 103;
ull part1 (std::vector<std::string> lines) {
    ull sum = 0, M = lines.size();
    std::map<std::pair<ull,ull>,ull> coords;
    for (int i = 0; i < lines.size(); i++) {
        std::istringstream iss(lines[i]);
        int x, y, vx, vy;
        char c;
        iss >> c >> c >> x >> c >> y >> c >> c >> vx >> c >> vy;
        // std::cout << c << ' ' << x << ' ' << y << ' ' << vx << " " << vy <<'\n';

        int pomakpoX = 100 * vx,
            pomakpoY = 100 * vy;
        
        x += pomakpoX;
        y += pomakpoY;

        x %= X;
        y %= Y;

        x += X;
        y += Y;

        x %= X;
        y %= Y;

        coords[{x,y}]++;
        // std::cout << " konacna pozicija je " << x << ' ' << y << '\n';

        // break;



    }
    ull q1 = 0, q2 = 0, q3 = 0, q4 = 0;
    std::ofstream fs("output.txt");
    std::vector<std::string> a;
    for (int i = 0; i < Y; i++)
        a.push_back(std::string(X, '.'));
    for (auto [key, val] : coords) {
        a[key.first][key.second] = val; 
        
        if (key.first == (X-1) / 2 || key.second == (Y - 1) / 2)
            continue;
        // std::cout << key.first << ',' << key.second << ' ' << val << '\n';
        if (key.first < (X-1) / 2 && key.second < (Y-1) / 2)
            q1 += val;
        if (key.first < (X-1) / 2 && key.second > (Y-1) / 2)
            q2 += val;
        if (key.first > (X-1) / 2 && key.second < (Y-1) / 2)
            q3 += val;
        if (key.first > (X-1) / 2 && key.second > (Y-1) / 2)
            q4 += val;
    }
    // for (auto x : a){
    //     for (auto y : x)
    //         fs << y << ' ';
    //     fs << '\n';}
    sum = q1 * q2 * q3 * q4;
    // std::cout << q1 << ' ' << q2 << ' ' << q3 << ' ' << q4 << a.size() << ' ' << a[0].size();
    
    return sum;
}

ull part2 (std::vector<std::string> lines) {
    ull sum = 0, M = lines.size(); 
    std::map<std::pair<ull,ull>,ull> coords;
    std::ofstream fs("output.txt");
    std::vector<std::pair<std::pair<ull,ull>,std::pair<ull,ull>>> robots;
    std::vector<std::string> a;
    for (int i = 0; i < Y; i++)
        a.push_back(std::string(X, '.'));
    for (int i = 0; i < lines.size(); i++) {
        std::istringstream iss(lines[i]);
        ull x, y, vx, vy;
        char c;
        iss >> c >> c >> x >> c >> y >> c >> c >> vx >> c >> vy;
        // std::cout << c << ' ' << x << ' ' << y << ' ' << vx << " " << vy <<'\n';
        
        coords[{x,y}]++;
        a[x][y] = coords[{x,y}]; 
        robots.push_back({{x,y},{vx,vy}});
        // int pomakpoX = 100 * vx,
        //     pomakpoY = 100 * vy;
        
        // x += pomakpoX;
        // y += pomakpoY;

        // x %= X;
        // y %= Y;

        // x += X;
        // y += Y;

        // x %= X;
        // y %= Y;

        // std::cout << " konacna pozicija je " << x << ' ' << y << '\n';
        // break;
    }
    // ull q1 = 0, q2 = 0, q3 = 0, q4 = 0;
    

    for (int i = 0; i < 10000; i++) {
        // if (i % 2000 == 0)
        //     fs << "\n FOR i = " << i << " positions: \n";
        // if (i > 499 ) 
        
        for (auto &r : robots) {
            coords[{r.first.first,r.first.second}]--;

            r.first.first += r.second.first;
            r.first.second += r.second.second;

            r.first.first %= X;
            r.first.second %= Y;
            
            r.first.first += X;
            r.first.second += Y;

            r.first.first %= X;
            r.first.second %= Y;

            coords[{r.first.first,r.first.second}]++;
        }
        for (auto [key, val] : coords)
            if (val == 0)
                a[key.first][key.second] = '.';
            else a[key.first][key.second] = '#';
        int count = 0;
        for (int k = 20; k < 80; k++) {
            for (int l = 20; l < 80; l++) {
                if (a[k][l] == '#')
                    count++;
            } 
        }
        if (count > 300){
            fs << "\n for blinks = " << i + 1 << " positions are: \n";
            for (auto x : a) {
                for (auto y : x)
                    fs << y ;
                fs << '\n';
            }
            sum = i + 1;
            break;
        }
    }
    
    // for (auto [key, val] : coords) {
    //     if (key.first == (X-1) / 2 || key.second == (Y - 1) / 2)
    //         continue;
    //     // std::cout << key.first << ',' << key.second << ' ' << val << '\n';
    //     if (key.first < (X-1) / 2 && key.second < (Y-1) / 2)
    //         q1 += val;
    //     if (key.first < (X-1) / 2 && key.second > (Y-1) / 2)
    //         q2 += val;
    //     if (key.first > (X-1) / 2 && key.second < (Y-1) / 2)
    //         q3 += val;
    //     if (key.first > (X-1) / 2 && key.second > (Y-1) / 2)
    //         q4 += val;
    // }
    
    // sum = q1 * q2 * q3 * q4;
    // std::cout << q1 << ' ' << q2 << ' ' << q3 << ' ' << q4 << a.size() << ' ' << a[0].size();
    
    return sum;
}

int main () {
    std::vector<std::string> linesFromInputFile = extractLinesFromInputFile("input.txt");
    ull part1result = part1(linesFromInputFile); std::cout << "\nPart 1: " << part1result << "\n";
    ull part2result = part2(linesFromInputFile); std::cout << "Part 2: " << part2result << "\n\n";
    return 0;
}
