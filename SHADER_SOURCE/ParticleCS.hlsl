#include "globals.hlsli"

RWStructuredBuffer<Particle> ParticleBuffer : register(u0);
RWStructuredBuffer<ParticleShared> ParticleSharedBuffer : register(u1);

// 각각의 스레드가 동기화할 데이터가 필요하다.

[numthreads(128, 1, 1)] 
void main(uint3 DTid : SV_DispatchThreadID) 
{
    if(elementCount <= DTid.x ) /// 스레드 개수를 넘어가면 계산하지않음
        return;
    
    if (ParticleBuffer[DTid.x].active == 0)
    {
        while(0 < ParticleSharedBuffer[0].gActiveCount)
        {
            int originValue = ParticleSharedBuffer[0].gActiveCount;
            int exchange = originValue - 1;
            
            // 동기화
            // dest값을 exchange값으로 바꾸는 동안 다른 스레드는 멈춘다.
            InterlockedExchange(ParticleSharedBuffer[0].gActiveCount, exchange, exchange); /// 값을 변경하는동안 lock을 건다-> 각 스레드가 동시에 값을 변경할 수 없게 동기화

            if (originValue == exchange) /// 다 실행된 후 -하고 값이 같아지면
            {
                ParticleBuffer[DTid.x].active = 1;
                break;
            }
        }
    }
    else // active == 1
    {
        ParticleBuffer[DTid.x].position += ParticleBuffer[DTid.x].direction * ParticleBuffer[DTid.x].speed * deltaTime;
    }
}