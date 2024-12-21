#pragma once

#include "vector"

void updateBoard(int startIndex, int newIndex);
char* currBoard();
void changePlayer();
void printBoard();
bool isPieceWhite(int index);
std::vector<int> legalDiagIndexes(int startingIndex);
bool pawnMove(int startIndex, int newIndex);
bool isPromotion(int index, char piece);
void promotePawn(int index, char newPiece);
bool bishopMove(int startIndex, int newIndex);
bool knightMove(int startIndex, int newIndex);
bool kingMove(int startIndex, int newIndex);
bool rookMove(int startIndex, int newIndex);
bool queenMove(int startIndex, int newIndex);
bool isLegalMove(int startIndex, int newIndex);