#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>
#include <map>

int main() {
    std::ifstream file("input05.txt");
    if (!file.is_open()){
        std::cerr << "Failed to  open file" << std::endl;
        return 1;
    }
    std::string line;
    std::vector<std::string> map;
    int i = 0;  
    while (std::getline(file, line)){
        map.push_back(line);
        line.find(" ");
    }
    file.close();
    int pos[2] = {-1, -1};
    for (int i = 0; i < map.size(); ++i){
        for (int j = 0; j < line.size(); ++j){
            if (line[j] == '>' || line[j] == '<' || line[j] == '^' || line[j] == 'v'){
                std::cout << "Guard ound: " << line[j] << " at " << i << " " << j << std::endl;
                pos[0] = i;
                pos[1] = j;
                break;
            }
        }
        if (pos[0] != -1)
            break;
    }
    
    return 0;
}
//6267