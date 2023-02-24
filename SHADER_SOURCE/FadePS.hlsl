#include "globals.hlsli"

struct VSIn
{
    float4 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

float4 main(VSOut In) : SV_TARGET
{
    const float alpha = (float) cbfData;
    
   // float4 fade = float4(0.0f, 0.0f, 0.0f, alpha);
    float4 fade = float4(In.Color.xyz, alpha);

    return fade;
}