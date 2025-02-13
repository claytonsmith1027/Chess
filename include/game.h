#pragma once

#include <iostream>
#include <vector>

const int BOARD_SIZE = 8;
const std::string STARTING_BOARD_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"; 

void printBoard();

bool isInBounds(int x, int y);
char* currBoard();
bool isWhitePiece(int startRow, int startCol);
bool isPathClear(int startRow, int startCol, int endRow, int endCol);
int abs(int input);
void updateLastMove(int startRow, int startCol, int endRow, int endCol);
bool canEnPassant(int startRow, int startCol, int endRow, int endCol);
bool isPromotion(int endRow, int endCol);
bool isAttacked(int row, int column);
bool canCastle(int startRow, int startCol, int endRow, int endCol);
void castleKing(int startRow, int startCol, int endRow, int endCol);
int legalMovesCount();
bool isNoLegalMoves();

bool isValidPawnMove(int startRow, int startCol, int endRow, int endCol);
bool isValidRookMove(int startRow, int startCol, int endRow, int endCol);
bool isValidKnightMove(int startRow, int startCol, int endRow, int endCol);
bool isValidBishopMove(int startRow, int startCol, int endRow, int endCol);
bool isValidQueenMove(int startRow, int startCol, int endRow, int endCol);
bool isValidKingMove(int startRow, int startCol, int endRow, int endCol);
bool isValidPieceMovement(int startRow, int startCol, int endRow, int endCol);
bool isValidMove(int startRow, int startCol, int endRow, int endCol);

void switchPlayer();
void movePiece(int startRow, int startCol, int endRow, int endCol);
void promotePiece(int endRow, int endCol, char piece);
void playMove(int startRow, int startCol, int endRow, int endCol);

bool isCheckmate();
bool isStalemate();

std::vector<int> getValidIndexes(int startRow, int startCol);
void loadBoardFromFEN(std::string fen);
void resetGame();
