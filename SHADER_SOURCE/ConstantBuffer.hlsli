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
    int padding1;
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
    float4 worldPosition;
    float4 startColor;
    float4 startSize;
    
    uint maxParticles;
    uint simulationSpace; /// 로컬좌표계인지 월드좌표계인지 구분
    float radius;
    float startSpeed;
    
    float startLifeTime;
    float deltaTime;
    float elapsedTime; //누적시간
    int padding;
}