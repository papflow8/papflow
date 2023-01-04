//==========================
//	player.cpp
//==========================

#define	CONIOEX
#include	"player.h"

//======マクロ定義など
//Block* p_Ground0;
//Block* p_Ground1;
//Block* p_LeftWall;
Player* p_Player = new Player(68.0f, 108.0f);
Bitmap* Hint1Bmp;
int JumpSound;

//Animation* Player::Kid_Idle;
#define PLAYER_MOVE_SPEED (3.0f)
#define PLAYER_JUMP_POWER (0.250f)
#define PLAYER_JUMP_POWER_LIT (0.125f)
#define GRAVITY_PERSEC (0.125f)

/*
#define		STS_NORMAL  (0)
#define		STS_JUMP	(1)
*/



//グローバル変数
//PLAYER		mario;//プレイヤー構造体変数
//PLAYERMUL	player;

//プロトタイプ宣言　内部関数 自分だけが使う
void	PlayerNormal();//移動処理



//====================
//初期化
//====================
void	PlayerInit()
{
	p_Player->Init();
	//Sprite* p_Player = new Sprite();

	//mario.PositionX = 5.0f;
	//mario.PositionY = 15.0f;
	//mario.PositionOldX = mario.PositionX;
	//mario.PositionOldY = mario.PositionY;
	//mario.MoveFlag = false;

	//mario.Status = STS_NORMAL;

	//mario.JumpPower = -1.0f;//<<<<<<<<<<<<<<値調整
	//mario.Gravity = 15.0f;  //<<<<<<<<<<<値調整
	//mario.MoveY = 0.0f;


	//mario.UseFlag = TRUE;//初期化完了

	/*player.PositionX = 5.0f;
	player.PositionY = 15.0f;

	player.PositionOldX = player.PositionX;
	player.PositionOldY = player.PositionY;
	player.MoveFlag = false;

	player.Status = STS_NORMAL;

	player.JumpPower = -1.0f;
	player.Gravity = 15.0f;
	player.MoveY = 0.0f;*/

}
//====================
//更新
//====================
void	PlayerUpdate()
{
	if (p_Player->Status == STS_GAMEOVER)
	{
		return;
	}
	


	p_Player->SaveOldPosition();

	Collider* PlayerCol = p_Player->getPlayerCol();
	float _PlayerX = p_Player->getPlayerX();
	float _PlayerY = p_Player->getPlayerY();
	float _PlayerWidth = p_Player->getPlayerWidth();
	float _PlayerHeight = p_Player->getPlayerHeight();

	p_Player->RowNowUp = (DOWN_BLOCK_Y + TILE_HEIGHT - PlayerCol->StartY) / TILE_HEIGHT;
	p_Player->RowNowDown = ((DOWN_BLOCK_Y + TILE_HEIGHT - PlayerCol->StartY - (PlayerCol->getFrameHeight() - 1) - 1) / TILE_HEIGHT);
	p_Player->ColumnNowLeft = (PlayerCol->StartX - LEFT_BLOCK_X) / TILE_WIDTH;
	p_Player->ColumnNowRight = (PlayerCol->StartX - LEFT_BLOCK_X + PlayerCol->getFrameWidth() - 1) / TILE_WIDTH;

	switch (StageNow)
	{
	case 1:
		if (p_Player->RowNowDown == 1 && p_Player->ColumnNowLeft > 2 && p_Player->ColumnNowLeft < 8)
		{
			Image* Hint1Img = new Image(70, 152, Hint1Bmp);
			Hint1Img->width = 140;
			Hint1Img->height = 8;
			textcolor(WHITE);
			Hint1Img->showImage();
		}
			break;
	}

	/*textcolor(LIGHTCYAN);
	gotoxy(200, 50);
	printf("RowUp:%d", p_Player->RowNowUp);
	gotoxy(200, 55);
	printf("RowDown:%d", p_Player->RowNowDown);
	gotoxy(200, 60);
	printf("ColumnLeft:%d", p_Player->ColumnNowLeft);
	gotoxy(200, 65);
	printf("ColumnRight:%d", p_Player->ColumnNowRight);*/



	p_Player->PlayerMove();
	p_Player->PlayerJump();
	p_Player->CalPlayerPos();


	p_Player->CheckBorder();
	//check up
	if (p_Player->ColumnNowLeft != p_Player->ColumnNowRight)
	{
		p_Player->CheckCollisionUp(&ScreenBlock[p_Player->RowNowDown + 1][p_Player->ColumnNowLeft]);
	}
	p_Player->CheckCollisionUp(&ScreenBlock[p_Player->RowNowDown + 1][p_Player->ColumnNowRight]);
	//check down
	if (p_Player->ColumnNowLeft != p_Player->ColumnNowRight)
	{
		p_Player->CheckOnGroundTest(&ScreenBlock[p_Player->RowNowDown - 1][p_Player->ColumnNowLeft]);
	}
	p_Player->CheckOnGroundTest(&ScreenBlock[p_Player->RowNowDown - 1][p_Player->ColumnNowRight]);

	if (!ScreenBlock[p_Player->RowNowDown - 1][p_Player->ColumnNowLeft].isCollider && !ScreenBlock[p_Player->RowNowDown - 1][p_Player->ColumnNowRight].isCollider)
	{
		p_Player->OnGround = false;
	}

	//check Right
	if (p_Player->RowNowUp != p_Player->RowNowDown)
	{
		p_Player->CheckCollisionRight(&ScreenBlock[p_Player->RowNowDown][p_Player->ColumnNowRight + 1]);
	}
	p_Player->CheckCollisionRight(&ScreenBlock[p_Player->RowNowUp][p_Player->ColumnNowRight + 1]);
	//check left
	if (p_Player->RowNowUp != p_Player->RowNowDown)
	{
		p_Player->CheckCollisionLeft(&ScreenBlock[p_Player->RowNowDown][p_Player->ColumnNowLeft - 1]);
	}
	p_Player->CheckCollisionLeft(&ScreenBlock[p_Player->RowNowUp][p_Player->ColumnNowLeft - 1]);

	p_Player->UpdateCoord();
}
//====================
//表示
//====================
void	PlayerDraw()
{
	if (p_Player->isVisible)
	{
		p_Player->getPlayerCol()->DrawCollider();
	}

	//if (mario.UseFlag != TRUE)
	//{
	//	return;//フラグがOFFならキャンセル
	//}

	//if (mario.MoveFlag == true)
	//{
	//	//前回座標へカーソルを移動させる
	//	gotoxy((int)player.PositionOldX, (int)player.PositionOldY);
	//	printf("  ");//半角スペース二つ
	//	mario.MoveFlag = false;
	//}


	//textcolor(BLUE);
	//gotoxy((int)player.PositionX, (int)player.PositionY);
	//wchar_t shikaku[] = L"■";
	//printf("%ls", L"正");
	//gotoxy(1, 1);
	//printf("■");
	//printf("█");
	//gotoxy(1, 1);
	//printf("░");


	/*if (player.UseFlag != TRUE)
	{
		return;
	}*/

	/*for (int i = 0; i < length; i++)
	{

	}*/

	/*if (player.MoveFlag == true)
	{
		gotoxy((int)player.PositionOldX, (int)player.PositionOldY);
		printf("  ");
	}*/
	//player->Idle_Ani();
}
//====================
//終了
//====================
void	PlayerUninit()
{
	delete p_Player;

}



void PlayerNormal(void)
{
	//Aキーで左に移動する
	//if (inport(PK_A))
	//{
	//	mario.PositionX -= PLAYER_MOVE_SPEED;
	//	//LIMIT_LEFTより先に行かないように補正する
	//	if (mario.PositionX < LIMIT_LEFT)
	//	{
	//		mario.PositionX = LIMIT_LEFT;
	//	}
	//}
	//Dキーで右に移動する
	//if (inport(PK_D))
	//{
	//	mario.PositionX += PLAYER_MOVE_SPEED;
	//	//LIMIT_RIGHTより先に行かないように補正する
	//	if (mario.PositionX > LIMIT_RIGHT)
	//	{
	//		mario.PositionX = LIMIT_RIGHT;
	//	}
	//}
	//スペースキーが押されたらジャンプ処理を行う
	//if (inport(PK_SP))
	//{
	//	//縦方向の初速度を設定する
	//	mario.MoveY = mario.JumpPower;//<<<<<<<<<<<<<<<<<<<<
	//	//ステータスをジャンプ状態へ移行させる
	//	mario.Status = STS_JUMP;
	//}
}

void Player::PlayerMove()
{
	if (!isVisible)
	{
		return;
	}
	
	if (InputManager::IsPressing(InputManager::k_W))
	{
		//p_Player->setPlayerY(y -= p_Player->getPlayerMoveY());
		//p_coltest->MoveCollider(MoveX, 0);
		MoveY -= MoveSpeed;
		OnGround = false;
	}
	//to do (nanamebug)
	else if (InputManager::IsPressing(InputManager::k_A))
	{
		MoveX -= MoveSpeed;
		//MoveY += MoveSpeed;
	}
	else if (InputManager::IsPressing(InputManager::k_S))
	{
		MoveY += MoveSpeed;
		OnGround = false;
	}
	else if (InputManager::IsPressing(InputManager::k_D))
	{
		MoveX += MoveSpeed;
	}
	if (OnGround)
	{
		if ((MoveX != 0 || MoveY != 0))
		{
			Status = STS_WALK;
		}
		else
		{
			Status = STS_IDLE;
		}
	}
}

void Player::PlayerJump()
{
	if (!isVisible)
	{
		return;
	}

	if (OnGround)
	{
		gravityCount = 0;
		JumpCd = 2;
	}
	else if(gravityCount < 13)
	{
		gravityCount += 4;
		MoveY += Gravity * gravityCount;
	}
	else
	{
		MoveY += Gravity * gravityCount;
	}
	if (InputManager::OnPressed(InputManager::k_SPACE) && JumpCd > 0)
	{
		playsound(JumpSound, 0);
		JumpCd--;
		gravityCount = 0;
		MoveY = 0;
		OnGround = false;
		JumpPower = PLAYER_JUMP_POWER;
		Status = STS_JUMP;
		jumpCount = 20;
	}
	if (InputManager::OnPressed(InputManager::k_V) && JumpCd > 0)
	{
		playsound(JumpSound, 0);
		JumpCd--;
		gravityCount = 0;
		MoveY = 0;
		OnGround = false;
		JumpPower = PLAYER_JUMP_POWER_LIT;
		Status = STS_JUMP;
		jumpCount = 25;
	}

	if (Status == STS_JUMP)
	{
		if (JumpPower > 0)
		{
			jumpCount--;
			MoveY -= p_Player->JumpPower * jumpCount;
		}
		else
		{
			gravityCount = 0;
			return;
		}
		
	}
	//Aキーで左に移動する
	//if (inport(PK_A))
	//{
	//	mario.PositionX -= PLAYER_MOVE_SPEED;

	//	//LIMIT_LEFTより先に行かないように補正する
	//	if (mario.PositionX < LIMIT_LEFT)
	//	{
	//		mario.PositionX = LIMIT_LEFT;
	//	}
	//}
	////Dキーで右に移動する
	//if (inport(PK_D))
	//{
	//	mario.PositionX += PLAYER_MOVE_SPEED;
	//	//LIMIT_RIGHTより先に行かないように補正する
	//	if (mario.PositionX > LIMIT_RIGHT)
	//	{
	//		mario.PositionX = LIMIT_RIGHT;
	//	}
	//}

	//プレイヤーのY座標にYの移動量を反映させる
//	mario.PositionY += mario.MoveY;
	//mario.MoveY -= (mario.JumpPower / mario.Gravity);//<<<<<<<毎回ジャンプ量を作成しなおす

	//Yの移動量に重力の影響を与える
//	mario.MoveY += mario.Gravity;
	//mario.PositionY += mario.MoveY;//<<<<<<<<<<<<<<Y座標に今回のジャンプ量を反映させる

	//着地したかどうかのチェックを行う  とりあえず版
	//if (mario.PositionY > 15.0f)
	//{
	//	//着地していたら高さの補正をする
	//	mario.PositionY = 15.0f;
	//	//ステータスをSTS_NORMALに戻す
	//	mario.Status = STS_NORMAL;
	//	mario.MoveY = 0;//<<<<<<<<<<<<
	//}
}

void Player::CalPlayerPos()
{
	/*if ((int)MoveX > 0)
	{
		PlayerX += MoveX;
		MoveX--;
	}
	else if ((int)MoveX < 0)
	{
		PlayerX += MoveX;
		MoveX++;
	}*/

	

	if (MoveX != 0)
	{
		PlayerX += MoveX;
		MoveX = 0;
	}
	if (MoveY != 0)
	{
		PlayerY += MoveY;
		MoveY = 0;
	}
	
	Player_Col->UpdateStartPos(PlayerX, PlayerY, frame_width, frame_height);

	/*if (MoveX > 0 )
	{
		PlayerX++;
		MoveX--;
		isMoving = true;
	}
	else if (MoveX < 0)
	{
		PlayerX--;
		MoveX++;
		isMoving = true;
	}
	
	if (MoveY > 0)
	{
		PlayerY++;
		MoveY--;
		isMoving = true;
	}
	else if (MoveY < 0)
	{
		PlayerY--;
		MoveY++;
		isMoving = true;
	}*/
}

void Player::CheckOnGround(Block* _ground, int _num)
{
	gotoxy(100, 10);
	printf("          ");
	if (OnGround)
	{
		Collider *groundNow = _ground[OnGroundId].getBlockCol();
		textcolor(YELLOW);
		gotoxy(100, 10);
		printf("OnGround!");
		if (groundNow->getFrameX()- (float)groundNow->getFrameWidth() / 2 > (Player_Col->getFrameX() + Player_Col->getFrameWidth() / 2) || ((groundNow->getFrameX() + (float)groundNow->getFrameWidth() / 2) < PlayerX))
		{
			OnGround = false;
		}
	}
	//Player_Col->PositionUpdate(PlayerX, PlayerY);
	for (int i = 0; i < _num; i++)
	{
		float Distance = _ground[i].getY() - Player_Col->getFrameY();
		if (OnGround && Distance == 4.5f)//Player_Col->getFrameHeight() / 2
		{
			return;
		}
		if (Player_Col->CheckCollision_RectRect(*_ground[i].getBlockCol()))
		{
			if (Distance > 0 && Distance <= Player_Col->getFrameHeight() / 2)
			{
				/*for (int j = 0; j < Player_Col->countOld; j++)
				{
					gotoxy(Player_Col->CoordOld[j].x, Player_Col->CoordOld[j].y);
					printf(" ");
				}*/
				
				for (int k = 0; k < Player_Col->count; k++)
				{
					Player_Col->Coord[k].needDraw = true;
				}
				while (Player_Col->CheckCollision_RectRect(*_ground[i].getBlockCol()))
				{
					PlayerY--;
					Player_Col->setFrameY(Player_Col->getFrameY() - 1.0f);
				}
				PlayerY++;
				Player_Col->setFrameY(Player_Col->getFrameY() + 1.0f);
				PositionOldY = PlayerY;
				Player_Col->setFrameOldY(Player_Col->getFrameY());
				Player_Col->GroundChecking = true;
				Player_Col->UpdateCoord();
				OnGround = true;
				OnCollision = true;
				OnGroundId = i;
			}
			/*if (!OnGround)
			{
				setPlayerY(PositionOldY);
				Player_Col->setFrameY(Player_Col->getFrameOldY());
			}*/
			/*else
			{
				setPlayerY(p_Ground[i].getY() - getPlayerHeight());
				Player_Col->setFrameY(p_Ground[i].getY() - Player_Col->getFrameHeight() / 2);
			}*/
			//Player_Col->PositionUpdate(PlayerX, PlayerY);
			return;
		}
	}
}

void Player::CheckOnGroundTest(Block* _ground)
{
	if (!_ground->isCollider)
	{
		return;
	}
	float Distance = _ground->getBlockCol()->StartY - Player_Col->StartY - Player_Col->getFrameHeight();

	
	if (_ground->isCollider && OnGround && abs(Distance) <= 0)
	{
		return;
	}
	else
	{
		OnGround = false;
	}
	
	while((Player_Col->CheckCollision_RectRect(*_ground->getBlockCol())) && _ground->isCollider)
	{
		Player_Col->GroundChecking = true;
		PlayerY--;
		Player_Col->setFrameY(Player_Col->getFrameY() - 1.0f);
		Player_Col->StartY -= 1.0f;
	}
	if (Player_Col->GroundChecking == true)
	{
		while (!Player_Col->CheckCollision_RectRect(*_ground->getBlockCol()))
		{
			PlayerY += 0.125f;
			Player_Col->setFrameY(Player_Col->getFrameY() + 0.125f);
			Player_Col->StartY += 0.125f;
		}
		PlayerY -= 0.125f;
		Player_Col->setFrameY(Player_Col->getFrameY() - 0.125f);
		Player_Col->StartY -= 0.125f;
		/*for (int i = 0; i < Player_Col->countOld; i++)
		{
			gotoxy((int)Player_Col->CoordOld[i].x, (int)Player_Col->CoordOld[i].y);
			printf(" ");
		}*/
 		OnGround = true;
		Status = STS_IDLE;
		//PositionOldX = PlayerX;
		//PositionOldY = PlayerY;
		//Player_Col->setFrameOldX(Player_Col->getFrameX());
		//Player_Col->setFrameOldY(Player_Col->getFrameY());
		Player_Col->UpdateCoord();
		//Player_Col->SaveOldCoord();
		Player_Col->GroundChecking = false;
		//Player_Col->setNeedClear(false);
	}
}

void Player::CheckCollisionRight(Block * _ground)
{
	if (!_ground->isCollider)
	{
		return;
	}
	while (Player_Col->CheckCollision_RectRect(*_ground->getBlockCol()))
	{
		Player_Col->GroundChecking = true;
		PlayerX--;
		Player_Col->setFrameX(Player_Col->getFrameX() - 1.0f);
		Player_Col->StartX--;
	}
	if (Player_Col->GroundChecking == true)
	{
		MoveX = 0;
		Player_Col->UpdateCoord();
		Player_Col->GroundChecking = false;
	}
}

void Player::CheckCollisionLeft(Block * _ground)
{
	if (!_ground->isCollider)
	{
		return;
	}
	while (Player_Col->CheckCollision_RectRect(*_ground->getBlockCol()))
	{
 		Player_Col->GroundChecking = true;
		PlayerX++;
		Player_Col->setFrameX(Player_Col->getFrameX() + 1.0f);
		Player_Col->StartX++;
	}
	if (Player_Col->GroundChecking == true)
	{
		MoveX = 0;
		Player_Col->UpdateCoord();
		Player_Col->GroundChecking = false;
	}
}

void Player::CheckCollisionUp(Block * _ground)
{
	if (!_ground->isCollider)
	{
		return;
	}
	while (Player_Col->CheckCollision_RectRect(*_ground->getBlockCol()))
	{
		Player_Col->GroundChecking = true;
		PlayerY += 0.5f;
		Player_Col->setFrameY(Player_Col->getFrameY() + 0.5f);
		Player_Col->StartY += 0.5f;
	}
	if (Player_Col->GroundChecking == true)
	{
		while (Player_Col->CheckCollision_RectRect(*_ground->getBlockCol()))
		{
			PlayerY -= 0.125f;
			Player_Col->setFrameY(Player_Col->getFrameY() - 0.125f);
			Player_Col->StartY -= 0.125f;
		}
		PlayerY += 0.125f;
		Player_Col->setFrameY(Player_Col->getFrameY() + 0.125f);
		Player_Col->StartY += 0.125f;
		/*for (int i = 0; i < Player_Col->countOld; i++)
		{
			gotoxy((int)Player_Col->CoordOld[i].x, (int)Player_Col->CoordOld[i].y);
			printf(" ");
		}*/
		MoveY = 0;
		//Player_Col->setFrameOldX(Player_Col->getFrameX());
		//Player_Col->setFrameOldY(Player_Col->getFrameY());
		Player_Col->UpdateCoord();
		//Player_Col->SaveOldCoord();
		Player_Col->GroundChecking = false;
		//Player_Col->setNeedClear(false);
	}
}

void Player::CheckBorder()
{
	//Check Left if PlayerX < LeftWall
	if (PlayerX < LEFT_BLOCK_X + TILE_WIDTH)
	{
		setPlayerX(LEFT_BLOCK_X + TILE_WIDTH);
		Player_Col->UpdateStartPos(PlayerX, PlayerY, frame_width, frame_height);
		SaveOldPosition();
	}
	//Check Right if PlayerX > RightWall
	if (PlayerX > RIGHT_BLOCK_X - Player_Col->getFrameWidth())
	{
		setPlayerX(RIGHT_BLOCK_X - Player_Col->getFrameWidth());
		Player_Col->UpdateStartPos(PlayerX, PlayerY, frame_width, frame_height);
		SaveOldPosition();
	}
	//Check Down if PlayerY > DownBlock
	if (PlayerY > DOWN_BLOCK_Y - Player_Col->getFrameHeight())
	{
		setPlayerY(DOWN_BLOCK_Y - Player_Col->getFrameHeight());
		Player_Col->UpdateStartPos(PlayerX, PlayerY, frame_width, frame_height);
		SaveOldPosition();
		OnGround = true;
	}
	//Check Up if PlayerY < UpBlock
	if (PlayerY < UP_BLOCK_Y + TILE_HEIGHT + 1)
	{
		setPlayerY(UP_BLOCK_Y + TILE_HEIGHT + 1);
		Player_Col->UpdateStartPos(PlayerX, PlayerY, frame_width, frame_height);
		SaveOldPosition();
	}

}

void Player::UpdateCoord()
{
	UpdateIntPos();

	if ((PlayerX_int - PlayerXOld_int) != 0 || (PlayerY_int - PlayerYOld_int) != 0)
	{
		isMoving = true;
	}

	if (isMoving)
	{
		ColPositionUpdate();
		Player_Col->UpdateCoord();
		Player_Col->setNeedDraw(true);
		Player_Col->setNeedClear(true);
		PlayerAniNow->setNeedDraw(true);
		PlayerAniNow->setNeedClear(true);
		isMoving = false;
		return;
	}
	Player_Col->setNeedDraw(false);
	Player_Col->setNeedClear(false);

	/*if (OnCollision)
	{
		Player_Col->setNeedClear(false);
		OnCollision = false;
	}*/
}


Player::Player()
{
	//Player_Col.setFrameX(PlayerX);
	//Player_Col.setFrameY(PlayerY);
	//Player_Col.setFrameWidth(frame_width);
	//Player_Col.setFrameHeight(frame_height);
}

Player::Player(float _x, float _y)
{
	setPlayerX(_x);
	setPlayerY(_y);

	PlayerAniNow = NULL;
	Player_Col = NULL;
	//Player_Col->setFrameX(_x);
	//Player_Col->setFrameY(_y);
	//Player_Col->setFrameWidth(frame_width);
	//Player_Col->setFrameHeight(frame_height);
	//Player_Col->setNeedClear(false);
}
Player::~Player()
{
	delete PlayerAniNow;
	delete Player_Col;
}

void Player::Init()
{
	MoveX = 0.0f;
	MoveY = 0.0f;
	JumpPower = PLAYER_JUMP_POWER;
	MoveSpeed = PLAYER_MOVE_SPEED;
	Gravity = GRAVITY_PERSEC;
	gravityCount = 0;
	OnGround = false;
	OnGroundId = 0;
	NowSaveId = 0;
	isMoving = false;
	OnCollision = false;
	isVisible = true;
	frame_width = 20;
	frame_height = 9;

	Player_Col = new Collider(0,0,20,9);
	Player_Col->UpdateStartPos(PlayerX, PlayerY, frame_width, frame_height);
	Player_Col->setNeedClear(false);
	Player_Col->InitCoord();
	Player_Col->visible = true;
	
	
	/*Player_Col->StartX = PlayerX + frame_width / 2 - Player_Col->getFrameWidth() / 2;
	Player_Col->StartY = PlayerY + frame_height - Player_Col->getFrameHeight();*/
	
	Status = STS_IDLE;
}

void Player::SaveOldPosition()
{
	PositionOldX = PlayerX;
	PositionOldY = PlayerY;
	
	Player_Col->SaveOldCoord();
}

void Player::UpdateIntPos()
{
	PlayerXOld_int = (int)PositionOldX;
	PlayerYOld_int = (int)PositionOldY;

	PlayerX_int = (int)PlayerX;
	PlayerY_int = (int)PlayerY;

}

float Player::getPlayerX()
{
	return PlayerX;
}

void Player::setPlayerX(float _x)
{
	PlayerX = _x;
}

float Player::getPlayerY()
{
	return PlayerY;
}

void Player::setPlayerY(float _y)
{
	PlayerY = _y;
}

float Player::getPlayerMoveX()
{
	return MoveX;
}

float Player::getPlayerMoveY()
{
	return MoveY;
}

void Player::setPlayerMoveX(float _x)
{
	MoveX = _x;
}

void Player::setPlayerMoveY(float _y)
{
	MoveY = _y;
}

float Player::getPlayerWidth()
{
	return frame_width;
}

void Player::setPlayerWidth(int _w)
{
	frame_width = _w;
}

float Player::getPlayerHeight()
{
	return frame_height;
}

void Player::setPlayerHeight(int _h)
{
	frame_height = _h;
}

void Player::ColPositionUpdate()
{
	Player_Col->setFrameOldX(Player_Col->getFrameX());
	Player_Col->setFrameOldY(Player_Col->getFrameY());
	Player_Col->StartX = PlayerX + (frame_width - 1) / 2 - (Player_Col->getFrameWidth() - 1) / 2;
	Player_Col->StartY = PlayerY + (frame_height - 1) - (Player_Col->getFrameHeight() - 1);
	Player_Col->setFrameX(PlayerX + (Player_Col->getFrameWidth() - 1) / 2.0f);
	Player_Col->setFrameY(PlayerY + (Player_Col->getFrameHeight() - 1) / 2.0f);
}

void Player::setPlayerAni(Animation * _ani)
{
	PlayerAniNow = _ani;
}

void Player::setPlayerCol(Collider * _col)
{
	Player_Col = _col;
}

Animation * Player::getPlayerAni()
{
	return PlayerAniNow;
}

Collider * Player::getPlayerCol()
{
	return Player_Col;
}


