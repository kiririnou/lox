#include <iostream>
#include <format>
#include <memory>
#include <variant>

#include "lib/test.hpp"
#include "utils/utils.hpp"
#include "lexer/token.hpp"
#include "lexer/lexer.hpp"
#include "parser/expr.hpp"

static void run(const std::string &src) {
    Lexer lexer{src};
    auto tokens = lexer.process();
    dbg("lexer.tokens.size() = {}", tokens.size());

    for (auto &token : tokens) {
        info("token: {} = {}", token.to_str(), token.lexeme);
    }
}

static void run_file(const std::string &path) {
    std::string file = read_file(path);
    info("{} content:\n{}\n", path, file);
    run(file);
}

// TODO: fix
static void run_prompt() {
    std::cout << ">";
    for (std::string line; std::getline(std::cin, line);) {
        if (line == ":q") {
            break;
        }
        logger("", std::format("{}\n", line));
        run(line);

        std::cout << ">";
    }
}

int main(int argc, char **argv) {
    // UnaryExpr ===========================================
    Token t{TokenType::Minus, "-", std::monostate{}, 1};
    // UnaryExpr ue{t, std::unique_ptr<LiteralExpr>{
    //     new LiteralExpr{std::string{"123"}}
    // }};
    // UnaryExpr ===========================================

    Token t1{TokenType::Star, "*", std::monostate{}, 1};

    // LiteralExpr le1{45.67};
    // GroupExpr ge1{std::unique_ptr<LiteralExpr>{
    //     new LiteralExpr{45.68}
    // }};

    // BinaryExpr be = BinaryExpr{&ue, t1, &ue};

    std::unique_ptr<IExpr> arg(new BinaryExpr{
            std::unique_ptr<UnaryExpr>{
                new UnaryExpr{
                t,
                std::unique_ptr<LiteralExpr>{
                    new LiteralExpr{std::string{"123"}}
                }
            }},
            t1,
            std::unique_ptr<GroupExpr>{
                new GroupExpr{std::unique_ptr<LiteralExpr>{
                    new LiteralExpr{45.67}
                }
            }}
    });

    AstPrintVisitor v{};
    auto str = v.print(*arg);
    dbg("{}", str);

    // if (argc > 2) {
    //     std::cout << "Usage: lox [script]\n";
    // } else if (argc == 2) {
    //     run_file(argv[1]);
    // } else {
    //     run_prompt();
    // }

    return 0;
}
