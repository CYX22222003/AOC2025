#include "utils.hpp"
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <regex>
#include <string>
#include <climits>
#include <stdexcept>
#include <unordered_set>
#include <algorithm>
#include <numeric>

using namespace std;

unordered_set<int> find_split(const string& s) {
    int n = s.size();
    unordered_set<int> out;
    for (int i = 0; i < n; i++) {
        if(s[i] == '^') out.insert(i);
    }
    return out;
}

void soln1() {
    vector<string> mat = read_lines("./inputs/day7.txt");
    int R = mat.size();
    int C = mat[0].size();
    unordered_set<int> prev_beams;

    // Find the starting point of S
    int start_pos = mat[0].find("S");
    // Insert prev beams
    prev_beams.insert(start_pos);
    int cnt = 0;
    // Traverse and split
    for (int i = 1; i < R; i++) {
        unordered_set<int> new_beams;
        auto split_poss = find_split(mat[i]);
        if (split_poss.empty()) continue;
        for (auto p : prev_beams) {
            if (split_poss.count(p)) {
                cnt++;
                if (p - 1 >= 0) new_beams.insert(p - 1);
                if (p + 1 < C) new_beams.insert(p + 1);
            } else {
                new_beams.insert(p);
            }
        }
        prev_beams = new_beams;
    }    

    cout << cnt << endl;
}

void soln2() {
    vector<string> mat = read_lines("./inputs/day7.txt");
    int R = mat.size();
    int C = mat[0].size();

    vector<long long> countPaths(C, 0L);
    int start_pos = mat[0].find("S");
    countPaths[start_pos] = 1L;
    
    for (int i = 1; i < R; i++) {
        auto split_poss = find_split(mat[i]);
        if (split_poss.empty()) continue;
        vector<long long> newPaths(C, 0L);

        for (int p = 0; p < C; p++) {
            if (countPaths[p] > 0L) {
                if (split_poss.count(p)) {
                    if (p - 1 >= 0) newPaths[p - 1] += countPaths[p];
                    if (p + 1 < C) newPaths[p + 1] += countPaths[p];
                } else {
                    newPaths[p] += countPaths[p];
                }
            }    
        }

        countPaths = newPaths;
    }

    cout << accumulate(countPaths.begin(), countPaths.end(), 0L) << endl;
}

int main() {
    soln1();
    soln2();
    return 0;
}