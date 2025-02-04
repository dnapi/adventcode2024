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

long min_score(std::vector<std::string> data, std::vector<std::vector<std::map<char, long>>>& scores
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
        // for (int i = 0; i < data.size(); i++){
        //      std::cout << data[i] << std::endl;
        // }
        scores[s.y][s.x][s.state] = s.score;
        for (char c : "><v^")
            std::cout << c << "=" << scores[s.y][s.x][c] << std::endl;
        std::cout << "steps=" << s.states << std::endl;
        std::cout << "num of steps= " << s.states.size() << std::endl;
        long turns = 0;
        for (int i = 1; i < s.states.size(); i++){
            if (s.states[i] != s.states[i - 1])
                turns++;
        }
        std::cout << "turns:=" << turns << std::endl;
        
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

void get_deltas(std::vector<std::vector<long>>& data
    , int x, int y
    , long num_cheats
    , long start_score
    , std::vector<long>& cheat_scores
    );
void get_next_deltas(
    std::vector<std::vector<long>>& data
    , int x, int y
    , int next_x, int next_y
    , long num_cheats
    , long start_score
    , std::vector<long>& cheat_scores
    ){
    long next_score = data[next_y][next_x];
    if (next_score < 0 && num_cheats <=  -next_score){ // on cheat
        std::cout << "on cheat" << num_cheats << std::endl;
        data[next_y][next_x] =  -num_cheats;
        get_deltas(data, next_x, next_y, num_cheats, start_score, cheat_scores);
    }
}

void get_deltas(std::vector<std::vector<long>>& data
    , int x, int y
    , long num_cheats
    , long start_score
    , std::vector<long>& cheat_scores
    ){
    if (x < 1 || y < 1 || x >= data[0].size() - 1 || y >= data.size() - 1 || num_cheats > 20)
        return;
    if (data[y][x] > start_score){
        std::cout << "back to regular path" << std::endl;
        cheat_scores[data[y][x]] = std::max(cheat_scores[data[y][x]], data[y][x] - start_score - num_cheats);
        return;
    }
    get_next_deltas(data, x, y, x + 1, y, num_cheats + 1, start_score, cheat_scores);// right
    get_next_deltas(data, x, y, x - 1, y, num_cheats + 1, start_score, cheat_scores);// left
    get_next_deltas(data, x, y, x, y + 1, num_cheats + 1, start_score, cheat_scores);// down
    get_next_deltas(data, x, y, x, y - 1, num_cheats + 1, start_score, cheat_scores);// up
}

void find_scores(std::vector<std::vector<long>> data, int x, int y, std::vector<long>& saved_scores);
void check_next(
    std::vector<std::vector<long>> data
    , int cur_x, int cur_y
    , int next_x, int next_y
    , long start_score, long num_cheats
    , std::vector<long>& saved_scores
    ){
    long next_score = data[next_y][next_x];
    long cur_score = data[cur_y][cur_x];
    if (next_score > cur_score){  // regular path
        std::cout << "regular path step " << next_score << " xy=" << next_x << " " << next_y << std::endl;
        find_scores(data, next_x, next_y, saved_scores);
    }
    else {
        std::cout << "cheat path step " << next_score << " xy=" << next_x << " " << next_y << std::endl;
        std::vector<long> cheat_scores(10000,-1);
        std::vector<std::vector<long>> data_copy(data);
        get_deltas(data_copy, next_x, next_y, 1, start_score, cheat_scores);
        for (int i = 0; i < cheat_scores.size(); i++){
            if (cheat_scores[i] != -1){
                saved_scores.push_back(cheat_scores[i]);
          //      std::cout << "cheat score right =" << cheat_scores[i] << " i= " <<  i << std::endl;
            }
        }
        for (int i = 0; i < data_copy.size(); i++){
            for (int j = 0; j < data_copy[i].size(); j++){
                if (data_copy[i][j] == - MAX_SCORE){
                    data_copy[i][j] = 0;
                }
                std::cout << data_copy[i][j] << " ";
            }
            std::cout << std::endl;
        }

    }
}

void find_scores(std::vector<std::vector<long>> data, int x, int y, std::vector<long>& saved_scores){
    if (x < 1 || y < 1 || x >= data[0].size() - 1 || y >= data.size() - 1)
        return;
    if (data[y][x] >= 1)
        return;
    check_next(data, x, y, x + 1, y, data[y][x], 1, saved_scores);// right
    check_next(data, x, y, x - 1, y, data[y][x], 1, saved_scores);// left
    check_next(data, x, y, x, y + 1, data[y][x], 1, saved_scores);// down
    check_next(data, x, y, x, y - 1, data[y][x], 1, saved_scores);// up
}

int main() {
    // std::ifstream file("input.txt");
    std::ifstream file("input-test.txt");

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

    long best_score = 1505570;
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
    // long left = min_score(data, scores, State{x, y,   '<', 0});
    // std::cout << "left=" << left << std::endl;

    long left = min_score(data, scores, tiles_map, State{x - 1, y, '<', 1, ""});
    std::cout << "left=" << left << std::endl;
    long up = min_score(data, scores, tiles_map, State{x, y - 1,   '^', 1, ""});
    std::cout << "up=" << up << std::endl;
    // long down = min_score(data, scores, State{x, y,   'v', 1000});
    // std::cout << "down=" << down << std::endl;
    // long total = min3(left, right, min3(up, down, best_score));
    long total = std::min(left, up);
    std::cout << "min score=" << total << std::endl;
    for (char c: "><v^"){
        std::cout << c << "->" << scores[1][data[0].size() - 2][c];
        std::cout << std::endl;
    }
    long total2 = 0;
    for (auto& [key,value] : tiles_map){
        if (key == total){
            total2 = value.size();
            break;
        }
    }
    std::cout << "total2=" << total2 << std::endl;
    //std::vector<std::vector<std::map<char, long>>> scores_saved(scores);
    std::vector<std::vector<long>> best_scores(data.size(), std::vector<long>(data[0].size(), best_score));
    best_scores[y][x] = 0;
    for (int i = 0; i < data.size(); i++){
        for (int j = 0; j < data[i].size(); j++){
            for (char c: "><v^"){
                best_scores[i][j] = std::min(best_scores[i][j], scores[i][j][c]);
            }
            if (best_scores[i][j] == best_score)
                best_scores[i][j] = - MAX_SCORE;
            // std::cout << best_scores[i][j] << " ";
        }
        // std::cout << std::endl;
    }
    std::cout << "finding cheats" << "x=" << x << " y=" << y << std::endl;
    std::vector<long> cheats = {};
    find_scores(best_scores, x, y, cheats);
    std::cout << "num of cheats = " << cheats.size() << std::endl;
    long total0 = 0;
    for (int i = 0; i < cheats.size(); i++){
        if (cheats[i] >=0){
            std::cout << cheats[i] << " ";
            total0++;
        }
    }
    std::cout << "total0=" << total0 << std::endl;
    return 0;
}



// 241860 too high
//116476 -2000