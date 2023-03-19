#include "yaIsaac.h"
#include "yaMeshRenderer.h"
#include "yaMaterial.h"
#include "yaMesh.h"
#include "yaResources.h"
#include "yaPlayerScript.h"
#include "yaTransform.h"

namespace ya
{
	Isaac::Isaac()
		: GameObject()
		, mMr(nullptr)
	{
		SetName(L"Isaac");
	}

	Isaac::~Isaac()
	{
	}

	void Isaac::Initialize()
	{
		GameObject::Initialize();

		mMr = AddComponent<MeshRenderer>();
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		std::shared_ptr<Material> material = Resources::Find<Material>(L"isaacMaterial");
		mMr->SetMaterial(material);

		AddComponent<PlayerScript>();
		Transform* tr = GetComponent<Transform>();
		tr->SetPosition(Vector3(0.0f, 1.0f, 5.0f));
	}

	void Isaac::Update()
	{
		GameObject::Update();
	}

	void Isaac::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Isaac::Render()
	{
		GameObject::Render();
	}
}