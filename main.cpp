#include "game.hpp"
#include "display.hpp"
#include <iostream>
#include <string>
#include <stdexcept>

struct Config {
    int length = 5;
    int maxAttempts = 6;
};

void showHelp() {
    std::cout << "Wordle CLI\n\n"
              << "Usage: wordle [-l length] [-m maxAttempts]\n\n"
              << "Options:\n"
              << "  -l, --length <n>        Word length (3–12, default: 5)\n"
              << "  -m, --max-attempts <n>  Max allowed attempts (min: 1, default: 6)\n"
              << "  -h, --help              Show help message\n";
}

bool parseArgs(int argc, char* argv[], Config& cfg) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            showHelp();
            return false;
        }
        if ((arg == "-l" || arg == "--length") && i + 1 < argc) {
            try {
                int val = std::stoi(argv[++i]);
                if (val < 3 || val > 12) {
                    std::cerr << "Error: Word length must be between 3 and 12.\n";
                    return false;
                }
                cfg.length = val;
            } catch (const std::exception&) {
                std::cerr << "Error: Invalid number provided for " << arg << ".\n";
                return false;
            }
        } else if ((arg == "-m" || arg == "--max-attempts") && i + 1 < argc) {
            try {
                int val = std::stoi(argv[++i]);
                if (val < 1) {
                    std::cerr << "Error: Max attempts must be at least 1.\n";
                    return false;
                }
                cfg.maxAttempts = val;
            } catch (const std::exception&) {
                std::cerr << "Error: Invalid number provided for " << arg << ".\n";
                return false;
            }
        } else {
            std::cerr << "Unknown option: " << arg << "\nUse -h for help.\n";
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    initTerminal();

    Config config;
    if (!parseArgs(argc, argv, config)) {
        return 0;
    }

    Game game(config.length, config.maxAttempts);
    game.play();
    return 0;
}
