#pragma once
#include <string>
#include <vector>

class Game {
private:
    int length;
    int maxAttempts;
    std::string targetWord;
    std::vector<std::string> guesses;
    bool isWon;

    void renderBoard() const;
    std::string promptGuess(int attemptNumber);
    void printSummary() const;

public:
    Game(int length = 5, int maxAttempts = 6);
    void play();
};
