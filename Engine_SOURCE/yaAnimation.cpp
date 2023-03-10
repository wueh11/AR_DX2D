#include "yaAnimation.h"
#include "yaTime.h"
#include "yaAnimator.h"
#include "yaMaterial.h"

namespace ya
{
    Animation::Animation()
        : mAnimator(nullptr)
        , mAtlas(nullptr)
        , mSpriteSheet{}
        , mIndex(-1)
        , mTime(0.0f)
        , mbComplete(false)
    {
    }

    Animation::~Animation()
    {
    }

    void Animation::Update()
    {
        if (mbComplete)
            return;

        mTime += Time::DeltaTime();

        if (mSpriteSheet[mIndex].duration < mTime)
        {
            mTime = 0.0f;
            ++mIndex;

            if (mSpriteSheet.size() <= mIndex)
            {
                mbComplete = true;
                mIndex = mSpriteSheet.size() - 1;
            }
        }

        BindShader();
    }

    void Animation::FixedUpdate()
    {
    }

    void Animation::Render()
    {
    }

    void Animation::Create(const std::wstring& name, std::shared_ptr<Texture> atlas
                                , Vector2 leftTop, Vector2 size, Vector2 offset
                                , UINT columnLength, UINT spriteLength, float duration)
    {
        for (size_t i = 0; i < spriteLength; i++)
        {
            Sprite sprite;
            sprite.leftTop = leftTop + (i * size);
            sprite.size = size / columnLength;
            sprite.offset = offset;
            sprite.duration = duration;

            mSpriteSheet.push_back(sprite);
        }
    }

    void Animation::BindShader()
    {
        std::shared_ptr<Material> material = mAnimator->GetMaterial();
        if (material == nullptr)
            return;
        
        Sprite sprite = mSpriteSheet[mIndex];

        //constant buffer
        ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Animation];
        renderer::AnimationCB data;
        data.atlasSize = sprite.size;
        data.leftTop = sprite.leftTop;
        data.offset = sprite.offset;
        data.size = sprite.size;
        data.used = true;

        cb->Bind(&data);
        cb->SetPipeline(eShaderStage::VS);
        cb->SetPipeline(eShaderStage::PS);
    }

    void Animation::Clear()
    {
    }

    void Animation::Reset()
    {
        mTime = 0.0f;
        mIndex = 0;
        mbComplete = false;
    }
}