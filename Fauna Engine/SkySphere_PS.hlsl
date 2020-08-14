TextureCube tex;
SamplerState samp;

struct VS_OUT
{
	float4 pos : POSITION;
	float3 texCoord : TEXCOORD;
};

float4 main(VS_OUT input) : SV_TARGET
{
	//return (1.0f, 1.0f, 1.0f, 1.0f);
	return tex.Sample(samp, input.texCoord);
}