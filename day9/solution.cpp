#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <set>
#define ull unsigned long long 

std::vector<std::string> extractLinesFromInputFile (std::string fileName) {
    std::ifstream inputFile(fileName);
    std::vector<std::string> lines;
    std::string inputLine;
    while(std::getline(inputFile, inputLine))
        lines.push_back(inputLine);
    return lines;
}

ull part1 (std::vector<std::string> m) {
    std::vector<ull> line;
    for (auto x : m[0])
        line.push_back(x - '0');
    line.push_back(0);
    ull sum = 0, memSize = 0, N = line.size();
    for (auto x : line) {
        memSize += x;
    }
    std::vector<ull> IDs, freeSpaces;
    for (ull i = 0; i < N; i += 2) { 
        IDs.push_back(line[i]);
        freeSpaces.push_back(line[i + 1]);
    }
    // std::cout << "IDs: ";
    // for (auto x : IDs)
    //     std::cout << x << ' ';
    // std::cout << "\nspc: "; 
    // for (auto x : freeSpaces)
    //     std::cout << x << ' ';
    // std::cout << '\n';
    ull i = 0, idPos = 0, spacePos = 0, idInsPos = IDs.size() - 1;    
    while (true) {
        while (IDs[idPos] != 0) {
            if (idPos > idInsPos){
                // std::cout << "a\n"; 
                // std::cout << "\n 1: break za idpos " << idPos << " idInsPos " << idInsPos << '\n';
                break;
            }
            sum += i * idPos;
            // std::cout << "1: " << i << " * " << idPos << '\n';
            i++;
            IDs[idPos]--;
        }
        idPos++;
        while (freeSpaces[spacePos] != 0) {
            if (idPos > idInsPos){
                // std::cout << "a\n"; 
                break;
            }
            
            sum += i * idInsPos;
            // memSize--;
            // std::cout << "2: " << i << " * " << idInsPos << '\n';
            i++;
            IDs[idInsPos]--;
            freeSpaces[spacePos]--;
            if (IDs[idInsPos] == 0)
                idInsPos--;
        }
        spacePos++;
        if (/*memSize == i-1 ||*/ idPos == IDs.size()){
            // std::cout << "\n SVE break za " << i - 1<< "  " << memSize << '\n';
            // sum -= (i - 1) * idInsPos;
            break;
        }
    }
    // 64450702 too low
    // 1195323826 too low
    // 2147483647

    // for (ull i = 0; i < N / 2; i += 2) {
    //     x1 = line[i];
    //     x2 = line[i + 1];
    //     y1 = line[N - 1 - i - 1];
    //     y2 = line[N - 1 - i];

    //     std::cout << x1 << ' ' << x2 << ' ' << y1 << ' ' << y2 << '\n';
// 0099811188827773336446555566..............

    // }
    
    return sum;
}

ull part22 (std::vector<std::string> m) {
    std::vector<ull> line;
    for (auto x : m[0])
        line.push_back(x - '0');
    line.push_back(0);
    ull sum = 0, memSize = 0, N = line.size();
    for (auto x : line) {
        memSize += x;
    }
    std::vector<ull> IDs, freeSpaces;
    for (ull i = 0; i < N; i += 2) { 
        IDs.push_back(line[i]);
        freeSpaces.push_back(line[i + 1]);
    }
    std::cout << "IDs: ";
    for (auto x : IDs)
        std::cout << x << ' ';
    std::cout << "\nspc: "; 
    for (auto x : freeSpaces)
        std::cout << x << ' ';
    std::cout << '\n';
    
// IDs: 2 3 1 3 2 4 4 3 4 2 
// spc: 3 3 3 1 1 1 1 1 0 0
// 2 3 1 3 2 4 4 3 4 2
// 1 3 3 1 1 1 1 1 2 0
// 
// 2 3 1 3 0 4 4 0 4 0
// 1 0 3 1 4 1 1 1 2 0
// 
// 

// 00...111...2...333.44.5555.6666.777.888899
// 0099.111...2...333.44.5555.6666.777.8888..
// 0099.1117772...333.44.5555.6666.....8888..
// 0099.111777244.333....5555.6666.....8888..
// 00992111777.44.333....5555.6666.....8888..
    ull i = 0, idPos = 0, spacePos = 0, idInsPos = IDs.size() - 1;    
    int c = 0;
    while (c++ < 5) {
        std::cout << "-------iteracija c = " << c << "\n";
        while (IDs[idPos] != 0) {
            sum += i * idPos;
            std::cout << "1: " << i << " * " << idPos << '\n';
            i++;
            IDs[idPos]--;
        }
        idInsPos = IDs.size() - 1;
        //while ()
        spacePos = 0;

        while (IDs[idInsPos] > freeSpaces[spacePos]) {

        }



        idPos++; // PROVJERI KAD IDE
    }

    while (false && c++ < 1) {
        while (IDs[idPos] != 0) {
            sum += i * idPos;
            std::cout << "1: " << i << " * " << idPos << '\n';
            i++;
            IDs[idPos]--;
        }
        idPos++;
        std::cout << "ID POS JE " << idPos << "\n";
        while (true) {
            idInsPos = IDs.size() - 1;
            while (IDs[idInsPos] == 0 || IDs[idInsPos] > freeSpaces[idPos - 1]) {
                idInsPos--;
            }
            // idInsPos++;
            std::cout << "IDs[id ins pos] " << IDs[idInsPos] << " idInspos " << idInsPos << '\n';

                // ovdje ulazi kad se moze ubacit
            if (IDs[idInsPos] <= freeSpaces[idPos - 1]) {
                 freeSpaces[idInsPos] += IDs[idInsPos];
                std::cout << " moze se ubacit IDs[idInsPos] " << IDs[idInsPos] << " freespaces[idPos - 1] " << freeSpaces[idPos - 1] << "  idpos-1 je " << idPos - 1 <<  '\n' ;
                freeSpaces[idPos - 1] -= IDs[idInsPos]; // ??? ne treba uvijek i ovo premjesteno u ids stavit 0
                std::cout << " nakon oduzimanja freespace[idPos - 1] " << freeSpaces[idPos - 1] << "\n";

                while (IDs[idInsPos] != 0) {
                    sum += i * idInsPos;
                    std::cout << "2: " << i << " * " << idInsPos << '\n';
                    i++;
                    IDs[idInsPos]--;
                }

                if (freeSpaces[idPos - 1] == 0) {
                    spacePos++;
                    break;
                }

            }
            else {
                //i+=freeSpaces[spacePos];
                // spacePos++;
                break;
            }
            std::cout << "\n\n";
        }
        
    }


    
    while (false) {
        while (IDs[idPos] != 0) {
            if (idPos > idInsPos){
                std::cout << "a\n"; 
                std::cout << "\n 1: break za idpos " << idPos << " idInsPos " << idInsPos << '\n';
                break;
            }
            sum += i * idPos;
            std::cout << "1: " << i << " * " << idPos << '\n';
            i++;
            IDs[idPos]--;
        }
        idPos++;
        while (freeSpaces[spacePos] != 0) {
            if (idPos > idInsPos){
                std::cout << "a\n"; 
                break;
            }
            
            sum += i * idInsPos;
            // memSize--;
            std::cout << "2: " << i << " * " << idInsPos << '\n';
            i++;
            IDs[idInsPos]--;
            freeSpaces[spacePos]--;
            if (IDs[idInsPos] == 0)
                idInsPos--;
        }
        spacePos++;
        if (/*memSize == i-1 ||*/ idPos == IDs.size()){
            std::cout << "\n SVE break za " << i - 1<< "  " << memSize << '\n';
            // sum -= (i - 1) * idInsPos;
            break;
        }
    }
    
    return sum;
}

ull part2 (std::vector<std::string> m) {
    std::vector<ull> line;
    for (auto x : m[0])
        line.push_back(x - '0');
    line.push_back(0);
    ull sum = 0, memSize = 0, N = line.size();
    for (auto x : line) {
        memSize += x;
        // std::cout << x << ' ';
    }
    std::vector<int> vec(memSize);
    int v = 0;
    for (int i = 0; i < N; i += 2) {
        while (line[i] != 0) {
            vec[v] = i / 2;
            line[i]--;
            v++;
        }
        while (line[i+1] != 0) {
            vec[v] = - 1;
            line[i+1]--;
            v++;
        }
    } 
    // for (auto x : vec)
    //     if (x == -1)
    //         std::cout << ". ";
    //     else 
    //         std::cout << x << ' ';
    // std::cout  << "\n\n";
    int j, k, freeSpaceSize, c = 0;
    for (int i = vec.size() - 1; i >=0; ) {
        // std::cout << " i " << i << '\n';
        j = i;
        while (vec[i] == vec[j]) {
            j--;
        }

        bool tooBig = false;
        k = 0;
        while (!tooBig) {
            while (vec[k] != -1) {
                k++;
            }
            freeSpaceSize = 0;
            while (vec[k] == -1) {
                k++;
                freeSpaceSize++;
            }
            if (k <= i && freeSpaceSize >= i - j) {
                // std::cout << "k " << k << " freespace " << freeSpaceSize << ' ' << i << "\n";
                k -= freeSpaceSize;
                int l = i, temp = vec[i];
                int count = 0;
                
                while (k <= i && vec[l] == temp) {
                    // std::cout << " vec l " << vec[l] << " vec i" << vec[i] << '\n';
        //             for (auto x : vec)
        //     if (x == -1)
        //         std::cout << ". ";
        //     else 
        //         std::cout << x << ' ';
        // std::cout  << "\n\n";
                    vec[k] = vec[l];
                    vec[l] = -1;
                    k++;
                    l--;
                    i--;
                }
                    // std::cout << " vec l " << vec[l] << " vec i" << vec[i] << '\n';
                break;
            }
            if (k > i)
                tooBig = true;
        }
        // std::cout << " nakon breaka i je " << i  << '\n';
        if (tooBig){
            //  std::cout << "too big za i " << i << " j " << j << '\n';
            i -= i-j;
        
        }

        // for (auto x : vec)
        //     if (x == -1)
        //         std::cout << ". ";
        //     else 
        //         std::cout << x << ' ';
        // std::cout  << "\n\n";

        // if (c++ == 3)
        //     break;

    // 6547228390670 TOO HIGH AAAAAAAAAAAA
    // 6519155389266
        
    }

    for (int i = 0; i < memSize; i++) {
        if (vec[i] != -1){
            sum += i * vec[i];
            
            // std::cout << i << ' ' << vec[i] << ' ' << i * vec[i] <<  '\n';
        }
    }
        
// 00...111...2...333.44.5555.6666.777.888899
// 0099.111...2...333.44.5555.6666.777.8888..
// 0099.1117772...333.44.5555.6666.....8888..
// 0099.111777244.333....5555.6666.....8888..
// 00992111777.44.333....5555.6666.....8888..
    return sum;
}
int main () {
    std::vector<std::string> linesFromInputFile = extractLinesFromInputFile("input.txt");
    ull part1result = part1(linesFromInputFile); std::cout << "\nPart 1: " << part1result << "\n";
    ull part2result = part2(linesFromInputFile); std::cout << "Part 2: " << part2result << "\n\n";
    return 0;
}
