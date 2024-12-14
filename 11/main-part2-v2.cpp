#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>
#include <map>
#include <set>
#include <list>
#include <chrono>

bool is_even_digits(long num){
    long count = 0;
    while (num > 0){
        num /= 10;
        count++;
    }
    return count % 2 == 0;
}

// long decay_count(long num, long times){
//     if (times == 0){
//         return 1;
//     }
//     for (int i = 0; i < times; ++i){
//         if (num == 0){
//             return decay_count(1, times - 1);
//         }
//         else if (is_even_digits(num)){
//             std::string first = std::to_string(num);
//             std::string second = first.substr(first.size() / 2, first.size());
//             first = first.substr(0, first.size() / 2);
//             long result = decay_count(std::stol(first), times - 1);
//             result += decay_count(std::stol(second), times - 1);
//             return result;
//         }
//         else
//             return decay_count(num * 2024, times - 1);
//     }
//     return num;
// }


int main() {
    std::ifstream file("input-test.txt");
    // std::ifstream file("input.txt");
    if (!file.is_open()){
        std::cerr << "Failed to  open file" << std::endl;
        return 1;
    }
    std::string line;
    std::getline(file, line);

    std::istringstream ss(line);
    long num;
    std::list<long> row;
    while (ss >> num){
        row.push_back(num);
    }
    file.close();
    std::cout << "Initial: ";
    for (auto& value : row){
        std::cout << value << " ";
    }
    // long total = 0;
    // for (auto it = row.begin(); it != row.end();){
    //     for (int k = 0; k < 25; ++k){
            
    //     }
    // }
    std::cout << std::endl;
    for (int k = 0; k < 75; ++k){
        std::cout << k << " size =" << row.size() << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        for (auto it = row.begin(); it != row.end();){
            //std::cout << *it << std::endl;
            if (*it == 0){
                row.insert(it, 1);
                it = row.erase(it);
                continue;
            }
            else if (is_even_digits(*it)){
                std::string first = std::to_string(*it);
                std::string second = first.substr(first.size() / 2, first.size());
                first = first.substr(0, first.size() / 2);
                row.insert(it, std::stol(first));
                row.insert(it, std::stol(second));
                it = row.erase(it);
                continue;
            }
            else {
                row.insert(it, *it * 2024);
                it = row.erase(it);
                continue;
            }
        }
        // Get the end time
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

    }
    // long total = 0;
    // for (auto& value : row){
    //     //std::cout << value << std::endl;
    //     total += decay_count(value, 75);
    // }

    std::cout << "Total: " << row.size() << std::endl;
    return 0;
}

// 4602