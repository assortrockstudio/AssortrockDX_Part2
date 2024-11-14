#ifndef _STD2D
#define _STD2D

cbuffer TRANSFORM : register(b0)
{
    float4 g_Position;
    float4 g_Scale;
};


SamplerState g_sam_0 : register(s0);
SamplerState g_sam_1 : register(s1);


Texture2D g_tex : register(t0);



struct VS_IN
{
    float3 vPos : POSITION;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};

VS_OUT VS_Std2D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;

    output.vPosition = float4((_in.vPos * g_Scale.xyz) + g_Position.xyz, 1.f);
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_Std2D(VS_OUT _in) : SV_Target
{        
    float4 vColor = g_tex.Sample(g_sam_0, _in.vUV);    
    return vColor;
}

#endif