#pragma once
#include "yaScene.h"
#include "yaLayer.h"
#include "yaRoom.h"

namespace ya
{
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
		Room* CreateRoom(int x, int y);

		Room* GetCurrentRoom() { return mCurrentRoom; }
		void SetCurrentRoom(Room* room);
		void SetCurrentRoom(int x, int y);

	protected:
		std::vector<std::vector<Room*>> mRooms;
		Room* mCurrentRoom;
	};
}

