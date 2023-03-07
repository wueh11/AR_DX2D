#include "yaUIheart.h"

#include "yaMeshRenderer.h"
#include "yaMaterial.h"
#include "yaMesh.h"
#include "yaResources.h"
#include "yaTransform.h"

namespace ya
{
	UIheart::UIheart()
		: GameObject()
		, mMr(nullptr)
	{
		SetName(L"UIheart");
	}

	UIheart::~UIheart()
	{
	}

	void UIheart::Initialize()
	{
		GameObject::Initialize();

		mMr = AddComponent<MeshRenderer>();
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		std::shared_ptr<Material> material = Resources::Find<Material>(L"UIheartMaterial");
		mMr->SetMaterial(material);

		Transform* tr = GetComponent<Transform>();
		tr->SetPosition(Vector3(0.0f, 1.0f, 5.0f));
	}

	void UIheart::Update()
	{
		GameObject::Update();
	}

	void UIheart::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void UIheart::Render()
	{
		GameObject::Render();
	}
}