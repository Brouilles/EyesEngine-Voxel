

float4x4 WorldViewProj : WorldViewProjection;
Texture2D MeshTexture; // Color texture for mesh

SamplerState MeshTextureSampler
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

struct VS_INPUT
{
	float3 Position : POSITION0;
	float2 TextureUV : TEXCOORD0;
	float4 Color : COLOR0;
};

struct VS_OUTPUT
{
	float4 NewPosition : POSITION0;
	float4 InterpolatedColor : COLOR0;
};

VS_OUTPUT mainVS(VS_INPUT vsIn)
{
	VS_OUTPUT vsOut;

	vsOut.NewPosition = mul(float4(vsIn.Position, 1.0f), WorldViewProj);
	vsOut.InterpolatedColor = vsIn.Color;

	return vsOut;
}

float4 mainPS(VS_OUTPUT psIn) : COLOR
{
	//return psIn.InterpolatedColor;
	return MeshTexture.Sample(MeshTextureSampler, In.TextureUV);
}

technique technique0 {
	pass p0 {
		CullMode = None;
		VertexShader = compile vs_3_0 mainVS();
		PixelShader = compile ps_3_0 mainPS();
	}
}
