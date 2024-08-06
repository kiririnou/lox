#include <iostream>
#include <format>

#include "lib/test.hpp"
#include "utils/utils.hpp"
#include "lexer/token.hpp"
#include "lexer/lexer.hpp"

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
    if (argc > 2) {
        std::cout << "Usage: lox [script]\n";
    } else if (argc == 2) {
        run_file(argv[1]);
    } else {
        run_prompt();
    }

    return 0;
}
