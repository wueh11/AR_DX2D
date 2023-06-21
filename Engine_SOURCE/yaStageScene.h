#pragma once
#include "yaScene.h"
#include "yaLayer.h"
#include "yaRoom.h"

namespace ya
{
	using namespace isaac;
	class Monster;
	class UIScript;
	class MinimapScript;
	class StageScene : public Scene
	{
	public:
		StageScene(eSceneType type);
		virtual ~StageScene();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		virtual void Destroy();

		virtual void OnEnter();
		virtual void OnExit();

	public: 
		std::vector<std::vector<Room*>> GetRooms() { return mRooms; }
		Room* GetRoom(int x, int y);

		void AddRoom(Room* room, int x, int y);
		Room* CreateRoom(int x, int y, eRoomType type = eRoomType::Normal, bool bLock = false);

		Room* GetCurrentRoom() { return mCurrentRoom; }
		void SetCurrentRoom(Room* room);
		void SetCurrentRoom(int x, int y);

		void StageClear(bool clear);
		bool IsStageClear() { return mbStageClear; }

		void SetBoss(Monster* monster) { mBoss = monster;  }
		Monster* GetBoss() { return mBoss; }

		void SetBossRoom(bool boss);
		bool IsBossRoom() { return mbBossRoom; }

		UIScript* GetUI() { return mUI; }
		void SetUI(UIScript* ui) { mUI = ui; }

	protected:
		std::vector<std::vector<Room*>> mRooms;
		Room* mCurrentRoom;
		
		bool mbStageClear;
		
		Monster* mBoss;
		bool mbBossRoom;

		UIScript* mUI;
		MinimapScript* mMinimap;
	};
}

