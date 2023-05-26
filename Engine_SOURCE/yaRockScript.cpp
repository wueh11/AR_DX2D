#include "yaRockScript.h"
#include "yaRock.h"

#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaObject.h"

#include "yaPlayer.h"

#include "yaResources.h"
#include "yaSpriteRenderer.h"

#include "Commons.h"

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
		Player* player = dynamic_cast<Player*>(other);

		if (player == nullptr)
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
			animator->Play(L"rock_" + std::to_wstring(random(1, 3)), false);
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
			animator->Play(L"jar_" + std::to_wstring(random(1, 3)), false);
	}
}