#include "yaAltarScript.h"

#include "yaPlayer.h"
#include "yaPlayerScript.h"

#include "yaTime.h"
#include "yaRigidbody.h"

#include "yaResources.h"
#include "yaImageRenderer.h"

#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaScene.h"
#include "yaStageScene.h"
#include "yaRoom.h"

#include "yaPickup.h"

#include "Commons.h"

#include "yaActiveItem.h"
#include "yaPassiveItem.h"

namespace ya
{
	AltarScript::AltarScript()
		: WallScript()
		, mItem(nullptr)
	{
	}
	AltarScript::~AltarScript()
	{
	}
	void AltarScript::Initialize()
	{
		Transform* altarTr = GetOwner()->GetComponent<Transform>();
		altarTr->SetScale(Vector3(0.64f, 0.64f, 1.0f));

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> material = Resources::Find<Material>(L"itemaltarMaterial");
		std::shared_ptr<Texture> texture = material->GetTexture();

		ImageRenderer* rd = GetOwner()->AddComponent<ImageRenderer>();
		rd->SetMesh(mesh);
		rd->SetMaterial(material);
		rd->SetImageSize(texture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f));

		Collider2D* collider = GetOwner()->GetComponent<Collider2D>();
		collider->SetSize(Vector2(0.5f, 0.5f));
	}
	void AltarScript::Update()
	{
		if (mItem == nullptr)
			return;

		Transform* tr = mItem->GetComponent<Transform>();
		tr->SetPosition(Vector3(0.0f, 0.6f + SinByTime(0.007f, 0.05f), 0.0f));

		WallScript::Update();
	}

	void AltarScript::FixedUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		tr->SetPosition(Vector3(pos.x, pos.y, PositionZ(pos.y)));

		WallScript::FixedUpdate();
	}
	void AltarScript::Render()
	{
		WallScript::Render();
	}

	void AltarScript::OnCollisionEnter(Collider2D* collider)
	{
		if(mItem != nullptr)
		{
			ActiveItem* activeItem = dynamic_cast<ActiveItem*>(mItem);
			if (activeItem != nullptr && activeItem->GetActveItemType() != eActiveItem::None)
			{
				GameObject* other = collider->GetOwner();
				Player* player = dynamic_cast<Player*>(other);

				if (player != nullptr)
				{
					PlayerScript* playerScript = player->GetScript<PlayerScript>();
					if (playerScript->IsGainItem())
					{
						Player::Items item = player->GetItem();
						eActiveItem temp = item.activeItem;
						
						playerScript->gainActiveItem(activeItem);

						if (temp == eActiveItem::None)
						{
							mItem->Pause();
							SetItem(nullptr);
						}
						else
							activeItem->SetActiveItemType(temp);
					}
				}
			}

			PassiveItem* passiveItem = dynamic_cast<PassiveItem*>(mItem);
			if (passiveItem != nullptr)
			{
				GameObject* other = collider->GetOwner();
				Player* player = dynamic_cast<Player*>(other);
				if (player != nullptr)
				{
					PlayerScript* playerScript = player->GetScript<PlayerScript>();

					if (playerScript->IsGainItem())
					{
						//playerScript->gainPassiveItem(dynamic_cast<PassiveItem*>(GetOwner()));
					}
				}
			}

		}

		WallScript::OnCollisionEnter(collider);
	}
	void AltarScript::OnCollisionStay(Collider2D* collider)
	{
		WallScript::OnCollisionStay(collider);
	}
	void AltarScript::OnCollisionExit(Collider2D* collider)
	{
		WallScript::OnCollisionExit(collider);
	}
	void AltarScript::OnTriggerEnter(Collider2D* collider)
	{
		WallScript::OnTriggerEnter(collider);
	}
	void AltarScript::OnTriggerStay(Collider2D* collider)
	{
		WallScript::OnTriggerStay(collider);
	}
	void AltarScript::OnTriggerExit(Collider2D* collider)
	{
		WallScript::OnTriggerExit(collider);
	}
	void AltarScript::SetItem(Item* item)
	{
		mItem = item;
		item->Active();

		if (item == nullptr)
			return;

		item->SetParent(GetOwner());
		Transform* tr = item->GetComponent<Transform>();
		tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		tr->SetPosition(Vector3(0.0f, 0.6f, 0.0f));

		Collider2D* collider = item->GetComponent<Collider2D>();
		collider->Disable(true);
	}
}