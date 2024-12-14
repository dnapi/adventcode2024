#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>

int main() {
    std::ifstream file("input.txt");
    // std::ifstream file("input-test.txt");

    if (!file.is_open()){
        std::cerr << "Failed to  open file" << std::endl;
        return 1;
    }
    std::string line;
    std::vector<std::vector<long>> data;
    data.push_back(std::vector<long>());
    int i = 0;
    int line_num = 0;
    int group_num = 0;
    while (std::getline(file, line)){
        if (line.empty()){
            line_num = 0;
            group_num++;
            data.push_back(std::vector<long>());
            continue;
        }
        std::cout << line << std::endl;
        std::cout << "line_num=" << line_num << std::endl;
        long num1 = 0;
        long num2 = 0;
        size_t pos_x = line.find("X");
        size_t pos_c = line.find(",");
        size_t pos_y = line.find("Y");
        std::cout << line.substr(pos_x + 2, pos_c - pos_x - 2) << " " << line.substr(pos_y + 2) << std::endl;
        if (line_num < 3){
            num1 = std::stol(line.substr(pos_x + 2, pos_c - pos_x - 2));
            num2 = std::stol(line.substr(pos_y + 2));
            data[group_num].push_back(num1);
            data[group_num].push_back(num2);
        }
    }
    file.close();
    for (int i = 0; i < data.size(); i++){
        for (int j = 0; j < data[i].size(); j++){
            std::cout << data[i][j] << " ";
        }
        long x1 = data[i][0];
        long y1 = data[i][1];
        long x2 = data[i][2];
        long y2 = data[i][3];
        long x3 = data[i][4];
        long y3 = data[i][5];
        //data[i].push_back((x3 * y2 - y3 * x2) / (x1 * y2 - y1 * x2));
        data[i].push_back((x3 * y2 - y3 * x2) % (x1 * y2 - y1 * x2));
        data[i].push_back((x3 * y2 - y3 * x2 + 10000000000000 * (y2 - x2)) % (x1 * y2 - y1 * x2));
        data[i].push_back((x3 * y1 - y3 * x1+ 10000000000000 * (y1 - x1)) % (y1 * x2 - x1 * y2));
        std::cout << std::endl;
    }
    int total = 0;
    long total2 = 0;
    for (int i = 0; i < data.size(); i++){
        long x1 = data[i][0];
        long y1 = data[i][1];
        long x2 = data[i][2];
        long y2 = data[i][3];
        long x3 = data[i][4];
        long y3 = data[i][5];
        if (data[i][6] == 0){
            std::cout << "i=" << i << std::endl;
            long a = (x3 * y2 - y3 * x2) / (x1 * y2 - y1 * x2);
            long b = (x3 * y1 - y3 * x1) / (y1 * x2 - x1 * y2);
            total += 3 * a + b;
            std::cout << "a=" << a << " b=" << b << std::endl;
        }
        if (data[i][7] == 0 && data[i][8] == 0){
            std::cout << "i=" << i << std::endl;
            long a = (x3 * y2 - y3 * x2 + 10000000000000 * (y2 - x2)) / (x1 * y2 - y1 * x2);
            long b = (x3 * y1 - y3 * x1+ 10000000000000 * (y1 - x1)) / (y1 * x2 - x1 * y2);
            total2 += 3 * a + b;
            std::cout << "a=" << a << " b=" << b << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << "total=" << total << std::endl;
    std::cout << "total2=" << total2 << std::endl;
    return 0;
}

//1375574

//total2=78007322679356  too high