#include "string"
#include "vector"
#include <iostream>

const int BOARD_SIZE = 8;
bool isWhitesTurn = true;

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

void changePlayer(){
    isWhitesTurn = !isWhitesTurn;
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

bool isPieceWhite(int index){
    if(board[index] >= 'A' && board[index]  <= 'Z'){
        // std::cout << "piece is white" << std::endl;
        return true;
    }
    else{
        // std::cout << "piece is black" << std::endl;
        return false;
    }
}

std::vector<int> legalDiagIndexes(int startingIndex){
    std::vector<int> legalIndexes(13, -1);
    // legalIndexes.resize(13); // 13 is the max number of squares that a piece can see diagonally
    int index;

    // check up right
    index = startingIndex;
    index -= 7;
    while(index >= 0 && board[index] == '0' && index % 8 != 0){
        legalIndexes.push_back(index);
        index -= 7;
    }
    if(index >= 0){
        if(board[index] != '0' && isPieceWhite(index) != isWhitesTurn){
            legalIndexes.push_back(index);
        }
    }

    // check up left
    index = startingIndex;
    index -= 9;
    while(index >= 0 && board[index] == '0' && (index + 1) % 8 != 0){
        legalIndexes.push_back(index);
        index -= 9;
    }
    if(index >= 0){
        if(board[index] != '0' && isPieceWhite(index) != isWhitesTurn){
            legalIndexes.push_back(index);
        }
    }
    
    // check down right
    index = startingIndex;
    index += 9;
    while(index <= 63 && board[index] == '0' && index % 8 != 0){
        legalIndexes.push_back(index);
        index += 9;
    }
    if(index <= 63){
        if(board[index] != '0' && isPieceWhite(index) != isWhitesTurn){
            legalIndexes.push_back(index);
        }
    }

    // check down left
    index = startingIndex;
    index += 7;
    while(index <= 63 && board[index] == '0' && (index + 1) % 8 != 0){
        legalIndexes.push_back(index);
        index += 7;
    }
    if(index <= 63){
        if(board[index] != '0' && isPieceWhite(index) != isWhitesTurn){
            legalIndexes.push_back(index);
        }
    }

    return legalIndexes;
}

std::vector<int> legalCardinalIndexes(int startingIndex){
    std::vector<int> legalIndexes(14, -1);
    legalIndexes.resize(14); // 14 is the max number of squares that a piece can see cardinally
    int index;

    // check up
    index = startingIndex;
    index -= 8;
    while(index >= 0 && board[index] == '0'){
        legalIndexes.push_back(index);
        index -= 8;
    }
    if(index >= 0){
        if(isPieceWhite(index) != isWhitesTurn){
            legalIndexes.push_back(index);
        }
    }

    // check down
    index = startingIndex;
    index += 8;
    while(index <= 63 && board[index] == '0'){
        legalIndexes.push_back(index);
        index += 8;
    }
    if(index <= 63){
        if(isPieceWhite(index) != isWhitesTurn){
            legalIndexes.push_back(index);
        }
    }

    // check left
    index = startingIndex;
    index -= 1;
    while(index >= startingIndex - startingIndex % 8 && board[index] == '0'){
        legalIndexes.push_back(index);
        index -= 1;
    }
    if(index >= startingIndex - startingIndex % 8){
        if(isPieceWhite(index) != isWhitesTurn){
            legalIndexes.push_back(index);
        }
    }

    // check right
    index = startingIndex;
    index += 1;
    while(index % 8 != 0 && board[index] == '0'){
        legalIndexes.push_back(index);
        index += 1;
    }
    if(index % 8 != 0){
        if(isPieceWhite(index) != isWhitesTurn){
            legalIndexes.push_back(index);
        }
    }

    return legalIndexes;
}

std::vector<int> legalKnightIndexes(int startingIndex){
    int startRow = startingIndex / 8;
    int startCol = startingIndex % 8;

    std::vector<int> legalIndexes(8, -1);
    legalIndexes[0] = startingIndex - 17;
    legalIndexes[1] = startingIndex - 15;
    legalIndexes[2] = startingIndex - 10;
    legalIndexes[3] = startingIndex - 6;
    legalIndexes[4] = startingIndex + 17;
    legalIndexes[5] = startingIndex + 15;
    legalIndexes[6] = startingIndex + 10;
    legalIndexes[7] = startingIndex + 6;

    for(int i = 0; i < legalIndexes.size(); i++){
        if(legalIndexes[i] > 63 || legalIndexes[i] < 0){
            legalIndexes[i] = -1;
            continue;
        }
        if(board[legalIndexes[i]] != '0' && isPieceWhite(legalIndexes[i]) == isWhitesTurn){
            legalIndexes[i] = -1;
            continue;
        }
        int newRow = legalIndexes[i] / 8;
        int newCol = legalIndexes[i] % 8;
        if(startRow == newRow || startRow - newRow > 2 || startRow - newRow < -2 || startCol - newCol > 2 || startCol - newCol < -2){
            legalIndexes[i] = -1;
            continue;
        }
        int rowDelta;
        if(startRow - newRow > 0){
            rowDelta = startRow - newRow;
        }
        else{
            rowDelta = newRow - startRow;
        }
        int colDelta;
        if(startCol - newCol > 0){
            colDelta = startCol - newCol;
        }
        else{
            colDelta = newCol - startCol;
        }

        if(rowDelta + colDelta != 3){
            legalIndexes[i] = -1;
        }
    }
    
    return legalIndexes;
}

bool pawnMove(int startIndex, int newIndex){
    bool isWhitePiece = isPieceWhite(startIndex);
    bool hasMoved;

    // handle playing wrong color piece
    if((isWhitePiece && !isWhitesTurn) || (!isWhitePiece && isWhitesTurn)){
        return false;
    }

    // handle single move case
    if((startIndex - newIndex == 8 && isWhitePiece) || (newIndex - startIndex == 8 && !isWhitePiece))
    {
        if((board[startIndex - 8] == '0' && isWhitePiece) || (board[startIndex + 8] == '0' && !isWhitePiece)){
            return true;
        }
        return false;
    }

    // handle double move case
    if((startIndex < 16 && !isWhitePiece) || (startIndex > 47 && isWhitePiece)){
        hasMoved = false;
    }
    else{
        hasMoved = true;
    }
    if((startIndex - newIndex == 16 && isWhitePiece) || (newIndex - startIndex == 16 && !isWhitePiece)){
        if(!hasMoved){
            if(isWhitePiece && board[startIndex - 8] == '0' && board[startIndex - 16] == '0'){
                return true;
            }
            else if(!isWhitePiece && board[startIndex + 8] == '0' && board[startIndex + 16] == '0'){
                return true;
            }
        }
        return false;
    }

    //handle captures excluding en passant
    if((isWhitePiece && ((startIndex - newIndex == 7 && startIndex % 8 != 0) || (startIndex - newIndex == 9 && (startIndex + 1) % 8 != 0)))){
        if(board[newIndex] == '0' || isPieceWhite(newIndex) == isWhitePiece){
            return false;
        }
        else{
            return true;
        }
    }
    if((!isWhitePiece && ((newIndex - startIndex == 7 && (startIndex + 1) % 8 != 0 ) || (newIndex - startIndex == 9 && startIndex % 8 != 0)))){
        if(board[newIndex] == '0' || isPieceWhite(newIndex) == isWhitePiece){
            return false;
        }
        else{
            return true;
        }
    }
    return false; //temp
}

bool isPromotion(int index, char piece){
    if((index < 8 && piece == 'P') || (index > 55 && piece == 'p')){
        return true;
    }
    else{
        return false;
    }
}

void promotePawn(int index, char newPiece){
    board[index] = newPiece;
}

bool bishopMove(int startIndex, int newIndex){
    bool isWhitePiece = isPieceWhite(startIndex);

    // handle playing wrong color piece
    if((isWhitePiece && !isWhitesTurn) || (!isWhitePiece && isWhitesTurn)){
        return false;
    }

    std::vector<int> legalIndexes = legalDiagIndexes(startIndex);
    for(size_t i = 0; i < legalIndexes.size(); i++){
        if(legalIndexes.at(i) == newIndex){
            return true;
        }
    }
    return false;
}

bool knightMove(int startIndex, int newIndex){
    bool isWhitePiece = isPieceWhite(startIndex);

    // handle playing wrong color piece
    if((isWhitePiece && !isWhitesTurn) || (!isWhitePiece && isWhitesTurn)){
        return false;
    }

    std::vector<int> legalIndexes = legalKnightIndexes(startIndex);
    for(size_t i = 0; i < legalIndexes.size(); i++){
        if(legalIndexes.at(i) == newIndex){
            return true;
        }
    }
    return false;
}

bool kingMove(int startIndex, int newIndex){
    bool isWhitePiece = isPieceWhite(startIndex);

    // handle playing wrong color piece
    if((isWhitePiece && !isWhitesTurn) || (!isWhitePiece && isWhitesTurn)){
        return false;
    }

    return true; //temp
}

bool rookMove(int startIndex, int newIndex){
    bool isWhitePiece = isPieceWhite(startIndex);

    // handle playing wrong color piece
    if((isWhitePiece && !isWhitesTurn) || (!isWhitePiece && isWhitesTurn)){
        return false;
    }

    std::vector<int> legalIndexes = legalCardinalIndexes(startIndex);
    for(size_t i = 0; i < legalIndexes.size(); i++){
        if(legalIndexes.at(i) == newIndex){
            return true;
        }
    }
    return false;
}

bool queenMove(int startIndex, int newIndex){
    bool isWhitePiece = isPieceWhite(startIndex);
    
    // handle playing wrong color piece
    if((isWhitePiece && !isWhitesTurn) || (!isWhitePiece && isWhitesTurn)){
        return false;
    }

    std::vector<int> legalDiagIndexesVect = legalDiagIndexes(startIndex);
    std::vector<int> legalCardinalIndexesVect = legalCardinalIndexes(startIndex);
    std::vector<int> legalIndexes = legalDiagIndexesVect;
    legalIndexes.insert(legalIndexes.end(), legalCardinalIndexesVect.begin(), legalCardinalIndexesVect.end());
    for(size_t i = 0; i < legalIndexes.size(); i++){
        if(legalIndexes.at(i) == newIndex || legalIndexes.at(i) == newIndex){
            return true;
        }
    }
    return false;
}

bool isLegalMove(int startIndex, int newIndex){
    bool isLegal = false;
    switch(board[startIndex]){
        case 'P':
        case 'p':
            isLegal = pawnMove(startIndex, newIndex);
            break;
        case 'B':
        case 'b':
            isLegal = bishopMove(startIndex, newIndex);
            break;
        case 'N':
        case 'n':
            isLegal = knightMove(startIndex, newIndex);
            break;
        case 'K':
        case 'k':
            isLegal = kingMove(startIndex, newIndex);
            break;
        case 'R':
        case 'r':
            isLegal = rookMove(startIndex, newIndex);
            break;
        case 'Q':
        case 'q':
            isLegal = queenMove(startIndex, newIndex);
            break;
    }
    if(isLegal){
        changePlayer();
    }
    return isLegal;
}