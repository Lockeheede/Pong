// Pong.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <time.h>
#include <conio.h>

using namespace std;

enum eDir {
    STOP = 0, LEFT = 1, DLEFT = 2, ULEFT = 3, RIGHT = 4, DRIGHT = 5, URIGHT = 6
};

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
        x = posX; y = posY;
        direction = STOP;
    }

void Reset() 
{
    x = originalX; 
    y = originalY;
    direction = STOP;
}

void ChangeDirection(eDir d)
{
    direction = d;
}

void RandomDirection()
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
    case DLEFT:
        x--; y++;
        break;
    case ULEFT:
        x--; y--;
        break;
    case DRIGHT:
        x++; y++;
        break;
    case URIGHT:
        x++; y--;
        break;
    default:
        break;
    }
}

friend ostream& operator<<(ostream& o, cBall c) {
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
        x = posX;
        y = posY;
        originalX = posX;
        originalY = posY;
    }

inline void Reset() { x = originalX; y = originalY; }
inline int getX() { return x; }
inline int getY() { return y; }
inline void moveUp() { y--; }
inline void moveDown() { y++; }

friend ostream& operator<<(ostream& o, cPaddle c) {
    o << "Paddle [" << c.x << "," << c.y << "]";
    return o;
}
};

class cGameManager 
{
private:
    int width, height;
    int scoreP1, scoreP2;
    char upP1, downP1, upP2, downP2;
    bool quit;
    cBall* ball;
    cPaddle* player1;
    cPaddle* player2;
public:
    cGameManager(int w, int h)
    {
        srand(time(NULL));
        quit = false;
        upP1 = 'w'; upP2 = 'i';
        downP1 = 's'; downP2 = 'k';
        scoreP1 = scoreP2 = 0;
        width = w; height = h;
        ball = new cBall(w / 2, h / 2);
        player1 = new cPaddle(1, h / 2 - 3);
        player2 = new cPaddle(w-2, h / 2 - 3);
    }
    ~cGameManager() 
    {
        delete ball, player1, player2;
    }
    void ScoreUp(cPaddle * player)
    {
        if (player == player1) scoreP1++;
        else if (player == player2) scoreP2++;
        ball->Reset();
    }
    void Draw()//Render objects
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
                int player2x = player2->getX();
                int player1y = player1->getY();
                int player2y = player2->getY();

                if (j == 0)
                    cout << "\xB2";
                if (ballx == j && bally == i)
                    cout << "0";//Draw Ball
                else if (player1x == j && player1y == i)
                    cout << "\xDB";//Draw Player1
                else if (player2x == j && player2y == i)
                    cout << "\xDB";//Draw Player2

                else if (player1x == j && player1y + 1 == i)
                    cout << "\xDB";//Draw Player1
                else if (player1x == j && player1y + 2== i)
                    cout << "\xDB";//Draw Player1
                else if (player1x == j && player1y + 3 == i)
                    cout << "\xDB";//Draw Player1

                else if (player2x == j && player2y + 1 == i)
                    cout << "\xDB";//Draw Player1
                else if (player2x == j && player2y + 2 == i)
                    cout << "\xDB";//Draw Player1
                else if (player2x == j && player2y + 3 == i)
                    cout << "\xDB";//Draw Player1
                else
                    cout << " ";

                if (j == width - 1)
                    cout << "\xB2";
            }
            cout << endl;
        }

        for (int i = 0; i < width + 2; i++)
            cout << "\xB2";
        cout << endl;

        cout << "Player 1: " << scoreP1 << endl << "Player 2: " << scoreP2;
    }

    void Input()
    {
        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player1->getX();
        int player2x = player2->getX();
        int player1y = player1->getY();
        int player2y = player2->getY();
        ball->Move();
        if (_kbhit())
        {
            char current = _getch();
            if (current == upP1)
                if (player1y > 0)
                    player1->moveUp();
            if (current == upP2)
                if (player2y > 0)
                    player2->moveUp();

            if (current == downP1)
                if (player1y + 4 < height)
                    player1->moveDown();
            if (current == downP2)
                if (player2y + 4 < height)
                    player2->moveDown();

            if (ball->getDirection() == STOP)
                ball->RandomDirection();

            if (current == 'q')
                quit = true;
        }
    }

    void Logic()
    {
        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player1->getX();
        int player2x = player2->getX();
        int player1y = player1->getY();
        int player2y = player2->getY();

        //Ball to the Paddles
        for (int i = 0; i < 4; i++)
            if (ballx == player1x + 1)
                if (bally == player1y + i)
                    ball->ChangeDirection((eDir)(rand() % 3 + 4));

        for (int i = 0; i < 4; i++)
            if (ballx == player2x - 1)
                if (bally == player2y + i)
                    ball->ChangeDirection((eDir)(rand() % 3 + 1));

        //Ball to the Walls
        if (bally == height - 1)
            ball->ChangeDirection(ball->getDirection() == DRIGHT ? URIGHT : ULEFT);

        if (bally == 0)
            ball->ChangeDirection(ball->getDirection() == URIGHT ? DRIGHT : DLEFT);

        //Ball to The End (Scoring)
        if (ballx == width - 1) 
            ScoreUp(player1);
        if (ballx == 0)
            ScoreUp(player2);
    }

    void Run()
    {
        while (!quit)
        {
            Draw();
            Input();
            Logic();
        }
    }
};

int main()
{
    cGameManager c(40, 20);
    c.Run();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
