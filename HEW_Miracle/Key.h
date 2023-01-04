#pragma once

#define		CONIOEX
#include	"main.h"
#include	<string>;
using namespace std;

class Key
{
public:

	Key() {};
	Key(string _name, int _value) : Key_Pressing(false), Key_OnPressed(false), Key_OnReleased(false)
	,Key_LastState(false), Key_IsExtending(false), Key_Value(_value)
	{
		
	};

	int Key_Value;
	float Key_Cd;
	bool Key_OnPressed;
	bool Key_Pressing;
	bool Key_OnReleased;
	bool Key_LastState;
	bool Key_IsExtending;
	string Key_Name;
	
};