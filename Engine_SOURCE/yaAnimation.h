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
			Vector2 leftTop;	// 좌측 상단 좌표
			Vector2 size;		// 좌측 상단부터 잘라낼 가로 세로의 픽셀 길이
			Vector2 offset;		// 렌덜이 위치 조정하기 위한 좌표
			Vector2 atlasSize;	// 텍스쳐 이미지의 크기
			float duration;		// 프레임간의 시간 간격

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

		void BindShader();	//쉐이더에 셋팅
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
