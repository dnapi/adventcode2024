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

void move_left(int &x, int &y, std::vector<std::string>& data){
    if (data[y][x - 1] == '#')
        return;
    if (data[y][x - 1] == '.'){
        data[y][x] = '.';
        data[y][x - 1] = '@';
        x--;
    }
    else if (data[y][x - 1] == ']'){
        int empty = x - 1;
        for (; empty >= 0; empty--){
            if (data[y][empty] == '#')
                return;
            if (data[y][empty] == '.')
                break;
        }
        for (; empty <= x - 2; empty++){
            data[y][empty] = data[y][empty + 1];
        }
        data[y][x - 1] = '@';
        data[y][x] = '.';
        x--;
    }
}

void move_right(int &x, int &y, std::vector<std::string>& data){
    if (data[y][x + 1] == '#')
        return;
    if (data[y][x + 1] == '.'){
        data[y][x] = '.';
        data[y][x + 1] = '@';
        x++;
    }
    else if (data[y][x + 1] == '['){
        int empty = x + 1;
        for (; empty < data[y].size(); empty++){
            if (data[y][empty] == '#')
                return;
            if (data[y][empty] == '.')
                break;
        }
        for (; empty >= x + 2; empty--){
            data[y][empty] = data[y][empty - 1];
        }
        data[y][x + 1] = '@';
        data[y][x] = '.';
        x++;
    }
}

bool moveble_up(int x, int y, std::vector<std::string>& data){
    if (data[y][x] == '.')
        return true;
    if (data[y][x] == ']')
        return moveble_up(x - 1, y - 1, data) && moveble_up(x, y - 1, data);
    if (data[y][x] == '[')
        return moveble_up(x, y - 1, data) && moveble_up(x + 1, y - 1, data);
    return false;
}

bool moveble_down(int x, int y, std::vector<std::string>& data){
    if (data[y][x] == '.')
        return true;
    if (data[y][x] == ']')
        return moveble_down(x - 1, y + 1, data) && moveble_down(x, y + 1, data);
    if (data[y][x] == '[')
        return moveble_down(x, y + 1, data) && moveble_down(x + 1, y + 1, data);
    return false;
}

void move_blocks_up(int x, int y, std::vector<std::string>& data){
    if (data[y][x] == '#'){
        std::cout << "Error 1" << std::endl;
        return;
    }
    if (y < 1){
        std::cout << "Error 2" << std::endl;
        return;
    }
    if (data[y][x] == '.')
        return;
    move_blocks_up(x, y - 1, data);
    if (data[y][x] == ']'){
        move_blocks_up(x - 1, y - 1, data);
        data[y - 1][x - 1] = data[y][x - 1];
        data[y][x - 1] = '.';
    }
    else if (data[y][x] == '['){
        move_blocks_up(x + 1, y - 1, data);
        data[y - 1][x + 1] = data[y][x + 1];
        data[y][x + 1] = '.';
    }
    data[y - 1][x] = data[y][x];
    data[y][x] = '.';
}

void move_blocks_down(int x, int y, std::vector<std::string>& data){
    if (data[y][x] == '#'){
        std::cout << "Error 1" << std::endl;
        return;
    }
    if (y >= data.size() - 1){
        std::cout << "Error 2" << std::endl;
        return;
    }
    if (data[y][x] == '.')
        return;
    move_blocks_down(x, y + 1, data);
    if (data[y][x] == ']'){
        move_blocks_down(x - 1, y + 1, data);
        data[y + 1][x - 1] = data[y][x - 1];
        data[y][x - 1] = '.';
    }
    else if (data[y][x] == '['){
        move_blocks_down(x + 1, y + 1, data);
        data[y + 1][x + 1] = data[y][x + 1];
        data[y][x + 1] = '.';
    }
    data[y + 1][x] = data[y][x];
    data[y][x] = '.';
}


void move_up(int &x, int &y, std::vector<std::string>& data){
    if (data[y - 1][x] == '#')
        return;
    if (data[y - 1][x] == '.'){
        data[y][x] = '.';
        data[y - 1][x] = '@';
        y--;
    }
    else if (data[y - 1][x] == '[' || data[y - 1][x] == ']'){
        if (moveble_up(x, y - 1, data)){
            move_blocks_up(x, y - 1, data);
            data[y][x] = '.';
            data[y - 1][x] = '@';
            y--;
        }
    }
}



void move_down(int &x, int &y, std::vector<std::string>& data){
    if (data[y + 1][x] == '#')
        return;
    if (data[y + 1][x] == '.'){
        data[y][x] = '.';
        data[y + 1][x] = '@';
        y++;
    }
    else if (data[y + 1][x] == '[' || data[y + 1][x] == ']'){
        if (moveble_down(x, y + 1, data)){
            move_blocks_down(x, y + 1, data);
            data[y][x] = '.';
            data[y + 1][x] = '@';
            y++;
        }
    }
}


int main() {
    std::ifstream file("input.txt");
    // std::ifstream file("input-mini.txt");
    // std::ifstream file("input-mini2.txt");
    //std::ifstream file("input-small.txt");
    //std::ifstream file("input-part2-test1.txt");

    if (!file.is_open()){
        std::cerr << "Failed to  open file" << std::endl;
        return 1;
    }
    std::string line;
    std::vector<std::string> data;
    while (std::getline(file, line) && !line.empty()){
        std::string line_str(line.size() * 2, '#');
        for (int i = 0; i < line_str.size(); i += 2){
            if (line[i / 2] == 'O'){
                line_str[i] = '[';
                line_str[i + 1] = ']';
                continue;
            }
            if (line[i / 2] != '@'){
                line_str[i] = line[i / 2];
                line_str[i + 1] = line[i / 2];
                continue;
            }
            line_str[i] = '@';
            line_str[i + 1] = '.';
            
        }
        data.push_back(line_str);
    }
    std::string commands;
    while (std::getline(file, line)){
        commands += line.substr(0, line.size());
    }
    file.close();

    for (int i = 0; i < data.size(); i++){
        std::cout << data[i] << std::endl;
    }
    std::cout << commands << std::endl;
//return 0;
    int x = 0;
    int y = 0;
    for (int i = 0; i < data.size(); i++){
        for (int j = 0; j < data[i].size(); j++){
            if (data[i][j] == '@'){
                x = j;
                y = i;
            }
        }
    }
    while (false){
        char c;
        std::cin >> c;
        std::cout << "Move" << c << std::endl;
        if (c == '^')
            move_up(x, y, data);
        else if (c == 'v')
            move_down(x, y, data);
        else if (c == '<')
            move_left(x, y, data);
        else if (c == '>')
            move_right(x, y, data);
        else if (c == 'q')
            break;
        for (int i = 0; i < data.size(); i++){
            std::cout << data[i] << std::endl;
        }
        std::cout << std::endl;
        for (int i =0; i < data.size() + 3; i++){
            std::cout << "\033[A";
        }
    }
    for (char c : commands){
        std::cout << "Move" << c << std::endl;
        if (c == '^')
            move_up(x, y, data);
        else if (c == 'v')
            move_down(x, y, data);
        else if (c == '<')
            move_left(x, y, data);
        else if (c == '>')
            move_right(x, y, data);
        // for (int i = 0; i < data.size(); i++){
        //     std::cout << data[i] << std::endl;
        // }
        // std::cout << std::endl; 
    }
    for (int i = 0; i < data.size(); i++){
        std::cout << data[i] << std::endl;
    }
    std::cout << std::endl; 
    int total = 0;
    for (int i = 0; i < data.size(); i++){
        for (int j = 0; j < data[i].size(); j++){
            if (data[i][j] == '[')
                total += 100 * i + j;
        }
    }
    int total2 = 0;
    std::cout << "total=" << total << std::endl;
    std::cout << "total2=" << total2 << std::endl;
    return 0;
}