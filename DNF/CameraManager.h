#pragma once
#include "Singleton.h"
#include "GameEntity.h"

class CameraManager : public Singleton<CameraManager>, public GameEntity
{
public:
	CameraManager() = default;
	virtual ~CameraManager() noexcept = default;

	LONG GetX();
	LONG GetY();
	void SetCameraPos(LONG posX, LONG posY);
	void AddX(LONG x);
	void AddY(LONG y);
	void SetCameraMaxPos(LONG maxX, LONG maxY);
	void SetCameraMinPos(LONG minX, LONG minY);

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
private:
	POINT mPos = {};
	POINT mMaxPos = {};
	POINT mMinPos = {};
};

