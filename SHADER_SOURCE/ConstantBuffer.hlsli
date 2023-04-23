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
    int padding1;
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
    float4 worldPosition;
    float4 startColor;
    float4 startSize;
    
    uint maxParticles;
    uint simulationSpace; /// ������ǥ������ ������ǥ������ ����
    float radius;
    float startSpeed;
    
    float startLifeTime;
    float deltaTime;
    float elapsedTime; //�����ð�
    int padding;
}