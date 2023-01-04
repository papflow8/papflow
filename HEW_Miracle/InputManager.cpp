#include	"InputManager.h"
#include	"player.h"


Key InputManager::k_W = Key("W", PK_W);
Key InputManager::k_A = Key("A", PK_A);
Key InputManager::k_S = Key("S", PK_S);
Key InputManager::k_D = Key("D", PK_D);
Key InputManager::k_R = Key("R", PK_R);
Key InputManager::k_V = Key("V", PK_V);

Key InputManager::k_SPACE = Key("Space", PK_SP);




void InputManager::KeyInit()
{

}

void InputManager::KeyUpdate_Add(Key &_key)
{
	_key.Key_LastState = _key.Key_Pressing;
	_key.Key_Pressing = IsPressing(_key);
	_key.Key_OnPressed = OnPressed(_key);
	_key.Key_IsExtending = IsExtending(_key);
	_key.Key_OnReleased = OnReleased(_key);
}

bool InputManager::IsPressing(Key &_key)
{
	/*if (inport(_key.Key_Value))
	{
		return true;
	}
	return false;*/
	return inport(_key.Key_Value);
}

bool InputManager::OnPressed(Key &_key)
{
	//bool _lastState = _key.Key_LastState;
	//bool _curState = _key.Key_Pressing;
	if (_key.Key_LastState != _key.Key_Pressing && _key.Key_Pressing == true)
	{
		return true;
	}
	return false;
}

bool InputManager::IsExtending(Key & _key)
{
	//bool _lastState = _key.Key_LastState;
	//bool _curState = _key.Key_Pressing;
	if (_key.Key_LastState == _key.Key_Pressing && _key.Key_Pressing == true)
	{
		return true;
	}
	return false;
}

bool InputManager::OnReleased(Key & _key)
{
	if (_key.Key_LastState != _key.Key_Pressing && _key.Key_Pressing == false)
	{
		return true;
	}
	return false;
}

bool InputManager::GetLastState(Key &_key)
{
	return _key.Key_LastState;
}



void InputInit()
{
	InputManager::KeyInit();
}

void InputUpdate()
{
	InputManager::KeyUpdate_Add(InputManager::k_W);
	InputManager::KeyUpdate_Add(InputManager::k_A);
	InputManager::KeyUpdate_Add(InputManager::k_S);
	InputManager::KeyUpdate_Add(InputManager::k_D);
	InputManager::KeyUpdate_Add(InputManager::k_R);
	InputManager::KeyUpdate_Add(InputManager::k_V);
	InputManager::KeyUpdate_Add(InputManager::k_SPACE);
}

void InputDraw_test()
{
	textcolor(WHITE);
	gotoxy(0, 0);
	printf("\nKEY_D:\nLastState = %d\nPressing = %d\nOnPressed = %d\nIsExtending = %d\nOnReleased = %d\n", 
		InputManager::k_D.Key_LastState, InputManager::k_D.Key_Pressing, InputManager::k_D.Key_OnPressed, InputManager::k_D.Key_IsExtending, InputManager::k_D.Key_OnReleased);
}

