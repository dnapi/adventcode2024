#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// Function to clear the screen for animation
void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

// Function to print the animated Christmas tree
void printTree(const vector<string>& tree) {
    for (const string& line : tree) {
        cout << line << endl;
    }
}

// Function to randomize ornaments and lights on the tree
void randomizeTree(vector<string>& tree) {
    for (size_t i = 1; i < tree.size() - 2; ++i) { // Skip the top and base
        for (char& c : tree[i]) {
            if (c == 'o' || c == '.') {
                c = (rand() % 2 == 0) ? 'o' : '.'; // Randomly toggle between 'o' and '.'
            }
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(0))); // Seed random number generator

    // Initial tree design with larger size
    vector<string> tree = {
        "        *        ",
        "       /_\\       ",
        "      /o..\\      ",
        "     /..o.o\\     ",
        "    /o....o.\\    ",
        "   /..o.o...o\\   ",
        "  /o....o...o.\\  ",
        " /..o...o.o...o\\ ",
        "/o...o....o...o.\\",
        "       |||       ",
        "       |||       ",
        "    ^^[_]^^      "
    };

    while (true) {
        clearScreen();
        printTree(tree);     // Print the current state of the tree
        randomizeTree(tree); // Randomize ornaments for the next frame
        this_thread::sleep_for(chrono::milliseconds(500)); // Pause for animation
    }

    return 0;
}

