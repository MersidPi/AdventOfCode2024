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
    for (auto x : line)
        memSize += x;
    std::vector<ull> IDs, freeSpaces;
    for (ull i = 0; i < N; i += 2) { 
        IDs.push_back(line[i]);
        freeSpaces.push_back(line[i + 1]);
    }
    ull i = 0, idPos = 0, spacePos = 0, idInsPos = IDs.size() - 1;    
    while (true) {
        while (IDs[idPos] != 0) {
            if (idPos > idInsPos)
                break;
            sum += i * idPos;
            i++;
            IDs[idPos]--;
        }
        idPos++;
        while (freeSpaces[spacePos] != 0) {
            if (idPos > idInsPos)
                break;
            sum += i * idInsPos;
            i++;
            IDs[idInsPos]--;
            freeSpaces[spacePos]--;
            if (IDs[idInsPos] == 0)
                idInsPos--;
        }
        spacePos++;
        if (idPos == IDs.size())
            break;
    }
    return sum;
}

ull part2 (std::vector<std::string> m) {
    std::vector<ull> line;
    for (auto x : m[0])
        line.push_back(x - '0');
    line.push_back(0);
    ull sum = 0, memSize = 0, N = line.size();
    for (auto x : line)
        memSize += x;
    std::vector<int> vec(memSize);
    int v = 0;
    for (int i = 0; i < N; i += 2) {
        while (line[i] != 0) {
            vec[v] = i / 2;
            v++;
            line[i]--;
        }
        while (line[i+1] != 0) {
            vec[v] = - 1;
            v++;
            line[i+1]--;
        }
    }
    int j, k, freeSpaceSize, c = 0;
    for (int i = vec.size() - 1; i >=0; ) {
        j = i;
        while (vec[i] == vec[j])
            j--;

        bool tooBig = false;
        k = 0;
        while (!tooBig) {
            while (vec[k] != -1)
                k++;
            freeSpaceSize = 0;
            while (vec[k] == -1) {
                k++;
                freeSpaceSize++;
            }
            if (k <= i && freeSpaceSize >= i - j) {
                k -= freeSpaceSize;
                int l = i, temp = vec[i];
                int count = 0;
                while (k <= i && vec[l] == temp) {
                    vec[k] = vec[l];
                    vec[l] = -1;
                    k++;
                    l--;
                    i--;
                }
                break;
            }
            if (k > i)
                tooBig = true;
        }
        if (tooBig)
            i -= i - j;
    }
    for (int i = 0; i < memSize; i++)
        if (vec[i] != -1)
            sum += i * vec[i];
    return sum;
}

int main () {
    std::vector<std::string> linesFromInputFile = extractLinesFromInputFile("input.txt");
    ull part1result = part1(linesFromInputFile); std::cout << "\nPart 1: " << part1result << "\n";
    ull part2result = part2(linesFromInputFile); std::cout << "Part 2: " << part2result << "\n\n";
    return 0;
}
