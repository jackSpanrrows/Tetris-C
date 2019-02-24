/**
  main.c
  eluosifkuai
@Author Created by cfu on 2019/2/10.
@Copyright 2019 cheng.fu. All rights reserved.
**/

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "constant.h"

//定义常量库
//#include <constant.h>

//#include <cstdlib.h>
//#include <cstdio>
//#include <iostream>
//using namespace std;

int i, j, Temp, Temp1, Temp2;
int a[80][80] = {0};
int b[4];

struct Tetris {
	int x;
	int y;
	int flag;
	int next;
	int speed;
	int number;
	int score;
	int level;
};



int color(int c);
//定位坐标系
void gotoxy(int x, int y);
//制作游戏窗口
void DrwaGameframe(void);

void Flag(struct Tetris *);
//制作俄罗斯方块
void MakeTetris(struct Tetris *);
void PrintTetris(struct Tetris *);
void CleanTetris(struct Tetris *);
int ifMove(struct Tetris *);
void Del_Fullline(struct Tetris *);
void Gameplay(void);
void regulation(void);
void explation(void);
//欢迎界面
void welcom(void);

void Replay(struct Tetris * tetris);
//标题
void title(void);
//修饰
void flower(void);
//关闭游戏
void closed(void);

HANDLE hOut;

int color(int c) {
	//  获取输出流的句柄
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); // 更改文字颜色

	return 0;
}

void gotoxy(int x, int y) {
	COORD pos;
	pos.X = x;//横坐标
	pos.Y = y;//纵坐标
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void title() {
	color(15);
	gotoxy(24,3);
	printf("趣  味  俄  罗  斯  方  块\n");
	color(11);
	gotoxy(18,5);
	printf("■");
	gotoxy(18,6);
	printf("■■");
	gotoxy(18,7);
	printf("■");

	color(14);//黄色
	gotoxy(26, 6);
	printf("■■");
	gotoxy(28,7);
	printf("■■");

	color(10); //绿色
	gotoxy(36,6);
	printf("■■");
	gotoxy(36, 7);
	printf("■■");

	color(13);
	gotoxy(44, 5);
	printf("■");
	gotoxy(44, 6);
	printf("■");
	gotoxy(44, 7);
	printf("■");
	gotoxy(44, 8);
	printf("■");

	color(12); //亮红色
	gotoxy(56, 6);
	printf("■");
	gotoxy(52, 7);
	printf("■■■");
}

void flower() {
	gotoxy(66, 11);
	color(12);
	printf("(_)");

	gotoxy(64, 12);
	printf("(_)");

	gotoxy(68, 12);
	printf("(_)");

	gotoxy(66, 13);
	printf("(_)");

	gotoxy(67, 12);
	color(6);
	printf("@");

	gotoxy(72, 10);
	color(13);
	printf("(_)");

	gotoxy(76, 10);
	printf("(_)");

	gotoxy(74, 9);
	printf("(_)");

	gotoxy(74, 11);
	printf("(_)");

	gotoxy(75, 10);
	color(6);
	printf("@");

	gotoxy(71, 12);
	printf("|");

	gotoxy(72, 11);
	printf("/");

	gotoxy(70, 13);
	printf("\\|");

	gotoxy(70, 14);
	printf("|/");

	gotoxy(70, 15);
	printf("\\|");

	gotoxy(71, 16);
	printf("| /");

	gotoxy(71, 17);
	printf("|");

	gotoxy(67, 17);
	color(10);
	printf("\\\\\\\\");

	gotoxy(73, 17);
	printf("//");

	gotoxy(67, 18);
	color(2);
	printf("^^^^^^^^");

	gotoxy(68, 19);
	color(5);
	printf("AChan");

}

void welcome() {
	int n;
	int i, j = 1;
	color(14);

	for(i = 9; i<=20; i++) {
		for(j = 15; j<=60; j++) {
			gotoxy(j, i);
			if (i == 9 || i == 20) {
				printf("=");
			} else if(j == 15 || j == 59) {
				printf("||");
			}
		}
	}

	color(12);
	gotoxy(25, 12);
	printf("1.开始游戏");
	gotoxy(40, 12);
	printf("2.按键说明");

	gotoxy(25, 17);
	printf("3.游戏规则");

	gotoxy(40, 17);
	printf("4.退出");

	gotoxy(21, 22);
	color(3);

	printf("请选择[1 2 3 4]:[ ]\b\b");

	color(14);
	scanf("%d", &n);
	switch(n) {
		case 1:
			system("cls");
			DrwaGameframe();//制作游戏窗口
			Gameplay();
			break;
		case 2:
			explation();
			break;
		case 3:
			regulation();
			break;
		case 4:
			closed();
			break;
	}

}

void DrwaGameframe() {
	gotoxy(FrameX + Frame_width-7, FrameY-1);
	color(11);
	printf("趣味俄罗斯方块");

	gotoxy(FrameX + 2*Frame_width+3, FrameY+7);
	color(2);
	printf("**********");

	gotoxy(FrameX + 2*Frame_width+13, FrameY+7);
	color(3);
	printf("下一次出现方块：");

	gotoxy(FrameX + 2*Frame_width+3, FrameY+3);
	color(2);
	printf("**********");

	gotoxy(FrameX + 2*Frame_width+3, FrameY+17);
	color(14);
	printf("↑键:旋转");

	gotoxy(FrameX + 2*Frame_width+3, FrameY+19);
	printf("Space:暂停游戏");

	gotoxy(FrameX + 2*Frame_width+3, FrameY+15);

	printf("ESC:退出游戏");

	gotoxy(FrameX, FrameY);
	color(12);
	printf("◤");

	gotoxy(FrameX + 2*Frame_width - 2, FrameY);
	printf("◥");

	gotoxy(FrameX,FrameY+Frame_height);
	printf("◣");

	gotoxy(FrameX +2*Frame_width - 2, FrameY + Frame_height);
	printf("◢");

	a[FrameX][FrameY+Frame_height] = 2;
	a[FrameX+2*Frame_width - 2][FrameY+Frame_height] = 2;

	for(i=2; i<2*Frame_width-3; i+=2) {
		gotoxy(FrameX+i,FrameY);
		printf("☆");//☆?■?
	}

	for(i=2; i<2*Frame_width - 3; i+=2) {
		gotoxy(FrameX+i,FrameY+Frame_height);
		printf("☆");
		a[FrameX+i][FrameY+Frame_height] = 2;
	}

	for(i=1; i<Frame_height; i++) {
		gotoxy(FrameX, FrameY+i);
		printf("☆");
		a[FrameX][FrameY+i] = 2;
	}

	for(i=1; i<Frame_height; i++) {
		gotoxy(FrameX+2 * Frame_width-2,FrameY+i);
		printf("☆");
		a[FrameX+2*Frame_width-2][FrameY+i] = 2;
	}

//	color(14);
}

void MakeTetris(struct Tetris *tetris) {
	a[tetris->x][tetris->y] = b[0];

	switch(tetris->flag) {
		case 1: { /**田方块**/
			color(10);
			a[tetris->x][tetris->y-1] = b[1];
			a[tetris->x+2][tetris->y-1] = b[2];
			a[tetris->x+2][tetris->y] = b[3];
			break;
		}
		case 2: { /**水平直线方块**/
			color(13);
			a[tetris->x-2][tetris->y] = b[1];
			a[tetris->x+2][tetris->y] = b[2];
			a[tetris->x+4][tetris->y] = b[3];
			break;
		}
		case 3: { /**垂直直线方块**/
			color(13);
			a[tetris->x][tetris->y-1] = b[1];
			a[tetris->x][tetris->y-2] = b[2];
			a[tetris->x][tetris->y+1] = b[3];
			break;
		}
		case 4: { /*T字方块*/
			color(11);
			a[tetris->x-2][tetris->y] = b[1];
			a[tetris->x+2][tetris->y] = b[2];
			a[tetris->x][tetris->y+1] = b[3];
			break;
		}
		case 5: {
			color(11);
			a[tetris->x][tetris->y-1] = b[1];
			a[tetris->x][tetris->y+1] = b[2];
			a[tetris->x-2][tetris->y] = b[3];
			break;
		}
		case 6: {
			color(11);
			a[tetris->x][tetris->y-1] = b[1];
			a[tetris->x-2][tetris->y] = b[2];
			a[tetris->x+2][tetris->y] = b[3];
			break;
		}
		case 7: {
			color(11);
			a[tetris->x][tetris->y-1] = b[1];
			a[tetris->x][tetris->y+1] = b[2];
			a[tetris->x+2][tetris->y] = b[3];
			break;
		}
		case 8: {
			color(14);
			a[tetris->x][tetris->y+1] = b[1];
			a[tetris->x-2][tetris->y] = b[2];
			a[tetris->x+2][tetris->y+1] = b[3];
			break;
		}
		case 9: {
			color(14);
			a[tetris->x][tetris->y-1] = b[1];
			a[tetris->x-2][tetris->y] = b[2];
			a[tetris->x-2][tetris->y+1] = b[3];
			break;
		}
		case 10: {
			color(14);
			a[tetris->x][tetris->y-1] = b[1];
			a[tetris->x-2][tetris->y-1] = b[2];
			a[tetris->x+2][tetris->y] = b[3];
			break;
		}
		case 11: {
			color(14);
			a[tetris->x][tetris->y+1] = b[1];
			a[tetris->x-2][tetris->y-1] = b[2];
			a[tetris->x-2][tetris->y] = b[3];
			break;
		}
		case 12: {
			color(14);
			a[tetris->x][tetris->y-1] = b[1];
			a[tetris->x][tetris->y+1] = b[2];
			a[tetris->x-2][tetris->y-1] = b[3];
			break;
		}
		case 13: {
			color(12);
			a[tetris->x-2][tetris->y] = b[1];
			a[tetris->x+2][tetris->y-1] = b[2];
			a[tetris->x+2][tetris->y] = b[3];
			break;
		}
		case 14: {
			color(12);
			a[tetris->x][tetris->y-1] = b[1];
			a[tetris->x][tetris->y+1] = b[2];
			a[tetris->x+2][tetris->y+1] = b[3];
			break;
		}
		case 15: {
			color(12);
			a[tetris->x-2][tetris->y] = b[1];
			a[tetris->x-2][tetris->y+1] = b[2];
			a[tetris->x+2][tetris->y] = b[3];
			break;
		}
		case 16: {
			color(12);
			a[tetris->x][tetris->y+1] = b[1];
			a[tetris->x][tetris->y-1] = b[2];
			a[tetris->x+2][tetris->y-1] = b[3];
			break;
		}
		case 17: {
			color(12);
			a[tetris->x-2][tetris->y] = b[1];
			a[tetris->x+2][tetris->y+1] = b[2];
			a[tetris->x+2][tetris->y] = b[3];
			break;
		}
		case 18: {
			color(12);
			a[tetris->x][tetris->y-1] = b[1];
			a[tetris->x][tetris->y+1] = b[2];
			a[tetris->x-2][tetris->y+1] = b[3];
			break;
		}
		case 19: {
			color(12);
			a[tetris->x-2][tetris->y] = b[1];
			a[tetris->x-2][tetris->y-1] = b[2];
			a[tetris->x+2][tetris->y] = b[3];
			break;
		}

	}
}

void PrintTetris(struct Tetris *tetris) {
	int i;
	for(i=0; i<4; i++) {
		b[i] = 1;
	}

	MakeTetris(tetris);
	for(i=tetris->x-2; i<=tetris->x+4; i+=2) {
		for(j=tetris->y-2; j<=tetris->y+1; j++) {
			if (a[i][j] == 1 && j>FrameY) {
				gotoxy(i,j);
				printf("■");
			}
		}
	}

	gotoxy(FrameX+2*Frame_width+3,FrameY+1);
	color(4);
	printf("level : ");
	color(12);
	printf(" %d", tetris->level);
	gotoxy(FrameX+2*Frame_width+3, FrameY+3);
	color(4);
	printf("score : ");
	color(12);
	printf(" %d", tetris->score);
	gotoxy(FrameX+2*Frame_width+3, FrameY+5);
	color(4);
	printf("speed : ");
	color(12);
	printf(" %dms", tetris->speed);
}

int ifMove(struct Tetris *tetris) {
	if (a[tetris->x][tetris->y]!=0) {
		return 0;
	} else {
		if (
		    (tetris->flag == 1 && (a[tetris->x][tetris->y-1] == 0 &&
		                           a[tetris->x+2][tetris->y-1] == 0 && a[tetris->x+2][tetris->y] == 0)) ||
		    ( tetris->flag == 2 && ( a[tetris->x-2][tetris->y] == 0 &&
		                             a[tetris->x+2][tetris->y] == 0 && a[tetris->x+4][tetris->y] == 0)) ||
		    ( tetris->flag == 3 && ( a[tetris->x][tetris->y-1] == 0 &&
		                             a[tetris->x][tetris->y-2] == 0 && a[tetris->x][tetris->y+1] == 0)) ||
		    ( tetris->flag == 4 && ( a[tetris->x-2][tetris->y] == 0 &&
		                             a[tetris->x+2][tetris->y] == 0 && a[tetris->x][tetris->y+1] == 0)) ||
		    ( tetris->flag == 5 && ( a[tetris->x][tetris->y-1] == 0 &&
		                             a[tetris->x][tetris->y+1] == 0 && a[tetris->x-2][tetris->y] == 0)) ||
		    ( tetris->flag == 6 && ( a[tetris->x][tetris->y-1] == 0 &&
		                             a[tetris->x-2][tetris->y] == 0 && a[tetris->x+2][tetris->y] == 0)) ||
		    ( tetris->flag == 7 && ( a[tetris->x][tetris->y-1] == 0 &&
		                             a[tetris->x][tetris->y+1] == 0 && a[tetris->x+2][tetris->y] == 0)) ||
		    ( tetris->flag == 8 && ( a[tetris->x][tetris->y+1] == 0 &&
		                             a[tetris->x-2][tetris->y] == 0 && a[tetris->x+2][tetris->y+1] == 0)) ||
		    ( tetris->flag == 9 && ( a[tetris->x][tetris->y-1] == 0 &&
		                             a[tetris->x-2][tetris->y] == 0 && a[tetris->x-2][tetris->y+1] == 0)) ||
		    ( tetris->flag == 10 && ( a[tetris->x][tetris->y-1] == 0 &&
		                              a[tetris->x-2][tetris->y-1] == 0 && a[tetris->x+2][tetris->y] == 0)) ||
		    ( tetris->flag == 11 && ( a[tetris->x][tetris->y+1] == 0 &&
		                              a[tetris->x-2][tetris->y-1] == 0 && a[tetris->x-2][tetris->y] == 0)) ||
		    ( tetris->flag == 12 && ( a[tetris->x][tetris->y-1] == 0 &&
		                              a[tetris->x][tetris->y+1] == 0 && a[tetris->x-2][tetris->y-1] == 0)) ||
		    ( tetris->flag == 15 && ( a[tetris->x-2][tetris->y] == 0 &&
		                              a[tetris->x-2][tetris->y+1] == 0 && a[tetris->x+2][tetris->y] == 0)) ||
		    ( tetris->flag == 14 && ( a[tetris->x][tetris->y-1] == 0 &&
		                              a[tetris->x][tetris->y+1] == 0 && a[tetris->x+2][tetris->y+1] == 0)) ||
		    ( tetris->flag == 13 && ( a[tetris->x-2][tetris->y] == 0 &&
		                              a[tetris->x+2][tetris->y-1] == 0 && a[tetris->x+2][tetris->y] == 0)) ||
		    ( tetris->flag == 16 && ( a[tetris->x][tetris->y+1] == 0 &&
		                              a[tetris->x][tetris->y-1] == 0 && a[tetris->x+2][tetris->y-1] == 0)) ||
		    ( tetris->flag == 19 && ( a[tetris->x-2][tetris->y] == 0 &&
		                              a[tetris->x-2][tetris->y-1] == 0 && a[tetris->x+2][tetris->y] == 0)) ||
		    ( tetris->flag == 18 && ( a[tetris->x][tetris->y-1] == 0 &&
		                              a[tetris->x][tetris->y+1] == 0 && a[tetris->x-2][tetris->y+1] == 0)) ||
		    ( tetris->flag == 17 && ( a[tetris->x-2][tetris->y] == 0 &&
		                              a[tetris->x+2][tetris->y+1] == 0 && a[tetris->x+2][tetris->y] == 0))) {
			return 1;
		}
	}
	return 0;
}

void CleanTetris(struct Tetris *tetris) {
	int i,j;
	for(i = 0; i<4; i++) {
		b[i] = 0;
	}
	MakeTetris(tetris);
	for (i=tetris->x-2; i<=tetris->x+4; i+=2) {
		for (j=tetris->y-2; j<=tetris->y+1; j++) {
			if(a[i][j] == 0 && j> FrameY) {
				gotoxy(i,j);
				printf(" "); //清除方块
			}
		}
	}
}

void Flag(struct Tetris *tetris) {
	tetris->number++;
	srand(time(NULL));
	if (tetris->number == 1) {
		tetris->flag = rand()%19 + 1;
	}
	tetris->next = rand()%19 + 1;
}

/**
 * 判断是否满航，并删除满行的方块
 */
void Del_Fullline(struct Tetris *tetris) {
	int k,del_rows=0;
	for(j=FrameY+Frame_height-1; j>=FrameY+1; j--) 
	{
		k = 0;
		for(i=FrameX+2; i<FrameX+2*Frame_width-2; i+=2) {
			if(a[i][j] == 1) {
				k++;
				if(k==Frame_width - 2) {
					for(k=FrameX+2; k<FrameX+2*Frame_width-2; k+=2) {
						a[k][j] = 0;
						gotoxy(k,j);
						printf("  ");
					}
					for(k=j-1; k>FrameY; k--) {
						for(i=FrameX+2; i<FrameX+2*Frame_width-2; i+=2) {
							if(a[i][k] == 1) {
								a[i][k] = 0;
								gotoxy(i,k);
								printf("  ");
								a[i][k+1] = 1;
								gotoxy(i,k+1);
								printf("■");
							}
						}
					}
					j++;
					del_rows++;
				}
			}

		}
	}
	tetris->score+=100*del_rows;
	if (del_rows>0 && (tetris->score%1000 == 0 || tetris->score/1000>tetris->level-1)) {
		tetris->speed -=20;
		tetris->level++;
	}

}



void Gameplay() {
	int n;
	struct Tetris t,*tetris=&t;
	char ch;
	tetris->number = 0;
	tetris->speed = 300;
	tetris->score = 0;
	tetris->level = 1;
	while(1) {
		Flag(tetris);
		Temp = tetris->flag; //记住当前的俄罗斯方块序号
		tetris->x = FrameX+2*Frame_width+6;
		tetris->y = FrameY+10;
		tetris->flag = tetris->next; //获取下一个方块的序号
		PrintTetris(tetris);
		tetris->x = FrameX + Frame_width;
		tetris->y = FrameY - 1;
		tetris->flag = Temp; //取出当前的俄罗斯方块序号
		while(1) {
label:
			PrintTetris(tetris);//打印俄罗斯方块
			Sleep(tetris->speed);//延缓时间
			CleanTetris(tetris);
			Temp1 = tetris->x;
			Temp2 = tetris->flag;
			if(kbhit()) {
				ch = getch();
				if(ch == 75) {
					tetris->x-=2;
				}
				if(ch == 77) {
					tetris->x+=2;
				}
				if(ch == 80) {
					if (ifMove(tetris)!=0) {
						tetris->y+=2;
					}
					if (ifMove(tetris) == 0) {
						tetris->y = FrameY+Frame_height - 2;
					}
				}
				if (ch == 72) {
					if (tetris->flag>=2 && tetris->flag <=3) {
						tetris->flag++;
						tetris->flag%=2;
						tetris->flag+=2;
					}
					if (tetris->flag >= 4 && tetris->flag <= 7) {
						tetris->flag++;
						tetris->flag%=4;
						tetris->flag+=4;
					}
					if (tetris->flag >= 8 && tetris->flag <= 11) {
						tetris->flag++;
						tetris->flag%=4;
						tetris->flag+=8;
					}
					if (tetris->flag >= 12 && tetris->flag <= 19) {
						tetris->flag++;
						tetris->flag%=4;
						tetris->flag+=16;
					}
				}
				if (ch == 32) {
					PrintTetris(tetris);
					while(1) {
						if (kbhit()) {
							ch = getch();
							if (ch == 32) {
								goto label;
							}
						}
					}
				}
				if (ch == 27) {
					system("cls");
					memset(a, 0, 6400*sizeof(int));
					welcome();
				}
				if (ifMove(tetris) == 0) {
					tetris->x = Temp1;
					tetris->flag = Temp2;
				} else {
					goto label;
				}
			}
			tetris->y++;
			if (ifMove(tetris) == 0) {
				tetris->y--;
				PrintTetris(tetris);
				Del_Fullline(tetris);
				break;
			}
		}

		//游戏结束条件：方块接触到框顶位置
		for(i=tetris->y-2; i<tetris->y+2; i++) {
			if (i == FrameY) {
				system("cls");
				gotoxy(29, 7);
				printf("  \n");
				color(12);
				printf("\t\t\t■■■■   ■      ■    ■■     \n");
				printf("\t\t\t■         ■■    ■    ■  ■   \n");
				printf("\t\t\t■■■     ■  ■  ■    ■   ■  \n");
				printf("\t\t\t■         ■    ■■    ■  ■   \n");
				printf("\t\t\t■■■■   ■      ■    ■■     \n");
				gotoxy(17, 18);
				color(14);
				printf("我要重新玩一局-------1");
				gotoxy(44, 18);
				printf("不玩了，退出吧-------2\n");
				int n;
				gotoxy(32, 20);
				printf("选择【1/2】：");
				color(11);
				scanf("%d", &n);
				switch(n) {
					case 1:
						system("cls");
						Replay(tetris);
						break;
					case 2:
						exit(0);
						break;
				}
			}
		}
		tetris->flag = tetris->next;
		tetris->x = FrameX+2*Frame_width+6;
		tetris->y = FrameY+10;
		CleanTetris(tetris);

	}
}

void Replay(struct Tetris *tetris) {
	system("cls");
	memset(a,0,6400*sizeof(int));
	DrwaGameframe();
	Gameplay();
}

void explation() {
	int i, j = 1;
	system("cls");
	color(13);
	gotoxy(32, 3);
	printf("按键说明");
	color(2);
	for (i = 6; i <= 16; i++) {
		for(j = 15; j <= 60; j++) {
			gotoxy(j, i);
			if (i == 6|| i== 16) {
				printf("=");
			} else if (j == 15 || j == 59) {
				printf("||");
			}
		}
		color(3);
		gotoxy(18, 7);
		printf("tip1:玩家可以通过<- ->方向键来移动方块");
		color(10);
		gotoxy(18, 9);
		printf("tip2:通过↑使方块旋转");
		color(14);
		gotoxy(18, 11);
		printf("tip3:通过↓加速方块下落");
		color(11);
		gotoxy(18, 13);
		printf("tip4:按空格键暂停游戏，再按空格键继续");
		color(4);
		gotoxy(18, 15);
		printf("tip5:按ESC退出游戏");
		getch();
		system("cls");
		main();
	}
}

void regulation() {
	int i, j = 1;
	system("cls");
	color(13);
	gotoxy(34, 3);
	printf("游戏规则");
	color(2);
	for (i = 6; i<= 18; i++) {
		for (j = 12; j <= 70; j++) {
			gotoxy(j, i);
			if (i == 6 || i == 18) {
				printf("=");
			} else if (j == 12 || j == 69) {
				printf("||");
			}
		}

	}
	color(12);
	gotoxy(16, 7);
	printf("tip1:不同形状的小方块从屏幕上方落下，玩家通过调整");
	gotoxy(22,9);
	printf("方块的位置和方向，使它们在屏幕底部拼出完整的");
	gotoxy(22, 11);
	printf("一行或几行");
	color(14);
	gotoxy(16, 13);
	printf("tip2:每消除一行，积分增加100");
	color(11);
	gotoxy(16, 15);
	printf("tip3:每累计1000分，会提升一个等级");
	color(10);
	gotoxy(16, 17);
	printf("tip4:提升等级会使方块下落速度加快，游戏难度加大");
	getch();
	system("cls");
	welcome();
}

void closed() {
	exit(0);
}


int main(int argc, const char * argv[]) {
	title();
	flower();
	welcome();
	DrwaGameframe();
	Gameplay();
	printf("\n");
//    printf("Hello, World!\n");
	return 0;
}
