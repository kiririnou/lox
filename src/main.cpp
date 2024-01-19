#include "lib/test.hpp"
#include "lexer/lexer.hpp"

int main() {
    print_hello();

    Lexer lexer{};
    lexer.test();

    return 0;
}
