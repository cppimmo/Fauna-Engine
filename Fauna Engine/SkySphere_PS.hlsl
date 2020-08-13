TextureCube tex;
SamplerState samp;

struct PS_IN
{
	float4 pos : SV_POSITION;
	float3 texCoord : TEXCOORD;
};

float4 main(PS_IN i) : SV_TARGET
{
	return tex.Sample(samp, i.texCoord);
}