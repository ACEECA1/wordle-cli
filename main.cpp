#include "game.hpp"
#include <iostream>
#include <string>

struct Config {
    int length = 5;
    int maxAttempts = 6;
};

void showHelp() {
    std::cout << "Wordle CLI\n\n"
              << "Usage: ./wordle [-l length] [-m maxAttempts]\n\n"
              << "Options:\n"
              << "  -l, --length <n>        Word length (default: 5)\n"
              << "  -m, --max-attempts <n>  Max allowed attempts (default: 6)\n"
              << "  -h, --help              Show help\n";
}

bool parseArgs(int argc, char* argv[], Config& cfg) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            showHelp();
            return false;
        }
        if ((arg == "-l" || arg == "--length") && i + 1 < argc) {
            cfg.length = std::max(3, std::stoi(argv[++i]));
        } else if ((arg == "-m" || arg == "--max-attempts") && i + 1 < argc) {
            cfg.maxAttempts = std::max(1, std::stoi(argv[++i]));
        } else {
            std::cerr << "Unknown option: " << arg << "\nUse -h for help.\n";
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    Config config;
    if (!parseArgs(argc, argv, config)) {
        return 0;
    }

    Game game(config.length, config.maxAttempts);
    game.play();
    return 0;
}
