#include <stdio.h>

// Sudoku is a 9x9 grid of cells
// I chose to define these seperately to better tell what is being iterated in the for loops
#define ROWS  9
#define COLS  9


int find_next_blank(int puzzle[ROWS][COLS], int coords[2]){
    for (int i = 0; i < ROWS; ++i){
        for (int j = 0; j < COLS; ++j){
            // If we find a "0" cell, set the coord array and then return true
            if (puzzle[i][j] == 0){
                coords[0] = i;
                coords[1] = j;
                return 1;
            }
        }
    }
    // If we never find a blank space, then return false.
    return 0;
}

int isValid(int puzzle[ROWS][COLS], int coords[2], int guess){
    // First check the row to see if the number is already there
    for (int i = 0; i < COLS; ++i){
        // If the number is in the row, this guess is invalid
        if (puzzle[coords[0]][i] == guess){
            return 0;
        }
    }
    // Then check the column to see if the number is there
    for (int i = 0; i < ROWS; ++i){
        if (puzzle[i][coords[1]] == guess){
            // If the number is in the column, this guess is invalid
            return 0;
        }
    }
    // Then check the current 3x3 grid to see if the number is there
    // this can be broken up into a 3x3 xy axis

    // First we find our y value
    int sudoku_chunk_row = coords[0] / 3;

    // Then our x value
    int sudoku_chunk_col = coords[1] / 3;

    // Now we search that 3x3 grid, starting with the top left cell of the chunk and ending at the bottom right cell
    for (int i = sudoku_chunk_row * 3; i < (sudoku_chunk_row * 3) + 3; ++i){
        for (int j = sudoku_chunk_col * 3; j < (sudoku_chunk_col * 3) + 3; ++j){
            if (puzzle[i][j] == guess){
                // If the number is in the chunk, this guess is invalid
                return 0;
            }
        }
    }

    // If we haven't returned a 0 by now then this is a valid number
    return 1;
}

int findSolution(int puzzle[ROWS][COLS]){
    int coords[2];
    if (find_next_blank(puzzle, coords)){
        for (int i = 1; i <= 9; ++i){
            // We guess 1-9, if the guess was valid then we input it into the puzzle
            if (isValid(puzzle, coords, i)){
                puzzle[coords[0]][coords[1]] = i;
                // Now we recursively call the function to test out the next iteration
                if (findSolution(puzzle)){
                    return 1;
                }
                else{
                    // Our guess was not valid so we will back track!
                    puzzle[coords[0]][coords[1]] = 0;
                }
            }
        }
    }
    else{
        // If the find_next_blank function returns 0 then there are no more guesses to be made. The puzzle SHOULD be solved.
        printf("Ran out of blank cells, puzzle is solved.\n");
        return 1;
    }
    return 0;
}

int printPuzzle(int puzzle[ROWS][COLS]){
    // Prints the entire puzzle and makes it nice and easy to read
    printf("+-----------------------+\n");
    for (int i = 0; i < ROWS; ++i){
        printf("| ");
        for (int j = 0; j < COLS; ++j){
            if (puzzle[i][j] == 0){
                putchar('-');
            }
            else{
                printf("%d",puzzle[i][j]);
            }
            if ((((j + 1)% 3) == 0) && (j != COLS - 1)){
                printf(" | ");
            }
            else if (j != COLS - 1){
                putchar(' ');
            }
        }
        printf(" |\n");

        if ((((i + 1 )% 3) == 0) && (i != ROWS - 1)){
            printf("+-----------------------+\n");
        }
    }
    printf("+-----------------------+\n");
    return 1;
}

int main(void){
    
    int puzzle[ROWS][COLS] = {
    {4,0,2,9,0,0,6,0,7},
    {3,9,0,0,0,0,2,4,8},
    {7,0,0,0,0,1,9,0,3},
    {5,4,0,0,0,0,0,0,0},
    {0,0,3,7,0,9,5,0,4},
    {8,2,0,0,5,0,0,9,6},
    {0,0,5,0,0,6,0,7,0},
    {0,0,4,8,0,0,0,0,9},
    {0,0,8,0,0,0,4,0,0}
    };


    if (findSolution(puzzle)){   
        printPuzzle(puzzle);
    }
    else{
        printf("Could not find solution..\n");
    }
    

    // returning a 0 to OS usually means success
    return 0;
}
