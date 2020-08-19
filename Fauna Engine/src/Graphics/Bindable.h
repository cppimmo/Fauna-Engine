#pragma once

class Graphics;
//bindable interface
class Bindable
{
public:
	virtual ~Bindable() = default;
	virtual void Bind(Graphics& gfx) = 0;
	virtual void Unbind(Graphics& gfx) = 0;
};

