#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>
#include <map>

int main() {
    std::ifstream file("input05.txt");
    if (!file.is_open()){
        std::cerr << "Failed to  open file" << std::endl;
        return 1;
    }
    std::string line;
    int part = 0;
    std::vector<std::vector<int>> grid(100, std::vector<int>(100, 0)); // Adjacency matrix
    std::vector<std::vector<int>> updates;
    std::map<int, int> rules_right;
    std::map<int, int> rules_left;
    while (std::getline(file, line)){
        if (0 == part){
            if (!line.empty()){
                int page1 = std::stoi(line.substr(0, 2));
                int page2 = std::stoi(line.substr(3, 2));
                grid[page1][page2] = 1;
                rules_right[page1] = page2;
                rules_left[page2] = page1;
                //std::cout << "Page1: " << page1 << " Page2: " << page2 << std::endl;
            }
            else { 
                part = 1;
                continue;
            }
        }
        else if (0 < part){
            std::istringstream ss(line);
            std::string token;
            std::vector<int> values;
            while (std::getline(ss, token, ',')){
                int value = std::stoi(token);
                values.push_back(value);

            }
            updates.push_back(values);
        }
    }
    file.close();
    std::vector<int> pages_list(updates.size(), 0);
    for (int k = 0; k < updates.size(); ++k){
        auto& update = updates[k];
        int flag = 0;
        for (int i = 0; i < update.size(); ++i){
            if (flag)
                break;
            int page = update[i];
            for (int j = 0; j < i; ++j){  // left side
                int left_page = update[j];
                if (1 == grid[page][left_page]){
                    flag = 1;
                    break;
                }
            }
            if (flag)
                break;
            for (int j = i + 1; j < update.size(); ++j){  // right side
                int right_page = update[j];
                if (1 == grid[right_page][page]){
                    flag = 1;
                    break;
                }
            }
            //std::cout << "Page: " << page << "map->" << rules_right[page] <<  std::endl;
        }
        if (!flag)
            pages_list[k] = update[update.size() / 2];
    }
    std::cout << "Pages list: ";
    for (auto& page : pages_list){
        std::cout << page << " ";
    }
    int total = 0;
    for (auto& page : pages_list){
        total += page;
    }
    std::cout << "Total: " << total << std::endl;
    std::vector<int> pages_list_wrong(updates.size(), 0);
    for (int k = 0; k < updates.size(); ++k){
        if (pages_list[k])
            continue;
        auto& update = updates[k];
        int flag = 1;
        while (flag){
            flag = 1;
            for (int i = 0; i < update.size() - 1; ++i){
                int page_left = update[i];
                int page_right = update[i + 1];
                if (grid[update[i + 1]][update[i]]){
                     std::swap(update[i], update[i + 1]);
                    flag = 2;
                    break;
                }
            }
            if (1 == flag)
                break;
        }
        pages_list_wrong[k] = update[update.size() / 2];
    }
    std::cout << "Pages list wrong: ";
    for (auto& page : pages_list_wrong){
        std::cout << page << " ";
    }
    total = 0;
    for (auto& page : pages_list_wrong){
        total += page;
    }
    std::cout << "Total wrong: " << total << std::endl;
    return 0;
}
//6267
//6267