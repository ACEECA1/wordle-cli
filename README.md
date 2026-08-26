# Wordle CLI 🟩🟨⬛

A fast, modular, terminal-based **Wordle** game built in C++17 with real-time REST API integration, ANSI terminal styling, and customizable gameplay options.

---

## ✨ Features

- **Accurate Wordle Mechanics**: Implements a two-pass algorithm correctly handling duplicate letters and position matching.
- **Dynamic API-Powered Word Bank**: Fetches random secret words on the fly based on your chosen word length.
- **Real-Time Word Validation**: Verifies player guesses against a live dictionary API to prevent invalid words.
- **Educational Word Definitions**: Automatically looks up and displays the real dictionary definition of the secret word at the end of every match.
- **Customizable Gameplay**: Play with any word length (3–12 letters) and custom attempt limits via CLI flags (`-l`, `-m`).
- **Vibrant ANSI Terminal UI**: Colored feedback tiles (Green, Yellow, Gray) with live board redrawing.

---

## 🌐 APIs Used

The game connects to two public REST APIs via **`libcpr`** and **`nlohmann/json`**:

| API | Endpoint | Purpose in Game |
| :--- | :--- | :--- |
| **Random Word API** | `https://random-word-api.herokuapp.com/word?length={n}` | Generates a random secret word dynamically for any chosen word length `{n}`. |
| **Free Dictionary API** | `https://freedictionaryapi.com/api/v1/entries/en/{word}` | **1. Guess Validation:** Verifies if a guessed word is valid English before accepting it.<br>**2. Definition Lookup:** Fetches the meaning of the target word on game over. |

---

## 📦 Prerequisites (Arch Linux)

Install the required build tools and libraries:

```bash
# Compiler, build tools, curl, and OpenSSL
sudo pacman -S base-devel curl openssl

# JSON parser (header-only)
sudo pacman -S nlohmann-json

# libcpr (C++ Requests wrapper)
# If not already installed, build & install from source:
git clone https://github.com/libcpr/cpr.git /tmp/cpr
cmake -B /tmp/cpr/build -S /tmp/cpr -DCPR_USE_SYSTEM_CURL=ON -DCPR_BUILD_TESTS=OFF -DCMAKE_BUILD_TYPE=Release
sudo cmake --build /tmp/cpr/build --target install
```

---

## 🛠️ Build & Run Locally

1. **Clone the repository:**
   ```bash
   git clone https://github.com/ACEECA1/wordle-cli.git
   cd wordle-cli
   ```

2. **Compile the project:**
   ```bash
   make
   ```

3. **Run the game:**
   ```bash
   ./wordle
   ```

---

## 🚀 How to Run Globally (`wordle` from Any Directory)

To make `wordle` a global command that you can run from anywhere without being inside this folder:

### Option 1: System-Wide Install (Recommended)
```bash
sudo make install
```
This copies the binary to `/usr/local/bin/wordle`. Now open any terminal and simply type:
```bash
wordle
```

To uninstall:
```bash
sudo make uninstall
```

---

### Option 2: User-Level Install (No `sudo` needed)
```bash
make install PREFIX=$HOME/.local
```
*(Ensure `~/.local/bin` is in your `$PATH`)*.

---

## 🎮 CLI Usage & Flags

```text
Usage:
  wordle [options]

Options:
  -l, --length <n>        Word length (default: 5, min: 3, max: 12)
  -m, --max-attempts <n>  Maximum allowed guesses (default: 6, min: 1)
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
├── display.hpp / display.cpp       # ANSI color blocks & terminal rendering
├── dictionary.hpp / dictionary.cpp # libcpr REST API integration, JSON parsing & definitions
├── game.hpp / game.cpp             # Game state machine & interactive loop
├── main.cpp                        # CLI argument parsing and entrypoint
└── Makefile                        # Compilation and global installation rules
```

---

## 📜 License
MIT License.
