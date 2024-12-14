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

int main() {
    // std::ifstream file("input-test.txt");
    std::ifstream file("input.txt");
    if (!file.is_open()){
        std::cerr << "Failed to  open file" << std::endl;
        return 1;
    }
    std::string line;
    std::getline(file, line);

    std::istringstream ss(line);
    long num;
    std::map<long, long> stones;
    while (ss >> num){
        stones[num] += 1;
    }
    file.close();
    std::cout << "Initial: ";
    for (auto& [key, value] : stones){
        std::cout << key << " ";
    }
    std::cout << std::endl;
    std::cout << "Init size =" << stones.size() << std::endl;
    for (int k = 0; k < 75; ++k){
        std::cout << k << " size =" << stones.size() << std::endl;
        std::vector<long> keys;
        for (auto& [key, value] : stones){
            keys.push_back(key);
        }
        std::map<long, long> temp;
        // for (auto& i: keys){
        //     std::cout << i << " ";
        // }
        std::cout << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < keys.size(); ++i){
            if (keys[i] == 0)
                temp[1] = temp[1] + stones[keys[i]];
            else if (is_even_digits(keys[i])){
                std::string first = std::to_string(keys[i]);
                std::string second = first.substr(first.size() / 2, first.size());
                first = first.substr(0, first.size() / 2);
                temp[std::stol(first)] = temp[std::stol(first)] + stones[keys[i]];
                temp[std::stol(second)] = temp[std::stol(second)] + stones[keys[i]];
            }
            else if (stones[keys[i]] != 0)
                temp[keys[i] * 2024] = temp[keys[i] * 2024] + stones[keys[i]];
        }
        stones = temp;
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
        // for (auto& [key, value] : stones){
        //     std::cout << key << "->" << value << " ";
        // }
        // std::cout << std::endl;
    }
    long total = 0;
    for (auto& [key, value] : stones){
        total += value;
    }
    std::cout << "Total: " << total << std::endl;
    return 0;
}

// 4602