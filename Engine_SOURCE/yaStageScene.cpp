#include "yaStageScene.h"
#include "yaSceneManager.h"
#include "yaIsaacEnums.h"

#include "yaPlayer.h"
#include "yaScene.h"

namespace ya
{
	StageScene::StageScene(eSceneType type)
		: Scene(type)
		, mCurrentRoom(nullptr)
	{
		mRooms.resize(isaac::ROOM_MAX_ROW);
		for (size_t i = 0; i < isaac::ROOM_MAX_ROW; i++)
		{
			mRooms[i].resize(isaac::ROOM_MAX_COLUMN);
		}
	}

	StageScene::~StageScene()
	{
	}

	void StageScene::Initialize()
	{
		Scene::Initialize();
	}

	void StageScene::Update()
	{
		Scene::Update();
	}

	void StageScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void StageScene::Render()
	{
		Scene::Render();
	}

	void StageScene::Destroy()
	{
		Scene::Destroy();
	}

	void StageScene::OnEnter()
	{
	}

	void StageScene::OnExit()
	{
	}

	Room* StageScene::GetRoom(int x, int y)
	{
		if (x < 0 || y < 0)
			return nullptr;
		else
			return mRooms[x][y];
	}
	void StageScene::AddRoom(Room* room, int x, int y)
	{
		if (x < 0 || y < 0)
			return;

		room->SetRoomGrid(Vector2(x, y));
		mRooms[x][y] = room;
	}

	void StageScene::SetCurrentRoom(Room* room)
	{
		mCurrentRoom = room;

		Transform* tr = room->GetComponent<Transform>();
		mainCamera->GetOwner()->GetComponent<Transform>()->SetPosition(tr->GetPosition());
	}

	void StageScene::SetCurrentRoom(int x, int y)
	{
		mCurrentRoom = GetRoom(x, y);

		Transform* tr = mCurrentRoom->GetComponent<Transform>();
		mainCamera->GetOwner()->GetComponent<Transform>()->SetPosition(tr->GetPosition());
	}

	Room* StageScene::CreateRoom(int x, int y)
	{
		Room* room = new Room(x, y);
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(eLayerType::Stage);
		layer.AddGameObject(room);

		AddRoom(room, x, y);

		return room;
	}
}