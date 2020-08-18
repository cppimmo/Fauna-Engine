#pragma once

#include "Graphics/Graphics.h"

//bindable interface
class Binder
{
public:
	Binder(Graphics& gfx) : gfx(gfx) {}

	virtual void bind() = 0;
	virtual void unbnd() = 0;
protected:
	Graphics& gfx;
};

