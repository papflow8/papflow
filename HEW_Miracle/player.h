#pragma once

#define		CONIOEX
#include	"main.h"
#include	"field.h"
#include	"Animation.h"
#include	"InputManager.h"

//============マクロ定義=====
//============構造体定義=====
//typedef	struct
//{
//	float	PositionX;
//	float	PositionY;
//
//	float	PositionOldX;//前回のプレイヤー座標(X)
//	float	PositionOldY;//前回のプレイヤー座標(Y)
//	BOOL	MoveFlag;	//移動したか移動していないか
//
//	BOOL	UseFlag;	//構造体が初期化してあるか
//	int		Status;		//構造体の状態
//
//	float	JumpPower;	//ジャンプ力
//	float	Gravity;	//重力
//	float	MoveY;		//縦方向の移動量
//
//}PLAYER;//プレイヤー構造体定義

//typedef struct
//{
//	BOOL	MoveFlag;
//	BOOL	UseFlag;
//
//	int		Height;
//	int		Width;
//
//	float	PositionX;
//	float	PositionY;
//
//	float	PositionOldX;
//	float	PositionOldY;
//	int		Status;
//	
//	float	JumpPower;
//	float	Gravity;
//	float	MoveY;
//
//	char*	SourceImg;
//
//	int		len;
//	PLAYER	player[];
//}PLAYERMUL;

class Player
{
public:
	Player();
	Player(float _x, float _y);

	~Player();
	bool OnGround;
	bool OnCollision;
	int OnGroundId;
	int NowSaveId;
	int RowNowUp;
	int RowNowDown;
	int ColumnNowLeft;
	int ColumnNowRight;
	int RowMiddle;
	int ColumnMiddle;
	int JumpCd;

	float	PositionOldX;
	float	PositionOldY;
	int	Status;
	bool isVisible;

	float	JumpPower;
	float	Gravity;
	int gravityCount;
	int jumpCount;

	void Init();
	void SaveOldPosition();
	void UpdateIntPos();

	float getPlayerX();
	void setPlayerX(float _x);
	float getPlayerY();
	void setPlayerY(float _y);
	float getPlayerMoveX();
	float getPlayerMoveY();
	void setPlayerMoveX(float _x);
	void setPlayerMoveY(float _y);

	float getPlayerWidth();
	void setPlayerWidth(int _w);
	float getPlayerHeight();
	void setPlayerHeight(int _h);
	void PlayerMove();
	void PlayerJump();
	void CalPlayerPos();
	void CheckOnGround(Block* _ground, int _num);
	void CheckOnGroundTest(Block* _ground);
	void CheckCollisionRight(Block* _ground);
	void CheckCollisionLeft(Block* _ground);
	void CheckCollisionUp(Block* _ground);

	void CheckBorder();
	void UpdateCoord();

	void ColPositionUpdate();
	void setPlayerAni(Animation* _ani);
	void setPlayerCol(Collider* _col);
	Animation* getPlayerAni();
	Collider* getPlayerCol();
	//void Idle_Ani();
private:
	int PlayerX_int;
	int PlayerY_int;
	int PlayerXOld_int;
	int PlayerYOld_int;

	float	PlayerX;
	float	PlayerY;
	float	MoveX;
	float	MoveY;
	bool	isMoving;
	float	MoveSpeed;

	float frame_width;
	float frame_height;

	Collider* Player_Col;
	Animation* PlayerAniNow;
};

void	PlayerInit();
void	PlayerUpdate();
void	PlayerDraw();
void	PlayerUninit();
void	PlayerNormal();
//void PlayAni_OneBlock1(Animation* p);

extern Player* p_Player;

