#include "headers.h"
#include "intcomp.h"

constexpr long long kPaddle = 3;
constexpr long long kBall = 4;

struct Game {
    vh::IntcodeComputer src;
    long long ballx = 0;
    long long paddlex = 0;
    long long joystick = 0;
    long long score = 0;

    void update() {
        for (size_t i = 0, endI = src.out.size(); i < endI; i += 3) {
            if (src.out[i] == -1 && src.out[i + 1] == 0) {
                score = src.out[i + 2];
            }
            else if (src.out[i + 2] == kPaddle) {
                paddlex = src.out[i];
            }
            else if (src.out[i + 2] == kBall) {
                ballx = src.out[i];
            }
        }
        joystick = (paddlex < ballx) ? 1 : (paddlex > ballx) ? -1 : 0;
    }

    void play() {
        src.mem[0] = 2; // play for free, woohoo!
        while (src.run(joystick)) {
            update();
        }
        update();
    }
};


int main() {
    Game game;
    if (!game.src.load("input.txt")) {
        std::cout << stderr << "Could not open input file\n";
        return EXIT_FAILURE;
    }

    game.play();
    std::cout << "Final Score :" << game.score << std::endl;
}