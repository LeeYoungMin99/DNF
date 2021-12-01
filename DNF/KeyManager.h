#pragma once
#include <bitset>
#include "Singleton.h"

#define KEY_MAX_COUNT	256

class KeyManager : public Singleton<KeyManager>
{
private:
	bitset<KEY_MAX_COUNT>	keyUp;	
	bitset<KEY_MAX_COUNT>	keyDown;

public:
	virtual ~KeyManager() = default;

	void Init();
	void Release();

	bool IsOnceKeyDown(int key);
	bool IsOnceKeyUp(int key);	
	bool IsStayKeyDown(int key);
};

