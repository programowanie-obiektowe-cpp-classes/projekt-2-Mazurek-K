#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <ranges>
#include <string>

int main() {
    std::vector<std::vector<char>> array;
    std::string filename = "Text.txt";
    std::ifstream infile(filename);

    auto data = std::ranges::istream_view<std::string>(infile);
    size_t total_size = 0;
    std::vector<std::pair<int, int>> coord; 
    int x = 0, y = 0;

    for (std::string& line : data) {
        std::vector<char> row(line.begin(), line.end());
        for (int i = 0; i < row.size(); ++i) {
            if (row[i] == '^') {  
                coord.push_back({ y, i });  // (y, x)
            }
        }
        total_size += row.size();
        array.push_back(row);
        ++y;
    }

    int zad2_result = 0;

    for (int step = 0; step < total_size; ++step) {
        int current_x = step % array[0].size();
        int current_y = step / array[0].size();
        if (current_y >= array.size()) break;  

        if (array[current_y][current_x] == '.') {
            array[current_y][current_x] = '#';

            int dir_x = 0, dir_y = -1;  
            int xx = coord[0].second;  
            int yy = coord[0].first;  
            int step_count = 0;

            while (step_count < 70000) {
                int next_x = xx + dir_x;
                int next_y = yy + dir_y;

                if (next_y >= 0 && next_y < array.size() && next_x >= 0 && next_x < array[0].size()) {
                    if (array[next_y][next_x] != '#') {
                        xx = next_x;
                        yy = next_y;
                    }
                    else {
                        if (dir_x == 0 && dir_y == -1) { dir_x = 1; dir_y = 0; }
                        else if (dir_x == 1 && dir_y == 0) { dir_x = 0; dir_y = 1; }
                        else if (dir_x == 0 && dir_y == 1) { dir_x = -1; dir_y = 0; }
                        else if (dir_x == -1 && dir_y == 0) { dir_x = 0; dir_y = -1; }

                        next_x = xx + dir_x;
                        next_y = yy + dir_y;

                       /* if (next_y >= 0 && next_y < array.size() && next_x >= 0 && next_x < array[0].size()) {
                            if (array[next_y][next_x] != '#') {
                                xx = next_x;
                                yy = next_y;
                            }
                        }*/
                    }
                }
                else {
                    break;
                }

                ++step_count;
            }


            if (step_count >= 70000) {
                ++zad2_result;
            }
            std::cout  << 100*(static_cast<double>(step)/static_cast<double>(total_size))<<" %" << std::endl;
            array[current_y][current_x] = '.';
        }
    }

    // Output the results
    std::cout << "Result: " << zad2_result << std::endl;
    std::cout << "Total size: " << total_size << std::endl;

    return 0;
}
