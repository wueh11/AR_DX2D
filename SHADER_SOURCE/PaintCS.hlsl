RWTexture2D<float4> tex : register(u0); /// u: unordered access  /// RW : ReadWrite
Texture2D defaultTexture : register(t0);

// SV_GroupID : �����忡 ���� �׷��� ��ǥ
// SV_GroupThreadID : �׷� ������, �������� ��ǥ
// SV_GroupIndex : �׷� ������ �������� �ε��� ��ǥ(1����)
// SV_DispathThreadID : ��ü ������ �������� ȣ��� ��ǥ

[numthreads(32, 32, 1)] // �׷�� ������ ���� (�ִ� 1024�� ���� ��������
void main( uint3 DTid : SV_DispatchThreadID ) /// SV_DispatchThreadID -> �ڵ����� ������ �ø�ƽ
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