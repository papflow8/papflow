#pragma once

#define		CONIOEX
#include	"main.h"
#include	"Collider.h"
#include	"Bitmap.h"
#include	<string>


using namespace std;

struct AnimationData {
	//static int BeingHurtAnimationId;
	static int count;
	int index;

	string name;

	int maxFrame;
	int xCount, yCount;
	int speed;

	//vector<ShineData> shine;

	string fileName;

	AnimationData();
	AnimationData(string key, string file, int fc, int xc, int yc, int spd = 1);

	//void addShineData(int time, int last, char c, bool screen = false);
	//void addShineData(ShineData dt);
};

extern vector<AnimationData> animations;
//
class Animation{
public:
	//Animation(int id);
	Animation() {};
	Animation(AnimationData* data, Bitmap* ani_bmp);
	~Animation();

	void DrawAni();
	void DrawTitleAni();
	
	void start(); void play(); void pause(); void stop();
	void setSpeed(int spd);
	int getSpeed();
	void setLoop(bool l);
	void setReverse(bool r);

	void setAutoRotate(bool r);
	bool isAutoRotate();

	bool getNeedDraw();
	void setNeedDraw(bool n);

	bool getNeedClear();
	void setNeedClear(bool n);

	void UpdateCoordTitle();
	void ClearTitle();

	void UpdateCoord();
	void ClearCurFrame();

	int getFrame();

	int duration();
	bool isPlaying();
	bool isEnded();

	int width;
	int height;
	bool isInited;

	void InitPlayerCoord(float _x, float _y);
	void InitPlayerCoord();

	int X;
	int Y;

	int OldX;
	int OldY;

	char** OldPosition;

	VecPlus** aniCoord;
	VecPlus* aniCoordOld;
	VecPlus* aniCoordNow;
	int CoordCount;
	int CoordOldCount;
	int CoordNowCount;

	int getFrameRectWidth();
	int getFrameRectHeight();
	void setFrameRect(Rect rect);

	AnimationData* aData;
	Bitmap* bitmap;

	Rect frameRect;


	friend void PlayAni_OneBlock(Animation &p_PlayAni);
	friend void ClearAni_OneBlock(Animation &p_ClearAni);
	void updateAnimationFrame();
	void updateAnimationFrameTitle();
	void UpdatePlayerAnimation();
private:
	/*int getFrameRectX();
	int getFrameRectY();

	void makeShineData();*/


	int count, frame;
	int speed;
	int lastFrame;
	bool needclear;
	bool needdraw;
	bool playing;
	bool loop;
	bool reverse;
	bool autoRotate;

	//vector<ShineData*> shineData;
protected:
	//void updateOthers();
	//void updateAnimationFrame();
	//void updateShineData();
	//void updateFrameRect();
	
	int animationFunction(int c);
};

void AnimationInit();
void AnimationUpdate();
void AnimationDraw();
void AnimationUninit();
//void CollisionCheckText();

