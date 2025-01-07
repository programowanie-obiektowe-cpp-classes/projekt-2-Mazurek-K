#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <ranges>
#include <tuple>
#include <set>
#include <string>
#include <iostream>
#include <print>

int main() {
    std::vector<std::vector<char>> array;
    std::string filename = "Text.txt";
    std::ifstream infile(filename);

    auto data = std::ranges::istream_view<std::string>(infile);

    std::vector<std::pair<int, int>> coord;
    int x = 0, y = 0;

    for (std::string& line : data) {
        std::vector<char> row = line | std::ranges::views::transform([](char c) { return c; }) | std::ranges::to<std::vector<char>>();

        for (auto it = row.begin(); it != row.end(); ++it) {
            if (*it == '^') {
                coord.push_back({ x, y });
            }
            ++x;
        }
        array.push_back(row);
        x = 0;
        ++y;
    }


    int dir_x = 0;
    int dir_y = -1;

    int i = 0;
    int yy = 0;
    int xx = 0;
    int next_yy = 0;
    int next_xx = 0;



    while (i < 7000) {


        auto& current_pos = coord[i];
        yy = current_pos.second;
        xx = current_pos.first;

        next_yy = yy + dir_y;
        next_xx = xx + dir_x;

        if (next_yy >= 0 && next_yy < array.size() && next_xx >= 0 && next_xx < array[0].size()) {
            if (array[next_yy][next_xx] != '#') {
                yy += dir_y;
                xx += dir_x;

                coord.push_back({ xx, yy });
            }
            else {


                if (dir_x == 0 && dir_y == -1) { dir_x = 1; dir_y = 0; }
                else if (dir_x == 1 && dir_y == 0) { dir_x = 0; dir_y = 1; }
                else if (dir_x == 0 && dir_y == 1) { dir_x = -1; dir_y = 0; }
                else if (dir_x == -1 && dir_y == 0) { dir_x = 0; dir_y = -1; }

                next_yy = yy + dir_y;
                next_xx = xx + dir_x;

                if (next_yy >= 0 && next_yy < array.size() && next_xx >= 0 && next_xx < array[0].size()) {
                    yy += dir_y;
                    xx += dir_x;
                    coord.push_back({ xx, yy });

                }
                else {
                    break;
                }
            }
        }
        else {
            std::cout << "Out of bounds\n";
            break;
        }

        std::cout << "Value at position: " << array[yy][xx] << "\n";

        if (array[yy][xx] == '.' && dir_x==0){
            array[yy][xx] = '|';
        }
        else if(array[yy][xx] == '.' && dir_y == 0 ){
            array[yy][xx] = '-';
        }
        else if (array[yy][xx] == '-' || array[xx][yy]== '|' || array[xx][yy] == '+') {
            array[yy][xx] = '+';
        }
        else {
            array[yy][xx] = '+';
        }


        //if (array[yy][xx] == '.' && dir_x == 0 && dir_y==-1) {
        //    array[yy][xx] = '^';
        //}
        //else if (array[yy][xx] == '.' && dir_x == 0 && dir_y == 1) {
        //    array[yy][xx] = 'v';
        //}
        //else if (array[yy][xx] == '.' && dir_x == 1 && dir_y == 0) {
        //    array[yy][xx] = '>';
        //}
        //else if (array[yy][xx] == '.' && dir_x == -1 && dir_y == 0) {
        //    array[yy][xx] = '<';
        //}
        //else if ((array[yy][xx] == '>' || array[yy][xx] == '<') && dir_y == 0) {
        //    array[yy][xx] = '-';
        //}
        //else if ((array[yy][xx] == '^' || array[yy][xx] == 'v') && dir_x == 0) {
        //    array[yy][xx] = '|';
        //}
        //else if (array[yy][xx] == '-' || array[xx][yy] == '|' || array[xx][yy] == '+') {
        //    array[yy][xx] = '+';
        //}
        //else {
        //    array[yy][xx] = '+';
        //}


        ++i;
    }


    for (const auto& row : array) {
        for (char c : row) {
            std::cout << c;
        }
        std::cout << '\n';
    }

    std::set<std::pair<int, int>> unique_pairs(coord.begin(), coord.end());
    std::cout << "unique pairs: " << unique_pairs.size() << std::endl;




    return 0;
}