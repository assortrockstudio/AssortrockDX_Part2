#ifndef _STD2D
#define _STD2D

cbuffer TRANSFORM : register(b0)
{
    row_major matrix g_matWorld;
    row_major matrix g_matView;
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

    // 행렬을 곱할때 3차원 좌표를 4차원으로 확장(동차좌표)
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWorld);
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