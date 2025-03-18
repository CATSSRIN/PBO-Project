#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>

using namespace std;

enum eDir {STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT =3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6};

class cEntity {
protected:
    int x, y;
    int originalX, originalY;
public:
    cEntity(int posX, int posY) {
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
    }
    void Reset() {
        x = originalX;
        y = originalY;
    }
    inline int getX() { return x; }
    inline int getY() { return y; }
};

//inheritance
class cBall : public cEntity {
private:
    eDir direction;
public:
    cBall(int posX, int posY) : cEntity(posX, posY) {
        direction = STOP;
    }
    void changeDirection(eDir d) { direction = d; }
    void randomDirection() { direction = (eDir)((rand() % 6) + 1); }
    inline eDir getDirection() { return direction; }
    void Move() {
        switch (direction) {
            case STOP: break;
            case LEFT: x--; break;
            case RIGHT: x++; break;
            case UPLEFT: x--; y--; break;
            case DOWNLEFT: x--; y++; break;
            case UPRIGHT: x++; y--; break;
            case DOWNRIGHT: x++; y++; break;
        }
    }
};

//inheritance
class cPaddle : public cEntity {
public:
    cPaddle(int posX, int posY) : cEntity(posX, posY) {}
    void moveUp() { y--; }
    void moveDown() { y++; }
};

class cGameManager {
    private:
        int width, height;
        int score1, score2;
        char up1, down1, up2, down2;
        bool quit;
        bool gameStarted; // Flag to indicate if the game has started
        cBall* ball;
        cPaddle* player1;
        cPaddle* player2;
    public:
        cGameManager(int w, int h) {
            srand(time(NULL));
            quit = false;
            gameStarted = false; // Initialize the flag to false
            up1 = 'w'; down1 = 's';
            up2 = 'i'; down2 = 'k';
            score1 = score2 = 0;
            width = w; height = h;
            ball = new cBall(w/2, h/2);
            player1 = new cPaddle(1, h/2 - 3);
            player2 = new cPaddle(w - 2, h/2 - 3);
        }
    ~cGameManager() {
        delete ball;
        delete player1;
        delete player2;
    }
    void ScoreUp(cPaddle* player) {
        if (player == player1) score1++;
        else if (player == player2) score2++;
        ball->Reset();
        player1->Reset();
        player2->Reset();
    }
    void Draw() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD cursorPosition = {0, 0};
        SetConsoleCursorPosition(hConsole, cursorPosition);

        for (int i = 0; i < width + 2; i++) cout << "\xB2";
        cout << endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0) cout << "\xB2";
                if (ball->getX() == j && ball->getY() == i) cout << "o";
                else if (player1->getX() == j && (i >= player1->getY() && i < player1->getY() + 4)) cout << "\xDB";
                else if (player2->getX() == j && (i >= player2->getY() && i < player2->getY() + 4)) cout << "\xDB";
                else cout << " ";
                if (j == width - 1) cout << "\xB2";
            }
            cout << endl;
        }
        for (int i = 0; i < width + 2; i++) cout << "\xB2";
        cout << endl;
        cout << "Score 1: " << score1 << "  Score 2: " << score2 << endl;
    }
    void Input() {
        if (_kbhit()) {
            char current = _getch();
            if (current == up1 && player1->getY() > 0) player1->moveUp();
            if (current == down1 && player1->getY() + 4 < height) player1->moveDown();
            if (current == up2 && player2->getY() > 0) player2->moveUp();
            if (current == down2 && player2->getY() + 4 < height) player2->moveDown();
            if (ball->getDirection() == STOP) ball->randomDirection();
            if (current == 'q') quit = true;
            if (!gameStarted) {
                gameStarted = true; // Set the flag to true when the game starts
                ball->randomDirection(); // Start the ball movement
            }
        }
    }

    void Logic() {
        if (gameStarted) { // Only move the ball if the game has started
            Sleep(50);

            // Ball collision with walls
            if (ball->getY() == height - 1 || ball->getY() == 0) {
                ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : (ball->getDirection() == DOWNLEFT ? UPLEFT : (ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT)));
            }

            // Ball collision with paddles
            if (ball->getX() == player1->getX() + 1) {
                if (ball->getY() >= player1->getY() && ball->getY() <= player1->getY() + 3) {
                    ball->changeDirection((eDir)((rand() % 3) + 4)); // Randomize direction to RIGHT, UPRIGHT, or DOWNRIGHT
                }
            }
            if (ball->getX() == player2->getX() - 1) {
                if (ball->getY() >= player2->getY() && ball->getY() <= player2->getY() + 3) {
                    ball->changeDirection((eDir)((rand() % 3) + 1)); // Randomize direction to LEFT, UPLEFT, or DOWNLEFT
                }
            }

            // Ball out of bounds
            if (ball->getX() == width - 1) ScoreUp(player1);
            if (ball->getX() == 0) ScoreUp(player2);

            ball->Move(); // Move the ball
        }
    }
    
    void Run() {
        while (!quit) {
            Draw();
            Input();
            Logic();
        }
    }
};

int main() {
    cGameManager c(40, 20);
    c.Run();
    return 0;
}
