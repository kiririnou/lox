#include "lexer.hpp"
#include "../utils/utils.hpp"

#include <iostream>
#include <format>

// auto Lexer::process() -> std::vector<Token> {
//     // dbg("src = {}", src);

//     while(!is_end()) {
//         start = current;
//         process();
//     }

//     tokens.emplace_back(Token(TokenType::EoF, "", std::any::any(), line)); 
//     return tokens;
// }

auto Lexer::process() -> void {
    while (!is_end()) {
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
            if (match('/')) {
                while (peek() != '\n' && !is_end()) advance();
            } else {
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
        default:
            err("Unexpected character on line {}: {}", line, c);
            break;
        }
    }

    add_token(TokenType::EoF);
}

auto Lexer::advance() -> char {
    return src.at(current++);
}

auto Lexer::add_token_with_literal(TokenType type, std::any literal) -> void {
    // TODO: check if substr is used in a correct way
    auto text = src.substr(start, current - start);
    tokens.emplace_back(Token(type, text, literal, line));
}

auto Lexer::add_token(TokenType type) -> void {
    add_token_with_literal(type, std::any::any());
}

auto Lexer::match(char expected) -> bool {
    if (is_end())
        return false;
    if (src.at(current) != expected)
        return false;
    
    current++;
    return true;
}

auto Lexer::peek() -> char {
    if (is_end())
        return '\0';
    return src.at(current);
}

auto Lexer::is_end() -> bool {
    return current >= src.length();
}