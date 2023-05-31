#include "yaPitScript.h"
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
	PitScript::PitScript()
		: WallScript()
	{
	}
	PitScript::~PitScript()
	{
	}
	void PitScript::Initialize()
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

		// ¿ì ÇÏ ÁÂ »ó //¿¬°á
		/*
			¿ìÇÏÁÂ»ó
			1000 0100 0010 0001
			1010 0101 1100 0110
			0011 1001 1110 0111
			0000 0000 1101 1111
			1011 1101 0111 0001
			0001 1100 0110 1010
			1111 0101 0101 0011
			1001 0001 1110 1110
			1110
		*/

		Animator* animator = GetOwner()->AddComponent<Animator>();
		animator->Create(L"None", spikesTexture, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2::Zero, 1, 0.1f);

		animator->Create(L"pit_8_0", spikesTexture, Vector2(00.0f, 0.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"pit_4_0", spikesTexture, Vector2(26.0f, 0.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"pit_2_0", spikesTexture, Vector2(52.0f, 0.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"pit_1_0", spikesTexture, Vector2(78.0f, 0.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);

		animator->Create(L"pit_A_0", spikesTexture, Vector2(00.0f, 26.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"pit_5_0", spikesTexture, Vector2(26.0f, 26.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"pit_C_0", spikesTexture, Vector2(52.0f, 26.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"pit_6_0", spikesTexture, Vector2(78.0f, 26.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);

		animator->Create(L"pit_3_0", spikesTexture, Vector2(00.0f, 52.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"pit_9_0", spikesTexture, Vector2(26.0f, 52.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"pit_E_0", spikesTexture, Vector2(52.0f, 52.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"pit_7_0", spikesTexture, Vector2(78.0f, 52.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);

		animator->Create(L"pit_0_0", spikesTexture, Vector2(00.0f, 78.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"pit_0_1", spikesTexture, Vector2(26.0f, 78.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"pit_D_0", spikesTexture, Vector2(52.0f, 78.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"pit_F_0", spikesTexture, Vector2(78.0f, 78.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);

		animator->Create(L"pit_B_0", spikesTexture, Vector2(00.0f, 104.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"pit_D_1", spikesTexture, Vector2(26.0f, 104.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"pit_7_1", spikesTexture, Vector2(52.0f, 104.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"pit_1_1", spikesTexture, Vector2(78.0f, 104.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);

		animator->Create(L"pit_1_2", spikesTexture, Vector2(00.0f, 130.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"pit_C_1", spikesTexture, Vector2(26.0f, 130.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"pit_5_1", spikesTexture, Vector2(52.0f, 130.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"pit_A_1", spikesTexture, Vector2(78.0f, 130.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);

		animator->Create(L"pit_F_1", spikesTexture, Vector2(00.0f, 156.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"pit_5_2", spikesTexture, Vector2(26.0f, 156.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"pit_5_3", spikesTexture, Vector2(52.0f, 156.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"pit_3_1", spikesTexture, Vector2(78.0f, 156.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);

		animator->Create(L"pit_9_1", spikesTexture, Vector2(00.0f, 182.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"pit_1_3", spikesTexture, Vector2(26.0f, 182.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"pit_E_1", spikesTexture, Vector2(52.0f, 182.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"pit_E_2", spikesTexture, Vector2(78.0f, 182.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);

		animator->Create(L"pit_E_3", spikesTexture, Vector2(78.0f, 208.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);

		animator->Play(L"None", false);
	}

	void PitScript::Update()
	{
		WallScript::Update();
	}
	void PitScript::FixedUpdate()
	{
		WallScript::FixedUpdate();
	}
	void PitScript::Render()
	{
		WallScript::Render();
	}

	void PitScript::OnCollisionEnter(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();
		Player* player = dynamic_cast<Player*>(other);

		if (player != nullptr)
		{
		}

		WallScript::OnCollisionEnter(collider);
	}

	void PitScript::OnCollisionStay(Collider2D* collider)
	{
		WallScript::OnCollisionStay(collider);
	}
	void PitScript::OnCollisionExit(Collider2D* collider)
	{
		WallScript::OnCollisionExit(collider);
	}
	void PitScript::OnTriggerEnter(Collider2D* collider)
	{
		WallScript::OnTriggerEnter(collider);
	}
	void PitScript::OnTriggerStay(Collider2D* collider)
	{
		WallScript::OnTriggerStay(collider);
	}
	void PitScript::OnTriggerExit(Collider2D* collider)
	{
		WallScript::OnTriggerExit(collider);
	}
}