#include "Light.hlsli"
#include "Particle.hlsli"

cbuffer Transform : register(b0) /// 슬롯 번호. 그래픽카드에서 사용할 수잇는 상수버퍼 슬롯
{
    row_major matrix world; /// 월드
    row_major matrix view; /// 카메라
    row_major matrix projection; /// 원근나누기가 진행되지않은 투영좌표
    /// row_major. column_major -> 열우선, 행우선 지정
}

cbuffer MaterialData : register(b1)
{
    int cbiData;
    float cbfData;
    float2 cbxy;
    float3 cbxyz;
    float4 cbxyzw;
    matrix cbmat;
}

cbuffer Grid : register(b2) /// 상수버퍼 크기 16byte로 맞춰야....
{
    float4 cameraPosition;
    float2 cameraScale;
    float2 resolution;
}

cbuffer Animation : register(b3)
{
    float2 leftTop;
    float2 spriteSize;
    float2 offset;
    float2 atlasSize;
		
    uint animationType;
}

cbuffer NumberOfLight : register(b4)
{
    uint numberOfLight;
}

cbuffer ParticleSystem : register(b5)
{
    float4 particleColor;
}

SamplerState pointSampler : register(s0);
SamplerState linearSampler : register(s1);
SamplerState anisotropicSampler : register(s2);

StructuredBuffer<LightAttribute> lightAttributes : register(t13);
StructuredBuffer<Particle> particleBuffer : register(t15);

Texture2D defaultTexture : register(t0);
Texture2D defaultTexture2 : register(t1);
//Texture2D defaultTexture3 : register(t2);

Texture2D atlasTexture : register(t12);

/// 빛의 색깔 계산
void CalculateLight(in out LightColor pLightColor, float3 position, int idx) /// in out -> 포인터처럼 참조로 사용. 읽,쓰기 가능(in->읽기전용)
{
    if (0 == lightAttributes[idx].type) /// 0 : Directional
    {
        pLightColor.diffuse += lightAttributes[idx].color.diffuse; /// 누적해서 색더함
    }
    else if (1 == lightAttributes[idx].type) /// 1 : Point
    {
        float length = distance(lightAttributes[idx].position.xy, position.xy); /// 빛과의 거리
        if (length < lightAttributes[idx].radius)
        {
            float ratio = 1.0f - (length / lightAttributes[idx].radius);
            pLightColor.diffuse += lightAttributes[idx].color.diffuse * ratio; // cos(time) -> 크기가 커졋다작아졌다.. /// 거리에 따른 빛의 세기
        }
    }
    else if (2 == lightAttributes[idx].type) /// 2 : Spotlight
    {
        
    }
    else
    {
        pLightColor.diffuse += lightAttributes[idx].color.diffuse;
    }
};