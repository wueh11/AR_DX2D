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
#include "yaTime.h"
#include "yaStageScene.h"

namespace ya
{
	TrapdoorScript::TrapdoorScript()
		: Script()
		, mbInTrapdoor(false)
		, mbOpen(true)
		, mbCreateComplete(false)
		, mPlayerTrapdoor(nullptr)
		, mTimer(1.0f)
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
		collider->SetSize(Vector2(0.4f, 0.4f));

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

		{
			mPlayerTrapdoor = object::Instantiate<GameObject>(eLayerType::Background, GetOwner());

			Transform* playerTrapdoorTr = mPlayerTrapdoor->GetComponent<Transform>();
			playerTrapdoorTr->SetScale(Vector3(1.28f, 1.28f, 1.0f));
			playerTrapdoorTr->SetPosition(Vector3(0.0f, 0.5f, -50.0f));

			std::shared_ptr<Material> playerTrapdoorMaterial = Resources::Find<Material>(L"isaacMaterial");
			std::shared_ptr<Texture> playerTrapdoorTexture = playerTrapdoorMaterial->GetTexture();

			SpriteRenderer* playerTrapdoorMr = mPlayerTrapdoor->AddComponent<SpriteRenderer>();
			playerTrapdoorMr->SetMesh(mesh);
			playerTrapdoorMr->SetMaterial(playerTrapdoorMaterial);

			Animator* playerTrapdoorAnimator = mPlayerTrapdoor->AddComponent<Animator>();
			playerTrapdoorAnimator->Create(L"none", playerTrapdoorTexture, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2::Zero, 1, 0.1f);
			playerTrapdoorAnimator->Create(L"trapdoor", playerTrapdoorTexture, Vector2(0.0f, 256.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 2, 0.3f);

			playerTrapdoorAnimator->Play(L"none", false);
		}
	}

	void TrapdoorScript::Update()
	{
		if (mbInTrapdoor)
		{
			if (mTimer < 0.0f)
			{
				mbInTrapdoor = false;
				SceneManager::GetActiveScene()->FadeIn();
			}
			else if (mTimer > 0.7f)
			{
				Transform* tr = mPlayerTrapdoor->GetComponent<Transform>();
				Vector3 pos = tr->GetPosition();
				pos.y += 0.5f * Time::DeltaTime();
				tr->SetPosition(pos);

				Vector3 scale = tr->GetScale();
				scale.x -= Time::DeltaTime();
				scale.y += Time::DeltaTime();
				tr->SetScale(scale);
			}
			else
			{
				Transform* tr = mPlayerTrapdoor->GetComponent<Transform>();
				Vector3 pos = tr->GetPosition();
				pos.y -= 7.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}

			mTimer -= Time::DeltaTime();
		}
	}
	void TrapdoorScript::FixedUpdate()
	{
	}
	void TrapdoorScript::Render()
	{
		Transform* tr = mPlayerTrapdoor->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		//if(pos.y < 0.0f)
		{
			BaseRenderer* rd = mPlayerTrapdoor->GetComponent<BaseRenderer>();
			rd->UseRange(true);
			float newRange = 1.0f + pos.y - 0.32f;
			rd->SetRange(Vector4(0.0f, 0.0f, 1.0f, newRange));
		}
	}

	void TrapdoorScript::OnCollisionEnter(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();
		Player* player = dynamic_cast<Player*>(other);

		if (player != nullptr)
		{
			if (mbOpen)
			{
				mbInTrapdoor = true;
				player->Pause();
				
				Animator* animator = mPlayerTrapdoor->GetComponent<Animator>();
				animator->Play(L"trapdoor", false);
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