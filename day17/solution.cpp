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

int pow2(int x) {
    int result = 1;
    while (x-- != 0)
        result *= 2;
    return result;
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
    // for (auto x : ins)
    //     std::cout << x << ' ';
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
        // std::cout << operand << '\n';
        // std::cout << " TEST i = " << i  << ' ' << ins[i] << ' ' << ins[i+1] << ' ' << A << ' ' << B << ' ' << C << '\n'; 
        switch (instruction) {
            case 0: A = A / pow2(operand); break;
            case 1: B = B ^ ins[i+1]; break;
            case 2: B = operand % 8; break;
            case 3: if (A != 0) i = ins[i+1] - 2; break;
            case 4: B = B ^ C; break;
            case 5: out << operand % 8 << ','; break;
            case 6: B = A / pow2(operand);break;
            case 7: C = A / pow2(operand);break;
        }
        i += 2;
        if (i >= N)
            halt = true;
    }
    std::string output = out.str();
    output.resize(output.size() - 1);
    return output;
}
    std::ofstream fs("output.txt");

ull part1COPY (std::vector<std::string> lines, ull A) {
    ull sum = 0; 
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
    // for (auto x : ins)
    //     std::cout << x << ' ';
    ull N = ins.size();
    bool halt = false;
    ull i = 0;
    //std::ofstream fs("output.txt");
    while (!halt) {
        ull instruction = ins[i];
        ull operand = ins[i + 1];
        if (operand == 4)
            operand = A;
        else if (operand == 5)
            operand = B;
        else if (operand == 6)
            operand = C;
        // std::cout << operand << '\n';
        // std::cout << " TEST i = " << i  << ' ' << ins[i] << ' ' << ins[i+1] << ' ' << A << ' ' << B << ' ' << C << '\n'; 
        switch (instruction) {
            case 0: A = A / pow2(operand); break;
            case 1: B = B ^ ins[i+1]; break;
            case 2: B = operand % 8; break;
            case 3: if (A != 0) i = ins[i+1] - 2; break;
            case 4: B = B ^ C; break;
            case 5: fs << operand % 8 << ','; std::cout << operand % 8<<','; break;
            case 6: B = A / pow2(operand);break;
            case 7: C = A / pow2(operand);break;
        }

        i += 2;
        if (i >= N)
            halt = true;
    }
    fs << '\n';
    return sum;
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
        // std::cout << x << ' ';
        inString.append(std::string(1, char(x + '0')));
        inInt *= 10;
        inInt += x;
    }
    // std::cout << inString;
    int N = ins.size();
    std::ofstream fs("output.txt");
    ull AA, A, i, halt, s, instruction, operand;
    std::string outString(inString.size(), ' ');
    //  for (AA = 281474976710656 + 35184372088832; true || AA < 281474976710006560; AA += 35184372088832) {
    for (AA = 0; false && AA < 400; AA += 1) {
        // ull outInt = 0;
// 0       000000000 4                2411751543550330 1
// 1       000000001 4                2411751543550330 1
// 2       000000010 6                2411751543550330 1
// 3       000000011 7                2411751543550330 1
// 4       000000100 0                2411751543550330 1
// 5       000000101 1                2411751543550330 1
// 6       000000110 2                2411751543550330 1
// 7       000000111 3                2411751543550330 1
         A = AA;
         i = 0;
         halt = false;
         s = 0;
        while (!halt) {
             instruction = ins[i];
             operand = ins[i + 1];
            if (operand == 4)
                operand = A;
            else if (operand == 5)
                operand = B;
            else if (operand == 6)
                operand = C;
            // std::cout << operand << '\n';
            // std::cout << " TEST i = " << i  << ' ' << ins[i] << ' ' << ins[i+1] << ' ' << A << ' ' << B << ' ' << C << '\n'; 
            switch (instruction) {
                case 0: A = A / pow2(operand); break;
                case 1: B = B ^ ins[i+1]; break;
                case 2: B = operand % 8; break;
                case 3: if (A != 0) i = ins[i+1] - 2; break;
                case 4: B = B ^ C; break;
                case 5: 
                    // fs << operand % 8 << ','; 
                    // std::cout << "OUT: " << operand % 8<<'\n'; 
                    // outInt *= 10;
                    // outInt += operand % 8;
                    // outString.append(std::string(1, char((operand % 8) + '0')));
                    outString[s] = (operand % 8) + '0';
                    s++;
                    //if (s == inString.size())
                        // std::cout << " IMA SANSE " << AA << '\n';
                    break;
                case 6: B = A / pow2(operand);break;
                case 7: C = A / pow2(operand);break;
            }
            i += 2;
            if (i >= N)
                halt = true;
            // if (i >= N || s > outString.size() || s > 0 && outString[s - 1] != inString[s - 1])
            //     break;
        }
        if (inString.compare(outString) == 0)
            return AA;
        
        if (AA % 1 == 0){
            std::cout << AA << '\t';
            std::cout << std::bitset<9>(AA) << ' ';
            std::cout << outString << ' ' << inString << ' ' << s << '\n';
        }
        // if (outInt == inInt)
            // return A;
    }
    sum = AA;
    int digits[16] = {0};
    ull Aa = 0;
    int digit = 0;
    for (int i = ins.size() - 1; i >= 0; i--) {
        int numForPrint = ins[i];
        // std::cout << "numforprint " << ins[i] << '\n';
        bool breakao = false;
        for (int j = digit; j < 8; j++) {
            if (numForPrint == printForA((Aa << 3) + j)) {
                Aa = (Aa << 3) + j;
                digits[16 - i] = j;
                // std::cout << " u printfor a ide " << ((Aa << 3) + j) << '\n';
                breakao = true;
                break;
            }
        }
        // OVDJE BRATE VRATIS A ZA 3 UNAZAD PA ONDA POJACAS DIGIT NA 1 I OPET DOK NE BREAKA MOZE SE VLJD RAZRADIT OVA IDEJA BREAKANO ITD
        // if (!breakao) {
            // digit++;
            // i += 1;
        //    A >>= 3;
        // }
        // else {
            // digit = 0;
        // }
    }
    Aa = Aa << 3;
    // for (int i = 0; i < 16; i++)
    //     std::cout << digits[i] << ' ';
    // std::cout << '\n';
    for (; ; Aa++) {
        if (part1(lines, Aa).compare("2,4,1,1,7,5,1,5,4,3,5,5,0,3,3,0") == 0)
            return Aa;
    }
    return sum;
}

int main () {
    std::vector<std::string> linesFromInputFile = extractLinesFromInputFile("input.txt");
    std::string part1result = part1(linesFromInputFile); std::cout << "\nPart 1: " << part1result << "\n";
    ull part2result = part2(linesFromInputFile); std::cout << "Part 2: " << part2result << "\n\n";
    // for (int i = 61; i < 200; i++) {
        // part1COPY(linesFromInputFile, part2result + 61); std::cout << '\n';
        // std::cout << std::bitset<64>(part2result + 61) << '\n';
        // std::cout << std::bitset<64>(part2result) ;
    // }
    // std::cout << std::bitset<64>(865220799953); std::cout << '\n';
    return 0;
}
