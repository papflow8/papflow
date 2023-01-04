#define CONIOEX
#include "SavePoint.h"
#include "player.h"

Bitmap* SavePointBmp;
SavePoint::SavePoint()
{
}
SavePoint::SavePoint(float _x, float _y, Bitmap* _bmp)
{
	x = _x;
	y = _y;
	width = 20;
	height = 13;
	count = 0;
	countOld = 0;
	IsSaveing = false;
	visible = true;
	SaveCol = new Collider(x, y, (float)width, (float)height);
	//SaveCol->InitCoord();
	Coord = new VecPlus[width * height];
	CoordOld = new VecPlus[width * height];
	sourcebmp = _bmp;

	for (int dy = 0; dy < SaveCol->getFrameHeight(); dy++)
	{
		for (int dx = 0; dx < SaveCol->getFrameWidth(); dx++)
		{
			Coord[count++] = { dx + x, dy + y, true, sourcebmp->data[dy][dx] };
			CoordOld[countOld++] = { dx + x, dy + y, false, sourcebmp->data[dy][dx] };
		}
	}
}

SavePoint::~SavePoint()
{
	delete sourcebmp;
	delete SaveCol;
	delete[] Coord;
	delete[] CoordOld;
}

void SavePoint::DrawSavePoint()
{
	if (!visible)
	{
		return;
	}
	for (int i = 0; i < count; i++)
	{
		if (Coord[i].content == '0')
		{
			textcolor(BLACK);
			gotoxy(Coord[i].x, Coord[i].y);
			printf("█");
		}
		else if (Coord[i].content == 'G')
		{
			textcolor(DARKGRAY);
			gotoxy(Coord[i].x, Coord[i].y);
			printf("█");
		}
		else if (Coord[i].content == 'R')
		{
			textcolor(RED);
			gotoxy(Coord[i].x, Coord[i].y);
			printf("█");
		}
		else if (Coord[i].content == 'Y')
		{
			textcolor(YELLOW);
			gotoxy(Coord[i].x, Coord[i].y);
			printf("█");
		}
	}

}

void SavePoint::SavePointUpdate()
{

}

void SavePoint::DeleteSavePoint()
{
	visible = false;
	for (int i = 0; i < count; i++)
	{
		gotoxy(Coord[i].x, Coord[i].y);
		printf(" ");
	}
}

void SavePoint::DrawSavePointOnCol()
{
	bool isSaveing = SaveCol->CheckCollision_RectRect(*p_Player->getPlayerCol());
	if (isSaveing)
	{
		IsSaveing = true;
		for (int i = 0; i < count; i++)
		{
			if (Coord[i].content == '0')
			{
				textcolor(BLACK);
				gotoxy(Coord[i].x, Coord[i].y);
				printf("█");
			}
			else if (Coord[i].content == 'G')
			{
				textcolor(DARKGRAY);
				gotoxy(Coord[i].x, Coord[i].y);
				printf("█");
			}
			else if (Coord[i].content == 'R')
			{
				textcolor(RED);
				if (IsSaveing)
				{
					textcolor(GREEN);
				}
				gotoxy(Coord[i].x, Coord[i].y);
				printf("█");
			}
			else if (Coord[i].content == 'Y')
			{
				textcolor(YELLOW);
				gotoxy(Coord[i].x, Coord[i].y);
				printf("█");
			}
		}
	}
	else
	{
		if (IsSaveing)
		{
			for (int i = 0; i < count; i++)
			{
				if (Coord[i].content == '0')
				{
					textcolor(BLACK);
					gotoxy(Coord[i].x, Coord[i].y);
					printf("█");
				}
				else if (Coord[i].content == 'G')
				{
					textcolor(DARKGRAY);
					gotoxy(Coord[i].x, Coord[i].y);
					printf("█");
				}
				else if (Coord[i].content == 'R')
				{
					textcolor(RED);
					gotoxy(Coord[i].x, Coord[i].y);
					printf("█");
				}
				else if (Coord[i].content == 'Y')
				{
					textcolor(YELLOW);
					gotoxy(Coord[i].x, Coord[i].y);
					printf("█");
				}
			}
			IsSaveing = false;
		}
	}

	
	SaveCol->DrawCollider();
}
