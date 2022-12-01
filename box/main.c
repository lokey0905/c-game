#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include<time.h>
#include<windows.h> 
#define height 10
#define width 10
#define debugmode 0
#define rulefile "..//rule.txt"
#define levelfile "..//level.txt"

void setup();
void showrull();
void gameover();
void readfile();
int map[height][width] = { 0 };
int map_h = 1, map_w = 1, level = 1;

void print(int x, int y, int *string) {
	COORD pos;	pos.X = x;	pos.Y = y;//偏移遊標位置
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);//偏移遊標位置
	switch (*string){
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

void buildrandmap(int map_w,int map_h) {
	int box = 0, point = 0; //點與箱子

	for (int i = 1;i < map_h - 1;i++) {  //生成路
		for (int k = 1;k < map_w - 1;k++) {
			map[i][k] = 1; //1是路
		}
	}
	if (debugmode) printf("done ");

	for (int i = 1;i < map_h - 1;i++) {  //隨機生成牆
		for (int k = 1;k < map_w - 1;k++) {
			if (!((rand() * rand()) % (map_w * map_h))) {
				map[i][k] = 0;
				//if (debugmode) break;
			}
		}
		//if (debugmode) break;
	}
	//a[3][1] = 0;

	map[map_h / 2][map_h / 2] = 5;

	if (debugmode) printf("done\n");

	while (!point || point < map_w * map_h / 15) { //生成點
		for (int i = 0;i < map_h;i++) {
			for (int k = 0;k < map_w;k++) {
				if (map[i][k] == 1 && map[i][k] != 4) {
					if (!(rand() % (map_w * map_h))) {
						map[i][k] = 2;
						point++;//幾個點
						if (debugmode) break;
					}
				}
			}
		}
	}
	if (debugmode) printf("point:%d\n", point);

	while (box < point) { //生成箱子
		for (int i = 2;i < map_h - 2;i++) {
			for (int k = 2;k < map_w - 2;k++) {
				if (map[i][k] == 1 && map[i][k] != 2 && map[i][k] != 5) {
					if (!(rand() % 10)) {
						if (box >= point) break;
						map[i][k] = 3;
						box++;//幾個點
					}
				}
			}
		}
	}
	if (debugmode) printf("box:%d\n", box);
	if (debugmode) system("pause");
}
	

int run() {
	setup();	//初始設定
	int n = 0, box = 0, x = 1, y = 1;
	while (1) {
		box = 0;
		for (int i = 0;i < map_h + 2;i++) {	//顯示
			for (int k = 0;k < map_w + 2;k++) {
				print((k + 1) * 2, (i + 1), &map[i][k]);	//呼叫輸出函式
				if (!i)	!level ? printf("  目前關卡： 隨機模式 %dx%d", map_w, map_h) : printf("  目前關卡： %d", level);
				if (i == 1)	printf("  移動次數： %d", n);	//顯示移動次數
				if (map[i][k] == 5) { x = k; y = i; }	//定位玩家位置
				if (map[i][k] == 3)	box++;
			}
		}
		/*box = 0;
		for (int i = 1;i < height - 1;i++) {  //check box
			for (int k = 1;k < width - 1;k++) {
				if (a[i][k] == 3)
					box++;
			}
		}*/
		if (!box) {
			gameover(n);
			if (_getch() != 27) return 1;
			else	return 0;
		}

		char get = _getch();

		if (get == 27)	return 0;	//ESC
		if (get == 'r')	return 1;	//try again
		if (get == 'w' && map[y - 1][x]) {
			n++;
			switch (map[y - 1][x]) {
			case 1:
				map[y - 1][x] = 5;
				if (map[y][x] == 6) map[y][x] = 2;
				else map[y][x] = 1;
				y--;
				break;

			case 2:
				map[y - 1][x] = 6;
				if (map[y][x] == 6) map[y][x] = 2;
				else map[y][x] = 1;
				y--;
				break;

			case 3:
				if (map[y - 2][x] == 1) {
					map[y - 2][x] = 3;
					map[y - 1][x] = 5;
					if (map[y][x] == 6) map[y][x] = 2;
					else map[y][x] = 1;
					y--;
				}
				else if (map[y - 2][x] == 2) {
					map[y - 2][x] = 4;
					map[y - 1][x] = 5;
					if (map[y][x] == 6) map[y][x] = 2;
					else map[y][x] = 1;
					y--;
				}
				break;

			case 4:
				if (map[y - 2][x] == 1) {
					map[y - 2][x] = 3;
					map[y - 1][x] = 6;
					if (map[y][x] == 6) map[y][x] = 2;
					else map[y][x] = 1;
					y--;
				}
				else if (map[y - 2][x] == 2) {
					map[y - 2][x] = 4;
					map[y - 1][x] = 6;
					if (map[y][x] == 6) map[y][x] = 2;
					else map[y][x] = 1;
					y--;
				}
				break;

			default:
				break;
			}

		}
		else if (get == 'a' && map[y][x - 1]) {
			n++;
			switch (map[y][x - 1]) {
			case 1:
				map[y][x - 1] = 5;
				if (map[y][x] == 6) map[y][x] = 2;
				else map[y][x] = 1;
				x--;
				break;

			case 2:
				map[y][x - 1] = 6;
				if (map[y][x] == 6) map[y][x] = 2;
				else map[y][x] = 1;
				x--;
				break;

			case 3:
				if (map[y][x - 2] == 1) {
					map[y][x - 2] = 3;
					map[y][x - 1] = 5;
					if (map[y][x] == 6) map[y][x] = 2;
					else map[y][x] = 1;
					x--;
				}
				else if (map[y][x - 2] == 2) {
					map[y][x - 2] = 4;
					map[y][x - 1] = 5;
					if (map[y][x] == 6) map[y][x] = 2;
					else map[y][x] = 1;
					x--;
				}
				break;

			case 4:
				if (map[y][x - 2] == 1) {
					map[y][x - 2] = 3;
					map[y][x - 1] = 6;
					if (map[y][x] == 6) map[y][x] = 2;
					else map[y][x] = 1;
					x--;
				}
				else if (map[y][x - 2] == 2) {
					map[y][x - 2] = 4;
					map[y][x - 1] = 6;
					if (map[y][x] == 6) map[y][x] = 2;
					else map[y][x] = 1;
					x--;
				}
				break;

			default:
				break;
			}

		}
		else if (get == 's' && map[y + 1][x]) {
			n++;
			switch (map[y + 1][x]) {
			case 1:
				map[y + 1][x] = 5;
				if (map[y][x] == 6) map[y][x] = 2;
				else map[y][x] = 1;
				y++;
				break;

			case 2:
				map[y + 1][x] = 6;
				if (map[y][x] == 6) map[y][x] = 2;
				else map[y][x] = 1;
				y++;
				break;

			case 3:
				if (map[y + 2][x] == 1) {
					map[y + 2][x] = 3;
					map[y + 1][x] = 5;
					if (map[y][x] == 6) map[y][x] = 2;
					else map[y][x] = 1;
					y++;
				}
				else if (map[y + 2][x] == 2) {
					map[y + 2][x] = 4;
					map[y + 1][x] = 5;
					if (map[y][x] == 6) map[y][x] = 2;
					else map[y][x] = 1;
					y++;
				}
				break;

			case 4:
				if (map[y + 2][x] == 1) {
					map[y + 2][x] = 3;
					map[y + 1][x] = 6;
					if (map[y][x] == 6) map[y][x] = 2;
					else map[y][x] = 1;
					y++;
				}
				else if (map[y + 2][x] == 2) {
					map[y + 2][x] = 4;
					map[y + 1][x] = 6;
					if (map[y][x] == 6) map[y][x] = 2;
					else map[y][x] = 1;
					y++;
				}
				break;

			default:
				break;
			}

		}
		else if (get == 'd' && map[y][x + 1]) {
			n++;
			switch (map[y][x + 1]) {
			case 1:
				map[y][x + 1] = 5;
				if (map[y][x] == 6) map[y][x] = 2;
				else map[y][x] = 1;
				x++;
				break;

			case 2:
				map[y][x + 1] = 6;
				if (map[y][x] == 6) map[y][x] = 2;
				else map[y][x] = 1;
				x++;
				break;

			case 3:
				if (map[y][x + 2] == 1) {
					map[y][x + 2] = 3;
					map[y][x + 1] = 5;
					if (map[y][x] == 6) map[y][x] = 2;
					else map[y][x] = 1;
					x++;
				}
				else if (map[y][x + 2] == 2) {
					map[y][x + 2] = 4;
					map[y][x + 1] = 5;
					if (map[y][x] == 6) map[y][x] = 2;
					else map[y][x] = 1;
					x++;
				}
				break;

			case 4:
				if (map[y][x + 2] == 1) {
					map[y][x + 2] = 3;
					map[y][x + 1] = 6;
					if (map[y][x] == 6) map[y][x] = 2;
					else map[y][x] = 1;
					x++;
				}
				else if (map[y][x + 2] == 2) {
					map[y][x + 2] = 4;
					map[y][x + 1] = 6;
					if (map[y][x] == 6) map[y][x] = 2;
					else map[y][x] = 1;
					x++;
				}
				break;

			default:
				break;
			}
		}
	}
}

int main(void){
	showrull();
	while (run()); //遊戲主體
	gameover(0);
	printf("\n\t\t\t\t~~~感謝遊玩~~~\n");
	system("pause");
	return(0);
}

void readfile(char filename[]) {
	FILE* file;	// 宣告指向檔案的結構指標
	char cStr[126];	// 存放讀取的字元
	int l=1;
	for (int i = 0;i < height;i++) {  //清除先前地圖檔
		for (int k = 0;k < width ;k++) {
			map[i][k] = 0;
		}
	}

	if ((file = fopen(filename, "r")) == NULL) {  // 判斷檔案是否開啟失敗
		printf("%s 檔案無法開啟", filename);
	}
	rewind(file);
	while (!feof(file)) {	//判斷是否讀到檔案尾
		if (!strncmp(filename, rulefile, strlen(rulefile))) {
			fgets(cStr, 126, file);
			printf("%s", cStr);
		}
		if (!strncmp(filename, levelfile, strlen(levelfile))) {
			fscanf(file, "%d %d", &map_h,&map_w);
			int num=0;
			for (int i = 1;i < map_h + 1;i++) {  //生成地圖
				for (int k = 1;k < map_w + 1;k++) {
					fscanf(file, " %d", &map[i][k]);
				}
			}
			if(l == level)	break;
			l++;
		}
	}
	fclose(file);
}

void showrull() {
	system("color 7");	//黑底白字
	system("title 倉庫番 made by lokey");
	system("mode con cols=79 lines=12");//視窗大小設定
	system("type \"..\\welcome.txt\"");	//顯示歡迎訊息
	printf("\n\n\t\t\t 按下任一鍵進入遊戲....");_getch();
	system("cls");
	system("mode con cols=57 lines=22");//視窗大小設定
	readfile(rulefile);					//讀取規則
	printf("\n\n");	system("pause");
}

void setup() {
	system("color 7");
	srand(time(NULL));
	system("cls");
	printf("\n\n\t\tlevel:0(隨機模式),1,2,3");
	printf("\n\n\t\t\t level:");
	scanf("%d", &level);
	if (!level) {
		printf("\n\n\t\t請輸入自訂大小 長 寬:");
		scanf("%d %d", &map_w, &map_h);	
		buildrandmap(map_w+2, map_h+2);
	}
	else if (level >= 1 && level <= 3)	readfile(levelfile);
	else setup();
	system("mode con cols=52 lines=20");
}

void gameover(int score) {
	//system("cls");
	system("color 4");
	printf("\n\n");
	printf("\t\t\t   ****遊戲結束****\n\a");
	if (score) {
		printf("\t\t\t****你的移動步數：%d****\n\n", score);
		printf("\t\t\t按ESC退出,按任一鍵重新遊戲\n");
	}
}
