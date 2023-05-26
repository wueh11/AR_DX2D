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
#include "yaFireplace.h"
#include "yaPit.h"
#include "yaRock.h"
#include "yaSpike.h"
#include "yaItem.h"

#include "yaStageScene.h"

#include "yaInput.h"
#include "yaTime.h"

#include "yaIsaacEnums.h"

namespace ya
{
	const float ROOM_GRID_ROW_SIZE = 0.5f;
	const float ROOM_GRID_COLUMN_SIZE = 0.49f;

	Room::Room(int x, int y)
		: GameObject()
		, mRoomType(eRoomType::Normal)
		, mMonsterCount(0)
		, mbClear(false)
		, mbLock(false)
		, mGrid{}
		, mRoomGrid(x, y)
		, mRoomPosition(Vector2::Zero)
	{
		SetName(L"Room[" + std::to_wstring(x) + L", " + std::to_wstring(y) + L"]");
	}
	Room::~Room()
	{
	}
	void Room::Initialize()
	{
		SetRoomPosition(mRoomGrid);

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		for (size_t i = 0; i < 2; i++)
		{
			for (size_t j = 0; j < 2; j++)
			{
				GameObject* basement = object::Instantiate<GameObject>(eLayerType::Background, this);
				Transform* basementTr = basement->GetComponent<Transform>();
				basementTr->SetPosition(Vector3(-2.1f + (4.2f * i), 1.36f + (-2.72f * j), 100.0f));
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
					GameObject* wall = object::Instantiate<GameObject>(eLayerType::Wall, this);
					Transform* wallTr = wall->GetComponent<Transform>();
					wallTr->SetPosition(Vector3(-2.0f + (4.0f * j), 1.86f + (-3.7f * i), 100.0f));
					wallTr->SetScale(Vector3(3.2f, 0.2f, 1.0f));
					wall->AddComponent<WallScript>();
					Collider2D* collider = wall->AddComponent<Collider2D>();
					collider->SetColliderType(eColliderType::Rect);
				}
			}

			for (size_t i = 0; i < 2; i++)
			{
				for (size_t j = 0; j < 2; j++)
				{
					GameObject* wall = object::Instantiate<GameObject>(eLayerType::Wall, this);
					Transform* wallTr = wall->GetComponent<Transform>();
					wallTr->SetPosition(Vector3(-3.4f + (6.8f * j), 1.3f + (-2.6f * i), 100.0f));
					wallTr->SetScale(Vector3(0.2f, 1.8f, 1.0f));
					wall->AddComponent<WallScript>();
					Collider2D* collider = wall->AddComponent<Collider2D>();
					collider->SetColliderType(eColliderType::Rect);
				}
			}
		}

		{ // shading
			GameObject* shading = object::Instantiate<GameObject>(eLayerType::Background, this);
			Transform* shadingTr = shading->GetComponent<Transform>();
			shadingTr->SetPosition(Vector3(0.0f, 0.0f, 100.0f));
			shadingTr->SetScale(Vector3(8.7f, 6.0f, 1.0f));

			MeshRenderer* shadingMr = shading->AddComponent<MeshRenderer>();
			shadingMr->SetMesh(mesh);
			std::shared_ptr<Material> shadingMaterial = Resources::Find<Material>(L"shadingMaterial");
			shadingMr->SetMaterial(shadingMaterial);
		}

		GameObject::Initialize();
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

	void Room::InitDoor()
	{
		StageScene* stage = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());
		if (stage != nullptr)
		{
			// 주위에 방이 있는 경우 문 생성
			//상
			if (stage->GetRoom(mRoomGrid.x - 1, mRoomGrid.y) != nullptr)
			{
				Door* door = object::Instantiate<Door>(eLayerType::Land, this);
				door->SetDirection(Door::eDirection::UP);

				Transform* doorTr = door->GetComponent<Transform>();
				doorTr->SetPosition(Vector3(0.0f, 2.05f, 90.0f));
			}

			//하
			if (stage->GetRoom(mRoomGrid.x + 1, mRoomGrid.y) != nullptr)
			{
				Door* door = object::Instantiate<Door>(eLayerType::Land, this);
				door->SetDirection(Door::eDirection::DOWN);

				Transform* doorTr = door->GetComponent<Transform>();
				doorTr->SetPosition(Vector3(0.0f, -2.05f, 90.0f));
			}

			//좌
			if (stage->GetRoom(mRoomGrid.x, mRoomGrid.y - 1) != nullptr)
			{
				Door* door = object::Instantiate<Door>(eLayerType::Land, this);
				door->SetDirection(Door::eDirection::LEFT);

				Transform* doorTr = door->GetComponent<Transform>();
				doorTr->SetPosition(Vector3(-3.6f, 0.0f, 90.0f));
			}

			//우
			if (stage->GetRoom(mRoomGrid.x, mRoomGrid.y + 1) != nullptr)
			{
				Door* door = object::Instantiate<Door>(eLayerType::Land, this);
				door->SetDirection(Door::eDirection::RIGHT);

				Transform* doorTr = door->GetComponent<Transform>();
				doorTr->SetPosition(Vector3(3.6f, 0.0f, 90.0f));
			}
		}
	}

	void Room::AddRoomObject(GameObject* roomObj, int x, int y)
	{
		if (x < 0 || y < 0 || x > 6 || y > 12)
			return;

		Monster* monster = dynamic_cast<Monster*>(roomObj);
		if (monster != nullptr)
			mMonsterCount++;

		mGrid[x][y] = roomObj;

		Transform* tr = roomObj->GetComponent<Transform>();
		tr->SetPosition(Vector3((y - 6) * ROOM_GRID_ROW_SIZE, (x - 3) * ROOM_GRID_COLUMN_SIZE, 0.0f));
	}

	void Room::SetRoomGrid(Vector2 roomGrid)
	{
		mRoomGrid = roomGrid;
		SetRoomPosition(mRoomGrid);
	}

	void Room::SetRoomPosition(Vector2 roomGrid)
	{
		mRoomPosition = Vector2(mRoomGrid.y * 7.0f, mRoomGrid.x * -4.0f);
		Transform* tr = GetComponent<Transform>();
		tr->SetPosition(Vector3(mRoomPosition.x, mRoomPosition.y, 100.0f));
	}
}