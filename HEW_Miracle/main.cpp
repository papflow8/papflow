//=============================================================================
//
// アクションゲームサンプル [main.cpp]
// 
//
//=============================================================================
//#include <stdio.h>
//#include <windows.h>
//#include "conioex.h"

#include "main.h"
#include "player.h"//プレイヤーのことを教える
#include "field.h"//フィールド処理
#include "enemy.h"//敵の処理
#include "Animation.h"
#include "InputManager.h"
#include <iostream>
#include <stdexcept>



//*****************************************************************************
// マクロ定義
//*****************************************************************************
Bitmap* TitleAniBmp;
bool ifStart = false;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
#ifdef _DEBUG
void DispFPS(void);
#endif
void	SoundInit();
void	SoundUpdate();
void	Init();		//初期化
void	Update();	//更新処理
void	Draw();		//表示
void	Uninit();	//終了
void	StartMenu();

//*****************************************************************************
// グローバル変数
//*****************************************************************************
int g_nCountFPS;				// FPSカウンタ

//=============================================================================
// メイン関数
//=============================================================================
int main(void)
{
	int nExecLastTime;
	int nFPSLastTime;
	int nCurrentTime;
	int nFrameCount;

	// 分解能を設定
	timeBeginPeriod(1);

	nExecLastTime = 
	nFPSLastTime = timeGetTime();
	nCurrentTime =
	nFrameCount = 0;

	SoundInit();
	StartMenu();

	Init();		//一度だけ行う初期化


	// ゲームメイン処理
	do
	{
		nCurrentTime = timeGetTime();
		if((nCurrentTime - nFPSLastTime) >= 500)	// 0.5秒ごとに実行
		{
			g_nCountFPS = nFrameCount * 1000 / (nCurrentTime - nFPSLastTime);
			nFPSLastTime = nCurrentTime;
			nFrameCount = 0;
		}

		if((nCurrentTime - nExecLastTime) >= (1000 / 60))
		{
			nExecLastTime = nCurrentTime;
			// FPS表示
			#ifdef _DEBUG	
			DispFPS();		//現在のフレームレートの表示
			#endif

		//===============ゲームの処理の呼び出し元
			
			Update();		//更新処理
			Draw();			//表示処理
		
		//===============

			nFrameCount++;
		}
	} while(!inport(PK_ESC));

	Uninit();				//一回だけ終了処理

	// 分解能を戻す
	timeEndPeriod(1);

	return 0;
}

//=================
//初期化
//=================	
void SoundInit()
{
	BGM1Handle = opensound((char*)"background.mp3");
	SpikeMoveSound = opensound((char*)"SpikeMove.wav");
	JumpSound = opensound((char*)"Jump.wav");
	BlockMoveSound = opensound((char*)"BlockMove.wav");
}
void SoundUpdate()
{
	
	
}

void	Init()
{
	//カーソル無しに変更する
	setcursortype(NOCURSOR);
	setlocale(LC_ALL, "ja_JP.UTF-8");
	//乱数初期化
	srand((unsigned int)time(NULL));
	
	playsound(BGM1Handle, 1);

	BitmapInit();
	FieldInit();
	AnimationInit();

	PlayerInit();//プレイヤーの初期化
	EnemyInit();//敵の初期化

	/*Vec T[3] = { { 305.0f, 134.0f, true }, { 325.0f, 134.0f, true }, {315.0f, 125.0f, true} };
	Spike* s = new Spike(T);*/
	InputInit();
	
}
//=================
//更新
//=================	
void	Update()
{
	SoundUpdate();
	FieldUpdate();
	PlayerUpdate();//プレイヤーの更新
	EnemyUpdate();//敵の更新
	AnimationUpdate();
	InputUpdate();
}
//=================
//表示
//=================
void	Draw()
{
	PlayerDraw();//プレイヤーの表示
	EnemyDraw();//	敵の表示
	FieldDraw();
	AnimationDraw();
	//InputDraw_test();
}

//=================
//終了
//=================	
void	Uninit()
{
	PlayerUninit();//プレイヤーの終了
	EnemyUninit();//敵の終了
	FieldUninit();
	AnimationUninit();
}

void StartMenu()
{
	if(ifStart) return;
	TitleAniBmp = Bitmap::getBitmap("../HEW_Miracle/ASCII-Title_ani.txt");
	Animation* _titleAni = new Animation(new AnimationData("Kid_Idle", "../HEW_Miracle/ASCII-Kid_Idle_Animation.txt", 2, 1, 2, 100), TitleAniBmp);
	_titleAni->UpdateCoordTitle();
	/*_titleAni->updateAnimationFrameTitle();
	_titleAni->DrawTitleAni();*/
	while (!ifStart)
	{
		if (inport(PK_ENTER) || inport(PK_SP))
		{
			ifStart = true;
			break;
		}
		
	}
	_titleAni->ClearTitle();
}

#ifdef _DEBUG
//=============================================================================
// FPS表示
//=============================================================================
void DispFPS(void)
{
	gotoxy(1,1);

	printf("FPS:%d", g_nCountFPS);
}
#endif




