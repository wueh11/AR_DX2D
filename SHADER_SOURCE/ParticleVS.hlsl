#include "globals.hlsli"

struct VSIn
{
    float4 Pos : POSITION;
    uint iInstance : SV_InstanceID; /// ���° ��ü���� �ڵ����� ����
};

struct VSOut /// ParticleGS�� �Ѿ
{
    float4 Pos : SV_Position;
    uint iInstance : SV_InstanceID;
};

VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.0f;
    
    Out.Pos = In.Pos;
    Out.iInstance = In.iInstance;
    
    //float3 worldPos = (In.Pos.xyz * 50.0f) + world._41_42_43 + particleBuffer[In.iInstance].position.xyz;
    
    //float4 viewPos = mul(float4(worldPos, 1.0f), view);
    //Out.Pos = mul(viewPos, projection);
    
    return Out;

}