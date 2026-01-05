#include <stdio.h>

char board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
char current_player = 'X';

void displayboard(){
    printf("\n");
    printf(" %c | %c | %c \n", board[0], board[1], board[2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", board[3], board[4], board[5]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", board[6], board[7], board[8]);
    printf("\n");
}

void switchplayer(){
    current_player = (current_player == 'X') ? 'O' : 'X';
}

int checkwin(){
    int wincondition[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // columns
        {0, 4, 8}, {2, 4, 6}             // diagonals

    };
    for (int i = 0; i < 8; i++) {
        if (board[wincondition[i][0]] == current_player &&
            board[wincondition[i][1]] == current_player &&
            board[wincondition[i][2]] == current_player) {
            return 1;
        }
    }
    return 0;
}

// jika seri 
int checkdraw(){
    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            return 0;
        }
    }
    return 1;
}

int main(){
    int choice;

    printf("Tic Tac Toe Game\n");
    printf("=== TIC TAC TOE (Player vs Player) ===\n");
    while (1) {
        displayboard();
        printf("Player %c, pilih angka (1-9): ", current_player);
        scanf("%d", &choice);
        
        if (choice < 1 || choice > 9 ||
            board[choice - 1] == 'X' || board[choice - 1] == 'O') {
            printf("Pilihan tidak valid. Coba lagi kawan~.\n");
            continue;
        }

        board[choice - 1] = current_player;

        if (checkwin()) {
            displayboard();
            printf("Player %c menang!\n", current_player);
            break;
        }

        if (checkdraw()) {
            displayboard();
            printf("Permainan seri!\n");
            break;
        }

        switchplayer();
    }
    return 0;
}