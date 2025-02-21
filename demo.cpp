#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>

using namespace std;

enum eDir { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6 };

class cBall
{
    private:
        int x, y;
        int originalX, originalY;
        eDir direction;

    public:
        cBall(int posX, int posY)
        {
            originalX = posX;
            originalY = posY;
            x = posX;
            y = posY;
            direction = STOP;
        }

        void Reset()
        {
            x = originalX;
            y = originalY;
            direction = STOP;
        }

        void changeDirection(eDir d)
        {
            direction = d;
        }

        void randomDirection()
        {
            direction = (eDir)((rand() % 6) + 1);
        }
        inline int getX() { return x; }
        inline int getY() { return y; }
        inline eDir getDirection() { return direction; }
        
        void Move()
        {
            switch (direction)
            {
                case STOP:
                    break;
                case LEFT:
                    x--;
                    break;
                case RIGHT:
                    x++;
                    break;
                case UPLEFT:
                    x--; y--;
                    break;
                case DOWNLEFT:
                    x--; y++;
                    break;
                case UPRIGHT:
                    x++; y--;
                    break;
                case DOWNRIGHT:
                    x++; y++;
                    break;
                default:
                    break;
            }
        }
        friend ostream & operator<<(ostream & o, cBall c)
        {
            o << "Ball [" << c.x << "," << c.y << "][" << c.direction << "]";
            return o;
        }

};
class cPaddle
{
    private:
        int x, y;
        int originalX, originalY;

    public:
        cPaddle()
        {
            x = y = 0;
        }
        cPaddle(int posX, int posY) : cPaddle()
        {
            originalX = posX;
            originalY = posY;
            x = posX;
            y = posY;
        }

        inline void Reset() { x = originalX; y = originalY; }
        inline int getX() { return x; }
        inline int getY() { return y; }
        inline void moveUp() { y--; }
        inline void moveDown() { y++; }

        friend ostream & operator<<(ostream & o, cPaddle c)
        {
            o << "Paddle [" << c.x << "," << c.y << "]";
            return o;
        }
};
class cGameManager
{
    private: 
        int width, height;
        int score1, score2;
        char up1, down1, up2, down2;
        bool quit;
        cBall * ball;
        cPaddle * player1;
        cPaddle * player2;

    public:
        cGameManager(int w, int h)
        {
            srand(time(NULL));
            quit = false;
            up1 = 'w'; down1 = 's';
            up2 = 'i'; down2 = 'k';
            width = w; height = h;
            score1 = score2 = 0;
            ball = new cBall(w/2, h/2);
            player1 = new cPaddle(1, h/2 - 3);
            player2 = new cPaddle(w - 2, h/2 - 3);
        }

        ~cGameManager()
        {
            delete ball, player1, player2;
        }
        void ScoreUp(cPaddle * player)
        {
            if (player == player1)
                score1++;
            else if (player == player2)
                score2++;

            ball->Reset();
            player1->Reset();
            player2->Reset();
        }

        void Draw()
        {
            system("cls");
            for (int i = 0; i < width + 2; i++)
                cout << "\xB2";
            cout << endl;   


            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    int ballx = ball->getX();
                    int bally = ball->getY();
                    int player1x = player1->getX();
                    int player1y = player1->getY();
                    int player2x = player2->getX();
                    int player2y = player2->getY();





                    if (j == 0)
                        cout << "\xB2";
                    else if (j == width - 1)
                        cout << "#";
                    else if (j == ball->getX() && i == ball->getY())
                        cout << "O"; //ball
                    else if (j == player1->getX() && i >= player1->getY() && i < player1->getY() + 4)
                        cout << "|"; //player 1
                    else if (j == player2->getX() && i >= player2->getY() && i < player2->getY() + 4)
                        cout << "|"; //player 2
                    else
                        cout << " ";
                }
                cout << endl;
            }

            for (int i = 0; i < width; i++)
            {
                cout << "#";
            }
            cout << endl;

            cout << "Score 1: " << score1 << " Score 2: " << score2 << endl;
        }
        void Input()
        {
            ball->Move();

            int ballX = ball->getX();
            int ballY = ball->getY();
            int player1;

};


int main()
{
    cGameManager c(40, 20);
    c.Draw();








    // cPaddle p1(0, 0);
    // cPaddle p2(10, 0);
    // cout << p1 << endl;
    // cout << p2 << endl;
    // p1.moveUp();
    // p2.moveDown();
    // cout << p1 << endl;
    // cout << p2 << endl;








    // cBall c(0, 0);
    // cout << c << endl;
    // c.randomDirection();
    // cout << c << endl;
    // c.Move();
    // cout << c << endl;
    // c.randomDirection();
    // c.Move();
    // cout << c << endl;
    // c.randomDirection();
    // c.Move();
    // cout << c << endl;

    return 0;
};