#include "utils.hpp"
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
using namespace std;

vector<int> process_file()
{
    vector<int> out;

    auto lines = read_lines("inputs/day1.txt");

    for (auto s : lines) {
        int dir = s[0] == 'R' ? 1 : -1;
        int disp = stoi(s.substr(1));

        out.push_back(dir * disp);
    }

    return out;
}

void soln1() {
    auto movements = process_file();
    int start = 50, cnt = 0;
    for (auto mv : movements) {
        start = (start + mv) % 100; 
        if (start == 0) {
            cnt++;
        }
        if (start < 0) start += 100;
    }
    cout << cnt << endl;
    // return 0;
}

void soln2() {
    auto movements = process_file();
    int start = 50, cnt = 0;
    for (auto mv : movements) {
        if (mv > 0) {
            cnt += (start + mv) / 100;
            start = (start + mv) % 100;
        } else if (mv < 0) {
            if (start + mv <= 0) {
                cnt += start > 0 ? 1 : 0;
                int displacement = abs(mv) - start;
                cnt += (displacement) / 100;
            }
            start = (start + mv) % 100;
            if (start < 0) start += 100;
        }
    }
    cout << cnt << endl;
}

int main()
{
    soln1();
    soln2();
    return 0;
}