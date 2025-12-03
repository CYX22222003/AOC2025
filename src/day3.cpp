#include "utils.hpp"
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <regex>
#include <string>
#include <climits>

#define TO_INT(n) ((n) - '0')

using namespace std;

vector<string> process_files() {
    return read_lines("./inputs/day3.txt");
}

int process_line(const string& str) {
    int n = str.size();
    int prefix_max = TO_INT(str[0]);
    int out = INT_MIN;
    for (int i = 1; i < n; ++i) {
        prefix_max = max(prefix_max, TO_INT(str[i - 1]));
        out = max(out, 10 * prefix_max + TO_INT(str[i]));
    }
    return out;
}

long long process_line2(const string& str, int limit = 12) {
    // Use monotonic stack
    int n = str.size();
    vector<char> st;

    for (int i = 0; i < n; i++) {
        char c = str[i];
        // When can pop? 
        // 1. last elements in the stack is less than c 
        // 2. total number of elements remained is not less than 12 
        while (!st.empty() && st.back() < c && (int)st.size() - 1 + (n - i) >= limit) {
            st.pop_back();
        }

        if ((int)st.size() < limit) {
            st.push_back(c);
        }
    }
    return stoll(string(st.begin(), st.end()));
}


int soln1() {
    vector<string> lines = process_files();
    int out = 0;
    for (auto l : lines) {
        out += process_line(l);
    }
    return out;
}

long long soln2() {
    vector<string> lines = process_files();
    long long out = 0;
    for (auto l : lines) {
        out += process_line2(l);
    }
    return out;
}

int main() {
    cout << soln1() << endl;
    cout << soln2() << endl;
    return 0;
}