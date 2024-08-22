#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define BLACK_BG_WHITE_TEXT "\x1b[0;30;107m"
#define CYAN "\033[0;36m"
#define YELLOW "\e[1;93m"
#define GREEN   "\x1b[32m"
#define RED_R "\e[0;31m"
#define RED_B "\e[1;31m"
#define RED_UL "\e[4;31m"
#define RED_BG "\e[41m"
#define RED_HIBG "\e[0;101m"
#define RED_HI "\e[0;91m"
#define RED_BHI "\e[1;91m"
#define BLUE_R "\e[1;94m"
#define RESET "\x1b[0m"

void CHECK_WINNER();
void delay(int delay_time);
void JUST_THE_TABLE();
void PRINT_TABLE();
void UPDATE();
void START_GAME();
void RESET_GAME();
void END_SCREEN();
void END_OR_NEW_GAME();
int playerX = 0; // ++ if playerX wins
int playerO = 0; // ++ if playerO wins
int end_game_counter = 1; // repeat current game
int X_USER; // X user_input
int O_USER; // O user_input
int flag = 1; // switch between X & O players
int inputs_counter = 0; // check_winner invoker
// =========== OPENING_SCREEN ===========
void printX_SHAPE(int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j || i + j == size - 1) {
                printf(RED_B"X ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
};
void printO_SHAPE(int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if ((i == 0 || i == size - 1) && (j > 0 && j < size - 1)) {
                printf(BLUE_R" O");
            } else if ((i > 0 && i < size - 1) && (j == 0 || j == size - 1)) {
                printf(BLUE_R" O");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
    printf(RESET);
}
void printG(int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if ((i == 0 || i == size - 1) && (j > 0 && j < size - 1)) {
                printf(" *");
            } else if (i > 0 && i < size - 1 && j == 0) {
                printf(" *");
            } else if (i == size / 2 && j > size / 4 && j < size - 1) {
                printf(" *");
            } else if (i >= size / 2 && j == size - 1) {
                printf(" *");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
}
void printO(int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if ((i == 0 || i == size - 1) && (j > 0 && j < size - 1)) {
                printf(" *");
            } else if ((i > 0 && i < size - 1) && (j == 0 || j == size - 1)) {
                printf(" *");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
}
void XO_ANIMATION(int times){
    for(int i = 0; i < times; i++){
        printX_SHAPE(5);
        delay(2);
        system("cls");
        printO_SHAPE(5);
        delay(2);
        system("cls");
        
    }
}
void WELCOME_RULES() {
    // ====
    XO_ANIMATION(2);
    // ====
    printG(5); printf("\n"); printO(5);
    
    delay(7);
    system("cls");
    // ====
    // rules-welcome
    const int ch = 175;
    printf("--------------------------\n""|"CYAN" WELCOME TO TIC TAC TOE "RESET"|\n""--------------------------\n");
    printf(RED_R "Rules of the game:" RESET"\n\n");
    printf(BLACK_BG_WHITE_TEXT" 1 "RESET" %c Get three in a line first to win.\n""\n", ch);
    printf(BLACK_BG_WHITE_TEXT" 2 "RESET" %c Enter the number of the targeted position to be changed to ("RED_B"X"RESET"/"BLUE_R"O"RESET").\n\n", ch);
    printf(BLACK_BG_WHITE_TEXT" 3 "RESET" %c If no one made it, it is a draw.\n""\n"RESET, ch);
    for (int i = 0; i < 40; i++) printf("%c",205);
    printf("\nIf you are ready press any "RED_BG "key" RESET": ");
    getch();
}
/*-------------------------------------------*/
char SQUARES_NUMBERS[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};
/*-------------------------------------------*/
void START_GAME(){
    system("cls");
    XO_ANIMATION(1);
    
    system("cls");
    PRINT_TABLE(); // for the first time only
    
    while(1){
        UPDATE();
        // print game results:
        // returns 1 if x win, o win, draw happen
        // returns 0 else
        if(PRINT_GAME_RESULT()) break;
        end_game_counter++;
    }
    
    END_OR_NEW_GAME();
};
/*-------------------------------------------*/
void UPDATE(){
    int USER = getch();
    
    int invalid = 0;
    int taken = 0;   
    USER -= '0';
    // ==> Invalid number <==
    if(USER > 9 || USER < 1){
        invalid = 1;
        printf("\n");
        end_game_counter--;
    }
    // ==> IF ALREADY TAKEN <==
    if( SQUARES_NUMBERS[(USER-1)/3][(USER-1)%3] == 'X' || 
        SQUARES_NUMBERS[(USER-1)/3][(USER-1)%3] == 'O'){
        // when input the same number twice
        // The third symbol will be the first symbol
        // input [1] -> X
        // input [1] -> for "O" but 1 is already taken
        // input [2] -> for "O" but we get X again in 2
        // that's because the change of the flag every input
        // this condition prevent that bug
        
        taken = 1;
        end_game_counter--; 
    }
    // ==> Updating <==
    if(!invalid && !taken)
        if(flag){
            SQUARES_NUMBERS[(USER-1)/3][(USER-1)%3] = 'X';
            flag--;
        }
        else{
            SQUARES_NUMBERS[(USER-1)/3][(USER-1)%3] = 'O';
            flag++;
        }
    /*
    --> after every action from above
        the terminal is cleared
        new table is generated
        a message is displayed according to the provided conditions
    */
    system("cls");
    PRINT_TABLE();
    
    if (invalid){
        printf(RED_HIBG"\nEnter a valid input"RESET);
        return;
    }
    if (taken){
        printf(YELLOW"\n[%d] "CYAN,USER);
        printf(RED_R"Already taken\n"RESET);
        printf("Enter another number:");
        return;
    }
    
    inputs_counter++;
    if(inputs_counter > 4)
        CHECK_WINNER();
};
/*-------------------------------------------*/
void CHECK_WINNER(){
    //Check Win for rows
    for(int i=0; i<3; i++)
        if(SQUARES_NUMBERS[i][0] == SQUARES_NUMBERS[i][1] && SQUARES_NUMBERS[i][0] == SQUARES_NUMBERS[i][2])
            if(SQUARES_NUMBERS[i][0] == 'O'){
                playerO++;
            }
            else{
                playerX++;
            }
                
    // Check win for coloumns
    for(int i = 0; i < 3; i++)
        if(SQUARES_NUMBERS[0][i] == SQUARES_NUMBERS[1][i] && SQUARES_NUMBERS[0][i] == SQUARES_NUMBERS[2][i])
            if(SQUARES_NUMBERS[0][i]=='O'){
                playerO++;
            }
            else{
                playerX++;
            }
                
    //checking the win for both diagonal
    if(SQUARES_NUMBERS[0][0] == SQUARES_NUMBERS[1][1] && SQUARES_NUMBERS[0][0] == SQUARES_NUMBERS[2][2])
        if(SQUARES_NUMBERS[0][0]=='O'){
            playerO++;
        }
        else{
            playerX++;
        }

    if(SQUARES_NUMBERS[0][2] == SQUARES_NUMBERS[1][1] && SQUARES_NUMBERS[0][2] == SQUARES_NUMBERS[2][0])
        if(SQUARES_NUMBERS[0][2]=='O'){
            playerO++;
        }
        else{
            playerX++;
        }
}
/*-------------------------------------------*/
// its logic is based on playerX/O after CHECK_WINNER updates them
// and end_game_counter variable
int PRINT_GAME_RESULT(){
    if(playerX) {
        system("cls");
        JUST_THE_TABLE();
        printf("Player " RED_B "X" RESET " won!\n");
        return 1;
    }
    else if (playerO){
        system("cls");
        JUST_THE_TABLE();
        printf("Player " BLUE_R "O" RESET " won!\n\n");
        return 1;
    }
    else if (end_game_counter == 9){
        system("cls");
        JUST_THE_TABLE();
        printf("It's a "BLACK_BG_WHITE_TEXT"DRAW!\n"RESET);
        return 1;
    }
    return 0;
}
/*-------------------------------------------*/
void JUST_THE_TABLE(){
    printf("-------------\n");
    for (int i = 0; i < 3; i++)
    {
        printf("|");
        for (int j = 0; j <= 2; j++)
            if(SQUARES_NUMBERS[i][j] == 'X'){
                printf(RED_B" %c "RESET, SQUARES_NUMBERS[i][j]);
                printf("|");
            }
            else if(SQUARES_NUMBERS[i][j] == 'O'){
                printf(BLUE_R" %c "RESET, SQUARES_NUMBERS[i][j]);
                printf("|");
            }else{
                printf(" %c ",SQUARES_NUMBERS[i][j]);
                printf("|");
            }
        printf("\n");
        printf("-------------\n");
    }
}
void PRINT_TABLE(){
    if(flag) printf(RED_B "X "RESET "turn...\n");
    else printf(BLUE_R "O " RESET "turn...\n");
    printf("-------------\n");
    for (int i = 0; i < 3; i++)
    {
        printf("|");
        for (int j = 0; j <= 2; j++)
            if(SQUARES_NUMBERS[i][j] == 'X'){
                printf(RED_B" %c "RESET, SQUARES_NUMBERS[i][j]);
                printf("|");
            }
            else if(SQUARES_NUMBERS[i][j] == 'O'){
                printf(BLUE_R" %c "RESET, SQUARES_NUMBERS[i][j]);
                printf("|");
            }else{
                printf(" %c ",SQUARES_NUMBERS[i][j]);
                printf("|");
            }
        printf("\n");
        printf("-------------\n");
    }
}
/*------------------------------------------*/
void END_OR_NEW_GAME(){
    printf("\nNew Game? [Y/y] \nor press any key to "RED_HI"EXIT"RESET".");
    char NEW_END = getch();
    if(NEW_END == 'Y' || NEW_END == 'y'){
        RESET_GAME();
        return START_GAME();
    }
    else{
        system("cls");
        END_SCREEN();
        return;
    }
}
void RESET_GAME(){
    char x = '1';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            SQUARES_NUMBERS[i][j] = x;
            x++;
        }
    }    
    playerX = 0;
    playerO = 0;
    end_game_counter = 1;
    X_USER;
    O_USER;
    flag = 1;
    inputs_counter = 0;
}
void END_SCREEN(){
    delay(1);
    if(playerX){
        for (int i = 0; i < 3; i++)
        {
            printX_SHAPE(5);
            delay(3);
            system("cls");
            
            printX_SHAPE(7);
            delay(3);
            system("cls");
        }
        printX_SHAPE(7);
    }else if(playerO){
        for (int i = 0; i < 3; i++)
        {
            printO_SHAPE(5);
            delay(3);
            system("cls");
            
            printO_SHAPE(7);
            delay(3);
            system("cls");
        }
        printO_SHAPE(7);
    }
    printf("\n");
    
    printf("%c" RED_BHI "Thanks for playing ^.^" RESET "\n", 248);
    printf(YELLOW "ab2a t3ala tany\n\n" RESET);
    // replaced by X-O animation
    // JUST_THE_TABLE();
    
    delay(1);

    printf("\e[4;37m""Produced by:\n" RESET);
    delay(1);
    
    const char symbol_end = 192;
    printf(RED_HI "%cAhmed Mohamed\n" RESET, symbol_end);
    delay(1);
    
    printf(BLUE_R "%cMalak Salah Elddin\n" RESET, symbol_end);
    delay(1);
    
    printf(YELLOW "%cMoataz Mohamed\n" RESET, symbol_end);
    delay(1);

    printf(GREEN "%cAhmed Tharwat\n" RESET, symbol_end);

    delay(1);
    printf("\n====");
    delay(1);
    printf("====");
    delay(1);
    printf("====");
    delay(1);
    printf(RED_BG "BYE!" RESET);
    delay(1);
    printf("====");
    delay(1);
    printf("====");
    delay(1);
    printf("====\n");
    printf("Press any key...");
    getch();
}
/*------------------------------------------*/
void delay(int delay_time){
    for (int i = 0; i < delay_time*199990000; i++);
}
/*------------------------------------------*/
int main(){
    WELCOME_RULES();
    START_GAME();
    exit(0);
}