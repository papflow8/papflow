#include	"Bitmap.h"

using namespace std;

map<string, Bitmap> Bitmap::bitmapCache;



void Bitmap::readFromFile(string fileName) {
	string fileData = "";
	height = 0; width = 0;
	fstream file;
	file.open(fileName, ios::in);
	char c;
	file >> noskipws;
	while (!file.eof()) {
		file >> c;
		if (c == '\n') height++;
		else { if (height == 0) width++; fileData += c; }
	}
	data = new char*[++height];
	for (int i = 0, y = 0; y < height; y++) {
		data[y] = new char[width];
		for (int x = 0; x < width; x++)
			data[y][x] = fileData[i++];
	}
	file.close();
}

Bitmap* Bitmap::getBitmap(string str) {
	if (bitmapCache.count(str) <= 0) bitmapCache[str] = Bitmap(str);
	return &bitmapCache[str];
}

int Bitmap::getWidth() {
	return width;
}
int Bitmap::getHeight() { return height; }

Bitmap::Bitmap()
{
	width = height = 0;
}

Bitmap::Bitmap(string fileName)
{
	url = fileName;
	readFromFile(url);
}

Bitmap::Bitmap(int width, int height) {
	url = "custom";
	createEmpty(width, height);
}

void Bitmap::createEmpty(int width, int height)
{
	this->width = width;
	this->height = height;

	data = new char*[height];
	for (int y = 0; y < height; y++) {
		data[y] = new char[width];
		for (int x = 0; x < width; x++) data[y][x] = 'T';
	}
}

void Bitmap::paint(int x, int y, char c)
{
	if (x >= 0 && y < width && y >= 0 && y < height)
	{
		data[y][x] = c;
	}
}

void BitmapInit()
{
	Wall = Bitmap::getBitmap("../HEW_Miracle/ASCII-GroundWithGrass.txt");
	Kid_Idle = Bitmap::getBitmap("../HEW_Miracle/ASCII-Kid_Idle_Animation.txt");
	Kid_Walk = Bitmap::getBitmap("../HEW_Miracle/ASCII-Kid_Walk.txt");
	GameOverBmp = Bitmap::getBitmap("../HEW_Miracle/ASCII-GameOver.txt");
	SavePointBmp = Bitmap::getBitmap("../HEW_Miracle/ASCII-SavePoint.txt");
	PortalBmp = Bitmap::getBitmap("../HEW_Miracle/ASCII-Iwanna_portal.txt");
	Hint1Bmp = Bitmap::getBitmap("../HEW_Miracle/ASCII-Hint1.txt");
	RainbowBallBmp = Bitmap::getBitmap("../HEW_Miracle/ASCII-Ball.txt");
	MiracleBmp = Bitmap::getBitmap("../HEW_Miracle/ASCII-Miracle.txt");
	EndBmp = Bitmap::getBitmap("../HEW_Miracle/ASCII-END.txt");
	/*for (int dy = 0; dy < TILE_HEIGHT; dy++)
	{
		for (int dx = 0; dx < TILE_WIDTH; dx++)
		{
			Wall->paint(dx, dy, Wall->data[dy][dx]);
		}
	}*/

	

}
