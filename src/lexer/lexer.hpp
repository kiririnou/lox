#pragma once

#include <string>
#include <vector>
#include <any>

#include "token.hpp"

class Lexer {
public:
    // Lexer() {}
    Lexer(const std::string &src)
        : src(src), tokens(std::vector<Token>{}), start(0), current(0), line(1) {}

    void process();
    char advance();
    void add_token_with_literal(TokenType type, std::any literal);
    void add_token(TokenType type);
    bool match(char expected);
    char peek();

    bool is_end();

// private:
    const std::string src;
    std::vector<Token> tokens;
    uint32_t start;
    uint32_t current;
    uint32_t line;
};