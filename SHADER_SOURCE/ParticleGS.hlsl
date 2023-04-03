#include "globals.hlsli"

struct VSOut /// VS에서 받아옴
{
    float4 Pos : SV_Position;
    uint iInstance : SV_InstanceID;
};

struct GSOutput
{
	float4 Pos : SV_POSITION;
    float2 UV : TEXCOORD;
};


[maxvertexcount(6)] /// 삼각형두개붙여서 사각형 만들거기 때문에..
void main(
    point VSOut input[1] : SV_POSITION,     /// point -> 삼각형이아니라 점으로 처리하기때문에 point input[1] 사용
    inout TriangleStream<GSOutput> output 
)
{
    GSOutput Out[4] = { (GSOutput) 0.0f, (GSOutput) 0.0f, (GSOutput) 0.0f, (GSOutput) 0.0f };
    
    if (0 == particleBuffer[input[0].iInstance].active)
        return;
    
    float3 vWorldPos = input[0].Pos.xyz + particleBuffer[input[0].iInstance].position.xyz;
    float3 vViewPos = mul(float4(vWorldPos, 1.0f), view);
    
    /// point 점 좌표를 사각형모양으로 셋팅해줘야한다
    float3 NewPos[4] =
    {
        vViewPos - float3(-0.5f, 0.5f, 0.0f) * float3(50.0f, 50.0f, 1.0f)
        , vViewPos - float3(0.5f, 0.5f, 0.0f) * float3(50.0f, 50.0f, 1.0f)
        , vViewPos - float3(0.5f, -0.5f, 0.0f) * float3(50.0f, 50.0f, 1.0f)
        , vViewPos - float3(-0.5f, -0.5f, 0.0f) * float3(50.0f, 50.0f, 1.0f)
    };
    
    for (int i = 0; i < 4; i++)
    {
        Out[i].Pos = mul(float4(NewPos[i], 1.0f), projection);
    }
    
    Out[0].UV = float2(0.0f, 0.0f);
    Out[1].UV = float2(1.0f, 0.0f);
    Out[2].UV = float2(1.0f, 1.0f);
    Out[3].UV = float2(0.0f, 1.0f);
    
    // 0 -- 1
    // | \  |
    // 3 -- 2
    
    output.Append(Out[0]);
    output.Append(Out[1]);
    output.Append(Out[2]);
    output.RestartStrip();
    
    output.Append(Out[0]);
    output.Append(Out[2]);
    output.Append(Out[3]);
    output.RestartStrip();
}