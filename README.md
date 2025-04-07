# Simple Lexical Analyzer in C++

This project is a basic lexical analyzer written in C++. It reads an input file (`front.in`) and breaks the content into tokens such as identifiers, integer literals, and operators.

## 🔍 What It Does

- Recognizes identifiers (e.g., `varName`)
- Recognizes integer literals (e.g., `123`)
- Supports basic operators: `+`, `-`, `*`, `/`, `=`
- Handles parentheses: `(` and `)`
- Ignores whitespace
- Outputs tokens with their corresponding lexemes

## 🛠 How to Compile

Use any standard C++ compiler. Example with `g++`:

```bash
g++ front.cpp -o lexer
