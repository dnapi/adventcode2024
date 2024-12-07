#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>
#include <map>

bool is_about_to_escape(int* pos, std::vector<std::string> map){
    if (pos[0] == 0 && map[pos[0]][pos[1]] == '^')
        return true;
    else if (pos[1] == 0 && map[pos[0]][pos[1]] == '<')
        return true;
    else if (pos[0] == map.size() - 1 && map[pos[0]][pos[1]] == 'v')
        return true;
    else if (pos[1] == map[pos[0]].size() - 1 && map[pos[0]][pos[1]] == '>')
        return true;
    else if (pos[0] == map.size() - 1 && map[pos[0]][pos[1]] == 'v')
        return true;
    else if (pos[1] == 0 && map[pos[0]][pos[1]] == '<')
        return true;
    else if (pos[1] == map[pos[0]].size() - 1 && map[pos[0]][pos[1]] == '>')
        return true;
    return false;
}

enum Direction {
        up = 1,
        down = 2,
        left = 4,   
        right = 8   
    };

void make_step(int* pos, std::vector<std::string>& map, std::vector<std::vector<int>>& visited){
    if (map[pos[0]][pos[1]] == '>'){
        visited[pos[0]][pos[1]] |= right;
        if (map[pos[0]][pos[1] + 1] == '#')
            map[pos[0]][pos[1]] = 'v';
        else {
            map[pos[0]][pos[1]] = '.';
            pos[1] += 1;
            map[pos[0]][pos[1]] = '>';
        }
    }
    else if (map[pos[0]][pos[1]] == '<'){
        visited[pos[0]][pos[1]] |= left;
        if (map[pos[0]][pos[1] - 1] == '#')
            map[pos[0]][pos[1]] = '^';
        else {
            map[pos[0]][pos[1]] = '.';
            pos[1] -= 1;
            map[pos[0]][pos[1]] = '<';
        }
    }
    else if (map[pos[0]][pos[1]] == '^'){
        visited[pos[0]][pos[1]] |= up;
        if (map[pos[0] - 1][pos[1]] == '#')
            map[pos[0]][pos[1]] = '>';
        else {
            map[pos[0]][pos[1]] = '.';
            pos[0] -= 1;
            map[pos[0]][pos[1]] = '^';
        }
    }
    else if (map[pos[0]][pos[1]] == 'v'){
        visited[pos[0]][pos[1]] |= down;
        if (map[pos[0] + 1][pos[1]] == '#')
            map[pos[0]][pos[1]] = '<';
        else {
            map[pos[0]][pos[1]] = '.';
            pos[0] += 1;
            map[pos[0]][pos[1]] = 'v';
        }
    }
}

int get_state(char c){
    if (c == '^')
        return up;
    else if (c == 'v')
        return down;
    else if (c == '<')
        return left;
    else if (c == '>')
        return right;
    return 0;
}

int is_loop(int* pos, std::vector<std::string> map){
    int loop_flag = 0;
    int steps = 0;
    std::vector<std::vector<int>> visited(map.size(), std::vector<int>(map[0].size(), 0));
    while (true){
        if (is_about_to_escape(pos, map))
            break;
        make_step(pos, map, visited);
        steps++;
        if (visited[pos[0]][pos[1]] & get_state(map[pos[0]][pos[1]])){
            loop_flag = 1;
            break;
        }
        // std::cout << "Pos: " << pos[0] << " " << pos[1] << std::endl;
        // std::cout << "Steps: " << steps << std::endl;
    }
    return loop_flag;
}

int main() {
    // std::ifstream file("input06test.txt");
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
    int total = 0;
    int done = 0;
    for (int i = 0; i < map.size(); ++i){
        for (int j = 0; j < map[i].size(); ++j){
            if (map[i][j] == '.'){
                //std::cout << "i: " << i << " j: " << j << std::endl;
                auto temp_map = map;
                int temp_pos[2] = {pos[0], pos[1]};
                temp_map[i][j] = '#';
                total += is_loop(temp_pos, temp_map);
            }
            done++;
            if (done % 100 == 0)
                std::cout << "Progress: " << done <<  "/" <<  map.size() * map[1].size() << "\r" << std::flush; 
        }
    }
    std::cout << "Total number of loops: " << total << std::endl;
    return 0;
}

// 4602