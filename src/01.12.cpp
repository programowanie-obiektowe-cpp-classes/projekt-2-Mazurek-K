#include <vector>
#include <algorithm> 
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <fstream>
#include <ranges>
#include <tuple>

int main()
{
    std::vector<int> col1;
    std::vector<int> col2;

    std::string filename = "Text.txt";
    std::ifstream infile(filename);
    auto numbers = std::ranges::istream_view<int>(infile);

    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        col1.push_back(*it);
        if (++it != numbers.end()) {
            col2.push_back(*it);
        }
    }

    infile.close();
 

      std::sort(col1.begin(), col1.end());
      std::sort(col2.begin(), col2.end());

      int dist = 0;
      int score = 0;
      int counter;
      auto iter2 = col2.begin();

      for (auto iter = col1.begin(); iter != col1.end(); ++iter) {
          dist = dist + std::abs(*iter-*iter2);
          ++iter2;

      }


      for (auto iter = col1.begin(); iter != col1.end(); ++iter) {
          counter = std::count(col2.begin(), col2.end(), *iter) * (*iter);
          score=score+counter;
      }

      std::cout << "zad1: " << dist << std::endl;
      std::cout << "zad2: " << score << std::endl;
        
   
    return 0;
}

//zad1: 2192892
//zad2 : 22962826
