#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <set>

std::vector<std::string> extractLinesFromInputFile (std::string fileName) {
    std::ifstream inputFile(fileName);
    std::vector<std::string> lines;
    std::string inputLine;
    while(std::getline(inputFile, inputLine))
        lines.push_back(inputLine);
    return lines;
}

int part1 (std::vector<std::string> m) {
    int i, j, sum = 1;
    bool br = false;
    for ( i = 0;   i < m.size(); i++) {
        for ( j = 0; j < m.size(); j++) {
            if (m[i][j] == '^') {
                br = true;
                m[i][j] = 'O';
                break;
            }
        }
        if (br) break;
    }
            //std::cout << "nadjena poz " << i << " " << j << " \n";
    try {
        while (1) {
            //std::cout << "prva pet prij "<< i << " " << j << " \n";
            while (m.at(i - 1).at(j) == '.' || m.at(i - 1).at(j) == 'O') {
                m.at(i).at(j) = 'O';
                i--;
            }
            //std::cout << "prva pet " << i << " " << j << " \n";
            //std::cout << "prva pet " << m.at(i-1).at(j) << " " << (m.at(i - 1).at(j) == '.' || m.at(i - 1).at(j) == 'O') << " \n";
            while (m.at(i ).at(j + 1) == '.' || m.at(i ).at(j + 1) == 'O') {
                m.at(i).at(j) = 'O';
                j++;
            }
            while (m.at(i + 1).at(j) == '.' || m.at(i + 1).at(j) == 'O') {
                m.at(i).at(j) = 'O';
                i++;
            }
            while (m.at(i  ).at(j - 1) == '.' || m.at(i ).at(j - 1) == 'O') {
                m.at(i).at(j) = 'O';
                j--;
            }
            for (auto x : m) {
        // for (auto y : x)
            // //std::cout << y << ' ';
        // //std::cout << '\n';
    }
        }
    }
    catch (...) {
        //std::cout << "\n EXC" << i << j << "\n"; 

    }
    for (auto x : m) {
        for (auto y : x) {
            if (y == 'O') sum++;
            //std::cout << y << ' ';
        }
        //std::cout << '\n';
    }
    return sum;
}

bool isOk(std::vector<std::string> m, int i, int j) {
    for (auto x : "^>v<1234")
        if (m.at(i).at(j) == x)
            return true;
    return false;
}


int part2 ( std::vector<std::string> m) {
    int sum = 0, rulesSize = 0;
    int i, j;
    bool br = false;
    
    for ( i = 0;   i < m.size(); i++) {
        for ( j = 0; j < m.size(); j++) {
            if (m[i][j] == '^') {
                br = true;
                int k = i;
                while (k < m.size())
                    m[k++][j] = '^';
                while (i >= 1 && m[i-1][j] != '#')
                    m[i--][j] = '^';
                break;
            }
        }
        if (br) break;
    }
            // std::cout << "nadjena poz " << i << " " << j << " \n";
    int sum2 = 0;
    bool prva = true;
    try {
        while (1) {
            // std::cout << "prva pet prij "<< i << " " << j << " \n";
            while (m.at(i - 1).at(j) == '.' || isOk(m, i - 1, j) /*m.at(i - 1).at(j) == 'O'*/) {
                if (prva)
                    m.at(i).at(j) = '1';
                else 
                    m.at(i).at(j) = '^';
                if ((m.at(i).at(j + 1) == '>' || m.at(i).at(j + 1) == '3') && i > 0 && m.at(i - 1).at(j) == '.') {
                    sum2++;
                    //std::cout << "\nsum2++ za " << i << " " << j << "\n"; 
                }
                i--;
                prva = false;
            }
            // //std::cout << "prva pet " << i << " " << j << " \n";
            // std::cout << "prva pet " << m.at(i-1).at(j) << " " << (m.at(i - 1).at(j) == '.' || m.at(i - 1).at(j) == 'O') << " \n";
            prva = true;
            while (m.at(i ).at(j + 1) == '.' || isOk(m, i , j + 1) /*m.at(i ).at(j + 1) == 'O'*/) {
                if (prva)
                    m.at(i).at(j) = '2';
                else 
                    m.at(i).at(j) = '>';
                if ((m.at(i + 1).at(j ) == 'v' || m.at(i + 1).at(j ) == '4') && j < m.at(i).size() - 1 && m.at(i ).at(j + 1) == '.') {
                    sum2++;
                    //std::cout << "\nsum2++ za " << i << " " << j << "\n"; 
                }
                j++;
                prva = false;
            }
            prva = true;
            while (m.at(i + 1).at(j) == '.' || isOk(m, i + 1, j)/*m.at(i + 1).at(j) == 'O'*/) {
                if (prva)
                    m.at(i).at(j) = '3';
                else 
                    m.at(i).at(j) = 'v';
                if ((m.at(i ).at(j - 1) == '<' || m.at(i ).at(j - 1) == '1') && i < m.size() - 1 && m.at(i + 1).at(j) == '.') {
                    sum2++;
                    //std::cout << "\nsum2++ za " << i << " " << j << "\n"; 
                }
                i++;
                prva = false;
            }
            prva = true;
            while (m.at(i  ).at(j - 1) == '.' || isOk(m, i , j-1)/*m.at(i ).at(j - 1) == 'O'*/) {
                if (prva)
                    m.at(i).at(j) = '4';
                else 
                    m.at(i).at(j) = '<';
                if ((m.at(i - 1 ).at(j ) == '^' || m.at(i - 1 ).at(j ) == '2' ) && j > 0 && m.at(i).at(j-1) == '.') {
                    sum2++;
                    //std::cout << "\nsum2++ za " << i << " " << j << "\n"; 
                }
                j--;
                prva = false;
            }
            prva = true;
            for (auto x : m) {
        // for (auto y : x)
            // std::cout << y << ' ';
        // std::cout << '\n';
    }
        }
    }
    catch (...) {
        //std::cout << "\n EXC" << i << j << "\n"; 
    }
    for (auto x : m) {
        for (auto y : x) {
            if (y == '^' || y == '>' || y == 'v' || y == '<') sum++;
            //std::cout << y << ' ';
        }
        //std::cout << '\n';
    }
    return sum2;
}


int part11 (std::vector<std::string> m, std::vector<int>& x,std::vector<int>& y) {
    int i, j, sum = 1, rulesSize = 0;
    bool br = false;
    for ( i = 0;   i < m.size(); i++) {
        for ( j = 0; j < m.size(); j++) {
            if (m[i][j] == '^') {
                br = true;
                m[i][j] = 'O';
                break;
            }
        }
        if (br) break;
    }
            //std::cout << "nadjena poz " << i << " " << j << " \n";
    try {
        while (1) {
            //std::cout << "prva pet prij "<< i << " " << j << " \n";
            while (m.at(i - 1).at(j) == '.' || m.at(i - 1).at(j) == 'O') {
                m.at(i).at(j) = 'O';
                i--;
            }
            //std::cout << "prva pet " << i << " " << j << " \n";
            //std::cout << "prva pet " << m.at(i-1).at(j) << " " << (m.at(i - 1).at(j) == '.' || m.at(i - 1).at(j) == 'O') << " \n";
            while (m.at(i ).at(j + 1) == '.' || m.at(i ).at(j + 1) == 'O') {
                m.at(i).at(j) = 'O';
                j++;
            }
            while (m.at(i + 1).at(j) == '.' || m.at(i + 1).at(j) == 'O') {
                m.at(i).at(j) = 'O';
                i++;
            }
            while (m.at(i  ).at(j - 1) == '.' || m.at(i ).at(j - 1) == 'O') {
                m.at(i).at(j) = 'O';
                j--;
            }
            for (auto x : m) {
        // for (auto y : x)
            // std::cout << y << ' ';
        // std::cout << '\n';
    }
        }
    }
    catch (...) {
        //std::cout << "\n EXC" << i << j << "\n"; 
        m[i][j] = 'O';
    }
    for (int i = 0;   i < m.size(); i++) {
        for (int j = 0; j < m.size(); j++) {
            if (m[i][j] == 'O') {
                sum++;
                x.push_back(i);
                y.push_back(j);
            }
             //std::cout << m[i][j] << ' ';
        }
         //std::cout << '\n';
    }
    return sum;
}
int part22 (std::vector<std::string> mm) {
    int i, j, sum = 0, rulesSize = 0;
    bool br = false;
    for ( i = 0;   i < mm.size(); i++) {
        for ( j = 0; j < mm.size(); j++) {
            if (mm[i][j] == '^') {
                br = true;
                //mm[i][j] == 'O';
                break;
            }
        }
        if (br) break;
    }
            //std::cout << "nadjena poz " << i << " " << j << " \n";
    int posI = i, posJ = j;
    std::vector<int> x, y;
    part11(mm, x, y);
    //std::cout << " x size" <<  x.size();
    
    for (int a = 0; a < x.size(); a++) {

        int I = x[a], J = y[a];
        if (I == 6 && J == 4) std::cout << "\n UIMA\n";
            auto m = mm;
            if (m[I][J] == '#' || m[I][J] == '^')
                continue;
            else
                m[I][J] = 'O';
            m[posI][posJ] = '.';
            try {
                bool loop = false;
                i = posI;
                j = posJ;
                while (!loop) {
                    if (loop) break;
                    while (m.at(i - 1).at(j) == '.' || isOk(m, i - 1, j) /*m.at(i - 1).at(j) == 'O'*/) {
                        if (m.at(i).at(j) == '^') {
                            loop = true;
                            sum++;
                            break;
                        }
                        m.at(i).at(j) = '^';
                        i--;
                    }
                    if (loop) break;
                    while (m.at(i ).at(j + 1) == '.' || isOk(m, i , j + 1) /*m.at(i ).at(j + 1) == 'O'*/) {
                        if (m.at(i).at(j) == '>') {
                            loop = true;
                            sum++;
                            break;
                        }
                            m.at(i).at(j) = '>';
                        j++;
                    }
                    if (loop) break;
                    while (m.at(i + 1).at(j) == '.' || isOk(m, i + 1, j)/*m.at(i + 1).at(j) == 'O'*/) {
                        if (m.at(i).at(j) == 'v') {
                            loop = true;
                            sum++;
                            break;
                        }
                            m.at(i).at(j) = 'v';
                        i++;
                    }
                    if (loop) break;
                    while (m.at(i  ).at(j - 1) == '.' || isOk(m, i , j-1)/*m.at(i ).at(j - 1) == 'O'*/) {
                        if (m.at(i).at(j) == '<') {
                            loop = true;
                            sum++;
                            break;
                        }
                            m.at(i).at(j) = '<';
                        j--;
                    }
                    if (loop) break;
                }
                    if (loop) {
                        // std::cout << "\n O na poz " << I << " " <<  J << "\n";
                    } 
            }
            catch (...) {
                // std::cout << "\n EXC" << i << j << "\n"; 
            }
                        // for (auto x : m) {
                        //     for (auto y : x) {
                                
                        //         std::cout << y << ' ';
                        //     }
                        //     std::cout << '\n';
                        // }
            m[I][J] = '.';
        
    }
    return sum;
}


int main () {
    std::vector<std::string> linesFromInputFile = extractLinesFromInputFile("input.txt");
     int part1result = part1(linesFromInputFile); std::cout << "\nPart 1: " << part1result << "\n";
    int part2result = part22(linesFromInputFile); std::cout << "Part 2: " << part2result << "\n\n";
    return 0;
}
