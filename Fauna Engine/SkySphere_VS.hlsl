
cbuffer ConstantBuffer
{
	float4x4 WVP;
};

struct VS_IN 
{
	float3 pos : POSITION;
};

struct PS_IN
{
	float4 pos : SV_POSITION;
	float3 texCoord : TEXCOORD;
};

PS_IN main(VS_IN i)
{	
	PS_IN toPS = (PS_IN)0;
	toPS.pos = mul(float4(i.pos, 1.0f), WVP).xyww;
	//make sure that the depth after w divide will be 1.0 (so that the z-buffer
	toPS.texCoord = i.pos;
	return toPS;
}