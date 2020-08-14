
cbuffer ConstantBuffer
{
	float4x4 WVP;
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float3 texCoord : TEXCOORD;
};

VS_OUT main(float3 inPos : POSITION, float2 inTexCoord : TEXCOORD)
{	
	VS_OUT vso = (VS_OUT)0;
	vso.pos = mul(float4(inPos, 1.0f), WVP).xyww;
	//make sure that the depth after w divide will be 1.0 (so that the z-buffer
	vso.texCoord = inPos;
	return vso;
}