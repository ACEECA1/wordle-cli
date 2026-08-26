#include <iostream>
#include "evaluator.hpp"
#include "display.hpp"
void printResult(const std::string& guess, const std::vector<LetterStatus>& res) {
    std::cout << "Guess: " << guess << " -> ";
    for (auto status : res) {
        if (status == LetterStatus::Green) std::cout << "[G]";
        else if (status == LetterStatus::Yellow) std::cout << "[Y]";
        else std::cout << "[_]";
    }
    std::cout << "\n";
}

int main() {
    clearScreen();
    printBanner();
    printGuess("BOBBY", evaluate("ROBOT", "BOBBY"));
    return 0;
}
