#include "yaWebScript.h"
#include "yaRock.h"

#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaObject.h"

#include "yaPlayer.h"

#include "yaResources.h"
#include "yaSpriteRenderer.h"

#include "Commons.h"

#include "yaRigidbody.h"

namespace ya
{
	WebScript::WebScript()
		: Script()
		, mPrevSpeed(0.0f)
	{
	}
	WebScript::~WebScript()
	{
	}
	void WebScript::Initialize()
	{
		Transform* transform = GetOwner()->GetComponent<Transform>();
		transform->SetScale(Vector3(0.45f, 0.45f, 1.0f));

		Collider2D* collider = GetOwner()->GetComponent<Collider2D>();
		collider->SetSize(Vector2(0.8f, 0.8f));

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		std::shared_ptr<Material> websMaterial = Resources::Find<Material>(L"webMaterial");
		std::shared_ptr<Texture> websTexture = websMaterial->GetTexture();

		SpriteRenderer* websMr = GetOwner()->AddComponent<SpriteRenderer>();
		websMr->SetMesh(mesh);
		websMr->SetMaterial(websMaterial);

		Animator* animator = GetOwner()->AddComponent<Animator>();
		animator->Create(L"web_1", websTexture, Vector2(0.0f, 0.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"web_2", websTexture, Vector2(26.0f, 0.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"web_3", websTexture, Vector2(0.0f, 26.0f), Vector2(26.0f, 26.0f), Vector2::Zero, 1, 0.1f);

		animator->Play(L"web_" + std::to_wstring(random(1, 3)), false);
	}

	void WebScript::Update()
	{
	}
	void WebScript::FixedUpdate()
	{
	}
	void WebScript::Render()
	{
	}

	void WebScript::OnCollisionEnter(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();
		Player* player = dynamic_cast<Player*>(other);

		if (player != nullptr)
		{
			mPrevSpeed = player->GetStatus().speed;
			player->AddSpeed(-1.0f);
		}
	}

	void WebScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void WebScript::OnCollisionExit(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();
		Player* player = dynamic_cast<Player*>(other);

		if (player != nullptr)
		{
			player->AddSpeed(1.0f);
		}
	}

	void WebScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void WebScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void WebScript::OnTriggerExit(Collider2D* collider)
	{
	}
}