#include "display.hpp"
#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

void initTerminal() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }
#endif
}

void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void printBanner() {
    std::cout << "\033[1;36m=======================\033[0m\n";
    std::cout << "\033[1;32m       WORDLE CLI      \033[0m\n";
    std::cout << "\033[1;36m=======================\033[0m\n\n";
}

void printGuess(const std::string& guess, const std::vector<LetterStatus>& feedback) {
    std::cout << "  ";
    for (size_t i = 0; i < guess.length(); i++) {
        if (feedback[i] == LetterStatus::Green) {
            std::cout << "\033[1;37;42m " << guess[i] << " \033[0m ";
        } else if (feedback[i] == LetterStatus::Yellow) {
            std::cout << "\033[1;37;43m " << guess[i] << " \033[0m ";
        } else {
            std::cout << "\033[1;37;100m " << guess[i] << " \033[0m ";
        }
    }
    std::cout << "\n\n";
}

void printKeyboard(const std::unordered_map<char, LetterStatus>& keyboardStatus) {
    const std::vector<std::string> rows = {
        "QWERTYUIOP",
        "ASDFGHJKL",
        "ZXCVBNM"
    };

    std::cout << "\033[1;33mKeyboard Tracker:\033[0m\n";
    for (size_t r = 0; r < rows.size(); ++r) {
        if (r == 1) std::cout << " ";
        else if (r == 2) std::cout << "   ";

        for (char c : rows[r]) {
            auto it = keyboardStatus.find(c);
            if (it != keyboardStatus.end()) {
                if (it->second == LetterStatus::Green) {
                    std::cout << "\033[1;37;42m " << c << " \033[0m ";
                } else if (it->second == LetterStatus::Yellow) {
                    std::cout << "\033[1;37;43m " << c << " \033[0m ";
                } else {
                    std::cout << "\033[2;37;100m " << c << " \033[0m ";
                }
            } else {
                std::cout << "\033[1;37;48;5;238m " << c << " \033[0m ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
