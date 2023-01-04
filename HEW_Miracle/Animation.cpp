#define	CONIOEX
#include "Animation.h"
#include "player.h"

using namespace std;

vector<AnimationData> animations;
int AnimationData::count = 0;
Bitmap* Kid_Idle;
Bitmap* Kid_Walk;
Animation* anitest;
Animation anitest2;
Animation* Idle;
Animation* Walk;
//Collider* p_coltest = new Collider;
//Collider* p_coltest2 = new Collider;
//Collider* p_PlayerCol = new Collider;

//TriangleCollider* p_trianglecoltest = new TriangleCollider;
int Anicount = 0;
bool isSwitching = false;
int LastStatus = 0;

AnimationData::AnimationData() {}
AnimationData::AnimationData(string key, string file, int fc, int xc, int yc, int spd) :
	index(AnimationData::count++), name(key), fileName(file), maxFrame(fc), xCount(xc), yCount(yc), speed(spd) {}


//Animation::Animation(int id) {
//	this->Animation::Animation(&animations[id]);
//}
//:Sprite(data->fileName)
Animation::Animation(AnimationData* data, Bitmap* ani_bmp) {
	this->bitmap = ani_bmp;
	count = frame = 0;
	aData = data;
	//makeShineData();
	setSpeed(data->speed);
	width = bitmap->getWidth();
	height = bitmap->getHeight();
	OldX = X = 0;
	OldY = Y = 0;
	
	//updateFrameRect();
	setNeedDraw(true);
	setNeedClear(false);
	setAutoRotate(true);
	setReverse(false);
	setLoop(true);
	play();
	
	//Create Coord array
	aniCoord = new VecPlus*[aData->maxFrame];
	for (int i = 0; i < aData->maxFrame; i++)
	{
		aniCoord[i] = new VecPlus[width / aData->xCount * height / aData->yCount];
	}
	aniCoordNow = new VecPlus[width / aData->xCount * height / aData->yCount];
	aniCoordOld = new VecPlus[width / aData->xCount * height / aData->yCount];
	//Init Coord array's content(char)
	/*for (int frame = 0; frame < aData->maxFrame; frame++)
	{
		CoordCount = 0;
		CoordOldCount = 0;
		for (int dy = (height / aData->yCount) * (frame / aData->xCount); dy < (height / aData->yCount) * ((frame / aData->xCount) + 1); dy++)
		{
			for (int dx = (width / aData->xCount) * (frame % aData->xCount); dx < (width / aData->xCount) * ((frame % aData->xCount) + 1); dx++)
			{
				aniCoord[frame][CoordCount].needDraw = true;
				aniCoord[frame][CoordCount].x = X + dx % (width / aData->xCount);
				aniCoord[frame][CoordCount].y = Y + dy % (height / aData->yCount);
				aniCoordOld[frame][CoordOldCount].needDraw = true;
				aniCoordOld[frame][CoordOldCount].x = X + dx % (width / aData->xCount);
				aniCoordOld[frame][CoordOldCount].y = Y + dy % (height / aData->yCount);

				aniCoord[frame][CoordCount++].content = bitmap->data[dy][dx];
				aniCoordOld[frame][CoordOldCount++].content = bitmap->data[dy][dx];
			}
		}
	}*/

	for (int _frame = 0; _frame < aData->maxFrame; _frame++)
	{
		CoordCount = 0;
		for (int dy = (height / aData->yCount) * (_frame / aData->xCount); dy < (height / aData->yCount) * ((_frame / aData->xCount) + 1); dy++)
		{
			for (int dx = (width / aData->xCount) * (_frame % aData->xCount); dx < (width / aData->xCount) * ((_frame % aData->xCount) + 1); dx++)
			{
				aniCoord[_frame][CoordCount++] = { 0, 0, true, bitmap->data[dy][dx] };
			}
		}
	}
	for (int _frame = 0; _frame < aData->maxFrame; _frame++)
	{
		for (int i = 0; i < CoordCount; i++)
		{
			aniCoord[_frame][i].x = (float)(i % (width / aData->xCount));
			aniCoord[_frame][i].y = (float)(i / (width / aData->xCount));
		}
	}


	CoordOldCount = CoordNowCount = width / aData->xCount * height / aData->yCount;
	for (int i = 0; i < CoordNowCount; i++)
	{
		aniCoordNow[i] = { (float)(X + (i % (width / aData->xCount))),(float)(Y + (i / (width / aData->xCount))),true,aniCoord[0][i].content };
		aniCoordOld[i] = { (float)(X + (i % (width / aData->xCount))),(float)(Y + (i / (width / aData->xCount))),true,aniCoord[0][i].content };
	}

	//for test
	/*textcolor(RED);
	gotoxy(0, 0);
	for (int i = 0; i < CoordNowCount; i++)
	{
		printf("%c", aniCoordNow[i].content);
		if (i % 30 == 0)
		{
			printf("\n");
		}
	}*/
	/*textcolor(RED);
	for (int frame = 0; frame < aData->maxFrame; frame++)
	{
		for (int i = 0; i < CoordCount; i++)
		{
			gotoxy(aniCoord[frame][i].x, aniCoord[frame][i].y);
			if (aniCoord[1][i].content == 'T')
			{
				printf(" ");
			}
			else if(aniCoord[1][i].content == '0')
			{
				printf("█");
			}
		}
	}*/
}

Animation::~Animation()
{
	delete bitmap;
	delete[] aniCoord;
	delete[] aniCoordOld;
	delete[] aniCoordNow;
}

void Animation::DrawAni()
{
	if (needclear)
	{
		for (int i = 0; i < CoordOldCount; i++)
		{
			if (aniCoordOld[i].needDraw && aniCoordOld[i].content != 'T')
			{
				gotoxy((int)aniCoordOld[i].x, (int)aniCoordOld[i].y);
				printf(" ");
			}
		}
		needclear = false;
	}

	if (playing && needdraw)
	{
		for (int i = 0; i < CoordNowCount; i++)
		{
			switch (aniCoordNow[i].content)
			{
			case 'T':
				continue;
			case '0':
				textcolor(DARKGRAY); break;
			case '1':
				textcolor(RED); break;
			case '2':
				textcolor(YELLOW); break;
			case '3':
				textcolor(LIGHTBLUE); break;
			case '4':
				textcolor(BLACK); break;
			}
			gotoxy((int)aniCoordNow[i].x, (int)aniCoordNow[i].y);
			printf("█");
		}
		needdraw = false;
	}
}

void Animation::DrawTitleAni()
{
	if (lastFrame == frame)
		return;
	if (frame == 0)
	{
		textcolor(RED);

		for (int i = 0; i < CoordNowCount; i++)
		{
			if (aniCoordNow[i].needDraw)
			{
				gotoxy((int)aniCoordNow[i].x, (int)aniCoordNow[i].y);
				printf(" ");
			}
			
			for (int i = 0; i < CoordOldCount; i++)
			{
				if (aniCoordOld[i].needDraw)
				{
					gotoxy((int)aniCoordOld[i].x, (int)aniCoordOld[i].y);
					printf("█");
				}
			}
		}
	}
	else if (frame == 1)
	{
		textcolor(WHITE);

		/*for (int i = 0; i < CoordNowCount; i++)
		{
			if (aniCoordNow[i].needDraw)
			{
				gotoxy((int)aniCoordNow[i].x, (int)aniCoordNow[i].y);
				printf(" ");
			}
		}*/
		for (int i = 0; i < CoordOldCount; i++)
		{
			if (aniCoordOld[i].needDraw)
			{
				gotoxy((int)aniCoordOld[i].x, (int)aniCoordOld[i].y);
				printf(" ");
			}
		}

		for (int i = 0; i < CoordNowCount; i++)
		{
			if (aniCoordNow[i].needDraw)
			{
				gotoxy((int)aniCoordNow[i].x, (int)aniCoordNow[i].y);
				printf("█");
			}
		}
	}
	
}


//void Animation::makeShineData() {
//	for (int i = 0; i < aData->maxFrame; i++) {
//		shineData.push_back(NULL);
//	}
//	for (int i = 0; i < aData->shine.size(); i++) {
//		shineData[aData->shine[i].time] = &aData->shine[i];
//	}
//}
void Animation::setSpeed(int spd) { speed = spd; }
int Animation::getSpeed() { return speed; }

void Animation::start() {
	count = frame = 0; playing = true;
}
void Animation::play() { playing = true; }
void Animation::pause() { playing = false; }
void Animation::stop() {
	count = 0; frame = -1; playing = false;
	setFrameRect(Rect(0, 0, 0, 0));
}

bool Animation::getNeedDraw() { return needdraw; }
void Animation::setNeedDraw(bool n) { needdraw = n; }

bool Animation::getNeedClear()
{
	return needclear;
}

void Animation::setNeedClear(bool n)
{
	needclear = n;
}

void Animation::UpdateCoordTitle()
{
	CoordOldCount = CoordNowCount = 0;
	for (int i = 0; i < CoordCount; i++)
	{
		if (aniCoord[0][i].content == '0')
		{
			aniCoordOld[CoordOldCount].x = aniCoord[0][i].x;
			aniCoordOld[CoordOldCount].y = aniCoord[0][i].y;
			aniCoordOld[CoordOldCount++].content = aniCoord[0][i].content;
		}
	}
	for (int i = 0; i < CoordCount; i++)
	{
		if (aniCoord[1][i].content == '0')
		{
			aniCoordNow[CoordNowCount].x = aniCoord[1][i].x;
			aniCoordNow[CoordNowCount].y = aniCoord[1][i].y;
			aniCoordNow[CoordNowCount++].content = aniCoord[1][i].content;
		}
	}
	
	for (int i = 0; i < CoordOldCount; i++)
	{
		switch (aniCoordOld[i].content)
		{
		case 'T':
			continue;
		case '0':
			textcolor(WHITE); break;
		}
		gotoxy((int)aniCoordOld[i].x, (int)aniCoordOld[i].y);
		printf("█");
	}
	for (int j = 0; j < CoordOldCount; j++)
	{
		for (int i = 0; i < CoordNowCount; i++)
		{
			if ((int)aniCoordNow[i].x == (int)aniCoordOld[j].x && (int)aniCoordNow[i].y == (int)aniCoordOld[j].y && aniCoordNow[i].content == aniCoordOld[j].content)
			{
				aniCoordNow[i].needDraw = false;
				aniCoordOld[j].needDraw = false;
				break;
			}
		}
	}
	int tempold = 0;
	int tempnow = 0;

	textcolor(RED);
	for (int i = 0; i < CoordNowCount; i++)
	{
		if (aniCoordNow[i].needDraw)
		{
			gotoxy((int)aniCoordNow[i].x, (int)aniCoordNow[i].y);
			printf("█");
		}
		
	}
	/*for (int i = 0; i < CoordOldCount; i++)
	{
		if (aniCoordOld[i].needDraw)
		{
			aniCoordOld[tempold].x = aniCoordOld[i].x;
			aniCoordOld[tempold++].y = aniCoordOld[i].y;
		}
	}
	for (int i = 0; i < CoordNowCount; i++)
	{
		if (aniCoordNow[i].needDraw)
		{
			aniCoordNow[tempnow].x = aniCoordNow[i].x;
			aniCoordNow[tempnow++].y = aniCoordNow[i].y;
		}
	}
	CoordOldCount = tempold;
	CoordNowCount = tempnow;*/
	
	/*for (int i = 0; i < CoordNowCount; i++)
	{
		if(!aniCoordNow[i].needDraw)
		{
			continue;
		}
		switch (aniCoordNow[i].content)
		{
		case 'T':
			textcolor(RED); break;
		case '0':
			textcolor(WHITE); break;
		}
		gotoxy((int)aniCoordNow[i].x, (int)aniCoordNow[i].y);
		printf("█");
	}*/
	/*for (int i = 0; i < CoordNowCount; i++)
	{
		switch (aniCoordNow[i].content)
		{
		case 'T':
			continue;
		case '0':
			textcolor(WHITE); break;
		}
		gotoxy((int)aniCoordNow[i].x, (int)aniCoordNow[i].y);
		printf("█");
	}*/
	
}

void Animation::ClearTitle()
{
	for (int i = 0; i < CoordNowCount; i++)
	{
		if (aniCoordNow[i].needDraw)
		{
			gotoxy((int)aniCoordNow[i].x, (int)aniCoordNow[i].y);
			printf(" ");
		}

	}
	for (int i = 0; i < CoordOldCount; i++)
	{
		gotoxy((int)aniCoordOld[i].x, (int)aniCoordOld[i].y);
		printf(" ");
	}
}

void Animation::UpdateCoord()
{
	if (needdraw)
	{
		for (int i = 0; i < CoordNowCount; i++)
		{
			aniCoordOld[i].x = aniCoordNow[i].x;
			aniCoordOld[i].y = aniCoordNow[i].y;
			aniCoordOld[i].content = aniCoordNow[i].content;
			aniCoordNow[i].x += (X - OldX);
			aniCoordNow[i].y += (Y - OldY);
			aniCoordNow[i].content = aniCoord[frame][i].content;
		}
	}

	if (needclear)
	{
		for (int i = 0; i < CoordOldCount; i++)
		{
			aniCoordNow[i].needDraw = true;
			aniCoordOld[i].needDraw = true;
		}

		for (int j = 0; j < CoordOldCount; j++)
		{
			for (int i = 0; i < CoordCount; i++)
			{
				if ((int)aniCoordNow[i].x == (int)aniCoordOld[j].x && (int)aniCoordNow[i].y == (int)aniCoordOld[j].y && aniCoordNow[i].content == aniCoordOld[j].content)
				{
					aniCoordNow[i].needDraw = false;
					aniCoordOld[j].needDraw = false;
					break;
				}
			}
		}
		/*for (int i = 0; i < CoordOldCount; i++)
		{
			aniCoordOld[frame][i] = aniCoord[frame][i];
		}*/
	}
}

void Animation::ClearCurFrame()
{
	for (int i = 0; i < CoordNowCount; i++)
	{
		gotoxy(aniCoordNow[i].x, aniCoordNow[i].y);
		printf(" ");
	}
}

int Animation::getFrame() { return frame; }

void Animation::setLoop(bool l) { loop = l; }
void Animation::setReverse(bool r) { reverse = r; }

void Animation::setAutoRotate(bool r) { autoRotate = r; }
bool Animation::isAutoRotate() { return autoRotate; }

bool Animation::isPlaying() { return playing; }
bool Animation::isEnded() { return frame == -1; }

void Animation::InitPlayerCoord(float _x, float _y)
{
	OldX = X = _x;
	OldY = Y = _y;

	for (int i = 0; i < CoordNowCount; i++)
	{
		aniCoordNow[i].x += _x;
		aniCoordNow[i].y += _y;
		aniCoordNow[i].content = aniCoord[frame][i].content;
	}
	for (int i = 0; i < CoordOldCount; i++)
	{
		aniCoordOld[i].x += _x;
		aniCoordOld[i].y += _y;
		aniCoordOld[i].content = aniCoord[frame][i].content;
	}
}

void Animation::InitPlayerCoord()
{
	for (int i = 0; i < CoordOldCount; i++)
	{
		aniCoordOld[i].content = aniCoord[frame][i].content;
	}

	for (int i = 0; i < CoordNowCount; i++)
	{
		aniCoordNow[i].content = aniCoord[frame][i].content;
	}
}

void Animation::setFrameRect(Rect rect) {
	frameRect = rect;
}

//int Animation::getFrameRectX() {
//	return (frame % aData->xCount)*getFrameRectWidth();
//}
//int Animation::getFrameRectY() {
//	return (frame / aData->xCount)*getFrameRectHeight();
//}
int Animation::getFrameRectWidth() {
	return width / aData->xCount;
}
int Animation::getFrameRectHeight() {
	return height / aData->yCount;
}
int Animation::duration() {
	return aData->maxFrame * speed;
}
//void Animation::updateOthers() {
//	Sprite::updateOthers();
//	updateAnimationFrame();
//	updateShineData();
//}
void Animation::updateAnimationFrame() {

	lastFrame = frame;

	if (playing) {
		frame = animationFunction(++count);
		if (frame >= aData->maxFrame)
			if (loop)
				frame = animationFunction(count = reverse ? 1 - duration() : 0);
			else stop();


		if (lastFrame != frame && frame >= 0)
		{
			setNeedDraw(true);
			setNeedClear(true);
		}

		if (X != OldX || Y != OldY)
		{
			setNeedClear(true);
			setNeedDraw(true);
		}
		

		//if (frame >= 0) updateFrameRect();
	}
}
void Animation::updateAnimationFrameTitle()
{
	lastFrame = frame;
	frame = animationFunction(++count);
	if (frame >= aData->maxFrame)
	{
		frame = animationFunction(0);
	}
}
void Animation::UpdatePlayerAnimation()
{
	OldX = X;
	OldY = Y;

	X = p_Player->getPlayerX();
	Y = p_Player->getPlayerY();

	updateAnimationFrame();

	UpdateCoord();
}
//void Animation::updateShineData() {
//	if (lastFrame != frame && frame >= 0) {
//		lastFrame = frame;
//		if (shineData[frame] != NULL) {
//			ShineData* dt = shineData[frame];
//			if (!dt->screen)
//				dynamic_cast<Sprite*>(parent)->shine(dt->c, dt->last*speed);
//			else
//				ScreenManager::currentScene()->shine(dt->c, dt->last*speed);
//		}
//	}
//}
//void Animation::updateFrameRect() {
//
//	setFrameRect(Rect(getFrameRectX(), getFrameRectY(), getFrameRectWidth(), getFrameRectHeight()));
//}
int Animation::animationFunction(int c) {
	return std::abs(c) / speed;
}

void AnimationInit()
{
	float PlayerX = p_Player->getPlayerX();
	float PlayerY = p_Player->getPlayerY();


	//animations.push_back(AnimationData("Kid_Idle_Animation", "../HEW_Miracle/ASCII-Kid_Idle_Animation.txt", 4, 4, 1, 3));
	animations.push_back(AnimationData("Kid_Idle", "../HEW_Miracle/ASCII-Kid_Idle_Animation.txt", 4, 4, 1, 10));
	animations.push_back(AnimationData("Kid_Walk", "../HEW_Miracle/ASCII-Kid_Walk.txt", 6, 6, 1, 20));
	Idle = new Animation(&animations[0], Kid_Idle);
	Walk = new Animation(&animations[1], Kid_Walk);
	//anitest = new Animation(&animations[0], Kid_Idle);
	p_Player->setPlayerAni(Idle);
	Idle->start();
	//p_Player->setPlayerCol(p_PlayerCol);

	/*p_Player->getPlayerAni()->OldPosition = new char*[TILE_HEIGHT];
	for (int i = 0; i < TILE_HEIGHT; i++)
	{
		p_Player->getPlayerAni()->OldPosition[i] = new char[TILE_WIDTH];
	}*/

	p_Player->getPlayerAni()->InitPlayerCoord(PlayerX, PlayerY);
	Walk->InitPlayerCoord(PlayerX, PlayerY);
	//p_Player->getPlayerAni()->X = PlayerX;
	//p_Player->getPlayerAni()->Y = PlayerY;
	

	//anitest2 = Animation(&animations[0], Kid_Idle);

	/*anitest2.OldPosition = new char*[TILE_HEIGHT];
	for (int i = 0; i < TILE_HEIGHT; i++)
	{
		anitest2.OldPosition[i] = new char[TILE_WIDTH];
	}*/

	//int keycd = 0;
	//anitest->z = 5;
	//anitest->play();
	//keycd = 5;
	//anitest->visible = true;
	/*anitest->setLoop(true);
	anitest->X = 10;
	anitest->Y = 20;
	anitest->setNeedDraw(false);
*/

	/*anitest2.setLoop(true);
	anitest2.X = 10;
	anitest2.Y = 20;
	anitest2.setNeedDraw(true);
	anitest2.setNeedClear(false);*/

	//p_coltest->setFrameX(anitest2.X + 14);
	//p_coltest->setFrameY(anitest2.Y + 8);
	//p_coltest->setFrameHeight(TILE_HEIGHT);
	//p_coltest->setFrameWidth(TILE_WIDTH);
	//p_coltest->setNeedClear(false);

	/*p_coltest2->setFrameX(50);
	p_coltest2->setFrameY(50);
	p_coltest2->setFrameHeight(TILE_HEIGHT);
	p_coltest2->setFrameWidth(TILE_WIDTH);
	p_coltest2->setNeedClear(false);*/

	/*Vec temp_v[3] = { {100, 80}, {120, 80}, {120, 90} };
	p_trianglecoltest->setNeedClear(false);
	p_trianglecoltest->setTriangle(temp_v);*/
	//p_trianglecoltest->TriInit();
	//addChild(anitest);
	//anitest->play();
	//gotoxy(anitest->x, anitest->y);
	//for (int dy = TILE_HEIGHT * (anitest->aData->yCount - 1), i = 1; dy < TILE_HEIGHT * anitest->aData->yCount; dy++)
	//{
	//	for (int dx = TILE_WIDTH * (anitest->aData->xCount - 1); dx < TILE_WIDTH * anitest->aData->xCount; dx++)
	//	{
	//		printf("%c", anitest->getBitmap()->data[dy][dx]);
	//	}
	//	gotoxy(anitest->x, anitest->y + i);
	//	i++;
	//}
	
}

void AnimationUpdate()
{

	if (LastStatus != p_Player->Status)
	{
		isSwitching = true;
	}
	else
	{
		isSwitching = false;
	}
	switch (p_Player->Status)
	{
	case STS_IDLE:
		if (isSwitching && LastStatus != STS_GAMEOVER)
		{
			p_Player->getPlayerAni()->ClearCurFrame();
			p_Player->getPlayerAni()->setNeedClear(true);
		}
		p_Player->setPlayerAni(Idle);
		p_Player->getPlayerAni()->InitPlayerCoord();
		p_Player->getPlayerAni()->UpdatePlayerAnimation();
		break;
	case STS_WALK:
		if (isSwitching && LastStatus != STS_GAMEOVER)
		{
			p_Player->getPlayerAni()->ClearCurFrame();
			p_Player->getPlayerAni()->setNeedClear(true);
		}
		p_Player->setPlayerAni(Walk);
		p_Player->getPlayerAni()->InitPlayerCoord();
		p_Player->getPlayerAni()->UpdatePlayerAnimation();
		break;
	case STS_JUMP:
		if (isSwitching)
		{
			p_Player->getPlayerAni()->ClearCurFrame();
			p_Player->getPlayerAni()->setNeedClear(true);
		}
		p_Player->setPlayerAni(Idle);
		p_Player->getPlayerAni()->InitPlayerCoord();
		p_Player->getPlayerAni()->UpdatePlayerAnimation();
		break;
	case STS_GAMEOVER:
		break;
	}


	/*gotoxy(0, 20);
	textcolor(RED);
	printf("Anicount = %d", Anicount);

	anitest2.OldX = anitest2.X;
	anitest2.OldY = anitest2.Y;
	p_coltest->setFrameOldX(p_coltest->getFrameX());
	p_coltest->setFrameOldY(p_coltest->getFrameY());
	p_coltest->setFrameX(anitest2.X + 14);
	p_coltest->setFrameY(anitest2.Y + 7);


	anitest->updateAnimationFrame();
	anitest2.updateAnimationFrame();


	if (inport(PK_D))
	{
		int MoveX = 2;
		anitest2.X += MoveX;
		p_coltest->MoveCollider(MoveX, 0);
		Anicount++;
		anitest2.setNeedClear(true);
		p_coltest->setNeedClear(true);
	}
	else if (inport(PK_S))
	{
		int MoveY = 1;
		anitest2.Y += MoveY;
		p_coltest->MoveCollider(0, MoveY);
		anitest2.setNeedClear(true);
		p_coltest->setNeedClear(true);
	}
	else if (inport(PK_A))
	{
		int MoveX = -2;
		anitest2.X += MoveX;
		p_coltest->MoveCollider(MoveX, 0);
		anitest2.setNeedClear(true);
		p_coltest->setNeedClear(true);
	}
	else if (inport(PK_W))
	{
		int MoveY = -1;
		anitest2.Y += MoveY;
		p_coltest->MoveCollider(0, MoveY);
		anitest2.setNeedClear(true);
		p_coltest->setNeedClear(true);
	}*/

	LastStatus = p_Player->Status;
}

void AnimationDraw()
{
	//PlayAni_OneBlock(anitest);
	//ClearAni_OneBlock(anitest2);
	//PlayAni_OneBlock(anitest2);

	//ClearAni_OneBlock(*p_Player->getPlayerAni());
	//PlayAni_OneBlock(*p_Player->getPlayerAni());
	p_Player->getPlayerAni()->DrawAni();
	//p_coltest->DrawCollider();
	//p_coltest2->DrawCollider();
	//CollisionCheckText();
	//p_trianglecoltest->DrawTriangleCol();
}

void AnimationUninit()
{
	//delete[](p_Player->getPlayerAni()->OldPosition);
}

void PlayAni_OneBlock(Animation &p_PlayAni)
{
	if (!p_PlayAni.getNeedDraw()) { return; }

	int _frame = p_PlayAni.getFrame();//p_PlayAni.getFrame();
	int xCount = p_PlayAni.aData->xCount;

	textcolor(RED);
	gotoxy(p_PlayAni.X, p_PlayAni.Y);
	for (int dy = TILE_HEIGHT * (_frame / xCount), i = 1, Oy = 0; dy < TILE_HEIGHT * ((_frame / xCount) + 1); dy++, i++, Oy++)
	{
		for (int dx = TILE_WIDTH * (_frame % xCount), Ox = 0; dx < TILE_WIDTH * (_frame % xCount + 1); dx++, Ox++)
		{
			p_PlayAni.OldPosition[Oy][Ox] = p_PlayAni.bitmap->data[dy][dx];
			if (p_PlayAni.bitmap->data[dy][dx] == 'T')
			{
				//printf(" ");
				gotoxy(wherex() + 1, wherey());
				/*int tempX = wherex();
				int tempY = wherey();
				gotoxy(tempX+1, tempY);*/
			}
			else
			{
				//int tempX = wherex();
				//int tempY = wherey();
				printf("%c", p_PlayAni.bitmap->data[dy][dx]);
			}
		}
		gotoxy(p_PlayAni.X, p_PlayAni.Y + i);
	}
	/*if (p_PlayAni.X != p_PlayAni.OldX || p_PlayAni.Y != p_PlayAni.OldY)
	{
		p_PlayAni.setNeedClear(true);
	}*/
}

void ClearAni_OneBlock(Animation &p_ClearAni)
{
	//Clear Last Draw
	if (p_ClearAni.needclear)
	{
		gotoxy(p_ClearAni.OldX, p_ClearAni.OldY);
		for (int y = p_ClearAni.OldY, i = 1, Oy = 0; y < p_ClearAni.OldY + TILE_HEIGHT; y++, i++, Oy++)
		{
			for (int x = p_ClearAni.OldX, Ox = 0; x < p_ClearAni.OldX + TILE_WIDTH; x++, Ox++)
			{
				if (p_ClearAni.OldPosition[Oy][Ox] != 'T')
				{
					gotoxy(p_ClearAni.OldX + Ox, p_ClearAni.OldY + Oy);
					//int tempX = wherex();
					//int tempY = wherey();
					printf(" ");
				}
			}
			gotoxy(p_ClearAni.OldX, p_ClearAni.OldY + i);
		}
		p_ClearAni.setNeedClear(false);
	}
}

//void CollisionCheckText()
//{
//	if (p_Player->getPlayerCol()->CheckCollision_RectRect(*p_coltest2))
//	{
//		textcolor(GREEN);
//		gotoxy(10, 10);
//		printf("CollisionCheck: True ");
//	}
//	else
//	{
//		textcolor(RED);
//		gotoxy(10, 10);
//		printf("CollisionCheck: False");
//	}
//}
