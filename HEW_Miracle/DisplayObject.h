#pragma once
#include<vector>

#include "Rect.h"
using namespace std;
class DisplayObject {
public:

	//virtual vector<vector<char> > getDisplayData();
	//void update();
	//void render(Stage* stage, int lx, int ly);
	//void render(char** map, int lx, int ly);
	//virtual void quickRender(char**& map, int lx, int ly);
	bool visible;
	int x, y, z;

	void addChild(DisplayObject* obj);
	void removeChild(DisplayObject* obj);
	void clearChildren();

	virtual int getWidth();
	virtual int getHeight();
private:
	//void updateChildren();
protected:
	//virtual void updateOthers();

	DisplayObject* parent;
	vector<DisplayObject*> children;
	vector<DisplayObject*> backChildren;
	int width, height;
};
//bool DisplayObjectComp(const DisplayObject* a, const DisplayObject* b);