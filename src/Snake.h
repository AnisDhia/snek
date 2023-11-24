//
// Created by Anis on 11/23/2023.
//

#ifndef SNEK_SNAKE_H
#define SNEK_SNAKE_H

// snake food
typedef struct {
    int x;
    int y;
} Food;


class Snake {
public:
    Snake(
            int x = 0,
            int y = 0,
            int direction = 3,
            int speed = 10
    );

    ~Snake();

    void update(int screenWidth, int screenHeight);

    void render();

    void changeDirection(int dir);

    void addTail();

    int getX() { return x; }

    int getY() { return y; }

    int getDirection() { return direction; }

    int getSpeed() { return speed; }

    int getNTail() { return nTail; }

    int getTailX(int i) { return tailX[i]; }

    int getTailY(int i) { return tailY[i]; }

    bool isDead() { return !isAlive; }

    void reset() {
        x = 0;
        y = 0;
        direction = 0;
        nTail = 0;
        isAlive = true;
    }

    void Die() {
        isAlive = false;
        nTail = 0;
    }

private:
    bool isAlive = true;
    int x, y;
    int direction; // 0 - up, 1 - right, 2 - down, 3 - left
    int speed;
    int tailX[1000], tailY[1000];
    int nTail = 0;
};


#endif //SNEK_SNAKE_H
