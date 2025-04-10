#pragma once
#include "token.hpp"
#include "lexer.hpp"
#include "ast.hpp"

class Parser {
public:
    explicit Parser(Lexer& lexer);
    std::unique_ptr<ASTNode> parse();

private:
    Lexer& lexer;
    Token currentToken;

    void eat(TokenType expected);
    std::unique_ptr<ASTNode> parseExpression();
    std::unique_ptr<ASTNode> parsePrimary();
    std::unique_ptr<ASTNode> parseAssignment();
};
