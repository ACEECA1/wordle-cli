# Wordle CLI 🟩🟨⬛

A fast, modular, cross-platform terminal-based **Wordle** game built in C++17 with real-time REST API integration, live QWERTY keyboard tracking, ANSI terminal styling, and customizable gameplay options.

---

## ✨ Features

- **Accurate Wordle Mechanics**: Implements a two-pass algorithm correctly handling duplicate letters and position matching.
- **Dynamic API-Powered Word Bank**: Fetches random secret words on the fly based on your chosen word length.
- **Real-Time Word Validation**: Verifies player guesses against a live dictionary API to prevent invalid words.
- **Live QWERTY Keyboard Tracker**: Displays the status of all letters (Green, Yellow, Gray, Unused) directly beneath the board.
- **Educational Word Definitions**: Automatically looks up and displays the real dictionary definition of the secret word at the end of every match.
- **Customizable Gameplay**: Play with any word length (3–12 letters) and custom attempt limits via CLI flags (`-l`, `-m`).
- **Cross-Platform & Zero Manual Dependencies**: Uses CMake `FetchContent` to download and compile dependencies (`cpr`, `nlohmann/json`) automatically on Windows, Linux, and macOS.

---

## 🌐 APIs Used

The game connects to two public REST APIs via **`libcpr`** and **`nlohmann/json`**:

| API | Endpoint | Purpose in Game |
| :--- | :--- | :--- |
| **Random Word API** | `https://random-word-api.herokuapp.com/word?length={n}` | Generates a random secret word dynamically for any chosen word length `{n}`. |
| **Free Dictionary API** | `https://freedictionaryapi.com/api/v1/entries/en/{word}` | **1. Guess Validation:** Verifies if a guessed word is valid English before accepting it.<br>**2. Definition Lookup:** Fetches the meaning of the target word on game over. |

---

## 🪟 Windows Setup (One-Click)

### 1. One-Click Build & Install:
Double-click **`install.bat`** (or run it in Command Prompt / PowerShell):
```cmd
install.bat
```
This automatically:
1. Downloads and compiles all required libraries (`cpr`, `nlohmann/json`) via CMake.
2. Compiles `wordle.exe` in Release mode.
3. Installs `wordle.exe` to `%LOCALAPPDATA%\Wordle` and adds it to your user `PATH`.

Now open any Command Prompt or PowerShell and type:
```cmd
wordle
```

---

## 🐧 Linux / macOS Setup

### Option 1: Using CMake (Auto-fetches dependencies)
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
sudo cmake --install build
```

### Option 2: Using Makefile
```bash
make
make install PREFIX=$HOME/.local   # or sudo make install
```

---

## 🎮 CLI Usage & Flags

```text
Usage:
  wordle [options]

Options:
  -l, --length <n>        Word length (3–12, default: 5)
  -m, --max-attempts <n>  Maximum allowed guesses (min: 1, default: 6)
  -h, --help              Show help message
```

### Examples:

```bash
# Standard 5-letter game with 6 attempts
wordle

# 6-letter word with 7 attempts
wordle -l 6 -m 7

# Hardcore mode: 4-letter word in only 4 attempts
wordle -l 4 -m 4
```

---

## 📂 Project Architecture

```text
├── evaluator.hpp / evaluator.cpp   # Core two-pass letter matching logic
├── display.hpp / display.cpp       # ANSI color blocks, keyboard tracker & terminal rendering
├── dictionary.hpp / dictionary.cpp # libcpr REST API integration, JSON parsing & definitions
├── game.hpp / game.cpp             # Game state machine & interactive loop
├── main.cpp                        # CLI argument parsing and entrypoint
├── CMakeLists.txt                  # Cross-platform CMake build with FetchContent
├── build.bat / install.bat         # One-click Windows build and install scripts
└── Makefile                        # Native Linux compilation and installation rules
```

---

## 📜 License
MIT License.
