#include <vector>
#include "game.h"

// Board definition
char board[BOARD_SIZE][BOARD_SIZE];

bool isWhitesTurn = true;
int lastMove[4] = {-1, -1, -1, -1}; // {startRow, startCol, endRow, endCol}
int whiteKingRow = 7;
int whiteKingCol = 4;
int blackKingRow = 0;
int blackKingCol = 4;
bool canWhiteShortCastle = true;
bool canWhiteLongCastle = true;
bool canBlackShortCastle = true;
bool canBlackLongCastle = true;


//debug functions
void printBoard() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            std::cout << board[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}

// helper functions
bool isInBounds(int row, int col) {
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

char* currBoard(){
    return board[0];
}

bool isWhitePiece(int startRow, int startCol){
    if(board[startRow][startCol] >= 'A' && board[startRow][startCol]  <= 'Z'){
        return true;
    }
    else{
        return false;
    }
}

bool isPathClear(int startRow, int startCol, int endRow, int endCol) {
    int dRow = (endRow > startRow) - (endRow < startRow);
    int dCol = (endCol > startCol) - (endCol < startCol);

    int r = startRow + dRow;
    int c = startCol + dCol;
    while (r != endRow || c != endCol) {
        if (board[r][c] != '0') return false;
        r += dRow;
        c += dCol;
    }
    return true;
}

int abs(int input){
    if(input < 0){
        return -input;
    }
    else{
        return input;
    }
}

void updateLastMove(int startRow, int startCol, int endRow, int endCol){
    lastMove[0] = startRow;
    lastMove[1] = startCol;
    lastMove[2] = endRow;
    lastMove[3] = endCol;
}

bool canEnPassant(int startRow, int startCol, int endRow, int endCol){
    if((isWhitesTurn && board[lastMove[2]][lastMove[3]] == 'p') || (!isWhitesTurn && board[lastMove[2]][lastMove[3]] == 'P')){
        if(startRow == lastMove[2] && lastMove[3] == endCol){
            if(abs(lastMove[2] - lastMove[0]) == 2){
                return true;
            }
        }
    }
    return false;
}

bool isPromotion(int endRow, int endCol){
    if((board[endRow][endCol] == 'p' && endRow == 7) || (board[endRow][endCol] == 'P' && endRow == 0)){
        return true;
    }
    return false;
}

bool isAttacked(int row, int column){
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            if(board[i][j] != '0' && isWhitePiece(i, j) != isWhitesTurn){
                switchPlayer();
                if(board[i][j] == 'p' || board[i][j] == 'P'){
                    if(j != column && isValidPieceMovement(i, j, row, column)){
                        switchPlayer();
                        return true;
                    }
                }
                else if(isValidPieceMovement(i, j, row, column)){
                    switchPlayer();
                    return true;
                }
                switchPlayer();
            }
        }
    }
    return false;
}

bool canCastle(int startRow, int startCol, int endRow, int endCol){
    bool canShortCastle = canWhiteShortCastle;
    bool canLongCastle = canWhiteLongCastle;
    int castleRow = 7;

    if(board[startRow][startCol] != 'k' && board[startRow][startCol] != 'K'){
        return false;
    }

    if(!isWhitesTurn){
        canShortCastle = canBlackLongCastle;
        canLongCastle = canBlackShortCastle;
        castleRow = 0;
    }

    if(startRow != endRow || endRow != castleRow){
        return false;
    }

    if(endCol == 7 || endCol == 6){
        if(!canShortCastle || isAttacked(castleRow, 6) || isAttacked(castleRow, 5) || isAttacked(castleRow, 4)){
            return false;
        }
    }
    else if(endCol == 0 || endCol == 1 || endCol == 2){
        if(!canLongCastle || isAttacked(castleRow, 1) || isAttacked(castleRow, 2) || isAttacked(castleRow, 3) || isAttacked(castleRow, 4)){
            return false;
        }
    }
    else{
        return false;
    }
    if(isPathClear(startRow, startCol, endRow, endCol)){
        return true;
    }
    return false;
}

void castleKing(int startRow, int startCol, int endRow, int endCol){
    if(endCol > 5){
        board[startRow][6] = board[startRow][startCol];
        movePiece(startRow, 7, endRow, 5);
        board[startRow][startCol] = '0';
        if(isWhitesTurn){
            whiteKingCol = 6;
        }
        else{
            blackKingCol = 6;
        }
    }
    else{
        board[startRow][2] = board[startRow][startCol];
        movePiece(startRow, 0, endRow, 3);
        board[startRow][startCol] = '0';
        if(isWhitesTurn){
            whiteKingCol = 2;
        }
        else{
            blackKingCol = 2;
        }
    }
}

// piece rules functions
bool isValidPawnMove(int startRow, int startCol, int endRow, int endCol){
    char pawn = board[startRow][startCol];
    int direction = -1;
    int pawnStartRow = 6;
    if(pawn == 'p'){
        direction = 1;
        pawnStartRow = 1;
    }
    char target = board[endRow][endCol];
    if (endCol == startCol && endRow == startRow + direction && target == '0') {
        return true;
    }
    if (endCol == startCol && endRow == startRow + 2 * direction && startRow == pawnStartRow &&
        target == '0' && board[startRow + direction][startCol] == '0') {
        return true;
    }
    if (abs(endCol - startCol) == 1 && endRow == startRow + direction) {
        if (isWhitePiece(startRow, startCol) != isWhitePiece(endRow, endCol) && target != '0'){ 
            return true;
        }
        if (target == '0' && canEnPassant(startRow, startCol, endRow, endCol)) {
            return true;
        }
    }
    return false;
}

bool isValidRookMove(int startRow, int startCol, int endRow, int endCol) {
    return (startRow == endRow || startCol == endCol) && isPathClear(startRow, startCol, endRow, endCol);
}

bool isValidKnightMove(int startRow, int startCol, int endRow, int endCol) {
    int dRow = abs(endRow - startRow);
    int dCol = abs(endCol - startCol);
    return (dRow == 2 && dCol == 1) || (dRow == 1 && dCol == 2);
}

bool isValidBishopMove(int startRow, int startCol, int endRow, int endCol) {
    return abs(endRow - startRow) == abs(endCol - startCol) && isPathClear(startRow, startCol, endRow, endCol);
}

bool isValidQueenMove(int startRow, int startCol, int endRow, int endCol) {
    return isValidRookMove(startRow, startCol, endRow, endCol) || isValidBishopMove(startRow, startCol, endRow, endCol);
}

bool isValidKingMove(int startRow, int startCol, int endRow, int endCol) {
    return abs(endRow - startRow) <= 1 && abs(endCol - startCol) <= 1 || canCastle(startRow, startCol, endRow, endCol);
}

bool isValidPieceMovement(int startRow, int startCol, int endRow, int endCol) {
    if((isWhitePiece(startRow, startCol) && !isWhitesTurn) || (!isWhitePiece(startRow, startCol) && isWhitesTurn)){
        return false;
    }
    if(board[endRow][endCol] != '0'){
        if(isWhitesTurn && isWhitePiece(endRow, endCol)){
            return false;
        }
        else if(!isWhitesTurn && !isWhitePiece(endRow, endCol)){
            return false;
        }
    }

    switch(board[startRow][startCol]) {
        case 'P':
        case 'p': 
            return isValidPawnMove(startRow, startCol, endRow, endCol);
        case 'R':
        case 'r':
            return isValidRookMove(startRow, startCol, endRow, endCol);
        case 'N':
        case 'n':
            return isValidKnightMove(startRow, startCol, endRow, endCol);
        case 'B':
        case 'b':
            return isValidBishopMove(startRow, startCol, endRow, endCol);
        case 'Q':
        case 'q':
            return isValidQueenMove(startRow, startCol, endRow, endCol);
        case 'K':
        case 'k':
            return isValidKingMove(startRow, startCol, endRow, endCol);
        default:
            return false;
    }
}

bool isValidMove(int startRow, int startCol, int endRow, int endCol){
    char kingPiece = 'k';
    int kingRow = blackKingRow;
    int kingCol = blackKingCol;
    bool isKingAttacked = false;
    bool isEnPassant = false;

    if(isWhitesTurn){
        kingPiece = 'K';
        kingRow = whiteKingRow;
        kingCol = whiteKingCol;
    }
    
    if(!isValidPieceMovement(startRow, startCol, endRow, endCol)){
        return false;
    }
    else{
        char tempPiece = board[startRow][startCol];
        char tempAttackedPiece = board[endRow][endCol];
        char enPassantPiece;
        board[startRow][startCol] = '0';
        board[endRow][endCol] = tempPiece;
        if(tempPiece == 'k' || tempPiece == 'K'){
            kingRow = endRow;
            kingCol = endCol;
        }
        if(tempPiece == 'p' || tempPiece == 'P'){
            if(canEnPassant(startRow, startCol, endRow, endCol)){
                isEnPassant = true;
                enPassantPiece = board[lastMove[2]][lastMove[3]];
                board[lastMove[2]][lastMove[3]] = '0';
            }
        }
        if(isAttacked(kingRow, kingCol)){
            isKingAttacked = true;  
        }
        board[startRow][startCol] = tempPiece;
        board[endRow][endCol] = tempAttackedPiece;
        if(isEnPassant){
            board[lastMove[2]][lastMove[3]] = enPassantPiece;
        }
        return !isKingAttacked;
    }
}

// game state update functions
void switchPlayer(){
    isWhitesTurn = !isWhitesTurn;
}

void movePiece(int startRow, int startCol, int endRow, int endCol){
    if((board[startRow][startCol] == 'p' || board[startRow][startCol] == 'P') && canEnPassant(startRow, startCol, endRow, endCol)){
        board[lastMove[2]][lastMove[3]] = '0';
    }
    if(board[startRow][startCol] == 'r' || board[endRow][endCol] == 'r'){
        if(startCol == 7){
            canBlackShortCastle = false;
        }
        else if(startCol == 0){
            canBlackLongCastle == false;
        }
    }
    else if(board[startRow][startCol] == 'R' || board[endRow][endCol] == 'R'){
        if(startCol == 7){
            canWhiteShortCastle = false;
        }
        else if(startCol == 0){
            canWhiteLongCastle == false;
        }
    }
    if(board[startRow][startCol] == 'k'){
        blackKingRow = endRow;
        blackKingCol = endCol;
        if(canCastle(startRow, startCol, endRow, endCol)){
            castleKing(startRow, startCol, endRow, endCol);
        }
        else{
            board[endRow][endCol] = board[startRow][startCol];
            board[startRow][startCol] = '0';   
        }
        canBlackLongCastle = false;
        canBlackShortCastle = false;
        return;
    }
    else if(board[startRow][startCol] == 'K'){
        whiteKingRow = endRow;
        whiteKingCol = endCol;
        if(canCastle(startRow, startCol, endRow, endCol)){
            castleKing(startRow, startCol, endRow, endCol);
        }
        else{
            board[endRow][endCol] = board[startRow][startCol];
            board[startRow][startCol] = '0';
        }
        canWhiteLongCastle = false;
        canWhiteShortCastle = false;
        return;
    }
    board[endRow][endCol] = board[startRow][startCol];
    board[startRow][startCol] = '0';
}

void promotePiece(int endRow, int endCol, char piece){
    board[endRow][endCol] = piece;
}

void playMove(int startRow, int startCol, int endRow, int endCol){
    movePiece(startRow, startCol, endRow, endCol);
    updateLastMove(startRow, startCol, endRow, endCol);
    switchPlayer();
}

// external helper functions (i.e. highlighting squares, etc.)
std::vector<int> getValidIndexes(int startX, int startY){
    std::vector<int> validIndexes;
    char piece = board[startY][startX];
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            if(isValidMove(startX, startY, i, j)){
                validIndexes.push_back(i * 8 + j);
            }
        }
    }
    return validIndexes;
}

void loadBoardFromFEN(std::string fen){
    int boardRow = 0;
    int boardCol = 0;
    for(int i = 0; i < fen.length(); i++){
        if(isalpha(fen[i])){
            board[boardRow][boardCol] = fen[i];
            boardCol++;
        }
        else if(isdigit(fen[i])){
            for(int j = 0; j < fen[i] - '0'; j++){
                board[boardRow][boardCol + j] = '0';
            }
            boardCol += fen[i] - '0';
        }
        else{
            boardRow++;
            boardCol = 0;
        }
    }
}

void resetGame(){
    isWhitesTurn = true;
    lastMove[0] = -1;
    lastMove[1] = -1;
    lastMove[2] = -1;
    lastMove[3] = -1;
    whiteKingRow = 7;
    whiteKingCol = 4;
    blackKingRow = 0;
    blackKingCol = 4;
    canWhiteShortCastle = true;
    canWhiteLongCastle = true;
    canBlackShortCastle = true;
    canBlackLongCastle = true;
    loadBoardFromFEN(STARTING_BOARD_FEN);
}