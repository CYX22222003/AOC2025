#include "utils.hpp"
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <regex>
#include <string>
#include <climits>
using namespace std;

class Interval {
    private:
    long long l, r;

    friend class Node;
    friend class IntervalTree;

    public:
    Interval(long long lv, long long rv): l(lv), r(rv) {}
};

class Node {
    private:
    Interval it;
    long long max_end;
    Node *left, *right;

    friend class IntervalTree;

    public:
    Node(long long l, long long r) : it{l, r}, max_end(r), left(nullptr), right(nullptr) {}
};

class IntervalTree {

public:
    Node* root = nullptr;

    Node* insert(Node* node, long long l, long long r) {
        if (!node) return new Node(l, r);

        if (l < node->it.l)
            node->left = insert(node->left, l, r);
        else
            node->right = insert(node->right, l, r);

        node->max_end = max(node->max_end, r);
        return node;
    }

    void insert(long long l, long long r) {
        root = insert(root, l, r);
    }

    bool query_point(Node* node, long long x) {
        if (!node) return false;

        if (node->it.l <= x && x <= node->it.r) return true;

        if (node->left && node->left->max_end >= x)
            return query_point(node->left, x);

        return query_point(node->right, x);
    }

    bool query_point(long long x) {
        return query_point(root, x);
    }
};

vector<vector<string>> process_file() {
    vector<string> lines = read_lines("./inputs/day5.txt");
    vector<string> first;
    vector<string> cnd;
    vector<vector<string>> out;
    bool isFirst = true;
    for (auto l : lines) {
        if (l.size() == 0) {
            isFirst = false;
            continue;
        }

        if (isFirst) {
            first.push_back(l);
        } else {
            cnd.push_back(l);
        }
    }
    out.push_back(first);
    // display_list(first);
    out.push_back(cnd);
    // display_list(cnd);
    return out;
}

IntervalTree buildTreeFromXs(vector<string>& xs) {
    IntervalTree intTree;

    for (auto intv : xs) {
        vector<string> p = split(intv, '-');
        intTree.insert(stoll(p[0]), stoll(p[1]));
    }

    return intTree;
}

int checkIntervals(vector<string>& queries, IntervalTree& intTree) {
    int cnt = 0;
    for (auto q : queries) {
        if (intTree.query_point(stoll(q))) ++cnt;
    }
    return cnt;
}

void soln1() {
    auto res = process_file();
    auto treeXs = res[0];
    auto queryXs = res[1];
    IntervalTree tree = buildTreeFromXs(treeXs);
    cout << checkIntervals(queryXs, tree) << endl;
}


vector<vector<long long>> merge(vector<vector<long long>>& intervals) {
    vector<vector<long long>> merged;
    if (intervals.empty()) return merged;

    sort(intervals.begin(), intervals.end(),
            [](const vector<long long>& a, const vector<long long>& b) {
                return a[0] < b[0];
            });

    vector<long long> prev = intervals[0];
    int l = (int)intervals.size();
    for (int i = 1; i < l; ++i) {
        auto& interval = intervals[i];
        if (interval[0] <= prev[1]) {
            prev[1] = max(prev[1], interval[1]);
        } else {
            merged.push_back(prev);
            prev = interval;
        }
    }

    merged.push_back(prev);
    return merged;
}

void soln2() {
    auto res = process_file();
    auto treeXs = res[0];
    long long cnt = 0;
    vector<vector<long long>> intervals_ll;
    for (auto intv : treeXs) {
        vector<string> p = split(intv, '-');
        intervals_ll.push_back(vector<long long>{stoll(p[0]), stoll(p[1])});
    }

    vector<vector<long long>> mergedIntervals = merge(intervals_ll);

    for (auto i : mergedIntervals) {
        cnt += (i[1] - i[0] + 1);
    }
    cout << cnt << endl;
}

int main() {
    // process_file();
    soln1();
    soln2();
    return 0;
}
