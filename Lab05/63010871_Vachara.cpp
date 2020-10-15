#include<stdio.h>
#include<conio.h>
#include<windows.h>
char ch = '.';
int direction = 0, x = 38, y = 20, bullet[5] = { 0 }, xbullet[5], ybullet[5] = { 20,20,20,20,20 }, bulletPoint = -1;

void gotoxy(int, int);
void setcolor(int, int);
void draw_shot(int, int);
void erase_shot(int, int);
void erase_ship(int, int);
void draw_ship(int, int);
void setcursor(bool);


int main()
{
	setcursor(0);
	draw_ship(x, y);

	do {
		for (int i = 0; i <= 5; i++)
		{
			if (bullet[i] == 0)
			{
				xbullet[i] = x;
			}
		}
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a' || ch == 'A') { direction = 1; }
			if (ch == 'd' || ch == 'D') { direction = 2; }
			if (ch == 's' || ch == 'S') { direction = 0; }
			if (ch == ' ' && bulletPoint < 4) { ++bulletPoint; bullet[bulletPoint] = 1; }

		}
		if (direction == 1 && x > 0)
		{
			erase_ship(x, y);
			draw_ship(--x, y);
		}
		if (direction == 2 && x < 75)
		{
			erase_ship(x, y);
			draw_ship(++x, y);
		}
		for (int j = 0; j <= 4; j++)
		{
			if (bullet[j] == 1 && ybullet > 0) {
				erase_shot(xbullet[j], ybullet[j]);
				draw_shot(xbullet[j], --ybullet[j]);
			}
		}
		if (ybullet[0] == 1) {
			erase_shot(xbullet[0], ybullet[0]);
			bullet[0] = 0;
			ybullet[0] = y;
			--bulletPoint;
			for (int k = 1; k <= 4; k++)
			{
				bullet[k - 1] = bullet[k];
				ybullet[k - 1] = ybullet[k];
				xbullet[k - 1] = xbullet[k];
			}
			bullet[4] = 0;
			ybullet[4] = y;
			xbullet[4] = x;
		}
		fflush(stdin);
		Sleep(100);
	} while (ch != 'x');
	return 0;
}

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void draw_ship(int x, int y)
{
	setcolor(2, 4);
	gotoxy(x, y);
	printf(" <-0-> ");

}

void erase_ship(int x, int y)
{
	setcolor(0, 0);
	gotoxy(x, y);
	printf("       ");
}

void draw_shot(int x, int y)
{
	setcolor(4, 6);
	gotoxy(x += 3, --y);
	printf("^");
}

void erase_shot(int x, int y)
{
	gotoxy(x += 3, --y);
	setcolor(0, 0);
	printf(" ");
}