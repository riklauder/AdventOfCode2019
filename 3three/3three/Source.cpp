/**/
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
#include <utility>
#include <functional>
#include <set>

struct Point {
    Point() : x(0), y(0) {}
    Point(int newX, int newY) : x(newX), y(newY) {}
	int x, y;
};


inline bool operator==(const Point& p1, const Point& p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

inline bool operator!=(const Point& p1, const Point& p2) { return !(p1 == p2); }

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

/*Directions for distance
                    U   D   L  R*/
static int dx[] = { 0,  0, -1, 1 };
static int dy[] = { 1, -1,  0, 0 };

void getData(std::vector<int>& d) {
	std::string s;
	std::ifstream file("input.txt");
	while (getline(file, s)) {
		int dd;
		std::stringstream dat(s);
		dat >> dd;
		d.push_back(dd);
	}
}

int dist(const Line& a, const Line& b, int n) {
	// Euclidian Distance
    //d = static_cast<int>(sqrt(xd * xd + yd * yd));
	int xd = (b.start.x - a.start.x);
	int yd = (b.start.y - a.start.y);
    // Manhattan distance
     return std::abs(xd)+abs(yd);
    // Chebyshev distance
    //d=max(abs(xd), abs(yd));
}

bool intersects(const Line& v, const Line& h) {
	int y = h.start.y;
	int x = v.start.x;
	int xub = std::max(h.start.x, h.end.x);
	int xlb = std::min(h.start.x, h.end.x);
	int yub = std::max(v.start.y, v.end.y);
	int ylb = std::min(v.start.y, v.end.y);
	return  x >= xlb && x <= xub &&
		y >= ylb && y <= yub;
}

void find_intersections(const std::vector<Line>& v, const std::vector<Line>& h,
                        std::vector<Point>& intersections) {
    for (Line s : v) {
        // get iteration interval
        int lb = std::min(s.start.y, s.end.y);
        int ub = std::max(s.start.y, s.end.y);
        // 1st (smallest) occurance in hor 
        int l = 0;
        int r = h.size() - 1;
        int m;
        while (l < r) {
            m = (l + r) / 2;
            if (h[m].val < lb) {
                l = m + 1;
            }
            else if (h[m].val >= lb) {
                r = m;
            }
        }
        // walk all horizontal lines within the interval
        for (int i = m; i < h.size(); i++) {
            if (h[i].val > ub)
                break;
            if (intersects(s, h[i])) {
                intersections.push_back({ s.start.x, h[i].start.y });
            }
        }
    }
}

int main() {
    std::vector<Line> a_hor;
    std::vector<Line> a_vert;
    std::vector<Line> b_hor;
    std::vector<Line> b_vert;

    Point last, current = { 0,0 };
    bool line_b = false;
    while 

}