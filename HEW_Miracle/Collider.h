#pragma once

#define		CONIOEX
#include	"main.h"
//#include "field.h"



class TriangleCollider
{
public:
	TriangleCollider();
	TriangleCollider(Vec _v[3]);
	~TriangleCollider();

	bool isCollider;

	void setTriangle(Vec _v[3]);
	void setNeedClear(bool _b);
	void setNeedDraw(bool _b);
	void resetNeedDraw();

	void TriInit();
	void UpdateCoord();
	void UpdateCoordReverse();


	void ClearTriCol();
	//float Cal_Rad(int _x1, int _y1, int _x2, int _y2);

	bool IsInTriangle(Vec v[3], Vec _p);
	bool IsInTriangleReverse(Vec v[3], Vec _p);

	void DrawTriangleCol();
	void RotateTriCol(Vec _p, float _rad);

	int VerMovCount;
	int count;
	int countOld;
	Vec* Coord;
	Vec* CoordOld;

	bool VerMoving;
	bool MoveVertex(Vec _target, int _time, int _triId);
	Vec tri_Vec[3];
private:
	float	MoveDistanceX;
	float	MoveDistanceY;
	float	MoveX_PerFrame;
	float	MoveY_PerFrame;
	bool visible;
	bool needclear;
	bool needdraw;
	const float PI;

};


class Collider
{
public:
	Collider();
	Collider(float _x, float _y, float _w, float _h);
	~Collider();

	bool GroundChecking;
	float StartX;
	float StartY;
	bool visible;

	float getFrameX();
	void setFrameX(float _x);
	float getFrameY();
	void setFrameY(float _y);

	float getFrameOldX();
	void setFrameOldX(float _x);
	float getFrameOldY();
	void setFrameOldY(float _y);

	float getFrameWidth();
	void setFrameWidth(int _w);
	float getFrameHeight();
	void setFrameHeight(int _h);
	bool getNeedClear();
	void setNeedClear(bool n);
	void setNeedDraw(bool n);
	void InitCoord();
	void UpdateCoord();
	void SaveOldCoord();

	bool CheckCollision_RectRect(Collider& col);
	bool CheckCollision_RectTri(TriangleCollider* col);
	bool CheckCollision_RectTriReverse(TriangleCollider* col);


	void DrawCollider();
	void MoveCollider(int _MoveX, int _MoveY);
	void UpdateStartPos(float _x, float _y, float _w, float _h);
	//void PositionUpdate(int _x, int _y);
	int frame;
	int count;
	int countOld;
	Vec* Coord;
	Vec* CoordOld;
private:
	//Rect framerect;
	float frame_x;
	float frame_y;
	float frame_Oldx;
	float frame_Oldy;
	float frame_width;
	float frame_height;
	bool needclear;
	bool needdraw;
	bool OnCollision;

};

