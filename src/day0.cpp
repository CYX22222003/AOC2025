#include <iostream>
#include "utils.hpp"

using namespace std;

int main() {
    auto lines = read_lines("inputs/day0.txt");

    // --- Parse input ---
    // Example: convert lines to integers
    vector<int> nums;
    for (auto& s : lines) {
        if (!s.empty()) nums.push_back(stoi(s));
    }

    // --- Part 1 ---
    long long ans1 = nums[0];
    // write solution...

    // --- Part 2 ---
    long long ans2 = nums[0] + 1;
    // write solution...

    cout << "Part 1: " << ans1 << "\n";
    cout << "Part 2: " << ans2 << "\n";
}