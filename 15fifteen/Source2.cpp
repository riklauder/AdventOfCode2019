#include "headers.h"
#include "intcomp.h"


struct Point {
    long long x, y;
    Point& operator += (const Point a) { x += a.x; y += a.y; return *this; }
};
bool operator==(const Point a, const Point b) { return a.x == b.x && a.y == b.y; }
bool operator<(const Point a, const Point b) { return (a.x != b.x) ? (a.x < b.x) : (a.y < b.y); }
Point operator +(const Point a, const Point b) { return Point{ a.x + b.x, a.y + b.y }; }

constexpr Point Disc[] = {
  Point{  0, -1 }, // NORTH = 0 = 0b00
  Point{  0,  1 }, // SOUTH = 1 = 0b01
  Point{ -1,  0 }, // WEST  = 2 = 0b10
  Point{  1,  0 }, // EAST  = 3 = 0b11
};

static inline long long opposite(long long direction) {
    return direction ^ 1;
}

struct Data {
    ic::IntcodeComputer src;
    std::map<Point, int> depths;
    Point pos{ 0, 0 };
    Point target{ 0, 0 };

    void search() {
        int depth = 0;
        std::vector<int> directions;
        directions.reserve(1000);

        depths[pos] = 0;
        directions.push_back(-1);
        while (true) {
            int direction = ++directions.back();
            if (direction == 4) {
                directions.pop_back();
                if (directions.empty()) {
                    return;
                }

                int opp = opposite(directions.back());
                src.run(opp + 1);
                pos += Disc[opp];
                --depth;
                continue;
            }

            Point next = pos + Disc[direction];
            auto it = depths.find(next);
            if (it != depths.end() && it->second <= depth) {
                continue;
            }

            src.run(direction + 1);
            if (src.out[0] == 0) {
                depths[next] = -1;
                continue;
            }

            directions.push_back(-1);
            ++depth;
            depths[next] = depth;
            pos = next;
            if (src.out[0] == 2) {
                target = next;
            }
        }
    }

    int oxygenate() {
        std::map<Point, int> times;
        std::deque<std::pair<Point,int>> q;
        q.push_back(std::make_pair(target, 0));

        int maxTime = 0;
        while (!q.empty()) {
            std::pair<Point, int> tmp = q.front();
            q.pop_front();

            auto it = times.find(tmp.first);
            if (it != times.end()) {
                continue;
            }
            times[tmp.first] = tmp.second;
            maxTime = tmp.second;

            for (int i = 0; i < 4; i++) {
                if (depths[tmp.first + Disc[i]] == -1) {
                    continue;
                }
                q.push_back(std::make_pair(tmp.first + Disc[i], tmp.second + 1));
            }
        }
        return maxTime;
    }
};

int main() {
    Data data;
    if (!data.src.load("input.txt")) {
        std::cout << stderr << "Could not open input file\n";
        return EXIT_FAILURE;
    }

    data.search();
    std::cout << "shortest path to target of length:" << data.depths[data.target] << std::endl;
    std::cout << "target at pos x,y :" << data.target.x << "," << data.target.y << std::endl;
    int time = data.oxygenate();
    std::cout << time << " min to oxegenate entire area" << std::endl;

}