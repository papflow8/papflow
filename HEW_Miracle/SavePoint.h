#pragma once
#include "main.h"
#include "Collider.h"
#include "Bitmap.h"

class SavePoint
{
public:
	SavePoint();
	SavePoint(float _x, float _y, Bitmap* _bmp);
	~SavePoint();
	float x;
	float y;
	int count;
	int countOld;
	int height;
	int width;
	bool IsSaveing;
	bool visible;
	int SaveId;

	void DrawSavePoint();
	void SavePointUpdate();
	void DeleteSavePoint();
	void DrawSavePointOnCol();
	Bitmap* sourcebmp;
	Collider* SaveCol;
	VecPlus* Coord;
	VecPlus* CoordOld;
};

