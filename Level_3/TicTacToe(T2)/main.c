/*
 * Level 3 (Advanced) - Task 3: Mini Game Development (Tic-Tac-Toe)
 *
 * Description: A console-based two-player Tic-Tac-Toe game with win/draw
 * detection and turn switching.
 */

#include <stdio.h>

char board[3][3];

void initBoard(void) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

void printBoard(void) {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
        if (i < 2) printf("---+---+---\n");
    }
    printf("\n");
}

//Returns 1 if the given player has a winning line
int checkWin(char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return 1;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return 1;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return 1;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return 1;
    return 0;
}

int boardFull(void) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ') return 0;
    return 1;
}

int main(void) {
    int row, col;
    char currentPlayer = 'X';
    int gameOver = 0;

    initBoard();

    printf("===== Tic-Tac-Toe =====\n");
    printf("Players take turns entering row and column (1-3) to place their mark.\n");

    while (!gameOver) {
        printBoard();
        printf("Player %c, enter row and column (1-3 1-3): ", currentPlayer);

        if (scanf("%d %d", &row, &col) != 2) {
            while (getchar() != '\n');
            printf("Invalid input. Please enter two numbers between 1 and 3.\n");
            continue;
        }

        row--; col--; // convert to 0-indexed

        if (row < 0 || row > 2 || col < 0 || col > 2) {
            printf("Invalid position. Row and column must be between 1 and 3.\n");
            continue;
        }

        if (board[row][col] != ' ') {
            printf("That cell is already taken. Choose another.\n");
            continue;
        }

        board[row][col] = currentPlayer;

        if (checkWin(currentPlayer)) {
            printBoard();
            printf("Player %c wins! Congratulations!\n", currentPlayer);
            gameOver = 1;
        } else if (boardFull()) {
            printBoard();
            printf("It's a draw! Good game.\n");
            gameOver = 1;
        } else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }

    return 0;
}
