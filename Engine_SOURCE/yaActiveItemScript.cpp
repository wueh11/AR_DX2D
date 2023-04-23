#include "yaActiveItemScript.h"
#include "yaActiveItem.h"

#include "yaTransform.h"
#include "yaGameObject.h"

#include "yaAnimator.h"
#include "yaResources.h"
#include "yaSpriteRenderer.h"
#include "yaObject.h"

#include "yaPlayer.h"
#include "yaScene.h"
#include "yaSceneManager.h"

#include "yaItemManager.h"

#include "yaRigidbody.h"
#include "yaPlayerScript.h"
#include "yaTime.h"

namespace ya
{
	ActiveItemScript::ActiveItemScript()
		: CollectibleScript()
		, mActiveItem(eActiveItem::None)
	{
	}
	ActiveItemScript::~ActiveItemScript()
	{
	}
	void ActiveItemScript::Initialize()
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
		mAnimator->Create(L"active_" + std::to_wstring((UINT)eActiveItem::TheBible), Resources::Find<Texture>(L"thebible"), Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"active_" + std::to_wstring((UINT)eActiveItem::TammysHead), Resources::Find<Texture>(L"tammyshead"), Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"active_" + std::to_wstring((UINT)eActiveItem::YumHeart), Resources::Find<Texture>(L"yumheart"), Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Play(L"None", false);
	}

	void ActiveItemScript::Update()
	{
		CollectibleScript::Update();
	}
	void ActiveItemScript::FixedUpdate()
	{
	}
	void ActiveItemScript::Render()
	{
	}

	void ActiveItemScript::OnCollisionEnter(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();

		if (mActiveItem != eActiveItem::None)
		{
			Player* player = dynamic_cast<Player*>(other);
			if (player != nullptr)
			{
				PlayerScript* playerScript = player->GetScript<PlayerScript>();

				if (!playerScript->IsItemAction())
				{
					Player::Items item = player->GetItem();
					eActiveItem temp = item.activeItem;

					playerScript->gainActiveItem(dynamic_cast<ActiveItem*>(GetOwner()));
					SetActiveItem(temp);
				}
			}
		}

		CollectibleScript::OnCollisionEnter(collider);
	}

	void ActiveItemScript::OnCollisionStay(Collider2D* collider)
	{
		CollectibleScript::OnCollisionStay(collider);
	}

	void ActiveItemScript::OnCollisionExit(Collider2D* collider)
	{
		CollectibleScript::OnCollisionExit(collider);
	}
	void ActiveItemScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void ActiveItemScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void ActiveItemScript::OnTriggerExit(Collider2D* collider)
	{
	}
	void ActiveItemScript::SetActiveItem(eActiveItem activeItem)
	{
		mActiveItem = activeItem;

		if (mActiveItem != eActiveItem::None)
			mAnimator->Play(L"active_" + std::to_wstring((UINT)mActiveItem), false);
		else
			mAnimator->Play(L"None", false);
	}
}