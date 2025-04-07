#include <iostream>
#include "lexer.hpp"

int main() {
    std::string code = "int x = 42 + y;";
    Lexer lexer(code);
    Token token;

    while ((token = lexer.nextToken()).type != TokenType::EndOfFile) {
        std::cout << "Token: " << token.value << std::endl;
    }

    return 0;
}
