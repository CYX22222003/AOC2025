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
#include <thread>
#include <mutex>
#include <vector>
using namespace std;

void soln1() {
    vector<string> str_xs = read_lines("./inputs/day9.txt");
    vector<pair<long long, long long>> cords;
    for (auto s : str_xs) {
        auto v_xs = split(s, ',');
        cords.push_back({stoll(trim(v_xs[0])), stoll(trim(v_xs[1]))});
    }

    long long max_area = 0LL;
    int n = (int) cords.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            max_area = max(max_area, abs(cords[i].first - cords[j].first + 1) * abs(cords[i].second - cords[j].second + 1));
        }
    } 

    cout << max_area << endl;
}

class Point {
public:
    long long x, y;
    Point(long long a, long long b) : x(a), y(b) {}
};

class Edge {
public:
    Point a, b;

    Edge(const Point& p1, const Point& p2) : a(p1), b(p2) {}

    bool isPointOnEdge(const Point& p) const {
        if (p.x < min(a.x, b.x) || p.x > max(a.x, b.x)) return false;
        if (p.y < min(a.y, b.y) || p.y > max(a.y, b.y)) return false;
        long long dx1 = b.x - a.x;
        long long dy1 = b.y - a.y;
        long long dx2 = p.x - a.x;
        long long dy2 = p.y - a.y;
        return dx1 * dy2 - dy1 * dx2 == 0;
    }

    bool isRayIntersect(const Point& p) const {
        if (isPointOnEdge(p)) return true;
        if (a.y == b.y) return false;
        if (p.y <= min(a.y, b.y) || p.y > max(a.y, b.y)) return false;
        long long x_intersect = a.x + (b.x - a.x) * (p.y - a.y) / (b.y - a.y);
        return p.x <= x_intersect;
    }
};

class Polygon {
public:
    vector<Edge> edges;

    Polygon() {}
    Polygon(const vector<Edge>& eds) : edges(eds) {}

    void add_edge(const Edge& e) { edges.push_back(e); }

    bool isInside(const Point& p) const {
        for (const auto& e : edges)
            if (e.isPointOnEdge(p)) return true;

        int count = 0;
        for (const auto& e : edges)
            if (e.isRayIntersect(p))
                count++;
        return count % 2 == 1;
    }

    bool isRectangleInside(const vector<Point>& rect) const {
        for (const auto& p : rect)
            if (!isInside(p)) return false;
        return true;
    }
};

vector<Point> buildRectangle(const Point& p1, const Point& p2) {
    long long minX = min(p1.x, p2.x);
    long long maxX = max(p1.x, p2.x);
    long long minY = min(p1.y, p2.y);
    long long maxY = max(p1.y, p2.y);

    vector<Point> rectPoints;

    // Bottom and top edges
    for (long long x = minX; x <= maxX; x++) {
        rectPoints.emplace_back(x, minY); // bottom
        if (minY != maxY)
            rectPoints.emplace_back(x, maxY); // top
    }

    // Left and right edges (excluding corners already added)
    for (long long y = minY + 1; y < maxY; y++) {
        rectPoints.emplace_back(minX, y); // left
        if (minX != maxX)
            rectPoints.emplace_back(maxX, y); // right
    }

    return rectPoints;
}

long long rectangleArea(const Point& p1, const Point& p2) {
    long long width = abs(p2.x - p1.x) + 1;
    long long height = abs(p2.y - p1.y) + 1;
    return width * height;
}

// void soln2() {
//     vector<string> str_xs = read_lines("./inputs/day9.txt");
//     vector<Point> points;
//     points.reserve(str_xs.size());
//     Polygon polygon;

//     for (const auto& s : str_xs) {
//         auto v_xs = split(s, ',');
//         points.emplace_back(stoll(trim(v_xs[0])), stoll(trim(v_xs[1])));
//     }

//     int n = points.size();
//     for (int i = 1; i < n; i++)
//         polygon.add_edge(Edge{points[i - 1], points[i]});
//     polygon.add_edge(Edge{points[n - 1], points[0]}); // close polygon

//     long long max_area = 0;
//     for (int i = 0; i < n; i++) {
//         for (int j = i + 1; j < n; j++) {
//             auto rect = buildRectangle(points[i], points[j]);
//             if (polygon.isRectangleInside(rect)) {
//                 max_area = max(max_area, rectangleArea(points[i], points[j]));
//             }
//         }
//     }

//     cout << max_area << endl;
// }

// Update solutions using multithreading

mutex mtx;

long long global_max = 0;

void worker(int start, int end, const vector<Point>& points, const Polygon& polygon) {
    long long local_max = 0;
    int n = points.size();
    for (int i = start; i < end; i++) {
        for (int j = i + 1; j < n; j++) {
            auto rect = buildRectangle(points[i], points[j]);
            if (polygon.isRectangleInside(rect)) {
                local_max = max(local_max, rectangleArea(points[i], points[j]));
            }
        }
    }
    lock_guard<mutex> lock(mtx);
    global_max = max(global_max, local_max);
}

void soln2() {
    vector<string> str_xs = read_lines("./inputs/day9.txt");
    vector<Point> points;
    points.reserve(str_xs.size());
    Polygon polygon;

    for (const auto& s : str_xs) {
        auto v_xs = split(s, ',');
        points.emplace_back(stoll(trim(v_xs[0])), stoll(trim(v_xs[1])));
    }

    int n = points.size();
    for (int i = 1; i < n; i++)
        polygon.add_edge(Edge{points[i - 1], points[i]});
    polygon.add_edge(Edge{points[n - 1], points[0]});

    int n_threads = thread::hardware_concurrency();
    vector<thread> threads;
    int block = (n + n_threads - 1) / n_threads;

    for (int t = 0; t < n_threads; t++) {
        int start = t * block;
        int end = min(start + block, n);
        threads.emplace_back(worker, start, end, cref(points), cref(polygon));
    }

    for (auto& th : threads) th.join();

    cout << global_max << endl;
}

int main() {
    // soln1();
    soln2();
    return 0;
}