#pragma once
#include "Component.h"

class Animation;
class newAnimatorComponent : public Component
{
public:
	using Component::Component;
	virtual ~newAnimatorComponent() noexcept;

	virtual void Update() override;

    void        AddParameterBool(const wstring& name, bool value)
    {
        mBoolParams[name] = value;
    }

    void        SetBool(const wstring& name, bool value)
    {
        if (mBoolParams.end() != mBoolParams.find(name))
        {
            mBoolParams[name] = value;
        }
    }

    bool        GetBool(const wstring& name)
    {
        return mBoolParams[name];
    }

	Animation* GetCurrAnim() noexcept;
private:
	unordered_map<wstring, bool> mBoolParams;
	vector<vector<Animation*>> mpAnimationGraph = {};
	Animation* mpCurrAnim = nullptr;
};

