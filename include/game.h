#pragma once

#include <iostream>
#include <vector>

const int BOARD_SIZE = 8;

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

bool isValidPawnMove(int startRow, int startCol, int endRow, int endCol);
bool isValidRookMove(int startRow, int startCol, int endRow, int endCol);
bool isValidKnightMove(int startRow, int startCol, int endRow, int endCol);
bool isValidBishopMove(int startRow, int startCol, int endRow, int endCol);
bool isValidQueenMove(int startRow, int startCol, int endRow, int endCol);
bool isValidKingMove(int startRow, int startCol, int endRow, int endCol);
bool isValidPieceMovement(int startRow, int startCol, int endRow, int endCol);
bool isValidMove(int startRow, int startCol, int endRow, int endCol);

std::vector<int> getValidIndexes(int startRow, int startCol);
void switchPlayer();
void movePiece(int startRow, int startCol, int endRow, int endCol);
void promotePiece(int endRow, int endCol, char piece);
void playMove(int startRow, int startCol, int endRow, int endCol);


