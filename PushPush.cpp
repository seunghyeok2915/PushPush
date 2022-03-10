#include <iostream>
#include <time.h>
#include <Windows.h>
#include <conio.h>

using namespace std;

#define UP		72
#define DOWN	80
#define LEFT	75
#define RIGHT	77

int currentX, currentY;
int totalMove;
bool bPull;

char backgroundMap[10][16];

char Stage[10][16] =
{
	"+++++++++++++++",
	"+++++++++++++++",
	"++++&  ++++++++",
	"++++ OO++++++++",
	"++++ O ++++.+++",
	"++++++ ++++.+++",
	"++++++   @ .+++",
	"+++++    +  +++",
	"+++++@   ++++++",
	"+++++++++++++++"
};

void gotoXY(int x, int y)
{
	HANDLE hOut;
	COORD Cur;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(hOut, Cur);
}

void clrscr()
{
	system("cls");
}

void InitScreen()
{
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 15; x++)
		{
			gotoXY(x, y);
			_putch(backgroundMap[y][x]);
		}
	}
	gotoXY(currentX, currentY);
	_putch('&');
}

bool checkEnd()
{
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 15; x++)
		{
			if (Stage[y][x] == '.' && backgroundMap[y][x] != 'O')
			{
				return false;
			}
		}
	}
	return true;
}

void move(int dir)
{
	int dir_x = 0, dir_y = 0;

	switch (dir)
	{
	case LEFT:
		dir_x = -1;
		break;
	case RIGHT:
		dir_x = 1;
		break;
	case UP:
		dir_y = -1;
		break;
	case DOWN:
		dir_y = 1;
		break;
	}

	if (backgroundMap[currentY + dir_y][currentX + dir_x] != '+')
	{
		if (backgroundMap[currentY + dir_y][currentX + dir_x] == 'O')
		{
			if (backgroundMap[currentY + dir_y * 2][currentX + dir_x * 2] == ' ' || backgroundMap[currentY + dir_y * 2][currentX + dir_x * 2] == '.')
			{
				if (Stage[currentY + dir_y][currentX + dir_x] == '.')
				{
					backgroundMap[currentY + dir_y][currentX + dir_x] = '.';
				}
				else if (Stage[currentY + dir_y][currentX + dir_x] == '@')
				{
					backgroundMap[currentY + dir_y][currentX + dir_x] = '@';
				}
				else
				{
					backgroundMap[currentY + dir_y][currentX + dir_x] = ' ';
				}
				backgroundMap[currentY + dir_y * 2][currentX + dir_x * 2] = 'O';
			}
			else if (backgroundMap[currentY + dir_y * 2][currentX + dir_x * 2] == '@')
			{
				for (int y = 0; y < 10; y++)
				{
					for (int x = 0; x < 15; x++)
					{
						if (backgroundMap[y][x] == '@')
						{
							backgroundMap[y][x] = 'O';
							backgroundMap[currentY + dir_y * 2][currentX + dir_x * 2] = '@';
							backgroundMap[currentY + dir_y][currentX + dir_x] = ' ';
						}
					}
				}

			}
			else
				return;
		}

		if (bPull)
		{
			if (backgroundMap[currentY - 1][currentX] == '8')
			{
				if (Stage[currentY + dir_y - 1][currentX] == '.')
				{
					backgroundMap[currentY - 1][currentX] = '.';
				}
				else
				{
					backgroundMap[currentY - 1][currentX] = ' ';
				}
				if (backgroundMap[currentY + dir_y - 1][currentX + dir_x] != '+' && backgroundMap[currentY + dir_y - 1][currentX + dir_x] != 'O')
				{
					backgroundMap[currentY + dir_y - 1][currentX + dir_x] = '8';
				}
				else
				{
					backgroundMap[currentY -1][currentX] = '8';
					return;
				}
			}

			if (backgroundMap[currentY + 1][currentX] == '8')
			{
				if (Stage[currentY + dir_y + 1][currentX] == '.')
				{
					backgroundMap[currentY + 1][currentX] = '.';
				}
				else
				{
					backgroundMap[currentY + 1][currentX] = ' ';
				}
				if (backgroundMap[currentY + dir_y + 1][currentX + dir_x] != '+' && backgroundMap[currentY + dir_y + 1][currentX + dir_x] != 'O')
				{
					backgroundMap[currentY + dir_y + 1][currentX + dir_x] = '8';
				}
				else
				{
					backgroundMap[currentY + 1][currentX] = '8';
					return;
				}
			}

			if (backgroundMap[currentY][currentX - 1] == '8')
			{
				if (Stage[currentY + dir_y][currentX - 1] == '.')
				{
					backgroundMap[currentY][currentX - 1] = '.';
				}
				else
				{
					backgroundMap[currentY][currentX - 1] = ' ';
				}
				if (backgroundMap[currentY + dir_y ][currentX + dir_x - 1] != '+' && backgroundMap[currentY + dir_y][currentX + dir_x - 1] != 'O')
				{
					backgroundMap[currentY + dir_y][currentX + dir_x - 1] = '8';
				}
				else
				{
					backgroundMap[currentY][currentX - 1] = '8';
					return;
				}
			}

			if (backgroundMap[currentY][currentX + 1] == '8')
			{
				if (Stage[currentY + dir_y][currentX + 1] == '.')
				{
					backgroundMap[currentY][currentX + 1] = '.';
				}
				else
				{
					backgroundMap[currentY][currentX + 1] = ' ';
				}
				if (backgroundMap[currentY + dir_y][currentX + dir_x + 1] != '+' && backgroundMap[currentY + dir_y ][currentX + dir_x + 1] != 'O')
				{
					backgroundMap[currentY + dir_y][currentX + dir_x + 1] = '8';
				}
				else
				{
					backgroundMap[currentY][currentX + 1] = '8';
					return;
				}
			}
		}

		currentX += dir_x;
		currentY += dir_y;
		gotoXY(currentX, currentY);
		_putch('&');
	}
}

int main()
{
	int n = 0;
	memcpy(backgroundMap, Stage, sizeof(backgroundMap));

	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 15; x++)
		{
			if (backgroundMap[y][x] == '&')
			{
				currentX = x;
				currentY = y;
				backgroundMap[y][x] = ' ';
			}
		}
	}
	bPull = false;
	while (true)
	{
	InitScreen();
		n = _getch();

		if (n == 0xE0 || n == 0)
		{
			n = _getch();
			move(n);
		}
		else
		{
			n = tolower(n);
			if (n == 'q')
			{
				clrscr();
				exit(0);
			}
			else if (n == 'p')
			{
				if (bPull)
				{
					if (backgroundMap[currentY - 1][currentX] == '8')
					{
						backgroundMap[currentY - 1][currentX] = 'O';
					}
					if (backgroundMap[currentY + 1][currentX] == '8')
					{
						backgroundMap[currentY + 1][currentX] = 'O';
					}
					if (backgroundMap[currentY][currentX - 1] == '8')
					{
						backgroundMap[currentY][currentX - 1] = 'O';
					}
					if (backgroundMap[currentY][currentX +  1] == '8')
					{
						backgroundMap[currentY][currentX + 1 ] = 'O';
					}
					bPull = false;
				}
				else
				{
					if (backgroundMap[currentY + 1][currentX] == 'O')
					{
						backgroundMap[currentY + 1][currentX] = '8';
						bPull = true;
					}
					
					if (backgroundMap[currentY - 1][currentX] == 'O')
					{
						backgroundMap[currentY - 1][currentX] = '8';
						if (bPull)
						{
							if (backgroundMap[currentY - 1][currentX] == '8')
							{
								backgroundMap[currentY - 1][currentX] = 'O';
							}
							if (backgroundMap[currentY + 1][currentX] == '8')
							{
								backgroundMap[currentY + 1][currentX] = 'O';
							}
							if (backgroundMap[currentY][currentX - 1] == '8')
							{
								backgroundMap[currentY][currentX - 1] = 'O';
							}
							if (backgroundMap[currentY][currentX + 1] == '8')
							{
								backgroundMap[currentY][currentX + 1] = 'O';
							}
							bPull = false;
						}
						bPull = true;
					}

					if (backgroundMap[currentY][currentX + 1] == 'O')
					{
						backgroundMap[currentY][currentX + 1] = '8';
						if (bPull)
						{
							if (backgroundMap[currentY - 1][currentX] == '8')
							{
								backgroundMap[currentY - 1][currentX] = 'O';
							}
							if (backgroundMap[currentY + 1][currentX] == '8')
							{
								backgroundMap[currentY + 1][currentX] = 'O';
							}
							if (backgroundMap[currentY][currentX - 1] == '8')
							{
								backgroundMap[currentY][currentX - 1] = 'O';
							}
							if (backgroundMap[currentY][currentX + 1] == '8')
							{
								backgroundMap[currentY][currentX + 1] = 'O';
							}
							bPull = false;
						}
						bPull = true;
					}

					if (backgroundMap[currentY][currentX - 1] == 'O')
					{
						backgroundMap[currentY][currentX - 1] = '8';
						if (bPull)
						{
							if (backgroundMap[currentY - 1][currentX] == '8')
							{
								backgroundMap[currentY - 1][currentX] = 'O';
							}
							if (backgroundMap[currentY + 1][currentX] == '8')
							{
								backgroundMap[currentY + 1][currentX] = 'O';
							}
							if (backgroundMap[currentY][currentX - 1] == '8')
							{
								backgroundMap[currentY][currentX - 1] = 'O';
							}
							if (backgroundMap[currentY][currentX + 1] == '8')
							{
								backgroundMap[currentY][currentX + 1] = 'O';
							}
							bPull = false;
						}
						bPull = true;
					}

				}
			}
		}
		gotoXY(20, 20);

		if (checkEnd())
		{
			clrscr();
			gotoXY(10, 4);
			cout << "잘 풀어습니다. 아무키나 누르세요";
			_getch();
			clrscr();
			exit(0);
		}
	}
	return 0;
}
