#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>
#include <map>

int main() {
    //std::ifstream file("input06test.txt");
    std::ifstream file("input06.txt");
    if (!file.is_open()){
        std::cerr << "Failed to  open file" << std::endl;
        return 1;
    }
    std::string line;
    std::vector<std::string> map;
    int i = 0;  
    while (std::getline(file, line)){
        map.push_back(line);
    }
    file.close();
    int pos[2] = {-1, -1};
    for (int i = 0; i < map.size(); ++i){
        line = map[i];
        for (int j = 0; j < line.size(); ++j){
            if (line[j] == '>' || line[j] == '<' || line[j] == '^' || line[j] == 'v'){
                std::cout << "Guard found: " << line[j] << " at " << i << " " << j << std::endl;
                pos[0] = i;
                pos[1] = j;
                break;
            }
        }
        if (pos[0] != -1)
            break;
    }
    std::cout << "Position: " << pos[0] << " " << pos[1] << std::endl;
    std::vector<std::vector<int>> route(map.size(), std::vector<int>(map[0].size(), 0));
    //while (pos[0] >= 0 && pos[1] >= 0 && pos[0] < map.size() && pos[1] < map[pos[0]].size()){
    int total = 0;
    while (true){
        if (pos[0] == 0 && map[pos[0]][pos[1]] == '^')
            break;
        else if (pos[1] == 0 && map[pos[0]][pos[1]] == '<')
            break;
        else if (pos[0] == map.size() - 1 && map[pos[0]][pos[1]] == 'v')
            break;
        else if (pos[1] == map[pos[0]].size() - 1 && map[pos[0]][pos[1]] == '>')
            break;
        else if (pos[0] == map.size() - 1 && map[pos[0]][pos[1]] == 'v')
            break;
        else if (pos[1] == 0 && map[pos[0]][pos[1]] == '<')
            break;
        else if (pos[1] == map[pos[0]].size() - 1 && map[pos[0]][pos[1]] == '>')
            break;
        if (map[pos[0]][pos[1]] == '>'){
            if (map[pos[0]][pos[1] + 1] == '#')
                map[pos[0]][pos[1]] = 'v';
            else {
                map[pos[0]][pos[1]] = '.';
                pos[1] += 1;
                map[pos[0]][pos[1]] = '>';
                total += 1;
                route[pos[0]][pos[1]] = 1;
            }
        }
        else if (map[pos[0]][pos[1]] == '<'){
            if (map[pos[0]][pos[1] - 1] == '#')
                map[pos[0]][pos[1]] = '^';
            else {
                map[pos[0]][pos[1]] = '.';
                pos[1] -= 1;
                map[pos[0]][pos[1]] = '<';
                total += 1;
                route[pos[0]][pos[1]] = 1;
            }
        }
        else if (map[pos[0]][pos[1]] == '^'){
            if (map[pos[0] - 1][pos[1]] == '#')
                map[pos[0]][pos[1]] = '>';
            else {
                map[pos[0]][pos[1]] = '.';
                pos[0] -= 1;
                map[pos[0]][pos[1]] = '^';
                total += 1;
                route[pos[0]][pos[1]] = 1;
            }
        }
        else if (map[pos[0]][pos[1]] == 'v'){
            if (map[pos[0] + 1][pos[1]] == '#')
                map[pos[0]][pos[1]] = '<';
            else {
                map[pos[0]][pos[1]] = '.';
                pos[0] += 1;
                map[pos[0]][pos[1]] = 'v';
                total += 1;
                route[pos[0]][pos[1]] = 1;
            }
        }
        //std::cout << "Position: " << pos[0] << " " << pos[1] << " " << map[pos[0]][pos[1]] << std::endl;
    }
    std::cout << "Total: " << total << std::endl;
    total = 0;
    for (int i = 0; i < route.size(); ++i){
        for (int j = 0; j < route[i].size(); ++j){
            total += route[i][j];
        }
    }
    std::cout << "Total after corrections: " << total << std::endl;
    return 0;
}

// 4602