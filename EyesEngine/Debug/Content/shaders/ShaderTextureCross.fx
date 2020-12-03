float4x4 WorldViewProj : WorldViewProjection;

Texture2D shaderTexture;
sampler SampleType;

struct VS_INPUT
{
	float3 Position : POSITION0;
	float2 TextureCoord : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 NewPosition : POSITION0;
	float2 NewTextureCoord : TEXCOORD0;
};

VS_OUTPUT mainVS(VS_INPUT vsIn)
{
	VS_OUTPUT vsOut;

	vsOut.NewPosition = mul(float4(vsIn.Position, 1.0f), WorldViewProj);
	vsOut.NewTextureCoord = vsIn.TextureCoord;

	return vsOut;
}

float4 mainPS(VS_OUTPUT psIn) : SV_TARGET
{
	float4 textureColor;
	textureColor = tex2D(SampleType, psIn.NewTextureCoord); 

	return textureColor;
}

technique technique0 {
	pass p0 {
		CullMode = None;
		AlphaBlendEnable = true;
		VertexShader = compile vs_3_0 mainVS();
		PixelShader = compile ps_3_0 mainPS();
	}
}
