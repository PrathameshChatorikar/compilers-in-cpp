#include "parser.hpp"
#include <stdexcept>

Parser::Parser(Lexer& lex) : lexer(lex) {
    currentToken = lexer.nextToken();
}

void Parser::eat(TokenType expected) {
    if (currentToken.type == expected) {
        currentToken = lexer.nextToken();
    } else {
        throw std::runtime_error("Unexpected token: " + currentToken.value);
    }
}

std::unique_ptr<ASTNode> Parser::parse() {
    return parseAssignment();
}

std::unique_ptr<ASTNode> Parser::parseAssignment() {
    if (currentToken.type == TokenType::Keyword && currentToken.value == "int") {
        eat(TokenType::Keyword);
        std::string varName = currentToken.value;
        eat(TokenType::Identifier);
        eat(TokenType::Operator);  // should be '='
        auto expr = parseExpression();
        eat(TokenType::Operator);  // should be ';'
        return std::make_unique<AssignmentNode>(varName, std::move(expr));
    }
    return nullptr;
}

std::unique_ptr<ASTNode> Parser::parseExpression() {
    auto lhs = parsePrimary();
    if (currentToken.type == TokenType::Operator && (currentToken.value == "+" || currentToken.value == "-")) {
        std::string op = currentToken.value;
        eat(TokenType::Operator);
        auto rhs = parsePrimary();
        return std::make_unique<BinaryOpNode>(op, std::move(lhs), std::move(rhs));
    }
    return lhs;
}

std::unique_ptr<ASTNode> Parser::parsePrimary() {
    if (currentToken.type == TokenType::Number) {
        int val = std::stoi(currentToken.value);
        eat(TokenType::Number);
        return std::make_unique<NumberNode>(val);
    }
    if (currentToken.type == TokenType::Identifier) {
        std::string name = currentToken.value;
        eat(TokenType::Identifier);
        return std::make_unique<VariableNode>(name);
    }
    throw std::runtime_error("Unexpected primary token: " + currentToken.value);
}
