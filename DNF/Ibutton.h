#pragma once

struct IButton
{
	virtual void OnExecuteToClick() = 0;
	virtual void OnExecuteToIdle() = 0;
};
