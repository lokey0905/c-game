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
	system("title �ܮw�f");
	system("mode con cols=52 lines=20");
	printf("\n~~~�C������~~~\n\n");
	printf("���G���\n"); //0�O��
	printf("�@�G(�ť�)�O��\n"); //1�O��
	printf("���G�ؼЦ�m\n"); //2�O�I
	printf("��G�c�l\n"); //3�O�c�l
	printf("���G�b�ؼЦ�m���c�l\n"); //4�O�c�l�b�I�W
	printf("�I�G���a��m\n"); //5�O���a
	printf("���G���a�b�ؼЦ�m�W\n\n"); //5�O���a�b�I�W
	system("pause");
	printf("\n~~~�C���W�h~~~\n\n");
	printf("�H�u���v���覡�A���ʽc�l�C�i�H�b�S����ê���]�p���������ê���^�����p�U�A�V���B�k�B�W�B�U���a�貾�ʡC�N�c�l���ʨ���w�I�A�F����w�ƶq�A�Y�i�L���C\n");
	system("pause");
	printf("�����a���ʽc�l�A���U�C����n�`�N�G\n\n����������c�l�A���a�N���i�H�I������A��c�l���^��ųB�C�Y�c�l�u��H�u���v���覡���ʡA����H�u�ԡv���覡���ʡC���p�G���a���������A����������ⰼ�S����ê���A�h���a�i�H�³o��Ӥ��P����V�����c�l�C\n\n�@���c�l�Q���ʨ쨤���A���a�S�������k�A���ʳo�ӽc�l�C���a���i�P�ɱ��ʨ�өΥH�W���c�l�C���]�u�H���e���@�ӽc�l�A�c�l�����e��S���@�ӽc�l�A�h�o��ӽc�l�O������ʪ��C\n");
	system("pause");
}

void gameover(int score) {
	//system("cls");
	system("color 07");
	printf("\n\n");
	printf("\t\t\t   ****�C������****\n\a");
	if (score) {
		printf("\t\t\t****�A�����ʨB�ơG%d****\n\n", score);
		printf("\t\t\t��ESC�h�X,�����@�䭫�s�C��\n");
	}
}

void print(int x, int y, int string) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);//�����C�Ц�m
	switch (string)
	{
	case 0:
		printf("��"); //0�O��
		break;

	case 1:
		printf("�@"); //1�O��
		break;

	case 2:
		printf("��"); //2�O�I
		break;

	case 3:
		printf("��"); //3�O�c�l
		break;

	case 4:
		printf("��"); //4�O�c�l�b�I�W
		break;

	case 5:
		printf("�I"); //5�O���a
		break;

	case 6:
		printf("��"); //5�O���a�b�I�W
		break;

	default:
		break;
	}

}

int run() {
	int a[height][width] = { 0 }; //0�O��
	int box = 0, point = 0;  //�I�P�c�l

	for (int i = 1;i < height - 1;i++) {  //�ͦ���
		for (int k = 1;k < width - 1;k++) {
			a[i][k] = 1; //1�O��
		}
	}
	if (debugmode) printf("bone ");

	for (int i = 1;i < height - 1;i++) {  //�H���ͦ���
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

	while (!point || point < height * width / 15) { //�ͦ��I
		for (int i = 0;i < height;i++) {
			for (int k = 0;k < width;k++) {
				if (a[i][k] == 1 && a[i][k] != 4) {
					if (!(rand() % (height * width))) {
						a[i][k] = 2;
						point++;//�X���I
						if (debugmode) break;
					}
				}
			}
		}
	}
	if (debugmode) printf("point:%d\n", point);

	while (box < point) { //�ͦ��c�l
		for (int i = 2;i < height - 2;i++) {
			for (int k = 2;k < width - 2;k++) {
				if (a[i][k] == 1 && a[i][k] != 2 && a[i][k] != 5) {
					if (!(rand() % 10)) {
						if (box >= point) break;
						a[i][k] = 3;
						box++;//�X���I

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
		for (int i = 0;i < height;i++) { //���
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
		printf("  ���ʦ��ơG %d", n);
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
	printf("\n\t\t\t\t~~~�P�¹C��~~~\n");
	system("pause");
	return(0);
}
