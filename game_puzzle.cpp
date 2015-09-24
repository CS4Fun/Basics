/*
|-----------------------------------------------------------------------------|
| File Header Begin
|-----------------------------------------------------------------------------|
| Abstract:
|
| Puzzle game of specified dimension Board.d, where Board.d is >= 1 and <= 9.
|
|   ie. game of fifteen
|-----------------------------------------------------------------------------|
|
| To Run:
|
|   ./game_puzzle
|
|-----------------------------------------------------------------------------|
| Notes:
|-----------------------------------------------------------------------------|
| File Header End
|-----------------------------------------------------------------------------|
*/

/*
|------------------------------------------------------------------------------
| INCLUDE
|------------------------------------------------------------------------------
*/

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <stdio.h>
#include <unistd.h>
using namespace std;

/*
|------------------------------------------------------------------------------
| DEFINE
|------------------------------------------------------------------------------
*/

/* Board's minimal dimension */
#define D_MIN 3

/* Board's maximal dimension */
#define D_MAX 9

/* Value of the blank tile. */
#define D_BLANK_TILE  -1

/* Display value of the blank tile. */
#define D_BLANK_CHAR  ' '

/*
|------------------------------------------------------------------------------
| TYPE
|------------------------------------------------------------------------------
*/

typedef enum
{
    E_LEFT = 0,
    E_UP,
    E_RIGHT,
    E_DOWN,
    E_MAX_MOVES
} E_Move_Type;

typedef struct
{
    /*  Represents current board state of 2 dimensional puzzle. Each tile is
        represent with a positive integer starting at 1.
        A tile at board[i][j] is at row i and column j.
        Blank tile is represented by D_BLANK_TILE and displayed as '_'.
    */
    int state[D_MAX][D_MAX];
    int d;                      /* Dimension of the square Board. */
    int blank_r;                /* Row index of the blank tile. */
    int blank_c;                /* Column index of the blank tile. */
} Board_Type;

/*
|------------------------------------------------------------------------------
| DATA
|------------------------------------------------------------------------------
*/

/* The game board */
Board_Type Board;

/*
|------------------------------------------------------------------------------
| PROTOTYPE
|------------------------------------------------------------------------------
*/

/* Initialize board to a random state. */
void Board_Init(void);

void Clear(void);

/* 
    Swaps the tiles at the specified location.
*/
void Board_Move_Tile(int src_r, int src_c, int dest_r, int dest_c);

/*
    Swap the blank tile with an adjacent tile of the specified direction.
*/
void Board_Move_Direction(E_Move_Type direction);

/* Move the specified tile on the board.

   Returns:
    - false     : when specified tile is not next to the blank tile.
    - true      : when move was successful.
*/
bool Board_Move(int tile);

/* Prints current board state to screen. */
void Board_Update_Display(void);
void Board_Draw_Boarder(void);
bool Won(int* state);

void At_Exit();

/*
|------------------------------------------------------------------------------
| FUNCTION
|------------------------------------------------------------------------------
*/

int main(void)
{
    int tile_to_move;
    char command[5];

    cout << "\nWelcome to play the puzzle game.\n\n";
    cout << "Game commands:" << endl;
    cout << "\t- exit: exits the application." << endl;
    cout << "\t- solve: solves the puzzle.\n\n";

    do
    {
        cout << "To play, enter board dimension [" << D_MIN << ", " << D_MAX << "]: ";
        cin >> Board.d;
    } while (Board.d < D_MIN || Board.d > D_MAX);

    Board_Init();

    while (!Won(&Board.state[0][0]))
    {
        Board_Update_Display();

        cout << "Enter command or tile to move: ";
        cin >> command;

        if (strcmp(command, "exit") == 0)
        {
            return 0;
        }
        else if (strcmp(command, "solve") == 0)
        {
            //TODO
        }
        else
        {
            tile_to_move = atoi(command);
            if (atoi > 0)
                Board_Move(tile_to_move);
        }
    }

    Board_Update_Display();
    cout << "Game Won!" << endl;
    return 0;
}

void Board_Init(void)
{
    E_Move_Type move;
    
    /* Initialize the Board to the Won/complete state. */
    for (int i = 0; i < Board.d; ++i)
    {
        for (int j = 0; j < Board.d; ++j)
        {
            Board.state[i][j] = i*Board.d+j+1;
        }
    }
    Board.state[Board.d-1][Board.d-1] = D_BLANK_TILE;
    Board.blank_r = Board.d-1;
    Board.blank_c = Board.d-1;

    /* Make random moves to put the board in a random state. */
    for (int i = 0; i < 100; ++i)
    {
        move = (E_Move_Type)((rand() + time(NULL)) % 4); 
        Board_Move_Direction(move);
    }
}

void Board_Move_Tile(int src_r, int src_c, int dest_r, int dest_c)
{
    Board.state[dest_r][dest_c] = Board.state[src_r][src_c];
    Board.state[src_r][src_c] = D_BLANK_TILE;
}

void Board_Move_Direction(E_Move_Type direction)
{
    
    switch (direction)
    {
        case E_LEFT:
            if (Board.blank_c > 0)
            {
                Board_Move_Tile(Board.blank_r, Board.blank_c-1, Board.blank_r, Board.blank_c);
                Board.blank_c -= 1;
                break;
            }
        case E_UP:
            if (Board.blank_r > 0)
            {
                Board_Move_Tile(Board.blank_r-1, Board.blank_c, Board.blank_r, Board.blank_c);
                Board.blank_r -= 1;
                break;
            }
        case E_RIGHT:
            if (Board.blank_c < Board.d-1)
            {
                Board_Move_Tile(Board.blank_r, Board.blank_c+1, Board.blank_r, Board.blank_c);
                Board.blank_c += 1;
                break;
            }
        case E_DOWN:
        default:
            if (Board.blank_r < Board.d-1)
            {
                Board_Move_Tile(Board.blank_r+1, Board.blank_c, Board.blank_r, Board.blank_c);
                Board.blank_r += 1;
            }
        break;
    }
}

bool Board_Move(int tile)
{
    if (tile < 1 || tile >= Board.d*Board.d)
    {
        cout << "\n   >>> Invalid tile!   <<<\n" << endl;
        usleep(1500000);
        return false;
    }

    for (int i = 0; i < Board.d; ++i)
    {
        for (int j = 0; j < Board.d; ++j)
        {
            if (Board.state[i][j] == tile)    // found tile in Board
            {
                // left
                if ((j > 0) && (Board.state[i][j-1] == D_BLANK_TILE))
                {
                    Board_Move_Tile(i, j, i, j-1);
                    Board.blank_c -= 1;
                    return true;
                }
                // up
                else if ((i > 0) && (Board.state[i-1][j] == D_BLANK_TILE))
                {
                    Board_Move_Tile(i, j, i-1, j);
                    Board.blank_r -= 1;
                    return true;
                }
                // right
                else if ((j < (Board.d-1)) && (Board.state[i][j+1] == D_BLANK_TILE))
                {
                    Board_Move_Tile(i, j, i, j+1);
                    Board.blank_c += 1;
                    return true;
                }
                // down
                else if ((i < (Board.d-1)) && (Board.state[i+1][j] == D_BLANK_TILE))
                {
                    Board_Move_Tile(i, j, i+1, j);
                    Board.blank_r += 1;
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    }

    return false;
}

void Clear(void)
{
    /* ANSI Escape sequence to clear display console. */
    cout << "\033[2J";      /* Clear screen and home cursor. */
    cout << "\033[0;0H";    /* Move cursor to line 0 and column 0. */
}

void Board_Draw_Boarder(void)
{
    cout << "    ";
    for (int i = 0; i < Board.d; ++i)
    {
        cout << "-----";
    }
    cout << "-\n";
}

void Board_Update_Display(void)
{
    Clear();
    
    /* Print header */
    cout << " ";    /* set graphics rendition - green background.*/
    for (int i = 0; i < Board.d; ++i)
        cout << "  ";
    cout << "\033[0;01;42mPuzzle Game\033[0m" << endl;

    Board_Draw_Boarder();
    for (int i = 0; i < Board.d; ++i)
    {
        printf("    |");
        for (int j = 0; j < Board.d; ++j)
        {
            if (Board.state[i][j] < 10)
                cout << " ";

            if (Board.state[i][j] == -1)
                cout << " " << D_BLANK_CHAR << " |";
            else
                cout << " " << Board.state[i][j] << " |";
        }
        cout << endl;
        Board_Draw_Boarder();
    }
}

bool Won(int* state)
{
    for (int i = 0; i < Board.d-1; ++i)
    {
        for (int j = 0; j < Board.d; ++j)
        {
            if (state[i*D_MAX+j] != (i*Board.d + j + 1))
                return false;
        }
    }

    for (int j = 0; j < Board.d-1; ++j)
    {
        if (state[(Board.d-1)*D_MAX+j] != ((Board.d-1)*Board.d + j + 1))
            return false;
    }

    return true;
}
