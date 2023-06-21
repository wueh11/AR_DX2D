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
    float3 WorldPos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

float4 main(VSOut In) : SV_Target
{
    float4 color = (float) 0.0f;
    
     /**** Sprite 사이즈 계산 ***/
    if (animationType == 1) // 2D
    {
        float2 diff = (atlasSize - spriteSize) / 2.0f;
        float2 UV = (leftTop - diff - offset) + (atlasSize * In.UV);
        
        if (UV.x < leftTop.x || UV.y < leftTop.y 
            || UV.x > leftTop.x + spriteSize.x 
            || UV.y > leftTop.y + spriteSize.y)
            discard;

        color = atlasTexture.Sample(pointSampler, UV);
    }
    else if (animationType == 2)
    {
    }
    else
    {
        color = atlasTexture.Sample(pointSampler, In.UV);
    }
     
    /***** 빛 계산 *****/
    if (numberOfLight > 0)
    {
        LightColor lightColor = (LightColor) 0.0f;
        for (int i = 0; i < numberOfLight; i++)
        {
            CalculateLight(lightColor, In.WorldPos.xyz, i);
        }
    
        color *= lightColor.diffuse;
    }
    
    if (color.a <= 0.0f)
        discard;
    
        if (useRange == 1 && (In.UV.x < imageRange.x || In.UV.x > imageRange.z || In.UV.y < imageRange.y || In.UV.y > imageRange.w))
            discard;
    
    if (imageAlpha > 0.0f && color.a > 0.0f)
        color.a = imageAlpha;
    
    if (colorType == 1)
    {
        if (color.a > 0.0f)
            color = imageColor;
    }
    else if (colorType == 2)
    {
        color.r += imageColor.x * imageColor.w;
        color.g += imageColor.y * imageColor.w;
        color.b += imageColor.z * imageColor.w;
    }
        
    return color;
}