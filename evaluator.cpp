#include "evaluator.hpp"
#include <unordered_map>


std::vector<LetterStatus> evaluate(const std::string& secret , const std::string& guess){
    std::vector<LetterStatus> result(secret.length(), LetterStatus::Gray);
    std::unordered_map<char, int> letterCounts;
    for(const auto& letter : secret){
        letterCounts[letter]++;
    }
    for(size_t i = 0; i < guess.length(); i++){
        if(guess[i] == secret[i]){
            result[i] = LetterStatus::Green;
            letterCounts[secret[i]]--;
        }
    }
    for(size_t i = 0; i < secret.length(); i++){
        if(result[i] == LetterStatus::Green){
            continue;
        }
        if(letterCounts[guess[i]] > 0){
            result[i] = LetterStatus::Yellow;
            letterCounts[guess[i]]--;
        }
    }
    return result;
}