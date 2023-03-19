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

    UINT Animation::Update()
    {
        if (mbComplete)
            return -1;

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

            return mIndex;
        }

        return -1;
    }

    void Animation::FixedUpdate()
    {
    }

    void Animation::Render()
    {
    }

    void Animation::Create(const std::wstring& name, std::shared_ptr<Texture> atlas
						, Vector2 leftTop, Vector2 size, Vector2 offset
						, UINT spriteLength, float duration, UINT spriteRow, UINT spriteColumn)
    {
        mAnimationName = name;
        mAtlas = atlas;

        // �ؽ��� �̹��� ũ��
        float width = (float)atlas->GetWidth();
        float height = (float)atlas->GetHeight();

        if (spriteRow == 1)
            spriteColumn = spriteLength;

        for (size_t i = 0, row = 0, col = 0; i < spriteLength; i++, col++)
        {
            if (col > spriteColumn)
            {
                row++;
                col = 0;
            }

            // API�ʹ� �ٸ��� 0~1 ������ ������ǥ�� ��ġ�� ǥ���ؾ��Ѵ�.
            Sprite sprite = {};
            sprite.leftTop = Vector2((leftTop.x + (size.x * (float)col)) / width, (leftTop.y + (size.x * (float)row)) / height);
            sprite.size = Vector2(size.x / width, size.y / height);
            sprite.offset = offset;
            sprite.duration = duration;
            sprite.atlasSize = Vector2(size.x / width, size.y / height);

            mSpriteSheet.push_back(sprite);
        }
    }

    void Animation::BindShader()
    {
        mAtlas->BindShader(eShaderStage::PS, 12);

        ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Animation];

        renderer::AnimationCB info = {};
        info.type = (UINT)eAnimationType::SecondDimension;
        info.leftTop = mSpriteSheet[mIndex].leftTop;
        info.offset = mSpriteSheet[mIndex].offset;
        info.size = mSpriteSheet[mIndex].size;
        info.atlasSize = mSpriteSheet[mIndex].atlasSize;

        cb->Bind(&info);
        cb->SetPipeline(eShaderStage::PS);
    }

    void Animation::Clear()
    {
        // Texture clear
        Texture::Clear(12);

        ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Animation];
        renderer::AnimationCB info = {};
        info.type = (UINT)eAnimationType::None;
    }

    void Animation::Reset()
    {
        mTime = 0.0f;
        mIndex = 0;
        mbComplete = false;
    }
}