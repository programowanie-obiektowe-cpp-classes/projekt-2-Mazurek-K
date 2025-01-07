#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <iostream>
#include <string>
#include <ranges>


bool out_of_range(const std::vector<std::vector<int>>& vec, int i, int j) {

    if (i >= vec.size() || j >= vec[i].size()) return true;
    else return false;

}


void find_xmas(const std::vector<std::vector<int>>& vec, int i, int j,int vert, int hor, int &sum) {

    if (out_of_range(vec, i + 3*vert, j+3*hor) == false) {    
        if (vec[i][j] < vec[i + 1*vert][j + 1*hor] && vec[i + 1*vert][j+ 1*hor] < vec[i + 2*vert][j + 2*hor] && vec[i + 2*vert][j + 2*hor] < vec[i + 3 * vert][j+ 3*hor]) {
            ++sum;
        }
    }
    
}


void find_mas(const std::vector<std::vector<int>>& vec, int i, int j,  int& sum) {

    if (out_of_range(vec, i + 1, j + 1) == false && out_of_range(vec, i - 1, j - 1) == false &&
        out_of_range(vec, i - 1, j + 1) == false && out_of_range(vec, i + 1, j - 1) == false) {
        if ((vec[i + 1][j + 1]==1 && vec[i -1][j - 1 ] ==3) || (vec[i + 1][j + 1] == 3 && vec[i - 1][j - 1] == 1)) {
            if ((vec[i - 1][j + 1] == 1 && vec[i + 1][j - 1] == 3) || (vec[i - 1][j + 1] == 3 && vec[i + 1][j - 1] == 1)) {
                ++sum;
            }
        }
    }

}


int main() {


    // tylko wczytanie danych
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

    ////////////// matrix int

    int width = text.find('\n');
    int height = 0;
    size_t pos0 = 0;

    while (true) {
        pos0 = text.find('\n', pos0);
        if (pos0 != std::string::npos) {
            ++pos0;
        }
        else break;
        ++height;
    }

    std::cout <<"line length: " << width <<"  height: "<< height << std::endl;

    size_t pos = 0;
    size_t start_line_pos = 0;
    std::vector<std::vector<int>> matrix;

    while (pos != std::string::npos) {
        pos = text.find('\n', start_line_pos);

        std::vector<int> row;

        for (size_t i = start_line_pos; i < (pos == std::string::npos ? width : pos); ++i) {
            if (text[i] == 'X') {
                row.push_back(0);  
            }
            else if (text[i] == 'M') {
                row.push_back(1); 
            }
            else if (text[i] == 'A') {
                row.push_back(2);  
            }
            else if (text[i] == 'S') {
                row.push_back(3);  
            }
        }
        matrix.push_back(row);
        
        start_line_pos = pos + 1;
        
    }


    for (size_t row = 0; row < matrix.size(); ++row) {
        for (size_t col = 0; col < matrix[row].size(); ++col) {
            std::cout << matrix[row][col] << " ";
        }
        std::cout << '\n';  
    }

    /////////////  rozwi¹zanie (kierunki szukania)
    int xmas_count = 0;
    int mas_count = 0;
    for (int i = 0; i <= width-1; i++) {
        for (int j = 0; j <= height-1; j++) {
            if (matrix[i][j] == 0) {
                
                find_xmas(matrix, i, j, 0, 1, xmas_count);  // prawo
                find_xmas(matrix, i, j, 0, -1, xmas_count); // lewo
                find_xmas(matrix, i, j, 1, 0, xmas_count);  // gora
                find_xmas(matrix, i, j, -1, 0, xmas_count);  // dol
                find_xmas(matrix, i, j, 1, 1, xmas_count); //gp
                find_xmas(matrix, i, j, 1, -1, xmas_count); //gl
                find_xmas(matrix, i, j, -1, -1, xmas_count);  //dl
                find_xmas(matrix, i, j, -1, 1, xmas_count); //dp

            }
            if (matrix[i][j] == 2) {
                find_mas(matrix, i, j, mas_count);
            }

        }
    }



    



    std::cout << "Wynik xmas:     " << xmas_count << std::endl;
    std::cout << "Wynik mas:     " << mas_count << std::endl;
    return 0;
}

