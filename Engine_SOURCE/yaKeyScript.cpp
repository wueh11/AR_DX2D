#include "yaKeyScript.h"

#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaResources.h"
#include "yaImageRenderer.h"
#include "yaObject.h"

#include "yaPlayer.h"

namespace ya
{
	KeyScript::KeyScript()
		: PickupScript()
	{
	}
	KeyScript::~KeyScript()
	{
	}
	void KeyScript::Initialize()
	{
		PickupScript::Initialize();

		mTransform = GetOwner()->GetComponent<Transform>();
		mTransform->SetScale(Vector3(0.33f, 0.66f, 1.0f));

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		std::shared_ptr<Material> keyMaterial = Resources::Find<Material>(L"keyMaterial");
		std::shared_ptr<Texture> keyTexture = keyMaterial->GetTexture();

		ImageRenderer* keyMr = GetOwner()->AddComponent<ImageRenderer>();
		keyMr->SetMesh(mesh);
		keyMr->SetMaterial(keyMaterial);
		keyMr->SetImageSize(keyTexture, Vector2(0.0f, 0.0f), Vector2(16.0f, 32.0f));

	}
	void KeyScript::Update()
	{
		PickupScript::Update();
	}

	void KeyScript::FixedUpdate()
	{
		PickupScript::FixedUpdate();
	}
	void KeyScript::Render()
	{
		PickupScript::Render();
	}

	void KeyScript::OnCollisionEnter(Collider2D* collider)
	{
		if (mbDeath)
			return;

		GameObject* other = collider->GetOwner();

		Player* player = dynamic_cast<Player*>(other);
		if (player != nullptr)
		{
			player->AddKey(1);
			mbDeath = true;
		}

		PickupScript::OnCollisionEnter(collider);
	}
	void KeyScript::OnCollisionStay(Collider2D* collider)
	{
		PickupScript::OnCollisionStay(collider);
	}
	void KeyScript::OnCollisionExit(Collider2D* collider)
	{
		PickupScript::OnCollisionExit(collider);
	}

	void KeyScript::OnTriggerEnter(Collider2D* collider)
	{
		PickupScript::OnTriggerEnter(collider);
	}
	void KeyScript::OnTriggerStay(Collider2D* collider)
	{
		PickupScript::OnTriggerStay(collider);
	}
	void KeyScript::OnTriggerExit(Collider2D* collider)
	{
		PickupScript::OnTriggerExit(collider);
	}
}