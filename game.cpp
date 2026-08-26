#include "game.hpp"
#include "dictionary.hpp"
#include "evaluator.hpp"
#include "display.hpp"
#include <iostream>
#include <algorithm>
#include <cctype>

Game::Game(int length, int maxAttempts)
    : length(length), maxAttempts(maxAttempts), 
      targetWord(getRandomWord(length)), isWon(false) {}

void Game::updateKeyboard(const std::string& guess, const std::vector<LetterStatus>& feedback) {
    for (size_t i = 0; i < guess.length(); ++i) {
        char c = guess[i];
        LetterStatus status = feedback[i];

        auto it = keyboardStatus.find(c);
        if (it == keyboardStatus.end()) {
            keyboardStatus[c] = status;
        } else {
            if (status == LetterStatus::Green) {
                keyboardStatus[c] = LetterStatus::Green;
            } else if (status == LetterStatus::Yellow && it->second != LetterStatus::Green) {
                keyboardStatus[c] = LetterStatus::Yellow;
            }
        }
    }
}

void Game::renderBoard() const {
    clearScreen();
    printBanner();

    for (const auto& guess : guesses) {
        auto feedback = evaluate(targetWord, guess);
        printGuess(guess, feedback);
    }

    for (size_t i = guesses.size(); i < static_cast<size_t>(maxAttempts); ++i) {
        std::cout << "  ";
        for (int j = 0; j < length; ++j) {
            std::cout << "\033[1;30;100m _ \033[0m ";
        }
        std::cout << "\n\n";
    }

    printKeyboard(keyboardStatus);
}

std::string Game::promptGuess(int attemptNumber) {
    std::string guess;

    while (true) {
        std::cout << "Attempt " << attemptNumber << "/" << maxAttempts << ". Enter your guess: ";
        if (!(std::cin >> guess)) {
            std::cout << "\nExiting game.\n";
            exit(0);
        }

        if (guess.length() != static_cast<size_t>(length)) {
            std::cout << "Please enter a " << length << "-letter word.\n";
            continue;
        }

        bool allAlpha = std::all_of(guess.begin(), guess.end(), [](unsigned char c) {
            return std::isalpha(c);
        });
        if (!allAlpha) {
            std::cout << "Please enter alphabetic characters only.\n";
            continue;
        }

        if (!isValidWord(guess)) {
            std::cout << "Invalid word. Please try again.\n";
            continue;
        }

        for (char& c : guess) {
            c = std::toupper(static_cast<unsigned char>(c));
        }
        return guess;
    }
}

void Game::printSummary() const {
    if (isWon) {
        std::cout << "\033[1;32m🎉 Congratulations! You guessed the word: " << targetWord << "\033[0m\n\n";
    } else {
        std::cout << "\n\033[1;31mGame Over! The secret word was: " << targetWord << "\033[0m\n\n";
    }

    std::cout << "\033[1;36m📖 Definition:\033[0m " << getDefinition(targetWord) << "\n\n";
}

void Game::play() {
    renderBoard();

    while (guesses.size() < static_cast<size_t>(maxAttempts) && !isWon) {
        std::string guess = promptGuess(guesses.size() + 1);
        guesses.push_back(guess);

        auto feedback = evaluate(targetWord, guess);
        updateKeyboard(guess, feedback);

        renderBoard();

        if (guess == targetWord) {
            isWon = true;
        }
    }

    printSummary();
}
