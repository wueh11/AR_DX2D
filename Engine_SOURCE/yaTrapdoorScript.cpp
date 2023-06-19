#include "yaTrapdoorScript.h"
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
	TrapdoorScript::TrapdoorScript()
		: Script()
		, mbOpen(false)
		, mbCreateComplete(false)
	{
	}
	TrapdoorScript::~TrapdoorScript()
	{
	}
	void TrapdoorScript::Initialize()
	{
		Transform* transform = GetOwner()->GetComponent<Transform>();
		//transform->SetScale(Vector3(0.64f, 0.64f, 1.0f));

		Collider2D* collider = GetOwner()->GetComponent<Collider2D>();
		collider->SetSize(Vector2(0.8f, 0.8f));

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		std::shared_ptr<Material> trapdoorMaterial = Resources::Find<Material>(L"trapdoorMaterial");
		std::shared_ptr<Texture> trapdoorTexture = trapdoorMaterial->GetTexture();

		SpriteRenderer* trapdoorMr = GetOwner()->AddComponent<SpriteRenderer>();
		trapdoorMr->SetMesh(mesh);
		trapdoorMr->SetMaterial(trapdoorMaterial);

		Animator* animator = GetOwner()->AddComponent<Animator>();
		animator->Create(L"none", trapdoorTexture, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2::Zero, 3, 0.1f);
		animator->Create(L"door_opened", trapdoorTexture, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"door_open", trapdoorTexture, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 3, 0.1f);
		animator->Add(L"door_open", trapdoorTexture, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"door_close", trapdoorTexture, Vector2(0.0f, 64.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 3, 0.1f);
		animator->Add(L"door_close", trapdoorTexture, Vector2(0.0f, 64.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 1, 0.1f);

		animator->Play(L"door_close", false);

		animator->GetCompleteEvent(L"door_close") = std::bind(&TrapdoorScript::OpenTrapDoor, this);
	}

	void TrapdoorScript::Update()
	{
	}
	void TrapdoorScript::FixedUpdate()
	{
	}
	void TrapdoorScript::Render()
	{
	}

	void TrapdoorScript::OnCollisionEnter(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();
		Player* player = dynamic_cast<Player*>(other);

		if (player != nullptr)
		{
			if (mbOpen)
			{
				int a = 0;
			}
		
		}
	}

	void TrapdoorScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void TrapdoorScript::OnCollisionExit(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();
		Player* player = dynamic_cast<Player*>(other);

		if (player != nullptr)
		{
			/*if(!mbCreateComplete)
			{
				mbCreateComplete = true;
				Animator* animator = GetOwner()->GetComponent<Animator>();
				animator->Play(L"door_open", false);
			}*/
		}
	}

	void TrapdoorScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void TrapdoorScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void TrapdoorScript::OnTriggerExit(Collider2D* collider)
	{
	}
	void TrapdoorScript::OpenTrapDoor()
	{
		mbOpen = true;
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->Play(L"door_opened");
	}
}