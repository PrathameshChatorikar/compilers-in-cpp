#include <iostream>
#include <string>
#include <vector>
#include <cctype>

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

class Lexer {
public:
    Lexer(const std::string& src) : source(src), pos(0) {}

    Token nextToken() {
        skipWhitespace();

        if (pos >= source.size()) return { TokenType::EndOfFile, "" };

        char current = source[pos];

        // Numbers
        if (std::isdigit(current)) {
            std::string num;
            while (pos < source.size() && std::isdigit(source[pos])) {
                num += source[pos++];
            }
            return { TokenType::Number, num };
        }

        // Identifiers (starts with letter or underscore)
        if (std::isalpha(current) || current == '_') {
            std::string ident;
            while (pos < source.size() && (std::isalnum(source[pos]) || source[pos] == '_')) {
                ident += source[pos++];
            }
            return { TokenType::Identifier, ident };
        }

        // Single-character tokens
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

private:
    std::string source;
    size_t pos;

    void skipWhitespace() {
        while (pos < source.size() && std::isspace(source[pos])) {
            ++pos;
        }
    }
};

int main() {
    std::string code = "int x = 42 + y;";
    Lexer lexer(code);
    Token token;

    while ((token = lexer.nextToken()).type != TokenType::EndOfFile) {
        std::cout << "Token: " << token.value << std::endl;
    }

    return 0;
}