#include "cars.h"
#include<iostream>
#include<conio.h>
#include<dos.h>
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 90 //output console width
#define SCREEN_HEIGHT 26  //output console height
#define WIN_WIDTH 70 //game screen

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); //geiing contol on output screen
COORD CursorPosition; //coordinates structure

int enemyY[3];
int enemyX[3];
int enemyFlag[3]; //setted only 0th index
char car[4][4] = { ' ','±','±',' ',
					'±','±','±','±',
					' ','±','±',' ',
					'±','±','±','±' }; //out car structure

int carPos = WIN_WIDTH/2;
int score = 0;
int reduction_factor=100; //for level increase
int movement_factor=4;


void gotoxy(int x, int y){ //getting to particular co-ordinate
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition); // 1 to show cursor and 0 to hide.
}
void setcursor(bool visible, DWORD size) { //dword-double word
	if(size == 0)
		size = 20;

	CONSOLE_CURSOR_INFO lpCursor; //the percentage of character cell that is filled by cursor
	lpCursor.bVisible = visible; //setting to true
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor); //setting the characteristics of lpcursor to out console screen
}
void drawBorder(){
	for(int i=0; i<SCREEN_HEIGHT; i++){ //row iteration
		for(int j=0; j<17; j++){ //col iteration ***win_width=70***
			gotoxy(0+j,i); cout<<"*"; //putting in first row //x is changing y is stable
			gotoxy(WIN_WIDTH-j,i); cout<<"*"; //putting in first row from last
		}
	}
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(SCREEN_WIDTH,i); cout<<"|"; //putting in final row //dividing screen for game and score tab
	}

	for(int i=0;i<100;i++){
        gotoxy(SCREEN_WIDTH+i,SCREEN_HEIGHT); cout<<"_"; //putting in final row only last half.
	}
}
void genEnemy(int ind){//enemyX is enemy x co-ord value.
	enemyX[ind] = 17 + rand()%(33); //y 17 is check above function inner loop //generating enemies randomly //enemyX has size 3 //17+anything number b/w 0 to 33
}
void drawEnemy(int ind){
	if( enemyFlag[ind] == true ){ //if enemyflag array of particular index is true
		gotoxy(enemyX[ind], enemyY[ind]);   cout<<"****";
		gotoxy(enemyX[ind], enemyY[ind]+1); cout<<" ** ";
		gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"****";
		gotoxy(enemyX[ind], enemyY[ind]+3); cout<<" ** ";
	} //drawing put enemy there of four rows
}
void eraseEnemy(int ind){
	if( enemyFlag[ind] == true ){
		gotoxy(enemyX[ind], enemyY[ind]); cout<<"    ";
		gotoxy(enemyX[ind], enemyY[ind]+1); cout<<"    ";
		gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"    ";
		gotoxy(enemyX[ind], enemyY[ind]+3); cout<<"    ";
	}//clearing out that enemy
}
void resetEnemy(int ind){ //reseting means erasing and creating new
	eraseEnemy(ind); //erased
	enemyY[ind] = 1; //making true in y co-ord
	genEnemy(ind); //created //drawn??
}
void drawCar(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){ //4 of 4
			gotoxy(j+carPos, i+22); //taking the console there //y range 22-25
			cout<<car[i][j]; //and printing appropriate symbol
		}
	}
}
void eraseCar(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+carPos, i+22); cout<<" "; //cleared the car
		}
	}
}
int collision(){ //check for collision
	if( enemyY[0]+4 >= 23 ){ //if enemy on near to our car row line
		if( enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9  ){ //if range is b/w 0 to 8 (4 is enemy car size) (8 is since add of enemy+ our car size)
			return 1; //can hit on left or on right
		}
	}

	return 0;
}
void gameover(){
	system("cls");
	cout<<endl;
	cout<<"\t\t--------------------------"<<endl;
	cout<<"\t\t-------- Game Over -------"<<endl;
	cout<<"\t\t--------------------------"<<endl<<endl;
	cout<<"\t\tPress any key to go back to menu.";
	getch();
}
void updateScore(){
	gotoxy(WIN_WIDTH + 7, 5);cout<<"Score: "<<score<<endl; //updating the score
}
void instructions(){ //providing instructions

	system("cls");
	cout<<"Instructions";
	cout<<"\n----------------";
	cout<<"\n Avoid Cars by moving left or right. ";
	cout<<"\n\n Press 'a' to move left";
	cout<<"\n Press 'd' to move right";
	cout<<"\n Press 'escape' to exit";
	cout<<"\n\nPress any key to go back to menu";
	getch();
}
void play(){ //main handler function
	carPos = -1 + WIN_WIDTH/2; //initial car position
	score = 0; //initial score
	enemyFlag[0] = 1; //enemy at 0th index
	enemyFlag[1] = 0; //enemy not at 1th index //just to get enemies in flow
	enemyY[0] = enemyY[1] = 1; //makinh index 0's y-coord of enemy to true //since they start coming from topmost

	system("cls");
	drawBorder(); //drawing border
	updateScore(); //providing score tab
	genEnemy(0); //generating enemy at index 0 //generating is just providing x co-ordinate
	genEnemy(1); //generating enemy at index 1 //generating is just providing x co-ordinate

	//just printing
	gotoxy(WIN_WIDTH + 25, 2);cout<<"Car Game";
	gotoxy(WIN_WIDTH + 26, 4);cout<<"----------";
	gotoxy(WIN_WIDTH + 26, 6);cout<<"----------";
	gotoxy(WIN_WIDTH + 27, 12);cout<<"Control ";
	gotoxy(WIN_WIDTH + 27, 13);cout<<"-------- ";
	gotoxy(WIN_WIDTH + 25, 14);cout<<" A Key - Left";
	gotoxy(WIN_WIDTH + 25, 15);cout<<" D Key - Right";

	gotoxy(18, 5);cout<<"Press any key to start";
	getch();
	gotoxy(18, 5);cout<<"                      ";

	while(1){ //always running thread for game
		if(kbhit()){ //if keyboard hit
			char ch = getch();
			/*if(score%10==0 && score!=0)
                movement_factor=8;*/


			if( ch=='a' || ch=='A' ){ //left movement
				if( carPos > 18 )
					carPos -= movement_factor;
			}
			if( ch=='d' || ch=='D' ){ //right movement
				if( carPos < 50 )
					carPos += movement_factor;
			}
			if(ch==27){ //esc
				break;
			}

			/*if(score%5==0 && score!=0 && score%10!=0)
                movement_factor=4;*/
		}

		drawCar(); //drawing out out car
		drawEnemy(0); //drawing enemy at index 0 //only valid
		drawEnemy(1); //drawing enemy at index 1 //not valid since enemyflag is zero
        if( collision() == 1  ){ //checking for collision continuously
                gameover(); //should check for car collision in  the duration of enemy car creation and destroyation
                return;
        }

		Sleep(50); //controls speed of game
		eraseCar(); //i  moved the car to diff pos,so should delete the old one and draw new position modified car
		eraseEnemy(0); //clearing enemy car
		eraseEnemy(1);

		if( enemyY[0] == 10 ) //processed at index 0 now when 0th index enemy car at y-cord 10,generate starting enemyindex 1 car
			if( enemyFlag[1] == 0 )
				enemyFlag[1] = 1;

		if( enemyFlag[0] == 1 )
			enemyY[0] += 1; //moving enemy towards down to our car

		if( enemyFlag[1] == 1 )
			enemyY[1] += 1; //moving enemy towards down to our car


		if( enemyY[0] > SCREEN_HEIGHT-4 ){ //if enemy gone out of screen
			resetEnemy(0);
			score++;
			updateScore();
		}
		if( enemyY[1] > SCREEN_HEIGHT-4 ){ //if enemy gone out of screen
			resetEnemy(1);
			score++;
			updateScore();
		}

	}
}

void car_controller(){
    setcursor(0,0);
	srand( (unsigned)time(NULL));

	do{
		system("cls");
		gotoxy(10,5); cout<<" -------------------------- ";
		gotoxy(10,6); cout<<" |        Car Game        | ";
		gotoxy(10,7); cout<<" --------------------------";
		gotoxy(10,9); cout<<"1. Start Game";
		gotoxy(10,10); cout<<"2. Instructions";
		gotoxy(10,11); cout<<"3. Quit";
		gotoxy(10,13); cout<<"Select option: ";
		char op = getche();

		if( op=='1') play();
		else if( op=='2') instructions();
		else if( op=='3') exit(0);

	}while(1);
}
