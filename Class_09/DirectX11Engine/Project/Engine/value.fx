#ifndef _VALUE
#define _VALUE

cbuffer TRANSFORM : register(b0)
{
    row_major matrix g_matWorld;
    row_major matrix g_matView;
    row_major matrix g_matProj;
};

cbuffer MATERIAL_CONST : register(b1)
{
    int         g_int_0;
    int         g_int_1;
    int         g_int_2;
    int         g_int_3;
    
    float       g_float_0;
    float       g_float_1;
    float       g_float_2;
    float       g_float_3;    
    
    float2      g_vec2_0;
    float2      g_vec2_1;
    float2      g_vec2_2;
    float2      g_vec2_3;
    
    float4      g_vec4_0;
    float4      g_vec4_1;
    float4      g_vec4_2;
    float4      g_vec4_3;
    
    Matrix      g_mat_0;
    Matrix      g_mat_1;
    Matrix      g_mat_2;
    Matrix      g_mat_3;
}




SamplerState g_sam_0 : register(s0);
SamplerState g_sam_1 : register(s1);

Texture2D g_tex : register(t0);


#endif