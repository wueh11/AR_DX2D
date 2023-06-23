#pragma once
#include "yaComponent.h"
#include "yaMesh.h"
#include "yaMaterial.h"
#include "yaTexture.h"

namespace ya 
{
	class BaseRenderer : public Component
	{
	public:
		BaseRenderer(eComponentType type);
		virtual ~BaseRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void SetMesh(std::shared_ptr<Mesh> mesh) { mMesh = mesh; }
		void SetMaterial(std::shared_ptr <Material> shader) { mMaterial = shader; }

		std::shared_ptr<Mesh> GetMesh() { return mMesh; }
		std::shared_ptr<Material> GetMaterial() { return mMaterial; }

		void SetColorType(int type) { mColorType = type; }
		void UseRate(bool use) { mbUseRate = use; mbUseRate = true; }
		void UseRange(bool use) { mbUseRange = use; }
		void SetRange(Vector4 range) { mImageRange = range; mbUseRange = true; }
		void SetColor(Vector4 color) { mImageColor = color; }
		void SetRate(Vector2 rate) { mImageRate = rate; }
		void UseAlpha(bool use) { mbUseAlpha = use; }
		void SetAlpha(float alpha) { mImageAlpha = alpha; mbUseAlpha = true; }

	private:
		std::shared_ptr<Mesh> mMesh;
		std::shared_ptr<Material> mMaterial;

		int mColorType;
		bool mbUseRate;
		bool mbUseRange;
		Vector4 mImageColor;
		Vector4 mImageRange;
		Vector2 mImageRate;
		bool mbUseAlpha;
		float mImageAlpha;
	};
}

