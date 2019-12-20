#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <limits>
#include <numeric>	
#include <iterator>
#include <string>
#include <map>
#include <set>
#include <utility>
#include <functional>
#include <set>


struct Point {
    Point() : x(0), y(0) {}
    Point(int newX, int newY) : x(newX), y(newY) {}

    int x;
    int y;
};

inline bool operator==(const Point& p1, const Point& p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

inline bool operator!=(const Point& p1, const Point& p2) { return !(p1 == p2); }

// Segments are horizontal or vertical segments between two points.
// To ease intersection checks, ordered intervals of x and y coordinates are precomputed.
struct Segment {
    Segment(const Point& a, const Point& b) {
        p1 = a;
        p2 = b;
        xMin = std::min(p1.x, p2.x);
        xMax = std::max(p1.x, p2.x);
        yMin = std::min(p1.y, p2.y);
        yMax = std::max(p1.y, p2.y);
    }

    Point p1;
    Point p2;
    int xMin;
    int xMax;
    int yMin;
    int yMax;
};

// Check if two segments intersect. Returns true if segments intersect. If they
// do, intersection will be modified with the intersection if non-null.
bool intersects(const Segment& s1, const Segment& s2, Point* intersection) {
    if ((s1.xMin >= s2.xMin && s1.xMin <= s2.xMax) &&
        (s2.yMin >= s1.yMin && s2.yMin <= s1.yMax)) {
        if (intersection) {
            intersection->x = s1.xMin;
            intersection->y = s2.yMin;
        }
        return true;
    }
    else if ((s2.xMin >= s1.xMin && s2.xMin <= s1.xMax) &&
        (s1.yMin >= s2.yMin && s1.yMin <= s2.yMax)) {
        if (intersection) {
            intersection->x = s2.xMin;
            intersection->y = s1.yMin;
        }
        return true;
    }
    return false;
};

int manhattanDist(const Point& a, const Point& b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

std::vector<Segment> parseWire(std::istream& in) {
    std::vector<Segment> wire;

    // Wires by definition start at the origin
    Point currPoint;
    Point newPoint;

    for (char direction; in >> direction;) {
        int n;
        std::cin >> n;

        if (std::cin.peek() == ',') {
            std::cin.ignore();
        }

        newPoint = currPoint;
        switch (direction) {
        case 'U':
            newPoint.y += n;
            break;
        case 'D':
            newPoint.y -= n;
            break;
        case 'L':
            newPoint.x -= n;
            break;
        case 'R':
            newPoint.x += n;
            break;
        default:
            continue;
        }

        wire.emplace_back(currPoint, newPoint);
        currPoint = newPoint;

        if (std::cin.peek() == '\n' || std::cin.peek() == EOF) {
            std::cin.ignore();
            break;
        }
    }
    return wire;
}

int main() {
    std::vector<Segment> wireOne = parseWire(std::cin);
    std::vector<Segment> wireTwo = parseWire(std::cin);

    const Point ORIGIN(0, 0);

    ////////////////////////////////////////////////////////////
    // PART ONE
    ////////////////////////////////////////////////////////////
    int minDist = std::numeric_limits<int>::max();

    ////////////////////////////////////////////////////////////
    // PART TWO
    ////////////////////////////////////////////////////////////
    int minDelay = std::numeric_limits<int>::max();

    Point intersection;

    int oneDist = 0;
    for (const auto& i : wireOne) {
        int twoDist = 0;
        for (const auto& j : wireTwo) {
            if (intersects(i, j, &intersection) && intersection != ORIGIN) {
                minDelay = std::min(minDelay, (oneDist + twoDist +
                    manhattanDist(intersection, i.p1) +
                    manhattanDist(intersection, j.p1)));
                minDist = std::min(minDist, manhattanDist(intersection, ORIGIN));
            }
            twoDist += manhattanDist(j.p1, j.p2);
        }
        oneDist += manhattanDist(i.p1, i.p2);
    }

    std::cout << minDist << std::endl;
    std::cout << minDelay << std::endl;

    return 0;
}/*35038*/