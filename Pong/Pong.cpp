// Pong.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

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
        x--; y--;
        break;
    case ULEFT:
        x--; y++;
        break;
    case DRIGHT:
        x++; y--;
        break;
    case URIGHT:
        x++; y++;
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
int main()
{
    cBall c(0, 0);
    cout << c << endl;
    c.RandomDirection();
    cout << c << endl;
    c.Move();
    c.RandomDirection();
    cout << c << endl;
    c.Move();
    c.RandomDirection();
    cout << c << endl;
    c.Move();
    c.RandomDirection();
    cout << c << endl;

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
