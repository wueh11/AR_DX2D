#include "yaSpikeScript.h"

#include "Commons.h"
#include "yaResources.h"

#include "yaObject.h"
#include "yaTransform.h"
#include "yaSpriteRenderer.h"

#include "yaPlayer.h"
#include "yaPlayerScript.h"

namespace ya
{
	SpikeScript::SpikeScript()
		: Script()
	{
	}
	SpikeScript::~SpikeScript()
	{
	}
	void SpikeScript::Initialize()
	{
		Transform* transform = GetOwner()->GetComponent<Transform>();
		transform->SetScale(Vector3(0.66f, 0.66f, 1.0f));

		Animator* animator = GetOwner()->AddComponent<Animator>();

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		std::shared_ptr<Material> spikesMaterial = Resources::Find<Material>(L"spikesMaterial");
		std::shared_ptr<Texture> spikesTexture = spikesMaterial->GetTexture();

		SpriteRenderer* spikesMr = GetOwner()->AddComponent<SpriteRenderer>();
		spikesMr->SetMesh(mesh);
		spikesMr->SetMaterial(spikesMaterial);

		animator->Create(L"None", spikesTexture, Vector2(0.0f, 128.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"spike_1", spikesTexture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"spike_2", spikesTexture, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"spike_3", spikesTexture, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"spike_4", spikesTexture, Vector2(0.0f, 96.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"spike_change", spikesTexture, Vector2(64.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 5, 0.1f, 1, 5);

		animator->Play(L"spike_" + std::to_wstring(random(1, 4)), false);
	}

	void SpikeScript::Update()
	{
	}

	void SpikeScript::FixedUpdate()
	{
	}
	void SpikeScript::Render()
	{
	}

	void SpikeScript::OnCollisionEnter(Collider2D* collider)
	{
	}

	void SpikeScript::OnCollisionStay(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();
		Player* player = dynamic_cast<Player*>(other);

		if (player != nullptr)
		{
			PlayerScript* playerScript = player->GetScript<PlayerScript>();
			if (playerScript == nullptr)
				return;

			if (player->GetComponent<Transform>()->GetHeight() > 0)
				return;

			playerScript->Hurt();
		}
	}
	void SpikeScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void SpikeScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void SpikeScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void SpikeScript::OnTriggerExit(Collider2D* collider)
	{
	}
}