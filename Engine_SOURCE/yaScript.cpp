#include "yaScript.h"
#include "yaObject.h"
#include "yaMeshRenderer.h"
#include "yaResources.h"

namespace ya
{
	Script::Script()
		: Component(eComponentType::Script)
		, mShadow(nullptr)
	{
	}

	Script::~Script()
	{
	}

	void Script::Initialize()
	{
	}

	void Script::Update()
	{
	}

	void Script::FixedUpdate()
	{
		if (mShadow != nullptr)
		{
			float height = GetOwner()->GetComponent<Transform>()->GetHeight();

			Transform* shadowTr = mShadow->GetComponent<Transform>();
			shadowTr->SetPosition(mShadowPos + Vector3(0.0f, -height, 0.0f));
		}
	}
	void Script::Render()
	{
		if(mShadow != nullptr)
		{
			BaseRenderer* rd = mShadow->GetComponent<BaseRenderer>();
			rd->SetAlpha(0.3f);
		}
	}
	void Script::Shadow(Vector3 pos, Vector3 scale)
	{
		GameObject* owner = GetOwner();
		Vector3 ownerScale = owner->GetComponent<Transform>()->GetScale();

		mShadow = object::Instantiate<GameObject>(eLayerType::Effect, owner);
		Transform* shadowTr = mShadow->GetComponent<Transform>();
		SetShadowPosition(pos);
		shadowTr->SetPosition(mShadowPos);
		shadowTr->SetScale(scale);

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		MeshRenderer* shadowMr = mShadow->AddComponent<MeshRenderer>();
		shadowMr->SetMesh(mesh);
		std::shared_ptr<Material> gamemenuMaterial = Resources::Find<Material>(L"shadowMaterial");
		shadowMr->SetMaterial(gamemenuMaterial);
	}
	void Script::SetShadowPosition(Vector3 pos)
	{
		GameObject* owner = GetOwner();
		Vector3 ownerScale = owner->GetComponent<Transform>()->GetScale();
		mShadowPos = pos + Vector3(0.0f, 0.0f, 10.0f);
	}
	void Script::SetShadowScale(Vector3 scale)
	{
		Transform* shadowTr = mShadow->GetComponent<Transform>();
		shadowTr->SetScale(scale);
	}
}