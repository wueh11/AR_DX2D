#include "globals.hlsli"

struct VSIn   ///���� ������
{
    float4 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut  /// �������� ������
{
    float4 Pos : SV_Position;
    float3 WorldPos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

float4 main(VSOut In) : SV_Target
{
    float4 color = (float) 0.0f;
    
     /**** Sprite ������ ��� ***/
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
    
    /***** �� ��� *****/
    if (numberOfLight > 0)
    {
        LightColor lightColor = (LightColor) 0.0f;
        for (int i = 0; i < numberOfLight; i++)
        {
            CalculateLight(lightColor, In.WorldPos.xyz, i);
        }
    
        color *= lightColor.diffuse;
    }
    
    return color;
}