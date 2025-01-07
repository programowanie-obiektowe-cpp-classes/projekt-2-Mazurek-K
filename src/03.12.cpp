#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <iostream>
#include <string>
#include <ranges>




bool isInteger(const std::string& str) {
    if (str.empty()) {
        return false;
    }
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}


int main() {
    std::string fileName = "Text.txt";
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << fileName << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    std::string text = buffer.str();

    
    std::cout << "Original Text:\n" << text << "\n\n";

   //////////////////////////////////////////////////////////
    std::string do_ = "do()";
    std::string dont_ = "don't()";

    size_t pos1 = 0;
    size_t pos_start, pos_end;

    while (true) {
        pos_start = text.find(dont_, pos1);
        pos_end = text.find(do_, pos_start); 

        if (pos_start != std::string::npos && pos_end != std::string::npos && pos_start < pos_end) {
            text.erase(pos_start, pos_end - pos_start + do_.length());
        }
        else if (pos_start != std::string::npos && pos_end == std::string::npos) {
            text.erase(pos_start);
        }
        else {
            break; 
        }

        pos1 = pos_start;
    }



    std::vector<std::string> match;
    int sum_of_products = 0; 

    size_t pos = 0;
    while ((pos = text.find("mul(", pos)) != std::string::npos) {
        size_t endPos = text.find(")", pos);
        if (endPos != std::string::npos) {
            std::string substring = text.substr(pos + 4, endPos - pos - 4); 

            size_t commaPos = substring.find(",");
            if (commaPos != std::string::npos && substring.size() <= 7 ) { 
                std::string firstNumber = substring.substr(0, commaPos);
                std::string secondNumber = substring.substr(commaPos + 1);


                if (firstNumber.back() == ' ' || secondNumber.front() == ' '|| firstNumber.front() == ' ' || secondNumber.back() == ' ') {

                    pos = endPos + 1;
                    continue;
                }


                if (isInteger(firstNumber) && isInteger(secondNumber)) {
                    int num1 = std::stoi(firstNumber);
                    int num2 = std::stoi(secondNumber);


                    
                    match.push_back("mul(" + firstNumber + "," + secondNumber + ")");
                    sum_of_products += num1 * num2;
                    
                }
            }
        }
        ++pos;
    }


    std::cout << "\nFound " << match.size() << " mul(xxx,xxx) :\n";
    for (const auto& m : match) {
        std::cout << m << '\n';
    }

    std::cout << "\nSum : " << sum_of_products << std::endl;

    return 0;
}

//636 wring 650? wrong 105529485, 154005350,153962589, 153962589, 157621318
// 98930154 too high; 97971862 
// correct: 79845780  79845780