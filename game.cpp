#include "game.hpp"
#include "dictionary.hpp"
#include "evaluator.hpp"
#include "display.hpp"
#include <iostream>
#include <algorithm>

Game::Game(int length, int maxAttempts) {
    this->length = length;
    this->maxAttempts = maxAttempts;
    this->targetWord = getRandomWord(length);
}

void Game::play(){
    clearScreen();
    int attempts = 0;
    printBanner();
    while(attempts < maxAttempts && !isWon){
        std::string guess;
        std::cout << "Attempt " << (attempts + 1) << "/" << maxAttempts << ". Enter your guess: ";
        std::cin >> guess;
        if(guess.length() != length){
            std::cout << "Please enter a " << length << "-letter word.\n";
            continue;
        }
        if(!isValidWord(guess)){
            std::cout << "Invalid word. Please try again.\n";
            continue;
        }
        for(auto & c: guess) c = std::toupper(c);
        clearScreen();
        printBanner();
        guesses.push_back(guess);
        for(const auto& g : guesses){
            std::vector<LetterStatus> feedback = evaluate(targetWord, g);
            printGuess(g, feedback);
            std::cout << "\n";
        }
        std::vector<LetterStatus> feedback = evaluate(targetWord, guess);
        if(guess == targetWord){
            isWon = true;
            std::cout << "Congratulations! You've guessed the word: " ;
            std::cout << "\nDefinition: " << getDefinition(targetWord) << "\n";
        } else {
            std::cout << "Incorrect guess. Try again.\n";
            attempts++;
        }
    }
    if (!isWon) {
        std::cout << "\nGame Over! The secret word was: " << targetWord << "\n";
        std::cout << "Definition: " << getDefinition(targetWord) << "\n";
    }
}