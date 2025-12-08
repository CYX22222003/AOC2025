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
#include <set>

using namespace std;

#define SQUARE(A) ((A) * (A))

class UnionFind {
    public:
    vector<int> parent;
    vector<long long> size;
    int length;
    
    UnionFind(int n) {
        length = n;
        size.resize(n, 1L);
        parent.resize(n);
        for(int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool connect(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    bool allConnected() {
        if (parent.empty()) throw runtime_error("what the hell!");
        int root0 = find(0);
        for (int i = 1; i < length; ++i) {
            if (find(i) != root0) return false;
        }
        return true;
    }
};

class Junction {
    public:
    long long x, y, z;

    static Junction fromStr(string& s) {
        Junction j;
        auto xs = split(s, ',');
        j.x = stoll(trim(xs[0]));
        j.y = stoll(trim(xs[1]));
        j.z = stoll(trim(xs[2]));
        return j;
    }

    static long long get_dist(const Junction& a, const Junction& b) {
        return SQUARE(a.x - b.x) + SQUARE(a.y - b.y) + SQUARE(a.z - b.z);
    }
};

std::ostream& operator<<(std::ostream& os, const Junction& n) {
    return os << "(" << n.x << ", " << n.y << ", " << n.z <<")";
}

vector<Junction> process_files() {
    vector<string> strs_xs = read_lines("./inputs/day8.txt");
    vector<Junction> j_xs;
    for (auto str : strs_xs) {
        j_xs.push_back(Junction::fromStr(str));
    }
    return j_xs;
}

multiset<pair<long long, pair<int, int>>> findTopClosest(const vector<Junction>& junctions, long long limit) {
    int n = (int)junctions.size();
    multiset<pair<long long, pair<int, int>>> pq;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            long long dist = Junction::get_dist(junctions[i], junctions[j]);
            if ((long long)pq.size() < limit) {
                pq.insert({dist, {i, j}});
            } else {
                auto largest = prev(pq.end());
                if (dist < largest->first) {
                    pq.erase(largest);   
                    pq.insert({dist, {i, j}});
                }
            }
        }
    }
    return pq;
}

UnionFind union_junctions(int size, const multiset<pair<long long, pair<int, int>>>& topClosest) {
    UnionFind uf(size);

    for (const auto& entry : topClosest) {
        int i = entry.second.first;
        int j = entry.second.second;
        uf.connect(i, j);
    }

    return uf;
}

long long multiplyTop3Sizes(UnionFind& uf) {
    unordered_set<int> seen;
    vector<long long> sizes;

    for (int i = 0; i < (int)uf.parent.size(); ++i) {
        int root = uf.find(i);
        if (seen.count(root)) continue;
        seen.insert(root);
        sizes.push_back(uf.size[root]);
    }

    sort(sizes.rbegin(), sizes.rend()); 

    long long product = 1;
    for (int i = 0; i < min(3, (int)sizes.size()); ++i)
        product *= sizes[i];

    return product;
}

void soln1() {
    long long limit = 1000, result = 0;
    auto junctions = process_files();
    auto topClosest = findTopClosest(junctions, limit);
    auto uf = union_junctions(junctions.size(), topClosest);
    result = multiplyTop3Sizes(uf);
    cout << result << endl;
}

void soln2() {
    auto junctions = process_files();
    long long limit = junctions.size();
    auto topClosest = findTopClosest(junctions, limit * limit);

    UnionFind uf(limit);
    int i = 0, j = 0;
    for (const auto& entry : topClosest) {
        i = entry.second.first;
        j = entry.second.second;
        // cout << i << " " << j << endl;
        // cout << junctions[i] << endl;
        // cout << junctions[j] << endl;
        uf.connect(i, j);
        if (uf.allConnected()) break;
    }
    // cout << junctions[i] << endl;
    // cout << junctions[j] << endl;
    cout << junctions[i].x * junctions[j].x << endl;
}

int main() {
    // display_list(process_files());
    soln1();
    soln2();
    return 0;
}
