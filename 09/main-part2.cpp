#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <deque>

int main() {
    // std::ifstream file("input09test.txt");
    std::ifstream file("input09.txt");
    if (!file.is_open()){
        std::cerr << "Failed to  open file" << std::endl;
        return 1;
    }
    std::string line;
    std::getline(file, line);
    // while (std::getline(file, line)){
    //     data.push_back(line);
    // }
    file.close();
    long total = 0;
    std::vector<int> input;
    std::vector<int> files;
    std::vector<int> indexes;
    std::vector<int> free_sizes;
    std::vector<int> free_indexes;
    
    for (int i = 0; i < line.size(); i++){
        //std::cout << line[i] << std::endl;
        input.push_back(line[i] - '0');
        if (i % 2 == 0){
            files.push_back(input[i]);
            indexes.push_back(i / 2);
        } else {
            free_sizes.push_back(input[i]);
            free_indexes.push_back(0);
        }
    }
    for (int i = 0; i < files.size(); i++){
        std::cout << i << " ";
    }   
    std::cout << std::endl;
    for (int i = 0; i < files.size(); i++){
        std::cout << files[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < free_sizes.size(); i++){
        std::cout << free_sizes[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Files and Frees ready " << files.size() << " " << free_sizes.size() << std::endl;
    
    // feeling free spaces
    std::vector<std::vector<int>> free_data(free_sizes.size(), std::vector<int>());
    std::vector<int> freed_files(files.size(), 0);
    for (int i = files.size() - 1; i > 0; --i){  // i = index of file
        //std::cout << "File to be moved " << i << " " << files[i] << std::endl;
        for (int j = 0; j < i; j++){
            //std::cout << "\tChecking free space " << j << " " << free_sizes[j] << std::endl;
            if (free_sizes[j] >= files[i] && files[i] > 0){
                for (int k = 0; k < files[i]; k++)
                    free_data[j].push_back(i);
                free_sizes[j] -= files[i];
                freed_files[i] = files[i];
                files[i] = 0;
            }
        }
    }
    std::cout << "Free spaces filled" << std::endl;
    std::vector<int> data;
    for (int i = 0; i < files.size() - 1; i++){
        for (int j = 0; j < files[i]; j++){
            data.push_back(i);
        }
        if (freed_files[i] > 0){
            for (int j = 0; j < freed_files[i]; j++){
                data.push_back(0);
            }
        }
        for (int j = 0; j < free_data[i].size(); j++){
            data.push_back(free_data[i][j]);
        }
        for (int j = 0; j < free_sizes[i]; j++){
            data.push_back(0);
        }
    }
    for (int j = 0; j < files.back(); j++){
            data.push_back(files.size() - 1);
        }
    std::cout << "Data size=" << data.size() << std::endl;
    for (int i = 0; i < data.size(); i++){
        std::cout << data[i];
    }
    std::cout << std::endl;
    for (int i = 0; i < files.size(); i++){
        std::cout << files[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < free_sizes.size(); i++){
        std::cout << free_sizes[i] << " ";
    }
    std::cout << std::endl;
    total = 0;
    for (int i = 0; i < data.size(); i++){
        total += data[i] * i;
    }
    std::cout << "Answer=" << total << std::endl;
    return 0;
}

//Answer=6421724645083