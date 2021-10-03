#include "DXUT.h"
#include "Input.h"

void Input::Init()
{
	SetKeyboardState(curKey);
}

void Input::Update()
{
	memcpy(oldKey, curKey, sizeof(oldKey));

	memset(curKey, 0, sizeof(curKey));
	memset(keyMap, 0, sizeof(keyMap));

	GetKeyboardState(curKey);

	for (int i = 0; i < 256; ++i)
	{
		BYTE key = curKey[i] & 0x80;
		curKey[i] = (key) ? 1 : 0;

		if (oldKey[i] == 0 && curKey[i] == 1) keyMap[i] = InputState::INPUT_DOWN;
		else if (oldKey[i] == 1 && curKey[i] == 0) keyMap[i] = InputState::INPUT_UP;
		else if (oldKey[i] == 1 && curKey[i] == 1) keyMap[i] = InputState::INPUT_PRESS;
		else keyMap[i] = InputState::INPUT_NONE;
	}
}

bool Input::KeyDown(int key)
{
	return keyMap[key] == InputState::INPUT_DOWN;
}

bool Input::keyUp(int key)
{
	return keyMap[key] == InputState::INPUT_UP;
}

bool Input::KeyPress(int key)
{
	return keyMap[key] == InputState::INPUT_PRESS;
}
