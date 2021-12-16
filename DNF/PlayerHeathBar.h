#pragma once
#include "GameEntity.h"

class Image;
class PlayerHealthBar : public GameEntity
{
public:
	PlayerHealthBar(const wstring path, POINT pos) noexcept;
	virtual ~PlayerHealthBar() noexcept = default;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void SetRemainingAmount(float value) noexcept;
private:
	Image* mpHealthBar = nullptr;
	float mRemainingAmount = 100.0f;
	POINT mPos = {};
};

