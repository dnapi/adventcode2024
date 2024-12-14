#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>
#include <map>
#include <set>

bool is_even_digits(long num){
    long count = 0;
    while (num > 0){
        num /= 10;
        count++;
    }
    return count % 2 == 0;
}


int main() {
    //std::ifstream file("input-test.txt");
    std::ifstream file("input.txt");
    if (!file.is_open()){
        std::cerr << "Failed to  open file" << std::endl;
        return 1;
    }
    std::string line;
    std::vector<std::vector<int>> map;
    std::getline(file, line);

    std::istringstream ss(line);
    long num;
    std::vector<long> row;
    while (ss >> num){
        row.push_back(num);
    }
    file.close();
    std::cout << "Initial: ";
    for (int i = 0; i < row.size(); ++i){
        std::cout << row[i] << " ";
    }
    std::cout << std::endl;

    for (int k = 0; k < 75; ++k){
        //std::cout << "row.size(): " << row.size() << std::endl; 
        std::cout << k << " size =" << row.size() << std::endl;
        std::vector<long> temp;
        for (int i = 0; i < row.size(); ++i){
            //std::cout << i << "->" << row[i];
            if (row[i] == 0){
                temp.push_back(1);
                //std::cout << "null ";
            }
            else if (is_even_digits(row[i])){
                std::string first = std::to_string(row[i]);
                std::string second = first.substr(first.size() / 2, first.size());
                first = first.substr(0, first.size() / 2);
                temp.push_back(std::stol(first));
                temp.push_back(std::stol(second));
                //std::cout << "even ";
            }
            else {
                temp.push_back(row[i] * 2024);
                //std::cout << " ";
            }
        }
        row = temp;
        // for (int j = 0; j < row.size(); ++j){
        //     std::cout << row[j] << " ";
        // }
    }
    std::cout << std::endl;
    // std::cout << "Final: ";
    // for (int j = 0; j < row.size(); ++j){
    //     std::cout << row[j] << " ";
    // }
    // std::cout << std::endl;
    int total = 0; 
    for (int i = 0; i < row.size(); ++i){
        ++total;
    }
    std::cout << "Total: " << total << std::endl;
    return 0;
}

// 4602