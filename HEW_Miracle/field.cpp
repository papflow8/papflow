
#define	CONIOEX
#include "field.h"
#include "player.h"
using namespace std;


int DeathHandle;
int BGM1Handle;
int SpikeMoveSound;
int BlockMoveSound;
bool DeathSoundPlayed = false;
//Block *p_RightWall;
Bitmap* Wall;
Bitmap* GameOverBmp;
Bitmap* PortalBmp;
Bitmap* RainbowBallBmp;
Bitmap* MiracleBmp;
Bitmap* EndBmp;

Block** p_PortalArray;
SavePoint** p_SaveArray;
Block** ScreenBlock;
Block** p_RainbowBall;
Block* Miracle;
int StageNow;
bool isGameOverPlayed = false;
bool isStage1Init = false;
bool isStage2Init = false;
bool isClearEnd = false;
Image* GameOverImg;
Image* GameEndImg;

Spike* SpikeTest;
Spike** Spike_Stage1;
Spike** Spike_Stage2_1;
Spike** Spike_Stage2_2;
Spike* Spike_Stage2_3;
Spike* Spike_Stage2_4;
Collider* p_Spike_2_3;
Collider* p_Spike_2_4_1;
Collider* p_Spike_2_4_2;
Collider* p_Spike_2_4_3;
bool isCol_p_Spike_2_3 = false;
bool isCol_p_Spike_2_4_1 = false;
bool isCol_p_Spike_2_4_2 = false;
bool isCol_p_Spike_2_4_3 = false;
bool isCol_p_Spike_2_4_3_1 = false;




bool SpikeMoveTest = false;
Vec Test[3] = { {315.0f, 125.0f, true}, {305.0f, 135.0f, true }, { 325.0f, 135.0f, true } };
Vec Stage2Spike_1[3] = { {45.0f, 122.0f, true}, {32.0f, 135.0f, true},{58.0f, 135.0f, true} };
Vec Stage2Spike_2[3] = { {225.0f, 84.0f, true}, {215.0f, 76.0f, true}, {235.0f, 76.0f, true} };
Vec Stage2Spike_3[3] = { {300.0f, 102.0f, true}, {296.0f, 105.0f, true}, {304.0f, 105.0f, true} };
Vec Stage2Spike_4[4] = { {375.0f, 50.0f, true}, {365.0f, 60.0f, true}, {385.0f, 60.0f, true} };
void FieldInit(void)
{
	DeathHandle = opensound((char*)"deathsound.mp3");

	StageNow = 1;

	//init GameoverImg
	GameOverImg = new Image(70, 10, GameOverBmp);
	GameOverImg->width = 500;
	GameOverImg->height = 117;
	//init GameEndImg
	GameEndImg = new Image(70, 10, EndBmp);
	GameEndImg->width = 480;
	GameEndImg->height = 100;

	//init Spike
	Spike_Stage1 = new Spike*[3];
	Spike_Stage2_1 = new Spike*[17];
	Spike_Stage2_2 = new Spike*[5];

	InitNormalSpike(Spike_Stage1, 3, Test);
	InitNormalSpike(Spike_Stage2_1, 17, Stage2Spike_1);
	InitNormalSpike(Spike_Stage2_2, 5, Stage2Spike_2);

	SpikeTest = new Spike(Test);
	Spike_Stage2_3 = new Spike(Stage2Spike_3);
	Spike_Stage2_4 = new Spike(Stage2Spike_4);
	
	
	//init all block
	ScreenBlock = new Block*[WALL_NUM + 2];
	for (int i = 0; i < WALL_NUM + 2; i++)
	{
		ScreenBlock[i] = new Block[GROUND_NUM + 2];
	}
	CreateBlock();
	DrawBlock();
	
	//init all SavePoints
	p_SaveArray = new SavePoint*[MAX_SAVE_NUM];

	p_SaveArray[0] = new SavePoint(68.0f, 108.0f, SavePointBmp);
	p_SaveArray[0]->SaveId = 0;
	p_SaveArray[1] = new SavePoint(68.0f, 46.0f, SavePointBmp);
	p_SaveArray[1]->SaveId = 1;
	p_SaveArray[2] = new SavePoint(68.0f, 33.0f, SavePointBmp);
	p_SaveArray[2]->SaveId = 2;
	p_SaveArray[3] = new SavePoint(510.0f, 33.0f, SavePointBmp);
	p_SaveArray[3]->SaveId = 3;

	//init all portals
	p_PortalArray = new Block*[MAX_PORTAL_NUM];
	p_PortalArray[0] = new Block(PortalBmp, 20, 9);
	p_PortalArray[1] = new Block(PortalBmp, 20, 9);
	
	//init all Rainbow Balls
	p_RainbowBall = new Block*[7];
	p_RainbowBall[0] = new Block(RainbowBallBmp, 25, 15);

	//init temp Collider
	p_Spike_2_3 = new Collider(310.0f, 92.0f, 20.0f, 10.0f);
	p_Spike_2_3->UpdateCoord();
	p_Spike_2_4_1 = new Collider(240.0f, 16.0f, 10.0f, 45.0f);
	p_Spike_2_4_1->UpdateCoord();
	p_Spike_2_4_2 = new Collider(240.0f, 91.0f, 10.0f, 15.0f);
	p_Spike_2_4_2->UpdateCoord();
	p_Spike_2_4_3 = new Collider(340.0f, 46.0f, 10.0f, 15.0f);
	p_Spike_2_4_3->UpdateCoord();

	//init miracle
	Miracle = new Block(MiracleBmp, 90, 21);
}

void FieldUninit(void)
{
	//delete[]p_LeftWall;
	//delete[]p_RightWall;
	//delete[]p_Ground0;
	//delete[]p_Ground1;
	delete[] p_SaveArray;
	delete[] ScreenBlock;
	delete PortalBmp;
	delete GameOverBmp;
	delete SpikeTest;
	delete[] Spike_Stage1;
	delete[] Spike_Stage2_1;
	delete[] Spike_Stage2_2;
	delete[]p_RainbowBall;

}

void FieldUpdate(void)
{
	Collider* PlayerCol = p_Player->getPlayerCol();

	if (InputManager::OnPressed(InputManager::k_R))
	{
		Restart();
	}
	if (p_Player->Status == STS_GAMEOVER && !isGameOverPlayed)
	{
		GameOver();
		isGameOverPlayed = true;
	}
	switch (StageNow)
	{
	case STAGE_1:
		//init Stage_1
		if (!isStage1Init)
		{
			ScreenBlock[1][2].SetBlock();
			ScreenBlock[2][3].SetBlock();
			ScreenBlock[3][3].SetBlock();

			ScreenBlock[5][1].SetBlock();
			ScreenBlock[5][2].SetBlock();
			ScreenBlock[5][3].SetBlock();

			ScreenBlock[1][8].SetBlock();
			ScreenBlock[2][8].SetBlock();
			ScreenBlock[3][8].SetBlock();

			ScreenBlock[1][13].SetBlock();
			ScreenBlock[1][14].SetBlock();
			ScreenBlock[1][15].SetBlock();
			ScreenBlock[1][16].SetBlock();
			ScreenBlock[1][17].SetBlock();
			p_SaveArray[0]->DrawSavePoint();
			p_SaveArray[1]->DrawSavePoint();

			p_PortalArray[0]->SetPortal(510, 106);

			for (int i = 0; i < 3; i++)
			{
 				Spike_Stage1[i]->SetSpike(Spike_Stage1[i]->TriCol->tri_Vec);
			}
			SpikeMoveTest = false;
			isStage1Init = true;

			ScreenBlock[3][5].SetBlock();
			ScreenBlock[3][5].ClearBlock();
		}
		if (p_Player->OnGround && p_Player->RowNowDown == 4 && (p_Player->ColumnNowLeft == 5 || p_Player->ColumnNowRight == 5))
		{
			ScreenBlock[3][5].DrawBlock();
		}
		//record save ID
		if (p_SaveArray[0]->SaveCol->CheckCollision_RectRect(*PlayerCol))
		{
			p_Player->NowSaveId = p_SaveArray[0]->SaveId;
		}
		if (p_SaveArray[1]->SaveCol->CheckCollision_RectRect(*PlayerCol))
		{
			p_Player->NowSaveId = p_SaveArray[1]->SaveId;
		}

		//portal to next stage
		if (p_PortalArray[0]->getBlockCol()->CheckCollision_RectRect(*PlayerCol))
		{
			StageNow = STAGE_2;

			ScreenBlock[1][2].DeleteBlock();
			ScreenBlock[2][3].DeleteBlock();
			ScreenBlock[3][3].DeleteBlock();

			ScreenBlock[5][1].DeleteBlock();
			ScreenBlock[5][2].DeleteBlock();
			ScreenBlock[5][3].DeleteBlock();

			ScreenBlock[1][8].DeleteBlock();
			ScreenBlock[2][8].DeleteBlock();
			ScreenBlock[3][8].DeleteBlock();

			ScreenBlock[1][13].DeleteBlock();
			ScreenBlock[1][14].DeleteBlock();
			ScreenBlock[1][15].DeleteBlock();
			ScreenBlock[1][16].DeleteBlock();
			ScreenBlock[1][17].DeleteBlock();

			ScreenBlock[3][5].DeleteBlock();

			SpikeTest->DeleteSpike();
			for (int i = 0; i < 3; i++)
			{
				Spike_Stage1[i]->DeleteSpike();
			}

			p_PortalArray[0]->DeleteBlock();
			p_SaveArray[0]->DeleteSavePoint();
			p_SaveArray[1]->DeleteSavePoint();
			p_Player->NowSaveId = 2;
			Restart();
		}

		//update spike
		if (!SpikeTest->isInited)
		{
			SpikeTest->SetSpike(Test);
			SpikeTest->isMoving = false;
			SpikeMoveTest = false;
		}
		SpikeTest->SaveOldPos();
		if (p_Player->RowNowDown == 4 && p_Player->ColumnNowRight == 9)
		{
			if(!SpikeMoveTest)
				playsound(SpikeMoveSound, 0);
			SpikeMoveTest = true;
		}
		for (int i = 0; i < 3; i++)
		{
			//to do
			if (PlayerCol->CheckCollision_RectTri(Spike_Stage1[i]->TriCol))
			{
				p_Player->Status = STS_GAMEOVER;
				Spike_Stage1[i]->TriCol->DrawTriangleCol();
				isGameOverPlayed = false;
			}
		}

		if (SpikeTest->TriCol->isCollider && PlayerCol->CheckCollision_RectTri(SpikeTest->TriCol))
		{
			p_Player->Status = STS_GAMEOVER;
			SpikeTest->TriCol->ClearTriCol();
			isGameOverPlayed = false;
			SpikeMoveTest = false;
		}
		if (SpikeMoveTest)
		{
			if (SpikeTest->MoveSpikeTo({ 315.0f, 50.0f ,true }, 16))
			{
				SpikeMoveTest = false;
				SpikeTest->DeleteSpike();
			}
		}
		SpikeTest->CheckMove();
		break;
	case STAGE_2:
		//init Stage_2
		if (!isStage2Init)
		{
			ScreenBlock[6][1].SetBlock();
			ScreenBlock[6][2].SetBlock();
			ScreenBlock[6][3].SetBlock();

			ScreenBlock[6][15].SetBlock();
			ScreenBlock[6][16].SetBlock();
			ScreenBlock[6][17].SetBlock();

			ScreenBlock[5][7].SetBlock();
			ScreenBlock[5][8].SetBlock();
			ScreenBlock[5][9].SetBlock();
			ScreenBlock[5][10].SetBlock();
			ScreenBlock[5][11].SetBlock();

			ScreenBlock[4][13].SetBlock();

			ScreenBlock[2][7].SetBlock();
			ScreenBlock[2][8].SetBlock();
			ScreenBlock[2][9].SetBlock();
			ScreenBlock[2][10].SetBlock();
			ScreenBlock[2][11].SetBlock();


			Miracle->SetMiracle(480, 25);
			p_Spike_2_3->setFrameX(319.5f);

			p_SaveArray[2]->DrawSavePoint();

			p_Spike_2_3->DrawCollider();
			p_Spike_2_4_1->DrawCollider();
			p_Spike_2_4_2->DrawCollider();
			p_Spike_2_4_3->DrawCollider();

			Spike_Stage2_3->SetSpike(Stage2Spike_3);
			Spike_Stage2_4->SetSpike(Stage2Spike_4);
			Spike_Stage2_3->isMoving = false;
			Spike_Stage2_4->TriCol->VerMoving = false;
			isCol_p_Spike_2_3 = false;
			isCol_p_Spike_2_4_1 = false;
			isCol_p_Spike_2_4_2 = false;
			isCol_p_Spike_2_4_3 = false;

			isCol_p_Spike_2_4_3_1 = false;
			for (int i = 0; i < 17; i++)
			{
				Spike_Stage2_1[i]->SetSpike(Spike_Stage2_1[i]->TriCol->tri_Vec);
			}
			for (int i = 0; i < 5; i++)
			{
				Spike_Stage2_2[i]->SetSpikeReverse(Spike_Stage2_2[i]->TriCol->tri_Vec);
			}
			//p_RainbowBall[0]->SetRainbowBall(200.0f, 100.0f);
			isStage2Init = true;
		}
		//record save ID
		if (p_SaveArray[2]->SaveCol->CheckCollision_RectRect(*PlayerCol))
		{
			p_Player->NowSaveId = p_SaveArray[2]->SaveId;
		}

		//update Spike collision
		if (p_Player->RowNowDown < 3)
		{
			for (int i = 0; i < 17; i++)
			{
				//to do
				if (PlayerCol->CheckCollision_RectTri(Spike_Stage2_1[i]->TriCol))
				{
					p_Player->Status = STS_GAMEOVER;
					isGameOverPlayed = false;
				}
			}
		}
		if (p_Player->RowNowUp == 4 || p_Player->RowNowUp == 5)
		{
			for (int i = 0; i < 5; i++)
			{
				if (PlayerCol->CheckCollision_RectTriReverse(Spike_Stage2_2[i]->TriCol))
				{
					p_Player->Status = STS_GAMEOVER;
					isGameOverPlayed = false;
				}
			}
		}
		if (Spike_Stage2_3->TriCol->isCollider && PlayerCol->CheckCollision_RectTri(Spike_Stage2_3->TriCol))
		{
			p_Player->Status = STS_GAMEOVER;
			isGameOverPlayed = false;
		}
		if (PlayerCol->CheckCollision_RectTri(Spike_Stage2_4->TriCol))
		{
			p_Player->Status = STS_GAMEOVER;
			isGameOverPlayed = false;
		}

		//Move Spike_Stage2_3 if Collision
		if (PlayerCol->CheckCollision_RectRect(*p_Spike_2_3) && !isCol_p_Spike_2_3)
		{
			isCol_p_Spike_2_3 = true;
			playsound(SpikeMoveSound, 0);
		}
		if (isCol_p_Spike_2_3)
		{
			if (Spike_Stage2_3->MoveSpikeTo({340.0f, 102.0f, true}, 10))
			{
				p_Spike_2_3->setFrameX(0);
				Spike_Stage2_3->isMoving = false;
				Spike_Stage2_3->TriCol->isCollider = false;
				isCol_p_Spike_2_3 = false;
				Spike_Stage2_3->DeleteSpike();
			}
		}
		Spike_Stage2_3->CheckMove();
		//Move Spike_Stage2_4 Vertex if collision(6,7)
		if (PlayerCol->CheckCollision_RectRect(*p_Spike_2_4_1) && !isCol_p_Spike_2_4_1)
		{
			isCol_p_Spike_2_4_1 = true;
			playsound(SpikeMoveSound, 0);
		}
		if (isCol_p_Spike_2_4_1)
		{
			if (Spike_Stage2_4->TriCol->MoveVertex({ 375.0f, 16.0f, true }, 20, 0))
			{
				Spike_Stage2_4->TriCol->VerMoving = false;
				isCol_p_Spike_2_4_2 = false;
			}
		}
		if (PlayerCol->CheckCollision_RectRect(*p_Spike_2_4_2) && !isCol_p_Spike_2_4_2)
		{
			isCol_p_Spike_2_4_2 = true;
			playsound(SpikeMoveSound, 0);
		}
		if (isCol_p_Spike_2_4_2)
		{
			if (Spike_Stage2_4->TriCol->MoveVertex({ 375.0f, 61.0f, true }, 20, 0))
			{
				Spike_Stage2_4->TriCol->VerMoving = false;
				isCol_p_Spike_2_4_1 = false;
			}
		}

		//Rotate
		if (PlayerCol->CheckCollision_RectRect(*p_Spike_2_4_3) && !isCol_p_Spike_2_4_3)
		{
			isCol_p_Spike_2_4_3 = true;
			playsound(SpikeMoveSound, 0);
		}
		if (isCol_p_Spike_2_4_3 && !isCol_p_Spike_2_4_3_1)
		{
			int count = 64;
			for (int i = 0; i < Spike_Stage2_4->TriCol->count; i++)
			{
				Spike_Stage2_4->TriCol->Coord[i].needDraw = true;
			}
			for (int i = 0; i < Spike_Stage2_4->TriCol->countOld; i++)
			{
				Spike_Stage2_4->TriCol->CoordOld[i].needDraw = true;
			}
			while (count-- > 0)
			{
				Spike_Stage2_4->TriCol->RotateTriCol({ 375.0f, 60.0f, true }, 3.1415926 / 32);
				Spike_Stage2_4->TriCol->setNeedClear(true);
				Spike_Stage2_4->TriCol->DrawTriangleCol();
			}
			p_Player->Status = STS_GAMEOVER;
			isGameOverPlayed = false;
			isCol_p_Spike_2_4_3_1 = true;
		}

		//miracle col
		if (PlayerCol->CheckCollision_RectRect(*Miracle->getBlockCol()))
		{
			playsound(BlockMoveSound, 0);
			Miracle->ClearMiracle();

			ScreenBlock[6][1].DeleteBlock();
			ScreenBlock[6][2].DeleteBlock();
			ScreenBlock[6][3].DeleteBlock();
			ScreenBlock[6][15].DeleteBlock();
			ScreenBlock[6][16].DeleteBlock();
			ScreenBlock[6][17].DeleteBlock();
			ScreenBlock[5][7].DeleteBlock();
			ScreenBlock[5][8].DeleteBlock();
			ScreenBlock[5][9].DeleteBlock();
			ScreenBlock[5][10].DeleteBlock();
			ScreenBlock[5][11].DeleteBlock();
			ScreenBlock[4][13].DeleteBlock();
			ScreenBlock[2][7].DeleteBlock();
			ScreenBlock[2][8].DeleteBlock();
			ScreenBlock[2][9].DeleteBlock();
			ScreenBlock[2][10].DeleteBlock();
			ScreenBlock[2][11].DeleteBlock();

			ScreenBlock[6][1].isCollider = true;
			ScreenBlock[6][2].isCollider = true;
			ScreenBlock[6][3].isCollider = true;
			ScreenBlock[6][15].isCollider = true;
			ScreenBlock[6][16].isCollider = true;
			ScreenBlock[6][17].isCollider = true;
			ScreenBlock[5][7].isCollider = true;
			ScreenBlock[5][8].isCollider = true;
			ScreenBlock[5][9].isCollider = true;
			ScreenBlock[5][10].isCollider = true;
			ScreenBlock[5][11].isCollider = true;
			ScreenBlock[4][13].isCollider = true;
			ScreenBlock[2][7].isCollider = true;
			ScreenBlock[2][8].isCollider = true;
			ScreenBlock[2][9].isCollider = true;
			ScreenBlock[2][10].isCollider = true;
			ScreenBlock[2][11].isCollider = true;
			Spike_Stage2_3->TriCol->isCollider = true;
			Spike_Stage2_4->TriCol->isCollider = true;
			isCol_p_Spike_2_4_1 = true;


			p_SaveArray[2]->DeleteSavePoint();
			p_SaveArray[3]->DrawSavePoint();


			for (int i = 0; i < 17; i++)
			{
				Spike_Stage2_1[i]->DeleteSpike();
				Spike_Stage2_1[i]->TriCol->isCollider = true;
			}
			for (int i = 0; i < 5; i++)
			{
				Spike_Stage2_2[i]->DeleteSpike();
				Spike_Stage2_2[i]->TriCol->isCollider = true;
			}
			StageNow = STAGE_3;

			Miracle->SetMiracle(62, 25);
		}

		////portal to next stage
		//if (p_PortalArray[1]->getBlockCol()->CheckCollision_RectRect(*PlayerCol))
		//{
		//	
		//}
		break;
	case STAGE_3:
		//check Miracle
		if (PlayerCol->CheckCollision_RectRect(*Miracle->getBlockCol()))
		{
			p_Player->Status = STS_WIN;
		}

		//check spike collision
		if (p_Player->RowNowDown < 3)
		{
			for (int i = 0; i < 17; i++)
			{
				//to do
				if (PlayerCol->CheckCollision_RectTri(Spike_Stage2_1[i]->TriCol))
				{
					p_Player->Status = STS_GAMEOVER;
					isGameOverPlayed = false;
				}
			}
		}
		if (p_Player->RowNowUp == 4 || p_Player->RowNowUp == 5)
		{
			for (int i = 0; i < 5; i++)
			{
				if (PlayerCol->CheckCollision_RectTriReverse(Spike_Stage2_2[i]->TriCol))
				{
					p_Player->Status = STS_GAMEOVER;
					isGameOverPlayed = false;
				}
			}
		}
		if (Spike_Stage2_3->TriCol->isCollider && PlayerCol->CheckCollision_RectTri(Spike_Stage2_3->TriCol))
		{
			p_Player->Status = STS_GAMEOVER;
			isGameOverPlayed = false;
		}
		if (PlayerCol->CheckCollision_RectTri(Spike_Stage2_4->TriCol))
		{
			p_Player->Status = STS_GAMEOVER;
			isGameOverPlayed = false;
		}

		//Move Spike_Stage2_4 Vertex if collision(6,7)
		if (PlayerCol->CheckCollision_RectRect(*p_Spike_2_4_1) && !isCol_p_Spike_2_4_1)
		{
			isCol_p_Spike_2_4_1 = true;
			playsound(SpikeMoveSound, 0);
		}
		if (isCol_p_Spike_2_4_1)
		{
			if (Spike_Stage2_4->TriCol->MoveVertex({ 375.0f, 16.0f, true }, 20, 0))
			{
				Spike_Stage2_4->TriCol->VerMoving = false;
				isCol_p_Spike_2_4_1 = false;
			}
		}
		if (PlayerCol->CheckCollision_RectRect(*p_Spike_2_4_2) && !isCol_p_Spike_2_4_2)
		{
			isCol_p_Spike_2_4_2 = true;
			playsound(SpikeMoveSound, 0);
		}
		if (isCol_p_Spike_2_4_2)
		{
			if (Spike_Stage2_4->TriCol->MoveVertex({ 375.0f, 61.0f, true }, 20, 0))
			{
				Spike_Stage2_4->TriCol->VerMoving = false;
				isCol_p_Spike_2_4_2 = false;
			}
		}

		//record save ID
		p_Player->NowSaveId = p_SaveArray[3]->SaveId;
		break;

	}
}

void FieldDraw(void)
{
	switch (StageNow)
	{
	case STAGE_1:
		p_SaveArray[0]->DrawSavePointOnCol();
		p_SaveArray[1]->DrawSavePointOnCol();

		if (SpikeTest->isMoving)
		{
			SpikeTest->TriCol->DrawTriangleCol();
		}
		
		break;
	case STAGE_2:
		p_SaveArray[2]->DrawSavePointOnCol();
		/*if (Spike_Stage2_3->isMoving)
		{
			Spike_Stage2_3->TriCol->DrawTriangleCol();
		}*/
		if (Spike_Stage2_3->isMoving)
		{
			Spike_Stage2_3->TriCol->DrawTriangleCol();
		}
		if (Spike_Stage2_4->TriCol->VerMoving)
		{
			Spike_Stage2_4->TriCol->DrawTriangleCol();
		}
	case STAGE_3:
		p_SaveArray[3]->DrawSavePointOnCol();

		//if End clear whole screen
		if (p_Player->Status == STS_WIN && !isClearEnd)
		{
			isClearEnd = true;
			ClearEnd();
		}
		break;
	}
	
}

Block::Block() : Block_Width(30), Block_Height(15), Block_bmp(Wall)
{
	visible = true;
	isCollider = false;
	Block_Col = new Collider();
	Block_Col->setFrameWidth(Block_Width);
	Block_Col->setFrameHeight(Block_Height);
}

Block::Block(Bitmap *_bmp, int _width, int _height) : Block_Width(_width), Block_Height(_height)
{
	Block_bmp = _bmp;

	Block_Col = new Collider();
	Block_Col->setFrameWidth(Block_Width);
	Block_Col->setFrameHeight(Block_Height);
}

Block::Block(int _x, int _y) : Block_Width(30), Block_Height(15), Block_bmp(Wall)
{
	Block_Col = new Collider();
	Block_Col->setFrameX(_x);
	Block_Col->setFrameY(_y);
	Block_Col->setFrameWidth(Block_Width);
	Block_Col->setFrameHeight(Block_Height);
}

Block::~Block()
{
	delete Block_bmp;
	delete Block_Col;
	delete[] Coord;
	delete[] CoordOld;
}

int Block::getX()
{
	return Block_x;
}

void Block::setX(int _x)
{
	Block_x = _x;
}

int Block::getY()
{
	return Block_y;
}

void Block::setY(int _y)
{
	Block_y = _y;
}

Collider * Block::getBlockCol()
{
	return Block_Col;
}

int Block::getWidth() const
{
	if (this != NULL)
	{
		return Block_Width;
	}
	return NULL;
}

int Block::getHeight() const
{
	if (this != NULL)
	{
		return Block_Height;
	}
	return NULL;
}

void Block::InitMiracleCoord()
{
	count = 0;
	countold = 0;
	Coord = new Vec[Block_Height * Block_Width];
	CoordOld = new Vec[Block_Height * Block_Width];

	for (int dy = 0; dy < Block_Height; dy++)
	{
		for (int dx = 0; dx < Block_Width; dx++)
		{
			switch (Block_bmp->data[dy][dx])
			{
			case 'T':
				continue;
			case '0':
				Coord[count].x = Block_x + dx;
				Coord[count].needDraw = true;
				Coord[count++].y = Block_y + dy;
			}
		}
	}

	for (int i = 0; i < count; i++)
	{
		CoordOld[i] = Coord[i];
	}
}

void Block::UpdateMiracleCoord()
{
	for (int dy = 0; dy < Block_Height; dy++)
	{
		for (int dx = 0; dx < Block_Width; dx++)
		{
			switch (Block_bmp->data[dy][dx])
			{
			case 'T':
				continue;
			case '0':
				Coord[count].x = Block_x + dx;
				Coord[count].needDraw = true;
				Coord[count++].y = Block_y + dy;
			}
		}
	}

	/*for (int i = 0; i < countold; i++)
	{
		CoordOld[i].x = Coord[i].x;
		CoordOld[i].y = Coord[i].y;
	}

	for (int j = 0; j < countold; j++)
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
	}*/
}

void Block::SetBlock()
{
	visible = true;
	isCollider = true;
	Block_Col->setNeedDraw(true);
	DrawBlock();
}

void Block::SetMiracle(int _x, int _y)
{
	visible = true;
	isCollider = true;
	Block_Col->StartX = _x;
	Block_Col->StartY = _y;
	Block_Col->setFrameX(_x + (90-1) / 2);
	Block_Col->setFrameY(_y + (21-1) / 2);
	Block_x = _x;
	Block_y = _y;
	InitMiracleCoord();
	Block_Col->InitCoord();
	DrawMiracle();
	
}

void Block::ClearMiracle()
{
	for (int i = 0; i < count; i++)
	{
		gotoxy(Coord[i].x, Coord[i].y);
		printf(" ");
	}
}

void Block::SetPortal(int _x, int _y)
{
	visible = true;
	isCollider = true;
	Block_Col = new Collider(_x, _y, 20, 9);
	Block_Col->setFrameX(_x + (20-1)/2);
	Block_Col->setFrameY(_y + (9-1)/2);
	Block_x = _x;
	Block_y = _y;
	Block_Col->InitCoord();
	DrawPortal();
}

void Block::SetRainbowBall(int _x, int _y)
{
	visible = true;
	isCollider = true;
	Block_Col->setFrameX(_x);
	Block_Col->setFrameY(_y);
	Block_x = _x;
	Block_y = _y;
	DrawRainbowBall();
}

void Block::DeleteBlock()
{
	visible = false;
	isCollider = false;
	ClearBlock();
}

void Block::DrawBlock()
{
	if (visible)
	{
		gotoxy(Block_x, Block_y);
		for (int dy = 0, i = 1; dy < Block_Height; dy++, i++)
		{
			for (int dx = 0; dx < Block_Width; dx++)
			{
				if (Block_bmp->data[dy][dx] == '1')
				{
					textcolor(BROWN);
					printf("█");
				}
				else
				{
					textcolor(GREEN);
					printf("▓");
				}
			}
			gotoxy(Block_x, Block_y + i);
		}
	}
	
	if (isCollider)
	{
		Block_Col->DrawCollider();
	}
}

void Block::DrawPortal()
{
	if (visible)
	{
		gotoxy(Block_x, Block_y);
		for (int dy = 0, i = 1; dy < Block_Height; dy++, i++)
		{
			for (int dx = 0; dx < Block_Width; dx++)
			{
				switch (Block_bmp->data[dy][dx])
				{
				case 'T':
					printf(" "); break;
				case '0':
					textcolor(DARKGRAY);
					printf("█"); break;
				case '1':
					textcolor(WHITE);
					printf("▓"); break;
				case '2':
					textcolor(LIGHTGRAY);
					printf("█"); break;
				}
			}
			gotoxy(Block_x, Block_y + i);
		}
	}

	if (isCollider)
	{
		Block_Col->DrawCollider();
	}
}

void Block::DrawMiracle()
{
	textcolor(WHITE);

	/*for (int i = 0; i < countold; i++)
	{
		if (CoordOld[i].needDraw)
		{
			gotoxy(CoordOld[i].x, CoordOld[i].y);
			printf(" ");
		}
	}*/

	if (visible)
	{
		for (int i = 0; i < count; i++)
		{
			if (Coord[i].needDraw)
			{
				gotoxy(Coord[i].x, Coord[i].y);
				printf("█");
			}
		}
	}
	if (isCollider)
	{
		Block_Col->DrawCollider();
	}
}

void Block::DrawRainbowBall()
{
	textcolor(RED);
	if (visible)
	{
		gotoxy(Block_x, Block_y);
		for (int dy = 0, i = 1; dy < Block_Height; dy++, i++)
		{
			for (int dx = 0; dx < Block_Width; dx++)
			{
				printf("%c", Block_bmp->data[dy][dx]);
			}
			gotoxy(Block_x, Block_y + i);
		}
	}
	if (isCollider)
	{
		Block_Col->DrawCollider();
	}
}

void Block::ClearBlock()
{
	gotoxy(Block_x, Block_y);
	for (int dy = 0, i = 1; dy < Block_Height; dy++, i++)
	{
		for (int dx = 0; dx < Block_Width; dx++)
		{
			printf(" ");
		}
		gotoxy(Block_x, Block_y + i);
	}
}

void CreateBlock(float _x, float _y, int _num, int _column, Block* &_p)
{
	Block* temp_Block = new Block();

	float _BlockWidth = temp_Block->getWidth();
	float _BlockHeight = temp_Block->getHeight();

	_p = new Block[_num];
	for (int i = 0; i < _num; i++)
	{
		_p[i].setX(_x + (i % _column) *_BlockWidth);
		_p[i].setY(_y + (i / _column) *_BlockHeight);
		_p[i].row = (DOWN_BLOCK_Y - _p[i].getY() - TILE_HEIGHT) / TILE_HEIGHT;
		_p[i].column = (_p[i].getX() - LEFT_BLOCK_X - TILE_WIDTH) / TILE_WIDTH;
		_p[i].getBlockCol()->StartX = (_x + (i % _column) *_BlockWidth);
		_p[i].getBlockCol()->StartY = (_y + (i / _column) *_BlockHeight);

		_p[i].getBlockCol()->setFrameX(_x + (i % _column) *_BlockWidth + _BlockWidth / 2);
		_p[i].getBlockCol()->setFrameY(_y + (i / _column) *_BlockHeight + _BlockHeight / 2);

		_p[i].getBlockCol()->InitCoord();
	}
}

void CreateBlock()
{
	for (int y = 0; y < WALL_NUM + 2; y++)
	{
		for (int x = 0; x < GROUND_NUM + 2; x++)
		{
			ScreenBlock[y][x].row = y;
			ScreenBlock[y][x].column = x;
			ScreenBlock[y][x].setX(LEFT_BLOCK_X + x * TILE_WIDTH);
			ScreenBlock[y][x].setY(DOWN_BLOCK_Y - y * TILE_HEIGHT);
			
			Collider* _c = ScreenBlock[y][x].getBlockCol();

			_c->StartX = (LEFT_BLOCK_X + x * TILE_WIDTH);
			_c->StartY = (DOWN_BLOCK_Y - y * TILE_HEIGHT);

			_c->setFrameX(_c->StartX + (float)(TILE_WIDTH - 1) / 2);
			_c->setFrameY(_c->StartY + (float)(TILE_HEIGHT - 1) / 2);
			_c->setFrameOldX(_c->StartX + (float)(TILE_WIDTH - 1) / 2);
			_c->setFrameOldY(_c->StartY + (float)(TILE_HEIGHT - 1) / 2);
			
			_c->InitCoord();

			if (y == 0 || y == (WALL_NUM + 1) || x == 0 || x == (GROUND_NUM + 1))
			{
				ScreenBlock[y][x].visible = true;
				ScreenBlock[y][x].isCollider = true;
			}
			else
			{
				ScreenBlock[y][x].visible = false;
				ScreenBlock[y][x].isCollider = false;
			}
		}
	}
}

void DrawBlockMul(Block* &_p, int _num)
{
	for (int i = 0; i < _num; i++)
	{
		_p[i].DrawBlock();
	}
}

void DrawBlock()
{
	for (int y = 0; y < WALL_NUM + 2; y++)
	{
		for (int x = 0; x < GROUND_NUM + 2; x++)
		{
			ScreenBlock[y][x].DrawBlock();
		}
	}
}

void InitNormalSpike(Spike** _s, int _num, Vec _v[3])
{
	Vec** tempVec;
	tempVec = new Vec*[_num];
	for (int i = 0; i < _num; i++)
	{
		tempVec[i] = new Vec[3];
	}
	for (int i = 0; i < _num; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			tempVec[i][k] = _v[k];
			tempVec[i][k].x += 30 * (i + 1);
		}
		_s[i] = new Spike(tempVec[i]);
	}
	delete[] tempVec;
}

void Restart()
{
	stopsound(DeathHandle);
	playsound(BGM1Handle, 1);
	DeathSoundPlayed = false;

	Collider* _PCol = p_Player->getPlayerCol();
	
	if (p_Player->Status == STS_GAMEOVER)
	{
	
		p_Player->Status = STS_IDLE;
		GameOverImg->clearImage();
	}

	for (int i = 0; i < _PCol->countOld; i++)
	{
		gotoxy((int)_PCol->CoordOld[i].x, (int)_PCol->CoordOld[i].y);
		printf(" ");
	}
	for (int i = 0; i < _PCol->count; i++)
	{
		gotoxy((int)_PCol->Coord[i].x, (int)_PCol->Coord[i].y);
		printf(" ");
	}

	p_Player->setPlayerX(p_SaveArray[p_Player->NowSaveId]->x);
	p_Player->setPlayerY(p_SaveArray[p_Player->NowSaveId]->y);
	p_Player->ColPositionUpdate();
	p_Player->getPlayerCol()->UpdateCoord();
	p_Player->isVisible = true;

	

	switch (p_Player->NowSaveId)
	{
	case 0:
		isStage1Init = false;
		SpikeTest->isInited = false;
		//clear hint1
		for (int y = 152; y < 161; y++)
		{
			for (int x = 70; x < 292; x++)
			{
				gotoxy(x, y);
				printf(" ");
			}
		}
		break;
	case 1:
		isStage1Init = false; 
		SpikeTest->isInited = false;
		//clear hint1
		for (int y = 152; y < 161; y++)
		{
			for (int x = 70; x < 292; x++)
			{
				gotoxy(x, y);
				printf(" ");
			}
		}
		break;
	case 2:
		isStage2Init = false;

	default:break;
	}
	return;
	
}

void GameOver()
{
	if (!DeathSoundPlayed)
	{
		stopsound(BGM1Handle);
		playsound(DeathHandle, 0);
		DeathSoundPlayed = true;
	}
	Collider* _PCol = p_Player->getPlayerCol();
	
	/*if (p_Player->Status == STS_GAMEOVER)
	{
		return;
	}*/
	
	
	/*for (int i = 0; i < _PCol->count; i++)
	{
		gotoxy((int)_PCol->Coord[i].x, (int)_PCol->Coord[i].y);
		printf(" ");
	}*/
	if (_PCol->visible)
	{
		for (int i = 0; i < _PCol->countOld; i++)
		{
			gotoxy((int)_PCol->CoordOld[i].x, (int)_PCol->CoordOld[i].y);
			printf(" ");
		}
		for (int i = 0; i < _PCol->count; i++)
		{
			gotoxy((int)_PCol->Coord[i].x, (int)_PCol->Coord[i].y);
			printf(" ");
		}
	}
	p_Player->isVisible = false;
	_PCol->visible = false;
	
	textcolor(WHITE);
	GameOverImg->showImage();
	//p_Player->isVisible = false;
}

void ClearEnd()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (ScreenBlock[i][j].visible)
			{
				ScreenBlock[i][j].DeleteBlock();
			}
		}
	}
	p_SaveArray[3]->DeleteSavePoint();

	GameEndImg->showImage();
}
