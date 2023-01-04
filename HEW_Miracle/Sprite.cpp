#define CONIOEX
#include "main.h"
#include	<cmath>
#include	<fstream>
#include	"Sprite.h"

//#include"Database.h"
//#include"ScreenManager.h"

int Sprite::getSpriteWidth() const { return frameRect.width; }
int Sprite::getSpriteHeight() const { return frameRect.height; }

Sprite::Sprite() {
	this->Sprite::Sprite(new Bitmap());
}
Sprite::Sprite(string fileName) {
	this->Sprite::Sprite(Bitmap::getBitmap(fileName));
}
Sprite::Sprite(Bitmap* bitmap) {
	setBitmap(bitmap);
	//initialiaze();
}
Sprite::Sprite(int width, int height) {
	this->Sprite::Sprite(new Bitmap(width, height));
}
Rect Sprite::getFrameRect() {
	return frameRect;
}

//void Sprite::shake(int power, int duration, double speed, bool yShake) {
//	shakePower = power; shakeDuration = duration; shakeSpeed = speed; shakeY = yShake;
//}
//void Sprite::shine(char c, int duration, bool transparent) {
//	shineChar = c; shineDuration = duration; shineTransparent = transparent;
//}
//void Sprite::setMirror(bool mir) { mirror = mir; }
//bool Sprite::getMirror() { return mirror; }
//void Sprite::initialiaze() {
//	initialiazeEffect();
//	initialiazePosition();
//}
//void Sprite::initialiazeEffect() {
//	count = 0;
//	shineChar = 'T'; shakePower = 0;
//	shineDuration = shakeDuration = 0;
//}
//void Sprite::initialiazePosition() {
//	x = y = z = 0; rx = x; ry = y;
//	visible = true; mirror = false;
//}
//void Sprite::initialiazeFrameRect() {
//	width = bitmap->getWidth();
//	height = bitmap->getHeight();
//	setFrameRect();
//}
void Sprite::setFrameRect() {
	setFrameRect(Rect(0, 0, width, height));
}
void Sprite::setFrameRect(int x, int y, int width, int height) {
	setFrameRect(Rect(x, y, width, height));
}
void Sprite::setFrameRect(Rect rect) {
	frameRect = rect;
}
void Sprite::setBitmap(Bitmap* bitmap) {
	this->bitmap = bitmap;
	//initialiazeFrameRect();
}
Bitmap* Sprite::getBitmap() { return bitmap; }

//void Sprite::updateOthers() {
//	updateEffect();
//}
//void Sprite::updateEffect() {
//	updateShake();
//	updateShine();
//}
//void Sprite::updateShake() {
//	if (shakeDuration == 0) { rx = x; ry = y; }
//	if (shakeDuration > 0) {
//		processShake(shakePower, shakeDuration*shakeSpeed);
//		if (--shakeDuration <= 0) { x = rx; y = ry; }
//	}
//	if (shakeDuration < -1) {
//		processShake(shakePower, --shakeDuration*shakeSpeed);
//	}
//}
//void Sprite::processShake(int power, double dur) {
//	if (shakeY)
//		y = ry + power * sin(dur);
//	else
//		x = rx + power * sin(dur);
//}
//void Sprite::updateShine() {
//	if (shineDuration > 0) {
//		if (--shineDuration <= 0)
//			shineChar = 'T';
//	}
//}
//vector<vector<char> > Sprite::getDisplayData() {
//	//vector<vector<char> > data = bitmap.getData();
//	char** data = bitmap->getData();
//	int width = bitmap->getWidth();
//	int height = bitmap->getHeight();
//
//	vector<vector<char> > res;
//	vector<char> line;
//	for (int y = 0; y < frameRect.height; y++) {
//		for (int x = 0; x < frameRect.width; x++) {
//			int dx = x + frameRect.x;
//			int dy = y + frameRect.y;
//			if (dy >= 0 && dy < height && dx >= 0 && dx < width)
//				if (shineDuration > 0 || shineDuration == -1)
//					line.push_back(shineTransparent || data[dy][dx] != 'T' ? shineChar : 'T');
//				else
//					line.push_back(data[dy][dx]);
//		}
//		res.push_back(line);
//		line.clear();
//	}
//	return res;
//};
//void Sprite::quickRender(char** &map, int lx, int ly) {
//	if (!visible) return;
//
//
//	for (int i = 0; i < backChildren.size(); i++) {
//		DisplayObject* obj = backChildren[i];
//		int ox = obj->x; int oy = obj->y;
//		obj->quickRender(map, lx + ox, ly + oy);
//	}
//
//
//	char** data = bitmap->getData();
//	int width = bitmap->getWidth();
//	int height = bitmap->getHeight();
//
//
//	for (int y = 0; y < frameRect.height; y++) {
//		for (int x = 0; x < frameRect.width; x++) {
//			int dx = x + frameRect.x; int dy = y + frameRect.y;
//			if (mirror)
//				dx = frameRect.x + frameRect.width - x;
//
//			int sx = x + lx; int sy = y + ly;
//			if (dy >= 0 && dy < height && dx >= 0 && dx < width &&
//				sy >= 0 && sy < GHeight && sx >= 0 && sx < GWidth)
//
//				if (data[dy][dx] != 'T') map[sy][sx] =
//					(shineDuration > 0 || shineDuration == -1) ? shineChar : data[dy][dx];
//				else if ((shineDuration > 0 || shineDuration == -1) && shineTransparent)
//					map[sy][sx] = shineChar;
//		}
//	}
//
//	for (int i = 0; i < children.size(); i++) {
//		DisplayObject* obj = children[i];
//		int ox = obj->x; int oy = obj->y;
//		obj->quickRender(map, lx + ox, ly + oy);
//	}
//}


Image::Image(int _x, int _y, Bitmap* _bmp) : visible(false)
{
	x = _x;
	y = _y;
	sourcebmp = _bmp;
}

Image::~Image()
{
	delete sourcebmp;
}

void Image::showImage()
{
	for (int dy = 0; dy < height; dy++)
	{
		for (int dx = 0; dx < width; dx++)
		{
			if (sourcebmp->data[dy][dx] ==  '0')
			{
				gotoxy(dx + x, dy + y);
				printf("█");
			}
		}
	}
}

void Image::clearImage()
{
	for (int dy = 0; dy < height; dy++)
	{
		for (int dx = 0; dx < width; dx++)
		{
			if (sourcebmp->data[dy][dx] == '0')
			{
				gotoxy(dx + x, dy + y);
				printf(" ");
			}
		}
	}
}
