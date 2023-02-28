#include "yaIssac.h"
#include "yaMeshRenderer.h"
#include "yaMaterial.h"
#include "yaMesh.h"

namespace ya
{
	Issac::Issac()
		: GameObject()
		, mMr(nullptr)
	{
	}

	Issac::~Issac()
	{
	}

	void Issac::Initialize()
	{
		GameObject::Initialize();


		//GameObject* gridObject = object::Instantiate<GameObject>(eLayerType::None);
		//MeshRenderer* gridMr = gridObject->AddComponent<MeshRenderer>();
		//gridMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//gridMr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
		//gridObject->AddComponent<GridScript>();


		mMr = AddComponent<MeshRenderer>();
	}

	void Issac::Update()
	{
		GameObject::Update();
	}

	void Issac::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Issac::Render()
	{
		GameObject::Render();
	}
}