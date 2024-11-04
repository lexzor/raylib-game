#pragma once
#include <cstdint>

class Component
{
public:
	virtual ~Component() = default;
	virtual void OnUpdate() = 0;

	void SetDrawable(bool value)
	{
		m_Drawable = value;
	}

	bool IsDrawable() const
	{
		return m_Drawable;
	}

private:
	bool m_Drawable = false;
};