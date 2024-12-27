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


#define MAX_SCORE 100000000000

bool left_deadend(int i, int j, std::vector<std::string>& data){
    return data[i - 1][j] == '#' && data[i + 1][j] == '#' && data[i][j - 1] == '#';
}

bool right_deadend(int i, int j, std::vector<std::string>& data){
    return data[i - 1][j] == '#' && data[i + 1][j] == '#' && data[i][j + 1] == '#';
}

bool up_deadend(int i, int j, std::vector<std::string>& data){
    return data[i][j - 1] == '#' && data[i][j + 1] == '#' && data[i - 1][j] == '#';
}

bool down_deadend(int i, int j, std::vector<std::string>& data){
    return data[i][j - 1] == '#' && data[i][j + 1] == '#' && data[i + 1][j] == '#';
}

int fill_deadends(std::vector<std::string>& data){
    int count = 0;
    for (int i = 0; i < data.size(); i++){
        std::cout << data[i] << std::endl;
    }
    std::vector<std::pair<int,int>> deadends;
    for (int i = 1; i < data.size() -1; i++){
        for (int j = 1; j < data[i].size() - 1; j++){
            if (data[i][j] == '.'){
                std::pair<int,int> p(j, i);
                //left
                if (left_deadend(i, j, data)){
                    deadends.push_back(p);
                    for (int k = j; k < data[i].size(); k++){
                        if (left_deadend(i, k, data)){
                            data[i][k] = '#';
                            count++;
                        }
                    }
                }
                //right
                else if (right_deadend(i, j, data)){
                    deadends.push_back(p);
                    for (int k = j; k >= 0; k--){
                        if (right_deadend(i, k, data)){
                            data[i][k] = '#';
                            count++;
                        }
                    }
                }
                //up
                else if (up_deadend(i, j, data)){
                    deadends.push_back(p);
                    for (int k = i; k < data.size(); k++){
                        if (up_deadend(k, j, data)){
                            data[k][j] = '#';
                            count++;
                        }
                    }
                }
                //down
                else if (down_deadend(i, j, data)){
                    deadends.push_back(p);
                    for (int k = i; k >= 0; k--){
                        if (down_deadend(k, j, data)){
                            data[k][j] = '#';
                            count++;
                        }
                    }
                }
            }
        }
    }
    return count;
}

struct State{
    int x;
    int y;
    char state;
    long score;
};

long min3(long a, long b, long c){
    return std::min(a, std::min(b, c));
}

long min_score(std::vector<std::string> data, std::vector<std::vector<std::map<char, long>>>& scores, State s){
    if (data[s.y][s.x] == 'E'){
        if (s.score > scores[s.y][s.x][s.state]){
            return MAX_SCORE;
        }
        scores[s.y][s.x][s.state] = s.score;
        for (char c : "><v^")
            std::cout << c << "=" << scores[s.y][s.x][c] << std::endl;
        
        // std::cout << "EEE " << s.score << std::endl;
        // for (int i = 0; i < data.size(); i++){
        //      std::cout << data[i] << std::endl;
        // }
        return s.score;
    }
    if (data[s.y][s.x] != '.'){
        // std::cout << "no way" << std::endl;
        // std::cout << "x=" << s.x << " y=" << s.y << " state=" << s.state << " score=" << s.score << std::endl;
        // for (int i = 0; i < data.size(); i++){
        //     std::cout << data[i] << std::endl;
        // }
        return MAX_SCORE;
    }
    if (s.score > scores[s.y][s.x][s.state] + 1000){
        // std::cout << "score to big" << std::endl;
        return MAX_SCORE;
    }
    scores[s.y][s.x][s.state] = s.score;
    data[s.y][s.x] = s.state;
    long right = MAX_SCORE;
    long left = MAX_SCORE;
    long front = MAX_SCORE;
    if (s.state == '>'){
        front = min_score(data, scores, State{s.x + 1, s.y, s.state, s.score + 1});
        right = min_score(data, scores, State{s.x, s.y + 1, 'v', s.score + 1001});
        left = min_score(data, scores, State{s.x, s.y - 1, '^', s.score + 1001});
    }
    else if (s.state == '<'){
        front = min_score(data, scores, State{s.x - 1, s.y, s.state, s.score + 1});
        right = min_score(data, scores, State{s.x, s.y - 1, '^', s.score + 1001});
        left = min_score(data, scores, State{s.x, s.y + 1, 'v', s.score + 1001});
    }
    else if (s.state == 'v'){
        front = min_score(data, scores, State{s.x, s.y + 1, s.state, s.score + 1});
        right = min_score(data, scores, State{s.x - 1, s.y, '<', s.score + 1001});
        left = min_score(data, scores, State{s.x + 1, s.y, '>', s.score + 1001});
    }
    else if (s.state == '^'){
        front = min_score(data, scores, State{s.x, s.y - 1, s.state, s.score + 1});
        right = min_score(data, scores, State{s.x + 1, s.y, '>', s.score + 1001});
        left = min_score(data, scores, State{s.x - 1, s.y, '<', s.score + 1001});
    }
    return min3(front, right, left);
}

int main() {
    std::ifstream file("input.txt");
    // std::ifstream file("input-test.txt");
    // std::ifstream file("input-test2.txt");

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

    // while (true){
    //     int count = fill_deadends(data);
    //     std::cout << "count=" << count << std::endl;
    //     if (count == 0)
    //         break;
    // }

    for (int i = 0; i < data.size(); i++){
        std::cout << data[i] << std::endl;
    }
    
    //return 0;
    // for (int i = 0; i < deadends.size(); i++){
    //     data[deadends[i][1]][deadends[i][0]] = '#';
    // }
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

    long best_score = 150557;
    std::vector<std::vector<std::map<char, long>>> scores(data.size(), std::vector<std::map<char, long>>(data[0].size()));
    for (int i = 0; i < data.size(); i++){
        for (int j = 0; j < data[i].size(); j++){
            for (char c: "><v^"){
                scores[i][j][c] = best_score;
            }
        }
    }
    std::vector<std::vector<std::map<char, long>>> scores_saved(scores);
    // long left = min_score(data, scores, State{x, y,   '<', 0});
    // std::cout << "left=" << left << std::endl;
    long right = min_score(data, scores, State{x + 1, y,   '>', 2001});
    std::cout << "right=" << right << std::endl;
    long up = min_score(data, scores, State{x, y - 1,   '^', 1001});
    std::cout << "up=" << up << std::endl;
    // long down = min_score(data, scores, State{x, y,   'v', 1000});
    // std::cout << "down=" << down << std::endl;
    // long total = min3(left, right, min3(up, down, best_score));
    //long total = std::min(right, up);
    std::cout << "min score=" << total << std::endl;
    for (char c: "><v^"){
        std::cout << c << "->" << scores[1][data[0].size() - 2][c];
        std::cout << std::endl;
    }
    //std::cout << "number of scores=" << scores.size() << std::endl;
    //std::cout << "total2=" << std::numeric_limits<long>::max() << std::endl;
    return 0;
}

// 241860 too high
//116476