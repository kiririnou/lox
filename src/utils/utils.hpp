#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <iterator>
#include <format>

inline void logger(const std::string &level, const std::string &msg) {
    std::cout << std::format("[{}] {}\n", level, msg);
}

#define dbg(...) logger("debug", std::format(__VA_ARGS__))
#define err(...) logger("error", std::format(__VA_ARGS__))
#define info(...) logger("info", std::format(__VA_ARGS__))

static inline std::string read_file(const std::string &path) {
    std::ifstream reader(path, std::ios::in | std::ios::binary);
    std::string file;

    reader.unsetf(std::ios_base::skipws);
    reader.seekg(0, std::ios::end);
    file.reserve(reader.tellg());
    reader.seekg(0, std::ios::beg);

    file.assign((std::istream_iterator<char>(reader)), std::istream_iterator<char>());
    reader.setf(std::ios_base::skipws);

    return file;
}
