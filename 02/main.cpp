#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>

int is_save(std::vector<int> list, int tolerance){
    //std::cout << list.size() << std::endl;
    int sign = list[0] < list[1] ? 1 : -1;
    int prev = list[0];
    int count_unsafe = 0;
    int delta = 0;
    for (size_t i = 1; i < list.size(); i++){
        delta = list[i] - prev;
        //std::cout << delta << "/"; 
        if (delta == 0 || 
            delta * sign > 3 || 
            !(delta * sign > 0)
        ){
            count_unsafe++;
            if (count_unsafe > tolerance)
                return 0;
            if (count_unsafe == 1 && i == 1)
                sign = list[i] < list[i + 1] ? 1 : -1;
            prev = list[i - 1];
        }
        else
            prev = list[i];
    }
    return 1;
}

int is_save_from(std::vector<int> list, int start){
    if (list[start] == list[start + 1])
        return 0; 
    int sign = list[start] < list[start + 1] ? 1 : -1;
    if (sign == 0)
        return 0;
    int prev = list[start];
    for (size_t i = start + 1; i < list.size(); i++){
        int delta = list[i] - prev;
        //std::cout << delta << "/"; 
        if (delta == 0 ||
            delta * sign > 3 ||
            delta * sign < 0
        ){
            return 0;
        }
        prev = list[i];
    }
    return 1;
}

int is_save_part2(std::vector<int> list){
    int safe = 0;
    for (size_t i = 0; i < list.size(); i++){
        auto vec = list;
        vec.erase(vec.begin() + i);
        if (is_save(vec, 0))
            safe++;
    }
  //  std::cout << "safe=" << safe << std::endl;
    if (safe >= 1)
        return 1;
    return 0;
}

int main() {
    std::ifstream file("input02.txt");
    if (!file.is_open()){
        std::cerr << "Failed to  open file" << std::endl;
        return 1;
    }
    std::string line;
    std::vector<int> list;
    int num;
    int sum = 0;
    int sum_tolerance = 0;
    int sum_tolerance2 = 0;
    while (std::getline(file, line)){
        std::istringstream iss(line);
        while (iss >> num)
            list.push_back(num);
        int delta = is_save(list, 0);
        sum += delta;
        int save2 = is_save(list, 1);
        if (!save2)
            save2 = is_save_from(list, 1);
        sum_tolerance += save2;
        int save2v2 = is_save_part2(list);
        sum_tolerance2 += save2v2;
        if (save2v2 != save2){
            std::cout << "Error: ";
            for (auto i : list){
                std::cout << i << " ";
            }
            std::cout << "save=" << save2 << std::endl;
        }
        list = {};
    }
    file.close();
    std::cout << "Number of save series=" << sum << std::endl;
    std::cout << "Number of save series=" << sum_tolerance << std::endl;
    std::cout << "Number of save series=" << sum_tolerance2 << std::endl;
    std::vector<int> list1 = {47, 50, 51, 52, 51, 55};
    std::cout << is_save(list1, 1) << std::endl;
    std::cout << is_save_from(list1, 1) << std::endl;
    std::cout << is_save_part2(list1) << std::endl;
    return 0;
}

//301 322 319