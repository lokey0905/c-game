#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h> 
void print(int x, int y, int* string) {
	COORD pos;	pos.X = x;	pos.Y = y;//偏移遊標位置
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);//偏移遊標位置
	switch (*string) {
	case 0:	printf("■");	break;	//0是牆
	case 1:	printf("　");	break;	//1是路
	case 2:	printf("＊");	break;	//2是點
	case 3:	printf("Ｘ");	break;	//3是箱子
	case 4:	printf("※");	break;	//4是箱子在點上
	case 5:	printf("＠");	break;	//5是玩家
	case 6:	printf("◎");	break;	//6是玩家在點上
	default:	break;
	}
}