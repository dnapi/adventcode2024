#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <vector>
#include <algorithm>

int get_sum(const std::string &input){
    std::regex pattern(R"(mul\(\d+,\d+\))");
    //std::regex patternNum(R"(\bfun\((\d+),\s*(\d+)\)\b)");
    auto begin = std::sregex_iterator(input.begin(), input.end(), pattern);
    auto end = std::sregex_iterator();
    int count = 0;
    int sum = 0;
    for (auto it = begin; it != end; ++it) {
        //std::cout  << it->str() << " ";
        count++;
        // std::smatch match;
        // std::regex_search(it->str(), match, patternNum);
        // int num1 = std::stoi(match[1].str());
        // int num2 = std::stoi(match[2].str());
        std::string str = it->str();
        int num1 = std::stoi(str.substr(4));
        //std::cout << "(" << num1 << ",";
        size_t pos = str.find(',');
        size_t end = str.find(')');
        int num2 = std::stoi(str.substr(pos + 1, end - pos - 1));
        //std::cout << num2 << ") ";
        sum += num1 * num2;
    }
    return sum;
}

int main() {
    std::ifstream file("input03.txt");
    if (!file) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string input = buffer.str(); 
    std::cout << "sum=" << get_sum(input) << std::endl;
    size_t pos_do = 0;
    size_t pos_dont = input.find("don't()");
    int sum = get_sum(input.substr(pos_do, pos_dont - pos_do));
    pos_do = input.find("do()", pos_dont);
    while (pos_do != std::string::npos){
        pos_dont = input.find("don't()", pos_do);
        sum += get_sum(input.substr(pos_do, pos_dont - pos_do));
        pos_do = input.find("do()", pos_dont);
    }
    std::cout << "sum=" << sum << std::endl;
    return 0;
}
