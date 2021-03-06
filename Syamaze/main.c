#include <p24FJ64GB002.h>
#include <stdio.h>
#include <stdlib.h>
#include "DogM.h"

// Defining player perspective directions
#define NORTH 1
#define EAST 2
#define SOUTH 4
#define WEST 8

void turnLeft();
void turnRight();
void forward();
void drawArea(unsigned int x, unsigned int y, unsigned int length, unsigned int height);
void drawLine(unsigned int xA, unsigned int yA, unsigned int xB, unsigned int yB, unsigned int style);
void delayMs(unsigned int time);

unsigned char direction = 1;
unsigned int userX = 1;
unsigned int userY = 1;

/*
 * This is a map of the maze
 * 0 = walkable
 * 1 = wall
 * 2 = starting point
 * 3 = ending point
 */

int maze [10][10] = {
    { 1, 3, 1, 1, 1, 1, 1, 1, 1, 1},
    { 1, 0, 1, 0, 1, 0, 0, 0, 1, 1},
    { 1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    { 1, 1, 0, 0, 1, 1, 1, 1, 0, 1},
    { 1, 0, 1, 0, 0, 0, 0, 0, 1, 1},
    { 1, 0, 0, 1, 1, 0, 1, 0, 1, 1},
    { 1, 1, 0, 0, 0, 1, 0, 0, 0, 1},
    { 1, 1, 1, 0, 1, 1, 0, 1, 1, 1},
    { 1, 2, 0, 0, 0, 0, 0, 0, 0, 1},
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

void forward() {
    if (direction == NORTH) {
        if (maze[userY + 1][userX] == 0) {
            userY++;
        } else {
            //wall
        }
    } else if (direction == SOUTH) {
        if (maze[userY - 1][userX] == 0) {
            userY--;
        } else {
            //wall
        }
    } else if (direction == EAST) {
        if (maze[userY][userX + 1] == 0) {
            userX++;
        } else {
            //wall
        }
    } else if (direction == WEST) {
        if (maze[userY][userX - 1] == 0) {
            userX--;
        } else {
            //wall
        }
    } else {
        // error ofzo?
    }
}

// The following methods perform bit rotations on the players direction

void turnRight() {
    if (direction >= 1 && direction <= 4) {
        direction = direction << 1;
    } else {
        // reset direction to allow wrap-around
        direction = 1;
    }
}

void turnLeft() {
    if (direction >= 2 && direction <= 8) {
        direction = direction >> 1;
    } else {
        // reset direction to allow wrap-around
        direction = 8;
    }
}

/*
 lastButtonChanged is modified on a interrup basis
 The function doing ths is called _CNInterrupt(void)
 and is defined in file interrupts. This funtion is called
 on a pin level change detection.
 */

int lastButtonChanged = 0;

// This is a stupid delay function, it is NOT very precise

void delayMs(unsigned int time) {
    unsigned int i, j;
    for (i = 0; i <= time; i++) {
        asm("nop");
        for (j = 0; j <= 1140; j++) //1ms
        {
            asm("nop");
            asm("nop");
        }
    }
}

/**
 * drawLine
 * this function's style parameter takes 1 for dotted lines and 0 for regular lines
 * @param xA
 * @param yA
 * @param xB
 * @param yB
 * @param style
 */
void drawLine(unsigned int xA, unsigned int yA, unsigned int xB, unsigned int yB, unsigned int style) {
    int dX = xB - xA;
    int dY = yB - yA;
    int alpha = dX / dY;

    unsigned int i;
    for (i = 0; i < dY; i++) {
        int yP = yA + i;
        int xP = xA + (i * alpha);
        int xP2 = xA + ((i + 1) * alpha);

        if (style == 1) {
            setPixel(xP, yP);
        } else {
            while (xP < xP2) {
                setPixel(xP, yP);
                xP++;
            }
        }
    }
}

/**
 * drawArea
 * @param x
 * @param y
 * @param length
 * @param hight
 */
void drawArea(unsigned int x, unsigned int y, unsigned int length, unsigned int height) {
    int i;
    int j;
    for (i = 0; i < height; ++i) {
        for (j = 0; j < length; ++j) {
            setPixel((x + j), (y + i));
        }
    }
}

/**
 * startMenu
 */
void startMenu() {
    drawArea(0, 0, 128, 22);

    drawArea(0, 22, 34, 1);
    drawArea(0, 23, 33, 1);
    drawArea(0, 24, 32, 2);
    setPixel(33, 25);
    drawArea(0, 26, 34, 3);
    drawArea(0, 29, 33, 1);
    drawArea(0, 30, 34, 1);
    drawArea(0, 31, 33, 8);
    drawArea(0, 39, 34, 1);
    drawArea(0, 40, 35, 1);
    drawArea(0, 41, 37, 1);
    drawArea(0, 42, 39, 7);
    drawArea(0, 49, 38, 1);
    drawArea(0, 50, 37, 1);
    drawArea(0, 51, 35, 1);
    drawArea(0, 52, 34, 1);
    drawArea(0, 53, 33, 1);
    drawArea(0, 54, 32, 1);
    drawArea(0, 55, 31, 2);
    drawArea(0, 57, 30, 7);

    drawArea(36, 22, 55, 1);
    drawArea(37, 23, 53, 1);
    drawArea(38, 24, 51, 1);
    drawArea(39, 25, 49, 1);
    drawArea(40, 26, 47, 1);
    drawArea(41, 27, 45, 1);
    drawArea(42, 28, 43, 1);
    drawArea(43, 29, 41, 2);
    drawArea(44, 31, 39, 1);
    drawArea(45, 32, 39, 1);
    drawArea(46, 33, 37, 1);
    drawArea(47, 34, 11, 1);
    drawArea(47, 35, 7, 1);
    drawArea(48, 36, 5, 1);
    drawArea(49, 37, 4, 2);
    drawArea(50, 39, 2, 1);
    drawArea(49, 40, 3, 1);
    drawArea(45, 41, 7, 1);
    drawArea(42, 42, 9, 1);
    drawArea(39, 43, 11, 1);
    drawArea(39, 44, 8, 1);
    drawArea(39, 45, 5, 1);
    drawArea(39, 46, 3, 1);
    setPixel(39, 47);

    drawArea(69, 34, 14, 1);
    drawArea(74, 35, 9, 1);
    drawArea(74, 36, 10, 1);
    drawArea(74, 37, 4, 2);
    drawArea(74, 39, 3, 1);
    drawArea(79, 37, 4, 1);
    drawArea(79, 38, 5, 1);
    drawArea(79, 39, 6, 1);
    drawArea(75, 40, 11, 1);
    drawArea(75, 41, 12, 1);
    drawArea(76, 42, 10, 1);
    setPixel(88, 42);
    drawArea(77, 43, 13, 1);
    drawArea(80, 44, 9, 1);
    drawArea(83, 45, 7, 1);
    drawArea(85, 46, 6, 1);
    drawArea(87, 47, 5, 1);
    drawArea(88, 48, 6, 1);
    drawArea(89, 49, 6, 1);
    drawArea(90, 50, 5, 1);
    drawArea(92, 51, 3, 1);
    drawArea(93, 52, 2, 1);

    drawArea(93, 22, 35, 1);
    drawArea(94, 23, 34, 1);
    drawArea(95, 24, 33, 3);
    drawArea(96, 27, 32, 8);
    drawArea(97, 35, 31, 6);
    drawArea(96, 41, 32, 6);
    drawArea(95, 47, 33, 7);
    drawArea(96, 54, 32, 10);

    drawArea(60, 42, 9, 1);
    drawArea(57, 43, 14, 1);
    drawArea(56, 44, 16, 1);
    drawArea(55, 45, 19, 2);
    drawArea(56, 47, 18, 2);
    drawArea(56, 49, 17, 1);
    drawArea(45, 50, 4, 1);
    drawArea(57, 50, 15, 1);
    drawArea(80, 50, 4, 1);
    drawArea(42, 51, 4, 1);
    drawArea(48, 51, 4, 1);
    drawArea(58, 51, 13, 1);
    drawArea(77, 51, 10, 1);
    drawArea(41, 52, 4, 1);
    drawArea(47, 52, 6, 1);
    drawArea(58, 52, 13, 1);
    drawArea(76, 52, 13, 1);
    drawArea(39, 53, 6, 1);
    drawArea(46, 53, 8, 1);
    drawArea(59, 53, 12, 1);
    drawArea(75, 53, 15, 1);
    setPixel(39, 54);
    drawArea(42, 54, 2, 1);
    drawArea(46, 54, 9, 1);
    drawArea(59, 54, 11, 1);
    drawArea(74, 54, 2, 1);
    drawArea(77, 54, 10, 1);
    setPixel(89, 54);
    drawArea(42, 55, 2, 1);
    drawArea(45, 55, 11, 1);
    drawArea(59, 55, 11, 1);
    drawArea(73, 55, 2, 1);
    drawArea(77, 55, 7, 1);
    drawArea(85, 55, 2, 1);
    drawArea(42, 56, 2, 1);
    drawArea(46, 56, 7, 1);
    drawArea(54, 56, 2, 1);
    drawArea(59, 56, 11, 1);
    drawArea(73, 56, 2, 1);
    drawArea(77, 56, 7, 1);
    drawArea(85, 56, 2, 1);
    drawArea(43, 57, 1, 1);
    drawArea(46, 57, 6, 1);
    drawArea(53, 57, 4, 1);
    drawArea(59, 57, 11, 1);
    drawArea(73, 57, 3, 1);
    drawArea(77, 57, 7, 1);
    drawArea(85, 57, 2, 1);
    drawArea(43, 58, 2, 1);
    drawArea(46, 58, 6, 1);
    setPixel(53, 58);
    drawArea(55, 58, 2, 1);
    drawArea(59, 58, 12, 1);
    drawArea(72, 58, 4, 1);
    drawArea(78, 58, 5, 1);
    drawArea(84, 58, 2, 1);
    setPixel(44, 59);
    drawArea(47, 59, 4, 1);
    drawArea(54, 59, 3, 1);
    drawArea(59, 59, 12, 1);
    drawArea(72, 59, 3, 1);
    drawArea(78, 59, 4, 1);
    setPixel(84, 59);
    drawArea(45, 60, 2, 1);
    drawArea(51, 60, 7, 1);
    drawArea(59, 60, 19, 1);
    setPixel(80, 60);
    setPixel(83, 60);
    drawArea(46, 61, 37, 1);
    drawArea(55, 62, 19, 2);
}

/**
 * main
 * @return
 */
int main(void) {
    // Init ap set all ports to digital and enables the int on pin change 
    // needed for the buttons/
    InitApp();

    // Set up the hardware of the display
    mdog_Init(0x81, 0x19);

    clearDisplay();

    // Initscreen clears a internal bitmap used
    // in drawScreen to send out to the display
    initScreen();

    // Set both led's of
    LATBbits.LATB14 = LATBbits.LATB15 = 0;

    while (1) {
        // Splash screen
        if (lastButtonChanged == 0) {
        // startMenu();
        }
        if (lastButtonChanged == 1) {
            drawLine(0, 0, 129, 64, 1);
            drawLine(127, 0, -2, 64, 1);
        }
        if (lastButtonChanged == 2) {
        }
        if (lastButtonChanged == 3) {
        }
        if (lastButtonChanged == 4) {
        }
        delayMs(250);
        drawScreen(dogmScreen, 8, 128);
    };
}
