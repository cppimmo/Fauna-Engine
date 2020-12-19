#pragma once

#include <Graphics/Graphics.h>
#include <Graphics/VertexBuffer.h>
#include <Graphics/IndexBuffer.h>
#include <Graphics/Texture.h>

class Model
{
public:
	Model();
	~Model();

	bool Init();

	void Draw();
	void Update(float dt);

	void SetAnim(int type);
private:

};