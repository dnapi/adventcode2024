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
#include <cmath>

#include <limits>

struct reg {
    long a;
    long b;
    long c;
    size_t ip;
    std::vector<long> prog;
    size_t ip_max;
};

long combo(long i, reg r){
    if (i < 0){
        r.ip += r.ip_max;
        return -1;
    }
    if (i < 4)
        return i;
    if (i == 4)
        return r.a;
    if (i == 5)
        return r.b;
    if (i == 6)
        return r.c;
    r.ip += r.ip_max;
    return -1;
}

void adv(long f, long x, reg& r){
    r.ip += 2;
    long result = r.a >> combo(x, r);
    r.a = result;
}

void bxl(long f, long x, reg& r){
    long result = r.b ^ x;
    r.b = result;
    r.ip += 2;
}

void bst(long f, long x, reg& r){
    r.ip += 2;
    r.b = combo(x, r) & 7;
}

void jnz(long f, long x, reg& r){
    if (r.a == 0){
        r.ip += 2;
        return;
    }
    r.ip = x;
}

void bxc(long f, long x, reg& r){
    r.b = r.b ^ r.c;
    r.ip += 2;
}

void out(long f, long x, reg& r){
    r.ip += 2;
    r.prog.push_back(combo(x, r) & 7);
}

void bdv(long f, long x, reg& r){
    r.ip += 2;
    r.b = r.a >> combo(x, r);
}

void cdv(long f, long x, reg& r){
    r.ip += 2;
    r.c = r.a >> combo(x, r);
}

void run(reg& r, std::vector<long>& prog){
    while (r.ip < prog.size()){
        switch (prog[r.ip]){
            case 0:
                adv(prog[r.ip], prog[r.ip+1], r);
                break;
            case 1:
                bxl(prog[r.ip], prog[r.ip+1], r);
                break;
            case 2:
                bst(prog[r.ip], prog[r.ip+1], r);
                break;
            case 3:
                jnz(prog[r.ip], prog[r.ip+1], r);
                break;
            case 4:
                bxc(prog[r.ip], prog[r.ip+1], r);
                break;
            case 5:
                out(prog[r.ip], prog[r.ip+1], r);
                break;
            case 6:
                bdv(prog[r.ip], prog[r.ip+1], r);
                break;
            case 7:
                cdv(prog[r.ip], prog[r.ip+1], r);
                break;
            default:
                std::cout << "Unknown instruction: " << prog[r.ip] << std::endl;
                return;
        }
    }
}

long reg_list_to_long(std::vector<long> reg_list){
    long result = 0;
    for (auto i : reg_list){
        result = (result << 3) + i;
    }
    return result;
}

std::vector<long> long_to_reg_list(long l, size_t size){
    std::vector<long> result;
    for (size_t i = 0; i < size; i++){
        result.push_back(l & 7);
        l = l >> 3;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

std::vector<long> try_cmd(long num_reg_a, std::vector<long> reg_a_list, reg r, std::vector<long> prog){
    std::cout << "Trying num_reg_a: " << num_reg_a << std::endl;
    // for (auto i : reg_a_list){
    //     std::cout << i << ",";
    // }
    //std::cout << "reg A state" << std::endl;
    if (num_reg_a == prog.size()){
        return reg_a_list;
    }
    size_t num_prog = prog.size() - num_reg_a - 1;
    std::cout << "    num_prog: " << num_prog << std::endl;
    std::vector<long> result;
    for (int try_value = 0; try_value < 8; try_value++){
        //std::cout << "    Test: " << try_value << std::endl;
        reg_a_list[num_reg_a] = try_value;
        reg r_temp  = r;
        r_temp.a = reg_list_to_long(reg_a_list);
        run(r_temp, prog);
        if (r_temp.prog.size() == prog.size() 
            && r_temp.prog[num_prog] == prog[num_prog]
        ){
            std::cout << "Success" << num_reg_a << "-> " << try_value <<  std::endl;
            std::vector<long> result = try_cmd(num_reg_a + 1, reg_a_list, r, prog);
            if (result.size() > 0){
                return result;
            }
        }
    }
    std::cout << "Failed to find solution" << std::endl;
    return {};
}

int main() {
    //reg r = {60589763, 0, 0, 0};
    std::vector<long> prog = {2,4,1,5,7,5,1,6,4,1,5,5,0,3,3,0};
    reg r = {1, 0, 0, 0, {}, prog.size()};
    
    // reg r = {729, 0, 0, 0};
    // std::vector<unsigned char> prog = {0,1,5,4,3,0};

    // std::vector<long> prog = {0,3,5,4,3,0};
    // // reg r = {117440, 0, 0, 0, {}, prog.size()};
    // reg r = {1, 0, 0, 0, {}, prog.size()};

    for (auto i : long_to_reg_list(117440, 6)){
        std::cout << i << ",";
    }
    std::cout << " answer" << std::endl;
    // run(r, prog);
    // for (auto i : r.prog){
    //     std::cout << i << ",";
    // }
    // std::cout << std::endl;
    // for (auto i : prog){
    //     std::cout << i << ",";
    // }
    // return 0;
    std::vector <long> reg_a_list(prog.size(), 0);
    std::vector <long> solution = try_cmd(0, reg_a_list, r, prog);
    for (auto i : solution){
        std::cout << i << " ";
    }
    std::cout << "Found: " << reg_list_to_long(solution) << std::endl;
    std::cout << std::endl;

    return 0;

}
