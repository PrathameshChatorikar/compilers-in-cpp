#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

enum class TokenType {
    Identifier,
    Number,
    Assign,
    Plus,
    Minus,
    Multiply,
    Divide,
    Semicolon,
    LParen,
    RParen,
    EndOfFile,
    Unknown
};

struct Token {
    TokenType type;
    std::string value;
};

#endif // TOKEN_HPP
