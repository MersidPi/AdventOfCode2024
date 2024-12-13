#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <numeric>
#define ull unsigned long long int 
typedef  long long int Int;


std::vector<std::string> extractLinesFromInputFile (std::string fileName) {
    std::ifstream inputFile(fileName);
    std::vector<std::string> lines;
    std::string inputLine;
    while(std::getline(inputFile, inputLine))
        lines.push_back(inputLine);
    return lines;
}

Int Mod(Int a, Int b) {
  if(a >= 0) return a % b;
  else if(b > 0) return b + a % b;
  else return -b + a % b;
}

Int GCD(Int a, Int b) {
  if(b == 0) return a;
  while(true) {
    Int c = Mod(a, b);
    if(c == 0) return b;
    a = b; b = c;
  }
}

Int IntDiv(Int a, Int b) {
  Int q = a / b;
  if(q >= 0) return q;
  else return q - 1;
}

Int ExtendedGCD(Int a, Int b, Int &p, Int &q) {
  p = 1; q = 0;
  if(b == 0) return a;
  p = 0; q = 1;
  Int r = 1, s = 0;
  while(true) {
    Int d = IntDiv(a, b);
    Int c = a - d * b, u = r - d * p, v = s - d * q;
    if(c == 0) return b;
    a = b; b = c; r = p; p = u; s = q; q = v;
  }
}

Int ProductMod(Int a, Int b, Int m) {
  Int p = 0;
  a = Mod(a, m); b = Mod(b, m);
  while (b > 0) {
    if (b % 2 == 1) p = Mod(p + a, m);
    a = Mod(a * 2, m); b /= 2;
  }
  return Mod(p, m);
}

Int LinearCongruenceAux(Int a, Int b, Int m) {
  Int p, q;
  ExtendedGCD(a, m, p, q);
  return ProductMod(p, b, m);
}

std::vector<Int> LinearCongruence(Int a, Int b, Int m) {
  Int d = GCD(a, m);
  if(b % d != 0) return {};
  Int t = LinearCongruenceAux(a / d, b / d, m / d);
  std::vector<Int> x(d);
  for(Int i = 0; i < d; i++) x[i] = t + m * i / d;
  return x;
}

ull part1 (std::vector<std::string> lines) {
    ull sum = 0, M = lines.size();
    for (Int i = 0; i < lines.size(); i += 4) {
        std::istringstream iss(lines[i].substr(12));
        Int x1, x2, X, y1, y2, Y;
        char c;
        iss >> x1 >> c >> c >> c >> y1;
        std::istringstream iss2(lines[i + 1].substr(12));
        iss2 >> x2 >> c >> c >> c >> y2;
        std::istringstream iss3(lines[i + 2].substr(9));
        iss3 >> X >> c >> c >> c >> Y;
        bool end = false;
        for (int a = 0; a < 100; a++) {
            for (int b = 0; b < 100; b++) {
                if (a * x1 + b * x2 == X && a * y1 + b * y2 == Y) {
                    sum += 3 * a + b;
                    end = true;
                    //std::cout << i << " nasli rejsenjee " << a << ' ' << b << '\n'; 
                    break;
                }
            }
            if (end) break;
        }

    }

    return sum;
}

ull part2 (std::vector<std::string> lines) {
    ull sum = 0, M = lines.size(); ull sum2 = 0, inkrement1, inkrement2;
    for (Int i = 0; i < lines.size(); i += 4) {
        if (false) 
        {
            std::istringstream iss(lines[i].substr(12));
            Int x1, x2, X, y1, y2, Y;
            char c;
            iss >> x1 >> c >> c >> c >> y1;
            std::istringstream iss2(lines[i + 1].substr(12));
            iss2 >> x2 >> c >> c >> c >> y2;
            std::istringstream iss3(lines[i + 2].substr(9));
            iss3 >> X >> c >> c >> c >> Y;
            bool end = false;
            for (int a = 0; a < 100; a++) {
                for (int b = 0; b < 100; b++) {
                    if (a * x1 + b * x2 == X && a * y1 + b * y2 == Y) {
                        sum2 += 3 * a + b;
                        inkrement2 = 3 * a + b;
                        end = true;
                        std::cout << '\n' << i << " nasli rejsenjee " << a << ' ' << b << '\n'; 
                        break;
                    }
                }
                if (end) break;
            }
            if (!end) std::cout << "NEMA RJESENJA";
        }
        // std::cout << "\n i je " << i << "\n\n";
        if (lines[i][0] == 'S')
            break;
        std::istringstream iss(lines[i].substr(12));
        Int x1, x2, X, y1, y2, Y;
        char c;
        iss >> x1 >> c >> c >> c >> y1;
        std::istringstream iss2(lines[i + 1].substr(12));
        iss2 >> x2 >> c >> c >> c >> y2;
        std::istringstream iss3(lines[i + 2].substr(9));
        iss3 >> X >> c >> c >> c >> Y;

        X += 10000000000000;
        Y += 10000000000000;
           // ax1 + bx2 = X
           // ay1 + by2 = Y
        Int a = (X * y2 - Y * x2) / (x1 * y2 - y1 * x2);
        Int b = (X - a * x1) / x2;
        // std::cout << "rjesenje a b " << a << " " << b << "\n"; 
        if (a * x1 + b * x2 == X && a * y1 + b * y2 == Y) {
            sum += 3 * a + b;
        }
        Int pX, qX, pY, qY;
     /*   if (X % ExtendedGCD(x1, x2, pX, qX) == 0 && Y % ExtendedGCD(y1, y2, pY, qY) == 0) {
            // X dio
            auto NZD = ExtendedGCD(x1, x2, pX, qX);
            X /= NZD;
            x1 /= NZD;
            x2 /= NZD;
            // namjestene pX i qX
            ExtendedGCD(x1, x2, pX, qX);

            // Y dio
            NZD = ExtendedGCD(y1, y2, pY, qY);
            Y /= NZD;
            y1 /= NZD;
            y2 /= NZD;
            // namjestene pY i qY
            ExtendedGCD(y1, y2, pY, qY);
            Int tX = 0;
            Int tY = 0;

            // ispisano rjesenje za A od  kong za X
            Int n1 = x2, c1 = pX * X;
            Int solx1 = c1 + n1 * tX;
            // std::cout << "\n x1 = " << c1 << " + " << n1 << " * tX\n";

            // ispisano rjesenje za A od  kong za Y
            Int n2 = y2, c2 = pY * Y;
            Int soly1 = c2 + n2 * tY; 
            // std::cout << "\n y1 = " << c2 << " + " << n2 << " * tY\n";

            // uvjet rjesivosti nove kong
            if ((c2 - c1) % GCD(n1, n2) != 0)
                continue;

            // nova kong
            auto d1 = LinearCongruenceAux(n1, c2 - c1, n2);
            auto sdasdaw= LinearCongruence(n1, c2 - c1, n2);
            for (auto x : sdasdaw)
                std::cout << x << ' ';
            std::cout << "\n";
            continue;
            Int d2 = c1 + n1 * d1;
            std::cout << "\n nova kong je = " << d2 << " + " << std::lcm(n1,n2) << " * t\n";

            // a nam je najmanje rjesenje nove kongruencije, tkd d2 mod lcm(n1 n2)
            Int a = Mod(d2, std::lcm(n1,n2));
            Int b = (X - x1 * a) / x2;
            std::cout << "\n a b je:" << a << ' ' << b << ' ' << Mod(d2, std::lcm(n1,n2)) <<'\n';


            //  KONG ZA BROJ 2 TJ DUGME B
            Int Bn1 = -x1, Bc1 = qX * X;
            Int Bsolx1 = Bc1 + n1 * tX;

            Int Bn2 = -y1, Bc2 = qY * Y;
            Int Bsoly1 = Bc2 + n2 * tY; 

            // uvjet rjesivosti nove kong
            if ((Bc2 - Bc1) % GCD(Bn1, Bn2) != 0)
                continue;
                

            // DOLE VALJDA NECE ICI ONE KOJE NISU RJESIVE
            
            if (b >= 0 && y1 * a + y2 * b == Y) {
                sum += 3 * a + b;
                inkrement1 = 3 * a + b;
            }
            else {
                // if (a == 0) {
                //     std::swap(lines[i], lines[i+1]);
                //     i -= 4;
                //     continue;
                // }
                
                std::cout << std::lcm(n1,n2) << "uAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAslovo vdje";
                int k = 0;
                Int staroA = a, staroB = b;
                while ( !(staroA - a > 0 && staroB - b < 0) && y1 * a + y2 * b != Y) {
                    // break;
                    // if (b < 0) break;
                    a = Mod(d2, std::lcm(n1,n2)) + k * std::lcm(n1,n2);
                    b = (X - x1 * a) / x2;
                    std::cout << "\n probavanje a " << a << " b " << b << "\n";
                    k++;
                }
                if (staroA - a > 0 && staroB - b < 0)
                    ;
                else {
                    sum += 3 * a + b;
                    inkrement1 = 3 * a + b;
                }
            }
            std::cout << "\n NADJENO RJESENJE a b " << a << ' ' << b  << ' ' << std::lcm(n1,n2) << " tjt \n";



            
            if (inkrement2 != inkrement1) {
                std::cout << "\n\n BREAK NA " << i << '\n';
                std::cout << "inkrement1 je " << inkrement1 << " a inkrement2 je " << inkrement2 << '\n';
                break;
            }
        }
        */
    }
    return sum;
}



int main () {
    std::vector<std::string> linesFromInputFile = extractLinesFromInputFile("input.txt");
    ull part1result = part1(linesFromInputFile); std::cout << "\nPart 1: " << part1result << "\n";
    ull part2result = part2(linesFromInputFile); std::cout << "Part 2: " << part2result << "\n\n";
    return 0;
}
