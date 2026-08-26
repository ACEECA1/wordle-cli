#include "game.hpp"
#include "dictionary.hpp"
#include "evaluator.hpp"
#include "display.hpp"
#include <iostream>
#include <algorithm>

Game::Game(int length, int maxAttempts)
    : length(length), maxAttempts(maxAttempts), 
      targetWord(getRandomWord(length)), isWon(false) {}

void Game::renderBoard() const {
    clearScreen();
    printBanner();

    for (const auto& guess : guesses) {
        auto feedback = evaluate(targetWord, guess);
        printGuess(guess, feedback);
    }
    std::cout << "\n";
}

std::string Game::promptGuess(int attemptNumber) {
    std::string guess;

    while (true) {
        std::cout << "Attempt " << attemptNumber << "/" << maxAttempts << ". Enter your guess: ";
        std::cin >> guess;

        if (guess.length() != static_cast<size_t>(length)) {
            std::cout << "Please enter a " << length << "-letter word.\n";
            continue;
        }

        if (!isValidWord(guess)) {
            std::cout << "Invalid word. Please try again.\n";
            continue;
        }

        for (char& c : guess) {
            c = std::toupper(c);
        }
        return guess;
    }
}

void Game::printSummary() const {
    if (isWon) {
        std::cout << "Congratulations! You've guessed the word: " << targetWord << "\n";
    } else {
        std::cout << "\nGame Over! The secret word was: " << targetWord << "\n";
    }

    std::cout << "Definition: " << getDefinition(targetWord) << "\n";
}

void Game::play() {
    renderBoard();

    while (guesses.size() < static_cast<size_t>(maxAttempts) && !isWon) {
        std::string guess = promptGuess(guesses.size() + 1);
        guesses.push_back(guess);
        renderBoard();

        if (guess == targetWord) {
            isWon = true;
        }
    }

    printSummary();
}
