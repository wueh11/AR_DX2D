#pragma once
#include "yaComputeShader.h"
#include "yaStructedBuffer.h"

namespace ya::graphics
{
	class ParticleShader : public ComputeShader
	{
	public:
		ParticleShader();
		virtual ~ParticleShader();

		virtual void Binds() override;
		virtual void Clear() override;

		void SetStructedBuffer(StructedBuffer* buffer) { mBuffer = buffer; }
		void SetSharedStructedBuffer(StructedBuffer* buffer) { mSharedBuffer = buffer; }

	private:
		StructedBuffer* mBuffer;
		StructedBuffer* mSharedBuffer;
	};


}
