#include "yaIsaac.h"
#include "yaMeshRenderer.h"
#include "yaMaterial.h"
#include "yaMesh.h"
#include "yaResources.h"

namespace ya
{
	Isaac::Isaac()
		: GameObject()
		, mMr(nullptr)
	{
	}

	Isaac::~Isaac()
	{
	}

	void Isaac::Initialize()
	{
		GameObject::Initialize();

		/*MeshRenderer* gridMr = gridObject->AddComponent<MeshRenderer>();
		gridMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		gridMr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
		gridObject->AddComponent<GridScript>();*/


		mMr = AddComponent<MeshRenderer>();
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		std::shared_ptr<Material> material = Resources::Find<Material>(L"RectMaterial");
		mMr->SetMaterial(material);
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