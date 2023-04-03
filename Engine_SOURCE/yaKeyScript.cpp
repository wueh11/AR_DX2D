#include "yaKeyScript.h"

#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaImageRenderer.h"
#include "yaObject.h"

#include "yaPlayer.h"
#include "yaScene.h"
#include "yaSceneManager.h"

namespace ya
{
	KeyScript::KeyScript()
		: Script()
		, mTransform(nullptr)
		, mbDeath(false)
		, mTimer(0.1f)
	{
	}
	KeyScript::~KeyScript()
	{
	}
	void KeyScript::Initialize()
	{
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
		if (mTimer < 0.0f)
			Death();

		if (mbDeath && mTimer > 0.0f)
			Take();
	}

	void KeyScript::FixedUpdate()
	{
	}
	void KeyScript::Render()
	{
	}

	void KeyScript::OnCollisionEnter(Collider2D* collider)
	{
		if(!mbDeath)
		{
			Player* player = dynamic_cast<Player*>(collider->GetOwner());
			player->AddKey(1);
			mbDeath = true;
		}

	}
	void KeyScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void KeyScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void KeyScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void KeyScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void KeyScript::OnTriggerExit(Collider2D* collider)
	{
	}
	void KeyScript::Take()
	{
		Vector3 scale = mTransform->GetScale();
		scale.x -= 0.01f;
		scale.y += 0.01f;
		mTransform->SetScale(scale);

		mTimer -= Time::DeltaTime();
	}
	void KeyScript::Death()
	{
		GetOwner()->Death();
	}
}