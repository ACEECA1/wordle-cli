#pragma once
#include <string>
#include <vector>

enum class LetterStatus{
    Gray,
    Green,
    Yellow,
};

std::vector<LetterStatus> evaluate(const std::string& secret , const std::string& guess);
