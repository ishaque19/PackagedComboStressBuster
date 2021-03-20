#include <iostream>
#include <conio.h>
#include <windows.h>
#include <dos.h>
#include <time.h>

#define SCREEN_WIDTH 100 //output console width
#define SCREEN_HEIGHT 25  //output console height
#define WIN_WIDTH 90 //game screen
#define MAXSNAKESIZE 100 //snake size

using namespace std;

HANDLE consoles = GetStdHandle(STD_OUTPUT_HANDLE); //getting handle on output console
COORD CursorPositions; //co-ordinate structures.
int poison_x,poison_y; //poison food co-ordinate

void gettoxy(int x, int y){ //moving to particular co-ordinate
	CursorPositions.X = x;
	CursorPositions.Y = y;
	SetConsoleCursorPosition(consoles, CursorPositions);
}

class Point{
	private:
		int x;
		int y;
	public:

		Point(){ //default constructor
			x = y = 10;
		}
		Point(int x, int y){ //parameterized constructor
			this -> x = x;
			this -> y = y;
		}
		void SetPoint(int x, int y){ //assigning point
			this -> x = x;
			this -> y = y;
		}
		int GetX(){ //getting x co-ord val
			return x;
		}
		int GetY(){ //getting y co-ord val
			return y;
		}
		void MoveUp(){ //decrementing y co-ord value
			y--;
		}
		void MoveDown(){ //incrementing y co-ord value
			y++;
		}
		void MoveLeft(){ //decrementing x co-ord value
			x--;
		}
		void MoveRight(){ //incrementing x co-ord value
			x++;
		}

		void Draw(){ //drawing out snake in particular point
			gettoxy(x,y);
			cout<<"O";
		}
		void destroy(){
            gettoxy(x,y);
            cout<<" ";
		}
		void Erase(){ //erasing one point in snake body
			gettoxy(x,y);
			cout<<" ";
		}
		void CopyPos(Point * p){ //copy this current x and y to passes point x and y
			p->x = x;
			p->y = y;
		}
		void Debug(){ //just to debug
			cout<<"("<<x<<","<<y<<") ";
		}
};

class Snake{
	private:
		Point* cell[MAXSNAKESIZE]; // array of points to represent snake
		int size; // current size of snake //size is score
		char dir; // current direction of snake
		Point fruit; //fruit's point on console
        Point poisonous_fruit;
        bool poisonous_fruit_flag=false;
	public:

        Snake(){
			size = 1; // default size of snake
			cell[0] = new Point(45,12); // 20,20 is default position
			for( int i=1; i<MAXSNAKESIZE; i++){ //assigning null to all points to snake
				cell[i] = NULL;
			}
			fruit.SetPoint(rand()%50, rand()%25); //setting first fruit to screen
		}
		void AddCell(int x, int y){ //adding one poin to body
			cell[size++] = new Point(x,y);
		}
		void TurnUp(){
			dir = 'w'; // w is control key for turning upward
		}
		void TurnDown(){
			dir = 's'; // w is control key for turning downward
		}
		void TurnLeft(){
			dir = 'a'; // w is control key for turning left
		}
		void TurnRight(){
			dir = 'd'; // w is control key for turning right
		}
		bool border_collision(){
            int x=cell[0]->GetX();
            int y=cell[0]->GetY();
            if(x==0 || x==WIN_WIDTH){
                return true;
            }
            if(y==0 || y==SCREEN_HEIGHT){
                return true;
            }
            return false;
		}
		void Move(){
			// Clear screen
			//system("cls"); //if we didn't clear the screen it will trace out the path of snake

           for(int i=0;i<size;i++){
                cell[i]->destroy();
           }
			// making snake body follow its head
			for(int i=size-1; i>0; i--){ //head 0th will move individuallly
				cell[i-1]->CopyPos(cell[i]); //before snake point of body will be followed by curr point of body
			}

			// turning snake's head
			switch(dir){ //0th head moving
				case 'w':
					cell[0]->MoveUp();
					break;
				case 's':
					cell[0]->MoveDown();
					break;
				case 'a':
					cell[0]->MoveLeft();
					break;
				case 'd':
					cell[0]->MoveRight();
					break;
			}

			// Collision with fruit
			if( fruit.GetX() == cell[0]->GetX() && fruit.GetY() == cell[0]->GetY()){ //food collision
				AddCell(0,0);
				gettoxy(poison_x,poison_y);cout<<" ";
				poison_x=(rand()%89)+1;
				poison_y=(rand()%24)+1;
				poisonous_fruit.SetPoint(poison_x,poison_y);
				fruit.SetPoint((rand()%89)+1, (rand()%24)+1); //setiing next fruit immediately
			}

			//drawing snake
			for(int i=0; i<size; i++)
				cell[i]->Draw();//drawing whole snake
			fruit.Draw(); //drawing the fruit whoose co-ord is already setted in above

			gettoxy(100,12);cout<<"Score:"<<size-1<<endl;
            if((size-1)%5==0 && (size-1)!=0){
                poisonous_fruit.Draw();
                if( poisonous_fruit.GetX() == cell[0]->GetX() && poisonous_fruit.GetY() == cell[0]->GetY()){
                    cout<<"*****You ate Poisonous fruit!!******"<<endl;
                    exit(0);
                }
			}
			Sleep(100); //level of game
		}
		void Debug(){
			for( int i=0; i<size; i++){
				cell[i]->Debug();
			}
		}
};

void introduction(){
            cout<<"*****Controls and Instructions*******"<<endl;
            cout<<"______________________________________"<<endl;
            cout<<"              a-Left                  "<<endl;
            cout<<"              d-right                 "<<endl;
            cout<<"              w-up                    "<<endl;
            cout<<"              s-down                  "<<endl;
            cout<<"______________________________________"<<endl;
            cout<<"Collect Foods as much as possible and Don't hit the walls"<<endl;
            cout<<"For every five collection of food,there Occurs a poisonous fruit with cursor,Don't ate that!!"<<endl;
            Sleep(5000);
}
void draw_structure(){
            system("cls");
            for(int x=0;x<=WIN_WIDTH;x++){ //drawing two rows on top and bottom
                gettoxy(x,0);cout<<"_";
                gettoxy(x,SCREEN_HEIGHT);cout<<"_";
            }
            for(int y=1;y<=SCREEN_HEIGHT;y++){//drawing two columns on left and right
                gettoxy(0,y);cout<<"|";
                gettoxy(WIN_WIDTH,y);cout<<"|";
            }
            gettoxy(100,12);cout<<"Score:"<<0<<endl;
}
void snake_controller(){
	//random no generation
	srand( (unsigned)time(NULL)); //setting the seed for rand function used which gives diff random numbers
    introduction();
    draw_structure();
    // Testing snake

	Snake snake; //only one instance of snake is needed
	char op ;
	do{ //infinite thread running
		if(kbhit()){ //check if any control is hiited
			op = getch();
		}
		switch(op){
			case 'w':
			case 'W':
				snake.TurnUp();
				break;

			case 's':
			case 'S':
				snake.TurnDown();
				break;

			case 'a':
			case 'A':
				snake.TurnLeft();
				break;

			case 'd':
			case 'D':
				snake.TurnRight();
				break;
		}
		snake.Move(); //call to core fucnction
		if(snake.border_collision())
            break;

	}while(op != (char)27);


}
