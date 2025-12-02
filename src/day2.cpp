#include "utils.hpp"
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <regex>
#include <string>
using namespace std;

#define COUNT_DIGIT(N) ((N) == 0? 1 : floor(log10((N))) + 1)

long long fastpow(long long base, long long exp) {
    long long result = 1;
    while (exp > 0) {
        if (exp & 1) result *= base;
        base *= base;
        exp >>= 1;
    }
    return result;
}

inline bool isValid(long long v) {
    long long digits = COUNT_DIGIT(v);
    if (digits & 1) {
        return true;
    } else {
        long long divd = fastpow(10L, digits / 2);
        return !(v / divd == v % divd);
    }
}

vector<pair<long long, long long>> process_file() {
    auto v = read_file("./inputs/day2.txt");
    vector<string> ranges = split(trim(v), ',');
    vector<pair<long long, long long>> out;
    for (auto s : ranges) {
        vector<string> arr = split(s, '-');
        long long start = stoll(arr[0]), end = stoll(arr[1]);
        out.push_back({start, end});
    }
    return out;
}

bool isRepeated(string s) {
    static const regex re(R"((.+)\1+)");
    return regex_match(s, re);
}

void soln1() {
    auto ranges = process_file();
    long long out = 0L;
    for (auto r : ranges) {
        long long start = r.first, end = r.second;
        for (long long cur = start; cur < end; cur++) {
            if (!isValid(cur)) out += cur;
        }
    }
    cout << out << endl;
}

void soln2() {
    auto ranges = process_file();
    long long out = 0L;
    for (auto r : ranges) {
        long long start = r.first, end = r.second;
        for (long long cur = start; cur < end; cur++) {
            if (isRepeated(to_string(cur))) {
                // cout << cur << endl;
                out += cur;
            }
        }
    }
    cout << out << endl;
}

int main() {
    soln1();
    soln2();
    return 0;
}