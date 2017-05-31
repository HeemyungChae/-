#ifndef CSnake_H
#define CSnake_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define Black 0
#define Blue 1
#define Green 2
#define Cyan 3
#define Red 4
#define Magenta 5
#define Yellow 6
#define White 7
#define Gray 8
#define LightBlue 9
#define LightGreen 10
#define LightCyan 11
#define LightRed 12
#define LightMagenta 13
#define LightYellow 14
#define BrightWhite 15



#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACE 32
#define ENTER 13
#define ESCAPE 27







class CSnake
{
	public:

		int snakeXLocation[1000];
		int snakeYLocation[1000];
		int color_background, color_border  , color_apple , color_normal , color_snake ;  //  colors
		unsigned char  snake, prvSnake, snake_Enlongment ;
		int randomX, randomY, apple ;      //  apple
		int level ;
		int score ;
		char playAgain;



		int i, j;
		int centerX, centerY;         //
		int x, y, oldX, oldY;
		int rows, cols;
		char c;
		int direction, difficulty;

	public:
		CSnake();
		CSnake( int i);
		~CSnake();


	public:

	   void Settings();
	   void Game_Main();
	   void game_Canvas();
	   void initsnake();
	   void check_collision();
	   void keyPressed();
	   void Display_snake();
	   void check_Snake_Location();
	   void Create_Apples();
	   void Check_Apples();
	   void Remove_Apple();
	   void Game_Over();
	   void Display();
	   void Game_Main2();
	   void game_Canvas2();

		void gotoxy(int x, int y);
		void clrscr();
		void setcolor(WORD color);
		void clrbox(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char bkcol);
		void box(unsigned x,unsigned y,unsigned sx,unsigned sy,unsigned char col,unsigned char col2,char text_[]);
		void putbox(unsigned x1,unsigned y1,unsigned x2,unsigned y2,unsigned char texcol,unsigned char frcol,unsigned char bkgcol,char bheader[]);
        void CalclateFramesPerSecond();


};

#endif CSnake_H