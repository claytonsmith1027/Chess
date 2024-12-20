#pragma once



struct Square{
    float posX;
    float posY;
    int row = -1;
    int col = -1;
    float size;
    bool isLight;
    char piece = '\0';
};
void initBoard(const int WINDOW_WIDTH, const int WINDOW_HEIGHT);
void drawBoard();
void drawPieces(const int WINDOW_WIDTH, const int WINDOW_HEIGHT, Square selectedSquare = {});
void loadPieces(const int WINDOW_WIDTH, const int WINDOW_HEIGHT);
void unloadPieces();
Square currSquare(int WINDOW_WIDTH, int WINDOW_HEIGHT, int xPos, int yPos);
void highlightSquare(Square square, int WINDOW_HEIGHT);
void updateSquare(Square square, char piece);