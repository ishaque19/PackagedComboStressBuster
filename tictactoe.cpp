#include<bits/stdc++.h>
#include<iostream>
#include<conio.h>
#include<dos.h>
#include<windows.h>
#include<time.h>
#include "tictactoe.h"
using namespace std;


char board3of3[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}}; //3*3 board
char board4of4[4][4] = {{'a','b','c','d'},{'e','f','g','h'},{'i','j','k','l'},{'m','n','o','p'}};
int board_type;
string p1,p2;
char markers[2];
int current_player,tie=0;
int total_no_of_cells_filled=0;
char slot_no;

bool validate_player_name(string x){
    if(x==p1 || x==p2)
        return false;
    else
        return true;
}
void set_initial_player(string name){
    if(name==p1)
        current_player=1;
    else
        current_player=2;
}
bool validate_player_number(int x){
    if(x==1||x==2)
        return false;
    else{
        cout<<"Invalid player Number!!Try again..."<<endl;
        return true;
    }
}
void toggle_player(){
    if(current_player==1)
        current_player=2;
    else
        current_player=1;
}
bool validate_player_marker(char a){
    if( ((a>=65 && a<=90) || (a>=97 && a<=122)) )
            return false;
    else{
            cout<<"Character should lie b/w a to z OR A to z"<<endl;
            return true;
    }
}
bool validate_board(){
    if(board_type==3 || board_type==4)
        return false;
    else{
        cout<<"Invalid board type<"<<endl;
        return true;
    }
}
void intro(){
    cout<<"*****Welcome To The World of Stress Buster*****"<<endl;
    cout<<"Enter Player1 Name:";cin>>p1;cout<<endl;
    cout<<"Enter Player2 Name:";cin>>p2;cout<<endl;

    do{
        cout<<p1<<" \'s favourite character:";cin>>markers[0];cout<<endl;
    }while(validate_player_marker(markers[0]));
    do{
        cout<<p2<<" \'s favourite character:";cin>>markers[1];cout<<endl;
    }while(validate_player_marker(markers[1]));

    do{
    cout<<"Enter 3 for 3*3 board and 4 for 4*4 board:";
    cin>>board_type;
    cout<<endl;
    }while(validate_board());

    string temp;
    do{
        cout<<"Please Enter the player Name who willing to start first:";cin>>temp;cout<<endl;
    }while(validate_player_name(temp));

    set_initial_player(temp);

}
void draw_board_on_screen(){
    if(board_type==3){
        for(int i=0;i<board_type;i++){
            for(int j=0;j<board_type;j++){
                cout<<board3of3[i][j];
                if(j!=2)
                    cout<<" | ";
            }
            if(i!=2)
                cout<<"\n"<<"--|---|---"<<endl;
        }
        cout<<endl;
        cout<<"--------------------"<<endl;
    }
    else{
        for(int i=0;i<board_type;i++){
            for(int j=0;j<board_type;j++){
                cout<<board4of4[i][j];
                if(j!=3)
                    cout<<" | ";
            }
            if(i!=3)
                cout<<"\n"<<"--|---|---|---"<<endl;
        }
        cout<<endl;
        cout<<"---------------------"<<endl;
    }
}
int get_col(char slot){
    if(board_type==3){
        if(slot=='1'||slot=='4'||slot=='7')
            return 0;
        else if(slot=='2'||slot=='5'||slot=='8')
            return 1;
        else if(slot=='3'||slot=='6'||slot=='9')
                return 2;
        else
            return -1; //for invalid case
    }
    else{
         if(slot=='a'||slot=='e'||slot=='i'||slot=='m')
            return 0;
        else if(slot=='b'||slot=='f'||slot=='j'||slot=='n')
            return 1;
        else if(slot=='c'||slot=='g'||slot=='k'||slot=='o')
            return 2;
        else if(slot=='d'|| slot=='h'|| slot=='l' || slot=='p')
            return 3;
        else
            return -1; //for invalid case
    }

}
int get_row(char slot){
     if(board_type==3){
         if(slot=='1'||slot=='2'||slot=='3')
            return 0;
         else if(slot=='4'||slot=='5'||slot=='6')
            return 1;
         else if(slot=='7'||slot=='8'||slot=='9')
                return 2;
         else
            return -1; //for invalid case
     }
     else{
         if(slot=='a'||slot=='b'||slot=='c'|| slot=='d')
            return 0;
         else if(slot=='e'||slot=='f'||slot=='g'|| slot=='h')
            return 1;
         else if(slot=='i'||slot=='j'||slot=='k'|| slot=='l')
                return 2;
         else if(slot=='m'||slot=='n'||slot=='o'||slot=='p')
                return 3;
         else
            return -1; //for invalid case
     }
}
void place_the_marker(char slot){
    int row=get_row(slot);
    int col=get_col(slot);
    if(row!=-1 && col!=-1){
        if(board_type==3){
            board3of3[row][col]=markers[current_player-1];
        }
        else{
            board4of4[row][col]=markers[current_player-1];
        }
        total_no_of_cells_filled++;
    }
    else{
        cout<<">Please enter the valid slot position:";
        cin>>slot_no;
        place_the_marker(slot_no);
    }
}
char who_is_winner(){

    if(board_type==3){
        //row check
        for(int i=0;i<3;i++){
            if(board3of3[i][0]==board3of3[i][1] && board3of3[i][1]==board3of3[i][2] && board3of3[i][0]==board3of3[i][2])
                    return board3of3[i][0];
        }
        //col check
        for(int i=0;i<3;i++){
            if(board3of3[0][i]==board3of3[1][i] && board3of3[1][i]==board3of3[2][i] && board3of3[2][i]==board3of3[0][i])
                return board3of3[0][i];
        }
        //diagonal check
        if(board3of3[0][0]==board3of3[1][1] && board3of3[1][1]==board3of3[2][2] && board3of3[2][2]==board3of3[0][0])
            return board3of3[1][1];
        if(board3of3[0][2]==board3of3[1][1] && board3of3[1][1]==board3of3[2][0] && board3of3[0][2]==board3of3[2][0])
            return board3of3[1][1];
    }
    else{
        //row check
        for(int i=0;i<4;i++){
            if(board4of4[i][0]==board4of4[i][1] &&  board4of4[i][1]==board4of4[i][2] && board4of4[i][2]==board4of4[i][3] && board4of4[i][3]==board4of4[i][0] && board4of4[i][0]==board4of4[i][2] && board4of4[i][1]==board4of4[i][3])
                return board4of4[i][0];
        }
        //col check
        for(int i=0;i<4;i++){
            if(board4of4[0][i]==board4of4[1][i] && board4of4[0][i]==board4of4[2][i] && board4of4[0][i]==board4of4[3][i] && board4of4[1][i]==board4of4[2][i] && board4of4[1][i]==board4of4[3][i] && board4of4[2][i]==board4of4[3][i])
                return board4of4[0][i];
        }
        //diagonal check
        if(board4of4[0][0]==board4of4[1][1] &&  board4of4[1][1]==board4of4[2][2] && board4of4[2][2]==board4of4[3][3] && board4of4[3][3]==board4of4[0][0] && board4of4[0][0]==board4of4[2][2] && board4of4[1][1]==board4of4[3][3])
            return board4of4[1][1];
        if(board4of4[0][3]==board4of4[1][2] && board4of4[0][3]==board4of4[2][1] && board4of4[0][3]==board4of4[3][0] && board4of4[1][2]==board4of4[2][1] && board4of4[1][2]==board4of4[3][0] && board4of4[2][1]==board4of4[3][0])
            return board4of4[2][1];
    }
    return '*';
}
void tictactoe_controller(){
        intro();
        while(who_is_winner()=='*'){
            system("cls");
            draw_board_on_screen();
            cout<<"Player"<<current_player<<" 's turn to enter slot:";
            cin>>slot_no;
            place_the_marker(slot_no);
            if((board_type==3 && total_no_of_cells_filled==9) || (board_type==4 && total_no_of_cells_filled==16)){
                tie=1;
                break;
            }
            toggle_player();
        }
        system("cls");
        draw_board_on_screen();
        if(tie!=1){
            char winner_marker=who_is_winner();
            if(winner_marker==markers[0])
                cout<<p1<<" wins"<<endl;
            else
                cout<<p2<<" wins"<<endl;
        }
        else{
            cout<<"***The Game is tied***"<<endl;
        }
}
