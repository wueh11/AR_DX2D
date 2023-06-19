#include "yaChestScript.h"
#include "yaChest.h"

#include "yaPlayer.h"
#include "yaPlayerScript.h"

#include "yaRigidbody.h"

#include "yaResources.h"
#include "yaSpriteRenderer.h"

#include "yaSceneManager.h"
#include "yaScene.h"
#include "yaStageScene.h"
#include "yaRoom.h"

#include "yaPickup.h"

#include "Commons.h"

#include "yaActiveItem.h"
#include "yaPassiveItem.h"

#include "yaObject.h"
#include "yaExplosion.h"
namespace ya
{
	ChestScript::ChestScript()
		: PickupScript()
		, mChestType(eChestType::Normal)
		, mbOpen(false)
	{
	}
	ChestScript::~ChestScript()
	{
	}
	void ChestScript::Initialize()
	{
		PickupScript::Initialize();

		Transform* altarTr = GetOwner()->GetComponent<Transform>();
		altarTr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> material = Resources::Find<Material>(L"chestsMaterial");
		std::shared_ptr<Texture> texture = material->GetTexture();

		Collider2D* collider = GetOwner()->GetComponent<Collider2D>();
		collider->SetSize(Vector2(0.6f, 0.6f));

		mTransform = GetOwner()->GetComponent<Transform>();
		mTransform->SetScale(Vector3(0.64f, 0.64f, 1.0f));

		SpriteRenderer* rd = GetOwner()->AddComponent<SpriteRenderer>();
		rd->SetMesh(mesh);
		rd->SetMaterial(material);

		mAnimator = GetOwner()->AddComponent<Animator>();
		mAnimator->Create(L"Normal", texture, Vector2(0.0f, 48.0f), Vector2(32.0f, 32.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
		mAnimator->Create(L"Normal_Open", texture, Vector2(32.0f, 48.0f), Vector2(32.0f, 32.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
		mAnimator->Create(L"Spike", texture, Vector2(64.0f, 48.0f), Vector2(32.0f, 32.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
		mAnimator->Create(L"Spike_Open", texture, Vector2(96.0f, 48.0f), Vector2(32.0f, 32.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
		mAnimator->Create(L"Treasure", texture, Vector2(0.0f, 80.0f), Vector2(32.0f, 32.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
		mAnimator->Create(L"Treasure_Open", texture, Vector2(32.0f, 80.0f), Vector2(32.0f, 32.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
		mAnimator->Create(L"Rock", texture, Vector2(192.0f, 224.0f), Vector2(32.0f, 32.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
		mAnimator->Create(L"Rock_Open", texture, Vector2(224.0f, 224.0f), Vector2(32.0f, 32.0f), Vector2(0.0f, 0.0f), 1, 0.1f);
		mAnimator->Play(L"Normal");
	}
	void ChestScript::Update()
	{
		PickupScript::Update();
	}

	void ChestScript::FixedUpdate()
	{
		PickupScript::FixedUpdate();
	}
	void ChestScript::Render()
	{
		PickupScript::Render();
	}

	void ChestScript::OnCollisionEnter(Collider2D* collider)
	{
		if (mbOpen)
			return;

		GameObject* other = collider->GetOwner();
		Player* player = dynamic_cast<Player*>(other);

		if(mChestType == eChestType::Normal)
		{
			OpenChest();
		}
		else if (mChestType == eChestType::Treasure)
		{
			if(player != nullptr && player->GetPickup().key > 0)
				player->AddKey(-1);
				OpenChest();
		}
		else if (mChestType == eChestType::Rock)
		{
			Explosion* explosion = dynamic_cast<Explosion*>(other);
			if(explosion != nullptr)
				OpenChest();
		}

		//PickupScript::OnCollisionEnter(collider);
	}

	void ChestScript::OnCollisionStay(Collider2D* collider)
	{
		if (mbOpen)
			return;

		PickupScript::OnCollisionStay(collider);
	}
	void ChestScript::OnCollisionExit(Collider2D* collider)
	{
		if (mbOpen)
			return;

		PickupScript::OnCollisionExit(collider);
	}
	void ChestScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void ChestScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void ChestScript::OnTriggerExit(Collider2D* collider)
	{
	}
	void ChestScript::OpenChest()
	{
		mbOpen = true;

		if (mChestType == eChestType::Normal)
			mAnimator->Play(L"Normal_Open");
		else if (mChestType == eChestType::Spike)
			mAnimator->Play(L"Spike_Open");
		else if (mChestType == eChestType::Treasure)
			mAnimator->Play(L"Treasure_Open");
		else if (mChestType == eChestType::Rock)
			mAnimator->Play(L"Rock_Open");

		Chest* chest = dynamic_cast<Chest*>(GetOwner());
		std::vector<Item*> items = chest->GetItems();
		
		Vector3 pos = mTransform->GetPosition();

		Room* room = dynamic_cast<Room*>(chest->GetParent());

		Collider2D* collider = chest->GetComponent<Collider2D>();
		collider->Disable(true);

		for (Item* item : items)
		{
			item->SetParent(room);

			Transform* itemTr = item->GetComponent<Transform>();
			itemTr->SetPosition(pos);
			itemTr->SetHeight(0.4f);
			
			item->SetActive();

			Rigidbody* rigidbody = item->GetComponent<Rigidbody>();
			rigidbody->SetHeightGround(false);
			rigidbody->SetLimitVelocity(Vector3(5.0f, 5.0f, 0.0f));
			rigidbody->AddForce(Vector3((float)Random(-10, 10) * 800.0f, (float)Random(-10, 10) * 800.0f, 0.0f));
			rigidbody->AddHeightForce(500.0f);
		}
	}

	void ChestScript::SetChestType(eChestType type)
	{
		mChestType = type;

		if (mAnimator == nullptr)
			return;

		if(mChestType == eChestType::Normal)
			mAnimator->Play(L"Normal");
		else if(mChestType == eChestType::Spike)
			mAnimator->Play(L"Spike");
		else if(mChestType == eChestType::Treasure)
			mAnimator->Play(L"Treasure");
		else if(mChestType == eChestType::Rock)
			mAnimator->Play(L"Rock");
	}
}