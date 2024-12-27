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
#include <unordered_set>


#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }
        current->isEndOfWord = true;
    }
 
    bool search(const string& word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children[c];
        }
        return current->isEndOfWord;
    }

    std::vector<size_t> find_next_positions(const std::string &design, size_t pos){
        std::vector<size_t> result;
        TrieNode* current = root;
        for (size_t i = pos; i < design.size(); i++) {
            char c = design[i];
            if (current->children.find(c) == current->children.end())
                break;
            if (current->children.find(c) != current->children.end() && current->children[c]->isEndOfWord)
                result.push_back(i + 1);
            current = current->children[c];
        }
        return result;
    }

    bool compose2(const std::string &design, size_t pos) {
        std::vector<size_t> next_pos = find_next_positions(design, pos);
        if (next_pos.size() == 0)
            return false;
        for (auto p : next_pos) {
            if (p == design.size())
                return true;
            if (compose2(design, p))
                return true;
        }
        return false;
    }

    bool compose(const std::string &design, size_t pos) {
        TrieNode* current = root;
        for (size_t i = pos; i < design.size(); i++) {
            char c = design[i];
            // std::cout << "c=" << c << i << std::endl;
            // std::cout << design.substr(i) << std::endl;
            if (current->children.find(c) == current->children.end())
                return false;
            if (current->children.find(c) != current->children.end() && current->children[c]->isEndOfWord) {
                if (i == design.size() - 1)
                    return true;
                if (compose(design, i + 1))
                    return true;
            }
            current = current->children[c];
        }
        return false;
    }

};


std::vector<size_t> find_next_positions_slow(const std::string &design, const std::unordered_set<std::string> &towels, size_t pos, size_t max_len = 0) {
    std::vector<size_t> result;
    for (auto s : towels) {
        size_t len = s.size();
        if (s == design.substr(pos, len)) {
            result.push_back(pos + len);
            //std::cout << s << "-";
        }
    }
    //std::cout << std::endl;
    return result;
}

std::vector<size_t> find_next_positions(const std::string &design, const std::unordered_set<std::string> &towels, size_t pos, size_t max_len) {
    std::vector<size_t> result;
    for (int i = 1; i <= max_len; i++) {
        std::string s = design.substr(pos, i);
        //std::cout << "s=" << s << std::endl;
        if (towels.find(s) != towels.end())
            result.push_back(pos + i);
    }
    return result;
}

size_t number_of_ways(const std::string &design, const std::unordered_set<std::string> &towels, size_t pos, size_t max_len) {
    std::cout << "--"  << pos << "/" << design.size() <<  "  =" << design.substr(pos) << std::endl;
    if (pos >= design.size()) {
        return 1;
    }
    std::vector<size_t> next_pos = find_next_positions(design, towels, pos, max_len);
    if (next_pos.size() == 0) {
        std::cout << "    no next_pos" << std::endl;
        return 0;
    }
    for (auto p : next_pos) {
        std::cout << "    " << p;
    }
    std::cout << std::endl;
    size_t result = 0;
    for (auto p : next_pos) {
        if (p >= design.size())
            return 1;
    }
    for (auto p : next_pos) {
        result += number_of_ways(design, towels, p, max_len);
        if (result > 0) {
            return result;
        }
    }
    return result;   
}

bool is_design_possible(
        const std::string &design
        , const std::unordered_set<std::string> &towels
        , size_t pos
        , std::set<size_t> &memo
    ) {
    if (pos >= design.size()) {
        return true;
    }
    for (auto t : towels) {
        size_t len = t.size();
        if (t == design.substr(pos, len)) {
            if (memo.find(pos + len) != memo.end())
                continue;
            if (is_design_possible(design, towels, pos + len, memo))
                return true;
            else
                memo.insert(pos + len);
        }
    }
    return false;

}


long count_options(
        const std::string &design
        , const std::unordered_set<std::string> &towels
        , size_t pos
        , std::map<size_t, long> &memo
    ) {
    if (pos >= design.size()) {
        if (memo.find(pos) == memo.end())
            memo[pos] = 1;
        else
            memo[pos] = memo[pos] + 1;
        return memo[pos];
    }
    long result = 0;
    for (auto t : towels) {
        size_t len = t.size();
        if (t == design.substr(pos, len))
            if (memo.find(pos + len) != memo.end())
                result += memo[pos + len];
            else
                result += count_options(design, towels, pos + len, memo);
    }
    if (memo.find(pos) == memo.end())
        memo[pos] = result;
    else
        memo[pos] = memo[pos] + result;
    return result;
}


int main() {
    std::ifstream file("input.txt");
    // std::ifstream file("input-test.txt");

    if (!file.is_open()){
        std::cerr << "Failed to  open file" << std::endl;
        return 1;
    }
    std::unordered_set<std::string> towels;
    std::vector<std::string> towels_test;
    
    // std::string query = "banana";
    // if (stringSet.find(query) != stringSet.end()) {
    //     std::cout << query << " found!" << std::endl;
    // } else {
    //     std::cout << query << " not found!" << std::endl;
    // }
    std::string line;
    std::vector<std::string> designs;
    std::getline(file, line);
    size_t pos_start = 0;
    size_t pos_end = 0;
    while ((pos_end = line.find(", ", pos_start)) != std::string::npos) {
        towels.insert(line.substr(pos_start, pos_end - pos_start));
        towels_test.push_back(line.substr(pos_start, pos_end - pos_start));
        pos_start = pos_end + 2;
    }
    //std::cout << "pos_start=" << pos_start << std::endl;
    //std::cout << line.substr(pos_start) << std::endl;
    towels.insert(line.substr(pos_start));
    towels_test.push_back(line.substr(pos_start));
    std::getline(file, line);
    while (std::getline(file, line)){
        designs.push_back(line);
    }
    file.close();
    std::cout << "towels.size()=" << towels.size() << std::endl;
    std::cout << "designs.size()=" << designs.size() << std::endl;

    size_t total00 = 0;
    for (auto d: designs) {
        std::set<size_t> memo;
        size_t res = is_design_possible(d, towels, 0, memo) ? 1 : 0;
        total00 += res;
        std::cout << d << res << std::endl;
    }
    std::cout << "total00=" << total00 << std::endl;

    std::cout << "Part 2 " << std::endl;
    long total01 = 0;
    for (auto d: designs) {
        std::cout << d << std::flush;
        std::map<size_t,long> memo;
        long total_temp = count_options(d, towels, 0, memo);
        total01 += total_temp;
        std::cout <<  total_temp << std::endl;
    }
    std::cout << "total01=" << total01 << std::endl;

    Trie trie;
    for (auto t : towels) {
        trie.insert(t);
    }
    std::cout << "trie.search(banana)=" << trie.search("banana") << std::endl;
    std::cout << "trie.search(bgbggur)=" << trie.search("bgbggur") << std::endl;
    std::cout << "trie.search(bwe)=" << trie.search("bwu") << std::endl;
    std::vector<size_t> pos = trie.find_next_positions("bwu", 0);
    for (auto p : pos) {
        std::cout << p << std::endl;
    }
    size_t total0 = 0;
    for (auto d : designs) {
        std::cout << "trie.compose(" << d << ")=" << trie.compose(d, 0) << std::endl;
        total0 += trie.compose2(d, 0) ? 1 : 0;
    }
    std::cout << "total=" << total0 << std::endl;
    // size_t max_len = 0;
    // for (auto t : towels) {
    //     if (t.size() > max_len) {
    //         max_len = t.size();
    //     }
    // }
    // std::cout << "max_len=" << max_len << std::endl;
    // std::vector<size_t> positions = find_next_positions(designs[0], towels, 0, max_len);
    // for (auto p : positions) {
    //     std::cout << p << std::endl;
    // }
    // std::cout << "step 2" << std::endl; // 13:33
    // std::cout << "number_of_ways for " << designs[0] << "->"<< number_of_ways(designs[0], towels, 0, max_len) << std::endl;

    int total = 0;
    int total2 = 0;
    // size_t i = 0;
    // for (auto& d : designs) {
    //     std::cout << "design i=" << i << " " << d << std::endl;
    //     size_t num = number_of_ways(d, towels, 0, max_len);
    //     std::cout << "    ->"<< num << std::endl;
    //     total += num;
    //     total2 += num > 0 ? 1 : 0;
    //     i++;
    // }
    // std::cout << "total=" << total << std::endl;
    std::cout << "total2=" << total2 << std::endl;
    return 0;
}

//256 = too low 