#pragma once
#include <string>
#include <vector>

class Game{
    size_t length = 5;
    int maxAttempts = 6;
    std::string targetWord = "";
    std::vector<std::string> guesses = {};
    bool isWon = false;
    public:
        Game(int length, int maxAttempts);
        void play();
};