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


#define MAX_SCORE 100000000
struct State{
    int x;
    int y;
    char state;
    long score;
    //std::vector<long> scores;
};

long min3(long a, long b, long c){
    return std::min(a, std::min(b, c));
}

long min4(long a, long b, long c, long d){
    return std::min(a, std::min(b, std::min(c, d)));
}

long min_dict(std::map<char,long> dict){
    long min_value = MAX_SCORE;
    for (char c : "><v^"){
        if (dict[c] < min_value)
            min_value = dict[c];
    }
    return min_value;
}


long min_score(std::vector<std::string> data, std::vector<std::vector<long>>& scores
    , State s)
    {
    if (data[s.y][s.x] == 'E'){
        if (s.score > scores[s.y][s.x])
            return MAX_SCORE;
        std::cout << "EEE " << s.score << std::endl;
        // for (int i = 0; i < data.size(); i++){
        //     std::cout << data[i] << std::endl;
        // }
        scores[s.y][s.x] = s.score;
        return s.score;
    }
    if (data[s.y][s.x] != '.')
        return MAX_SCORE;
    if (s.score >= scores[s.y][s.x])
        return MAX_SCORE;
    //std::cout << "x=" << s.x << ", y=" << s.y << ", score=" << s.score << std::endl;
    scores[s.y][s.x] = s.score;
    data[s.y][s.x] = s.state;
    long right = MAX_SCORE;
    long left = MAX_SCORE;
    long front = MAX_SCORE;
    long up = MAX_SCORE;
    if (s.state == '>'){
        front = min_score(data, scores, State{s.x + 1, s.y, '>', s.score + 1});
        right = min_score(data, scores, State{s.x, s.y + 1, 'v', s.score + 1});
        left = min_score(data, scores, State{s.x, s.y - 1, '^', s.score + 1});
        up = min_score(data, scores, State{s.x - 1, s.y, '<', s.score + 1});
    }
    if (s.state == 'v'){
        right = min_score(data, scores, State{s.x, s.y + 1, 'v', s.score + 1});
        front = min_score(data, scores, State{s.x + 1, s.y, '>', s.score + 1});
        left = min_score(data, scores, State{s.x, s.y - 1, '^', s.score + 1});
        up = min_score(data, scores, State{s.x - 1, s.y, '<', s.score + 1});
    }
    else {
        front = min_score(data, scores, State{s.x + 1, s.y, '>', s.score + 1});
        right = min_score(data, scores, State{s.x, s.y + 1, 'v', s.score + 1});
        left = min_score(data, scores, State{s.x, s.y - 1, '^', s.score + 1});
        up = min_score(data, scores, State{s.x - 1, s.y, '<', s.score + 1});
    }
    return min4(front, right, left, up);
}

int main() {
    // std::ifstream file("input.txt");
    // size_t size = 71;
    // size_t num_bytes = 1024;
    std::ifstream file("input-test.txt");
    size_t size = 7;
    size_t num_bytes = 20; //12;
    // std::ifstream file("input-test2.txt");

    if (!file.is_open()){
        std::cerr << "Failed to open file" << std::endl;
        return 1;
    }
    std::string line;
    std::vector<std::vector<int>> data;
    size_t count_bytes = 0;
    while (std::getline(file, line) && count_bytes < num_bytes){
        size_t pos = line.find(',');
        int num1 = std::stoi(line.substr(0, pos));
        int num2 = std::stoi(line.substr(pos + 1));
        data.push_back({num1, num2});
        count_bytes++;
    }
    file.close();
    for (const auto& d : data){
        std::cout << d[0] << ", " << d[1] << std::endl;
    }
    std::vector<std::string> map(size + 2, std::string(size + 2, '.'));
    for (size_t i = 0; i < data.size(); i++){
        map[data[i][1] + 1][data[i][0] + 1] = '#';
    }
    for (size_t i = 0; i < size + 2; i++){
        map[0][i] = '#';
        map[i][0] = '#';
        map[size + 1][i] = '#';
        map[i][size + 1] = '#';
    }
    map[size][size] = 'E';

    while (true){
        int count = fill_deadends(map);
        std::cout << "count=" << count << std::endl;
        if (count == 0)
            break;
    }

    for (size_t i = 0; i < size + 2; i++)
            std::cout << map[i] << std::endl;
    
    std::vector<std::vector<long>> scores(size + 2, std::vector<long>(size + 2, MAX_SCORE));
    long total0 = min_score(map, scores, State{1, 1, '>',0});
    long total1 = min_score(map, scores, State{1, 1, 'v',0});
    std::cout << "min score=" << total0 << total1 << std::endl;


    return 0;
}
