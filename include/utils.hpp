#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

// Utilities to process text files

inline std::vector<std::string> read_lines(const std::string& path) {
    std::ifstream in(path);
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(in, line))
        lines.push_back(line);

    return lines;
}

inline std::string read_file(const std::string& path) {
    std::ifstream in(path);
    std::stringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

inline std::vector<std::string> split(const std::string& s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> result;
    while (std::getline(ss, item, delim))
        result.push_back(item);
    return result;
}

inline std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end   = s.find_last_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    return s.substr(start, end - start + 1);
}

template <typename T>
void display_list(std::vector<T> arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void printCharLiteral(char ch) {
    switch (ch) {
        case '\n': std::cout << "\\n"; break;
        case '\t': std::cout << "\\t"; break;
        case '\\': std::cout << "\\\\"; break;
        default:   std::cout << ch; break;
    }
}