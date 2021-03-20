#ifndef TICTACTOE_H_INCLUDED
#define TICTACTOE_H_INCLUDED



bool validate_player_name(char *x);
void set_initial_player(char *name);
bool validate_player_number(int x);
void toggle_player();
bool validate_player_marker(char a);
bool validate_board();
void intro();
void draw_board_on_screen();
int get_col(char slot);
int get_row(char slot);
void place_the_marker(char slot);
char who_is_winner();
void tictactoe_controller();


#endif // TICTACTOE_H_INCLUDED
