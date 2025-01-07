#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>


// rozwi¹zane beznadziejnie ale i tak za d³ugo nad tym siedzia³em

int sort_fun(std::vector<int> row, std::string mode, int low, int high) {

    int flag = 0;
    int returned = 0;
    int fl;
    if (mode == "inc") fl = 1;
    else fl = 2;

    for (auto iter = row.begin(); iter != row.end() - 1; ++iter) {
        if (*(iter + 1) - *iter >= low && *(iter + 1) - *iter <= high) {
            flag = fl;
        }
        else if (returned == 0) {
            ++returned;
            if (iter + 2 != row.end()) {
                if (*(iter + 2) - *iter >= low && *(iter + 2) - *iter <= high)
                    iter++;
                else if (iter == row.begin()) {
                    continue;
                }
                else {
                    flag = 0;
                    returned = 0;
                    break;
                }
            }
            else {

                returned = 0;
                break;
            }

        }
        else {
            flag = 0;
            returned = 0;
            break;
        }
    }

    return flag;

}



int main()
{
    std::vector<int> row;
    std::ifstream file("Text.txt");
    int safe_n = 0;
    int flag = 0;
    int returned = 0;
    if (file.is_open()) {
        std::string line;

        while (true) {
            if (std::getline(file, line)) {

                std::istringstream iss(line);
                int number;
                while (iss >> number) {
                    row.push_back(number);
                }


                flag = sort_fun(row, "inc", 1, 3);                 // spr czy rosnie
                if (flag == 0) flag = sort_fun(row, "dec", -3, -1);  // jesli nie rosnie to sp czy maleje



                if (flag == 1) {
                    ++safe_n;
                    for (int num : row) {
                        std::cout << num << " ";
                    }
                    std::cout << "  increasing" << std::endl;

                }
                else if (flag == 2) {
                    ++safe_n;
                    for (int num : row) {
                        std::cout << num << " ";
                    }
                    std::cout << "  decreasing" << std::endl;
                }
                else {
                    for (int num : row) {
                        std::cout << num << " ";
                    }
                    std::cout << "  nothing" << std::endl;

                }


                row.clear();

            }
            else {
                exit;
                file.close();
                break;
            }


        }

    }
    else {
        std::cerr << "Unable to open file" << std::endl;
    }

    std::cout << "number of safe: " << safe_n << std::endl;
    return 0;
}
