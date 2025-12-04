#include "utils.hpp"
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <regex>
#include <string>
#include <climits>

using namespace std;

vector<vector<char>> make_map() {
    vector<string> a = read_lines("./inputs/day4_eg.txt");
    vector<vector<char>> mat;
    for (auto s : a) {
        vector<char> x;
        int l = (int) s.size();
        for (int j = 0; j < l; j++) {
            x.push_back(s[j]);
        }
        // display_list(x);
        mat.push_back(x);
    }
    return mat;
}

int countAround(const vector<vector<char>>& mat, int r, int c) {
    if (mat[r][c] != '@') return 5;
    // cout << mat[r][c] << endl;
    int dr[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
    int dc[8] = {-1, 0, 1,-1, 1,-1, 0, 1};
    int R = mat.size();
    int C = mat[0].size();
    int cnt = 0;

    for (int k = 0; k < 8; ++k) {
        int nr = r + dr[k];
        int nc = c + dc[k];
        if (0 <= nr && nr < R && 0 <= nc && nc < C) {
            if (mat[nr][nc] == '@') cnt++;
        }
    }
    // cout << r << " " << c << " " << cnt << endl;
    return cnt;
}

int soln1() {
    auto mat = make_map();
    int R = mat.size();
    int C = mat[0].size();
    int cnt = 0;
    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            int adj = countAround(mat, r, c);
            // cout << r << " " << c << " " << adj << endl;
            if (adj < 4) {
                cnt++;
            }
        }
    }
    return cnt;
}

vector<vector<char>> soln2_helper(vector<vector<char>> mat) {
    int R = mat.size();
    int C = mat[0].size();
    vector<vector<int>> op;
    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            int adj = countAround(mat, r, c);
            if (adj < 4) {
                op.push_back(vector<int>{r, c});
            }
        }
    }
    for (auto v : op) {
        mat[v[0]][v[1]] = 'x';
    }

    return mat;
}

int count_x(vector<vector<char>> mat) {
    int R = mat.size();
    int C = mat[0].size();
    int cnt = 0;
    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) { 
            if (mat[r][c] == 'x') ++cnt;
        }
    }
    return cnt;
}

void soln2() {
    auto mat = make_map();

    while (true) {
        auto new_mat = soln2_helper(mat);
        if (mat == new_mat) {
            cout << count_x(new_mat) << endl;
            return;
        }
        mat = new_mat;
    }
}

int main() {
    cout << soln1() << endl;
    soln2();
    return 0;
}