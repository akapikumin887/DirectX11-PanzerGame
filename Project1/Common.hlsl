

//�}�g���N�X�o�b�t�@
cbuffer WorldBuffer : register(b0)
{
	matrix World;
}
cbuffer ViewBuffer : register(b1)
{
	matrix View;
}
cbuffer ProjectionBuffer : register(b2)
{
	matrix Projection;
}


struct VS_IN
{
	float4 Position		: POSITION0;
	float4 Normal		: NORMAL0;
	float4 Diffuse		: COLOR0;
	float2 TexCoord		: TEXCOORD0;
};

struct PS_IN
{
	float4 Position			: SV_POSITION;
	float4 WorldPosition	: POSITION0;
	float4 Normal			: NORMAL0;
	float4 Diffuse			: COLOR0;
	float2 TexCoord			: TEXCOORD0;
};

//�}�e���A���o�b�t�@
struct Material
{
    float4  Ambient;
    float4  Diffuse;
    float4  Specular;
    float4  Emission;
    float   Shininess;
    float3  Dummy;
};

cbuffer MaterialBuffer : register(b3)
{
    Material _Material;
}

//���C�g�o�b�t�@
struct LIGHT
{
    bool Enable;
    bool3 Dummy;    //16byte�̋��E�p
    float4 Direction;
    float4 Diffuse;
    float4 Ambient;
};

cbuffer LightBuffer : register(b4)
{
    LIGHT _Light;
}


cbuffer CameraBuffer : register(b5)
{
    float4 CameraPosition;
}

cbuffer ParameterBuffer : register(b6)
{
    float4 Parameter;
}


cbuffer cbPerObject
{
    float4x4 WVP;
    float4x4 world;
};

struct SkyMapVS_Output
{
    float4 pos : SV_Position;
    float3 texcoord : TEXCOORD;
};
