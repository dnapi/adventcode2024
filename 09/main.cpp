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
    std::ifstream file("input09test.txt");
    //std::ifstream file("input09.txt");
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
    int total = 0;
    std::vector<int> input;
    std::deque<int> files;
    std::deque<int> indexes;
    std::deque<int> frees;
    for (int i = 0; i < line.size(); i++){
        //std::cout << line[i] << std::endl;
        input.push_back(line[i] - '0');
        if (i % 2 == 0){
            files.push_back(input[i]);
            indexes.push_back(i / 2);
        } else {
            frees.push_back(input[i]);
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
    for (int i = 0; i < frees.size(); i++){
        std::cout << frees[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Files and Frees ready " << files.size() << " " << frees.size() << std::endl;
    std::vector<int> data;
    for (int i = 0; files.size() > 0; i++){
        while (files[0] > 0){
            std::cout << "i=" << i << "File left=" << files[i] << std::endl;
            data.push_back(i);
            files[0]--;
        }
        files.pop_front();
        indexes.pop_front();
        for (int j = 0; j < frees[i]; j++){
            int last_file_size = files.back();
            int last_file_id = indexes.back();
            std::cout << "i=" << i << "Last file size=" << last_file_size << " id=" << last_file_id << std::endl;
            data.push_back(last_file_id);
            files.back()--;
            if (files.back() == 0){
                files.pop_back();
                indexes.pop_back();
            }
        }
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
    for (int i = 0; i < frees.size(); i++){
        std::cout << frees[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Answer=" << total << std::endl;
    return 0;
}

//1157
