
#ifndef CARS_H_INCLUDED
#define CARS_H_INCLUDED

#include<windows.h>
void gotoxy(int x, int y);
void setcursor(bool visible, DWORD size);
void drawBorder();
void genEnemy(int ind);
void drawEnemy(int ind);
void eraseEnemy(int ind);
void resetEnemy(int ind);
void drawCar();
void eraseCar();
int collision();
void gameover();
void updateScore();
void instructions();
void play();
void car_controller();


#endif // CARS_H_INCLUDED
