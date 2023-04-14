#include "globals.hlsli"

RWStructuredBuffer<Particle> ParticleBuffer : register(u0);
RWStructuredBuffer<ParticleShared> ParticleSharedBuffer : register(u1);

// 각각의 스레드가 동기화할 데이터가 필요하다.

[numthreads(128, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    if (maxParticles <= DTid.x) /// 스레드 개수를 넘어가면 계산하지않음
        return;
    
    if (ParticleBuffer[DTid.x].active == 0)
    {
        while (0 < ParticleSharedBuffer[0].gActiveCount)
        {
            int originValue = ParticleSharedBuffer[0].gActiveCount;
            int exchange = originValue - 1;
            
            // 동기화
            // dest값을 exchange값으로 바꾸는 동안 다른 스레드는 멈춘다.
            //InterlockedExchange(ParticleSharedBuffer[0].gActiveCount, exchange, exchange); /// 값을 변경하는동안 lock을 건다-> 각 스레드가 동시에 값을 변경할 수 없게 동기화
            InterlockedCompareExchange(ParticleSharedBuffer[0].gActiveCount, originValue, exchange, exchange); /// 값을 비교해서 동일하면 덮어씌운다.
            
            if (originValue == exchange) /// 다 실행된 후 -하고 값이 같아지면
            {
                ParticleBuffer[DTid.x].active = 1;
                break;
            }
        }
        
        if (ParticleBuffer[DTid.x].active)
        {
                // 랜덤값으로 위치와 방향을 설정해준다.
                // 샘플링을 시도할 uv를 계산해준다.
            float4 Random = (float4) 0.0f;
            float2 UV = float2((float) DTid.x / maxParticles, 0.5f);
            UV.x += elapsedTime;
            UV.y += sin((UV.x + elapsedTime) * 3.141592f + 2.0f * 10.0f) * 0.5f;

            Random = float4
                (
                    GaussianBlur(UV + float2(0.0f, 0.0f)).x
                    , GaussianBlur(UV + float2(0.1f, 0.0f)).x
                    , GaussianBlur(UV + float2(0.2f, 0.0f)).x
                    , GaussianBlur(UV + float2(0.2f, 0.0f)).x
                );

            // radius 원형 범위로 스폰
            float fTheta = Random.xy * 3.141592f * 2.0f;
            ParticleBuffer[DTid.x].position.xy = float2(cos(fTheta), sin(fTheta)) * Random.y * radius;
            ParticleBuffer[DTid.x].position.z = 100.0f;
            
            ParticleBuffer[DTid.x].direction.xy 
                = normalize(float2(ParticleBuffer[DTid.x].position.xy));

            if (simulationSpace) // 1 world, 0 local
            {
                ParticleBuffer[DTid.x].position.xyz += worldPosition.xyz;
            }
            
            // 파티클 속력
            ParticleBuffer[DTid.x].time = 0.0f;
            ParticleBuffer[DTid.x].speed = startSpeed;
            ParticleBuffer[DTid.x].lifeTime = startLifeTime;
        }
    }
    else // active == 1
    {
        ParticleBuffer[DTid.x].time += deltaTime;
        if (ParticleBuffer[DTid.x].lifeTime < ParticleBuffer[DTid.x].time)
        {
            ParticleBuffer[DTid.x].active = 0;
        }
        else
        {
            ParticleBuffer[DTid.x].position 
            += ParticleBuffer[DTid.x].direction * ParticleBuffer[DTid.x].speed * deltaTime;
        }
    }
}