#pragma once
#include "yaEntity.h"
#include "yaTexture.h"

using namespace ya::math;
using namespace ya::graphics;
namespace ya
{
	class Animation : public Entity
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;	// ���� ��� ��ǥ
			Vector2 size;		// ���� ��ܺ��� �߶� ���� ������ �ȼ� ����
			Vector2 offset;		// ������ ��ġ �����ϱ� ���� ��ǥ
			Vector2 atlasSize;	// �ؽ��� �̹����� ũ��
			float duration;		// �����Ӱ��� �ð� ����

			Sprite()
				: leftTop(Vector2::Zero)
				, size(Vector2::Zero)
				, offset(Vector2::Zero)
				, atlasSize(Vector2::Zero)
				, duration(0.1f)
			{
			}
		};

		Animation();
		virtual ~Animation();
		
		void Update();
		void FixedUpdate();
		void Render();

		void Create(const std::wstring& name, std::shared_ptr<Texture> atlas
						, Vector2 leftTop, Vector2 size, Vector2 offset
						, UINT spriteLength, float duration);

		void BindShader();	//���̴��� ����
		void Clear();

		void Reset();

		bool IsComplete() { return mbComplete; }
		
		std::wstring& AnimationName() { return mAnimationName; }


	private:
		class Animator* mAnimator;
		std::wstring mAnimationName;
		std::shared_ptr<Texture> mAtlas;
		std::vector<Sprite> mSpriteSheet;
		int mIndex;
		float mTime;
		bool mbComplete;

	};
}
