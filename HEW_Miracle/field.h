#pragma once
#define	CONIOEX

#define DOWN_BLOCK_Y (136)
#define UP_BLOCK_Y (0)
#define LEFT_BLOCK_X (30)
#define RIGHT_BLOCK_X (570)
#define GROUND_NUM (17)
#define WALL_NUM (8)
#define MAX_SAVE_NUM (10)
#define MAX_PORTAL_NUM (10)

#include "main.h"
#include "SavePoint.h"
#include "Sprite.h"
#include "enemy.h"

class Block
{
public:
	Block();
	Block(Bitmap *_bmp, int _width, int _height);
	Block(int _x, int _y);

	~Block();

	int row;
	int column;
	bool visible;
	bool isCollider;

	int getX();
	void setX(int _x);
	int getY();
	void setY(int _y);

	int count;
	int countold;
	Vec* Coord;
	Vec* CoordOld;

	Collider* getBlockCol();

	int getWidth() const;
	int getHeight() const;

	void InitMiracleCoord();
	void UpdateMiracleCoord();

	void SetBlock();
	void SetMiracle(int _x, int _y);
	void ClearMiracle();
	void SetPortal(int _x, int _y);
	void SetRainbowBall(int _x, int _y);
	void DeleteBlock();
	void DrawBlock();
	void DrawPortal();
	void DrawMiracle();
	void DrawRainbowBall();
	void ClearBlock();
private:
	Bitmap* Block_bmp;
	Collider* Block_Col;

	int Block_x;
	int Block_y;
	const int Block_Width;
	const int Block_Height;
};


void FieldInit(void);
void FieldUninit(void);
void FieldUpdate(void);
void FieldDraw(void);
void CreateBlock(float _x, float _y, int _num, int _column, Block* &_p);
void CreateBlock();
void DrawBlockMul(Block* &_p, int _num);
void DrawBlock();
void InitNormalSpike(Spike** _s, int _num, Vec _v[3]);
void Restart();
void GameOver();
void ClearEnd();

//extern Block *p_Ground0;
//extern Block *p_Ground1;
//extern Block *p_LeftWall;
extern SavePoint** p_SaveArray;
extern Block** ScreenBlock;
extern int StageNow;
extern Block** p_PortalArray;
