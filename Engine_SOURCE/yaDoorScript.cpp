#include "yaDoorScript.h"

#include "yaTransform.h"
#include "yaGameObject.h"

#include "yaObject.h"
#include "yaResources.h"

#include "yaAnimator.h"
#include "yaSpriteRenderer.h"
#include "yaImageRenderer.h"

#include "yaPlayer.h"
#include "yaPlayerScript.h"

#include "yaDoor.h"

#include "yaSceneManager.h"
#include "yaStageScene.h"
#include "yaExplosion.h"

namespace ya
{
	DoorScript::DoorScript()
		: Script()
		, mDoorframe(nullptr)
		, mDoorLeft(nullptr)
		, mDoorRight(nullptr)
		, mDoorBackground(nullptr)
	{
	}
	DoorScript::~DoorScript()
	{
	}

	void DoorScript::Initialize()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3(1.2f, 1.0f, 1.0f));

		Collider2D* collider = GetOwner()->GetComponent<Collider2D>();
		collider->SetSize(Vector2(1.0f, 0.3f));
		
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> material = Resources::Find<Material>(L"normaldoorMaterial");
		std::shared_ptr<Texture> texture = material->GetTexture();

		{
			mDoorBackground = object::Instantiate<GameObject>(eLayerType::Land, GetOwner());

			ImageRenderer* renderer = mDoorBackground->AddComponent<ImageRenderer>();
			renderer->SetMesh(mesh);
			renderer->SetMaterial(material);
			renderer->SetImageSize(texture, Vector2(64.0f, 0.0f), Vector2(64.0f, 48.0f));
		}
		
		{
			mDoorLeft = object::Instantiate<GameObject>(eLayerType::Land, GetOwner());

			ImageRenderer* renderer = mDoorLeft->AddComponent<ImageRenderer>();
			renderer->SetMesh(mesh);
			renderer->SetMaterial(material);
			renderer->SetImageSize(texture, Vector2(0.0f, 48.0f), Vector2(64.0f, 48.0f));

			mDoorLeft->Pause();
		}

		{
			mDoorRight = object::Instantiate<GameObject>(eLayerType::Land, GetOwner());

			SpriteRenderer* renderer = mDoorRight->AddComponent<SpriteRenderer>();
			renderer->SetMesh(mesh);
			renderer->SetMaterial(material);
	
			Animator* doorAnimator = mDoorRight->AddComponent<Animator>();
			doorAnimator->Create(L"normal", texture, Vector2(64.0f, 48.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"lock", texture, Vector2(64.0f, 96.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Play(L"normal", false);

			mDoorRight->Pause();
		}

		{
			mDoorframe = object::Instantiate<GameObject>(eLayerType::Land, GetOwner());

			SpriteRenderer* renderer = mDoorframe->AddComponent<SpriteRenderer>();
			renderer->SetMesh(mesh);
			renderer->SetMaterial(material);

			Animator* doorAnimator = mDoorframe->AddComponent<Animator>();
			doorAnimator->Create(L"normal", texture, Vector2(0.0f, 0.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"damaged", texture, Vector2(0.0f, 96.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);

			doorAnimator->Play(L"normal", false);
		}
	}

	void DoorScript::Update()
	{
	}

	void DoorScript::FixedUpdate()
	{
	}
	void DoorScript::Render()
	{
	}
	void DoorScript::OnCollisionEnter(Collider2D* collider)
	{
		Door* door = dynamic_cast<Door*>(GetOwner());

		GameObject* gameObject = collider->GetOwner();
		Player* player = dynamic_cast<Player*>(gameObject);

		if (!door->IsOpen())
		{
			Explosion* explosion = dynamic_cast<Explosion*>(gameObject);
			if (explosion != nullptr)
			{
				door->SetOpen(true);
				door->SetDamaged(true);
			}
			else
			{
				return;
			}
		}
		
		if (player != nullptr)
		{
			if (door->IsLock())
			{
				if (player->GetPickup().key > 0)
				{
					player->AddKey(-1);
					door->SetLock(false);
					door->SetOpen(true);
				}
				else
				{
					return;
				}
			}

			Transform* playerTr = player->GetComponent<Transform>();
			Vector3 pos = playerTr->GetPosition();

			Door::eDirection dir = door->GetDirection();

			StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());
			Vector2 roomgrid = scene->GetCurrentRoom()->GetRoomGrid();

			float dist = 0.6f;
			if (dir == Door::eDirection::LEFT)
			{
				pos.x -= dist;
				scene->SetCurrentRoom(roomgrid.x, roomgrid.y - 1);
			}
			else if (dir == Door::eDirection::RIGHT)
			{
				pos.x += dist;
				scene->SetCurrentRoom(roomgrid.x, roomgrid.y + 1);
			}
			else if (dir == Door::eDirection::UP)
			{
				pos.y += dist;
				scene->SetCurrentRoom(roomgrid.x - 1, roomgrid.y);
			}
			else if (dir == Door::eDirection::DOWN)
			{
				pos.y -= dist;
				scene->SetCurrentRoom(roomgrid.x + 1, roomgrid.y);
			}

			playerTr->SetPosition(pos);
		}
	}

	void DoorScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void DoorScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void DoorScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void DoorScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void DoorScript::OnTriggerExit(Collider2D* collider)
	{
	}
	void DoorScript::SetDoorDirection(Door::eDirection dir)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		if (dir == Door::eDirection::UP)
			tr->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
		else if (dir == Door::eDirection::DOWN)
			tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2 * 2));
		else if (dir == Door::eDirection::LEFT)
			tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
		else if (dir == Door::eDirection::RIGHT)
			tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2 * 3));
	}
	void DoorScript::SetOpen(bool open)
	{
		if(open == true)
		{
			mDoorRight->SetActive();
			mDoorLeft->SetActive();
		}
		else
		{
			mDoorRight->Pause();
			mDoorLeft->Pause();
		}
	}
	void DoorScript::SetDamaged(bool damaged)
	{
		mDoorframe->GetComponent<Animator>()->Play(L"damaged");
		dynamic_cast<Door*>(GetOwner())->SetOpen(true);
	}
	void DoorScript::SetLock(bool lock)
	{
		if(lock == true)
			mDoorRight->GetComponent<Animator>()->Play(L"lock");
		else
			mDoorRight->GetComponent<Animator>()->Play(L"normal");
	}
}