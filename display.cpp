#include "display.hpp"
#include <iostream>
#include <string>

void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void printBanner(){
    std::cout << "===========================\n";
    std::cout << "        WORDLE CLI         \n";
    std::cout << "===========================\n\n";
}
void printGuess(const std::string& guess, const std::vector<LetterStatus>& feedback) {
    for(size_t i = 0 ; i < guess.length(); i++){
        if(feedback[i] == LetterStatus::Green){
            std::cout << "\033[1;37;42m " << guess[i] << " \033[0m ";
        }else if(feedback[i] == LetterStatus::Yellow){
            std::cout << "\033[1;37;43m " << guess[i] << " \033[0m ";
        }else{
            std::cout << "\033[1;37;100m " << guess[i] << " \033[0m ";
        }
    }
    std::cout << "\n";
}
