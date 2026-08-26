#pragma once
#include "evaluator.hpp"
#include <string>
#include <vector>
#include <unordered_map>

class Game {
private:
    int length;
    int maxAttempts;
    std::string targetWord;
    std::vector<std::string> guesses;
    std::unordered_map<char, LetterStatus> keyboardStatus;
    bool isWon;

    void renderBoard() const;
    std::string promptGuess(int attemptNumber);
    void printSummary() const;
    void updateKeyboard(const std::string& guess, const std::vector<LetterStatus>& feedback);

public:
    Game(int length = 5, int maxAttempts = 6);
    void play();
};
