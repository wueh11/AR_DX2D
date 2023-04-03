#pragma once
#include "yaBaseRenderer.h"
#include "yaParticleShader.h"

namespace ya
{
	class ParticleSystem : public BaseRenderer
	{
	public:
		ParticleSystem();
		virtual ~ParticleSystem();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	private:
		class StructedBuffer* mBuffer;
		class StructedBuffer* mSharedBuffer;

		std::shared_ptr<graphics::ParticleShader> mCS;

		UINT mCount;	/// 파티클 개수
		Vector4 mStartSize;
		Vector4 mEndSize;
		Vector4 mStartColor;
		Vector4 mEndColor;
		float mStartLifeTime;
		float mFrequency;		/// 몇초에 한번ㅁ ㅏㄴ들지
		float mTime;		///현재 시간
	};

}
