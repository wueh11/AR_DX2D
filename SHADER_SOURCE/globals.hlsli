

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

SamplerState pointSampler : register(s0);
SamplerState linearSampler : register(s1);
SamplerState anisotropicSampler : register(s2);

Texture2D defaultTexture : register(t0);
//Texture2D defaultTexture2 : register(t1);
//Texture2D defaultTexture3 : register(t2);