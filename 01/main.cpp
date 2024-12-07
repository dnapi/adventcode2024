#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>

int main() {
    std::ifstream file("file01.txt");
    if (!file.is_open()){
        std::cerr << "Failed to  open file" << std::endl;
        return 1;
    }
    std::string line;
    std::vector<u_int64_t> column1;
    std::vector<u_int64_t> column2;
    u_int64_t num1, num2;
    while (std::getline(file, line)){
        std::istringstream iss(line);
        if (iss >> num1 >> num2) {
            column1.push_back(num1);
            column2.push_back(num2);
        }
    }
    file.close();

    //std::cout << "Column 1 sze " << column1.size() << std::endl;
    //std::cout << "Column 2 sze " << column2.size() << std::endl;
    std::sort(column1.begin(), column1.end());
    std::sort(column2.begin(), column2.end());
    unsigned long total_distance = 0;
    unsigned long total_similarity_score = 0;
    for (int i = 0; i < column1.size(); i++){
        unsigned long temp = column1[i] > column2[i] ? column1[i] - column2[i] : column2[i] - column1[i];
        total_distance += temp;
        temp = std::count(column2.begin(), column2.end(), column1[i]);
        total_similarity_score += column1[i] * temp;
    }
    std::cout << "total_distance=" << total_distance << std::endl;
    std::cout << "total_similarity_score=" << total_similarity_score << std::endl;

    return 0;
}