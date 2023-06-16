#include "yaShopItemScript.h"

#include "yaPlayer.h"
#include "yaPlayerScript.h"

#include "yaTime.h"
#include "yaRigidbody.h"

#include "yaResources.h"
#include "yaImageRenderer.h"
#include "yaSpriteRenderer.h"

#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaScene.h"
#include "yaStageScene.h"
#include "yaRoom.h"

#include "yaPickup.h"

#include "Commons.h"

#include "yaActiveItem.h"
#include "yaPassiveItem.h"

#include "yaObject.h"

namespace ya
{
	ShopItemScript::ShopItemScript()
		: Script()
		, mItem(nullptr)
		, mPrice(0)
		, mPriceObject(nullptr)
	{
	}
	ShopItemScript::~ShopItemScript()
	{
	}
	void ShopItemScript::Initialize()
	{
		Transform* altarTr = GetOwner()->GetComponent<Transform>();
		altarTr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> material = Resources::Find<Material>(L"bitfontMaterial");
		std::shared_ptr<Texture> texture = material->GetTexture();

		Collider2D* collider = GetOwner()->GetComponent<Collider2D>();
		collider->SetSize(Vector2(0.4f, 0.4f));

		{
			mPriceObject = object::Instantiate<GameObject>(eLayerType::Background, GetOwner());
			Transform* priceObjectTr = mPriceObject->GetComponent<Transform>();
			priceObjectTr->SetScale(Vector3(0.32f, 0.32f, 1.0f));
			priceObjectTr->SetPosition(Vector3(-0.08f, -0.36f, 0.0f));

			SpriteRenderer* priceObjectRd = mPriceObject->AddComponent<SpriteRenderer>();
			priceObjectRd->SetMesh(mesh);
			priceObjectRd->SetMaterial(material);

			Animator* priceObjectAnimator = mPriceObject->AddComponent<Animator>();
			priceObjectAnimator->Create(L"number_0", texture, Vector2(0.0f, 0.0f), Vector2(16.0f, 16.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
			priceObjectAnimator->Create(L"number_1", texture, Vector2(16.0f, 0.0f), Vector2(16.0f, 16.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
			priceObjectAnimator->Create(L"number_2", texture, Vector2(32.0f, 0.0f), Vector2(16.0f, 16.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
			priceObjectAnimator->Create(L"number_3", texture, Vector2(48.0f, 0.0f), Vector2(16.0f, 16.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
			priceObjectAnimator->Create(L"number_4", texture, Vector2(64.0f, 0.0f), Vector2(16.0f, 16.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
			priceObjectAnimator->Create(L"number_5", texture, Vector2(80.0f, 0.0f), Vector2(16.0f, 16.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
			priceObjectAnimator->Create(L"number_6", texture, Vector2(0.0f, 16.0f), Vector2(16.0f, 16.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
			priceObjectAnimator->Create(L"number_7", texture, Vector2(16.0f, 16.0f), Vector2(16.0f, 16.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
			priceObjectAnimator->Create(L"number_8", texture, Vector2(32.0f, 16.0f), Vector2(16.0f, 16.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
			priceObjectAnimator->Create(L"number_9", texture, Vector2(48.0f, 16.0f), Vector2(16.0f, 16.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
			priceObjectAnimator->Play(L"number_0");
		}

		{
			GameObject* cent = object::Instantiate<GameObject>(eLayerType::Background, GetOwner());
			Transform* centTr = cent->GetComponent<Transform>();
			centTr->SetScale(Vector3(0.32f, 0.32f, 1.0f));
			centTr->SetPosition(Vector3(0.1f, -0.4f, 0.0f));

			ImageRenderer* centRd = cent->AddComponent<ImageRenderer>();
			centRd->SetMesh(mesh);
			centRd->SetMaterial(material);
			centRd->SetImageSize(texture, Vector2(64.0f, 16.0f), Vector2(16.0f, 16.0f));
		}

		
		
	}
	void ShopItemScript::Update()
	{
	}

	void ShopItemScript::FixedUpdate()
	{
	}
	void ShopItemScript::Render()
	{
	}

	void ShopItemScript::OnCollisionEnter(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();
		Player* player = dynamic_cast<Player*>(other);

		if (player == nullptr)
			return;

		PlayerScript* playerScript = player->GetScript<PlayerScript>();

		if (mItem != nullptr)
		{
			Player::Pickup pickup = player->GetPickup();
			if (pickup.coin < mPrice)
			{
				Collider2D* c = mItem->GetComponent<Collider2D>();
				c->Active(false);
				return;
			}
		
			GetOwner()->Pause();
			player->AddCoin(mPrice * -1);
			mItem->GetScript<Script>()->OnCollisionEnter(collider);
			GetOwner()->Death();
		}

	}
	void ShopItemScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void ShopItemScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void ShopItemScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void ShopItemScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void ShopItemScript::OnTriggerExit(Collider2D* collider)
	{
	}
	void ShopItemScript::SetItem(Item* item, int price)
	{
		mItem = item;
		item->Active();

		if (item == nullptr)
			return;

		item->SetParent(GetOwner());
		Transform* tr = item->GetComponent<Transform>();
		tr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));

		mPrice = price;

		Animator* priceObjectAnimator = mPriceObject->GetComponent<Animator>();
		priceObjectAnimator->Play(L"number_" + std::to_wstring(price));
	}
}