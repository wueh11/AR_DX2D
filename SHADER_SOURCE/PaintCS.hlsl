RWTexture2D<float4> tex : register(u0); /// u: unordered access  /// RW : ReadWrite
Texture2D defaultTexture : register(t0);

// SV_GroupID : 스레드에 속한 그룹의 좌표
// SV_GroupThreadID : 그룹 내에서, 스레드의 좌표
// SV_GroupIndex : 그룹 내에서 스레드의 인덱스 좌표(1차원)
// SV_DispathThreadID : 전체 스레드 기준으로 호출된 좌표

[numthreads(32, 32, 1)] // 그룹당 쓰레드 개수 (최대 1024개 까지 지정가능
void main( uint3 DTid : SV_DispatchThreadID ) /// SV_DispatchThreadID -> 자동으로 들어오는 시맨틱
{
    /// DTid.xyz; /// uint3
    
    if (1024 <= DTid.x || 1024 <= DTid.y)
    {
        return;
    }
    
    //tex[DTid.xy] = float4(0.0f, 0.0f, 1.0f, 1.0f); 
    
    float4 px = defaultTexture.Load(DTid);
    tex[DTid.xy] = float4(sin(px.x * DTid.x), sin(px.y * DTid.y), sin(px.z + (DTid.x * DTid.y)), 1.0f);
}