#include "dictionary.hpp"
#include "cpr/cpr.h"
#include <algorithm>
#include <cctype>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

bool isValidWord(const std::string& word) {
    if (word.empty()) return false;

    std::string lowerWord = word;
    std::transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    std::string url = "https://freedictionaryapi.com/api/v1/entries/en/" + lowerWord;
    try {
        cpr::Response r = cpr::Get(cpr::Url{url}, cpr::Timeout{3000});
        if (r.status_code != 200 || r.text.empty()) {
            return false;
        }

        json responseJson = json::parse(r.text);
        if (responseJson.contains("entries") && responseJson["entries"].is_array()) {
            return !responseJson["entries"].empty();
        }
    } catch (...) {
        return false;
    }
    return false;  
}

std::string getRandomWord(int length) {
    std::string url = "https://random-word-api.herokuapp.com/word?length=" + std::to_string(length);
    try {
        cpr::Response r = cpr::Get(cpr::Url{url}, cpr::Timeout{3000});
        if (r.status_code == 200 && !r.text.empty()) {
            json responseJson = json::parse(r.text);
            if (responseJson.is_array() && !responseJson.empty()) {
                std::vector<std::string> words = responseJson.get<std::vector<std::string>>();
                if (!words.empty() && !words[0].empty()) {
                    std::string randomWord = words[0];
                    std::transform(randomWord.begin(), randomWord.end(), randomWord.begin(),
                                   [](unsigned char c) { return std::toupper(c); });
                    return randomWord;
                }
            }
        }
    } catch (...) {
    }

    return "";
}

std::string getDefinition(std::string word) {
    std::transform(word.begin(), word.end(), word.begin(),
                    [](unsigned char c) { return std::tolower(c); });

    std::string url = "https://freedictionaryapi.com/api/v1/entries/en/" + word;
    try {
        cpr::Response r = cpr::Get(cpr::Url{url}, cpr::Timeout{3000});
        if (r.status_code != 200 || r.text.empty()) {
            return "Definition not available.";
        }

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
        return "Definition not available.";
    }

    return "Definition not available.";
}