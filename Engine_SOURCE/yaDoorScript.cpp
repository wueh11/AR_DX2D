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

namespace ya
{
	DoorScript::DoorScript()
		: Script()
	{
	}
	DoorScript::~DoorScript()
	{
	}

	void DoorScript::Initialize()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3(1.5f, 1.5f, 1.5f));
		
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> material = Resources::Find<Material>(L"normaldoorMaterial");
		std::shared_ptr<Texture> texture = material->GetTexture();

		{ // door frame
			GameObject* doorframe = object::Instantiate<GameObject>(eLayerType::Land, tr);
			SpriteRenderer* renderer = doorframe->AddComponent<SpriteRenderer>();
			renderer->SetMesh(mesh);
			renderer->SetMaterial(material);

			Transform* doorframeTr = doorframe->GetComponent<Transform>();
			doorframeTr->SetScale(Vector3(0.66f, 0.66f, 1.0f));

			Animator* doorAnimator = doorframe->AddComponent<Animator>();
			doorAnimator->Create(L"normal", texture, Vector2(0.0f, 0.0f), Vector2(64.0f, 45.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"damaged", texture, Vector2(0.0f, 100.0f), Vector2(64.0f, 45.0f), Vector2::Zero, 1, 1.0f);

			doorAnimator->Play(L"normal", false);
		}

		/*ImageRenderer* renderer = GetOwner()->AddComponent<ImageRenderer>();*/
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
		GameObject* gameObject = collider->GetOwner();

		Player* player = dynamic_cast<Player*>(gameObject);
		if (player != nullptr)
		{
			Transform* playerTr = player->GetComponent<Transform>();
			Vector3 pos = playerTr->GetPosition();

			Door::eDirection dir = dynamic_cast<Door*>(GetOwner())->GetDirection();

			StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());
			Vector2 roomgrid = scene->GetCurrentRoom()->GetRoomGrid();

			float dist = 2.0f;
			if (dir == Door::eDirection::LEFT)
			{
				pos.x += dist;
				scene->SetCurrentRoom(roomgrid.x, roomgrid.y + 1);
			}
			else if (dir == Door::eDirection::RIGHT)
			{
				pos.x -= dist;
				scene->SetCurrentRoom(roomgrid.x, roomgrid.y - 1);
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

			/*
			Vector2 roompos = scene->GetCurrentRoom()->GetRoomPosition();
			Transform* cameraTr = mainCamera->GetOwner()->GetComponent<Transform>();
			cameraTr->SetPosition(Vector3(roompos.x, roompos.y, 0.0f));
			int a = 0;*/
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
}