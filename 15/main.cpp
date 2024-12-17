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
    else if (data[y][x - 1] == 'O'){
        int empty = x - 1;
        for (; empty >= 0; empty--){
            if (data[y][empty] == '#')
                return;
            if (data[y][empty] == '.')
                break;
        }
        data[y][x] = '.';
        data[y][x - 1] = '@';
        data[y][empty] = 'O';
        x--;
    }
}

void move_up(int &x, int &y, std::vector<std::string>& data){
    if (data[y - 1][x] == '#')
        return;
    if (data[y - 1][x] == '.'){
        data[y][x] = '.';
        data[y - 1][x] = '@';
        y--;
    }
    else if (data[y - 1][x] == 'O'){
        int empty = y - 1;
        for (; empty >= 0; empty--){
            if (data[empty][x] == '#')
                return;
            if (data[empty][x] == '.')
                break;
        }
        data[y][x] = '.';
        data[y - 1][x] = '@';
        data[empty][x] = 'O';
        y--;
    }
}

void move_right(int &x, int &y, std::vector<std::string>& data){
    //std::cout << "x=" << x << " y=" << y << std::endl;
    if (data[y][x + 1] == '#')
        return;
    if (data[y][x + 1] == '.'){
        data[y][x] = '.';
        data[y][x + 1] = '@';
        x++;
    }
    else if (data[y][x + 1] == 'O'){
        int empty = x + 1;
        //std::cout << data[y] << std::endl;
        //std::cout << "empty start=" << empty << std::endl;
        for (; empty < data[y].size(); empty++){
            if (data[y][empty] == 'O')
                continue;
            if (data[y][empty] == '#')
                return;
            if (data[y][empty] == '.')
                break;
        }
        //std::cout << "empty=" << empty << std::endl;
        data[y][x] = '.';
        data[y][x + 1] = '@';
        data[y][empty] = 'O';
        x++;
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
    else if (data[y + 1][x] == 'O'){
        int empty = y + 1;
        for (; empty < data.size(); empty++){
            if (data[empty][x] == '#')
                return;
            if (data[empty][x] == '.')
                break;
        }
        data[y][x] = '.';
        data[y + 1][x] = '@';
        data[empty][x] = 'O';
        y++;
    }
}


int main() {
    std::ifstream file("input.txt");
    //std::ifstream file("input-mini.txt");
    //std::ifstream file("input-small.txt");
    //std::ifstream file("input-part2-test1.txt");

    if (!file.is_open()){
        std::cerr << "Failed to  open file" << std::endl;
        return 1;
    }
    std::string line;
    std::vector<std::string> data;
    while (std::getline(file, line) && !line.empty()){
        data.push_back(line);
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
    int total = 0;
    for (int i = 0; i < data.size(); i++){
        for (int j = 0; j < data[i].size(); j++){
            if (data[i][j] == 'O')
                total += 100 * i + j;
        }
    }
    int total2 = 0;
    std::cout << "total=" << total << std::endl;
    std::cout << "total2=" << total2 << std::endl;
    return 0;
}