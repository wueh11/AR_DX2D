
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

StructuredBuffer<LightAttribute> lightAttributes : register(t13); ///��ǻƮ���̴�. structure buffer: GPU���� �����Ѱ� CPU���� ����� �� ����
StructuredBuffer<LightAttribute> lightAttributes3D : register(t14);


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