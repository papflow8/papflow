#include "Collider.h"

Collider::Collider() : frame(0), needclear(false)
{
	setFrameWidth(TILE_WIDTH);
	setFrameHeight(TILE_HEIGHT);
	setNeedClear(false);
	setNeedDraw(true);

	Coord = new Vec[(frame_height + frame_width) * 2 - 2];
	CoordOld = new Vec[(frame_height + frame_width) * 2 - 2];
	count = 0;
	countOld = 0;

	
}

Collider::Collider(float _x, float _y, float _w, float _h)
{
	StartX = _x;
	StartY = _y;
	frame_x = _x + (_w - 1) / 2;
	frame_y = _y + (_h - 1) / 2;
	frame_width = _w;
	frame_height = _h;
	needdraw = true;
	Coord = new Vec[(frame_height + frame_width) * 2 - 4];
	CoordOld = new Vec[(frame_height + frame_width) * 2 - 4];
	count = 0;
	countOld = 0;
}

Collider::~Collider()
{
	delete[] Coord;
	delete[] CoordOld;
}

float Collider::getFrameX()
{
	return frame_x;
}

void Collider::setFrameX(float _x)
{
	frame_x = _x;
}

float Collider::getFrameY()
{
	return frame_y;
}

void Collider::setFrameY(float _y)
{
	frame_y = _y;
}

float Collider::getFrameOldX()
{
	return frame_Oldx;
}

void Collider::setFrameOldX(float _x)
{
	frame_Oldx = _x;
}

float Collider::getFrameOldY()
{
	return frame_Oldy;
}

void Collider::setFrameOldY(float _y)
{
	frame_Oldy = _y;
}

float Collider::getFrameWidth()
{
	return frame_width;
}

void Collider::setFrameWidth(int _w)
{
	frame_width = _w;
}

float Collider::getFrameHeight()
{
	return frame_height;
}

void Collider::setFrameHeight(int _h)
{
	frame_height = _h;
}

bool Collider::getNeedClear()
{
	return needclear;
}

void Collider::setNeedClear(bool n)
{
	needclear = n;
}

void Collider::setNeedDraw(bool n)
{
	needdraw = n;
}

void Collider::InitCoord()
{
	//float Left_x = frame_x - frame_width / 2;
	//float Right_x = frame_x + frame_width / 2 - 1;
	//float Up_y = frame_y - frame_height / 2;
	//float Down_y = frame_y + frame_height / 2 - 1;
	float Left_x = StartX;
	float Right_x = StartX + frame_width - 1;
	float Up_y = StartY;
	float Down_y = StartY + frame_height - 1;
	countOld = 0;
	count = 0;
	for (int i = 0; i < count; i++, countOld++)
	{
		CoordOld[countOld].x = Coord[i].x;
		CoordOld[countOld].y = Coord[i].y;
		CoordOld[countOld].needDraw = true;
	}

	for (float x = Left_x; x <= Right_x; x++)
	{
		Coord[count++] = { x, Up_y, true };
		CoordOld[countOld++] = { x, Up_y, true };
		Coord[count++] = { x, Down_y, true };
		CoordOld[countOld++] = { x, Down_y, true };
	}
	for (float y = Up_y + 1; y <= Down_y - 1; y++)
	{
		Coord[count++] = { Left_x, y, true };
		CoordOld[countOld++] = { Left_x, y, true };
		Coord[count++] = { Right_x, y, true };
		CoordOld[countOld++] = { Right_x, y, true };
	}
}

void Collider::UpdateCoord()
{
	float Left_x = StartX;
	float Right_x = StartX + frame_width - 1;
	float Up_y = StartY;
	float Down_y = StartY + frame_height - 1;

	count = 0;
	for (float x = Left_x; x <= Right_x; x++)
	{
		Coord[count++] = { x, Up_y, true };
		Coord[count++] = { x, Down_y, true };
	}
	for (float y = Up_y + 1; y <= Down_y - 1; y++)
	{
		Coord[count++] = { Left_x, y, true };
		Coord[count++] = { Right_x, y, true };
	}

	if (GroundChecking)
	{
		return;
	}
	for (int j = 0; j < countOld; j++)
	{
		for (int i = 0; i < count; i++)
		{
			if ((int)Coord[i].x == (int)CoordOld[j].x && (int)Coord[i].y == (int)CoordOld[j].y)
			{
				Coord[i].needDraw = false;
				CoordOld[j].needDraw = false;
				break;
			}
		}
	}
}

void Collider::SaveOldCoord()
{
	countOld = 0;
	for (int i = 0; i < count; i++, countOld++)
	{
		CoordOld[countOld].x = Coord[i].x;
		CoordOld[countOld].y = Coord[i].y;
		CoordOld[countOld].needDraw = true;
	}
}

bool Collider::CheckCollision_RectRect(Collider &col)
{
	float col_x = col.getFrameX();
	float col_y = col.getFrameY();
	float col_w = col.getFrameWidth();
	float col_h = col.getFrameHeight();

	if ((abs(frame_x - col_x) < (col_w + frame_width) / 2) && (abs(frame_y - col_y) < (col_h + frame_height) / 2))
		return true;
	return false;
}

bool Collider::CheckCollision_RectTri(TriangleCollider* col)
{
	for (int i = 0; i < count; i++)
	{
		if (col->IsInTriangle(col->tri_Vec, Coord[i]))
		{
			return true;
		}
	}
	return false;
}

bool Collider::CheckCollision_RectTriReverse(TriangleCollider * col)
{
	for (int i = 0; i < count; i++)
	{
		if (col->IsInTriangleReverse(col->tri_Vec, Coord[i]))
		{
			return true;
		}
	}
	return false;
}

void Collider::DrawCollider()
{
	return;
	textcolor(GREEN);
	if (needclear)
	{
		for (int i = 0; i < countOld; i++)
		{
			if (CoordOld[i].needDraw)
			{
				gotoxy((int)CoordOld[i].x, (int)CoordOld[i].y);
				printf(" ");
			}
		}
		needclear = false;
	}
	/*if (needclear)
	{
		for (int x = frame_Oldx - frame_width / 2; x < frame_Oldx + frame_width / 2; x++)
		{
			gotoxy(x, (int)(frame_Oldy - frame_height / 2));
			printf(" ");
			gotoxy(x, (int)(frame_Oldy + frame_height / 2));
			printf(" ");
		}
		for (int y = frame_Oldy - frame_height / 2; y < frame_Oldy + frame_height / 2; y++)
		{
			gotoxy((int)frame_Oldx - (int)(frame_width / 2), y);
			printf(" ");
			gotoxy((int)(frame_Oldx + frame_width / 2), y);
			printf(" ");
		}
		needclear = false;
	}*/


	/*if (frame++ < 10)
	{
		return;
	}
	frame = 0;*/
	if (needdraw)
	{
		for (int i = 0; i < count; i++)
		{
			if (Coord[i].needDraw)
			{
				gotoxy((int)Coord[i].x, (int)Coord[i].y);
				printf("█");
			}
		}
		needdraw = false;
	}
	

	/*for (int x = frame_x - frame_width / 2; x < frame_x + frame_width / 2; x++)
	{
		gotoxy(x, (int)(frame_y - frame_height / 2));
		printf("█");
		gotoxy(x, (int)(frame_y + frame_height / 2));
		printf("█");
	}
	for (int y = frame_y - frame_height / 2; y < frame_y + frame_height / 2; y++)
	{
		gotoxy((int)(frame_x - frame_width / 2), y);
		printf("█");
		gotoxy((int)(frame_x + frame_width / 2), y);
		printf("█");
	}*/
}

void Collider::MoveCollider(int _MoveX, int _MoveY)
{
	frame_x += _MoveX;
	frame_y += _MoveY;
}

void Collider::UpdateStartPos(float _x, float _y, float _w, float _h)
{
	StartX = _x + (_w - 1.0f) / 2 - (getFrameWidth() - 1.0f) / 2;
	StartY = _y + (_h - 1.0f) - (frame_height - 1.0f);
	
	frame_x = _x + (frame_width - 1.0f) / 2;
	frame_y = _y + (frame_height - 1.0f) / 2;
}

//void Collider::PositionUpdate(int _x, int _y)
//{
//	setFrameOldX(frame_x);
//	setFrameOldY(frame_y);
//	setFrameX(_x + TILE_WIDTH / 2);
//	setFrameY(_y + TILE_HEIGHT / 2);
//}

//float TriangleCollider::Cal_Rad(int _x1, int _y1, int _x2, int _y2)
//{
//	//sqrt(abs(_x1 - _x2) * abs(_x1 - _x2) + abs(_y1 - _y2) * abs(_y1 - _y2));
//	return atan(abs(_x1 - _x2) / abs(_y1 - _y2));
//}

TriangleCollider::TriangleCollider() : PI(3.14), needclear(false)
{
	Coord = NULL;
	CoordOld = NULL;
	isCollider = true;
	visible = true;
}

TriangleCollider::TriangleCollider(Vec _v[3]) : PI(3.14)
{
	Coord = NULL;
	CoordOld = NULL;
	isCollider = true;
	visible = true;
	VerMoving = false;
	float min_x, max_x, min_y, max_y;
	max_x = min_x = _v[0].x;
	max_y = min_y = _v[0].y;

	for (int i = 0; i < 3; i++)
	{
		tri_Vec[i] = _v[i];
		if (min_x > _v[i].x)
		{
			min_x = _v[i].x;
		}
		if (max_x < _v[i].x)
		{
			max_x = _v[i].x;
		}
		if (min_y > _v[i].y)
		{
			min_y = _v[i].y;
		}
		if (max_y < _v[i].y)
		{
			max_y = _v[i].y;
		}
	}
	int _width = max_x - min_x;
	int _height = max_y - min_y;
	Coord = new Vec[_height * _width];
	CoordOld = new Vec[_height * _width];
	count = 0;
	countOld = 0;

	/*for (int i = 0; i < _width; i++)
	{
		Coord[i] = new Vec[_width];
	}*/

	for (float y = min_y; y <= max_y; y++)
	{
		for (float x = min_x; x <= max_x; x++)
		{
			if (IsInTriangle(_v, { x, y, false }))
			{
				Coord[count++] = { x , y, true };
				CoordOld[countOld++] = { x, y, false };
			}
		}
	}
}

TriangleCollider::~TriangleCollider()
{
	delete[] Coord;
	delete[] CoordOld;
}

void TriangleCollider::setTriangle(Vec _v[3])
{
	float min_x, max_x, min_y, max_y;
	max_x = min_x = _v[0].x;
	max_y = min_y = _v[0].y;

	for (int i = 0; i < 3; i++)
	{
		tri_Vec[i] = _v[i];
		if (min_x > _v[i].x)
		{
			min_x = _v[i].x;
		}
		if (max_x < _v[i].x)
		{
			max_x = _v[i].x;
		}
		if (min_y > _v[i].y)
		{
			min_y = _v[i].y;
		}
		if (max_y < _v[i].y)
		{
			max_y = _v[i].y;
		}
	}
	int _width = max_x - min_x;
	int _height = max_y - min_y;
	Coord = new Vec[_height * _width];
	CoordOld = new Vec[_height * _width];
	count = 0;
	countOld = 0;
	
	/*for (int i = 0; i < _width; i++)
	{
		Coord[i] = new Vec[_width];
	}*/
	
	for (float y = min_y; y <= max_y; y++)
	{
		for (float x = min_x; x <= max_x; x++)
		{
			if (IsInTriangle(_v, { x, y, false}))
			{
				Coord[count++] = { x , y, true};
				CoordOld[countOld++] = { x, y, false};
			}
		}
	}
}

void TriangleCollider::setNeedClear(bool _b)
{
	needclear = _b;
}

void TriangleCollider::setNeedDraw(bool _b)
{
	needdraw = _b;
}

void TriangleCollider::resetNeedDraw()
{
	for (int i = 0; i < count; i++)
	{
		Coord[i].needDraw = true;
	}
}

void TriangleCollider::TriInit()
{
	Vec temp_v[3] = { {100, 80}, {120, 80}, {120, 70} };
	for (int i = 0; i < 3; i++)
	{
		tri_Vec[i] = temp_v[i];
	}
	setTriangle(tri_Vec);
	needclear = false;
}

void TriangleCollider::UpdateCoord()
{
	countOld = 0;
	for (int i = 0; i < count; i++, countOld++)
	{
		CoordOld[countOld].x = Coord[i].x;
		CoordOld[countOld].y = Coord[i].y;
		CoordOld[countOld].needDraw = true;
	}

	float min_x, max_x, min_y, max_y;
	max_x = min_x = tri_Vec[0].x;
	max_y = min_y = tri_Vec[0].y;

	for (int i = 0; i < 3; i++)
	{
		tri_Vec[i] = tri_Vec[i];
		if (min_x > tri_Vec[i].x)
		{
			min_x = tri_Vec[i].x;
		}
		if (max_x < tri_Vec[i].x)
		{
			max_x = tri_Vec[i].x;
		}
		if (min_y > tri_Vec[i].y)
		{
			min_y = tri_Vec[i].y;
		}
		if (max_y < tri_Vec[i].y)
		{
			max_y = tri_Vec[i].y;
		}
	}
	/*
	int _width = max_x - min_x;
	int _height = max_y - min_y;
	Coord = new Vec[_height * _width];
	CoordOld = new Vec[_height * _width];
	*/
	
	/*for (int i = 0; i < _width; i++)
	{
		Coord[i] = new Vec[_width];
	}*/
	count = 0;
	for (float y = min_y; y <= max_y; y++)
	{
		for (float x = min_x; x <= max_x; x++)
		{
			if (IsInTriangle(tri_Vec, { x,y,true }))
			{
				Coord[count++] = { x , y, true };
			}
		}
	}

	//?binary search..same place
	for (int j = 0; j < countOld; j++)
	{
		for (int i = 0; i < count; i++)
		{
			if ((int)Coord[i].x == (int)CoordOld[j].x && (int)Coord[i].y == (int)CoordOld[j].y)
			{
				Coord[i].needDraw = false;
				CoordOld[j].needDraw = false;
				break;
			}
		}
	}
	/*for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < countOld; j++)
		{
			if ((int)Coord[i].x == (int)CoordOld[j].x && (int)Coord[i].y == (int)CoordOld[j].y)
			{
				Coord[i].needDraw = false;
				CoordOld[j].needDraw = false;
				break;
			}
		}
	}*/
}

void TriangleCollider::UpdateCoordReverse()
{
	countOld = 0;
	for (int i = 0; i < count; i++, countOld++)
	{
		CoordOld[countOld].x = Coord[i].x;
		CoordOld[countOld].y = Coord[i].y;
		CoordOld[countOld].needDraw = true;
	}

	float min_x, max_x, min_y, max_y;
	max_x = min_x = tri_Vec[0].x;
	max_y = min_y = tri_Vec[0].y;

	for (int i = 0; i < 3; i++)
	{
		tri_Vec[i] = tri_Vec[i];
		if (min_x > tri_Vec[i].x)
		{
			min_x = tri_Vec[i].x;
		}
		if (max_x < tri_Vec[i].x)
		{
			max_x = tri_Vec[i].x;
		}
		if (min_y > tri_Vec[i].y)
		{
			min_y = tri_Vec[i].y;
		}
		if (max_y < tri_Vec[i].y)
		{
			max_y = tri_Vec[i].y;
		}
	}

	count = 0;
	for (float y = min_y; y <= max_y; y++)
	{
		for (float x = min_x; x <= max_x; x++)
		{
			if (IsInTriangleReverse(tri_Vec, { x,y,true }))
			{
				Coord[count++] = { x , y, true };
			}
		}
	}

	for (int j = 0; j < countOld; j++)
	{
		for (int i = 0; i < count; i++)
		{
			if ((int)Coord[i].x == (int)CoordOld[j].x && (int)Coord[i].y == (int)CoordOld[j].y)
			{
				Coord[i].needDraw = false;
				CoordOld[j].needDraw = false;
				break;
			}
		}
	}
}

void TriangleCollider::ClearTriCol()
{
	for (int i = 0; i < count; i++)
	{
		gotoxy((int)Coord[i].x, (int)Coord[i].y);
		printf(" ");
	}
}

bool TriangleCollider::IsInTriangle(Vec v[3], Vec _p)
{
	int j = 0, i = 2;
	for (; j < 3; i = j++)
	{
		Vec _normal = { 2 * (v[i].y - v[j].y), (v[j].x - v[i].x) };
		Vec _checked = { _p.x - v[i].x, 2 * (_p.y - v[i].y) };
		if ((_normal.x * _checked.x + _normal.y * _checked.y) > 0)
			return false;
	}
	return true;
}

bool TriangleCollider::IsInTriangleReverse(Vec v[3], Vec _p)
{
	int j = 0, i = 2;
	for (; j < 3; i = j++)
	{
		Vec _normal = { 2 * -(v[i].y - v[j].y), -(v[j].x - v[i].x) };
		Vec _checked = { _p.x - v[i].x, 2 * (_p.y - v[i].y) };
		if ((_normal.x * _checked.x + _normal.y * _checked.y) > 0)
			return false;
	}
	return true;
}

void TriangleCollider::DrawTriangleCol()
{
	if (!visible)
	{
		return;
	}
	textcolor(YELLOW);
	/*if (InputManager::IsExtending(InputManager::k_D))
	{
		RotateTriCol({ 80, 80, false}, 3.1415926 / 10);
	}*/

	if (needclear)
	{
		for (int i = 0; i < countOld; i++)
		{
			if (CoordOld[i].needDraw) 
			{
				gotoxy((int)CoordOld[i].x, (int)CoordOld[i].y);
				printf(" ");
			}
			
		}
		needclear = false;
	}
	
	if (needdraw)
	{
		for (int i = 0; i < count; i++)
		{
			if (Coord[i].needDraw)
			{
				gotoxy((int)Coord[i].x, (int)Coord[i].y);
				printf("█");
			}
		}
	}

	

	/*for (p.y = 65 ; p.y < 95; p.y++)
	{
		for ( p.x = 70; p.x < 130; p.x++)
		{
			if (IsInTriangle(tri_Vec, p))
			{
				gotoxy((int)p.x, (int)p.y);
				printf("█");
			}
			else
			{
				gotoxy((int)p.x, (int)p.y);
				printf("*");
			}
		}
	}*/
}

void TriangleCollider::RotateTriCol(Vec _p, float _rad)
{
	for (int i = 0; i < 3; i++)
	{
		float temp_x = (tri_Vec[i].x - _p.x);
		float temp_y = -2 * (tri_Vec[i].y - _p.y);

		float temp_goal_x_offset = temp_x * cos(_rad) - temp_y * sin(_rad);
		float temp_goal_y_offset = temp_y * cos(_rad) + temp_x * sin(_rad);

		tri_Vec[i].x = temp_goal_x_offset > 0 ? _p.x + abs(temp_goal_x_offset) : _p.x - abs(temp_goal_x_offset);
		tri_Vec[i].y = temp_goal_y_offset > 0 ? _p.y - abs(temp_goal_y_offset) / 2 : _p.y + abs(temp_goal_y_offset) / 2;
		
		//tri_Vec[i].x = ((int)(tri_Vec[i].x * 10) % 10) < 4 ? tri_Vec[i].x : tri_Vec[i].x + 1;
		//tri_Vec[i].y = ((int)(tri_Vec[i].y * 10) % 10) < 4 ? tri_Vec[i].y : tri_Vec[i].y + 1;
	}
	needclear = true;
	UpdateCoord();
}

bool TriangleCollider::MoveVertex(Vec _target, int _time, int _triId)
{
	if (VerMoving && VerMovCount <= 0)
	{
		VerMoving = false;
		VerMovCount = 0;
		return true;
	}
	if (!VerMoving)
	{
		VerMoving = true;
		VerMovCount = _time;
		MoveDistanceX   = _target.x - tri_Vec[_triId].x;
		MoveDistanceY   = _target.y - tri_Vec[_triId].y;
		MoveX_PerFrame  = MoveDistanceX / _time;
		MoveY_PerFrame  = MoveDistanceY / _time;
	}

	
	tri_Vec[_triId].x += MoveX_PerFrame;
	tri_Vec[_triId].y += MoveY_PerFrame;
	
	UpdateCoord();
	setNeedClear(true);
	setNeedDraw(true);
	VerMovCount--;
	return false;
}
