#pragma once

enum class InputState
{
	INPUT_NONE,
	INPUT_DOWN,
	INPUT_UP,
	INPUT_PRESS
};

class Input : public Singleton<Input>
{
private:
	BYTE curKey[256] = {};
	BYTE oldKey[256] = {};
	InputState keyMap[256] = {};

public:
	D3DXVECTOR2 mousePos = { 0, 0 };

	void Init();
	void Update();
	
	bool KeyDown(int key);
	bool keyUp(int key);
	bool KeyPress(int key);

};

