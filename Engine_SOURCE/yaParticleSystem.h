#pragma once
#include "yaBaseRenderer.h"
#include "yaParticleShader.h"

namespace ya
{
	enum class eSimulationSpace
	{
		Local,
		World,
	};

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
		renderer::ParticleSystemCB mCBData;

		Vector4 mStartSize;
		Vector4 mStartColor;

		eSimulationSpace mSimulationSpace;
		UINT mMaxParticles;	/// ��ƼŬ ����
		float mStartLifeTime;
		float mFrequency;	/// ���ʿ� �ѹ� ������
		float mRadius;

		float mStartSpeed;
		float mTime;		///���� �ð�
		float mElapsedTime; //�����ð�
	};
}
