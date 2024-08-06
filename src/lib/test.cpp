#include "test.hpp"

#include <iostream>
#include <format>

void print_hello() {
    std::cout << std::format("Hello, {}!\n", "World");
}