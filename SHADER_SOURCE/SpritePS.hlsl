#include "globals.hlsli"

struct VSIn   ///들어올 데이터
{
    float4 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut  /// 내보내줄 데이터
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

float4 main(VSOut In) : SV_Target
{
    float4 color = (float) 0.0f;
    
    if (animationType == 1) // 2D
    {
        float2 diff = (atlasSize - spriteSize) / 2.0f;
        float2 UV = (leftTop - diff - offset) + (atlasSize * In.UV);
        
        if (UV.x < leftTop.x || UV.y < leftTop.y 
            || UV.x > leftTop.x + spriteSize.x 
            || UV.y > leftTop.y + spriteSize.y)
            discard;
        
        color = atlasTexture.Sample(anisotropicSampler, UV);
    }
    else if (animationType == 2)
    {
    }
    else
    {
        color = atlasTexture.Sample(anisotropicSampler, In.UV);
    }
    
    return color;
}