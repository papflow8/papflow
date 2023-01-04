#pragma once
#define		CONIOEX
#include	"Key.h"

static class InputManager
{
public:
	static void KeyInit();
	static void KeyUpdate_Add(Key &_key);
	static bool IsPressing(Key &_key);
	static bool OnPressed(Key &_key);
	static bool IsExtending(Key &_key);
	static bool OnReleased(Key &_key);

	static bool GetLastState(Key &_key);

	static Key k_W;
	static Key k_A;
	static Key k_S;
	static Key k_D;
	static Key k_R;
	static Key k_V;
	static Key k_SPACE;
private:
	
};

void InputInit();
void InputUpdate();
void InputDraw_test();
