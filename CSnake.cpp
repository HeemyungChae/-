/* 
 *
 *파일 이름 : CSnake.cpp
 작성자 : https://www.codeproject.com/Articles/85531/Snake-Game-in-a-Win-Console
 목적: 뱀이 벽과 충돌하지 않고 사과를 먹는 게임


 2017. 05.25. 수정사항 : 배경과 사과 아스키코드 수정 - soyoungJeong */



#include "CSnake.h"


	unsigned long   lastTick=GetTickCount(),currTick=GetTickCount();
	unsigned long   UPDATESPEED;
	unsigned int frames=0;
	float fps=60.0f;
	float g_speed;

	//**********************************************
	//**                                          **
	//**********************************************

	CSnake::CSnake( int i)
	{

        lastTick=GetTickCount(),currTick=GetTickCount();
	    frames=0;
	    fps=60.0f;


		color_background=62,
		color_border=49;
		color_apple=44;
		color_normal=15;
		color_snake=2;  //  colors
		snake_Enlongment=5;
		apple=0;      //  apple
		level=1;
		if (prvSnake>200  || prvSnake<0) prvSnake=5;
		centerX=39-(cols/2);
		centerY=14-(rows/2);

        Game_Main();


    }

	//**********************************************
	//**                                          **
	//**********************************************



void CSnake::Game_Main()
{
    Settings();
	game_Canvas();
	Create_Apples();
	initsnake();
	if (prvSnake>200  || prvSnake<0) prvSnake=5;

   do{
	   keyPressed();
      check_collision();
      Check_Apples();
      check_Snake_Location();
      Display_snake();
	  CalclateFramesPerSecond();
      ;

   }while((c!=27) && (x!=centerX+(cols)) && (x!=centerX-1) && (y!=centerY+(rows)) && (y!=centerY-1));Game_Over();

}
	//**********************************************
	//**                                          **
	//**********************************************

	void CSnake::Settings()
	{
		 // clrscr();
		setcolor(color_normal);
		rows=15;
		cols=60;
		level=1;
		srand(time(NULL));
		centerX=39-(cols/2);
		centerY=14-(rows/2);
		if (prvSnake>200  || prvSnake<0) prvSnake=5;

	clrbox(10,8,70,16,31);
		box(10,8,70,16,31,31,"");


		gotoxy(28,10);cprintf("Get Ready");
		gotoxy(18,12);cprintf("Use the Arrow keys on the keyboard  ");
		gotoxy(18,13);cprintf("<LEFT> <RIGHT> <UP> <DOWN> to steer snake");
		gotoxy(18,15);printf( "Press any key to start snake");
		c=getch();

	}
	/***************************
	 *   game_Canvas                  *
	****************************/
	void CSnake::game_Canvas()
	{
  		clrbox(1,1,78,24,((16 *LightGreen)+LightGreen));
		//box(1,1,78,24,Green,White,"");
		clrbox(centerX-1,centerY-1,cols+centerX,rows+centerY,Green);
		box(centerX-1,centerY-1,cols+centerX,rows+centerY,Green,White,"");
		setcolor(color_normal);printf("%c",'o');
		for(i=0;i<=cols+1;i++)
		{
			for(j=0;j<=rows+1;j++)
			{
				gotoxy((centerX-1)+i,(centerY-1)+j);
				if((centerX+i==centerX)||
				(centerX+i-1==(centerX+cols))||
				(centerY+j==centerY)||
				(centerY+j-1==(rows+centerY)))
				{
					setcolor(color_border);
					printf("%c",' ');
				}
				else printf("%c",' ');
				setcolor(color_background);
			}
		}

}
	/***************************
	 *   initsnake             *
	****************************/
	void CSnake::initsnake()
	{
	   x=35;
	   y=14;
	   snake=5;
	   for(i=0;i<=201;i++)
	   {
	      snakeXLocation[i]=0;
	      snakeYLocation[i]=0;
	   }
	   for(i=snake;i>0;i--,x++)
	   {
	      snakeXLocation[i]=x;
	      snakeYLocation[i]=y;
	   }
	   x--;
	   oldX=x; oldY=y;
	   direction=1;          //
	   j=0;
	}
	/***************************
	 *   check_collision             *
	****************************/
	void CSnake::check_collision()
	{
	   for(i=2;i<=snake;i++)
	   {
	      if((snakeXLocation[1]==snakeXLocation[i])&&(snakeYLocation[1]==snakeYLocation[i])) Game_Over();
	   }
	}
	/***************************
	 *   create apples         *
	****************************/
	void CSnake::Create_Apples()
	{
	   setcolor(color_apple);
	   randomX= ( rand()% cols )+ centerX ;
	   randomY= ( rand()% rows)+ centerY  ;
	   for(i=1;i<=snake;i++)
	   {
	      if((randomX==snakeXLocation[i])&&(randomY==snakeYLocation[i])) Create_Apples();
	   }
	   gotoxy(randomX,randomY); printf("%c",'O');
	   if(score==1)getch();
	}
	/***************************
	 *   check apples          *
	****************************/
	void CSnake::Check_Apples()
	{
		if((snakeXLocation[1]==randomX)&&(snakeYLocation[1]==randomY))
		{
	       apple++;
	       Remove_Apple();
	       snake+=snake_Enlongment;
	       Create_Apples();
	    }
	}
	/***************************
	 *   display snake         *
	****************************/
	void CSnake::Display_snake()
	{
	   for(i=snake;i>=0;i--)
	   {
	      gotoxy(snakeXLocation[i],snakeYLocation[i]);
	      if(i==0)
		  {
	         setcolor(color_background);
	         printf("%d",1);
	      }else setcolor(color_snake);
	         if(i==1)           printf("%d",2);
	         if((i!=0)&&(i!=1)) printf("%d",3);
	   }
	   setcolor (color_normal);
	   gotoxy(centerX-1,centerY+rows+2);
	   printf("level: %2.d",level);
	   gotoxy(centerX-1,centerY+rows+2+1);
	   printf("/ %2.d,eaten /%2.d apples left ",apple,(((rows*cols)/30)+6));
	   setcolor (color_background);
	}
	/***************************
	 *   check Snake Location  *
	****************************/
	void CSnake::check_Snake_Location()
	{
		if (prvSnake>200  || prvSnake<0) prvSnake=5;
	   if((oldX!=x)||(oldY!=y))
	   {
	      if(snake==prvSnake)
		  {

	         snakeXLocation[0]=snakeXLocation[snake];
	         snakeYLocation[0]=snakeYLocation[snake];
	         for(i=snake;i>1;i--)
			 {
	            snakeXLocation[i]=snakeXLocation[i-1];
	            snakeYLocation[i]=snakeYLocation[i-1];
	         }
	      }
	      if(snake!=prvSnake)
		  {

	         snakeXLocation[0]=snakeXLocation[prvSnake];
	         snakeYLocation[0]=snakeYLocation[prvSnake];
	         for(i=prvSnake;i>1;i--)
			 {
	            snakeXLocation[i]=snakeXLocation[i-1];
	            snakeYLocation[i]=snakeYLocation[i-1];
	         }
	         for(i=(prvSnake+1);i<=snake;i++)
			 {
	            snakeXLocation[i]=snakeXLocation[i-1];
	            snakeYLocation[i]=snakeYLocation[i-1];
	         }
	      }
	      if(oldX!=x) snakeXLocation[1]=x;       //
	      if(oldY!=y) snakeYLocation[1]=y;       //
	   }
	   prvSnake=snake;   //
	   oldX=x; oldY=y;    //
	}

	 /***************************
	 *   keypressed             *
	****************************/

	void CSnake::keyPressed()
	{
	   if(kbhit())
	   {                           //
	      c=getch();
	      switch(c)
		  {
	         case RIGHT :
				 if(direction!=3)
				 {
	                       x++ ;
	                       direction=1;
	                       }else x-- ;
				 break;

	         case LEFT:
				 if(direction!=1)
				 {
	                       x-- ;
	                       direction=3;
	                       }else x++ ;
				 break;

	         case DOWN :
				 if(direction!=2)
				 {
	                       y++ ;
	                       direction=4;
	                       }else y-- ;
				 break;

	         case UP  :
				 if(direction!=4)
				 {
	                       y-- ;
	                       direction=2;
	                       }else y++ ;
				 break;

	         case SPACE : getch() ; break;
	      }
	   }
	   else{                                     //
	      switch(direction)
		  {
	         case 1 : x++; break;
	         case 3 : x--; break;
	         case 4 : y++; break;
	         case 2 : y--; break;
	      }
	   }
	   switch(level){                           //
	         case 1: difficulty=120  ; break ;
	         case 2: difficulty=90   ; break ;
	         case 3: difficulty=65   ; break ;
	         case 4: difficulty=40   ; break ;
	         case 5: difficulty=20   ; break ;
	         case 6: difficulty=15   ; break ;
	      }
	   Sleep(difficulty);
	}
	/***************************
	 *   remove apple          *
	****************************/
	void CSnake::Remove_Apple()
	{
	   if(apple==2)
	   {
	      apple=0;
	      Display();
	      level++;
	      if(level>2)
		  {                          //
	         score=0;
	         gotoxy(30,7);
	         setcolor(color_normal);
	         printf(" score ");
	         Sleep(700);
	         getch();
	         Game_Main();
	      }
	      score=1;
	      Game_Main();
	   }
	}
	/***************************
	 *   game over             *
	****************************/
	void CSnake::Game_Over()
	{

		apple=0;
        clrscr();
		clrbox(10,8,70,16,31);
		box(10,8,70,16,31,31,"Game Over ");

		gotoxy(18,10);cprintf("  ");
		gotoxy(18,11);cprintf("The snake has hit an obstacle");
		gotoxy(18,14);cprintf("");
		gotoxy(18,13);printf("play Again? (y/n)");


	   do{
	      playAgain=getch();
	      if((playAgain=='y')||(playAgain=='Y'))
		  {
	         rows=0;
	         cols=0;
	         Display();
	         Game_Main();
	      }
		  if((playAgain=='n')||
			 (playAgain=='N'))
		  {
			  setcolor(15);
			  clrscr();
			  gotoxy(1 ,23);
			  printf("\n				");
			  exit(1);
		  }
	   }while((playAgain!='y')||
		      (playAgain!='Y')||
			  (playAgain!='n')||
			  (playAgain!='N'));
	}
	/***************************
	 *   display               *
	****************************/
	void CSnake::Display()
	{
	   setcolor(0);
	   for(i=0;i<=70;i++)
	   {
	      for(j=0;j<=23;j++)
		  {
	         gotoxy(i,j);
	         printf("%d",5);
	      }
	   }
	}

/***************************
 *   setcolor              *
****************************/

void CSnake::setcolor(WORD color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
	return;
}
/***************************
 *   clear screen          *
****************************/
void CSnake::clrscr()
{
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(hConsole, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	SetConsoleCursorPosition(hConsole, coordScreen);
	return;
}

/***************************
 *   gotoxy                *
****************************/
void CSnake::gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x; coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	return;
}
	//**********************************************
	//**                                          **
	//**********************************************


void CSnake::clrbox(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char bkcol)
{ int x,y;


	for (y=y1;y<y2;y++)
	{
	  for (x=x1;x<x2;x++)
	  {
	  setcolor(bkcol);
	  gotoxy(x,y);cprintf(" ");
	  }
	}
}
	//**********************************************
	//**                                          **
	//**********************************************

void CSnake::box(unsigned x,unsigned y,unsigned sx,unsigned sy,unsigned char col,unsigned char col2,char text_[])
{  unsigned i,j,k=0,m;
    {

       m=(sx-x);
       j=m/8;
       j=j-1;


	setcolor(col2);
	gotoxy(x,y);cprintf("?");
	gotoxy(sx,y);cprintf("?");
	gotoxy(x,sy);cprintf("?");
	gotoxy(sx,sy);cprintf("?");

       for (i=x+1;i<sx;i++)
       {
	gotoxy(i,y);cprintf("?");
	gotoxy(i,sy);cprintf("?");
	}

	for (i=y+1;i<sy;i++)
	{
	gotoxy(x,i);cprintf("?");
	gotoxy(sx,i);cprintf("?");
	}
	setcolor(col);
	gotoxy(x+j,y);cprintf(text_);
	gotoxy(1,24);


    }
}
	//**********************************************
	//**                                          **
	//**********************************************


void CSnake::putbox(unsigned x1,unsigned y1,unsigned x2,unsigned y2,unsigned char texcol,unsigned char frcol,unsigned char bkgcol,char bheader[])
{
     clrbox(x1,y1,x2,y2,bkgcol);
     box(x1,y1,x2,y2,texcol,frcol,bheader);

}


void CSnake::CalclateFramesPerSecond()
{
	currTick=GetTickCount();
	unsigned long   tickDiff=currTick-lastTick;
	frames++;
	if(tickDiff>=UPDATESPEED)
	{

		lastTick=currTick;
		float calcVal=1/((float)UPDATESPEED/1000.0f);	// Inverse
		float fpsCalc=(float)frames*calcVal;		// Calculates our frames in one second
		fps+=fpsCalc;
		fps/=2;


		setcolor(31);gotoxy(60,22);printf(" %d FPS ",tickDiff );setcolor(15);

		frames=0;
		g_speed=60/fps;
	}
}



