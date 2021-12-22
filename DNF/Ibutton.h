#pragma once

struct IButton
{
	virtual void OnClick() = 0;
	virtual void OnIdle() = 0;
	virtual void OnHover() = 0;
	virtual void OnExecute() = 0;
};
