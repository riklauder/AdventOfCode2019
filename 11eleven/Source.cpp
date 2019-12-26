#include "headers.h"
#include "intcomp.h"


struct Point {
    int x, y;
};
Point operator + (const Point a, const Point b) { return Point{ a.x + b.x, a.y + b.y }; }
Point operator - (const Point a, const Point b) { return Point{ a.x - b.x, a.y - b.y }; }
Point operator / (const Point a, const int k) { return Point{ a.x / k, a.y / k }; }
bool operator==(const Point a, const Point b) { return a.x == b.x && a.y == b.y; }
bool operator<(const Point a, const Point b) { return (a.x != b.x) ? (a.x < b.x) : (a.y < b.y); }
Point min(Point a, Point b) { return Point{ std::min(a.x, b.x), std::min(a.y, b.y) }; }
Point max(Point a, Point b) { return Point{ std::max(a.x, b.x), std::max(a.y, b.y) }; }

static constexpr long long pBlack = 0;
static constexpr long long pWhite = 1;

static constexpr long long kTurnLeft = 0;
static constexpr long long kTurnRight = 1;


void print_grid(const std::map<Point, long long>& grid)
{
    Point lo{ 1 << 30, 1 << 30 };
    Point hi{ -(1 << 30), -(1 << 30) };
    for (auto it : grid) {
        Point pos = it.first;
        lo = min(lo, pos);
        hi = max(hi, pos);
    }
    char toP[] = { ' ', '#' };
    for (int y = lo.y; y <= hi.y; y++) {
        for (int x = lo.x; x <= hi.x; x++) {
            Point pos{ x, y };
            long long color = grid.count(pos) > 0 ? grid.at(pos) : pBlack;
            std::cout << toP[(color != pBlack)];
        }
        std::cout << std::endl;
    }
}

int main() {
    vh::IntcodeComputer src;
    if (!src.load("input.txt")) {
        std::cout << stderr << "Could not open input file\n";
        return EXIT_FAILURE;
    }
    
    std::map<Point, long long> grid;
 
    Point pos{ 0,0 };
    Point direction{ 0, -1 };//facing up inititally

    grid[pos] = pWhite;//for part 1 - remove this
    
    int result = 1;
    while (true) {
        long long input = (grid.count(pos) > 0) ? grid[pos] : pBlack;
        result = src.run(input);
        if (result == 0) {
            break;
        }
        grid[pos] = src.out[0];
        if (src.out[1] == kTurnLeft) {
            direction = Point{ direction.y, -direction.x };
        }
        else {
            direction = Point{ -direction.y, direction.x };
        }
        pos = pos + direction;
    }
    print_grid(grid);
    int gridSize = grid.size();
    std::cout << "Painted " << gridSize << " panels at least once" << std::endl;
    std::cout << std::endl;

    //std::cout << "part 2 input 2" << std::endl;
    //std::vector<long long> dt2 = maindata;
    //long long part2 = process(dt2, 2);
    //std::cout << std::endl;

    //std::vector<long long> dt2 = maindata;
    //std::cout << "Intcode diagnostic code part 2: "<< process(dt2) << std::endl;

}
