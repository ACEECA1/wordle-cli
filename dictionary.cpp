#include "dictionary.hpp"
#include "cpr/cpr.h"
#include <algorithm>
#include <cctype>
#include <nlohmann/json.hpp>
using json = nlohmann::json;


bool isValidWord(const std::string& word) {
    std::string lowerWord = word;
    std::transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    std::string url = "https://freedictionaryapi.com/api/v1/entries/en/" + lowerWord;
    cpr::Response r = cpr::Get(cpr::Url{url});
    json responseJson = json::parse(r.text);
    if (responseJson.contains("entries") && responseJson["entries"].is_array()) {
        return !responseJson["entries"].empty();
    }
    return false;  
}

std::string getRandomWord(int length){
    std::string url = "https://random-word-api.herokuapp.com/word?length=" + std::to_string(length);
    cpr::Response r = cpr::Get(cpr::Url{url});
    json responseJson = json::parse(r.text);
    std::vector<std::string> words = responseJson.get<std::vector<std::string>>();
    std::string randomWord = !words.empty() ? words[0] : "";
    std::transform(randomWord.begin(), randomWord.end(), randomWord.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return randomWord;
}


std::string getDefinition(std::string word) {
    std::transform(word.begin(), word.end(), word.begin(),
                    [](unsigned char c) { return std::tolower(c); });

    std::string url = "https://freedictionaryapi.com/api/v1/entries/en/" + word;
    cpr::Response r = cpr::Get(cpr::Url{url});

    if (r.status_code != 200 || r.text.empty()) {
        return "Definition not found.";
    }

    try {
        json responseJson = json::parse(r.text);
        if (responseJson.contains("entries") && responseJson["entries"].is_array() && !responseJson["entries"].empty()) {
            const auto& entry = responseJson["entries"][0];
            if (entry.contains("senses") && entry["senses"].is_array() && !entry["senses"].empty()) {
                const auto& sense = entry["senses"][0];
                if (sense.contains("definition") && sense["definition"].is_string()) {
                    return sense["definition"].get<std::string>();
                }
            }
        }
    } catch (...) {
        return "Definition not found.";
    }

    return "Definition not found.";
}