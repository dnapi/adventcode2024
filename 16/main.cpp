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

#include <limits>

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

long min_score(int x, int y, std::vector<std::string> data, char state, long s_score, std::vector<long>& scores){
        
        if (data[y][x] == 'E'){
            std::cout << "$$ EEE $$" << std::endl;
            std::cout << "s_score=" << s_score << std::endl;
            scores.push_back(s_score);
            long min_value = *std::min_element(scores.begin(), scores.end());
            std::cout << "min_value=" << min_value << std::endl;
            // for (int i = 0; i < data.size(); i++){
            //     std::cout << data[i] << std::endl;
            // }
            return s_score;
        }
        if (data[y][x] != '.'){
            //std::cout << "hit-#";
            return 100000000000;
        }
        long front = 100000000000;
        long left =  100000000000;
        long right = 100000000000;
        data[y][x] = state;
        //std::cout << state;
        if (state == '>'){
            front = min_score(x + 1, y, data, '>', s_score + 1, scores);
            left = min_score(x, y - 1, data, '^', s_score + 1001, scores);
            right = min_score(x, y + 1, data, 'v', s_score + 1001, scores);
        }
        else if (state == '<') {
            front = min_score(x - 1, y, data, '<', s_score + 1, scores);
            left = min_score(x, y + 1, data, 'v', s_score + 1001, scores);
            right = min_score(x, y - 1, data, '^', s_score + 1001, scores);
        }
        else if (state == 'v') {
            front = min_score(x, y + 1, data, 'v', s_score + 1, scores);
            left = min_score(x + 1, y, data, '>', s_score + 1001, scores);
            right = min_score(x - 1, y, data, '<', s_score + 1001, scores);
        }
        else if (state == '^') {
            front = min_score(x, y - 1, data, '^', s_score + 1, scores);
            left = min_score(x - 1, y, data, '<', s_score + 1001, scores);
            right = min_score(x + 1, y, data, '>', s_score + 1001, scores);
        }
        long score = std::min(front, std::min(left, right));
        // if (score == std::numeric_limits<long>::max())
        //     std::cout << "#";
        // else
        //     std::cout << "s";
        return score;
}

long min_score(int x, int y, std::vector<std::string> data, char state, long s_score){
    
    if (data[y][x] == 'E'){
        std::cout << "$$ EEE $$" << std::endl;
        std::cout << "s_score=" << s_score << std::endl;
        for (int i = 0; i < data.size(); i++){
            std::cout << data[i] << std::endl;
        }
        return s_score;
    }
    if (data[y][x] != '.'){
        //std::cout << "hit-#";
        return 100000000000;
    }
    long front = 100000000000;
    long left =  100000000000;
    long right = 100000000000;
    data[y][x] = state;
    //std::cout << state;
    if (state == '>'){
        front = min_score(x + 1, y, data, '>', s_score + 1);
        left = min_score(x, y - 1, data, '^', s_score + 1001);
        right = min_score(x, y + 1, data, 'v', s_score + 1001);
    }
    else if (state == '<') {
        front = min_score(x - 1, y, data, '<', s_score + 1);
        left = min_score(x, y + 1, data, 'v', s_score + 1001);
        right = min_score(x, y - 1, data, '^', s_score + 1001);
    }
    else if (state == 'v') {
        front = min_score(x, y + 1, data, 'v', s_score + 1);
        left = min_score(x + 1, y, data, '>', s_score + 1001);
        right = min_score(x - 1, y, data, '<', s_score + 1001);
    }
    else if (state == '^') {
        front = min_score(x, y - 1, data, '^', s_score + 1);
        left = min_score(x - 1, y, data, '<', s_score + 1001);
        right = min_score(x + 1, y, data, '>', s_score + 1001);
    }
    long score = std::min(front, std::min(left, right));
    // if (score == std::numeric_limits<long>::max())
    //     std::cout << "#";
    // else
    //     std::cout << "s";
    return score;
}

int main() {
    // std::ifstream file("input.txt");
    //std::ifstream file("input-test.txt");
    std::ifstream file("input-test2.txt");

    if (!file.is_open()){
        std::cerr << "Failed to open file" << std::endl;
        return 1;
    }
    std::string line;
    std::vector<std::string> data;
    while (std::getline(file, line)){
        data.push_back(line);
    }
    file.close();

    for (int i = 0; i < data.size(); i++){
        std::cout << data[i] << std::endl;
    }
    int x = 0;
    int y = 0;
    for (int i = 0; i < data.size(); i++){
        for (int j = 0; j < data[i].size(); j++){
            if (data[i][j] == 'S'){
                x = j;
                y = i;
                data[i][j] = '.';
            }
        }
    }
    std::vector<long> scores;
    long right = min_score(x + 1, y, data, '>', 1000 * 2 + 1, scores);
    std::cout << std::endl;
    std::cout << "right=" << right << std::endl;
    long up = min_score(x, y - 1, data, '^', 1000 + 1, scores);
    std::cout << std::endl;
    std::cout << "up=" << up << std::endl;
    long total = std::min(right, up);
    int total2 = 0;
    std::cout << "total=" << total << std::endl;
    //std::cout << "total2=" << std::numeric_limits<long>::max() << std::endl;
    return 0;
}

// 241860 too high