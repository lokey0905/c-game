#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include<time.h>
#include<windows.h> 
#define height 10
#define width 10
#define debugmode 0


void setup() {
	system("color 07");
	system("title 倉庫番");
	system("mode con cols=52 lines=20");
	printf("\n~~~遊戲介紹~~~\n\n");
	printf("■：牆壁\n"); //0是牆
	printf("　：(空白)是路\n"); //1是路
	printf("＊：目標位置\n"); //2是點
	printf("Ｘ：箱子\n"); //3是箱子
	printf("※：在目標位置的箱子\n"); //4是箱子在點上
	printf("＠：玩家位置\n"); //5是玩家
	printf("◎：玩家在目標位置上\n\n"); //5是玩家在點上
	system("pause");
	printf("\n~~~遊戲規則~~~\n\n");
	printf("以「推」的方式，推動箱子。可以在沒有阻礙物（如牆壁等的阻礙物）的情況下，向左、右、上、下的地方移動。將箱子移動到指定點，達到指定數量，即可過關。\n");
	system("pause");
	printf("但玩家移動箱子，有下列條件要注意：\n\n推到牆壁的箱子，玩家就不可以背對牆壁，把箱子推回到空處。即箱子只能以「推」的方式移動，不能以「拉」的方式移動。但如果玩家推至牆壁後，垂直牆壁的兩側沒有阻礙物，則玩家可以朝這兩個不同的方向推移箱子。\n\n一旦箱子被移動到角落，玩家沒有任何方法再移動這個箱子。玩家不可同時推動兩個或以上的箱子。假設工人面前有一個箱子，箱子的正前方又有一個箱子，則這兩個箱子是不能推動的。\n");
	system("pause");
}

void gameover(int score) {
	//system("cls");
	system("color 07");
	printf("\n\n");
	printf("\t\t\t   ****遊戲結束****\n\a");
	if (score) {
		printf("\t\t\t****你的移動步數：%d****\n\n", score);
		printf("\t\t\t按ESC退出,按任一鍵重新遊戲\n");
	}
}

void print(int x, int y, int string) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);//偏移遊標位置
	switch (string)
	{
	case 0:
		printf("■"); //0是牆
		break;

	case 1:
		printf("　"); //1是路
		break;

	case 2:
		printf("＊"); //2是點
		break;

	case 3:
		printf("Ｘ"); //3是箱子
		break;

	case 4:
		printf("※"); //4是箱子在點上
		break;

	case 5:
		printf("＠"); //5是玩家
		break;

	case 6:
		printf("◎"); //5是玩家在點上
		break;

	default:
		break;
	}

}

int run() {
	int a[height][width] = { 0 }; //0是牆
	int box = 0, point = 0;  //點與箱子

	for (int i = 1;i < height - 1;i++) {  //生成路
		for (int k = 1;k < width - 1;k++) {
			a[i][k] = 1; //1是路
		}
	}
	if (debugmode) printf("bone ");

	for (int i = 1;i < height - 1;i++) {  //隨機生成牆
		for (int k = 1;k < width - 1;k++) {
			if (!((rand() * rand()) % (height * width))) {
				a[i][k] = 0;
				//if (debugmode) break;
			}
		}
		//if (debugmode) break;
	}
	//a[3][1] = 0;

	int x = width / 2, y = height / 2;
	a[y][x] = 5;

	if (debugmode) printf("bone\n");

	while (!point || point < height * width / 15) { //生成點
		for (int i = 0;i < height;i++) {
			for (int k = 0;k < width;k++) {
				if (a[i][k] == 1 && a[i][k] != 4) {
					if (!(rand() % (height * width))) {
						a[i][k] = 2;
						point++;//幾個點
						if (debugmode) break;
					}
				}
			}
		}
	}
	if (debugmode) printf("point:%d\n", point);

	while (box < point) { //生成箱子
		for (int i = 2;i < height - 2;i++) {
			for (int k = 2;k < width - 2;k++) {
				if (a[i][k] == 1 && a[i][k] != 2 && a[i][k] != 5) {
					if (!(rand() % 10)) {
						if (box >= point) break;
						a[i][k] = 3;
						box++;//幾個點

					}
				}
			}
		}
	}
	if (debugmode) printf("box:%d\n", box);
	if (debugmode) system("pause");
	int n = 0;
	while (1) {
		system("cls");
		for (int i = 0;i < height;i++) { //顯示
			for (int k = 0;k < width;k++) {
				print((k + 1) * 2, (i + 1), a[i][k]);
			}
		}

		box = 0;
		for (int i = 1;i < height - 1;i++) {  //check box
			for (int k = 1;k < width - 1;k++) {
				if (a[i][k] == 3)
					box++;
			}
		}
		if (!box) {
			gameover(n);
			if (_getch() != 27) return 1;
			else { return 0; break; }
		}
		printf("  移動次數： %d", n);
		char get = _getch();

		if (get == 27) { return 0; break; }
		if (get == 'w' && a[y - 1][x]) {
			n++;
			switch (a[y - 1][x]) {
			case 1:
				a[y - 1][x] = 5;
				if (a[y][x] == 6) a[y][x] = 2;
				else a[y][x] = 1;
				y--;
				break;

			case 2:
				a[y - 1][x] = 6;
				if (a[y][x] == 6) a[y][x] = 2;
				else a[y][x] = 1;
				y--;
				break;

			case 3:
				if (a[y - 2][x] == 1) {
					a[y - 2][x] = 3;
					a[y - 1][x] = 5;
					if (a[y][x] == 6) a[y][x] = 2;
					else a[y][x] = 1;
					y--;
				}
				else if (a[y - 2][x] == 2) {
					a[y - 2][x] = 4;
					a[y - 1][x] = 5;
					if (a[y][x] == 6) a[y][x] = 2;
					else a[y][x] = 1;
					y--;
				}
				break;

			case 4:
				if (a[y - 2][x] == 1) {
					a[y - 2][x] = 3;
					a[y - 1][x] = 6;
					if (a[y][x] == 6) a[y][x] = 2;
					else a[y][x] = 1;
					y--;
				}
				else if (a[y - 2][x] == 2) {
					a[y - 2][x] = 4;
					a[y - 1][x] = 6;
					if (a[y][x] == 6) a[y][x] = 2;
					else a[y][x] = 1;
					y--;
				}
				break;

			default:
				break;
			}

		}
		else if (get == 'a' && a[y][x - 1]) {
			n++;
			switch (a[y][x - 1]) {
			case 1:
				a[y][x - 1] = 5;
				if (a[y][x] == 6) a[y][x] = 2;
				else a[y][x] = 1;
				x--;
				break;

			case 2:
				a[y][x - 1] = 6;
				if (a[y][x] == 6) a[y][x] = 2;
				else a[y][x] = 1;
				x--;
				break;

			case 3:
				if (a[y][x - 2] == 1) {
					a[y][x - 2] = 3;
					a[y][x - 1] = 5;
					if (a[y][x] == 6) a[y][x] = 2;
					else a[y][x] = 1;
					x--;
				}
				else if (a[y][x - 2] == 2) {
					a[y][x - 2] = 4;
					a[y][x - 1] = 5;
					if (a[y][x] == 6) a[y][x] = 2;
					else a[y][x] = 1;
					x--;
				}
				break;

			case 4:
				if (a[y][x - 2] == 1) {
					a[y][x - 2] = 3;
					a[y][x - 1] = 6;
					if (a[y][x] == 6) a[y][x] = 2;
					else a[y][x] = 1;
					x--;
				}
				else if (a[y][x - 2] == 2) {
					a[y][x - 2] = 4;
					a[y][x - 1] = 6;
					if (a[y][x] == 6) a[y][x] = 2;
					else a[y][x] = 1;
					x--;
				}
				break;

			default:
				break;
			}

		}
		else if (get == 's' && a[y + 1][x]) {
			n++;
			switch (a[y + 1][x]) {
			case 1:
				a[y + 1][x] = 5;
				if (a[y][x] == 6) a[y][x] = 2;
				else a[y][x] = 1;
				y++;
				break;

			case 2:
				a[y + 1][x] = 6;
				if (a[y][x] == 6) a[y][x] = 2;
				else a[y][x] = 1;
				y++;
				break;

			case 3:
				if (a[y + 2][x] == 1) {
					a[y + 2][x] = 3;
					a[y + 1][x] = 5;
					if (a[y][x] == 6) a[y][x] = 2;
					else a[y][x] = 1;
					y++;
				}
				else if (a[y + 2][x] == 2) {
					a[y + 2][x] = 4;
					a[y + 1][x] = 5;
					if (a[y][x] == 6) a[y][x] = 2;
					else a[y][x] = 1;
					y++;
				}
				break;

			case 4:
				if (a[y + 2][x] == 1) {
					a[y + 2][x] = 3;
					a[y + 1][x] = 6;
					if (a[y][x] == 6) a[y][x] = 2;
					else a[y][x] = 1;
					y++;
				}
				else if (a[y + 2][x] == 2) {
					a[y + 2][x] = 4;
					a[y + 1][x] = 6;
					if (a[y][x] == 6) a[y][x] = 2;
					else a[y][x] = 1;
					y++;
				}
				break;

			default:
				break;
			}

		}
		else if (get == 'd' && a[y][x + 1]) {
			n++;
			switch (a[y][x + 1]) {
			case 1:
				a[y][x + 1] = 5;
				if (a[y][x] == 6) a[y][x] = 2;
				else a[y][x] = 1;
				x++;
				break;

			case 2:
				a[y][x + 1] = 6;
				if (a[y][x] == 6) a[y][x] = 2;
				else a[y][x] = 1;
				x++;
				break;

			case 3:
				if (a[y][x + 2] == 1) {
					a[y][x + 2] = 3;
					a[y][x + 1] = 5;
					if (a[y][x] == 6) a[y][x] = 2;
					else a[y][x] = 1;
					x++;
				}
				else if (a[y][x + 2] == 2) {
					a[y][x + 2] = 4;
					a[y][x + 1] = 5;
					if (a[y][x] == 6) a[y][x] = 2;
					else a[y][x] = 1;
					x++;
				}
				break;

			case 4:
				if (a[y][x + 2] == 1) {
					a[y][x + 2] = 3;
					a[y][x + 1] = 6;
					if (a[y][x] == 6) a[y][x] = 2;
					else a[y][x] = 1;
					x++;
				}
				else if (a[y][x + 2] == 2) {
					a[y][x + 2] = 4;
					a[y][x + 1] = 6;
					if (a[y][x] == 6) a[y][x] = 2;
					else a[y][x] = 1;
					x++;
				}
				break;

			default:
				break;
			}
		}
	}
}

int main(void)
{
	srand(time(NULL));
	setup();
	while (run());
	gameover(0);
	printf("\n\t\t\t\t~~~感謝遊玩~~~\n");
	system("pause");
	return(0);
}
