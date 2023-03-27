#include "yaImageRenderer.h"
#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaAnimator.h"

namespace ya
{
	ImageRenderer::ImageRenderer()
		: BaseRenderer(eComponentType::ImageRenderer)
		, mAtlas(nullptr)
		, mImage{}
	{
	}

	ImageRenderer::~ImageRenderer()
	{
	}

	void ImageRenderer::Initialize()
	{
	}

	void ImageRenderer::Update()
	{
	}

	void ImageRenderer::FixedUpdate()
	{
	}

	void ImageRenderer::Render()
	{
		GetOwner()->GetComponent<Transform>()->SetConstantBuffer();

		GetMaterial()->Bind();
		GetMesh()->BindBuffer();

		Animator* animator = GetOwner()->GetComponent<Animator>();
		
		if(mAtlas != nullptr)
			Binds();

		GetMesh()->Render();
		GetMaterial()->Clear();
		
		Clear();
	}

	void ImageRenderer::Binds()
	{
		mAtlas->BindShader(eShaderStage::PS, 12);

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Animation];

		CutImage image = {};
		renderer::AnimationCB info = {};
		info.leftTop = mImage.leftTop;
		info.offset = Vector2::Zero;
		info.size = mImage.size;
		info.atlasSize = mImage.atlasSize;
		info.type = (UINT)eAnimationType::SecondDimension;

		cb->SetData(&info);
		cb->Bind(eShaderStage::PS);
	}

	void ImageRenderer::SetImageSize(std::shared_ptr<Texture> atlas, Vector2 leftTop, Vector2 size)
	{
		mAtlas = atlas;

		// 텍스쳐 이미지 크기
		mImage.atlasWidth = (float)atlas->GetWidth();
		mImage.atlasHeight = (float)atlas->GetHeight();

		mImage.leftTop = Vector2(leftTop.x / mImage.atlasWidth, leftTop.y / mImage.atlasHeight);
		mImage.size = Vector2(size.x / mImage.atlasWidth, size.y / mImage.atlasHeight);
		mImage.atlasSize = Vector2(size.x / mImage.atlasWidth, size.y / mImage.atlasHeight);
	}

	void ImageRenderer::Clear()
	{
		// Texture clear
		Texture::Clear(12);

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Animation];
		renderer::AnimationCB info = {};
		info.type = (UINT)eAnimationType::None;
	}
}