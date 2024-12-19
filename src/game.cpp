#include "string"

const int BOARD_SIZE = 8;

// starting board position with lowercase letters representing black pieces and uppercase characters representing white pieces, empty squares represented by 0
char board[BOARD_SIZE * BOARD_SIZE] = { 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r',
                                        'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
                                        '0', '0', '0', '0', '0', '0', '0', '0',
                                        '0', '0', '0', '0', '0', '0', '0', '0',
                                        '0', '0', '0', '0', '0', '0', '0', '0',
                                        '0', '0', '0', '0', '0', '0', '0', '0',
                                        'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
                                        'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};

char* currBoard(){
    return board;
}