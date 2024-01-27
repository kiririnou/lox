#include "lexer.hpp"
#include "../utils/utils.hpp"

#include <iostream>
#include <format>

auto Lexer::process() -> std::vector<Token> {
    while (!is_end()) {
        start = current;
        process_token();
    }

    add_token(TokenType::EoF);
    return tokens;
}

auto Lexer::process_token() -> void {
    auto c = advance();
    dbg("c = {}", c);

    switch (c)
    {
    case '(':
        add_token(TokenType::LeftParen);
        break;
    case ')':
        add_token(TokenType::RightParen);
        break;
    case '{':
        add_token(TokenType::LeftBrace);
        break;
    case '}':
        add_token(TokenType::RightBrace);
        break;
    case ',':
        add_token(TokenType::Comma);
        break;
    case '.':
        add_token(TokenType::Dot);
        break;
    case '-':
        add_token(TokenType::Minus);
        break;
    case '+':
        add_token(TokenType::Plus);
        break;
    case ';':
        add_token(TokenType::Semicolon);
        break;
    case '*':
        add_token(TokenType::Star);
        break;
    case '!':
        add_token(match('=') ? TokenType::BangEqual : TokenType::Bang);
        break;
    case '=':
        add_token(match('=') ? TokenType::EqualEqual : TokenType::Equal);
        break;
    case '<':
        add_token(match('<') ? TokenType::LessEqual : TokenType::Less);
        break;
    case '>':
        add_token(match('>') ? TokenType::GreaterEqual : TokenType::Greater);
        break;
    case '/':
        if (match('/'))
        {
            while (peek() != '\n' && !is_end())
                advance();
        }
        else
        {
            add_token(TokenType::Slash);
        }
        break;
    case ' ':
    case '\r':
    case '\t':
        break;
    case '\n':
        line++;
        break;
    case '"':
        string();
        break;
    default:
        if (is_digit(c)) {
            number();
        } else {
            err("Unexpected character on line {}: {}", line, c);
        }
        break;
    }
}

auto Lexer::advance() -> char {
    return src.at(current++);
}

auto Lexer::add_token_with_literal(TokenType type, std::any literal) -> void {
    // TODO: check if substr is used in a correct way
    std::string lexeme; 
    if (type == TokenType::EoF) {
        lexeme = "EoF";
    } else {
        lexeme = src.substr(start, current - start);
    }
    tokens.emplace_back(Token(type, lexeme, literal, line));
}

auto Lexer::add_token(TokenType type) -> void {
    add_token_with_literal(type, std::any::any());
}

auto Lexer::match(char expected) -> bool {
    if (is_end()) {
        return false;
    }
    if (src.at(current) != expected) {
        return false;
    }
    
    current++;
    return true;
}

auto Lexer::peek() -> char {
    if (is_end()) {
        return '\0';
    }
    return src.at(current);
}

auto Lexer::peek_next() -> char {
    if ((current + 1) >= src.length()) {
        return '\0';
    }
    return src.at(current + 1);
}

auto Lexer::string() -> void {
    while (peek() != '"' && !is_end()) {
        if (peek() == '\n') {
            line++;
        }
        advance();
    }

    if (is_end()) {
        err("Non terminated string at line {}", line);
        return;
    }

    advance();

    auto value = src.substr(start + 1, current - 1);
    add_token_with_literal(TokenType::String, value);
}

auto Lexer::number() -> void {
    dbg("inside number");
    while (is_digit(peek())) {
        advance();
    }

    if ((peek() == '.') && (is_digit(peek_next()))) {
        advance();
        while (is_digit(peek())) {
            advance();
        }
    }

    auto literal = src.substr(start, current - start);
    add_token_with_literal(TokenType::Number, std::stod(literal));
}

auto Lexer::is_digit(char c) -> bool {
    return (c >= '0') && (c <= '9');
}

auto Lexer::is_end() -> bool {
    return current >= src.length();
}