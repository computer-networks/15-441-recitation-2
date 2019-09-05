#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum square{hidden_ship, hidden_water, shown_ship, shown_water};


void printBoard(int **board, int boardSize){
  int i, j;
  for(i = 0; i <= boardSize; ++i){
    for(j = 0; j <= boardSize; ++j){
      switch(board[i][j]){
        case hidden_ship:
          //fall through
        case hidden_water:
          printf("~ ");
          break;
        case shown_ship:
          printf("X ");
          break;
        case shown_water:
          printf("O ");
          break;
      }
    }
    printf("\n");
  }
}

// One player battleship. Board is of size nxn where n is command line arg
// There are n ships the player must sink where each ship occupies one square
// Assume all user inputs are valid
int main(int argc, char **argv){
  if(argc != 2){
    printf("First arg should be length/width of board\n");
    return 1;
  }

  //Assume the user inputs a valid integer
  int boardSize = atoi(argv[1]);

  //Construct empty board
  int **board = (int **) malloc(boardSize*sizeof(int **));
  int i, j;
  for(i = 0; i < boardSize; ++i){
    board[i] = (int *) malloc(boardSize*sizeof(int *));
  }

  //Populate the board with battleships
  srand(time(0));

  int x,y;
  while(i < boardSize){
    x = rand() % boardSize;
    y = rand() % boardSize;
    if(board[x][y] == hidden_ship) continue;
    board[x][y] = hidden_ship;
    i = i + 1;
  }  
  
  int shipsFound = 0;
  int roundNum = 0;

  while(shipsFound < boardSize){
    
    printBoard(board, boardSize);

    int playerX, playerY;
    printf("Enter X and Y values: ");
    scanf("%d %d", &playerX, &playerY);
    printf("\n");

    switch(board[playerX][playerY]){
      case hidden_ship:
        printf("You hit a ship! %d ships left\n", boardSize-shipsFound);
        board[playerX][playerY] = shown_ship;
        shipsFound += 1;
        break;
      case hidden_water:
        printf("You hit nothing :(\n");
        board[playerX][playerY] = shown_water;
        break;
      default:
        printf("You already chose that square!\n");
    } 
    roundNum += 1;
  }
  printf("Congrats! You won in %d rounds\n", roundNum);
  return 0;
}

