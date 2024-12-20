#include "string"
#include <iostream>

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

void updateBoard(int startIndex, int newIndex){
    if(startIndex != newIndex){
        board[newIndex] = board[startIndex];
        board[startIndex] = '0';
    }
}

void printBoard(){
    for(int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++){
        if((i + 1) % 8 == 1){
            std::cout << std::endl;
        }
        std::cout << board[i] << " "; 
    }
    std::cout << std::endl;
}