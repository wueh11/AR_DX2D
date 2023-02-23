#include "yaSpriteRenderer.h"
#include "yaGameObject.h"
#include "yaTransform.h"


namespace ya
{
	SpriteRenderer::SpriteRenderer()
		: BaseRenderer(eComponentType::SpriteRenderer)
	{
	}
	SpriteRenderer::~SpriteRenderer()
	{
	}
	void SpriteRenderer::Initialize()
	{
	}
	void SpriteRenderer::Update()
	{
	}
	void SpriteRenderer::FixedUpdate()
	{
	}
	void SpriteRenderer::Render()
	{
		GetOwner()->GetComponent<Transform>()->SetConstantBuffer(); ///상수버퍼 셋팅

		GetMaterial()->Bind();
		GetMesh()->BindBuffer(); /// 정점버퍼 세팅

		GetMesh()->Render(); /// 그려지는 mesh 누적

		GetMaterial()->Clear();
	}
}