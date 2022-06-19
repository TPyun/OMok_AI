#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include<stdbool.h>

#define SIZE 19

int coordinates[SIZE][SIZE] = { 0 };
int vetical[2][SIZE] = { 0 };
int vetical_continue[2][SIZE] = { 0 };
int horizenal[SIZE] = { 0 };
int wquantity = 0, bquantity = 0;
int wcontinue = 1, bcontinue = 1;
int whiteSign = 1, blackSign = 2;
int turn = 1;
int blackNum, whiteNum;
int i = 1;
FILE* file;
int whiteContinue[10][10] = { 0 };
int blackContinue[10][10] = { 0 };

int whitedangerCoordinatesD1[19][19] = { 0 };
int blackdangerCoordinatesD1[19][19] = { 0 };

int whitedangerCoordinatesD3[19][19] = { 0 };
int blackdangerCoordinatesD3[19][19] = { 0 };

int whitedangerCoordinatesH[19][19] = { 0 };
int blackdangerCoordinatesH[19][19] = { 0 };

int whitedangerCoordinatesV[19][19] = { 0 };
int blackdangerCoordinatesV[19][19] = { 0 };

int whitedangerCoordinates[19][19] = { 0 };
int blackdangerCoordinates[19][19] = { 0 };




bool danger = false;

typedef struct STACK
{
	int x;
	int y;
	int color;
	struct STACK* next;

}s;

s* topU;
s* topR;
s* topB;

void pushU(s* data)
{
	s* new = data;
	new->next = topU;
	topU = new;
}
void pushR(s* data)
{
	s* new = data;
	new->next = topR;
	topR = new;
}
void pushB(s* data)
{
	s* new = data;
	new->next = topB;
	topB = new;
}

s* popU()
{
	if (topU == NULL)
	{
		return NULL;
	}
	s* out = topU;
	topU = topU->next;
	out->next = NULL;
	return out;
}
s* popR()
{
	if (topR == NULL)
	{
		return NULL;
	}
	s* out = topR;
	topR = topR->next;
	out->next = NULL;
	return out;
}
s* popB()
{
	if (topB == NULL)
	{
		return NULL;
	}
	s* out = topB;
	topB = topB->next;
	out->next = NULL;
	return out;
}

void Diagonal(int num)
{
	//printf("Diagonal%d", num);

	if (num == 1)
	{
		for (int height = 0; height < SIZE; height++)
		{
			int downw = 20;
			int downb = 20;
			int h = 1;
			Diagonal1_white(height);
			Diagonal1_black(height);

			for (int i = 0; i < 10; i++)
			{
				if (whiteContinue[0][i] != 20)
				{
					downw = whiteContinue[0][i];
				}
				if (blackContinue[0][i] != 20)
				{
					downb = blackContinue[0][i];
				}
				if (whiteContinue[0][i] != 20 || blackContinue[0][i] != 20)
				{
					Diagonal1_continue(h, height, downw, downb);
					h++;
				}
			}
		}
		//printf("\n");
	}
	if (num == 2)
	{
		for (int height = 1; height < SIZE; height++)
		{
			int downw = 20;
			int downb = 20;
			int h = 1;
			Diagonal2_white(height);
			Diagonal2_black(height);

			for (int i = 0; i < 10; i++)
			{
				if (whiteContinue[0][i] != 20)
				{
					downw = whiteContinue[0][i];
				}
				if (blackContinue[0][i] != 20)
				{
					downb = blackContinue[0][i];
				}
				if (whiteContinue[0][i] != 20 || blackContinue[0][i] != 20)
				{
					Diagonal2_continue(h, height, downw, downb);
					h++;
				}
			}
		}
		//printf("\n");
	}

	if (num == 3)
	{
		for (int height = 0; height < SIZE; height++)
		{
			int downw = 20;
			int downb = 20;
			int h = 1;
			Diagonal3_white(height);
			Diagonal3_black(height);

			for (int i = 0; i < 10; i++)
			{
				if (whiteContinue[0][i] != 20)
				{
					downw = whiteContinue[0][i];
				}
				if (blackContinue[0][i] != 20)
				{
					downb = blackContinue[0][i];
				}
				if (whiteContinue[0][i] != 20 || blackContinue[0][i] != 20)
				{
					Diagonal3_continue(h, height, downw, downb);
					h++;
				}
			}
		}
		//printf("\n");
	}

	if (num == 4)
	{
		for (int height = 1; height < SIZE; height++)
		{
			int downw = 20;
			int downb = 20;
			int h = 1;
			Diagonal4_white(height);
			Diagonal4_black(height);

			for (int i = 0; i < 10; i++)
			{
				if (whiteContinue[0][i] != 20)
				{
					downw = whiteContinue[0][i];
				}
				if (blackContinue[0][i] != 20)
				{
					downb = blackContinue[0][i];
				}
				if (whiteContinue[0][i] != 20 || blackContinue[0][i] != 20)
				{
					Diagonal4_continue(h, height, downw, downb);
					h++;
				}
			}
		}
		//printf("\n");
	}
}

int Diagonal1_white(int height)
{
	int h = 1;
	int max = 1;
	int before = 20;
	int next = 0;
	for (int down = 0, right = height; down < SIZE - height; down++, right++)
	{
		int blank = 0;
		wcontinue = 0;

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				whiteContinue[i][j] = 20;
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if (down + i > 18 || right + i > 18 || down + i < 0 || right + i < 0)
			{
				break;
			}
			else if (coordinates[down + i][right + i] == blackSign || blank > 1)
			{
				break;
			}
			else if (coordinates[down + i][right + i] == whiteSign)
			{
				whiteContinue[h][i] = 1;
				wcontinue++;
			}
			else if (coordinates[down + i][right + i] == 0)
			{
				blank++;
			}
		}
		if (wcontinue > max)
		{
			max = wcontinue;
		}
	}
	for (int down = 0, right = height; down < SIZE - height; down++, right++)
	{
		int blank = 0;

		if (wcontinue != max)
		{
			for (int i = 0; i < 10; i++)
			{
				whiteContinue[h][i] = 20;
			}
		}
		wcontinue = 0;
		for (int i = 0; i < 10; i++)
		{
			if (down + i > 18 || right + i > 18 || down + i < 0 || right + i < 0)
			{
				break;
			}
			else if (coordinates[down + i][right + i] == blackSign || blank > 1)
			{
				break;
			}
			else if (coordinates[down + i][right + i] == whiteSign)
			{
				whiteContinue[h][i] = 1;
				wcontinue++;
			}
			else if (coordinates[down + i][right + i] == 0)
			{
				blank++;
			}
			if (wcontinue == max)
			{
				if (before == down + i || before + 1 == down + i)
				{
					continue;
				}
			}
		}
		if (wcontinue == max && wcontinue > 1)
		{
			if (before == down + i || before + 1 == down + i)
			{
				continue;
			}
			else
			{
				whiteContinue[0][next] = down;
				next++;
				h++;
				before = down + i;
			}
		}
	}
	wcontinue = max;
}

int Diagonal1_black(int height)
{
	int h = 1;
	int max = 1;
	int before = 20;
	int next = 0;
	for (int down = 0, right = height; down < SIZE - height; down++, right++)
	{
		int blank = 0;
		bcontinue = 0;

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				blackContinue[i][j] = 20;
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if (down + i > 18 || right + i > 18 || down + i < 0 || right + i < 0)
			{
				break;
			}
			else if (coordinates[down + i][right + i] == whiteSign || blank > 1)
			{
				break;
			}
			else if (coordinates[down + i][right + i] == blackSign)
			{
				blackContinue[h][i] = 1;
				bcontinue++;
			}
			else if (coordinates[down + i][right + i] == 0)
			{
				blank++;
			}
		}
		if (bcontinue > max)
		{
			max = bcontinue;
		}
	}
	for (int down = 0, right = height; down < SIZE - height; down++, right++)
	{
		int blank = 0;

		if (bcontinue != max)
		{
			for (int i = 0; i < 10; i++)
			{
				blackContinue[h][i] = 20;
			}
		}
		bcontinue = 0;
		for (int i = 0; i < 10; i++)
		{
			if (down + i > 18 || right + i > 18 || down + i < 0 || right + i < 0)
			{
				break;
			}
			else if (coordinates[down + i][right + i] == whiteSign || blank > 1)
			{
				break;
			}
			else if (coordinates[down + i][right + i] == blackSign)
			{
				blackContinue[h][i] = 1;
				bcontinue++;
			}
			else if (coordinates[down + i][right + i] == 0)
			{
				blank++;
			}
			if (bcontinue == max)
			{
				if (before == down + i || before + 1 == down + i)
				{
					continue;
				}
			}
		}
		if (bcontinue == max && bcontinue > 1)
		{
			if (before == down + i || before + 1 == down + i)
			{
				continue;
			}
			else
			{
				blackContinue[0][next] = down;
				next++;
				h++;
				before = down + i;
			}
		}
	}
	bcontinue = max;
}

int Diagonal1_continue(int h, int right, int downw, int downb)
{
	if (wcontinue > bcontinue)
	{
		//printf("[");
		if (wcontinue >= 3)
		{
			//printf("DANGER!!");
		}
		//printf("/White:%2d/", wcontinue);
		for (int i = 0; i < 5; i++) {
			if (whiteContinue[h][i] != 20)
			{
				//printf("(%d, %d)", downw + i, downw + right + i);


				if (downw + i + 1 >= 0 && downw + i + 1 <= 18 && downw + right + i + 1 >= 0 && downw + right + i + 1 <= 18)
				{
					whitedangerCoordinatesD1[downw + i + 1][downw + right + i + 1] += wcontinue;
				}
				if (downw + i - 1 >= 0 && downw + i - 1 <= 18 && downw + right + i - 1 >= 0 && downw + right + i - 1 <= 18)
				{
					whitedangerCoordinatesD1[downw + i - 1][downw + right + i - 1] += wcontinue;
				}
			}
		}
		//printf("] ");
	}
	else if (wcontinue < bcontinue)
	{
		//printf("[");
		if (bcontinue >= 3)
		{
			//printf("DANGER!!");
		}
		//printf("/Black:%2d/", bcontinue);
		for (int i = 0; i < 5; i++) {
			if (blackContinue[h][i] != 20) {
				//printf("(%d, %d)", downb + i, downb + right + i);

				if (downb + i + 1 >= 0 && downb + i + 1 <= 18 && downb + right + i + 1 >= 0 && downb + right + i + 1 <= 18)
				{
					blackdangerCoordinatesD1[downb + i + 1][downb + right + i + 1] += bcontinue;
				}
				if (downb + i - 1 >= 0 && downb + i - 1 <= 18 && downb + right + i - 1 >= 0 && downb + right + i - 1 <= 18)
				{
					blackdangerCoordinatesD1[downb + i - 1][downb + right + i - 1] += bcontinue;
				}

			}
		}
		 //printf("] ");
	}
	else if (wcontinue > 1 && wcontinue == bcontinue)
	{
		//printf("[");
		if (wcontinue >= 3 || bcontinue >= 3)
		{
			//printf("DANGER!!");
		}
		//printf("White:%2d", wcontinue);
		for (int i = 0; i < 5; i++) {
			if (whiteContinue[h][i] != 20) {

				//printf("(%d, %d)", downw + i, downw + right + i);
				if (downw + i + 1 >= 0 && downw + i + 1 <= 18 && downw + right + i + 1 >= 0 && downw + right + i + 1 <= 18)
				{
					whitedangerCoordinatesD1[downw + i + 1][downw + right + i + 1] += wcontinue;
				}
				if (downw + i - 1 >= 0 && downw + i - 1 <= 18 && downw + right + i - 1 >= 0 && downw + right + i - 1 <= 18)
				{
					whitedangerCoordinatesD1[downw + i - 1][downw + right + i - 1] += wcontinue;
				}

			}
		}
		//printf("Black:%2d", bcontinue);
		for (int i = 0; i < 5; i++)
		{
			if (blackContinue[h][i] != 20) {

				//printf("(%d, %d)", downb + i, downb + right + i);
				if (downb + i + 1 >= 0 && downb + i + 1 <= 18 && downb + right + i + 1 >= 0 && downb + right + i + 1 <= 18)
				{
					blackdangerCoordinatesD1[downb + i + 1][downb + right + i + 1] += bcontinue;
				}
				if (downb + i - 1 >= 0 && downb + i - 1 <= 18 && downb + right + i - 1 >= 0 && downb + right + i - 1 <= 18)
				{
					blackdangerCoordinatesD1[downb + i - 1][downb + right + i - 1] += bcontinue;
				}
			}
		}
		//printf("] ");
	}
}

int Diagonal2_white(int height)
{
	int h = 1;
	int max = 1;
	int before = 20;
	int next = 0;
	for (int down = height, right = 0; down < SIZE; down++, right++)
	{
		int blank = 0;
		wcontinue = 0;

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				whiteContinue[i][j] = 20;
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if (down + i > 18 || right + i > 18 || down + i < 0 || right + i < 0)
			{
				break;
			}
			else if (coordinates[down + i][right + i] == blackSign || blank > 1)
			{
				break;
			}
			else if (coordinates[down + i][right + i] == whiteSign)
			{
				whiteContinue[h][i] = 1;
				wcontinue++;
			}
			else if (coordinates[down + i][right + i] == 0)
			{
				blank++;
			}
		}
		if (wcontinue > max)
		{
			max = wcontinue;
		}
	}
	for (int down = height, right = 0; down < SIZE; down++, right++)
	{
		int blank = 0;

		if (wcontinue != max)
		{
			for (int i = 0; i < 10; i++)
			{
				whiteContinue[h][i] = 20;
			}
		}
		wcontinue = 0;
		for (int i = 0; i < 10; i++)
		{
			if (down + i > 18 || right + i > 18 || down + i < 0 || right + i < 0)
			{
				break;
			}
			else if (coordinates[down + i][right + i] == blackSign || blank > 1)
			{
				break;
			}
			else if (coordinates[down + i][right + i] == whiteSign)
			{
				whiteContinue[h][i] = 1;
				wcontinue++;
			}
			else if (coordinates[down + i][right + i] == 0)
			{
				blank++;
			}
			if (wcontinue == max)
			{
				if (before == down + i || before + 1 == down + i)
				{
					continue;
				}
			}
		}
		if (wcontinue == max && wcontinue > 1)
		{
			if (before == down + i || before + 1 == down + i)
			{
				continue;
			}
			else
			{
				whiteContinue[0][next] = down;
				next++;
				h++;
				before = down + i;
			}
		}
	}
	wcontinue = max;
}

int Diagonal2_black(int height)
{
	int h = 1;
	int max = 1;
	int before = 20;
	int next = 0;
	for (int down = height, right = 0; down < SIZE; down++, right++)
	{
		int blank = 0;
		bcontinue = 0;

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				blackContinue[i][j] = 20;
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if (down + i > 18 || right + i > 18 || down + i < 0 || right + i < 0)
			{
				break;
			}
			else if (coordinates[down + i][right + i] == whiteSign || blank > 1)
			{
				break;
			}
			else if (coordinates[down + i][right + i] == blackSign)
			{
				blackContinue[h][i] = 1;
				bcontinue++;
			}
			else if (coordinates[down + i][right + i] == 0)
			{
				blank++;
			}
		}
		if (bcontinue > max)
		{
			max = bcontinue;
		}
	}
	for (int down = height, right = 0; down < SIZE; down++, right++)
	{
		int blank = 0;

		if (bcontinue != max)
		{
			for (int i = 0; i < 10; i++)
			{
				blackContinue[h][i] = 20;
			}
		}
		bcontinue = 0;
		for (int i = 0; i < 10; i++)
		{
			if (down + i > 18 || right + i > 18 || down + i < 0 || right + i < 0)
			{
				break;
			}
			else if (coordinates[down + i][right + i] == whiteSign || blank > 1)
			{
				break;
			}
			else if (coordinates[down + i][right + i] == blackSign)
			{
				blackContinue[h][i] = 1;
				bcontinue++;
			}
			else if (coordinates[down + i][right + i] == 0)
			{
				blank++;
			}
			if (bcontinue == max)
			{
				if (before == down + i || before + 1 == down + i)
				{
					continue;
				}
			}
		}
		if (bcontinue == max && bcontinue > 1)
		{
			if (before == down + i || before + 1 == down + i)
			{
				continue;
			}
			else
			{
				blackContinue[0][next] = down;
				next++;
				h++;
				before = down + i;
			}
		}
	}
	bcontinue = max;
}

int Diagonal2_continue(int h, int right, int downw, int downb)
{
	if (wcontinue > bcontinue)
	{
		//printf("[");
		if (wcontinue >= 3)
		{
			//printf("DANGER!!");
		}
		//printf("/White:%2d/", wcontinue);
		for (int i = 0; i < 5; i++) {
			if (whiteContinue[h][i] != 20)
			{
				//printf("(%d, %d)", downw + i, downw - right + i);

				if (downw + i + 1 >= 0 && downw + i + 1 <= 18 && downw - right + i + 1 >= 0 && downw - right + i + 1 <= 18)
				{
					whitedangerCoordinatesD1[downw + i + 1][downw - right + i + 1] += wcontinue;
				}
				if (downw + i - 1 >= 0 && downw + i - 1 <= 18 && downw - right + i - 1 >= 0 && downw - right + i - 1 <= 18)
				{
					whitedangerCoordinatesD1[downw + i - 1][downw - right + i - 1] += wcontinue;
				}

			}
		}
		//("] ");
	}
	else if (wcontinue < bcontinue)
	{
		//printf("[");
		if (bcontinue >= 3)
		{
			//printf("DANGER!!");
		}
		//printf("/Black:%2d/", bcontinue);
		for (int i = 0; i < 5; i++) {
			if (blackContinue[h][i] != 20) {
				//printf("(%d, %d)", downb + i, downb - right + i);

				if (downb + i + 1 >= 0 && downb + i + 1 <= 18 && downb - right + i + 1 >= 0 && downb - right + i + 1 <= 18)
				{
					blackdangerCoordinatesD1[downb + i + 1][downb - right + i + 1] += bcontinue;;
				}
				if (downb + i - 1 >= 0 && downb + i - 1 <= 18 && downb - right + i - 1 >= 0 && downb - right + i - 1 <= 18)
				{
					blackdangerCoordinatesD1[downb + i - 1][downb - right + i - 1] += bcontinue;
				}
			}
		}
		//printf("] ");
	}
	else if (wcontinue > 1 && wcontinue == bcontinue)
	{
		//printf("[");
		if (wcontinue >= 3 || bcontinue >= 3)
		{
			//printf("DANGER!!");
		}
		//printf("White:%2d", wcontinue);
		for (int i = 0; i < 5; i++) {
			if (whiteContinue[h][i] != 20) {

				//printf("(%d, %d)", downw + i, downw - right + i);
				if (downw + i + 1 >= 0 && downw + i + 1 <= 18 && downw - right + i + 1 >= 0 && downw - right + i + 1 <= 18)
				{
					whitedangerCoordinatesD1[downw + i + 1][downw - right + i + 1] += wcontinue / 2;
				}
				if (downw + i - 1 >= 0 && downw + i - 1 <= 18 && downw - right + i - 1 >= 0 && downw - right + i - 1 <= 18)
				{
					whitedangerCoordinatesD1[downw + i - 1][downw - right + i - 1] += wcontinue / 2;
				}
			}
		}
		//printf("Black:%2d", bcontinue);
		for (int i = 0; i < 5; i++)
		{
			if (blackContinue[h][i] != 20) {

				//printf("(%d, %d)", downb + i, downb - right + i);

				if (downb + i + 1 >= 0 && downb + i + 1 <= 18 && downb - right + i + 1 >= 0 && downb - right + i + 1 <= 18)
				{
					blackdangerCoordinatesD1[downb + i + 1][downb - right + i + 1] += bcontinue / 2;
				}
				if (downb + i - 1 >= 0 && downb + i - 1 <= 18 && downb - right + i - 1 >= 0 && downb - right + i - 1 <= 18)
				{
					blackdangerCoordinatesD1[downb + i - 1][downb - right + i - 1] += bcontinue / 2;
				}
			}
		}
		//printf("] ");
	}
}

int Diagonal3_white(int height)
{
	int h = 1;
	int max = 1;
	int before = 20;
	int next = 0;
	for (int down = 0, right = SIZE - height - 1; down < SIZE - height; down++, right--)
	{
		int blank = 0;
		wcontinue = 0;

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				whiteContinue[i][j] = 20;
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if (down + i > 18 || right - i > 18 || down + i < 0 || right - i < 0)
			{
				break;
			}
			else if (coordinates[down + i][right - i] == blackSign || blank > 1)
			{
				break;
			}
			else if (coordinates[down + i][right - i] == whiteSign)
			{
				whiteContinue[h][i] = 1;
				wcontinue++;
			}
			else if (coordinates[down + i][right - i] == 0)
			{
				blank++;
			}
		}
		if (wcontinue > max)
		{
			max = wcontinue;
		}
	}
	for (int down = 0, right = SIZE - height - 1; down < SIZE - height; down++, right--)
	{
		int blank = 0;

		if (wcontinue != max)
		{
			for (int i = 0; i < 10; i++)
			{
				whiteContinue[h][i] = 20;
			}
		}
		wcontinue = 0;
		for (int i = 0; i < 10; i++)
		{
			if (down + i > 18 || right - i > 18 || down + i < 0 || right - i < 0)
			{
				break;
			}
			else if (coordinates[down + i][right - i] == blackSign || blank > 1)
			{
				break;
			}
			else if (coordinates[down + i][right - i] == whiteSign)
			{
				whiteContinue[h][i] = 1;
				wcontinue++;
			}
			else if (coordinates[down + i][right - i] == 0)
			{
				blank++;
			}
			if (wcontinue == max)
			{
				if (before == down + i || before + 1 == down + i)
				{
					continue;
				}
			}
		}
		if (wcontinue == max && wcontinue > 1)
		{
			if (before == down + i || before + 1 == down + i)
			{
				continue;
			}
			else
			{
				whiteContinue[0][next] = down;
				next++;
				h++;
				before = down + i;
			}
		}
	}
	wcontinue = max;
}

int Diagonal3_black(int height)
{
	int h = 1;
	int max = 1;
	int before = 20;
	int next = 0;
	for (int down = 0, right = SIZE - height - 1; down < SIZE - height; down++, right--)
	{
		int blank = 0;
		bcontinue = 0;

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				blackContinue[i][j] = 20;
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if (down + i > 18 || right - i > 18 || down + i < 0 || right - i < 0)
			{
				break;
			}
			else if (coordinates[down + i][right - i] == whiteSign || blank > 1)
			{
				break;
			}
			else if (coordinates[down + i][right - i] == blackSign)
			{
				blackContinue[h][i] = 1;
				bcontinue++;
			}
			else if (coordinates[down + i][right - i] == 0)
			{
				blank++;
			}
		}
		if (bcontinue > max)
		{
			max = bcontinue;
		}
	}
	for (int down = 0, right = SIZE - height - 1; down < SIZE - height; down++, right--)
	{
		int blank = 0;

		if (bcontinue != max)
		{
			for (int i = 0; i < 10; i++)
			{
				blackContinue[h][i] = 20;
			}
		}
		bcontinue = 0;
		for (int i = 0; i < 10; i++)
		{
			if (down + i > 18 || right - i > 18 || down + i < 0 || right - i < 0)
			{
				break;
			}
			else if (coordinates[down + i][right - i] == whiteSign || blank > 1)
			{
				break;
			}
			else if (coordinates[down + i][right - i] == blackSign)
			{
				blackContinue[h][i] = 1;
				bcontinue++;
			}
			else if (coordinates[down + i][right - i] == 0)
			{
				blank++;
			}
			if (bcontinue == max)
			{
				if (before == down + i || before + 1 == down + i)
				{
					continue;
				}
			}
		}
		if (bcontinue == max && bcontinue > 1)
		{
			if (before == down + i || before + 1 == down + i)
			{
				continue;
			}
			else
			{
				blackContinue[0][next] = down;
				next++;
				h++;
				before = down + i;
			}
		}
	}
	bcontinue = max;
}

int Diagonal3_continue(int h, int right, int downw, int downb)
{
	if (wcontinue > bcontinue)
	{
		//printf("[");
		if (wcontinue >= 3)
		{
			//printf("DANGER!!");
		}
		//printf("/White:%2d/", wcontinue);
		for (int i = 0; i < 5; i++) {
			if (whiteContinue[h][i] != 20)
			{
				//printf("(%d, %d)", downw + i, SIZE - (downw + right + i + 1));
				if (downw + i + 1 >= 0 && downw + i + 1 <= 18 && SIZE - (downw + right + i + 1) - 1 >= 0 && SIZE - (downw + right + i + 1) - 1 <= 18)
				{
					whitedangerCoordinatesD3[downw + i + 1][SIZE - (downw + right + i + 1) - 1] += wcontinue;
				}
				if (downw + i - 1 >= 0 && downw + i - 1 <= 18 && SIZE - (downw + right + i + 1) + 1 >= 0 && SIZE - (downw + right + i + 1) + 1 <= 18)
				{
					whitedangerCoordinatesD3[downw + i - 1][SIZE - (downw + right + i + 1) + 1] += wcontinue;
				}
			}
		}
		//printf("] ");
	}
	else if (wcontinue < bcontinue)
	{
		//printf("[");
		if (bcontinue >= 3)
		{
			//printf("DANGER!!");
		}
		//printf("/Black:%2d/", bcontinue);
		for (int i = 0; i < 5; i++) {
			if (blackContinue[h][i] != 20) {
				//printf("(%d, %d)", downb + i, SIZE - (downb + right + i + 1));

				if (downb + i + 1 >= 0 && downb + i + 1 <= 18 && SIZE - (downb + right + i + 1) - 1 >= 0 && SIZE - (downb + right + i + 1) - 1 <= 18)
				{
					blackdangerCoordinatesD3[downb + i + 1][SIZE - (downb + right + i + 1) - 1] += bcontinue;
				}
				if (downb + i - 1 >= 0 && downb + i - 1 <= 18 && SIZE - (downb + right + i + 1) + 1 >= 0 && SIZE - (downb + right + i + 1) + 1 <= 18)
				{
					blackdangerCoordinatesD3[downb + i - 1][SIZE - (downb + right + i + 1) + 1] += bcontinue;
				}
			}
		}
		//printf("] ");
	}
	else if (wcontinue > 1 && wcontinue == bcontinue)
	{
		//printf("[");
		if (wcontinue >= 3 || bcontinue >= 3)
		{
			//printf("DANGER!!");
		}
		//printf("White:%2d", wcontinue);
		for (int i = 0; i < 5; i++) {
			if (whiteContinue[h][i] != 20) {

				//printf("(%d, %d)", downw + i, SIZE - (downw + right + i + 1));

				if (downw + i + 1 >= 0 && downw + i + 1 <= 18 && SIZE - (downw + right + i + 1) - 1 >= 0 && SIZE - (downw + right + i + 1) - 1 <= 18)
				{
					whitedangerCoordinatesD3[downw + i + 1][SIZE - (downw + right + i + 1) - 1] += wcontinue;
				}
				if (downw + i - 1 >= 0 && downw + i - 1 <= 18 && SIZE - (downw + right + i + 1) + 1 >= 0 && SIZE - (downw + right + i + 1) + 1 <= 18)
				{
					whitedangerCoordinatesD3[downw + i - 1][SIZE - (downw + right + i + 1) + 1] += wcontinue;
				}
			}
		}
		//printf("Black:%2d", bcontinue);
		for (int i = 0; i < 5; i++)
		{
			if (blackContinue[h][i] != 20) {

				//printf("(%d, %d)", downb + i, SIZE - (downb + right + i + 1));
				if (downb + i + 1 >= 0 && downb + i + 1 <= 18 && SIZE - (downb + right + i + 1) - 1 >= 0 && SIZE - (downb + right + i + 1) - 1 <= 18)
				{
					blackdangerCoordinatesD3[downb + i + 1][SIZE - (downb + right + i + 1) - 1] += bcontinue;
				}
				if (downb + i - 1 >= 0 && downb + i - 1 <= 18 && SIZE - (downb + right + i + 1) + 1 >= 0 && SIZE - (downb + right + i + 1) + 1 <= 18)
				{
					blackdangerCoordinatesD3[downb + i - 1][SIZE - (downb + right + i + 1) + 1] += bcontinue;
				}
			}
		}
		//printf("] ");
	}
}

int Diagonal4_white(int height)
{
	int h = 1;
	int max = 1;
	int before = 20;
	int next = 0;
	for (int down = height, right = SIZE - 1; down < SIZE; down++, right--)
	{
		int blank = 0;
		wcontinue = 0;

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				whiteContinue[i][j] = 20;
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if (down + i > 18 || right - i > 18 || down + i < 0 || right - i < 0)
			{
				break;
			}
			else if (coordinates[down + i][right - i] == blackSign || blank > 1)
			{
				break;
			}
			else if (coordinates[down + i][right - i] == whiteSign)
			{
				whiteContinue[h][i] = 1;
				wcontinue++;
			}
			else if (coordinates[down + i][right - i] == 0)
			{
				blank++;
			}
		}
		if (wcontinue > max)
		{
			max = wcontinue;
		}
	}
	for (int down = height, right = SIZE - 1; down < SIZE; down++, right--)
	{
		int blank = 0;

		if (wcontinue != max)
		{
			for (int i = 0; i < 10; i++)
			{
				whiteContinue[h][i] = 20;
			}
		}
		wcontinue = 0;
		for (int i = 0; i < 10; i++)
		{
			if (down + i > 18 || right - i > 18 || down + i < 0 || right - i < 0)
			{
				break;
			}
			else if (coordinates[down + i][right - i] == blackSign || blank > 1)
			{
				break;
			}
			else if (coordinates[down + i][right - i] == whiteSign)
			{
				whiteContinue[h][i] = 1;
				wcontinue++;
			}
			else if (coordinates[down + i][right - i] == 0)
			{
				blank++;
			}
			if (wcontinue == max)
			{
				if (before == down + i || before + 1 == down + i)
				{
					continue;
				}
			}
		}
		if (wcontinue == max && wcontinue > 1)
		{
			if (before == down + i || before + 1 == down + i)
			{
				continue;
			}
			else
			{
				whiteContinue[0][next] = down;
				next++;
				h++;
				before = down + i;
			}
		}
	}
	wcontinue = max;
}

int Diagonal4_black(int height)
{
	int h = 1;
	int max = 1;
	int before = 20;
	int next = 0;
	for (int down = height, right = SIZE - 1; down < SIZE; down++, right--)
	{
		int blank = 0;
		bcontinue = 0;

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				blackContinue[i][j] = 20;
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if (down + i > 18 || right - i > 18 || down + i < 0 || right - i < 0)
			{
				break;
			}
			else if (coordinates[down + i][right - i] == whiteSign || blank > 1)
			{
				break;
			}
			else if (coordinates[down + i][right - i] == blackSign)
			{
				blackContinue[h][i] = 1;
				bcontinue++;
			}
			else if (coordinates[down + i][right - i] == 0)
			{
				blank++;
			}
		}
		if (bcontinue > max)
		{
			max = bcontinue;
		}
	}
	for (int down = height, right = SIZE - 1; down < SIZE; down++, right--)
	{
		int blank = 0;

		if (bcontinue != max)
		{
			for (int i = 0; i < 10; i++)
			{
				blackContinue[h][i] = 20;
			}
		}
		bcontinue = 0;
		for (int i = 0; i < 10; i++)
		{
			if (down + i > 18 || right - i > 18 || down + i < 0 || right - i < 0)
			{
				break;
			}
			else if (coordinates[down + i][right - i] == whiteSign || blank > 1)
			{
				break;
			}
			else if (coordinates[down + i][right - i] == blackSign)
			{
				blackContinue[h][i] = 1;
				bcontinue++;
			}
			else if (coordinates[down + i][right - i] == 0)
			{
				blank++;
			}
			if (bcontinue == max)
			{
				if (before == down + i || before + 1 == down + i)
				{
					continue;
				}
			}
		}
		if (bcontinue == max && bcontinue > 1)
		{
			if (before == down + i || before + 1 == down + i)
			{
				continue;
			}
			else
			{
				blackContinue[0][next] = down;
				next++;
				h++;
				before = down + i;
			}
		}
	}
	bcontinue = max;
}

int Diagonal4_continue(int h, int right, int downw, int downb)
{
	if (wcontinue > bcontinue)
	{
		//printf("[");
		if (wcontinue >= 3)
		{
			//printf("DANGER!!");
		}
		//printf("/White:%2d/", wcontinue);
		for (int i = 0; i < 5; i++) {
			if (whiteContinue[h][i] != 20)
			{
				//printf("(%d, %d)", downw + i, SIZE - (downw - right + i + 1));

				if (downw + i + 1 >= 0 && downw + i + 1 <= 18 && SIZE - (downw - right + i + 1) - 1 >= 0 && SIZE - (downw + right + i + 1) - 1 <= 18)
				{
					whitedangerCoordinatesD3[downw + i + 1][SIZE - (downw - right + i + 1) - 1] += wcontinue;
				}
				if (downw + i - 1 >= 0 && downw + i - 1 <= 18 && SIZE - (downw - right + i + 1) + 1 >= 0 && SIZE - (downw + right + i + 1) + 1 <= 18)
				{
					whitedangerCoordinatesD3[downw + i - 1][SIZE - (downw - right + i + 1) + 1] += wcontinue;
				}
			}
		}
		//printf("] ");
	}
	else if (wcontinue < bcontinue)
	{
		//printf("[");
		if (bcontinue >= 3)
		{
			//printf("DANGER!!");
		}
		//printf("/Black:%2d/", bcontinue);
		for (int i = 0; i < 5; i++) {
			if (blackContinue[h][i] != 20) {
				//printf("(%d, %d)", downb + i, SIZE - (downb - right + i + 1));

				if (downb + i + 1 >= 0 && downb + i + 1 <= 18 && SIZE - (downb - right + i + 1) - 1 >= 0 && SIZE - (downb + right + i + 1) - 1 <= 18)
				{
					blackdangerCoordinatesD3[downb + i + 1][SIZE - (downb - right + i + 1) - 1] += bcontinue;
				}
				if (downb + i - 1 >= 0 && downb + i - 1 <= 18 && SIZE - (downb - right + i + 1) + 1 >= 0 && SIZE - (downb + right + i + 1) + 1 <= 18)
				{
					blackdangerCoordinatesD3[downb + i - 1][SIZE - (downb - right + i + 1) + 1] += bcontinue;
				}
			}
		}
		//printf("] ");
	}
	else if (wcontinue > 1 && wcontinue == bcontinue)
	{
		//printf("[");
		if (wcontinue >= 3 || bcontinue >= 3)
		{
			//printf("DANGER!!");
		}
		//printf("White:%2d", wcontinue);
		for (int i = 0; i < 5; i++) {
			if (whiteContinue[h][i] != 20) {

				//printf("(%d, %d)", downw + i, SIZE - (downw - right + i + 1));
				if (downw + i + 1 >= 0 && downw + i + 1 <= 18 && SIZE - (downw - right + i + 1) - 1 >= 0 && SIZE - (downw + right + i + 1) - 1 <= 18)
				{
					whitedangerCoordinatesD3[downw + i + 1][SIZE - (downw - right + i + 1) - 1] += wcontinue;
				}
				if (downw + i - 1 >= 0 && downw + i - 1 <= 18 && SIZE - (downw - right + i + 1) + 1 >= 0 && SIZE - (downw + right + i + 1) + 1 <= 18)
				{
					whitedangerCoordinatesD3[downw + i - 1][SIZE - (downw - right + i + 1) + 1] += wcontinue;
				}
			}
		}
		//printf("Black:%2d", bcontinue);
		for (int i = 0; i < 5; i++)
		{
			if (blackContinue[h][i] != 20) {

				//printf("(%d, %d)", downb + i, SIZE - (downb - right + i + 1));
				if (downb + i + 1 >= 0 && downb + i + 1 <= 18 && SIZE - (downb - right + i + 1) - 1 >= 0 && SIZE - (downb + right + i + 1) - 1 <= 18)
				{
					blackdangerCoordinatesD3[downb + i + 1][SIZE - (downb - right + i + 1) - 1] += bcontinue;
				}
				if (downb + i - 1 >= 0 && downb + i - 1 <= 18 && SIZE - (downb - right + i + 1) + 1 >= 0 && SIZE - (downb + right + i + 1) + 1 <= 18)
				{
					blackdangerCoordinatesD3[downb + i - 1][SIZE - (downb - right + i + 1) + 1] += bcontinue;
				}
			}
		}
		//printf("] ");
	}
}
void initializeDanger()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			whitedangerCoordinates[i][j] = 0;
			blackdangerCoordinates[i][j] = 0;

			whitedangerCoordinatesD1[i][j] = 0;
			blackdangerCoordinatesD1[i][j] = 0;

			whitedangerCoordinatesD3[i][j] = 0;
			blackdangerCoordinatesD3[i][j] = 0;

			whitedangerCoordinatesH[i][j] = 0;
			blackdangerCoordinatesH[i][j] = 0;

			whitedangerCoordinatesV[i][j] = 0;
			blackdangerCoordinatesV[i][j] = 0;
		}
	}
}
void Update()
{
	initializeDanger();

	Diagonal(1);
	Diagonal(2);
	Diagonal(3);
	Diagonal(4);
	printf("         0 1 2 3 4 5 6 7 8 9101112131415161718\n");

	printf("        --------------------------------------\n");
	for (int down = 0; down < SIZE; down++)
	{
		printf("     %02d|", down);
		wquantity = 0, bquantity = 0;
		for (int right = 0; right < SIZE; right++)
		{
			if (coordinates[down][right] == 0)
			{
				if (turn % 2 == 1)
				{
					if (blackdangerCoordinates[down][right] != 0)
					{
						printf(" %d", blackdangerCoordinates[down][right]);
					}
					else {
						printf(" +");
					}
				}
				else
				{
					if (whitedangerCoordinates[down][right] != 0)
					{
						printf(" %d", whitedangerCoordinates[down][right]);
					}
					else {
						printf(" +");
					}
				}
			}
			else if (coordinates[down][right] == whiteSign)
			{
				++whiteNum;
				++wquantity;
				printf(" 0");
				if (coordinates[down][right + 1] == whiteSign)
				{
					horizenal[right] = whiteSign;
					horizenal[right + 1] = whiteSign;
					++wcontinue;
				}
			}
			else if (coordinates[down][right] == blackSign)
			{
				++blackNum;
				++bquantity;
				printf(" X");
				if (coordinates[down][right + 1] == blackSign)
				{
					horizenal[right] = blackSign;
					horizenal[right + 1] = blackSign;
					++bcontinue;
				}
			}
			else
			{
				printf("♨");
			}
		}
		//printf("|White:%2d,Black:%2d|", wquantity, bquantity);
		int rightw = 20;
		int rightb = 20;
		int h = 1;
		Horizenal_white(down);
		Horizenal_black(down);

		for (int i = 0; i < 10; i++)
		{
			if (whiteContinue[0][i] != 20)
			{
				rightw = whiteContinue[0][i];
			}
			if (blackContinue[0][i] != 20)
			{
				rightb = blackContinue[0][i];
			}
			if (whiteContinue[0][i] != 20 || blackContinue[0][i] != 20)
			{
				Horizenal_continue(h, down, rightw, rightb);
				h++;
			}

		}

		printf("\n");
	}
	Vertical();

}

int Horizenal_white(int down)
{
	int h = 1;
	int max = 1;
	int before = 20;
	int next = 0;
	for (int right = 0; right < SIZE; right++)
	{

		int blank = 0;
		wcontinue = 0;

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				whiteContinue[i][j] = 20;
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if (down > 18 || right + i > 18 || down < 0 || right + i < 0)
			{
				break;
			}
			else if (coordinates[down][right + i] == blackSign || blank > 1)
			{
				break;
			}
			else if (coordinates[down][right + i] == whiteSign)
			{
				whiteContinue[h][i] = 1;
				wcontinue++;
			}
			else if (coordinates[down][right + i] == 0)
			{
				blank++;
			}
		}
		if (wcontinue > max)
		{
			max = wcontinue;
		}
	}
	for (int right = 0; right < SIZE; right++)
	{
		int blank = 0;

		if (wcontinue != max)
		{
			for (int i = 0; i < 10; i++)
			{
				whiteContinue[h][i] = 20;
			}
		}
		wcontinue = 0;
		for (int i = 0; i < 10; i++)
		{
			if (down > 18 || right + i > 18 || down < 0 || right + i < 0)
			{
				break;
			}
			else if (coordinates[down][right + i] == blackSign || blank > 1)
			{
				break;
			}
			else if (coordinates[down][right + i] == whiteSign)
			{
				whiteContinue[h][i] = 1;
				wcontinue++;
			}
			else if (coordinates[down][right + i] == 0)
			{
				blank++;
			}
			if (wcontinue == max)
			{
				if (before == right + i || before + 1 == right + i)
				{
					continue;
				}
			}
		}
		if (wcontinue == max && wcontinue > 1)
		{
			if (before == right + i || before + 1 == right + i)
			{
				continue;
			}
			else
			{
				whiteContinue[0][next] = right;
				next++;
				h++;
				before = right + i;
			}
		}
	}
	wcontinue = max;
}

int Horizenal_black(int down)
{
	int h = 1;
	int max = 1;
	int before = 20;
	int next = 0;
	for (int right = 0; right < SIZE; right++)
	{

		int blank = 0;
		bcontinue = 0;

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				blackContinue[i][j] = 20;
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if (down > 18 || right + i > 18 || down < 0 || right + i < 0)
			{
				break;
			}
			else if (coordinates[down][right + i] == whiteSign || blank > 1)
			{
				break;
			}
			else if (coordinates[down][right + i] == blackSign)
			{
				blackContinue[h][i] = 1;
				bcontinue++;
			}
			else if (coordinates[down][right + i] == 0)
			{
				blank++;
			}
		}
		if (bcontinue > max)
		{
			max = bcontinue;
		}
	}
	for (int right = 0; right < SIZE; right++)
	{
		int blank = 0;

		if (bcontinue != max)
		{
			for (int i = 0; i < 10; i++)
			{
				blackContinue[h][i] = 20;
			}
		}
		bcontinue = 0;
		for (int i = 0; i < 10; i++)
		{
			if (down > 18 || right + i > 18 || down < 0 || right + i < 0)
			{
				break;
			}
			else if (coordinates[down][right + i] == whiteSign || blank > 1)
			{
				break;
			}
			else if (coordinates[down][right + i] == blackSign)
			{
				blackContinue[h][i] = 1;
				bcontinue++;
			}
			else if (coordinates[down][right + i] == 0)
			{
				blank++;
			}
			if (bcontinue == max)
			{
				if (before == right + i || before + 1 == right + i)
				{
					continue;
				}
			}
		}
		if (bcontinue == max && bcontinue > 1)
		{
			if (before == right + i || before + 1 == right + i)
			{
				continue;
			}
			else
			{
				blackContinue[0][next] = right;
				next++;
				h++;
				before = right + i;
			}
		}
	}
	bcontinue = max;
}

int Horizenal_continue(int h, int down, int rightw, int rightb)
{
	if (wcontinue > bcontinue)
	{
		//printf("[");
		if (wcontinue >= 3)
		{
			//printf("DANGER!!");
		}
		//printf("/White:%2d/", wcontinue);
		for (int i = 0; i < 5; i++) {
			if (whiteContinue[h][i] != 20)
			{
				//printf("(%d, %d)", down, rightw + i);

				if (down >= 0 && down <= 18 && rightw + i + 1 >= 0 && rightw + i + 1 <= 18)
				{
					whitedangerCoordinatesH[down][rightw + i + 1] += wcontinue;
				}
				if (down >= 0 && down <= 18 && rightw + i - 1 >= 0 && rightw + i - 1 <= 18)
				{
					whitedangerCoordinatesH[down][rightw + i - 1] += wcontinue;
				}

			}
		}
		//printf("] ");
	}
	else if (wcontinue < bcontinue)
	{
		//printf("[");
		if (bcontinue >= 3)
		{
			//printf("DANGER!!");
		}
		//printf("/Black:%2d/", bcontinue);
		for (int i = 0; i < 5; i++) {
			if (blackContinue[h][i] != 20) {
				//printf("(%d, %d)", down, rightb + i);

				if (down >= 0 && down <= 18 && rightb + i + 1 >= 0 && rightb + i + 1 <= 18)
				{
					blackdangerCoordinatesH[down][rightb + i + 1] += bcontinue;
				}
				if (down >= 0 && down <= 18 && rightb + i - 1 >= 0 && rightb + i - 1 <= 18)
				{
					blackdangerCoordinatesH[down][rightb + i - 1] += bcontinue;
				}
			}
		}
		//printf("] ");
	}
	else if (wcontinue > 1 && wcontinue == bcontinue)
	{
		//printf("[");
		if (wcontinue >= 3 || bcontinue >= 3)
		{
			//printf("DANGER!!");
		}
		//printf("White:%2d", wcontinue);
		for (int i = 0; i < 5; i++) {
			if (whiteContinue[h][i] != 20) {

				//printf("(%d, %d)", down, rightw + i);
				if (down >= 0 && down <= 18 && rightw + i + 1 >= 0 && rightw + i + 1 <= 18)
				{
					whitedangerCoordinatesH[down][rightw + i + 1] += wcontinue;
				}
				if (down >= 0 && down <= 18 && rightw + i - 1 >= 0 && rightw + i - 1 <= 18)
				{
					whitedangerCoordinatesH[down][rightw + i - 1] += wcontinue;
				}
			}
		}
		//printf("Black:%2d", bcontinue);
		for (int i = 0; i < 5; i++)
		{
			if (blackContinue[h][i] != 20) {

				//printf("(%d, %d)", down, rightb + i);
				if (down >= 0 && down <= 18 && rightb + i + 1 >= 0 && rightb + i + 1 <= 18)
				{
					blackdangerCoordinatesH[down][rightb + i + 1] += bcontinue;
				}
				if (down >= 0 && down <= 18 && rightb + i - 1 >= 0 && rightb + i - 1 <= 18)
				{
					blackdangerCoordinatesH[down][rightb + i - 1] += bcontinue;
				}
			}
		}
		//printf("] ");
	}
}

int Vertical()
{
	for (int right = 0; right < SIZE; right++)
	{
		wquantity = 0, bquantity = 0;
		for (int down = 0; down < SIZE; down++)
		{
			if (coordinates[down][right] == whiteSign)
			{
				++wquantity;
			}
			if (coordinates[down][right] == blackSign)
			{
				++bquantity;
			}
		}
		vetical[0][right] = wquantity;
		vetical[1][right] = bquantity;

	}
	//printf("White:");
	for (int right = 0; right < SIZE; right++)
	{
		//printf("%2d", vetical[0][right]);
	}
	//printf("\nBlack:");
	for (int right = 0; right < SIZE; right++)
	{
		//printf("%2d", vetical[1][right]);
	}
	//printf("\n---------------------------------------------\n");

	for (int right = 0; right < SIZE; right++)
	{
		//printf("Vertical %d:", right);
		int downw = 20;
		int downb = 20;
		int h = 1;
		Vertical_white(right);
		Vertical_black(right);

		for (int i = 0; i < 10; i++)
		{
			if (whiteContinue[0][i] != 20)
			{
				downw = whiteContinue[0][i];
			}
			if (blackContinue[0][i] != 20)
			{
				downb = blackContinue[0][i];
			}
			if (whiteContinue[0][i] != 20 || blackContinue[0][i] != 20)
			{
				Vertical_continue(h, right, downw, downb);
				h++;
			}

		}
		//printf("\n");
	}
	printf("\n");
}

int Vertical_white(int right)
{
	int h = 1;
	int max = 1;
	int before = 20;
	int next = 0;
	for (int down = 0; down < SIZE; down++)
	{

		int blank = 0;
		wcontinue = 0;

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				whiteContinue[i][j] = 20;
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if (down + i > 18 || right > 18 || down + i < 0 || right < 0)
			{
				break;
			}
			else if (coordinates[down + i][right] == blackSign || blank > 1)
			{
				break;
			}
			else if (coordinates[down + i][right] == whiteSign)
			{
				whiteContinue[h][i] = 1;
				wcontinue++;
			}
			else if (coordinates[down + i][right] == 0)
			{
				blank++;
			}
		}
		if (wcontinue > max)
		{
			max = wcontinue;
		}
	}
	for (int down = 0; down < SIZE; down++)
	{
		int blank = 0;

		if (wcontinue != max)
		{
			for (int i = 0; i < 10; i++)
			{
				whiteContinue[h][i] = 20;
			}
		}
		wcontinue = 0;
		for (int i = 0; i < 10; i++)
		{
			if (down + i > 18 || right > 18 || down + i < 0 || right < 0)
			{
				break;
			}
			else if (coordinates[down + i][right] == blackSign || blank > 1)
			{
				break;
			}
			else if (coordinates[down + i][right] == whiteSign)
			{
				whiteContinue[h][i] = 1;
				wcontinue++;
			}
			else if (coordinates[down + i][right] == 0)
			{
				blank++;
			}
			if (wcontinue == max)
			{
				if (before == down + i || before + 1 == down + i)
				{
					continue;
				}
			}
		}
		if (wcontinue == max && wcontinue > 1)
		{
			if (before == down + i || before + 1 == down + i)
			{
				continue;
			}
			else
			{
				whiteContinue[0][next] = down;
				next++;
				h++;
				before = down + i;
			}
		}
	}
	wcontinue = max;
}

int Vertical_black(int right)
{
	int h = 1;
	int max = 1;
	int before = 20;
	int next = 0;
	for (int down = 0; down < SIZE; down++)
	{

		int blank = 0;
		bcontinue = 0;

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				blackContinue[i][j] = 20;
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if (down + i > 18 || right > 18 || down + i < 0 || right < 0)
			{
				break;
			}
			else if (coordinates[down + i][right] == whiteSign || blank > 1)
			{
				break;
			}
			else if (coordinates[down + i][right] == blackSign)
			{
				blackContinue[h][i] = 1;
				bcontinue++;
			}
			else if (coordinates[down + i][right] == 0)
			{
				blank++;
			}
		}
		if (bcontinue > max)
		{
			max = bcontinue;
		}
	}
	for (int down = 0; down < SIZE; down++)
	{
		int blank = 0;

		if (bcontinue != max)
		{
			for (int i = 0; i < 10; i++)
			{
				blackContinue[h][i] = 20;
			}
		}
		bcontinue = 0;
		for (int i = 0; i < 10; i++)
		{
			if (down + i > 18 || right > 18 || down + i < 0 || right < 0)
			{
				break;
			}
			else if (coordinates[down + i][right] == whiteSign || blank > 1)
			{
				break;
			}
			else if (coordinates[down + i][right] == blackSign)
			{
				blackContinue[h][i] = 1;
				bcontinue++;
			}
			else if (coordinates[down + i][right] == 0)
			{
				blank++;
			}
			if (bcontinue == max)
			{
				if (before == down + i || before + 1 == down + i)
				{
					continue;
				}
			}
		}
		if (bcontinue == max && bcontinue > 1)
		{
			if (before == down + i || before + 1 == down + i)
			{
				continue;
			}
			else
			{
				blackContinue[0][next] = down;
				next++;
				h++;
				before = down + i;
			}
		}
	}
	bcontinue = max;
}

int Vertical_continue(int h, int right, int downw, int downb)
{
	if (wcontinue > bcontinue)
	{
		//printf("[");
		if (wcontinue >= 3)
		{
			//printf("DANGER!!");
		}
		//printf("/White:%2d/", wcontinue);
		for (int i = 0; i < 5; i++) {
			if (whiteContinue[h][i] != 20)
			{
				//printf("(%d, %d)", downw + i, right);

				if (downw + i + 1 >= 0 && downw + i + 1 <= 18 && right >= 0 && right <= 18)
				{
					whitedangerCoordinatesV[downw + i + 1][right] += wcontinue;
				}
				if (downw + i - 1 >= 0 && downw + i - 1 <= 18 && right >= 0 && right <= 18)
				{
					whitedangerCoordinatesV[downw + i - 1][right] += wcontinue;
				}
			}
		}
		//printf("] ");
	}
	else if (wcontinue < bcontinue)
	{
		//printf("[");
		if (bcontinue >= 3)
		{
			//printf("DANGER!!");
		}
		//printf("/Black:%2d/", bcontinue);
		for (int i = 0; i < 5; i++) {
			if (blackContinue[h][i] != 20) {
				//printf("(%d, %d)", downb + i, right);


				if (downb + i + 1 >= 0 && downb + i + 1 <= 18 && right >= 0 && right <= 18)
				{
					blackdangerCoordinatesV[downb + i + 1][right] += bcontinue;
				}
				if (downb + i - 1 >= 0 && downb + i - 1 <= 18 && right >= 0 && right <= 18)
				{
					blackdangerCoordinatesV[downb + i - 1][right] += bcontinue;
				}
			}
		}
		//printf("] ");
	}
	else if (wcontinue > 1 && wcontinue == bcontinue)
	{
		//printf("[");
		if (wcontinue >= 3 || bcontinue >= 3)
		{
			//printf("DANGER!!");
		}
		//printf("White:%2d", wcontinue);
		for (int i = 0; i < 5; i++) {
			if (whiteContinue[h][i] != 20) {

				//printf("(%d, %d)", downw + i, right);

				if (downw + i + 1 >= 0 && downw + i + 1 <= 18 && right >= 0 && right <= 18)
				{
					whitedangerCoordinatesV[downw + i + 1][right] += wcontinue;
				}
				if (downw + i - 1 >= 0 && downw + i - 1 <= 18 && right >= 0 && right <= 18)
				{
					whitedangerCoordinatesV[downw + i - 1][right] += wcontinue;
				}
			}
		}
		//printf("Black:%2d", bcontinue);
		for (int i = 0; i < 5; i++)
		{
			if (blackContinue[h][i] != 20) {

				//printf("(%d, %d)", downb + i, right);
				if (downb + i + 1 >= 0 && downb + i + 1 <= 18 && right >= 0 && right <= 18)
				{
					blackdangerCoordinatesV[downb + i + 1][right] += bcontinue;
				}
				if (downb + i - 1 >= 0 && downb + i - 1 <= 18 && right >= 0 && right <= 18)
				{
					blackdangerCoordinatesV[downb + i - 1][right] += bcontinue;
				}
			}
		}
		//printf("] ");
	}
}

void DeleteUstack()
{
	s* trash;
	while (topU != NULL)
	{
		trash = popU();
		free(trash);
	}
}

void DeleteRstack()
{
	s* trash;
	while (topR != NULL)
	{
		trash = popR();
		free(trash);
	}
}



int down, right;

void AutoLay()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{

			whitedangerCoordinates[i][j] = whitedangerCoordinatesD1[i][j] + whitedangerCoordinatesD3[i][j] + whitedangerCoordinatesH[i][j] + whitedangerCoordinatesV[i][j];
			blackdangerCoordinates[i][j] = blackdangerCoordinatesD1[i][j] + blackdangerCoordinatesD3[i][j] + blackdangerCoordinatesH[i][j] + blackdangerCoordinatesV[i][j];
		}
	}

	if (turn % 2 == whiteSign)
	{
		down = 0;
		right = 0;
		int max = 0;
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				if (coordinates[i][j] != 0)
				{
					blackdangerCoordinates[i][j] = 0;
				}
				if (max < blackdangerCoordinates[i][j])
				{
					max = blackdangerCoordinates[i][j];
					down = i;
					right = j;
				}
			}
		}
		//만약 위험한 곳 없을 때 0,0 그대로 나오지 않게 예외처리 해야함 방어할거 없으면 공격하게끔

		if (down == 0 && right == 0)
		{
			max = 0;
			for (int i = 0; i < SIZE; i++)
			{
				for (int j = 0; j < SIZE; j++)
				{
					if (coordinates[i][j] != 0)
					{
						whitedangerCoordinates[i][j] = 0;
					}
					if (max < whitedangerCoordinates[i][j])
					{
						max = whitedangerCoordinates[i][j];
						down = i;
						right = j;
					}
				}
			}
		}
		if (down == 0 && right == 0)
		{
			for (int i = 0; i < SIZE; i++)
			{
				for (int j = 0; j < SIZE; j++)
				{
					if (coordinates[i][j] == whiteSign)
					{
						if (coordinates[i + 1][j + 1] == 0 && i + 1 >= 0 && i + 1 < 19 && j + 1 >= 0 && j + 1 < 19)
						{
							down = i + 1;
							right = j + 1;
						}
						else if (coordinates[i - 1][j - 1] == 0 && i - 1 >= 0 && i - 1 < 19 && j - 1 >= 0 && j - 1 < 19)
						{
							down = i - 1;
							right = j - 1;
						}
						else if (coordinates[i + 1][j - 1] == 0 && i + 1 >= 0 && i + 1 < 19 && j - 1 >= 0 && j - 1 < 19)
						{
							down = i + 1;
							right = j - 1;
						}
						else if (coordinates[i - 1][j + 1] == 0 && i - 1 >= 0 && i - 1 < 19 && j + 1 >= 0 && j + 1 < 19)
						{
							down = i - 1;
							right = j + 1;
						}
						else if (coordinates[i + 1][j] == 0 && i + 1 >= 0 && i + 1 < 19 && j >= 0 && j < 19)
						{
							down = i + 1;
							right = j;
						}
						else if (coordinates[i - 1][j] == 0 && i - 1 >= 0 && i - 1 < 19 && j >= 0 && j < 19)
						{
							down = i - 1;
							right = j;
						}
						else if (coordinates[i][j + 1] == 0 && i >= 0 && i < 19 && j + 1 >= 0 && j + 1 < 19)
						{
							down = i;
							right = j + 1;
						}
						else if (coordinates[i][j - 1] == 0 && i >= 0 && i < 19 && j - 1 >= 0 && j - 1 < 19)
						{
							down = i;
							right = j - 1;
						}
					}
				}
			}
		}
		if (down == 0 && right == 0)
		{
			for (int i = 0; i <= 18; i++)
			{
				for (int j = 8; j <= 10; j++)
				{
					if (coordinates[i][j] == 0)
					{
						down = i;
						right = j;
					}
				}
			}
			for (int i = 2; i <= 15; i++)
			{
				for (int j = 8; j <= 10; j++)
				{
					if (coordinates[i][j] == 0)
					{
						down = i;
						right = j;
					}
				}
			}
			for (int i = 5; i <= 13; i++)
			{
				for (int j = 8; j <= 10; j++)
				{
					if (coordinates[i][j] == 0)
					{
						down = i;
						right = j;
					}
				}
			}
			for (int i = 8; i <= 10; i++)
			{
				for (int j = 8; j <= 10; j++)
				{
					if (coordinates[i][j] == 0)
					{
						down = i;
						right = j;
					}
				}
			}
		}
	}
	else
	{
		down = 0;
		right = 0;
		int max = 0;
		int a, b;
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				if (coordinates[i][j] != 0)
				{
					whitedangerCoordinates[i][j] = 0;
				}
				if (max < whitedangerCoordinates[i][j])
				{
					max = whitedangerCoordinates[i][j];
					down = i;
					right = j;
				}
			}
		}
		//만약 위험한 곳 없을 때 0,0 그대로 나오지 않게 예외처리 해야함 방어할거 없으면 공격하게끔

		if (down == 0 && right == 0)
		{
			max = 0;
			for (int i = 0; i < SIZE; i++)
			{
				for (int j = 0; j < SIZE; j++)
				{
					if (coordinates[i][j] != 0)
					{
						blackdangerCoordinates[i][j] = 0;
					}
					if (max < blackdangerCoordinates[i][j])
					{
						max = blackdangerCoordinates[i][j];
						down = i;
						right = j;
					}
				}
			}
		}
		if (down == 0 && right == 0)
		{
			for (int i = 0; i < SIZE; i++)
			{
				for (int j = 0; j < SIZE; j++)
				{
					if (coordinates[i][j] == blackSign)
					{
						if (coordinates[i + 1][j + 1] == 0 && i + 1 >= 0 && i + 1 < 19 && j + 1 >= 0 && j + 1 < 19)
						{
							down = i + 1;
							right = j + 1;
						}
						else if (coordinates[i - 1][j - 1] == 0 && i - 1 >= 0 && i - 1 < 19 && j - 1 >= 0 && j - 1 < 19)
						{
							down = i - 1;
							right = j - 1;
						}
						else if (coordinates[i + 1][j - 1] == 0 && i + 1 >= 0 && i + 1 < 19 && j - 1 >= 0 && j - 1 < 19)
						{
							down = i + 1;
							right = j - 1;
						}
						else if (coordinates[i - 1][j + 1] == 0 && i - 1 >= 0 && i - 1 < 19 && j + 1 >= 0 && j + 1 < 19)
						{
							down = i - 1;
							right = j + 1;
						}
						else if (coordinates[i + 1][j] == 0 && i + 1 >= 0 && i + 1 < 19 && j >= 0 && j < 19)
						{
							down = i + 1;
							right = j;
						}
						else if (coordinates[i - 1][j] == 0 && i - 1 >= 0 && i - 1 < 19 && j >= 0 && j < 19)
						{
							down = i - 1;
							right = j;
						}
						else if (coordinates[i][j + 1] == 0 && i >= 0 && i < 19 && j + 1 >= 0 && j + 1 < 19)
						{
							down = i;
							right = j + 1;
						}
						else if (coordinates[i][j - 1] == 0 && i >= 0 && i < 19 && j - 1 >= 0 && j - 1 < 19)
						{
							down = i;
							right = j - 1;
						}
					}
				}
			}
		}
		if (down == 0 && right == 0)
		{
			for (int i = 0; i <= 18; i++)
			{
				for (int j = 8; j <= 10; j++)
				{
					if (coordinates[i][j] == 0)
					{
						down = i;
						right = j;
					}
				}
			}
			for (int i = 2; i <= 15; i++)
			{
				for (int j = 8; j <= 10; j++)
				{
					if (coordinates[i][j] == 0)
					{
						down = i;
						right = j;
					}
				}
			}
			for (int i = 5; i <= 13; i++)
			{
				for (int j = 8; j <= 10; j++)
				{
					if (coordinates[i][j] == 0)
					{
						down = i;
						right = j;
					}
				}
			}
			for (int i = 8; i <= 10; i++)
			{
				for (int j = 8; j <= 10; j++)
				{
					if (coordinates[i][j] == 0)
					{
						down = i;
						right = j;
					}
				}
			}
		}
	}



	whiteNum = 0;
	blackNum = 0;

	if (down < 0 || right < 0 || down > 18 || right > 18)
	{
		printf("INVALID VALUE\n");
		return;
	}
	else if (coordinates[down][right] == 0)
	{
		s* new = malloc(sizeof(s));
		new->x = down;
		new->y = right;
		if (turn % 2 == 1)
		{
			new->color = whiteSign;
			pushU(new);
			coordinates[down][right] = whiteSign;
			DeleteRstack();
			system("cls");
			Update();
		}
		else
		{
			new->color = blackSign;
			pushU(new);
			coordinates[down][right] = blackSign;
			DeleteRstack();
			system("cls");
			Update();
		}
	}
	else if (coordinates[down][right] != 0)
	{
		printf("ALREADY PLACED\n");
		return;
	}
	++turn;
	printf("%d, %d\n", down, right);
}

int Laying()
{
	printf("White:%2d, Black:%2d\n", whiteNum, blackNum);
	whiteNum = 0;
	blackNum = 0;
	printf("Down:");
	scanf("%d", &down);
	printf("Right:");
	scanf("%d", &right);

	if (down < 0 || right < 0 || down > 18 || right > 18)
	{
		printf("INVALID VALUE\n");
		return;
	}
	else if (coordinates[down][right] == 0)
	{
		s* new = malloc(sizeof(s));
		new->x = down;
		new->y = right;
		if (turn % 2 == 1)
		{
			new->color = whiteSign;
			pushU(new);
			coordinates[down][right] = whiteSign;
			DeleteRstack();
			system("cls");
			Update();
		}
		else
		{
			new->color = blackSign;
			pushU(new);
			coordinates[down][right] = blackSign;
			DeleteRstack();
			system("cls");
			Update();
		}
	}
	else if (coordinates[down][right] != 0)
	{
		printf("ALREADY PLACED\n");
		return;
	}
	++turn;
	AutoLay();

}

void Save()
{
	file = fopen("5MOK.txt", "w");
	for (down = 0; down < SIZE; down++)
	{
		for (right = 0; right < SIZE; right++)
		{
			fputc(coordinates[down][right], file);
		}
	}
	fclose(file);

	file = fopen("stackU.txt", "w");
	for (s* data = topU; data != NULL; data = data->next)
	{
		fprintf(file, "%d %d %d ", data->x, data->y, data->color);
	}
	fclose(file);
	file = fopen("stackR.txt", "w");
	for (s* data = topR; data != NULL; data = data->next)
	{
		fprintf(file, "%d %d %d ", data->x, data->y, data->color);
	}
	fclose(file);

	printf("Saved\n");
}

void Load()
{
	file = fopen("5MOK.txt", "r");
	for (down = 0; down < SIZE; down++)
	{
		for (right = 0; right < SIZE; right++)
		{
			coordinates[down][right] = fgetc(file);
		}
	}
	fclose(file);

	DeleteUstack();
	DeleteRstack();

	file = fopen("stackU.txt", "r");
	while (1)
	{
		s* new = malloc(sizeof(s));
		fscanf(file, "%d %d %d ", &new->x, &new->y, &new->color);
		if (new->color != whiteSign && new->color != blackSign)
		{
			free(new);
			break;
		}
		pushB(new);
		++i;
	}

	s* data;
	while (topB != NULL)
	{
		data = popB();
		pushU(data);
	}

	turn = i;

	file = fopen("stackR.txt", "r");
	while (1)
	{
		s* new = malloc(sizeof(s));
		fscanf(file, "%d %d %d ", &new->x, &new->y, &new->color);
		if (new->color != whiteSign && new->color != blackSign)
		{
			free(new);
			break;
		}
		pushB(new);
	}

	while (topB != NULL)
	{
		data = popB();
		pushR(data);
	}
}

int main()
{
	topU = NULL;
	topR = NULL;
	topB = NULL;
	int order;

	Update();
	while (1)
	{

		AutoLay();
		getchar();

		//Laying();

		

		
		//printf("---------------------------------------------\n");
		//if (turn % 2 == whiteSign)
		//{
		//	printf("Turn: white\n");
		//}
		//else
		//{
		//	printf("Turn: black\n");
		//}

		//printf("1.Save\n2.Load\n3.Undo\n4.ReUndo\n5.Put\nPress Number:");
		//scanf("%d", &order);
		//switch (order) {
		//case 1:
		//{
		//	Save();
		//	break;
		//}
		//case 2:
		//{
		//	Load();
		//	system("cls");
		//	Update();
		//	break;
		//}
		//case 3:
		//{
		//	s* data = popU();
		//	if (data == NULL)
		//	{
		//		printf("YOU CAN'T\n");
		//		continue;
		//	}
		//	pushR(data);
		//	coordinates[data->x][data->y] = 0;

		//	system("cls");
		//	turn--;
		//	whiteNum = 0;
		//	blackNum = 0;
		//	Update();
		//	break;
		//}
		//case 4:
		//{
		//	s* data = popR();
		//	if (data == NULL)
		//	{
		//		printf("YOU CAN'T\n");
		//		continue;
		//	}
		//	pushU(data);
		//	coordinates[data->x][data->y] = data->color;

		//	system("cls");
		//	turn++;
		//	whiteNum = 0;
		//	blackNum = 0;
		//	Update();
		//	break;
		//}
		//case 5:
		//{
		//	Laying();
		//	break;
		//}
		//case 6:
		//{
		//	AutoLay();
		//	break;
		//}
		//}
	}
}