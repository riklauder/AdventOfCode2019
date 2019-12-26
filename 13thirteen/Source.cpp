#include "headers.h"
#include "intcomp.h"

struct Point {
    int x, y;
};
bool operator==(const Point a, const Point b) { return a.x == b.x && a.y == b.y; }
bool operator<(const Point a, const Point b) { return (a.x != b.x) ? (a.x < b.x) : (a.y < b.y); }


void update(const ic::IntcodeComputer& src, std::map<Point, long long>& display)
{
    for (size_t i = 0, endI = src.out.size(); i < endI; i += 3) {
        Point pos{ src.out[i], src.out[i + 1] };
        if (src.out[i + 2] == 2) {// 2 == a block
            display[pos] = src.out[i + 2];
        }
        else if (src.out[i + 2] == 4) { // 4 == the ball
            display.erase(pos);
        }
    }
}



int main() {
    ic::IntcodeComputer src;
    if (!src.load("input.txt")) {
        std::cout << stderr << "Could not open input file\n";
        return EXIT_FAILURE;
    }

    std::map<Point, long long> display;

    while (src.run()) {
        update(src, display);
    }
    update(src, display);
    std::cout << (unsigned int)display.size() << " block tiles are on the screen when the game exits" << std::endl;

}