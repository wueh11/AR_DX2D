#include "yaMeshRenderer.h"
#include "yaGameObject.h"
#include "yaTransform.h"

namespace ya
{
	MeshRenderer::MeshRenderer()
		:BaseRenderer(eComponentType::MeshRenderer)
	{
	}

	MeshRenderer::~MeshRenderer()
	{
	}

	void MeshRenderer::Initialize()
	{
	}

	void MeshRenderer::Update()
	{
	}

	void MeshRenderer::FixedUpdate()
	{
	}

	void MeshRenderer::Render()
	{
		GetOwner()->GetComponent<Transform>()->SetConstantBuffer(); ///상수버퍼 셋팅

		GetMaterial()->Bind();
		GetMesh()->BindBuffer(); /// 정점버퍼 세팅

		GetMesh()->Render(); /// 그려지는 mesh 누적

		GetMaterial()->Clear();
	}
}