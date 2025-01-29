#include "board.h"
#include "game.h"
#include "raylib.h"
#include "window.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include <iostream>


int MainLoop()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Chess");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	loadPieces(WINDOW_WIDTH, WINDOW_HEIGHT);
	loadBoardFromFEN(STARTING_BOARD_FEN);
	initBoard(WINDOW_WIDTH, WINDOW_HEIGHT);
	Square hoveredSquare = {};
	Square heldSquare = {};

	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(DARKGRAY);
        drawBoard();
		if(IsKeyPressed(KEY_R)){
			resetGame();
			loadSquarePieces();
		}
		if(!IsMouseButtonDown(0)){
        	hoveredSquare = currSquare(WINDOW_WIDTH, WINDOW_HEIGHT, GetMouseX(), GetMouseY());
			if(hoveredSquare.piece != '0' && hoveredSquare.piece != '\0'){
				highlightAttackedSquares(hoveredSquare, WINDOW_WIDTH, WINDOW_HEIGHT);
			}
			if(heldSquare.row != -1 && hoveredSquare.row != -1){
				if(heldSquare.row != hoveredSquare.row || heldSquare.col != hoveredSquare.col){
					int startIndex = heldSquare.row * 8 + heldSquare.col;
					int newIndex = hoveredSquare.row * 8 + hoveredSquare.col;
					if(isValidMove(heldSquare.row, heldSquare.col, hoveredSquare.row, hoveredSquare.col)){
						if(canCastle(heldSquare.row, heldSquare.col, hoveredSquare.row, hoveredSquare.col)){
							if(hoveredSquare.col > 5){
								Square newRookSquare = getSquare(heldSquare.row * 8 + 5);
								Square oldRookSquare = getSquare(heldSquare.row * 8 + 7);
								Square newKingSquare = getSquare(heldSquare.row * 8 + 6);
								if(isWhitePiece(heldSquare.row, heldSquare.col)){
									updateSquare(newRookSquare, 'R');
									updateSquare(newKingSquare, 'K');
								}
								else{
									updateSquare(newRookSquare, 'r');
									updateSquare(newKingSquare, 'k');
								}
								updateSquare(oldRookSquare, '0');
								updateSquare(heldSquare, '0');
							}
							else{
								Square newRookSquare = getSquare(heldSquare.row * 8 + 3);
								Square oldRookSquare = getSquare(heldSquare.row * 8 + 0);
								Square newKingSquare = getSquare(heldSquare.row * 8 + 2);
								if(isWhitePiece(heldSquare.row, heldSquare.col)){
									updateSquare(newRookSquare, 'R');
									updateSquare(newKingSquare, 'K');
								}
								else{
									updateSquare(newRookSquare, 'r');
									updateSquare(newKingSquare, 'k');
								}
								updateSquare(oldRookSquare, '0');
								updateSquare(heldSquare, '0');
							}
							playMove(heldSquare.row, heldSquare.col, hoveredSquare.row, hoveredSquare.col);
							continue;
						}
						playMove(heldSquare.row, heldSquare.col, hoveredSquare.row, hoveredSquare.col);
						if(isPromotion(hoveredSquare.row, hoveredSquare.col)){
							if(heldSquare.piece == 'P'){
								promotePiece(hoveredSquare.row, hoveredSquare.col, 'Q');
								updateSquare(heldSquare, 'Q');
							}
							else{
								promotePiece(hoveredSquare.row, hoveredSquare.col, 'q');
								updateSquare(heldSquare, 'q');
							}
						}
						updateSquare(hoveredSquare, heldSquare.piece);
						updateSquare(heldSquare, '0');
					}
				}
			}
			heldSquare = {};
		}
		
		if(IsMouseButtonDown(0) && hoveredSquare.piece != '0' && hoveredSquare.piece != '\0'){
			if(heldSquare.row = -1){
				heldSquare = hoveredSquare;
			}
			highlightAttackedSquares(heldSquare, WINDOW_WIDTH, WINDOW_HEIGHT);
			drawPieces(WINDOW_WIDTH, WINDOW_HEIGHT, heldSquare);
		}
		else{
			drawPieces(WINDOW_WIDTH, WINDOW_HEIGHT);
		}
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	unloadPieces();

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
