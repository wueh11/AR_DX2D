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
		BaseRenderer::Render();

		GetOwner()->GetComponent<Transform>()->SetConstantBuffer(); ///������� ����

		GetMaterial()->Bind();
		GetMesh()->BindBuffer(); /// �������� ����

		GetMesh()->Render(); /// �׷����� mesh ����

		GetMaterial()->Clear();
	}
}