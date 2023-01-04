#pragma once
#include"DisplayObject.h"
#include "Bitmap.h"
using namespace std;

struct ShineData;


class Sprite : public DisplayObject
{
public:
	Sprite();
	Sprite(string fileName);
	Sprite(Bitmap* bitmap);
	Sprite(int width, int height);

	/*vector<vector<char> > getDisplayData();
	void quickRender(char** &map, int lx, int ly);*/
	void setBitmap(Bitmap* bitmap);
	Bitmap* getBitmap();
	void setFrameRect(Rect rect);
	void setFrameRect(int x, int y, int width, int height);
	void setFrameRect();
	Rect getFrameRect();

	int getSpriteWidth() const;
	int getSpriteHeight() const;

	/*int PositionX;
	int PositionY;
	int Ani_Id;*/
	//Bitmap* bit;

	/*
	void shake(int power, int duration, double speed = 1, bool yShake = false);
	void shine(char c, int duration, bool transparent = false);

	bool getMirror();
	virtual void setMirror(bool mir);
protected:
	virtual void updateOthers();
	virtual void updateEffect();
	void updateShine();
	void updateShake();
	void processShake(int power, double dur);

	void initialiaze();
	void initialiazeEffect();
	void initialiazePosition();
	void initialiazeFrameRect();*/
	int rx, ry;
	int count;
	char shineChar;
	int shakePower;
	bool shakeY;
	double shakeSpeed;
	int shineDuration;
	int shakeDuration;
	bool shineTransparent;
	bool mirror;
	Bitmap* bitmap;
	Rect frameRect;
};

class Image
{
public:
	Image(int _x, int _y, Bitmap* _bmp);
	~Image();
	bool visible;
	int x;
	int y;
	int width;
	int height;
	Bitmap* sourcebmp;
	void showImage();
	void clearImage();
};