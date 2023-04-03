#include "globals.hlsli"

struct VSIn
{
    float4 Pos : POSITION;
    uint iInstance : SV_InstanceID; /// 몇번째 물체인지 자동으로 들어옴
};

struct VSOut /// ParticleGS로 넘어감
{
    float4 Pos : SV_Position;
    uint iInstance : SV_InstanceID;
};

VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.0f;
    
    Out.Pos = In.Pos;
    Out.iInstance = In.iInstance;
    
    return Out;

}