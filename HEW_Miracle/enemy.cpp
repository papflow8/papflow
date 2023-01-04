//==========================
//	enemy.cpp
//==========================

#define		CONIOEX
#include	"enemy.h"//自身のヘッダーファイルをインクルード
#include	"player.h"
//======マクロ定義など

//======グローバル変数

//======プロトタイプ宣言　内部関数 自分だけが使う

//===================
//======初期化関数
void	EnemyInit()
{
	
}
//===================
//======更新関数
void	EnemyUpdate()
{
	
}

//===================
//======表示関数
void	EnemyDraw()
{
	
}
//===================
//======終了関数
void	EnemyUninit()
{
}

Spike::Spike()
{

}

Spike::Spike(Vec _v[3])
{
	TriCol = new TriangleCollider(_v);
	MoveCount = 0;
	isInited = false;
	isMoving = false;
	TriCol->setNeedDraw(false);
	for (int i = 0; i < 3; i++)
	{
		tri_Vec[i] = _v[i];
		tri_VecOld[i] = _v[i];
	}
}

Spike::~Spike()
{
	delete TriCol;
	delete bmp;
	delete[] Coord;
	delete[] CoordOld;
}

void Spike::SpikeUpdate()
{
	
}

void Spike::SetSpike(Vec _v[3])
{
	MoveCount = 0;
	isMoving = false;
	TriCol->isCollider = true;
	TriCol->setNeedDraw(true);
	for (int i = 0; i < 3; i++)
	{
		tri_Vec[i] = _v[i];
		TriCol->tri_Vec[i] = _v[i];
		tri_VecOld[i] = _v[i];
	}
	TriCol->UpdateCoord();
	TriCol->resetNeedDraw();
	TriCol->DrawTriangleCol();
	isInited = true;
}

void Spike::SetSpikeReverse(Vec _v[3])
{
	MoveCount = 0;
	isMoving = false;

	TriCol->setNeedDraw(true);
	for (int i = 0; i < 3; i++)
	{
		tri_Vec[i] = _v[i];
		TriCol->tri_Vec[i] = _v[i];
		tri_VecOld[i] = _v[i];
	}
	TriCol->UpdateCoordReverse();
	TriCol->resetNeedDraw();
	TriCol->DrawTriangleCol();
	isInited = true;
}

void Spike::DeleteSpike()
{
	TriCol->ClearTriCol();
	visible = false;
	TriCol->isCollider = false;
}

bool Spike::MoveSpikeTo(Vec _target, int _time)
{	
	if (isMoving && MoveCount <= 0)
	{
		isMoving = false;
		MoveCount = 0;
		return true;
	}
	if (!isMoving)
	{
		isMoving = true;
		MoveCount = _time;
		MoveDistanceX = _target.x - tri_Vec[0].x;
		MoveDistanceY = _target.y - tri_Vec[0].y;
		MoveX_PerFrame = MoveDistanceX / _time;
		MoveY_PerFrame = MoveDistanceY / _time;
	}
	
	MoveSpike(MoveX_PerFrame, MoveY_PerFrame);
	return false;
}

void Spike::MoveSpike(int _x, int _y)
{
	for (int i = 0; i < 3; i++)
	{
		tri_Vec[i].x += _x;
		tri_Vec[i].y += _y;
	}
	for (int i = 0; i < 3; i++)
	{
		TriCol->tri_Vec[i].x += _x;
		TriCol->tri_Vec[i].y += _y;
	}
	TriCol->UpdateCoord();
	TriCol->setNeedClear(true);
	TriCol->setNeedDraw(true);
	MoveCount--;
}

void Spike::SaveOldPos()
{
	for (int i = 0; i < 3; i++)
	{
		tri_VecOld[i].x = tri_Vec[i].x;
		tri_VecOld[i].y = tri_Vec[i].y;
	}
}

void Spike::CheckMove()
{
	for (int i = 0; i < 3; i++)
	{
		if (isMoving)
		{
			TriCol->setNeedClear(true);
			TriCol->setNeedDraw(true);
			break;
		}
		else
		{
			TriCol->setNeedDraw(false);
		}
	}
}
