#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> transposeMatrix(const std::vector<std::string>& xmas) {
    if (xmas.empty()) return {};
    
    size_t numRows = xmas.size();
    size_t numCols = xmas[0].size();
    std::vector<std::string> result(numCols, std::string(numRows, ' '));
    
    for (size_t i = 0; i < numRows; ++i) {
        for (size_t j = 0; j < numCols; ++j) {
            result[j][i] = xmas[i][j];
        }
    }
    
    return result;
}

std::vector<std::string> rotateMatrix(const std::vector<std::string>& xmas) {
    if (xmas.empty()) return {};
    
    size_t numRows = xmas.size();
    size_t numCols = xmas[0].size();
    std::vector<std::string> result(numCols, std::string(numRows, ' '));
    
    for (size_t i = 0; i < numRows; ++i) {
        for (size_t j = 0; j < numCols; ++j) {
            result[i][j] = xmas[j][numCols - i - 1];
        }
    }
    
    return result;
}

int is_xmas(const std::vector<std::string>& xmas) {
    if (xmas[1][1] != 'A')
        return 0;
    if (xmas[0][0] != 'M')
        return 0;
    if (xmas[2][0] != 'M')
        return 0;
    if (xmas[0][2] != 'S')
        return 0;
    if (xmas[2][2] != 'S')
        return 0;
    return 1;
}


int main() {
    std::ifstream file("input04.txt");
    //std::ifstream file("input04test.txt");
    //std::ifstream file("input04test2.txt");
    if (!file.is_open()){
        std::cerr << "Failed to  open file" << std::endl;
        return 1;
    }
    std::string line;
    std::vector<std::string> data;
    while (std::getline(file, line)){
        data.push_back(line);
    }
    file.close();
    size_t size_x = data[0].size();
    size_t size_y = data.size();

    std::cout << "size_x=" << size_x << " size_y=" << size_y << std::endl;
    size_t size = size_x;
    size_t total = 0;
    size_t total_h = 0;
    size_t total_v = 0;
    size_t total_dr = 0;
    size_t total_dl = 0;
    size_t total_xmas = 0;
    int delt[4] = {0, 0, 0, 0};

    // for (size_t i = 0; i < size_y; i++){
    //     for (size_t j = 0; j < size_x; j++){
    //         //horizontal
    //         if (data[i].substr(j, 4) == "XMAS" || data[i].substr(j, 4) == "SAMX")
    //             total_h++;
    //         //vertical down and up
    //         std::string str = "";
    //         if (i <= size_y - 4){
    //             str += data[i][j];
    //             str += data[i + 1][j];
    //             str += data[i + 2][j];
    //             str += data[i + 3][j];
    //             //std::cout << "str=" << str << std::endl;
    //             if (str == "XMAS" || str == "SAMX")
    //                 total_v++;
    //             str = "";
    //         }
    //         // diagonal down right
    //         if (i <= size_y - 4 && j <= size_x - 4){
    //             str += data[i][j];
    //             str += data[i + 1][j + 1];
    //             str += data[i + 2][j + 2];
    //             str += data[i + 3][j + 3];
    //             if (str == "XMAS" || str == "SAMX")
    //                 total_dr++;
    //             str = "";
    //         }
    //         //diagonal down left
    //         if (i <= size_y - 4 && j >= 3){
    //             str += data[i][j];
    //             str += data[i + 1][j - 1];
    //             str += data[i + 2][j - 2];
    //             str += data[i + 3][j - 3];
    //             if (str == "XMAS" || str == "SAMX")
    //                 total_dl++;
    //             str = "";
    //         }
    //     }
    // }
    // std::cout << "day 04 resutls" << std::endl;
    // std::cout << "total_h=" << total_h << std::endl;
    // std::cout << "total_v=" << total_v << std::endl;
    // std::cout << "total_dr=" << total_dr << std::endl;
    // std::cout << "total_dl=" << total_dl << std::endl;
    // total = total_h + total_v + total_dr + total_dl;
    // std::cout << "total=" << total << std::endl;

    for (size_t i = 0; i < size_y; i++){
        for (size_t j = 0; j < size_x; j++){
            std::vector<std::string> xmas;
            if (i <= size_y - 3 && j <= size_x - 3){
                xmas.push_back(data[i].substr(j, 3));
                xmas.push_back(data[i + 1].substr(j, 3));
                xmas.push_back(data[i + 2].substr(j, 3));
                int delta1 = is_xmas(xmas);
                xmas = rotateMatrix(xmas);
                int delta2 = is_xmas(xmas);
                xmas = rotateMatrix(xmas);
                int delta3 = is_xmas(xmas);
                xmas = rotateMatrix(xmas);
                int delta4 = is_xmas(xmas);
                delt[0] += delta1;
                delt[1] += delta2;
                delt[2] += delta3;
                delt[3] += delta4;
              //  std::cout << "delta1=" << delta1 << " delta2=" << delta2 << " delta3=" << delta3 << " delta4=" << delta4 << std::endl;
              //  std::cout << "i=" << i << " j=" << j << std::endl;
                if (delta1 || delta2 || delta3 || delta4)
                    total_xmas++;
            }

            //std::cout << data[i][j];
                
        }
    }
    std::cout << "day 04 part 2 resutls" << std::endl;
    std::cout << "total_xmas=" << total_xmas << std::endl;
    std::cout << "delt[0]=" << delt[0] << " delt[1]=" << delt[1] << " delt[2]=" << delt[2] << " delt[3]=" << delt[3] << std::endl;
    return 0;
}

//1841 too low