#pragma once
//****************
//main.h
//ゲーム全体で共有した設定などを
//ここへ定義する
//****************
#include	"conioex.h"//描画拡張機能
#include	<time.h>	//時間取得
#include	<math.h>	//数学系
#include	<cstdlib>
#include	<cmath>
#include	<locale.h>
#include	<vector>
//#include	"player.h"
//#include	"Collider.h"
//#include	"Bitmap.h"
//#include	"InputManager.h"


//=====画面座標限界=====
#define	LIMIT_UP	(1)
#define	LIMIT_DOWN	(30)
#define	LIMIT_LEFT	(1)
#define	LIMIT_RIGHT	(119)
#define TILE_WIDTH (30)
#define TILE_HEIGHT (15)
//ヘッダーファイル作成の注意点
//
//	※変数の宣言や初期化は記述しないこと
//
//	int		a;
//	int		b = 100;
//	PLAYER	mario;
//
//	※下記は記述してもよい
//  #include  ～
//	#define  ～
//	
//	typedef  struct
//  {
//     int a;
//  }PLAYER;
//
typedef struct { float x, y; bool needDraw; } Vec;
typedef struct { float x, y; bool needDraw; char content; } VecPlus;

enum Player_Status//行動に番号を割り振る(列挙体)
{
	STS_IDLE = 0,
	STS_WALK,
	STS_JUMP,
	STS_GAMEOVER,
	STS_WIN,
	STS_NUM,//この値を見ると何個の定義があるのか確認出来る
};
enum Stage
{
	STAGE_1 = 1,
	STAGE_2,
	STAGE_3,
};

extern int BGM1Handle;
extern int SpikeMoveSound;
extern int JumpSound;
extern int BlockMoveSound;