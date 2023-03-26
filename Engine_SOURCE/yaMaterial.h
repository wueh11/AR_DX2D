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

		//void SetTexture(std::shared_ptr<Texture> texture) { mTexture = texture; }
		void SetTexture(std::shared_ptr<Texture> texture, UINT slot = 0);
		//std::shared_ptr<Texture> GetTexture() { return mTexture; }
		std::shared_ptr<Texture> GetTexture(UINT slot = 0) { return mTextures[slot]; }

		eRenderingMode GetRenderingMode() { return mMode;  }
		void SetRenderingMode(eRenderingMode mode) { mMode = mode; }

	private:
		std::shared_ptr<Shader> mShader;
		//std::shared_ptr<Texture> mTexture;

		std::vector<std::shared_ptr<Texture>> mTextures;

		MaterialCB mCB;

		eRenderingMode mMode;
	};
}