#include "lexer.hpp"
#include <cctype>

Lexer::Lexer(const std::string& src) : source(src), pos(0) {}

void Lexer::skipWhitespace() {
    while (pos < source.size() && std::isspace(source[pos])) {
        ++pos;
    }
}

Token Lexer::nextToken() {
    skipWhitespace();

    if (pos >= source.size()) return { TokenType::EndOfFile, "" };

    char current = source[pos];

    if (std::isdigit(current)) {
        std::string num;
        while (pos < source.size() && std::isdigit(source[pos])) {
            num += source[pos++];
        }
        return { TokenType::Number, num };
    }

    if (std::isalpha(current) || current == '_') {
        std::string ident;
        while (pos < source.size() && (std::isalnum(source[pos]) || source[pos] == '_')) {
            ident += source[pos++];
        }
        return { TokenType::Identifier, ident };
    }

    switch (source[pos++]) {
        case '=': return { TokenType::Assign, "=" };
        case '+': return { TokenType::Plus, "+" };
        case '-': return { TokenType::Minus, "-" };
        case '*': return { TokenType::Multiply, "*" };
        case '/': return { TokenType::Divide, "/" };
        case ';': return { TokenType::Semicolon, ";" };
        case '(': return { TokenType::LParen, "(" };
        case ')': return { TokenType::RParen, ")" };
        default:  return { TokenType::Unknown, std::string(1, current) };
    }
}
