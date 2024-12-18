#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <numeric>
#include <bitset>
#define ull unsigned long long int 

std::vector<std::string> extractLinesFromInputFile (std::string fileName) {
    std::ifstream inputFile(fileName);
    std::vector<std::string> lines;
    std::string inputLine;
    while(std::getline(inputFile, inputLine))
        lines.push_back(inputLine);
    return lines;
}

int printForA (ull A) {
    ull B = A % 8;
    B = B ^ 1;
    ull C = A >> B;
    B = B ^ 5;
    B = B ^ C;
    return B % 8;
}

std::string part1 (std::vector<std::string> lines, ull Apt2 = 0) {
    ull sum = 0; 
    std::istringstream iss2(lines[0].substr(12));
    ull A;
    iss2 >> A;
    if (Apt2 != 0)
        A = Apt2;
    ull B = std::stoi(lines[1].substr(12));
    ull C = std::stoi(lines[2].substr(12));
    std::istringstream iss(lines[4].substr(9));
    std::vector<ull> ins;
    while (!iss.eof()) {
        ull num;
        char c;
        iss >> num >> c;
        ins.push_back(num);
    }
    ull N = ins.size();
    bool halt = false;
    ull i = 0;
    std::ofstream fs("output.txt");
    std::stringstream out;
    while (!halt) {
        ull instruction = ins[i];
        ull operand = ins[i + 1];
        if (operand == 4)
            operand = A;
        else if (operand == 5)
            operand = B;
        else if (operand == 6)
            operand = C;
        switch (instruction) {
            case 0: A = A >> operand; break;
            case 1: B = B ^ ins[i + 1]; break;
            case 2: B = operand % 8; break;
            case 3: if (A != 0) i = ins[i + 1] - 2; break;
            case 4: B = B ^ C; break;
            case 5: out << operand % 8 << ','; break;
            case 6: B = A >> operand;break;
            case 7: C = A >> operand; break;
        }
        i += 2;
        if (i >= N)
            halt = true;
    }
    std::string output = out.str();
    output.resize(output.size() - 1);
    return output;
}

ull part2 (std::vector<std::string> lines) {
    ull sum = 0; 
    ull B = std::stoi(lines[1].substr(12));
    ull C = std::stoi(lines[2].substr(12));
    std::istringstream iss(lines[4].substr(9));
    std::vector<int> ins;
    while (!iss.eof()) {
        int num;
        char c;
        iss >> num >> c;
        ins.push_back(num);
    }
    ull inInt = 0;
    std::string inString;
    for (auto x : ins) {
        inString.append(std::string(1, char(x + '0')));
        inInt *= 10;
        inInt += x;
    }
    int N = ins.size();
    std::ofstream fs("output.txt");
    ull AA, A, i, halt, s, instruction, operand;
    std::string outString(inString.size(), ' ');
    sum = AA;
    ull Aa = 0;
    for (int i = ins.size() - 1; i >= 0; i--)
        for (int j = 0; j < 8; j++)
            if (ins[i] == printForA((Aa << 3) + j)) {
                Aa = (Aa << 3) + j;
                break;
            }
    Aa = Aa << 3;
    for (; ; Aa++)
        if (part1(lines, Aa).compare("2,4,1,1,7,5,1,5,4,3,5,5,0,3,3,0") == 0)
            return Aa;
    return sum;
}

int main () {
    std::vector<std::string> linesFromInputFile = extractLinesFromInputFile("input.txt");
    std::string part1result = part1(linesFromInputFile); std::cout << "\nPart 1: " << part1result << "\n";
    ull part2result = part2(linesFromInputFile); std::cout << "Part 2: " << part2result << "\n\n";
    return 0;
}
