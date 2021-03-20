#include<bits/stdc++.h>
#include<iostream>
#include<conio.h>
#include<dos.h>
#include<windows.h>
#include<time.h>

#include"cars.h"
#include"tictactoe.h"
#include"snake.h"
using namespace std;


int main() {
         int option;
         cout<<"********Welcome to Stress buster********"<<endl;
         cout<<"----------------------------------------"<<endl;
         cout<<"            1.TicTacToe                 "<<endl;
         cout<<"            2.Cars                      "<<endl;
         cout<<"            3.Snake                     "<<endl;
         cout<<"Enter Option:";
         cin>>option;
         switch(option){
            case 1:{
                tictactoe_controller();
                break;
            }
            case 2:{
                car_controller();
                break;
            }
            case 3:{
                snake_controller();
                break;
            }
            default:{
                cout<<"\nInvalid option..Try out again!!"<<endl;
                Sleep(1000);
                system("cls");
                main();
                break;
            }
         }
         return 0;
}

