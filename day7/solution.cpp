#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <cmath>

std::vector<std::string> extractLinesFromInputFile (std::string fileName) {
    std::ifstream inputFile(fileName);
    std::vector<std::string> lines;
    std::string inputLine;
    while(std::getline(inputFile, inputLine))
        lines.push_back(inputLine);
    return lines;
}

#define ull unsigned long long
std::vector<ull> okVEC;
ull part1 (std::vector<std::string> m) {
    ull sum = 0;
    std::vector<std::vector<ull>> v;
    for (auto line : m) {
        std::istringstream iss(line);
        ull num;
        char c;
        iss >> num >> c;
        v.push_back({num});
        while (!iss.eof()) {
            iss >> num;
            v.at(v.size() - 1).push_back(num);
        }
    }

    for (int i = 0; i < v.size(); i++) {
        for (int k = 0; k < 2049; k++) {
            ull sumTemp = v[i][1];
            int pow = 1;
            for (int j = 2; j < v.at(i).size(); j++) {
                if ((k & pow) == pow) {
                    sumTemp += v[i][j];
                    //std::cout << "+";
                }
                else {
                    sumTemp *= v[i][j];
                  //  std::cout << "*";
                }
                pow *= 2;
            }
            if (sumTemp == v[i][0]){
                //std::cout << "\n";
                sum += sumTemp;
                okVEC.push_back(i);
                break;}
        }
    }

    return sum;
}

ull concat (ull a, ull b) {
    ull bb = b;
    if (b == 0)
        return a * 10;
    while (bb != 0) {
        a *= 10; 
        bb /= 10;
    }
    return a + b;
}

ull part22 (std::vector<std::string> m) {
    ull sum = 0;
    std::vector<std::vector<ull>> v;
    int j = 0;
    for (int i = 0; i < m.size(); i++) {
        if (okVEC.size() != 0 && okVEC[j] == i) {
            j++;
             continue;
        }
        std::istringstream iss(m[i]);
        ull num;
        char c;
        iss >> num >> c;
        v.push_back({num});
        while (!iss.eof()) {
            iss >> num;
            v.at(v.size() - 1).push_back(num);
        }
    }
    std::cout << v.size() << " v size \n";
    std::cout << okVEC.size() << " okvec siz \n";

    /*std::vector<std::string> op;

    /*ull combinations = std::pow(3, 11) + 1;
    for (int i = 0; i < combinations; i++) {
        ull granica = std::pow(2, 12);
        for (int k = 0; k < granica; k++) {
            int pow = 1;
            for (int j = 0; j < 13)
            
        }
    }*/

    int max = 0;

    for (int i = 0; i < v.size(); i++) {
        if (max < v[i].size()) max = v[i].size();
        // std::cout << v[i][0] << "\n";
        ull granicae = std::pow(2, 11) + 1;
        for (int l = 1; l < granicae; l++) {
            bool ubacen = false;
            auto row = v[i];
            ull granica = std::pow(2, row.size() - 1);
            for (int k = 0; k < granica; k++) {
                ull sumTemp = row[1];
                int pow = 1;
                for (int j = 2; j < row.size(); j++) {
                    if ((l & pow) == pow) {
                        sumTemp = concat(sumTemp, row[j]);
                        //  std::cout << "||";
                          pow /= 2;
                    }
                    else if ((k & pow) == pow) {
                        sumTemp += row[j];
                        //  std::cout << ".";
                    }
                    else {
                        sumTemp *= row[j];
                        //  std::cout << "*";
                    }
                    pow *= 2;
                }
                //  std::cout << "sumtemp = " << sumTemp << "\n";
                if (sumTemp == row[0]){
                    //   std::cout << "ubacen " << sumTemp <<  "\n";
                    okVEC.push_back(i);
                    sum += sumTemp;
                    ubacen = true;
                    break;
                }
            }
            if (ubacen)
                break;
            // else std::cout << " nije ubacen " << v[i][0] << "\n";
        }
                 
    }
    std::cout << okVEC.size() << "again okvec\n";
    std::cout << max << "max\n";
    return sum + part1(m);
}

ull part2 (std::vector<std::string> m) {
    ull sum = 0;
    std::vector<std::vector<ull>> v;
    int j = 0;
    for (int i = 0; i < m.size(); i++) {
        if (okVEC.size() != 0 && okVEC[j] == i) {
            j++;
             continue;
        }
        std::istringstream iss(m[i]);
        ull num;
        char c;
        iss >> num >> c;
        v.push_back({num});
        while (!iss.eof()) {
            iss >> num;
            v.at(v.size() - 1).push_back(num);
        }
    }
    std::cout << v.size() << " v size \n";
    std::cout << okVEC.size() << " okvec siz \n";
    for (int i = 0; i < v.size(); i++) {
        ull granica = std::pow(2, v[i].size() - 2);
        for (int l = 1; l < granica; l++) {
            bool ubacen = false;
            auto row = v[i];
            for (int k = 0; k < granica; k++) {
                ull sumTemp = row[1];
                int pow = 1;
                for (int j = 2; j < row.size(); j++) {
                    if ((l & pow) == pow) {
                        sumTemp = concat(sumTemp, row[j]);
                        //  std::cout << "|";
                        //   pow /= 2;
                    }
                    else if ((k & pow) == pow) {
                        sumTemp += row[j];
                        //  std::cout << ".";
                    }
                    else {
                        sumTemp *= row[j];
                        //  std::cout << "*";
                    }
                    pow *= 2;
                }
                //  std::cout << "sumtemp = " << sumTemp << "\n";
                if (sumTemp == row[0]){
                    //   std::cout << "ubacen " << sumTemp <<  "\n";
                    okVEC.push_back(i);
                    sum += sumTemp;
                    ubacen = true;
                    break;
                }
            }
            if (ubacen)
                break;
            // else std::cout << " nije ubacen " << v[i][0] << "\n";
        }
                 
            if (i % 100 == 0)
                std::cout << i << '\n'; 
    }
    std::cout << okVEC.size() << "again okvec\n";
    return sum + part1(m);
}

// 102141982350391
// 18446744073709551615 
// 102164190506999 ISTO TOO LOW
// 102139889341265
// 219942158253698 OPET TOO LOW WHAT
// 637696070419031

int main () {
    std::vector<std::string> linesFromInputFile = extractLinesFromInputFile("input.txt");
    ull part1result = part1(linesFromInputFile); std::cout << "\nPart 1: " << part1result << "\n";
    ull part2result = part2(linesFromInputFile); std::cout << "Part 2: " << part2result << "\n\n";
    //  std::cout << concat(10, 0);
    return 0;
}
