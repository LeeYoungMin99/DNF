#pragma once
#include "GameEntity.h"

class AnimatorComponent;
class Transition : public GameEntity
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	AnimatorComponent* mpAnimComp = nullptr;
};
