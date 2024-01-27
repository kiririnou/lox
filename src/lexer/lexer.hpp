#pragma once

#include <string>
#include <vector>
#include <map>
#include <any>

#include "token.hpp"

class Lexer {
public:
    // Lexer() {}
    Lexer(const std::string &src)
        : src(src), tokens(std::vector<Token>{}), start(0), current(0), line(1) {}

    auto process() -> std::vector<Token>;
    auto process_token() -> void;
    auto advance() -> char;
    auto add_token_with_literal(TokenType type, std::any literal) -> void;
    auto add_token(TokenType type) -> void;
    auto match(char expected) -> bool;
    auto peek() -> char;
    auto peek_next() -> char;
    auto string() -> void;
    auto number() -> void;
    auto identifier() -> void;

    auto is_digit(char c) -> bool;
    auto is_alpha(char c) -> bool;
    auto is_alpha_numeric(char c) -> bool;
    auto is_end() -> bool;

private:
    const std::string src;
    std::vector<Token> tokens;
    uint32_t start;
    uint32_t current;
    uint32_t line;
    const std::map<std::string, TokenType> keywords = {
        { "and", TokenType::And },
        { "class", TokenType::Class },
        { "else", TokenType::Else },
        { "false", TokenType::False },
        { "for", TokenType::For },
        { "fun", TokenType::Fun },
        { "if", TokenType::If },
        { "nil", TokenType::Nil },
        { "or", TokenType::Or },
        { "print", TokenType::Print },
        { "return", TokenType::Return },
        { "super", TokenType::Super },
        { "this", TokenType::This },
        { "true", TokenType::True },
        { "var", TokenType::Var },
        { "while", TokenType::While },
    };
};