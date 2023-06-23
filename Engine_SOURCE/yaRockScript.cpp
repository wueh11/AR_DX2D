#include "yaRockScript.h"
#include "yaRock.h"

#include "yaResources.h"
#include "yaObject.h"

#include "yaSpriteRenderer.h"
#include "yaTransform.h"
#include "yaRigidbody.h"
#include "yaAudioClip.h"

#include "Commons.h"

#include "yaGameObject.h"
#include "yaSoulHeartFull.h"
#include "yaRoom.h"
#include "yaMonster.h"
#include "yaPlayer.h"
#include "yaExplosion.h"

namespace ya
{
	RockScript::RockScript()
		: WallScript()
	{
	}
	RockScript::~RockScript()
	{
	}
	void RockScript::Initialize()
	{
		Transform* transform = GetOwner()->GetComponent<Transform>();
		transform->SetScale(Vector3(0.66f, 0.66f, 1.0f));

		Collider2D* collider = GetOwner()->GetComponent<Collider2D>();
		collider->SetSize(Vector2(0.6f, 0.6f));

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		std::shared_ptr<Material> spikesMaterial = Resources::Find<Material>(L"rocks_basementMaterial");
		std::shared_ptr<Texture> spikesTexture = spikesMaterial->GetTexture();

		SpriteRenderer* spikesMr = GetOwner()->AddComponent<SpriteRenderer>();
		spikesMr->SetMesh(mesh);
		spikesMr->SetMaterial(spikesMaterial);

		Animator* animator = GetOwner()->AddComponent<Animator>();
		animator->Create(L"None", spikesTexture, Vector2(96.0f, 128.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"rock_1", spikesTexture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"rock_2", spikesTexture, Vector2(32.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"rock_3", spikesTexture, Vector2(64.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"rock_2x2", spikesTexture, Vector2(0.0f, 96.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"rock_1x2", spikesTexture, Vector2(0.0f, 160.0f), Vector2(32.0f, 64.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"rock_2x1", spikesTexture, Vector2(0.0f, 224.0f), Vector2(64.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"iron", spikesTexture, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"rock_item", spikesTexture, Vector2(32.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"jar_1", spikesTexture, Vector2(64.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"jar_2", spikesTexture, Vector2(64.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"jar_3", spikesTexture, Vector2(64.0f, 96.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		animator->Play(L"None", false);
	}

	void RockScript::Update()
	{
		WallScript::Update();
	}
	void RockScript::FixedUpdate()
	{
		WallScript::FixedUpdate();
	}
	void RockScript::Render()
	{
		WallScript::Render();
	}

	void RockScript::OnCollisionEnter(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();

		Explosion* explosion = dynamic_cast<Explosion*>(other);
		if (explosion != nullptr)
		{
			GetOwner()->Death();

			std::shared_ptr<AudioClip> clip = Resources::Find<AudioClip>(L"maggot enter ground ");
			clip->Play();

			Rock* rock = dynamic_cast<Rock*>(GetOwner());
			Rock::eRockType rockType = rock->GetRockType();
			if (rockType == Rock::eRockType::RockItem)
			{
				Room* room = dynamic_cast<Room*>(rock->GetParent());
				if(room != nullptr)
				{
					SoulHeartFull* heart = object::Instantiate<SoulHeartFull>(eLayerType::Item, room);

					Transform* itemTr = heart->GetComponent<Transform>();
					itemTr->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
					itemTr->SetHeight(0.4f);

					Rigidbody* rigidbody = heart->GetComponent<Rigidbody>();
					rigidbody->SetHeightGround(false);
					rigidbody->SetLimitVelocity(Vector3(5.0f, 5.0f, 0.0f));
					rigidbody->AddForce(Vector3((float)Random(-10, 10) * 600.0f, (float)Random(-10, 10) * 600.0f, 0.0f));
					rigidbody->AddHeightForce(400.0f);
				}
			}

			return;
		}

		Player* player = dynamic_cast<Player*>(other);
		Monster* monster = dynamic_cast<Monster*>(other);
		if (player == nullptr && monster == nullptr)
			return;

		WallScript::OnCollisionEnter(collider);
	}

	void RockScript::OnCollisionStay(Collider2D* collider)
	{
		WallScript::OnCollisionStay(collider);
	}
	void RockScript::OnCollisionExit(Collider2D* collider)
	{
		WallScript::OnCollisionExit(collider);
	}

	void RockScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void RockScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void RockScript::OnTriggerExit(Collider2D* collider)
	{
	}
	void RockScript::SetRockType(Rock::eRockType type)
	{
		Rock* rock = dynamic_cast<Rock*>(GetOwner());
		Animator* animator = rock->GetComponent<Animator>();

		Rock::eRockType rockType = rock->GetRockType();

		if (rockType == Rock::eRockType::Rock)
			animator->Play(L"rock_" + std::to_wstring(Random(1, 3)), false);
		else if (rockType == Rock::eRockType::RockItem)
			animator->Play(L"rock_item", false);
		else if (rockType == Rock::eRockType::Rock1x2)
			animator->Play(L"rock_1x2", false);
		else if (rockType == Rock::eRockType::Rock2x1)
			animator->Play(L"rock_2x1", false);
		else if (rockType == Rock::eRockType::Rock2x2)
			animator->Play(L"rock_2x2", false);
		else if (rockType == Rock::eRockType::Iron)
			animator->Play(L"iron", false);
		else if (rockType == Rock::eRockType::Jar)
			animator->Play(L"jar_" + std::to_wstring(Random(1, 3)), false);
	}
}