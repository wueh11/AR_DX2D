

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

SamplerState pointSampler : register(s0);
SamplerState linearSampler : register(s1);
SamplerState anisotropicSampler : register(s2);

Texture2D defaultTexture : register(t0);
//Texture2D defaultTexture2 : register(t1);
//Texture2D defaultTexture3 : register(t2);