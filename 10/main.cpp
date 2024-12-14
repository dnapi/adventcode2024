#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>
#include <map>
#include <set>

std::vector<int> stringToVector(const std::string& str) {
    std::vector<int> result;
    for (char ch : str) {
        if (std::isdigit(ch)) { // Ensure the character is a digit
            result.push_back(ch - '0'); // Convert char to int
        }
    }
    return result;
}

void trails(
        std::set<std::pair<int, int>>& reached,
        std::vector<std::vector<int>>& map, 
        int i, int j, int value){
    if (i < 0 || i >= map.size() || j < 0 || j >= map[i].size())
        return ;
    if (value == 8 && map[i][j] == 9){
        reached.insert({i, j});
        return ;
    }
    if (map[i][j] == value + 1)
    {
        trails(reached, map, i - 1, j, value + 1);
        trails(reached, map, i + 1, j, value + 1);
        trails(reached, map, i, j - 1, value + 1);
        trails(reached, map, i, j + 1, value + 1);
    }
}

void trails_distinct(
        std::vector<std::pair<int, int>>& reached,
        std::vector<std::vector<int>>& map, 
        int i, int j, int value){
    if (i < 0 || i >= map.size() || j < 0 || j >= map[i].size())
        return ;
    if (value == 8 && map[i][j] == 9){
        reached.push_back({i, j});
        return ;
    }
    if (map[i][j] == value + 1)
    {
        trails_distinct(reached, map, i - 1, j, value + 1);
        trails_distinct(reached, map, i + 1, j, value + 1);
        trails_distinct(reached, map, i, j - 1, value + 1);
        trails_distinct(reached, map, i, j + 1, value + 1);
    }
}

int main() {
    //std::ifstream file("input10test.txt");
    std::ifstream file("input10.txt");
    if (!file.is_open()){
        std::cerr << "Failed to  open file" << std::endl;
        return 1;
    }
    std::string line;
    std::vector<std::vector<int>> map;
    while (std::getline(file, line)){
        map.push_back(stringToVector(line));
    }
    file.close();
    int total = 0;
    int total_2 = 0;
    for (int i = 0; i < map.size(); i++){
        for (int j = 0; j < map[i].size(); j++){
            std::set<std::pair<int,int>> state = {};
            std::vector<std::pair<int,int>> state2 = {};
            if (map[i][j] == 0){
                trails(state, map, i, j, -1);
                total += state.size();
                trails_distinct(state2, map, i, j, -1);
                total_2 += state2.size();
            }
        }
    }
    std::cout << "Total: " << total << std::endl;
    std::cout << "Total 2: " << total_2 << std::endl;
    return 0;
}

// 4602