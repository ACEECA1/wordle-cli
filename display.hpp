#pragma once
#include "evaluator.hpp"
#include <string>
#include <vector>
#include <unordered_map>

void initTerminal();

void printGuess(const std::string& guess, const std::vector<LetterStatus>& feedback);

void printKeyboard(const std::unordered_map<char, LetterStatus>& keyboardStatus);

void clearScreen();

void printBanner();
