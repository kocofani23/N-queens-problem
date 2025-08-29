#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/** \brief: function to create the initial chess board for the program
 *
 * \param1: size of chess board
 * \param2: pointer to 2dimensional chess board(matrix)
 * \return: nothing. void function
 *
 */

void createChessBoard(int N, int ***chessBoard)
{
    int i;
    *chessBoard = (int **)calloc(N, sizeof(int *)); // allocate memory for row pointers
    if(*chessBoard == NULL){
        printf("Memory allocation ERROR: chess field initialization!\n");
        return;
    }
    for(i=0; i<N; i++){ // allocate memory for each row
        (*chessBoard)[i] = (int *)calloc(N, sizeof(int));
        if((*chessBoard)[i] == NULL){
            printf("Memory allocation ERROR: row %d!\n", i);
            return;
        }
    }
}


/** \brief: function to reset the chess board when the functions are called back-2-back
 *
 * \param1: size of chess board
 * \param2: 2 dimensional array representing the chess board
 * \return: nothing. void function
 *
 */

void resetChessBoard(int N, int **chessBoard)
{
    int i, j;
    for(i=0; i<N; i++){
        for(j=0; j < N; j++){
            chessBoard[i][j] = 0;
        }
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////**BRUTE FORCE**///////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

/** \brief: function to check whether a queen position is valid or not
 *
 * \param1: size of chess board
 * \param2; 2 dimensional array representing chess board
 * \return
 *
 */

int isValidSolution(int N, int **positions)
{
    int i, j;

    // Check for any conflicts between queens
    for(i=0; i<N; i++){
        for(j=i+1; j<N; j++){ // same rows are skipped since here
            // Check if two queens are in the same column or on the same diagonal
            if(positions[i][1] == positions[j][1] || // Same column
                abs(positions[i][0] - positions[j][0]) == abs(positions[i][1] - positions[j][1])) { // Same diagonal
                return 0; // Conflict found
            }
        }
    }
    return 1; // No conflicts
}

/** \brief: function to generate the next combination of queen placements
 *
 * \param1: 2 dimensional array that holds the positions of the queens
 * \param2: size of chess board
 * \return: 1 if a combination can be added. 0 otherwise
 *
 */

int nextCombination(int **positions, int N)
{
    int i = N - 1;

    // Find the first column that has reached the last position
    while(i >= 0 && positions[i][1] == N - 1){
        positions[i][1] = 0; // Reset column position to 0 if it has reached the last column
        i--;
    }

    if(i < 0)
        return 0; // No more combinations

    positions[i][1]++; // Increment the column position for the current queen
    return 1;
}

/** \brief: function to generate all combinations of positions and check for solutions in brute force approach
 *
 * \param1: size of chess board
 * \return: nothing. void function
 *
 */

void bruteForce(int N)
{
    int i;
    int solutionCount = 0;

    // Initialize positions array (2D array with N rows and 2 columns)
    int **positions = (int **)malloc(N * sizeof(int *));
    for(i=0; i<N; i++){
        positions[i] = (int *)malloc(2 * sizeof(int));
        positions[i][0] = i; // Row number for each queen starts from i (row 0 to N-1)
        positions[i][1] = 0; // All queens start in the first column (column 0)
    }

    // Generate all combinations using a brute force approach
    do{
        // Check if the current arrangement is a valid solution
        if(isValidSolution(N, positions))
            solutionCount++;
    }while (nextCombination(positions, N)); // Generate the next combination

    if(solutionCount == 0)
        printf("No solutions found for the %d-queens problem. (Brute Force)\n", N);

    printf("Total solutions found (Brute Force): %d \n", solutionCount);

    // Free memory for the positions array
    for(i=0; i<N; i++){
        free(positions[i]);
    }
    free(positions);
}


/////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////**OPTIMIZED ONE**//////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/** \brief: function to generate all combinations of positions and check for solutions in optimized1 approach
 *          meaning positions matrix is initialized so no two queens are in the same row as an initial condition
 * \param: size of chess board
 * \return: nothing. void function
 *
 */

void optimizedOne(int N)
{
    int i;
    int solutionCount = 0;

    // Initialize positions array (2D array with N rows and 2 columns)
    int **positions = (int **)malloc(N * sizeof(int *));
    for(i=0; i<N; i++){
        positions[i] = (int *)malloc(2 * sizeof(int));
        positions[i][0] = i; // Row number for each queen starts from i (row 0 to N-1)
        positions[i][1] = 0; // All queens start in the first column (column 0)
    }

    // Generate all combinations using a brute force approach
    do{
        // Check if the current arrangement is a valid solution
        if(isValidSolution(N, positions))
            solutionCount++;

    }while(nextCombination(positions, N)); // Generate the next combination

    if(solutionCount == 0)
        printf("No solutions found for the %d-queens problem. (Optimized 1)\n", N);

    printf("Total solutions found (optimized 1): %d \n", solutionCount);

    // Free memory for the positions array
    for(i=0; i<N; i++){
        free(positions[i]);
    }
    free(positions);
}


/////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////**OPTIMIZED TWO**//////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

/** \brief: function to generate all combinations of positions and check for solutions in optimized2 approach
 *          meaning positions matrix is initialized so no two queens are in the same row or column as an initial condition
 *
 * \param: size of chess board
 * \return
 *
 */

void optimizedTwo(int N)
{
    int i;
    int solutionCount = 0;

    // Initialize positions array (2D array with N rows and 2 columns)
    int **positions = (int **)malloc(N * sizeof(int *));
    for(i=0; i<N; i++){
        positions[i] = (int *)malloc(2 * sizeof(int));
        positions[i][0] = i; // Row number for each queen starts from i (row 0 to N-1)
        positions[i][1] = i;
    }


    // Generate all combinations using a brute force approach
    do{
        // Check if the current arrangement is a valid solution
        if(isValidSolution(N, positions))
            solutionCount++;
    }while(nextCombination(positions, N)); // Generate the next combination

    if(solutionCount == 0)
        printf("No solutions found for the %d-queens problem. (Optimized 2)\n", N);

    printf("Total solutions found (Optimized 2): %d \n", solutionCount);

    // Free memory for the positions array
    for(i=0; i<N; i++){
        free(positions[i]);
    }
    free(positions);
}

/////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////**BACKTRACKING**//////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/** \brief: function used only in backtracking mode to check whether a queen position is valid or not
 *
 * \param1: size of chess board
 * \param2: 2 dimensional array representing the chess board
 * \param3: row used to check whether a queen can be put in this row
 * \param4: column used to check whether a queen can be put in this column
 * \return: 1 if a queen can be put into this position, 0 otherwise
 *
 */

int isValidBacktracking(int N, int **chessBoard, int row, int col)
{
    int i, j;

    for(i=0; i<col; i++){
        if(chessBoard[row][i] == 1)// if in any column a queen is present return 0
            return 0;
    }

    for(i=row, j=col; i>=0 && j>=0; i--, j--){
        if(chessBoard[i][j] == 1) // if in any diagonal a queen is present return 0
            return 0;
    }

    for(i=row, j=col; i<N && j>=0; i++, j--){
        if(chessBoard[i][j] == 1) // if in column going backwards a queen is present return 0
            return 0;
    }

    return 1;
}

/** \brief: helper function used in backtracking mode
 *
 * \param1: size of chess board
 * \param2: 2 dimensional array representing the chess board
 * \param3: integer used to check whether a queen can be put into that column
 * \param4: number of solutions found for N
 * \return: whether a queen can be put or not
 *
 */

int solveBacktracking(int N, int **chessBoard, int col, int *solutionCount)
{
    int row;
    if(col >= N){ // Base case: all queens are placed
        (*solutionCount)++;
        return 1; // Return to explore more solutions
    }

    for(row=0; row<N; row++){
        if(isValidBacktracking(N, chessBoard, row, col)){ // Check if queen can be placed
            chessBoard[row][col] = 1; // Place queen
            solveBacktracking(N, chessBoard, col + 1, solutionCount); // Recursive call
            chessBoard[row][col] = 0; // Backtrack
        }
    }
    return 0; // Indicate all possibilities explored for this branch
}

/** \brief: backtracking function used to solve the n-queens problem
 *
 * \param1: size of chess board
 * \param2: 2 dimensional array representing the chess board
 * \return
 *
 */

void backtracking(int N, int **chessBoard)
{
    int solutionCount = 0;
    solveBacktracking(N, chessBoard, 0, &solutionCount); // call recursive helper function
    if(solutionCount == 0){
        printf("No solutions found for the %d-queens problem.(Backtracking)\n", N);
    } else {
        printf("Total solutions found (Backtracking): %d\n", solutionCount);
    }
}



int main()
{
    int N, mode, **chessBoard = NULL;
    clock_t start, end;
    double time_taken;

    printf("Enter size of chess field(N>=4): "); // prompt user for queens number/board size
    scanf("%d", &N);
    if(N <= 3){
        printf("Size incorrect!\nExiting...\n"); // if less than 3 exit program
        return -1;
    }
    createChessBoard(N, &chessBoard); // call function to create chess board
    if(chessBoard == NULL){
        return -1;
    }
    printf("Select mode you wish the program to compute N-queens problem: \n"); // prompt user to select mode for solving problem
    printf("(1) => Brute Force\n");
    printf("(2) => Optimized 1\n");
    printf("(3) => Optimized 2\n");
    printf("(4) => Backtracking\n");
    printf("(0) => All together\n");
    printf("Mode: ");
    scanf("%d", &mode);

    switch(mode){ // switch case used
        case 1:
            start = clock(); // measure time
            bruteForce(N);
            end = clock();
            time_taken = (end - start)/CLOCKS_PER_SEC;
            printf("Time taken for brute force algorithm to solve %d-queens problem is: %f\n", N, time_taken);
            break;
        case 2:
            start = clock(); // measure time
            optimizedOne(N);
            end = clock();
            time_taken = (end - start)/CLOCKS_PER_SEC;
            printf("Time taken for optimized one algorithm to solve %d-queens problem is: %f\n", N, time_taken);
            break;
        case 3:
            start = clock(); // measure time
            optimizedTwo(N);
            end = clock();
            time_taken = (end - start)/CLOCKS_PER_SEC;
            printf("Time taken for optimized two algorithm to solve %d-queens problem is: %f\n", N, time_taken);
            break;
        case 4:
            start = clock();// measure time
            backtracking(N, chessBoard);
            end = clock();
            time_taken = (end - start)/CLOCKS_PER_SEC;
            printf("Time taken for backtracking algorithm to solve %d-queens problem is: %f\n", N, time_taken);
            break;
        case 0:
            start = clock();// measure time
            bruteForce(N);
            end = clock();
            time_taken = (end - start)/CLOCKS_PER_SEC;
            printf("Time taken for brute force algorithm to solve %d-queens problem is: %f\n", N, time_taken);
            resetChessBoard(N, chessBoard);// reset boards so a solution can be found for each mode

            start = clock();// measure time
            optimizedOne(N);
            end = clock();
            time_taken = (end - start)/CLOCKS_PER_SEC;
            printf("Time taken for optimized1 algorithm to solve %d-queens problem is: %f\n", N, time_taken);
            resetChessBoard(N, chessBoard);

            start = clock();// measure time
            optimizedTwo(N);
            end = clock();
            time_taken = (end - start)/CLOCKS_PER_SEC;
            printf("Time taken for optimized2 algorithm to solve %d-queens problem is: %f\n", N, time_taken);
            resetChessBoard(N, chessBoard);

            start = clock();// measure time
            backtracking(N, chessBoard);
            end = clock();
            time_taken = (end - start)/CLOCKS_PER_SEC;
            printf("Time taken for backtracking algorithm to solve %d-queens problem is: %f\n", N, time_taken);
            break;
        default:
            printf("Error while choosing mode...");
            break;
    }
    return 0;
}
