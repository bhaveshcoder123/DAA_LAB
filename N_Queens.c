#include <stdio.h>
#include <stdlib.h>

int answerNumber;

int isSafe(int row, int col, int* visitedCol, int* visitedRightDiag, int* visitedLeftDiag, int N) {
    if (visitedCol[col]) return 0;
    if (visitedRightDiag[col - row + N - 1]) return 0;
    if (visitedLeftDiag[col + row]) return 0;
    return 1;
}

void backtrack(int row, int** board, int* visitedCol, int* visitedRightDiag, int* visitedLeftDiag, int N) {
    if (row == N) {
        answerNumber++;
        printf("Solution #%d:\n", answerNumber);
        
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if(board[i][j] == 1) 
                    printf("Q ");
                else 
                    printf(". ");
            }
            printf("\n");
        }
        printf("\n");
        return;
    }

    for (int col = 0; col < N; col++) {
        if (isSafe(row, col, visitedCol, visitedRightDiag, visitedLeftDiag, N)) {
            
            board[row][col] = 1;
            visitedCol[col] = 1;
            visitedRightDiag[col - row + N - 1] = 1;
            visitedLeftDiag[col + row] = 1;

            
            backtrack(row + 1, board, visitedCol, visitedRightDiag, visitedLeftDiag, N);

            
            board[row][col] = 0;
            visitedCol[col] = 0;
            visitedRightDiag[col - row + N - 1] = 0;
            visitedLeftDiag[col + row] = 0;
        }
    }
}

int main() {
    int N;
    printf("Please enter the value of N: ");
    if (scanf("%d", &N) != 1) return 1;

    int** board = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        board[i] = (int*)calloc(N, sizeof(int));
    }

    answerNumber = 0;

    int* visitedCol = (int*)calloc(N, sizeof(int));
    int diagonals = 2 * N - 1;
    int* visitedRightDiag = (int*)calloc(diagonals, sizeof(int));
    int* visitedLeftDiag = (int*)calloc(diagonals, sizeof(int));

    backtrack(0, board, visitedCol, visitedRightDiag, visitedLeftDiag, N);

    printf("Total number of configurations found: %d\n", answerNumber);

    return 0;
}