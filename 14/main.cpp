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

long location(long x0, long v, long t, long nx){
    if (v < 0){
        return (nx - (-x0 - v * t) % nx) % nx;
    }
    return (x0 + v * t) % nx;
}

int main() {
    std::ifstream file("input.txt");
    // std::ifstream file("input-test.txt");

    if (!file.is_open()){
        std::cerr << "Failed to  open file" << std::endl;
        return 1;
    }
    std::string line;
    std::vector<std::vector<long>> data;
    long time = 100;
    // long nx = 11;
    // long ny = 7;
    long nx = 101;
    long ny = 103;
    while (std::getline(file, line)){
        std::cout << line << std::endl;
        size_t pos_x = line.find("=");
        size_t pos_y = line.find(",");
        size_t pos_space = line.find(" ");
        size_t pos_vx = line.find("=", pos_y);
        size_t pos_vy = line.find(",", pos_vx);
        long x = std::stol(line.substr(pos_x + 1, pos_y - pos_x));
        long y = std::stol(line.substr(pos_y + 1, pos_space - pos_y));
        long vx = std::stol(line.substr(pos_vx + 1, pos_vy - pos_vx));
        long vy = std::stol(line.substr(pos_vy + 1));
        std::vector<long> point = {x, y, vx, vy, 
            location(x, vx, time, nx), 
            location(y, vy, time, ny)};
        data.push_back(point);
    }
    file.close();
    long q_1 = 0;
    long q_2 = 0;
    long q_3 = 0;
    long q_4 = 0;
    std::vector<std::vector<long>> map(ny, std::vector<long>(nx, 0));
    for (int i = 0; i < data.size(); i++){
        std::cout << "i=" << i << " ";
        for (int j = 0; j < data[i].size(); j++){
            std::cout << data[i][j] << " ";
        }
        std::cout << "x=" << data[i][4] << "/" << nx << " y=" << data[i][5] << "/" << ny << std::endl;
        map[data[i][5]][data[i][4]] += 1;
        //std::cout << "size=" << data[i].size() << std::endl;
        if (data[i][4] < nx / 2 && data[i][5] < ny / 2){
            q_1++;
            std::cout << "q1" << std::endl;
        }
        else if (data[i][4] > nx / 2 && data[i][5] < ny / 2){
            q_2++;
            std::cout << "q2" << std::endl;
        }
        else if (data[i][4] < nx / 2 && data[i][5] > ny / 2){
            q_3++;
            std::cout << "q3" << std::endl;
        }
        else if (data[i][4] > nx / 2 && data[i][5] > ny / 2){
            q_4++;
            std::cout << "q4" << std::endl;
        }
        else {
            std::cout << "none" << std::endl;
        }
    }
    for (int i = 0; i < ny; i++){
        for (int j = 0; j < nx; j++){
            if (map[i][j] > 0){
                std::cout << map[i][j];
            }
            else{
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
    long total = q_1 * q_2 * q_3 * q_4;

    std::vector<std::vector<long>> map_t(ny, std::vector<long>(nx, 0));
    int t = 0; 
    long bestCrit = 0;
    for (;t < 1000000; t++){
        q_1 = 0;
        q_2 = 0;
        q_3 = 0;
        q_4 = 0;
        std::vector<std::vector<long>> temp(ny, std::vector<long>(nx, 0));
        for (int i = 0; i < data.size(); i++){
            long xt= location(data[i][0], data[i][2], t, nx);
            long yt = location(data[i][1], data[i][3], t, ny);
            temp[yt][xt] += 1;
            if (xt < nx / 2 &&  yt < ny / 2){
                q_1++;
            }
            else if (xt > nx / 2 && yt < ny / 2){
                q_2++;
            }
            else if (xt < nx / 2 && yt > ny / 2){
                q_3++;
            }
            else if (xt > nx / 2 && yt > ny / 2){
                q_4++;
            }
        }
        for (int i = 1; i < ny - 1; i++){
            for (int j = 1; j < nx - 1 ; j++){
                if (temp[i][j] > 0 && 
                    temp[i-1][j] < 1 && 
                    temp[i+1][j] < 1 && 
                    temp[i][j-1] < 1 && 
                    temp[i][j+1] < 1)
                {
                    temp[i][j] = 0;
                }
            }
        }
        long tempCrit = 0;
        for (int i = 0; i < ny; i++){
            for (int j = 0; j < nx; j++){
                if (temp[i][j] > 0){
                    tempCrit++;
                }
            }
        }
        if (tempCrit > bestCrit){
            bestCrit = tempCrit;
            //map_t = temp;
            std::cout << "t=" << t << std::endl;
            std::cout << "bestCrit=" << bestCrit << std::endl;
            for (int i = 0; i < ny; i++){
                for (int j = 0; j < nx; j++){
                    if (temp[i][j] > 0){
                        std::cout << temp[i][j];
                    }
                    else {
                        std::cout << ".";
                    }
                }
                std::cout << std::endl;
            }
        }

    }
    std::cout << "t=" << t << std::endl;
    for (int i = 0; i < ny; i++){
        for (int j = 0; j < nx; j++){
            if (map_t[i][j] > 0){
                std::cout << map_t[i][j];
            }
            else{
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }

    long total2 = 0;

    std::cout << "total=" << total << std::endl;
    std::cout << "total2=" << t << std::endl;
    return 0;
}

// total=221371920 too low
// total=191896320 
