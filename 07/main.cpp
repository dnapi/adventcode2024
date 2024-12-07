#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// #include <iostream>

// int main() {
//     int value = 0x12345678;  // Example 4-byte integer
//     int byte_position = 2;  // 0 for least significant byte, 3 for most significant byte

//     unsigned char extracted_byte = (value >> (byte_position * 8)) & 0xFF;

//     std::cout << "Extracted byte: 0x" << std::hex << static_cast<int>(extracted_byte) << std::endl;
//     return 0;
// }

// #include <iostream>

// int main() {
//     int value = 0x12345678;  // Example 4-byte integer
//     int byte_position = 2;  // 0 for LSB, 3 for MSB

//     // Access the byte array representation of the integer
//     unsigned char* bytes = reinterpret_cast<unsigned char*>(&value);

//     unsigned char extracted_byte = bytes[byte_position];

//     std::cout << "Extracted byte: 0x" << std::hex << static_cast<int>(extracted_byte) << std::endl;
//     return 0;
// }


#include <iostream>

//union IntBytes {
//     int value;
//     unsigned char bytes[sizeof(int)];
// };

// int main() {
//     IntBytes data;
//     data.value = 0x12345678;

//     int byte_position = 2;  // 0 for LSB, 3 for MSB

//     unsigned char extracted_byte = data.bytes[byte_position];

//     std::cout << "Extracted byte: 0x" << std::hex << static_cast<int>(extracted_byte) << std::endl;
//     return 0;
// }


int main() {
    std::ifstream file("input07.txt");
    if (!file.is_open()){
        std::cerr << "Failed to  open file" << std::endl;
        return 1;
    }
    std::string line;
    int part = 0;
    std::vector<std::vector<int>> data;
    std::vector<long> results;
    while (std::getline(file, line)){
        size_t pos_end = line.find(":");
        long result = std::stol(line.substr(0, pos_end));
        std::cout << "Result: " << result << std::endl;
        results.push_back(result);
        std::string left_str = line.substr(pos_end + 1, line.size() - pos_end);
        std::istringstream ss(left_str);
        std::vector<int> values;
        //std::string token;
        // while (std::getline(ss, token, ' ')){
        //     int value = std::stoi(token);
        //     values.push_back(value);
        // }
        int value = 0;
        while (ss >> value){
            //std::cout << "value=" << value << std::endl;
            values.push_back(value);
        }
        data.push_back(values);
    }
    file.close();
    int max_size = 0;
    for (size_t i = 0; i < data.size(); i++){
        auto& values = data[i];
        int result = results[i];
        int flag = 0;
        if (values.size() > max_size){
            max_size = values.size();
        }
        // for (size_t j = 0; j < values.size(); j++){
        // }
        // if (!flag){
        //     std::cout << "Result: " << result << std::endl;
        //     break;
        // }
    }
    std::cout << "Max size: " << max_size << std::endl;
    return 0;
}