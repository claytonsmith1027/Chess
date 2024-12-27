#pragma once

#include "vector"

void updateBoard(int startIndex, int newIndex);
void updateTempBoard(int startIndex, int newIndex);
char* currBoard();
void changePlayer();
void printBoard();
bool isPieceWhite(int index);
std::vector<int> legalDiagIndexes(int startingIndex);
std::vector<int> legalCardinalIndexes(int startingIndex);
std::vector<int> legalKnightIndexes(int startingIndex);
std::vector<int> legalPawnIndexes(int startIndex);
std::vector<int> legalKingIndexes(int startingIndex);
bool isPromotion(int index, char piece);
void promotePawn(int index, char newPiece);
int lastMoveStartIndex();
int lastMoveEndIndex();
std::vector<int> getLegalIndexes(int startingIndex);
std::vector<int> potentialAttackerIndexes(int startingIndex);
bool isInCheck(int startingIndex);
bool isLegalMove(int startIndex, int newIndex);
void playMove(int startingIndex, int newIndex);