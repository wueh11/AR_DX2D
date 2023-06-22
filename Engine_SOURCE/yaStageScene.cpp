#include "yaStageScene.h"
#include "yaSceneManager.h"
#include "yaIsaacEnums.h"

#include "yaPlayer.h"
#include "yaScene.h"

#include "yaUIScript.h"

namespace ya
{
	StageScene::StageScene(eSceneType type)
		: Scene(type)
		, mCurrentRoom(nullptr)
		, mPrevRoom(nullptr)
		, mbStageClear(false)
		, mbBossRoom(false)
		, mBoss(nullptr)
		, mUI(nullptr)
		, mMinimap(nullptr)
	{
		mRooms.resize(isaac::STAGE_MAX_ROW);
		for (size_t i = 0; i < isaac::STAGE_MAX_ROW; i++)
		{
			mRooms[i].resize(isaac::STAGE_MAX_COLUMN);
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
		if(mCurrentRoom != nullptr)
		{
			mPrevRoom = mCurrentRoom;
			mCurrentRoom->Pause();
			mCurrentRoom->ExitRoom();
		}

		room->SetActive();
		mCurrentRoom = room;
		mCurrentRoom->EnterRoom();

		Vector3 roomPos = room->GetComponent<Transform>()->GetPosition();
		Transform* cameraTr = mainCamera->GetOwner()->GetComponent<Transform>();
		cameraTr->SetPosition(Vector3(roomPos.x, roomPos.y, cameraTr->GetPosition().z));
	}

	void StageScene::SetCurrentRoom(int x, int y)
	{
		if (mCurrentRoom != nullptr)
		{
			mPrevRoom = mCurrentRoom;
			mCurrentRoom->Pause();
			mCurrentRoom->ExitRoom();
		}

		Room* nextRoom = GetRoom(x, y); 
		nextRoom->SetActive();
		mCurrentRoom = nextRoom;
		mCurrentRoom->EnterRoom();

		Vector3 roomPos = mCurrentRoom->GetComponent<Transform>()->GetPosition();
		Transform* cameraTr = mainCamera->GetOwner()->GetComponent<Transform>();
		cameraTr->SetPosition(Vector3(roomPos.x, roomPos.y, cameraTr->GetPosition().z));
	}

	void StageScene::StageClear(bool clear)
	{
		mbStageClear = clear;
	
		if (clear)
			mbBossRoom = false;
	}

	void StageScene::SetBossRoom(bool boss)
	{
		mbBossRoom = boss;
		mUI->UseBossHealth(true);
	}

	Room* StageScene::CreateRoom(int x, int y, eRoomType type, bool bLock)
	{
		Room* room = new Room(x, y, type);
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(eLayerType::Stage);
		layer.AddGameObject(room);

		room->Initialize();
		AddRoom(room, x, y);
		room->SetLock(bLock);

		room->Pause();

		return room;
	}
}