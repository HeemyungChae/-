/* 
 *
 *파일 이름 : CSnake.cpp
 
 작성자 : https://www.codeproject.com/Articles/85531/Snake-Game-in-a-Win-Console
 
 목적: 뱀이 벽과 충돌하지 않고 사과를 먹는 게임
 2017. 05. 25 수정사항 : 배경과 사과 아스키코드 수정 - soyoungJeong
 2017. 05. 31 수정사항 : 사과를 4개 먹으면 다음 스테이지로 넘어가고 스테이지가 넘어가면 공간이 작아짐
              에러사항 : 스테이지가 작아지면 사과 위치와 충돌 에러 생김  - soyoungJeong
 2017. 05. 31 수정사항 : 충돌 에러 해결 - soyoungJeong
 2017. 06. 01 수정사항 : 슈퍼사과와 폭탄 추가 - zoe0526
			  에러사항 : 랜덤생성 오류 - zoe0526 
 2017. 06. 02 수정사항 : 디자인 수정 -zoe0526
						 공간 밖 아이템 에러 해결 -zoe0526 
 2017. 06. 02 수정사항 : life 기능 추가 -sanhayo
 2017. 06. 02 수정사항 : 무적 아이템 추가 -heemyung
 
 */


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
		color_apple=44;//빨강
		color_normal=15;
		color_snake=2;
		color_superapple=45;//분홍
		color_bomb=48;//검정
		//color
		snake_Enlongment=5;
		apple=0;      //  apple
		item = 0;
		if (prvSnake>200  || prvSnake<0) prvSnake=5;
		centerA=centerX=39-(cols/2);
		centerB=centerY=14-(rows/2);

        Game_Main();


    }

	//**********************************************
	//**                                          **
	//**********************************************



void CSnake::Game_Main()
{
	level=1;
    Settings();
	game_Canvas();
	Create_Apples();
	Create_SuperApples();
	Create_Bombs();
	initsnake();
	if (prvSnake>200  || prvSnake<0) prvSnake=5;

   do{
	   keyPressed();
      check_collision();
      Check_Apples();
	   Check_SuperApples();
	  Check_Bombs();
	  Check_item();
      check_Snake_Location();
      Display_snake();
	  Display_state();
	  CalclateFramesPerSecond();
      

   }while(life>=1);Game_Over();

}

void CSnake::Game_Main2()
{
	level=2;
    Settings();
	game_Canvas2();
	Create_Apples2();
	Create_SuperApples2();
	Create_Bombs2();
	initsnake();
	if (prvSnake>200  || prvSnake<0) prvSnake=5;

   do{
	   keyPressed();
      check_collision();
      Check_Apples();
	   Check_SuperApples();
	  Check_Bombs();
	  Check_item();
	  check_Snake_Location();
      Display_snake();
	  Display_state();
	  CalclateFramesPerSecond();
      ;

   }while((c!=27) && (x!=centerX+(cols)) && (x!=centerX) && (y!=centerY+(rows)) && (y!=centerY));Game_Over();

}

void CSnake::Game_Main3()
{
	level=3;
    Settings();
	game_Canvas3();
	Create_Apples3();
	Create_SuperApples3();
	Create_Bombs3();
	initsnake();
	if (prvSnake>200  || prvSnake<0) prvSnake=5;

   do{
	   keyPressed();
      check_collision();
      Check_Apples();
	   Check_SuperApples();
	  Check_Bombs();
	  Check_item();
	  check_Snake_Location();
      Display_snake();
	  Display_state();
	  CalclateFramesPerSecond();
      ;

   }while((c!=27) && (x!=centerX+(cols)+3) && (x!=centerX+1) && (y!=centerY+(rows)) && (y!=centerY+1));Game_Over();

}
	//**********************************************
	//**                                          **
	//**********************************************

	void CSnake::Settings()
	{
		 // clrscr();
		life = 3; //목숨 3개로 초기화
		flag = 1;
		count = 1;
		setcolor(color_normal);
		rows=15;
		cols=60;
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
					setcolor(1);
					printf("%c", ' ');
				}
				else printf("%c", ' ');
				setcolor(color_background);
			}
		}

}

	void CSnake::game_Canvas2()
	{
  		clrbox(1,1,78,24,((16 *LightGreen)+LightGreen));
		//box(1,1,78,24,Green,White,"");
		clrbox(centerX-1,centerY-1,cols+centerX,rows+centerY,Green);
		box(centerX-1,centerY-1,cols+centerX,rows+centerY,Green,White,"");
		setcolor(color_normal);printf("%c",'o');
		for(i=2;i<=cols;i++)
		{
			for(j=2;j<=rows;j++)
			{
				gotoxy((centerX-1)+i,(centerY-1)+j);
				if((centerX+i==centerX)||
				(centerX+i-1==(centerX+cols))||
				(centerY+j==centerY)||
				(centerY+j-1==(rows+centerY)))
				{
					setcolor(1);
					printf("%c", ' ');
				}
				else printf("%c", ' ');
				setcolor(color_background);
			}
		}

}

	void CSnake::game_Canvas3()
	{
  		clrbox(1,1,78,24,((16 *LightGreen)+LightGreen));
		//box(1,1,78,24,Green,White,"");
		clrbox(centerX-1,centerY-1,cols+centerX,rows+centerY,Green);
		box(centerX-1,centerY-1,cols+centerX,rows+centerY,Green,White,"");
		setcolor(color_normal);printf("%c",'o');
		for(i=4;i<=cols;i++)
		{
			for(j=4;j<=rows;j++)
			{
				gotoxy((centerX-1)+i,(centerY-1)+j);
				if((centerX+i==centerX)||
				(centerX+i-1==(centerX+cols))||
				(centerY+j==centerY)||
				(centerY+j-1==(rows+centerY)))
				{
					setcolor(1);
					printf("%c", ' ');
				}
				else printf("%c", ' ');
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
	 
	//맵에 충돌할 때 목숨 1깎고 사과랑 뱀 초기화 시키고 다시 그림 (Game_Main이랑 똑같음)
	if (!((c!=27) && (x!=centerX+(cols)) && (x!=centerX-1) && (y!=centerY+(rows)) && (y!=centerY-1)))
	{
		life--;
		apple=0;
		game_Canvas();
		initsnake();
		Create_Apples();
		if (prvSnake>200  || prvSnake<0) prvSnake=5;
		Display_snake();

		return;
	}
	//자기 몸에 박을 땐데, 벽이랑 박을 때랑 똑같음
	for(i=2;i<=snake;i++)
	{
		if((snakeXLocation[1]==snakeXLocation[i])&&(snakeYLocation[1]==snakeYLocation[i]))
		{
			life--;
			apple=0;
			game_Canvas();
			initsnake();
			Create_Apples();
			if (prvSnake>200  || prvSnake<0) prvSnake=5;
			Display_snake();

			return;
		}
	}
	}
	/***************************
	 *   create apples         *
	****************************/
	void CSnake::Create_Apples()
	{
		Create_item();
	   setcolor(color_apple);
	   randomX= ( rand()% cols )+ centerX ;
	   randomY= ( rand()% rows)+ centerY  ;
	   for(i=1;i<=snake;i++)
	   {
	      if((randomX==snakeXLocation[i])&&(randomY==snakeYLocation[i])) Create_Apples();
	   }
	   gotoxy(randomX,randomY); printf("%c",'o');
	   if(score==1)getch();
	}

	/***************************
	 *   create superapples         *
	****************************/
	void CSnake::Create_SuperApples()
	{
		setcolor(color_superapple);
	   randomX= ( rand()% cols )+ centerX ;
	   randomY= ( rand()% rows)+ centerY  ;
	   for(i=1;i<=snake;i++)
	   {
	      if((randomX==snakeXLocation[i])&&(randomY==snakeYLocation[i])) 
			  Create_SuperApples();
	   }
	   gotoxy(randomX,randomY); printf("%c",'o');
	   if(score==1)getch();
	}
	/***************************
	 *   create bombs         *
	****************************/
	void CSnake::Create_item() {
		flag = 0;
		setcolor(color_item);
		randomA = (rand() % cols) + centerA;
		randomB = (rand() % rows) + centerB;
		for (i = 1; i <= snake; i++)
		{
			if ((randomA == snakeXLocation[i]) && (randomB == snakeYLocation[i])) Create_item();

		}
		gotoxy(randomA, randomB);
		printf("%c", 'Z');
	}


	void CSnake::Check_item() {
		if ((snakeXLocation[1] == randomA) && (snakeYLocation[1] == randomB))
		{
			flag = 1;

		}

	}

	void CSnake::Create_Bombs()
	{
		setcolor(color_bomb);
	   randomX= ( rand()% cols )+ centerX ;
	   randomY= ( rand()% rows)+ centerY  ;
	   for(i=1;i<=snake;i++)
	   {
	      if((randomX==snakeXLocation[i])&&(randomY==snakeYLocation[i])) 
			  Create_Bombs();
	   }
	   gotoxy(randomX,randomY); printf("%c",'o');
	   if(score==1)getch();

	}

	/***************************
	 *   create apples         *
	****************************/
	void CSnake::Create_Apples2()
	{
	   setcolor(color_apple);
	   randomX= ( rand()% (cols-1) )+ centerX ;
	   randomY= ( rand()% (rows-1))+ centerY  ;
	   for(i=1;i<=snake;i++)
	   {
	      if((randomX==snakeXLocation[i])&&(randomY==snakeYLocation[i])) Create_Apples();
	   }
	   gotoxy(randomX,randomY); printf("%c",'o');
	   if(score==1)getch();
	}

	/***************************
	 *   create superapples         *
	****************************/
	void CSnake::Create_SuperApples2()
	{
		setcolor(color_superapple);
	   randomX= ( rand()% (cols-1) )+ centerX ;
	   randomY= ( rand()% (rows-1))+ centerY  ;
	   for(i=1;i<=snake;i++)
	   {
	      if((randomX==snakeXLocation[i])&&(randomY==snakeYLocation[i])) 
			  Create_SuperApples();
	   }
	   gotoxy(randomX,randomY); printf("%c",'o');
	   if(score==1)getch();
	}
	/***************************
	 *   create bombs         *
	****************************/

	void CSnake::Create_Bombs2()
	{
		setcolor(color_bomb);
	   randomX= ( rand()% (cols-1) )+ centerX ;
	   randomY= ( rand()% (rows-1))+ centerY  ;
	   for(i=1;i<=snake;i++)
	   {
	      if((randomX==snakeXLocation[i])&&(randomY==snakeYLocation[i])) 
			 Create_Bombs();
	   }
	   gotoxy(randomX,randomY); printf("%c",'o');
	   if(score==1)getch();

	}

		/***************************
	 *   create apples         *
	****************************/
	void CSnake::Create_Apples3()
	{
	   setcolor(color_apple);
	   randomX= ( rand()% (cols-2) )+ centerX ;
	   randomY= ( rand()% (rows-2))+ centerY  ;
	   for(i=1;i<=snake;i++)
	   {
	      if((randomX==snakeXLocation[i])&&(randomY==snakeYLocation[i])) Create_Apples();
	   }
	   gotoxy(randomX,randomY); printf("%c",'o');
	   if(score==1)getch();
	}

	/***************************
	 *   create superapples         *
	****************************/
	void CSnake::Create_SuperApples3()
	{
		setcolor(color_superapple);
	   randomX= ( rand()% (cols-2) )+ centerX ;
	   randomY= ( rand()% (rows-2))+ centerY  ;
	   for(i=1;i<=snake;i++)
	   {
	      if((randomX==snakeXLocation[i])&&(randomY==snakeYLocation[i])) 
			  Create_SuperApples();
	   }
	   gotoxy(randomX,randomY); printf("%c",'o');
	   if(score==1)getch();
	}
	/***************************
	 *   create bombs         *
	****************************/

	void CSnake::Create_Bombs3()
	{
		setcolor(color_bomb);
	   randomX= ( rand()% (cols-2) )+ centerX ;
	   randomY= ( rand()% (rows-2))+ centerY  ;
	   for(i=1;i<=snake;i++)
	   {
	      if((randomX==snakeXLocation[i])&&(randomY==snakeYLocation[i])) 
			 Create_Bombs();
	   }
	   gotoxy(randomX,randomY); printf("%c",'o');
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
	 *   check superapples          *
	****************************/
	void CSnake::Check_SuperApples()
	{
		if((snakeXLocation[1]==randomX)&&(snakeYLocation[1]==randomY))
		{
	       apple++;
	       Remove_Apple();
	       snake+=snake_Enlongment+1;
	       Create_SuperApples();
	    }
	}
	/***************************
	 *   check bombs         *
	****************************/
	void CSnake::Check_Bombs()
	{
		if((snakeXLocation[1]==randomX)&&(snakeYLocation[1]==randomY))
		{
	       apple++;
	       Remove_Apple();
	       snake-=snake_Enlongment;
	       Create_Bombs();
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
	         printf("%c",0);
	      }else setcolor(color_snake);
	         if(i==1)           printf("%c",0);
	         if((i!=0)&&(i!=1)) printf("%c",0);
	   }


	   setcolor (color_background);
	}

	void CSnake::Display_state()
	{
	   setcolor (color_normal);
	   gotoxy(centerX-1,centerY+rows+2);
	   printf("level: %2.d",level);
	   gotoxy(centerX-1,centerY+rows+2+1);
	   printf("/ %2.d,eaten /%2.d apples left ",apple,(((rows*cols)/30)+6));
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

		  
		  if(level==1)
		  {
			 score=1;
	         gotoxy(30,7);
	         setcolor(color_normal);
	         printf(" score = %d", score);
	         Sleep(700);
	         getch();
	         Game_Main2();
		  }

		  if(level==2)
		  {			 
			 score=2;
	         gotoxy(30,7);
	         setcolor(color_normal);
	         printf(" score = %d", score);
	         Sleep(700);
	         getch();
	         Game_Main3();
		  }
		  
		  if(level==3)
		  {
			 score=3;
	         gotoxy(30,7);
	         setcolor(color_normal);
	         printf(" score = %d", score);
	         Sleep(700);
	         getch();
	         Game_Main3();

		  }
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
	gotoxy(x,y);cprintf(" ");
	gotoxy(sx,y);cprintf(" ");
	gotoxy(x,sy);cprintf(" ");
	gotoxy(sx,sy);cprintf(" ");

       for (i=x+1;i<sx;i++)
       {
	gotoxy(i,y);cprintf(" ");
	gotoxy(i,sy);cprintf(" ");
	}

	for (i=y+1;i<sy;i++)
	{
	gotoxy(x,i);cprintf(" ");
	gotoxy(sx,i);cprintf(" ");
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
		setcolor(31);gotoxy(60,23);printf("Life: %d",life);setcolor(15); //FPS밑에 Life도 표시

		frames=0;
		g_speed=60/fps;
	}
}