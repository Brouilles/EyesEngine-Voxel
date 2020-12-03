

float4x4 WorldViewProj : WorldViewProjection;

texture MeshTexture;
sampler2D MeshTextureSampler = sampler_state {
	Texture = (MeshTexture);
	MinFilter = Linear;
	MagFilter = Linear;
	AddressU = Clamp;
	AddressV = Clamp;
};

struct VS_INPUT
{
	float3 Position : POSITION0;
	float2 TextureUV : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 NewPosition : POSITION0;
	float2 NewUV : TEXCOORD1;
};

VS_OUTPUT mainVS(VS_INPUT vsIn)
{
	VS_OUTPUT vsOut;

	vsOut.NewPosition = mul(float4(vsIn.Position, 1.0f), WorldViewProj);
	vsOut.NewUV = vsIn.TextureUV;

	return vsOut;
}

float4 mainPS(VS_OUTPUT psIn) : COLOR0
{
	float4 textureColor = tex2D(MeshTextureSampler, psIn.NewUV);
	textureColor.a = 1;
	//textureColor.r = 255;

	return textureColor;
}

technique technique0 {
	pass p0 {
		CullMode = CCW;
		VertexShader = compile vs_3_0 mainVS();
		PixelShader = compile ps_3_0 mainPS();
	}
}
