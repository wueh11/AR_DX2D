#include "yaRoom.h"
#include "yaObject.h"
#include "yaResources.h"

#include "yaPlayer.h"

#include "yaMeshRenderer.h"
#include "yaImageRenderer.h"

#include "yaWallScript.h"
#include "yaPlayerScript.h"
#include "yaUIScript.h"

#include "yaMonster.h"
#include "yaDoor.h"
#include "yaFireplace.h"
#include "yaPit.h"
#include "yaRock.h"
#include "yaSpike.h"
#include "yaItem.h"

#include "yaStageScene.h"

namespace ya
{
	Room::Room(int x, int y)
		: GameObject()
		, mMonsterCount(0)
		, mbActive(false)
		, mbClear(false)
		, mbLock(false)
		, mGrid{}
		, mRoomPos(x, y)
	{
	}
	Room::~Room()
	{
	}
	void Room::Initialize()
	{
		GameObject::Initialize();

		Transform* tr = GetComponent<Transform>();
		tr->SetPosition(Vector3(mRoomPos.y * 7.0f, mRoomPos.x * -4.0f, 0.0f));

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		for (size_t i = 0; i < 2; i++)
		{
			for (size_t j = 0; j < 2; j++)
			{
				GameObject* basement = object::Instantiate<GameObject>(eLayerType::Background, tr);
				Transform* basementTr = basement->GetComponent<Transform>();
				basementTr->SetPosition(Vector3(-2.1f + (4.2f * i), 1.36f + (-2.72f * j), 0.0f));
				basementTr->SetRotation(Vector3(XM_PI * j, XM_PI * i, 0.0f));
				basementTr->SetScale(Vector3(4.4f, 2.72f, 1.0f));

				ImageRenderer* basementMr = basement->AddComponent<ImageRenderer>();
				basementMr->SetMesh(mesh);
				std::shared_ptr<Material> basementMaterial = Resources::Find<Material>(L"basementMaterial");
				basementMr->SetMaterial(basementMaterial);

				std::shared_ptr<Texture> basementTexture = basementMaterial->GetTexture();
				basementMr->SetImageSize(basementTexture, Vector2::Zero, Vector2(220.5f, 142.0f));
			}
		}

		// Wall Collider
		{
			for (size_t i = 0; i < 2; i++)
			{
				for (size_t j = 0; j < 2; j++)
				{
					GameObject* wall = object::Instantiate<GameObject>(eLayerType::Wall, tr);
					Transform* wallTr = wall->GetComponent<Transform>();
					wallTr->SetPosition(Vector3(-2.0f + (4.0f * j), 2.0f + (-4.0f * i), 0.0f));
					wall->AddComponent<WallScript>();
					Collider2D* collider = wall->AddComponent<Collider2D>();
					collider->SetSize(Vector2(3.2f, 0.2f));
					collider->SetColliderType(eColliderType::Rect);
				}
			}

			for (size_t i = 0; i < 2; i++)
			{
				for (size_t j = 0; j < 2; j++)
				{
					GameObject* wall = object::Instantiate<GameObject>(eLayerType::Wall, tr);
					Transform* wallTr = wall->GetComponent<Transform>();
					wallTr->SetPosition(Vector3(-3.4f + (6.8f * j), 1.3f + (-2.6f * i), 0.0f));
					wall->AddComponent<WallScript>();
					Collider2D* collider = wall->AddComponent<Collider2D>();
					collider->SetSize(Vector2(0.2f, 1.8f));
					collider->SetColliderType(eColliderType::Rect);
				}
			}
		}

		{ // shading
			GameObject* shading = object::Instantiate<GameObject>(eLayerType::Background, tr);
			Transform* shadingTr = shading->GetComponent<Transform>();
			shadingTr->SetPosition(Vector3(0.0f, 0.0f, 0.5f));
			shadingTr->SetScale(Vector3(8.7f, 6.0f, 1.0f));

			MeshRenderer* shadingMr = shading->AddComponent<MeshRenderer>();
			shadingMr->SetMesh(mesh);
			std::shared_ptr<Material> shadingMaterial = Resources::Find<Material>(L"shadingMaterial");
			shadingMr->SetMaterial(shadingMaterial);
		}

		StageScene* stage = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());
		if(stage != nullptr)
		{
			// 주위에 방이 있는 경우 문 생성
			//상
			if (stage->GetRoom(mRoomPos.x - 1, mRoomPos.y) != nullptr)
			{
				Door* door = object::Instantiate<Door>(eLayerType::Land, tr);
				Transform* doorTr = door->GetComponent<Transform>();
				//doorTr->SetPosition(Vector3(0.0f, -1.2f, 0.0f));
				AddRoomObject(door, 0, 6);
			}

			//하
			if (stage->GetRoom(mRoomPos.x + 1, mRoomPos.y) != nullptr)
			{
				Door* door = object::Instantiate<Door>(eLayerType::Land, tr);
				Transform* doorTr = door->GetComponent<Transform>();
				//doorTr->SetPosition(Vector3(0.0f, 1.2f, 0.0f));
				AddRoomObject(door, 6, 6);
			}

			//좌
			if (stage->GetRoom(mRoomPos.x, mRoomPos.y - 1) != nullptr)
			{
				Door* door = object::Instantiate<Door>(eLayerType::Land, tr);
				Transform* doorTr = door->GetComponent<Transform>();
				//doorTr->SetPosition(Vector3(-3.6f, 0.0f, 0.0f));
				AddRoomObject(door, 3, 0);
			}

			//우
			if (stage->GetRoom(mRoomPos.x, mRoomPos.y + 1) != nullptr)
			{
				Door* door = object::Instantiate<Door>(eLayerType::Land, tr);
				Transform* doorTr = door->GetComponent<Transform>();
				//doorTr->SetPosition(Vector3(3.6f, 0.0f, 0.0f));
				AddRoomObject(door, 3, 12);
			}
		}
	}

	void Room::Update()
	{
		GameObject::Update();
	}
	void Room::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Room::Render()
	{
		GameObject::Render();
	}
	void Room::AddRoomObject(GameObject* roomObj, int x, int y)
	{
		if (x < 0 || y < 0)
		{
			/*while (true)
			{
				int x, y;
				x = random(0, 7);
				y = random(0, 13);
				
				if (mGrid[x][y] == nullptr)
				{
					mGrid[x][y] = roomObj;
					break;
				}
			}*/
		}
		else
		{
			Monster* monster = dynamic_cast<Monster*>(roomObj);
			if (monster != nullptr)
				mMonsterCount++;

			mGrid[x][y] = roomObj;

			Transform* tr = roomObj->GetComponent<Transform>();
			tr->SetPosition(Vector3((y - 6) * 0.64f, (x - 3) * 0.8f, 0.0f));
		}
	}
	void Room::SetRoomPos(Vector2 roomPos)
	{
		mRoomPos = roomPos;
		
		Transform* tr = GetComponent<Transform>();
		tr->SetPosition(Vector3(roomPos.x * 3.4f, roomPos.y * 2.0f, 0.0f));
	}
}