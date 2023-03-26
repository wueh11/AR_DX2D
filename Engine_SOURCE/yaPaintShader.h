#pragma once
#include "yaComputeShader.h"
#include "yaTexture.h"

namespace ya::graphics
{
	class PaintShader : public ComputeShader
	{
	public:
		PaintShader();
		virtual ~PaintShader();

		virtual void Binds() override;
		virtual void Clear() override;

		void SetTarget(std::shared_ptr<Texture> target) { mTarget = target; }
		void SetTexture(std::shared_ptr<Texture> texture) { mTexture = texture; }

	private:
		std::shared_ptr<Texture> mTarget;
		std::shared_ptr<Texture> mTexture;
	};


}
