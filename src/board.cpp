#include "raylib.h"
#include "board.h"
#include "string"
#include "game.h"
#include <vector>
#include <filesystem>
#include <iostream>


const std::string RESOURCE_PATH = "../resources";
const std::string PIECES_PATH = RESOURCE_PATH + "/pieces";
const float SQUARE_SIZE_SCALAR = 9.0;
const int BOARD_SIZE = 8;
std::vector<Texture> pieceTextures = {};
Square squares[63] = {};

void initBoard(const int WINDOW_WIDTH, const int WINDOW_HEIGHT){
    float squareSize = WINDOW_HEIGHT / SQUARE_SIZE_SCALAR;
    float startX = WINDOW_WIDTH / 2 - squareSize * 4;
    float startY = WINDOW_HEIGHT / 2 - squareSize * 4 - squareSize;
    float offsetX = 0;
    float offsetY = 0;
    bool isLight = true;
    char* board = currBoard();
    for(int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++){
        if((i + 1) % 8 == 1){
            offsetX = 0;
            offsetY += squareSize;
            isLight = !isLight;
        }
        squares[i].posX = startX + offsetX;
        squares[i].posY = startY + offsetY;
        squares[i].size = squareSize;
        squares[i].piece = board[i];
        squares[i].isLight = isLight;
        squares[i].row = i / 8;
        squares[i].col = i % 8;
        isLight = !isLight;
        offsetX += squareSize;
    }
}

void drawBoard() {
    Color LIGHT_COLOR = {0xb8, 0x8b, 0x4a, 0xff};
    Color DARK_COLOR = {0xe3, 0xc1, 0x6f, 0xff};
    Color squareColor;
	for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        if (squares[i].isLight == true) {
            squareColor = LIGHT_COLOR;
        }
        else {
            squareColor = DARK_COLOR;
        }
        // std::cout << squares[i].posX << " " << squares[i].posY << " " << squares[i].size << " " << squares[i].size << std::endl;
        DrawRectangle(squares[i].posX, squares[i].posY, squares[i].size, squares[i].size, squareColor);
	}
}

void drawPieces(const int WINDOW_WIDTH, const int WINDOW_HEIGHT, Square selectedSquare){
    char* board = currBoard();
    for(int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++){
        if(!(selectedSquare.row != -1 && i == selectedSquare.row * 8 + selectedSquare.col)){
            switch (board[i]){
                case 'b':
                    DrawTexture(pieceTextures[0], squares[i].posX, squares[i].posY, WHITE);
                    break;
                case 'k':
                    DrawTexture(pieceTextures[1], squares[i].posX, squares[i].posY, WHITE);
                    break;
                case 'n':
                    DrawTexture(pieceTextures[2], squares[i].posX, squares[i].posY, WHITE);
                    break;
                case 'p':
                    DrawTexture(pieceTextures[3], squares[i].posX, squares[i].posY, WHITE);
                    break;
                case 'q':
                    DrawTexture(pieceTextures[4], squares[i].posX, squares[i].posY, WHITE);
                    break;
                case 'r':
                    DrawTexture(pieceTextures[5], squares[i].posX, squares[i].posY, WHITE);
                    break;
                case 'B':
                    DrawTexture(pieceTextures[6], squares[i].posX, squares[i].posY, WHITE);
                    break;
                case 'K':
                    DrawTexture(pieceTextures[7], squares[i].posX, squares[i].posY, WHITE);
                    break;
                case 'N':
                    DrawTexture(pieceTextures[8], squares[i].posX, squares[i].posY, WHITE);
                    break;
                case 'P':
                    DrawTexture(pieceTextures[9], squares[i].posX, squares[i].posY, WHITE);
                    break;
                case 'Q':
                    DrawTexture(pieceTextures[10], squares[i].posX, squares[i].posY, WHITE);
                    break;
                case 'R':
                    DrawTexture(pieceTextures[11], squares[i].posX, squares[i].posY, WHITE);
                    break;
                default:
                    break;
            }
        }
    }
    switch (board[selectedSquare.row * 8 + selectedSquare.col]){
            case 'b':
                DrawTexture(pieceTextures[0], GetMouseX() - selectedSquare.size / 2, GetMouseY() - selectedSquare.size / 2, WHITE);
                break;
            case 'k':
                DrawTexture(pieceTextures[1], GetMouseX() - selectedSquare.size / 2, GetMouseY() - selectedSquare.size / 2, WHITE);
                break;
            case 'n':
                DrawTexture(pieceTextures[2], GetMouseX() - selectedSquare.size / 2, GetMouseY() - selectedSquare.size / 2, WHITE);
                break;
            case 'p':
                DrawTexture(pieceTextures[3], GetMouseX() - selectedSquare.size / 2, GetMouseY() - selectedSquare.size / 2, WHITE);
                break;
            case 'q':
                DrawTexture(pieceTextures[4], GetMouseX() - selectedSquare.size / 2, GetMouseY() - selectedSquare.size / 2, WHITE);
                break;
            case 'r':
                DrawTexture(pieceTextures[5], GetMouseX() - selectedSquare.size / 2, GetMouseY() - selectedSquare.size / 2, WHITE);
                break;
            case 'B':
                DrawTexture(pieceTextures[6], GetMouseX() - selectedSquare.size / 2, GetMouseY() - selectedSquare.size / 2, WHITE);
                break;
            case 'K':
                DrawTexture(pieceTextures[7], GetMouseX() - selectedSquare.size / 2, GetMouseY() - selectedSquare.size / 2, WHITE);
                break;
            case 'N':
                DrawTexture(pieceTextures[8], GetMouseX() - selectedSquare.size / 2, GetMouseY() - selectedSquare.size / 2, WHITE);
                break;
            case 'P':
                DrawTexture(pieceTextures[9], GetMouseX() - selectedSquare.size / 2, GetMouseY() - selectedSquare.size / 2, WHITE);
                break;
            case 'Q':
                DrawTexture(pieceTextures[10], GetMouseX() - selectedSquare.size / 2, GetMouseY() - selectedSquare.size / 2, WHITE);
                break;
            case 'R':
                DrawTexture(pieceTextures[11], GetMouseX() - selectedSquare.size / 2, GetMouseY() - selectedSquare.size / 2, WHITE);
                break;
            default:
                break;
    }
}

void loadPieces(const int WINDOW_WIDTH, const int WINDOW_HEIGHT){
    for(const auto& dirEntry : std::filesystem::directory_iterator(PIECES_PATH)){
        Image image = LoadImage(dirEntry.path().string().c_str());
        ImageResize(&image, static_cast<int>(WINDOW_HEIGHT / SQUARE_SIZE_SCALAR), static_cast<int>(WINDOW_HEIGHT / SQUARE_SIZE_SCALAR));
        Texture texture = LoadTextureFromImage(image);
        UnloadImage(image);
        pieceTextures.push_back(texture);
    }
}


void unloadPieces(){
    for(int i = 0; i < pieceTextures.size(); i++){
        UnloadTexture(pieceTextures[i]);
    }
}

Square currSquare(int WINDOW_WIDTH, int WINDOW_HEIGHT, int xPos, int yPos){
    if(xPos > WINDOW_WIDTH / 2 + 4 * (WINDOW_HEIGHT / SQUARE_SIZE_SCALAR) || xPos < WINDOW_WIDTH / 2 - 4 * (WINDOW_HEIGHT / SQUARE_SIZE_SCALAR)){
        // std::cout << "x" << std::endl; 
        return Square{};
    }
    else if (yPos > WINDOW_HEIGHT / 2 + 4 * (WINDOW_HEIGHT / SQUARE_SIZE_SCALAR) || yPos < WINDOW_HEIGHT / 2 - 4 * (WINDOW_HEIGHT / SQUARE_SIZE_SCALAR)){
        // std::cout << "y" << std::endl;
        return Square{};
    }
    int row = 0;
    int col = 0;
    while(xPos > squares[col].posX && col < 8){
        col++;
    }
    while(yPos > squares[row * 8].posY && row < 8){
        row++;
    }
    return squares[(row - 1) * 8 + (col - 1)];
}

void highlightSquare(Square square, int WINDOW_HEIGHT){
    Color HIGHLIGHT_COLOR = {0xff, 0x00, 0x00, 0xff};
    if(square.row != -1){
        DrawRectangle(square.posX, square.posY, WINDOW_HEIGHT / SQUARE_SIZE_SCALAR, WINDOW_HEIGHT / SQUARE_SIZE_SCALAR, HIGHLIGHT_COLOR);
    }
}

void highlightAttackedSquares(Square square, int WINDOW_WIDTH, int WINDOW_HEIGHT){
    std::vector<int> indexes = getLegalIndexes(square.row * 8 + square.col);
    for(int i = 0; i < indexes.size(); i++){
        if(indexes[i] == -1){
            continue;
        }
        if(isLegalMove(square.row * 8 + square.col, indexes[i])){
            highlightSquare(squares[indexes[i]], WINDOW_HEIGHT);
        }
            
    }
}

void updateSquare(Square square, char piece){
    int index = square.row * 8 + square.col;
    squares[index].piece = piece;
}