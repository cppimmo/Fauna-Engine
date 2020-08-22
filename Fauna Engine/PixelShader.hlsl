cbuffer PSConstantBuffer 
{
	float3 camPos;
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float2 texCoord : TEXCOORD;
};

Texture2D doritoTexture;
SamplerState samplerState;

float4 main(VS_OUT vso) : SV_TARGET
{
	/*float fogStart = 100;	
	float fogEnd = 200;
	float4 fogColor = float4(0.9f, 0.9f, 0.9f, 1.0f);
	//toEye vector used for lighting
	float3 toEye = camPos - float3(vso.pos.x, vso.pos.y, vso.pos.z);
	float distToEye = length(toEye);
	toEye /= distToEye;
	float fogLerp = saturate((distToEye - fogStart) / fogEnd);
	diffuse = lerp(diffuse, fogColor, fogLerp);
	//float4 color = lerp(color, fogColor, fogLerp);
	//diffuse = lerp(diffuse, fogColor, fogLerp);*/
	float4 diffuse = doritoTexture.Sample(samplerState, vso.texCoord);
	clip(diffuse.a - .25);
	return diffuse;
}