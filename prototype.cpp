#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

class Point {
public:
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

class Ball {
public:
    Point position;
    Point direction;
    Ball(int x, int y) : position(x, y), direction(1, 1) {}

    void move() {
        position.x += direction.x;
        position.y += direction.y;
    }

    void bounceHorizontal() {
        direction.x = -direction.x;
    }

    void bounceVertical() {
        direction.y = -direction.y;
    }
};

class Paddle {
public:
    Point position;
    int length;
    Paddle(int x, int y, int length) : position(x, y), length(length) {}

    void moveUp() {
        if (position.y > 0) position.y--;
    }

    void moveDown(int maxHeight) {
        if (position.y + length < maxHeight) position.y++;
    }
};

void clearScreen() {
    system("cls");
}

void draw(Paddle &paddle, Ball &ball, int width, int height) {
    clearScreen();

    // Draw the game screen
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == ball.position.x && i == ball.position.y) {
                cout << "O";  // Ball
            } else if (j == paddle.position.x && i >= paddle.position.y && i < paddle.position.y + paddle.length) {
                cout << "|";  // Paddle
            } else {
                cout << " ";  // Empty space
            }
        }
        cout << endl;
    }
}

int main() {
    const int width = 40;
    const int height = 20;
    Paddle paddle(0, height / 2 - 2, 4);  // Paddle on the left side
    Ball ball(width / 2, height / 2);     // Ball in the center

    while (true) {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 'w') paddle.moveUp();
            if (ch == 's') paddle.moveDown(height);
        }

        ball.move();

        // Ball bounces off the top and bottom of the screen
        if (ball.position.y <= 0 || ball.position.y >= height - 1) {
            ball.bounceVertical();
        }

        // Ball bounces off the left side and checks for collision with the paddle
        if (ball.position.x <= 0) {
            if (ball.position.y >= paddle.position.y && ball.position.y < paddle.position.y + paddle.length) {
                ball.bounceHorizontal();
            } else {
                // Ball misses the paddle, reset position
                ball.position = Point(width / 2, height / 2);
                ball.direction = Point(1, 1);  // Ball goes back in the default direction
            }
        }

        // Ball bounces off the right side (optional, you can add scoring here)
        if (ball.position.x >= width - 1) {
            ball.bounceHorizontal();
        }

        draw(paddle, ball, width, height);
        Sleep(100);  // Control the game speed
    }

    return 0;
}
