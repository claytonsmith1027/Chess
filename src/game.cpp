#include "string"
#include "vector"
#include <iostream>

const int BOARD_SIZE = 8;
bool isWhitesTurn = true;
std::string lastMove = "";

// starting board position with lowercase letters representing black pieces and uppercase characters representing white pieces, empty squares represented by 0
char board[BOARD_SIZE * BOARD_SIZE] = { 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r',
                                        'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
                                        '0', '0', '0', '0', '0', '0', '0', '0',
                                        '0', '0', '0', '0', '0', '0', '0', '0',
                                        '0', '0', '0', '0', '0', '0', '0', '0',
                                        '0', '0', '0', '0', '0', '0', '0', '0',
                                        'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
                                        'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};

void printBoard(){
    for(int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++){
        if((i + 1) % 8 == 1){
            std::cout << std::endl;
        }
        std::cout << board[i] << " "; 
    }
    std::cout << std::endl;
}

char* currBoard(){
    return board;
}

void updateBoard(int startingIndex, int newIndex){
    if(startingIndex != newIndex){
        if(!isWhitesTurn && board[startingIndex] == 'P' && (startingIndex - newIndex) % 8 != 0 && board[newIndex] == '0'){
            // this can only happen if a white pawn is taking en passant
            board[newIndex + 8] = '0';
        }
        if(isWhitesTurn && board[startingIndex] == 'p' && (startingIndex - newIndex) % 8 != 0 && board[newIndex] == '0'){
            // this can only happen if a black pawn is taking en passant
            board[newIndex - 8] = '0';
        }
        board[newIndex] = board[startingIndex];
        board[startingIndex] = '0';
    }
}

void changePlayer(){
    isWhitesTurn = !isWhitesTurn;
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

void updateLastMove(int startingIndex, int newIndex){
    char startCol = 'a' + startingIndex % 8;
    char startRow = '8' - startingIndex / 8;
    char newCol = 'a' + newIndex % 8;
    char newRow = '8' - newIndex / 8;

    lastMove = startCol;
    lastMove += startRow;
    lastMove += newCol;
    lastMove += newRow;
}

int lastMoveStartIndex(){
    int col = lastMove[0] - 'a';
    int row = '8' - lastMove[1];
    return row * 8 + col;
}

int lastMoveEndIndex(){
    int col = lastMove[2] - 'a';
    int row = '8' - lastMove[3];
    return row * 8 + col;
}

std::vector<int> legalDiagIndexes(int startingIndex){
    std::vector<int> legalIndexes(13, -1);
    // legalIndexes.resize(13); // 13 is the max number of squares that a piece can see diagonally
    int index;
    int row;
    int col;

    if(isPieceWhite(startingIndex) != isWhitesTurn){
        return legalIndexes; 
    }
    

    // check up right
    index = startingIndex;
    row  = startingIndex / 8;
    col = startingIndex % 8;
    index -= 7;
    while(row > 0 && col < 7 && board[index] == '0' && index % 8 != 0){
        legalIndexes.push_back(index);
        index -= 7;
        row--;
        col++;
    }
    if(row > 0 && col < 7){
        if(board[index] != '0' && isPieceWhite(index) != isWhitesTurn){
            legalIndexes.push_back(index);
        }
    }

    // check up left
    index = startingIndex;
    row  = startingIndex / 8;
    col = startingIndex % 8;
    index -= 9;
    while(row > 0 && col > 0 && board[index] == '0' && index % 7 != 0){
        legalIndexes.push_back(index);
        index -= 9;
        row--;
        col--;
    }
    if(row > 0 && col > 0){
        if(board[index] != '0' && isPieceWhite(index) != isWhitesTurn){
            legalIndexes.push_back(index);
        }
    }
    
    // check down right
    index = startingIndex;
    row  = startingIndex / 8;
    col = startingIndex % 8;
    index += 9;
    while(row < 7 && col < 7 && board[index] == '0' && index % 8 != 0){
        legalIndexes.push_back(index);
        index += 9;
        row++;
        col++;
    }
    if(row < 7 && col < 7){
        if(board[index] != '0' && isPieceWhite(index) != isWhitesTurn){
            legalIndexes.push_back(index);
        }
    }

    // check down left
    index = startingIndex;
    row  = startingIndex / 8;
    col = startingIndex % 8;
    index += 7;
    while(row < 7 && col > 0 && board[index] == '0' && index % 7 != 0){
        legalIndexes.push_back(index);
        index += 7;
        row++;
        col--;
    }
    if(row < 7 && col > 0){
        if(board[index] != '0' && isPieceWhite(index) != isWhitesTurn){
            legalIndexes.push_back(index);
        }
    }

    return legalIndexes;
}

std::vector<int> legalCardinalIndexes(int startingIndex){
    std::vector<int> legalIndexes(14, -1);
    legalIndexes.resize(14); // 14 is the max number of squares that a piece can see cardinally

    if(isPieceWhite(startingIndex) != isWhitesTurn){
        return legalIndexes; 
    }

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
    
    if(isPieceWhite(startingIndex) != isWhitesTurn){
        return legalIndexes; 
    }
    
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

std::vector<int> legalPawnIndexes(int startingIndex){
    bool isWhitePiece = isPieceWhite(startingIndex);
    bool hasMoved;
    int col = startingIndex % 8; 
    std::vector<int> legalIndexes(4, -1);
    
    if(isPieceWhite(startingIndex) != isWhitesTurn){
        return legalIndexes; 
    }

    if((startingIndex < 16 && !isWhitePiece) || (startingIndex > 47 && isWhitePiece)){
        hasMoved = false;
    }
    else{
        hasMoved = true;
    }
    
    if(isWhitePiece){
        //handle fowards movement including double move
        if(board[startingIndex - 8] == '0'){
            legalIndexes.push_back(startingIndex - 8);
            if(!hasMoved && board[startingIndex - 16] == '0'){
                legalIndexes.push_back(startingIndex - 16);
            }
        }
        //handle captures excluding en passant
        if(col != 0 && board[startingIndex - 9] != '0' && !isPieceWhite(startingIndex - 9)){
            legalIndexes.push_back(startingIndex - 9);
        }
        if(col != 7 && board[startingIndex - 7] != '0' && !isPieceWhite(startingIndex - 7)){
            legalIndexes.push_back(startingIndex - 7);
        }
        //handle en passant captures
        int prevStartIndex = lastMoveStartIndex();
        int prevEndIndex = lastMoveEndIndex();
        if(col != 0 && board[startingIndex - 1] == 'p'){
            // a pawn directly next to another pawn can be taken en passant only on the very next turn and only if that pawn moved two squares on the previous turn
            if(startingIndex - 1 == prevEndIndex && prevEndIndex - prevStartIndex == 16){
                legalIndexes.push_back(startingIndex - 9);
            }
        }
        else if(col != 7 && board[startingIndex + 1] == 'p'){
            if(startingIndex + 1 == prevEndIndex && prevEndIndex - prevStartIndex == 16){
                legalIndexes.push_back(startingIndex - 7);
            }
        }
    }

    else{
        //handle fowards movement including double move
        if(board[startingIndex + 8] == '0'){
            legalIndexes.push_back(startingIndex + 8);
            if(!hasMoved && board[startingIndex + 16] == '0'){
                legalIndexes.push_back(startingIndex + 16);
            }
        }
        //handle captures excluding en passant
        if(col != 0 && board[startingIndex + 9] != '0' && isPieceWhite(startingIndex + 9)){
            legalIndexes.push_back(startingIndex + 9);
        }
        if(col != 7 && board[startingIndex + 7] != '0' && isPieceWhite(startingIndex + 7)){
            legalIndexes.push_back(startingIndex + 7);
        }
        //handle en passant captures
        int prevStartIndex = lastMoveStartIndex();
        int prevEndIndex = lastMoveEndIndex();
        if(col != 0 && board[startingIndex + 1] == 'P'){
            // a pawn directly next to another pawn can be taken en passant only on the very next turn and only if that pawn moved two squares on the previous turn
            if(startingIndex + 1 == prevEndIndex && prevStartIndex - prevEndIndex == 16){
                legalIndexes.push_back(startingIndex + 9);
            }
        }
        else if(col != 7 && board[startingIndex - 1] == 'P'){
            if(startingIndex - 1 == prevEndIndex && prevStartIndex - prevEndIndex == 16){
                legalIndexes.push_back(startingIndex + 7);
            }
        }
    }
    return legalIndexes;
}

std::vector<int> legalKingIndexes(int startingIndex){
    int startRow = startingIndex / 8;
    int startCol = startingIndex % 8;

    std::vector<int> legalIndexes(8, -1);
    
    if(isPieceWhite(startingIndex) != isWhitesTurn){
        return legalIndexes; 
    }
    
    legalIndexes[0] = startingIndex - 9;
    legalIndexes[1] = startingIndex - 8;
    legalIndexes[2] = startingIndex - 7;
    legalIndexes[3] = startingIndex - 1;
    legalIndexes[4] = startingIndex + 1;
    legalIndexes[5] = startingIndex + 7;
    legalIndexes[6] = startingIndex + 8;
    legalIndexes[7] = startingIndex + 9;

    // castling not implemented
    for(int i = 0; i < legalIndexes.size(); i++){
        if(board[legalIndexes[i]] != '0' && isPieceWhite(legalIndexes[i]) == isWhitesTurn){
            legalIndexes[i] = -1;
        }
    }

    if(startCol == 0){
        legalIndexes[0] = -1;
        legalIndexes[3] = -1;
        legalIndexes[5] = -1;
    }
    else if(startCol == 7){
        legalIndexes[2] = -1;
        legalIndexes[4] = -1;
        legalIndexes[7] = -1;
    }
    if(startRow == 0){
        legalIndexes[0] = -1;
        legalIndexes[1] = -1;
        legalIndexes[2] = -1;
    }
    else if(startRow == 7){
        legalIndexes[5] = -1;
        legalIndexes[6] = -1;
        legalIndexes[7] = -1;
    }

    return legalIndexes;
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


std::vector<int> getLegalIndexes(int startingIndex){
    std::vector<int> indexes;
    std::vector<int> pawnIndexes = legalPawnIndexes(startingIndex);
    std::vector<int> knightIndexes = legalKnightIndexes(startingIndex);
    std::vector<int> rookIndexes = legalCardinalIndexes(startingIndex);
    std::vector<int> bishopIndexes = legalDiagIndexes(startingIndex);
    std::vector<int> kingIndexes = legalKingIndexes(startingIndex);

    switch(board[startingIndex]){
        case 'P':
        case 'p':
            indexes.insert(indexes.end(), pawnIndexes.begin(), pawnIndexes.end());
            break;
        case 'B':
        case 'b':
            indexes.insert(indexes.end(), bishopIndexes.begin(), bishopIndexes.end());
            break;
        case 'N':
        case 'n':
            indexes.insert(indexes.end(), knightIndexes.begin(), knightIndexes.end());
            break;
        case 'K':
        case 'k':
            indexes.insert(indexes.end(), kingIndexes.begin(), kingIndexes.end());
            break;
        case 'R':
        case 'r':
            indexes.insert(indexes.end(), rookIndexes.begin(), rookIndexes.end());
            break;
        case 'Q':
        case 'q':
            indexes.insert(indexes.end(), bishopIndexes.begin(), bishopIndexes.end());
            indexes.insert(indexes.end(), rookIndexes.begin(), rookIndexes.end());
            break;
    }
    return indexes;
} 

bool isLegalMove(int startingIndex, int newIndex){
    bool isWhitePiece = isPieceWhite(startingIndex);

    // handle playing wrong color piece
    if((isWhitePiece && !isWhitesTurn) || (!isWhitePiece && isWhitesTurn)){
        return false;
    }

    std::vector<int> allLegalIndexes = getLegalIndexes(startingIndex); 
    for(int i = 0; i < allLegalIndexes.size(); i++){
        if(allLegalIndexes.at(i) == newIndex){
            updateLastMove(startingIndex, newIndex);
            changePlayer();
            return true;
        }
    }
    return false;
}