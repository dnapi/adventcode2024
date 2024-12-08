#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

int fun(std::vector<long> values, long result){
    if (values.size() == 2){
        if (values[0] + values[1] == result || values[0] * values[1] == result){
            return 1;
        }
        return 0;
    }
    long value1 = values.back();
    values.pop_back();
    long value2 = values.back();
    values.pop_back();
    long product = value1 * value2;
    values.push_back(product);
    if (product <= result && fun(values, result)){
        return 1;
    }
    values.pop_back();
    long sum = value1 + value2;
    values.push_back(sum);
    if (sum <= result && fun(values, result))
        return 1;
    return 0;
}

int fun_part2(std::vector<long> values, long result){
    if (values.size() == 2){
        if (values[0] + values[1] == result || 
            values[0] * values[1] == result ||
            std::stol(std::to_string(values[1]) + std::to_string(values[0])) == result
            ){
            return 1;
        }
        return 0;
    }
    long value1 = values.back();
    values.pop_back();
    long value2 = values.back();
    values.pop_back();
    long product = value1 * value2;
    values.push_back(product);
    if (product <= result && fun_part2(values, result)){
        return 1;
    }
    values.pop_back();
    long sum = value1 + value2;
    values.push_back(sum);
    if (sum <= result && fun_part2(values, result))
        return 1;
    values.pop_back();
    std::string str = std::to_string(value1) + std::to_string(value2);
    long comb = std::stol(str);
    values.push_back(comb);
    if (comb <= result && fun_part2(values, result))
        return 1;
    return 0;
}

int main() {
    std::ifstream file("input07.txt");
    //std::ifstream file("input07test.txt");
    if (!file.is_open()){
        std::cerr << "Failed to  open file" << std::endl;
        return 1;
    }
    std::string line;
    int part = 0;
    std::vector<std::vector<long>> data;
    std::vector<long> results;
    long total = 0;
    long total_part2 = 0;
    while (std::getline(file, line)){
        size_t pos_end = line.find(":");
        long result = std::stol(line.substr(0, pos_end));
        results.push_back(result);
        std::string left_str = line.substr(pos_end + 1, line.size() - pos_end);
        std::istringstream ss(left_str);
        std::vector<long> values;
        int value = 0;
        while (ss >> value){
            values.push_back(value);
        }
        std::reverse(values.begin(), values.end());
        //std::cout << "Result: " << result;
        if (fun(values, result)){
            total += result;
            // total_part2 += result;
        }
        // else if (fun_part2(values, result)){
        //     total_part2 += result;
        // }
        // else{
        //     std::cout << " Failed" << std::endl;
        // }
        // else{
        //    std::cout << " Failed" << std::endl;
        // }
        if (fun_part2(values, result)){
            total_part2 += result;
        //    std::cout << " Passed" << std::endl;
        }
        // else{
        //     std::cout << " Failed ";
        //     for (auto& v : values){
        //         std::cout << v << " ";
        //     }
        //     std::cout << std::endl;
        // }
        data.push_back(values);
    }
    file.close();
    std::cout << "Total: " << total << std::endl;
    std::cout << "Total part 2: " << total_part2 << std::endl;
    int max_size = 0;
    for (size_t i = 0; i < data.size(); i++){
        auto& values = data[i];
        long result = results[i];
        int flag = 0;
        if (values.size() > max_size){
            max_size = values.size();
        }
    }
    std::cout << "Max size: " << max_size << std::endl;
    return 0;
}

// 709063252057  too low

// 1582598718861

// part 2 165278151522644
