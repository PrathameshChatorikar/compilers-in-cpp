#include "parser.hpp"
#include "ast.hpp"

int main() {
    std::string code = "int x = 42 + y;";
    Lexer lexer(code);
    Parser parser(lexer);

    auto ast = parser.parse();

    std::cout << "AST successfully built.\n";
    return 0;
}
