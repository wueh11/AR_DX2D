#pragma once
#include "yaBaseRenderer.h"
#include "yaMesh.h"
#include "yaMaterial.h"

using namespace ya::graphics;
namespace ya
{
	class ImageRenderer : public BaseRenderer
	{
		struct CutImage
		{
			float atlasWidth;
			float atlasHeight;
			Vector2 leftTop;	// ���� ��� ��ǥ
			Vector2 size;		// ���� ��ܺ��� �߶� ���� ������ �ȼ� ����
			Vector2 atlasSize;	// �ؽ��� �̹����� ũ��

			CutImage()
				: atlasWidth(0.0f)
				, atlasHeight(0.0f)
				, leftTop(Vector2::Zero)
				, size(Vector2::Zero)
				, atlasSize(Vector2::Zero)
			{
			}
		};

	public:
		ImageRenderer();
		virtual ~ImageRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void Binds();
		void SetImageSize(std::shared_ptr<Texture> atlas, Vector2 leftTop, Vector2 size);
		void SetSprite(std::shared_ptr<Texture> atlas, Vector2 leftTop, Vector2 size, Vector2 atlasSize);
		void Clear();

		void SetImage(std::shared_ptr<Texture> atlas) { mAtlas = atlas; }
		CutImage GetImage() { return mImage; }

	private:
		std::shared_ptr<Texture> mAtlas;
		CutImage mImage;
	};
}
