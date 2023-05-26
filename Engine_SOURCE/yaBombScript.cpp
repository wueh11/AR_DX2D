#include "yaBombScript.h"

#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaImageRenderer.h"
#include "yaObject.h"

#include "yaPlayer.h"
#include "yaScene.h"
#include "yaSceneManager.h"
#include "yaRigidbody.h"

namespace ya
{
	BombScript::BombScript()
		: PickupScript()
	{
	}
	BombScript::~BombScript()
	{
	}
	void BombScript::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
		mTransform->SetScale(Vector3(0.66f, 0.66f, 1.0f));

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		std::shared_ptr<Material> bombMaterial = Resources::Find<Material>(L"bombMaterial");
		std::shared_ptr<Texture> bombTexture = bombMaterial->GetTexture();

		ImageRenderer* bombMr = GetOwner()->AddComponent<ImageRenderer>();
		bombMr->SetMesh(mesh);
		bombMr->SetMaterial(bombMaterial);
		bombMr->SetImageSize(bombTexture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f));

	}
	void BombScript::Update()
	{
		PickupScript::Update();
	}
	void BombScript::FixedUpdate()
	{
		PickupScript::FixedUpdate();
	}
	void BombScript::Render()
	{
		PickupScript::Render();
	}

	void BombScript::OnCollisionEnter(Collider2D* collider)
	{
		if (mbDeath)
			return;
		
		GameObject* other = collider->GetOwner();

		Player* player = dynamic_cast<Player*>(other);
		if (player != nullptr)
		{
			player->AddBomb(1);
			mbDeath = true;
		}

		PickupScript::OnCollisionEnter(collider);
	}
	void BombScript::OnCollisionStay(Collider2D* collider)
	{
		PickupScript::OnCollisionStay(collider);
	}
	void BombScript::OnCollisionExit(Collider2D* collider)
	{
		PickupScript::OnCollisionExit(collider);
	}
	void BombScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void BombScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void BombScript::OnTriggerExit(Collider2D* collider)
	{
	}
}