#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>


std::vector<std::vector<int>> generate_combinations(int size) {

    std::vector<std::vector<int>> output_vec;
    std::vector<int >line;

    for (int i = 0; i < size; ++i) {
        line.push_back(0);
    }

    for (int j = 0; j < size; ++j) {


        do {
            output_vec.push_back(line);

        } while (std::next_permutation(line.begin(), line.end()));


        std::sort(line.rbegin(), line.rend());
        line.at(j) = 1;
        std::sort(line.begin(), line.end());

    }

    line.clear();
    for (int i = 0; i < size; ++i) {
        line.push_back(1);
    }
    output_vec.push_back(line);


    //for (const auto& row : output_vec) {
    //    for (const auto& elem : row) {
    //        std::cout << elem << " ";
    //    }
    //    std::cout << std::endl; 
    //}

    return output_vec;
}


std::vector<std::vector<int>> generate_combinations_2(int size) {
    int total_rows = std::pow(3, size);

    std::vector<std::vector<int>> output(total_rows, std::vector<int>(size));


    for (int i = 0; i < size; ++i) {

        int k = std::pow(3, size -1- i);

        for (int j = 0; j < total_rows; ++j) {

            int a = (j / k) % 3;

            output[j][i] = a;
        }
    }

    return output;

}

long long evaluate(const std::vector<int>& values, const std::vector<int>& ops) {
    long long result = values[0];
    for (size_t i = 0; i < ops.size(); ++i) {
        if (ops[i] == 0) {
            result += values[i + 1];
        }
        else if (ops[i]==1) {
            result *= values[i + 1];
        }
        else {
            int p = std::log10(values[i+1])+1;
            result = result * std::pow(10, p) + values[i + 1];
        }
    }
    return result;
}

int main() {
    std::ifstream file("Text.txt");
    if (!file) {
        std::cerr << "Error: Could not open file.\n";
        return 1;
    }

    std::vector<long long> result;
    std::vector<std::vector<int>> values;
    std::string line;

    while (std::getline(file, line)) {
        auto colonPos = line.find(':');
        if (colonPos == std::string::npos) continue;

        long long firstValue = std::stoll(line.substr(0, colonPos));
        result.push_back(firstValue);

        std::vector<int> line_values;
        std::istringstream line_stream(line.substr(colonPos + 1));
        int num;
        while (line_stream >> num) {
            line_values.push_back(num);
        }
        values.push_back(std::move(line_values));
    }

    long long success = 0;
    int success_n = 0;

    for (size_t i = 0; i < values.size(); ++i) {
        const auto& value_line = values[i];
        int N = value_line.size();
        long long target_result = result[i];


        std::cout << "line: " << i << std::endl;

        std::vector<std::vector<int>> comb = generate_combinations_2(N - 1);

        for (const auto& row : comb) {
            if (evaluate(value_line, row) == target_result) {
                success += target_result;
                ++success_n;
                break; 
            }
        }
    }

    std::cout << "Wynik: " << success << "     " << success_n << std::endl;




    return 0;
}
