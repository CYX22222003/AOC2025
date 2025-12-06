#include "utils.hpp"
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <regex>
#include <string>
#include <climits>
#include <stdexcept>

using namespace std;

vector<vector<long long>> matrix;
vector<string> ops;
vector<string> str_matrix;

void process_file() {
    vector<string> lines = read_lines("./inputs/day6_eg.txt");
    int n = (int) lines.size();
    for (int i = 0; i < n - 1; i++) {
        vector<string> line = split(lines[i], ' ');
        vector<long long> row;
        for (auto l : line) {
            // cout << trim(l) << endl;
            if(trim(l).size() > 0)row.push_back(stoll(trim(l)));
        }
        display_list(row);
        matrix.push_back(row);
    }

    auto last_line = split(lines[n - 1], ' ');
    for (auto c : last_line) {
        if (trim(c).size() > 0) ops.push_back(trim(c));
    }
    display_list(ops);
}

vector<string> transposeMatrix(vector<string>& a) {
    const size_t H = a.size();
    const size_t W = a[0].size();
    vector<string> t(W, string(H, ' '));

    for (size_t r = 0; r < H; r++) {
        for (size_t c = 0; c < W; c++) {
            // printCharLiteral(a[r][c]);
            // cout << " ( " << r << " " << c << " -> " << c << " " << r << " )"<< endl;
            t[c][r] = a[r][c];
        }
    }

    return t;
}

void soln1() {
    int R = matrix.size();
    // int C = matrix[0].size();
    display_list(ops);
    int n = ops.size();
    long long total = 0;
    // cout << "size of ops: " << n << endl;
    for (int ci = 0; ci < n; ci++) {
        string c = ops[ci];
        long long acc;
        // cout << c << endl;
        if (c == "*") {
            acc = 1;
            for (int ri = 0; ri < R; ri++) {
                // cout << matrix[ri][ci] << endl;
                acc *= matrix[ri][ci];
            }
        } else {
            acc = 0;
            for (int ri = 0; ri < R; ri++) {
                // cout << matrix[ri][ci] << endl;
                acc += matrix[ri][ci];
            }
        }
        // cout << "acc: " << acc << endl;
        total += acc;
    }
    cout << "total: " << total << endl;
}

void soln2() {
    vector<string> mat = read_lines("./inputs/day6.txt");
    // for (auto j : mat) {
    //     cout << j << endl;
    // }
    auto new_mat = transposeMatrix(mat);
    int isMult = -1;
    long long total = 0;
    long long acc;
    size_t pos_star;
    size_t pos_plus;
    for (auto l : new_mat) {
        cout << l << endl;

        if (trim(l).size() == 0) {
            isMult = -1;
            total += acc;
            cout << "acc: " << acc << endl;
            continue;
        }
        
        if (isMult == -1) {
            pos_star = l.find("*");
            pos_plus = l.find("+");
            // cout << "pos_star: " << pos_star << endl;
            // cout << "pos_plus: " << pos_plus << endl;
            if (pos_star != string::npos) {
                isMult = 1;
                acc = stoll(trim(l.substr(0, pos_star)));
            } else if (pos_plus != string::npos) {
                isMult = 0;
                acc = stoll(trim(l.substr(0, pos_plus)));
            } else {
                throw runtime_error("What the hell!");
            }
        } else {
            if (isMult == 1) {
                acc *= stoll(trim(l));
            } else {
                acc += stoll(trim(l));
            }
        }
    }
    total += acc;
    cout << "total: " << total << endl;
}

int main() {
    // process_file();
    // soln1();
    soln2();
}