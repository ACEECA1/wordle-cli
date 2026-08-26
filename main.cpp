#include <iostream>
#include "evaluator.hpp"

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
    std::string secret = "ROBOT";
    std::string guess = "BOBBY";

    auto result = evaluate(secret, guess);
    printResult(guess, result);
    // Expected: [Y] [G] [G] [_] [_]

    return 0;
}
