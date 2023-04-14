
struct LightColor
{
    float4 diffuse;
    float4 specular;
    float4 ambient;
};

struct LightAttribute
{
    LightColor color;
    float4 position;
    float4 direction;
    
    int type;
    float radius;
    float angle;
    int padding;
};

StructuredBuffer<LightAttribute> lightAttributes : register(t13); ///컴퓨트셰이더. structure buffer: GPU에서 연산한걸 CPU에서 사용할 수 잇음
StructuredBuffer<LightAttribute> lightAttributes3D : register(t14);


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