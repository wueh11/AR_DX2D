#include "yaPassiveItemScript.h"
#include "yaActiveItem.h"

#include "yaResources.h"
#include "yaGameObject.h"

#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaSpriteRenderer.h"

#include "yaPlayer.h"
#include "yaPlayerScript.h"

namespace ya
{
	PassiveItemScript::PassiveItemScript()
		: CollectibleScript()
		, mPassiveItem(ePassiveItem::None)
	{
	}
	PassiveItemScript::~PassiveItemScript()
	{
	}
	void PassiveItemScript::Initialize()
	{
		CollectibleScript::Initialize();

		mTransform = GetOwner()->GetComponent<Transform>();
		mTransform->SetScale(Vector3(0.66f, 0.66f, 1.0f));

		mAnimator = GetOwner()->AddComponent<Animator>();

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> material = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Texture> texture = material->GetTexture();

		SpriteRenderer* pillMr = GetOwner()->AddComponent<SpriteRenderer>();
		pillMr->SetMesh(mesh);
		pillMr->SetMaterial(material);

		mAnimator->Create(L"None", Resources::Find<Texture>(L"transparent"), Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"passive_" + std::to_wstring((UINT)ePassiveItem::Lunch), Resources::Find<Texture>(L"lunch"), Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Play(L"None", false);
	}

	void PassiveItemScript::Update()
	{
		CollectibleScript::Update();
	}
	void PassiveItemScript::FixedUpdate()
	{
		CollectibleScript::FixedUpdate();
	}
	void PassiveItemScript::Render()
	{
		CollectibleScript::Render();
	}

	void PassiveItemScript::OnCollisionEnter(Collider2D* collider)
	{
		CollectibleScript::OnCollisionEnter(collider);
	}

	void PassiveItemScript::OnCollisionStay(Collider2D* collider)
	{
		CollectibleScript::OnCollisionStay(collider);
	}

	void PassiveItemScript::OnCollisionExit(Collider2D* collider)
	{
		CollectibleScript::OnCollisionExit(collider);
	}
	void PassiveItemScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void PassiveItemScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void PassiveItemScript::OnTriggerExit(Collider2D* collider)
	{
	}
	void PassiveItemScript::SetPassiveItem(ePassiveItem activeItem)
	{
		mPassiveItem = activeItem;

		if (mPassiveItem != ePassiveItem::None)
			mAnimator->Play(L"passive_" + std::to_wstring((UINT)mPassiveItem), false);
		else
			mAnimator->Play(L"None", false);
	}
}