#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


int main() {
    std::ifstream file("input07.txt");
    if (!file.is_open()){
        std::cerr << "Failed to  open file" << std::endl;
        return 1;
    }
    std::string line;
    int part = 0;
    std::vector<std::vector<int>> data;
    std::vector<int> results;
    while (std::getline(file, line)){
        size_t pos_end = line.find(":");
        int result = std::stoi(line.substr(0, pos_end));
        std::cout << "Result: " << result << std::endl;
        results.push_back(result);
        std::string left_str = line.substr(pos_end + 1, line.size() - pos_end);
        std::istringstream ss(left_str);
        std::vector<int> values;
        //std::string token;
        // while (std::getline(ss, token, ' ')){
        //     int value = std::stoi(token);
        //     values.push_back(value);
        // }
        int value = 0;
        while (ss >> value){
            //std::cout << "value=" << value << std::endl;
            values.push_back(value);
        }
        data.push_back(values);
    }
    file.close();
    for (size_t i = 0; i < data.size(); i++){
        auto& values = data[i];
        int result = results[i];
        int flag = 0;
        std::cout << values.size() << std::endl;
        // for (size_t j = 0; j < values.size(); j++){
        // }
        // if (!flag){
        //     std::cout << "Result: " << result << std::endl;
        //     break;
        // }
    }
    return 0;
}