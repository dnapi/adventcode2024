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

struct State{
    int x;
    int y;
    char state;
    long score;
    std::string states;
    //std::vector<long> scores;
};

long min3(long a, long b, long c){
    return std::min(a, std::min(b, c));
}

long min_dict(std::map<char,long> dict){
    long min_value = MAX_SCORE;
    for (char c : "><v^"){
        if (dict[c] < min_value)
            min_value = dict[c];
    }
    return min_value;
}


//mininam score without cheating
long min_score(std::vector<std::string> data
        , std::vector<std::vector<std::map<char, long>>>& scores
        , std::map<long,std::set<std::pair<int, int>>>& tiles_map
        , State s)
    {
    if (data[s.y][s.x] == 'E'){
        if (s.score > min_dict(scores[s.y][s.x])){
            return MAX_SCORE;
        }
    //part 2
        for (int i = 0; i < data.size(); i++){
            for (int j = 0; j < data[i].size(); j++){
                if (data[i][j] == '>' || data[i][j] == '<' || data[i][j] == '^' || data[i][j] == 'v'){
                    std::pair<int,int> p(j, i);
                    tiles_map[s.score].insert(p);
                }
            }
        }
        std::cout << "EEE " << s.score << std::endl;
        scores[s.y][s.x][s.state] = s.score;
        for (char c : "><v^")
            std::cout << c << "=" << scores[s.y][s.x][c] << std::endl;
        std::cout << "steps=" << s.states << std::endl;
        std::cout << "num of steps= " << s.states.size() << std::endl;
        // long turns = 0;
        // for (int i = 1; i < s.states.size(); i++){
        //     if (s.states[i] != s.states[i - 1])
        //         turns++;
        // }
        // std::cout << "turns:=" << turns << std::endl;
        
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
    if (s.score > scores[s.y][s.x][s.state]){
        // std::cout << "score to big" << std::endl;
        return MAX_SCORE;
    }
    scores[s.y][s.x][s.state] = s.score;
    data[s.y][s.x] = s.state;
    long right = MAX_SCORE;
    long left = MAX_SCORE;
    long front = MAX_SCORE;
    if (s.state == '>'){
        front = min_score(data, scores, tiles_map, State{s.x + 1, s.y, s.state, s.score + 1, s.states + s.state});
        right = min_score(data, scores, tiles_map, State{s.x, s.y + 1, 'v', s.score + 1, s.states + s.state});
        left = min_score(data, scores, tiles_map, State{s.x, s.y - 1, '^', s.score + 1, s.states + s.state});
    }
    else if (s.state == '<'){
        front = min_score(data, scores, tiles_map, State{s.x - 1, s.y, s.state, s.score + 1, s.states + s.state});
        right = min_score(data, scores, tiles_map, State{s.x, s.y - 1, '^', s.score + 1, s.states + s.state});
        left = min_score(data, scores, tiles_map, State{s.x, s.y + 1, 'v', s.score + 1, s.states + s.state});
    }
    else if (s.state == 'v'){
        front = min_score(data, scores, tiles_map, State{s.x, s.y + 1, s.state, s.score + 1, s.states + s.state});
        right = min_score(data, scores, tiles_map, State{s.x - 1, s.y, '<', s.score + 1, s.states + s.state});
        left = min_score(data, scores, tiles_map, State{s.x + 1, s.y, '>', s.score + 1, s.states + s.state});
    }
    else if (s.state == '^'){
        front = min_score(data, scores, tiles_map, State{s.x, s.y - 1, s.state, s.score + 1, s.states + s.state});
        right = min_score(data, scores, tiles_map, State{s.x + 1, s.y, '>', s.score + 1, s.states + s.state});
        left = min_score(data, scores, tiles_map, State{s.x - 1, s.y, '<', s.score + 1, s.states + s.state});
    }
    return min3(front, right, left);
}

long manhattan(int x1, int y1, int x2, int y2){
    return abs(x1 - x2) + abs(y1 - y2);
}

#define CHEAT_TIME 20
void find_cheats(std::vector<std::vector<long>>& data, int x, int y, std::vector<long>& saved_scores){
    if (x < 1 || y < 1 || x >= data[0].size() - 1 || y >= data.size() - 1) // outter walls
        return;
    int x_min = x - CHEAT_TIME > 0 ? x - CHEAT_TIME : 1;
    int x_max = x + CHEAT_TIME < data[0].size() - 1 ? x + CHEAT_TIME : data[0].size() - 2;
    int y_min = y - CHEAT_TIME > 0 ? y - CHEAT_TIME : 1;
    int y_max = y + CHEAT_TIME < data.size() - 1 ? y + CHEAT_TIME : data.size() - 2;
    //std::cout << "x=" << x << " y=" << y << std::endl;
    // std::cout << "x_min=" << x_min << " x_max=" << x_max << " y_min=" << y_min << " y_max=" << y_max << std::endl;
    for (int j = y_min; j <= y_max; j++){
        for (int i = x_min; i <= x_max; i++){
            if (data[j][i] < 0)
                continue;
            long saved_score = data[j][i] - data[y][x] - manhattan(x, y, i, j);
            if (manhattan(x, y, i, j) > CHEAT_TIME)
                continue;
            if (saved_score > 0){
                // std::cout << "i=" << i << " j=" << j 
                //     << " saved_score=" << saved_score 
                //     << " data= ji " << data[j][i]
                //     << " data= yx " << data[y][x]
                //     << " manhattan=" << manhattan(x, y, i, j)
                //     << std::endl;
                saved_scores.push_back(saved_score);
            }
        }

        
    }
}

void find_all_cheats(std::vector<std::vector<long>>& data, int x, int y, std::vector<long>& saved_scores){
    if (x < 1 || y < 1 || x >= data[0].size() - 1 || y >= data.size() - 1) // outter walls
        return;
    if (data[y][x] < 0)
        return;
    find_cheats(data, x, y, saved_scores);
    if (data[y][x + 1] > data[y][x]){
        find_all_cheats(data, x + 1, y, saved_scores);
        return;
    }
    if (data[y][x - 1] > data[y][x]){
        find_all_cheats(data, x - 1, y, saved_scores);
        return;
    }
    if (data[y + 1][x] > data[y][x]){
        find_all_cheats(data, x, y + 1, saved_scores);
        return;
    }
    if (data[y - 1][x] > data[y][x]){
        find_all_cheats(data, x, y - 1, saved_scores);
        return;
    }
    
}

int main() {
    // long top_limiit = 0;
    // std::ifstream file("input-test.txt");

    long top_limiit = 100;
    std::ifstream file("input.txt");

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
    // find the start position  (x,y)
    for (int i = 0; i < data.size(); i++){
        for (int j = 0; j < data[i].size(); j++){
            if (data[i][j] == 'S'){
                x = j;
                y = i;
                data[i][j] = '.';
            }
        }
    }

    long best_score = 1505570;
    // matrix of scores
    std::vector<std::vector<std::map<char, long>>> scores(data.size(), std::vector<std::map<char, long>>(data[0].size()));
    for (int i = 0; i < data.size(); i++){
        for (int j = 0; j < data[i].size(); j++){
            for (char c: "><v^"){
                scores[i][j][c] = best_score;
            }
        }
    }
    std::vector<std::vector<std::map<char, long>>> scores_saved(scores);
    std::map<long,std::set<std::pair<int, int>>> tiles_map;

    //First we find regular path
    long left = min_score(data, scores, tiles_map, State{x - 1, y, '<', 1, ""});
    std::cout << "left=" << left << std::endl;
    long up = min_score(data, scores, tiles_map, State{x, y - 1,   '^', 1, ""});
    std::cout << "up=" << up << std::endl;
    long total = std::min(left, up);
    std::cout << "min score=" << total << std::endl;
    long total2 = 0;
    for (auto& [key,value] : tiles_map){
        if (key == total){
            total2 = value.size();
            break;
        }
    }
    std::cout << "total2=" << total2 << std::endl;
    std::vector<std::vector<long>> best_scores(data.size(), std::vector<long>(data[0].size(), best_score));
    best_scores[y][x] = 0;
    for (int i = 0; i < data.size(); i++){
        for (int j = 0; j < data[i].size(); j++){
            for (char c: "><v^"){
                best_scores[i][j] = std::min(best_scores[i][j], scores[i][j][c]);
            }
            if (best_scores[i][j] == best_score)
                best_scores[i][j] = - MAX_SCORE;
            if (best_scores[i][j] == -MAX_SCORE)
                std::cout << "# ";
            else
                std::cout << best_scores[i][j] << " ";
        }
        std::cout << std::endl;
    }
    // Second part starts here.
    std::cout << "finding cheats" << "x=" << x << " y=" << y << std::endl;
    std::vector<long> cheats = {};
    find_all_cheats(best_scores, x, y, cheats);
    // find_cheats(best_scores, x, y, cheats);
    std::cout << "num of cheats = " << cheats.size() << std::endl;
    long total0 = 0;
    long max_cheat = 0;
    std::vector<long> count_scores(100000,0);
    for (int i = 0; i < cheats.size(); i++){
        if (cheats[i] >=0){
            count_scores[cheats[i]]++;
      //      std::cout << cheats[i] << " ";
            total0++;
            if (cheats[i] > max_cheat)
                max_cheat = cheats[i];
        }
    }
    std::cout << std::endl;
    long top100cheats = 0;
    for (int i = top_limiit; i < count_scores.size(); i++){
        if (count_scores[i] > 0){
           std::cout  
                << " count=" << count_scores[i] 
                << " i=" << i
                << std::endl;

            top100cheats += count_scores[i];
            //std::cout << "top100cheats=" << top100cheats << std::endl;
        }
    }
    std::cout << "total0=" << total0 << std::endl;
    std::cout << "max_cheat=" << max_cheat << std::endl;
    std::cout << "top100cheats=" << top100cheats << std::endl;
    return 0;
}

//top100cheats=2388801  too high
