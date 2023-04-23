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

float4 main(VSOut In) : SV_Target
{
    float4 color = (float) 0.0f;
    color = defaultTexture.Sample(pointSampler, In.UV);

    //if (cbxyzw.xyzw != float4(0.0f, 0.0f, 0.0f, 0.0f))
    //{
    //    if (In.UV.x < cbxyzw.x || In.UV.x > cbxyzw.z || In.UV.y < cbxyzw.y || In.UV.y > cbxyzw.w)
    //        discard;
    //}
    
    return color;
}