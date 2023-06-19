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

VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.f;

    float4 worldPosition = mul(In.Pos, world);
    float4 viewPosition = mul(worldPosition, view);
    float4 projPosition = mul(viewPosition, projection);
    
    Out.WorldPos = worldPosition;
    Out.Pos = projPosition;
    Out.Color = In.Color;
    Out.UV = In.UV;
    
    if (useRate == 1)
    {
        Out.Pos.x = Out.Pos.x * imageRate.x;
        Out.Pos.y = Out.Pos.y * imageRate.y;
    }
    
    return Out;
}