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

static constexpr long long kTurnLeft = 0;
static constexpr long long kTurnRight = 1;

void print(const std::map<Point, char>& map, Point size)
{
    for (int y = 0; y < size.y; y++) {
        for (int x = 0; x < size.x; x++) {
            auto it = map.find(Point{ x, y });
            if (it != map.end()) {
                fputc(it->second, stdout);
            }
            else {
                fputc('.', stdout);
            }
        }
        fputc('\n', stdout);
    }
}

int main() {
    ic::IntcodeComputer prog;
    if (!prog.load("input.txt")) {
        std::cout << stderr << "Could not open input file\n";
        return EXIT_FAILURE;
    }


    prog.run();

    Point pos{ 0, 0 };
    Point size{ 0, 0 };
    std::map<Point, char> map;
    for (int64_t x : prog.out) {
        if (x == '\n') {
            size.x = std::max(pos.x, size.x);
            pos.x = 0;
            pos.y++;
        }
        else if (x == '#') {
            map[pos] = '#';
            pos.x++;
        }
        else {
            pos.x++;
        }
    }
    size.y = pos.y;

    int64_t result = 0;
    for (auto it : map) {
        pos = it.first;
        bool intersection = true;
        for (Point delta : Disc) {
            Point neighbor = pos + delta;
            if (map.count(neighbor) == 0) {
                intersection = false;
                break;
            }
        }
        if (intersection) {
            map[pos] = 'O';
            result += pos.x * pos.y;
        }
    }

    print(map, size);
    std::cout << "Rezult:" << result;
    
}