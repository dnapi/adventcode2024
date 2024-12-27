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

int main() {
    //reg r = {60589763, 0, 0, 0};
    std::vector<long> prog = {2,4,1,5,7,5,1,6,4,1,5,5,0,3,3,0};
                            //2,4,1,5,7,5,1,6,4,1,5,5,0,3,3,0
    reg r = {1, 0, 0, 0, {},prog.size()};

    // reg r = {729, 0, 0, 0};
    // std::vector<unsigned char> prog = {0,1,5,4,3,0};

    // std::vector<long> prog = {0,3,5,4,3,0};
    // //reg r = {117440, 0, 0, 0, {}};
    // reg r = {1, 0, 0, 0, {}, prog.size()};

    size_t num_cmd = 0;
    size_t count = 0;
    std::vector <long> reg_a_list(prog.size(), 1);
    std::vector <std::vector<long>> solutions(prog.size(), std::vector<long>()); 
    long try_value = 0;
    //while (num_cmd < prog.size()){
    while (num_cmd < prog.size()){
        if (count > 8){
            //break;
            count = 0;
            try_value = 0;
            num_cmd++;
            std::cout << " End of num_cmd: " << num_cmd << std::endl << std::endl;
            continue;
        }
        std::cout << "Trying: " << try_value << " num_cmd=" << num_cmd;
        std::vector<long> regA(reg_a_list);
        regA[num_cmd] = try_value;
        try_value = (try_value + 1) % 8;
        count++;
        r.a = reg_list_to_long(regA);
        //std::cout << "r.a: " << r.a << std::endl;
        reg r_temp = r;
        run(r_temp, prog);
        if (r_temp.prog.size() != prog.size())
            continue;
        if (r_temp.prog[prog.size() - num_cmd - 1] == prog[prog.size() - num_cmd - 1]){
            std::cout << "Success" << std::endl;
            for (auto i : r_temp.prog){
                std::cout << i << ",";
            }
            std::cout << "= r_temp.prog" << std::endl;
            for (auto i : prog){
                std::cout << i << ",";
            }
            std::cout << "= prog" << std::endl;
            reg_a_list[num_cmd] = regA[num_cmd];
            solutions[num_cmd].push_back(regA[num_cmd]);
            std::cout << "num_cmd: " << num_cmd << " reg_a_list[n]=" << reg_a_list[num_cmd] << std::endl;
            //num_cmd++;
            //count = 0;
            continue;
        }
        else {
            std::cout << "Failed" << r_temp.prog[prog.size() - num_cmd -1]<< "<>" << prog[prog.size() - num_cmd -1] << std::endl;
            // for (auto i : r_temp.prog){
            //     std::cout << i << ","; 
            // }
            // std::cout << "= r_temp.prog" << std::endl;
        }
    }
    for (int i = 0; i < solutions.size(); i++){
        std::cout << "Solution for " << i << ": ";
        for (auto j : solutions[i]){
            std::cout << j << ",";
        }
        std::cout << std::endl;
    }
    //std::cout << "Found: " << r.a << std::endl;
    //std::cout << std::endl;

    return 0;

}
