#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h> 
void print(int x, int y, int* string) {
	COORD pos;	pos.X = x;	pos.Y = y;//�����C�Ц�m
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);//�����C�Ц�m
	switch (*string) {
	case 0:	printf("��");	break;	//0�O��
	case 1:	printf("�@");	break;	//1�O��
	case 2:	printf("��");	break;	//2�O�I
	case 3:	printf("��");	break;	//3�O�c�l
	case 4:	printf("��");	break;	//4�O�c�l�b�I�W
	case 5:	printf("�I");	break;	//5�O���a
	case 6:	printf("��");	break;	//6�O���a�b�I�W
	default:	break;
	}
}