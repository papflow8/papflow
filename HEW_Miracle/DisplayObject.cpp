#include<algorithm>

#include "DisplayObject.h"
#include "Sprite.h"

int DisplayObject::getWidth() { return width; }
int DisplayObject::getHeight() { return height; }


bool DisplayObjectComp(const DisplayObject* a, const DisplayObject* b) {
	return (a->z == b->z) ? a->y < b->y : a->z < b->z;
}
//void DisplayObject::update() {
//	updateChildren(); updateOthers();
//}
//void DisplayObject::updateChildren() {
//	for (int i = 0; i < backChildren.size(); i++) {
//		DisplayObject* obj = backChildren[i];
//		obj->update();
//	}
//	for (int i = 0; i < children.size(); i++) {
//		DisplayObject* obj = children[i];
//		obj->update();
//	}
//}
//void DisplayObject::updateOthers() {}
//vector<vector<char> > DisplayObject::getDisplayData() {
//	vector<vector<char> > res; return res;
//}
//void DisplayObject::render(char** map, int lx, int ly) {
//	if (!visible) return;
//
//	for (int i = 0; i < backChildren.size(); i++) {
//		DisplayObject* obj = backChildren[i];
//		int ox = obj->x; int oy = obj->y;
//		obj->render(map, lx + ox, ly + oy);
//	}
//
//	vector<vector<char> > data = getDisplayData();
//	for (int y = 0; y < data.size(); y++)
//		for (int x = 0; x < data[y].size(); x++) {
//			if (data[y][x] != 'T')
//				map[ly + y][lx + x] = data[y][x];
//		}
//
//	for (int i = 0; i < children.size(); i++) {
//		DisplayObject* obj = children[i];
//		int ox = obj->x; int oy = obj->y;
//		obj->render(map, lx + ox, ly + oy);
//	}
//}
//void DisplayObject::render(Stage* stage, int lx, int ly) {
//	if (!visible) return;
//
//	for (int i = 0; i < backChildren.size(); i++) {
//		DisplayObject* obj = backChildren[i];
//		int ox = obj->x; int oy = obj->y;
//		obj->render(stage, lx + ox, ly + oy);
//	}
//
//	vector<vector<char> > data = getDisplayData();
//	for (int y = 0; y < data.size(); y++)
//		for (int x = 0; x < data[y].size(); x++) {
//			if (data[y][x] != 'T')
//				stage->paint(lx + x, ly + y, data[y][x]);
//		}
//
//	for (int i = 0; i < children.size(); i++) {
//		DisplayObject* obj = children[i];
//		int ox = obj->x; int oy = obj->y;
//		obj->render(stage, lx + ox, ly + oy);
//	}
//}
//void DisplayObject::quickRender(char**& map, int lx, int ly) {}
void DisplayObject::addChild(DisplayObject* obj) {
	children.push_back(obj);
	obj->parent = this;
	sort(children.begin(), children.end(), DisplayObjectComp);
}
void DisplayObject::removeChild(DisplayObject* obj) {
	vector<DisplayObject*>::iterator pos;
	pos = find(children.begin(), children.end(), obj);
	if (pos != children.end()) children.erase(pos);
}
void DisplayObject::clearChildren() { children.clear(); }

