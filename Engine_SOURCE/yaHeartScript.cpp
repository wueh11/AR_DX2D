#include "yaHeartScript.h"

#include "yaGameObject.h"
#include "yaTransform.h"

#include "yaResources.h"
#include "yaImageRenderer.h"
#include "yaObject.h"

#include "yaPlayer.h"
#include "yaPickup.h"

namespace ya
{
	HeartScript::HeartScript()
		: PickupScript()
	{
	}
	HeartScript::~HeartScript()
	{
	}

	void HeartScript::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
		mTransform->SetPosition(Vector3(0.0f, 2.0f, 1.0f));
		mTransform->SetScale(Vector3(0.66f, 0.66f, 1.0f));

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		std::shared_ptr<Material> heartMaterial = Resources::Find<Material>(L"heartMaterial");
		std::shared_ptr<Texture> heartTexture = heartMaterial->GetTexture();

		ImageRenderer* heartMr = GetOwner()->AddComponent<ImageRenderer>();
		heartMr->SetMesh(mesh);
		heartMr->SetMaterial(heartMaterial);

		Pickup* item = dynamic_cast<Pickup*>(GetOwner());
		isaac::eItemType itemType = item->GetItemType();
		if (itemType == eItemType::HeartFull)
			heartMr->SetImageSize(heartTexture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f));
		else if (itemType == eItemType::HeartHalf)
			heartMr->SetImageSize(heartTexture, Vector2(32.0f, 0.0f), Vector2(32.0f, 32.0f));
		else if (itemType == eItemType::SoulHeartFull)
			heartMr->SetImageSize(heartTexture, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f));

	}
	void HeartScript::Update()
	{
		PickupScript::Update();
	}

	void HeartScript::FixedUpdate()
	{
		PickupScript::FixedUpdate();
	}
	void HeartScript::Render()
	{
		PickupScript::Render();
	}

	void HeartScript::OnCollisionEnter(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();
		Player* player = dynamic_cast<Player*>(other);

		if (mbDeath)
			return;

		if(player != nullptr)
		{
			Player::Info info = player->GetInfo();
			Pickup* item = dynamic_cast<Pickup*>(GetOwner());
			isaac::eItemType itemType = item->GetItemType();

			if (info.heartMax < 12 && itemType == eItemType::SoulHeartFull)
			{
				player->AddSoulHeart(2);
				mbDeath = true;
			}
			else if (info.heartMax > info.heart && itemType == eItemType::HeartFull)
			{
				player->AddHeart(2);
				mbDeath = true;
			}
			else if (info.heartMax > info.heart && itemType == eItemType::HeartHalf)
			{
				player->AddHeart(1);
				mbDeath = true;
			}
		}

		PickupScript::OnCollisionEnter(collider);
	}

	void HeartScript::OnCollisionStay(Collider2D* collider)
	{
		PickupScript::OnCollisionStay(collider);
	}

	void HeartScript::OnCollisionExit(Collider2D* collider)
	{
		PickupScript::OnCollisionExit(collider);
	}
	void HeartScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void HeartScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void HeartScript::OnTriggerExit(Collider2D* collider)
	{
	}
}