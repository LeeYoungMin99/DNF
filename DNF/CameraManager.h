#pragma once
#include "Singleton.h"
#include "IBehaviour.h"

class Player;
class CameraManager : public Singleton<CameraManager>, public IBehaviour
{
public:
	CameraManager() = default;
	virtual ~CameraManager() = default;

	virtual void Init() override {}
	virtual void Render() override {}
	virtual void Release() override {}

	virtual void Update() override;

	LONG		GetX() const { return _pos.x; }
	LONG		GetY() const { return _pos.y; }

	void		SetCameraPos(const LONG& posX, const LONG& posY);
	void		SetCameraMaxPos(const LONG& maxX, const LONG& maxY);
	void		SetCameraMinPos(const LONG& minX, const LONG& minY);
	void		SetPlayer(Player* player) { _player = player; }

	void		AddX(const LONG& x);
	void		AddY(const LONG& y);
private:
	POINT		_pos = {};
	POINT		_maxPos = {};
	POINT		_minPos = {};
	Player*		_player = nullptr;
};

