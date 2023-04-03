#pragma once
#include "yaResource.h"
#include "yaShader.h"
#include "yaRenderer.h"
#include "yaTexture.h"

/// material : 어떻게 표현해줄것인지 (반사, 하이라이트....)
using namespace ya::renderer;
namespace ya::graphics
{
	class Material : public Resource
	{
	public:
		Material();
		virtual ~Material();

		virtual HRESULT Load(const std::wstring& path);

		void SetData(eGPUParam param, void* data);
		void Bind();
		void Clear();

		void SetShader(std::shared_ptr<Shader> shader) { mShader = shader; }
		std::shared_ptr<Shader> GetShader() { return mShader; }

		void SetTexture(std::shared_ptr<Texture> texture, eTextureSlot slot = eTextureSlot::T0) { mTexture[(UINT)slot] = texture; }
		std::shared_ptr<Texture> GetTexture(eTextureSlot slot = eTextureSlot::T0) { return mTexture[(UINT)slot]; }

		eRenderingMode GetRenderingMode() { return mMode;  }
		void SetRenderingMode(eRenderingMode mode) { mMode = mode; }

	private:
		std::shared_ptr<Shader> mShader;
		std::shared_ptr<Texture> mTexture[(UINT)eTextureSlot::End];

		MaterialCB mCB;

		eRenderingMode mMode;
	};
}