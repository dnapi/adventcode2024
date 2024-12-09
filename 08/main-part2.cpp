#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <iostream>
#include <vector>
#include <string>
#include <map>

int main() {
    // std::ifstream file("input08test.txt");
    std::ifstream file("input08.txt");
    if (!file.is_open()){
        std::cerr << "Failed to  open file" << std::endl;
        return 1;
    }
    std::string line;
    std::map<char, std::vector<std::vector<int>>> map;  
    std::vector<std::string> data;
    int i = 0;
    while (std::getline(file, line)){
        data.push_back(line);
        for (int j = 0; j < line.size(); ++j){
            if (line[j] != '.'){
                map[line[j]].push_back({i, j});
            }
        }
        ++i;
    }
    file.close();
    // for (auto& line : data){
    //     std::cout << line << std::endl;
    // }
    std::vector<std::string> antidot_map = data;
    int total = 0;
    for (const auto& [key, coord] : map){
        std::cout << key << ": ";
        for (const auto& v : coord){
            std::cout << v[0] << " " << v[1] << " | ";
        }
        std::cout << std::endl;
        int delta_freq = 0;
        for (int i = 0; i < coord.size(); ++i){
            for (int j = i + 1; j < coord.size(); ++j){
                int delta_pair = 0;
                std::cout << "(" << coord[i][0] << " " << coord[i][1] << ")";
                std::cout << "(" << coord[j][0] << " " << coord[j][1] << ")";
                int delta_i = coord[i][0] - coord[j][0];
                int delta_j = coord[i][1] - coord[j][1];
                int k = 0;
                while (true){
                    int antidot1_i = coord[i][0] + delta_i * k;
                    int antidot1_j = coord[i][1] + delta_j * k;
                    k++;
                    if (antidot1_i >= 0 && antidot1_i < data.size() && 
                        antidot1_j >= 0 && antidot1_j < data[0].size() 
                        //&& data[antidot1_i][antidot1_j] == '.'
                    ){
                        delta_pair += 1;
                        antidot_map[antidot1_i].at(antidot1_j) = '#';
                    }
                    else
                        break;
                }
                k = 0;
                while (true){
                    int antidot2_i = coord[j][0] - delta_i * k;
                    int antidot2_j = coord[j][1] - delta_j * k;
                    k++;
                    if (antidot2_i >= 0 && antidot2_i < data.size() && 
                        antidot2_j >= 0 && antidot2_j < data[0].size() 
                        //&& data[antidot2_i][antidot2_j] == '.'
                    ){
                        delta_pair += 1;
                        antidot_map[antidot2_i].at(antidot2_j) = '#';
                    }
                    else
                        break;
                }

                int antidot2_i = coord[j][0] - delta_i;
                int antidot2_j = coord[j][1] - delta_j;
                if (antidot2_i >= 0 && antidot2_i < data.size() && 
                    antidot2_j >= 0 && antidot2_j < data[0].size() 
                    //&& data[antidot2_i][antidot2_j] == '.'
                ){
                    delta_pair += 1;
                    antidot_map[antidot2_i].at(antidot2_j) = '#';
                }
                std::cout << "-" << delta_pair << std::endl;
                delta_freq += delta_pair;
            }
        }
        total += delta_freq;
        std::cout << "delta_freq=" << delta_freq;
        std::cout << std::endl;
    }
    std::cout << "total=" << total << std::endl;
    total = 0;
    for (const auto& line : antidot_map){
        for (const auto& c : line){
            if (c == '#'){
                total += 1;
            }
        }
    }
    std::cout << "Answer=" << total << std::endl;
    return 0;
}

//1157
