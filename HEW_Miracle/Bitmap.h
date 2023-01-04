#pragma once

#define		CONIOEX

#include "Rect.h"
#include<vector>
#include<fstream>
#include<map>

using namespace std;

class Bitmap {
public:
	static Bitmap* getBitmap(string str);
	//static void clearCache();

	Bitmap();
	Bitmap(string fileName);
	Bitmap(int width, int height);


	int getWidth();
	int getHeight();
	/*char** getData();
	char getData(int x, int y);

	void drawRect(int x, int y, int width, int height, char c);
	void drawRect(Rect rect, char c);
	void clearRect(int x, int y, int width, int height);
	void clearRect(Rect rect);*/
	
	void paint(int x, int y, char c);
	char** data;

	/*Bitmap clip(int x, int y, int width, int height);

	void copyTo(Bitmap* bitmap, int x, int y, int width, int height, int tx = 0, int ty = 0, bool ignore = true);
	void copyFrom(Bitmap* bitmap, int x, int y, int width, int height, int tx = 0, int ty = 0, bool ignore = true);*/
private:
	void readFromFile(string fileName);
	void createEmpty(int width, int height);
	string url;
	int width, height;


	static map<string, Bitmap> bitmapCache;
	//static map<int, Bitmap> iconCache;
	//static vector<Bitmap> otherBitmaps;
};

void BitmapInit();

extern Bitmap* Wall;
extern Bitmap* Kid_Idle;
extern Bitmap* Kid_Walk;
extern Bitmap* GameOverBmp;
extern Bitmap* SavePointBmp;
extern Bitmap* PortalBmp;
extern Bitmap* Hint1Bmp;
extern Bitmap* RainbowBallBmp;
extern Bitmap* TitleAniBmp;
extern Bitmap* MiracleBmp;
extern Bitmap* EndBmp;
