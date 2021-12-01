#pragma once
#include <time.h>

class Timer
{
private:
	bool isHardware = false;			// ���� Ÿ�̸Ӹ� �� �� �ִ��� ����
	__int64	periodFrequency = 0;		// ���� Ÿ�̸��� ���ļ�( �ʴ� ������ ), �������� ������ 0
	float timeScale = 0.0f;				// 1�ʸ� �ʴ� �������� ������ ��� �������� �ð������� ��ȯ
	__int64 currTime = 0;				// ���� ���� ������ (���� �ð�)
	__int64 lastTime = 0;				// ���� ���� ������ (���� �ð�)
	float deltaTime = 0.0f;				// ��� �ð� (currTime - lastTime) * timeScale

	float fpsTimeElapsed = 0.0f;		// ������ ��� �ð�
	unsigned long fpsFrameCount = 0;	// �ʴ� ������ ��
	unsigned long fps = 0;

public:
	~Timer() = default;

	void Init();
	void Tick();

	inline unsigned long GetFPS() { return fps; }
	inline float GetDeltaTime() { return deltaTime; }

};

