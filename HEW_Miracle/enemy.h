#pragma once

#define		CONIOEX
#include	"main.h"
#include	"Bitmap.h"
#include	"Collider.h"
//============マクロ定義=====
#define		ENEMY_MAX	(1)		//敵の最大数


//============構造体定義=====
typedef	struct
{
	float	PositionX;
	float	PositionY;

	float	PositionOldX;//前回の敵座標(X)
	float	PositionOldY;//前回の敵座標(Y)
	BOOL	MoveFlag;	//移動したか移動していないか

	BOOL	UseFlag;	//構造体が初期化してあるか
	int		Status;		//構造体の状態

	float	JumpPower;	//ジャンプ力
	float	Gravity;	//重力
	float	MoveY;		//縦方向の移動量

	int		Color;		//表示色
	int		Life;		//ライフ

}ENEMY;

class Spike
{
public:
	Spike();
	Spike(Vec _v[3]);
	~Spike();
	TriangleCollider* TriCol;
	float MoveDistanceX;
	float MoveDistanceY;
	float MoveX_PerFrame;
	float MoveY_PerFrame;
	int MoveCount;
	bool isMoving;
	bool needclear;
	bool visible;
	bool isInited;

	void SpikeUpdate();
	void SetSpike(Vec _v[3]);
	void SetSpikeReverse(Vec _v[3]);
	void DeleteSpike();
	bool MoveSpikeTo(Vec _target, int _time);
	void MoveSpike(int _x, int _y);

	void SaveOldPos();
	void CheckMove();
	//void Transform(Vec _v[3]);
private:
	Bitmap* bmp;
	Vec tri_Vec[3];
	Vec tri_VecOld[3];
	VecPlus* Coord;
	VecPlus* CoordOld;
};

//======プロトタイプ宣言=====
//外部へ教えたい関数を書く
void	EnemyInit();
void	EnemyUpdate();
void	EnemyDraw();
void	EnemyUninit();

