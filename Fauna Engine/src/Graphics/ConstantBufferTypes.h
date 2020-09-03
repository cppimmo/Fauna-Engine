#pragma once

#include <DirectXMath.h>

struct CB_WVP 
{
	DirectX::XMMATRIX WVP;
};

struct CB_CamPos 
{
	DirectX::XMFLOAT3 camPos;
};

struct CB_Fog 
{
	float fogStart;
	float fogEnd;
	DirectX::XMFLOAT4 fogColor;
};

struct CB_DirectionalLight 
{
	DirectX::XMFLOAT4 Ambient;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT4 Direction;
	float Pad;
};

struct CB_PointLight 
{
	DirectX::XMFLOAT4 Ambient;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT4 Specular;
	
	DirectX::XMFLOAT3 Position;
	float Range;
	DirectX::XMFLOAT3 Att;
	float Pad;
};

struct CB_SpotLight 
{
	
};
