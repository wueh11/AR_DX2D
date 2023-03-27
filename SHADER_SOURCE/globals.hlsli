#include "Light.hlsli"
#include "Particle.hlsli"

cbuffer Transform : register(b0) /// ���� ��ȣ. �׷���ī�忡�� ����� ���մ� ������� ����
{
    row_major matrix world; /// ����
    row_major matrix view; /// ī�޶�
    row_major matrix projection; /// ���ٳ����Ⱑ ����������� ������ǥ
    /// row_major. column_major -> ���켱, ��켱 ����
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

cbuffer Grid : register(b2) /// ������� ũ�� 16byte�� �����....
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

/// ���� ���� ���
void CalculateLight(in out LightColor pLightColor, float3 position, int idx) /// in out -> ������ó�� ������ ���. ��,���� ����(in->�б�����)
{
    if (0 == lightAttributes[idx].type) /// 0 : Directional
    {
        pLightColor.diffuse += lightAttributes[idx].color.diffuse; /// �����ؼ� ������
    }
    else if (1 == lightAttributes[idx].type) /// 1 : Point
    {
        float length = distance(lightAttributes[idx].position.xy, position.xy); /// ������ �Ÿ�
        if (length < lightAttributes[idx].radius)
        {
            float ratio = 1.0f - (length / lightAttributes[idx].radius);
            pLightColor.diffuse += lightAttributes[idx].color.diffuse * ratio; // cos(time) -> ũ�Ⱑ Ŀ�����۾�����.. /// �Ÿ��� ���� ���� ����
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