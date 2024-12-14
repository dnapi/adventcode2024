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

struct region{
    char plant = ' ';
    int perimeter = 0;
    int area = 0;
    int price = 0;
    int number = -1;
    int corner = 0;
};

char save_data(const std::vector<std::string>& data, int i, int j){
    if (i < 0 || i >= data.size() || j < 0 || j >= data[i].size()){
        return '.';
    }
    return data[i][j];
}

char left_type(const std::vector<std::string>& data, int i, int j){
    if (j == 0){
        return '.';
    }
    return data[i][j - 1];
}

char right_type(const std::vector<std::string>& data, int i, int j){
    if (j == data[i].size() - 1){
        return '.';
    }
    return data[i][j + 1];
}

char up_type(const std::vector<std::string>& data, int i, int j){
    if (i == 0){
        return '.';
    }
    return data[i - 1][j];
}

char down_type(const std::vector<std::string>& data, int i, int j){
    if (i == data.size() - 1){
        return '.';
    }
    return data[i + 1][j];
}

void count_corners(std::vector<std::string>& data, int i, int j, region& r){
    if (left_type(data, i, j) != r.plant){
        if (up_type(data, i, j) != r.plant)
            r.corner++;
        if (down_type(data, i, j) != r.plant)
            r.corner++;
    }
    if (right_type(data, i, j) != r.plant){
        if (up_type(data, i, j) != r.plant)
            r.corner++;
        if (down_type(data, i, j) != r.plant)
            r.corner++;
    }
    // nord west
    if (save_data(data, i - 1, j - 1) != r.plant && 
        save_data(data, i - 1, j) == r.plant && 
        save_data(data, i, j - 1) == r.plant
    ){
            r.corner++;
    }
    // nord east
    if (save_data(data, i - 1, j + 1) != r.plant && 
        save_data(data, i - 1, j) == r.plant && 
        save_data(data, i, j + 1) == r.plant
    ){
            r.corner++;
    }
    // south west
    if (save_data(data, i + 1, j - 1) != r.plant && 
        save_data(data, i + 1, j) == r.plant && 
        save_data(data, i, j - 1) == r.plant
    ){
            r.corner++;
    }
    // south east
    if (save_data(data, i + 1, j + 1) != r.plant && 
        save_data(data, i + 1, j) == r.plant && 
        save_data(data, i, j + 1) == r.plant
    ){
            r.corner++;
    }
}

void fill_region(std::vector<std::string>& data, std::vector<std::vector<int>>& grid, int i, int j, region& r){
//perimeter
    std::cout << "perimeter for i=" << i << " j=" << j << std::endl;
    if (i < 0 || i >= data.size() || j < 0 || j >= data[i].size()){
        r.perimeter++;
        return;
    }
    if (data[i][j] != r.plant){
        r.perimeter++;
        return;
    }
    if (i < 0 || i >= data.size() || j < 0 || j >= data[i].size()){
        r.perimeter++;
        return;
    }
    if (data[i][j] != r.plant){
        r.perimeter++;
        return;
    }
    if (grid[i][j] == r.number){
        return;
    }
    r.area++;
    grid[i][j] = r.number;
    std::cout << "next step for i=" << i << " j=" << j << std::endl;
    fill_region(data, grid, i + 1, j, r);
    fill_region(data, grid, i - 1, j, r);
    fill_region(data, grid, i, j + 1, r);
    fill_region(data, grid, i, j - 1, r);
    std::cout << "end of fill_region" << std::endl;
}

int main() {
    std::ifstream file("input.txt");
    //std::ifstream file("input-test3.txt");
    //std::ifstream file("input-test.txt");
    //std::ifstream file("input-part2-test1.txt");

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
    std::vector <char> plants;
    for (auto& line : data){
        std::cout << line << std::endl;
        for (auto& c : line){
            if (std::find(plants.begin(),plants.end(), c) == plants.end()){
                plants.push_back(c);
            }
        }
    }   
    std::cout << plants.size() << " plants found" << std::endl;
    for (auto& c : plants){
        std::cout << c << " ";
    }
    int region_count = 1;
    std::vector<std::vector<int>> grid(data.size(), std::vector<int>(data[0].size(), 0));
    std::map<int, region> info = {};
    for (int i = 0; i < data.size(); ++i){
        for (int j = 0; j < data[i].size(); ++j){
            if (grid[i][j] != 0){
                continue;
            }
            std::cout << "i=" << i << " j=" << j << std::endl;
            region r;
            r.plant = data[i][j];
            std::cout << "Plant=" << r.plant << std::endl;
            r.number = region_count;
            fill_region(data, grid, i, j, r);
            info[r.number] = r;
            region_count++;
            
        }
    }
    std::cout << "Regions=" << info.size() << std::endl;
    for (int i = 0; i < data.size(); ++i){
        for (int j = 0; j < data[i].size(); ++j){
            count_corners(data, i, j, info[grid[i][j]]);
        }
    }
    int total = 0;
    int total2 = 0;
    for (auto& [key, value] : info){
        std::cout << "Region " << key 
            << "plant=" << value.plant << " has " 
            << value.area << " area and " 
            << value.perimeter << " perimeter " 
            << value.corner << "corners" <<std::endl;
        total += value.area * value.perimeter;
        total2 += value.area * value.corner;
    }
    std::cout << "total=" << total << std::endl;
    std::cout << "total2=" << total2 << std::endl;
    return 0;
}

//1375574