#pragma once
#include "yaGameObject.h"
#include "yaDoor.h"

namespace ya
{
	class Room : public GameObject
	{
	public:
		Room(int x, int y);
		virtual ~Room();
	
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		void InitDoor();
		Door* CreateDoor(Door::eDirection dir);
		void AddRoomObject(GameObject* roomObj, int x = -1, int y = -1);

		void Active(bool active) { mbActive = active; }
		bool IsActive() { return mbActive; }

		void SetRoomGrid(Vector2 roomGrid);
		void SetRoomPosition(Vector2 roomGrid);

		Vector2 GetRoomPosition() { return mRoomPosition; }
		Vector2 GetRoomGrid() { return mRoomGrid; }

	private:
		bool mbActive;	// player가 방에 있을 경우 true
		bool mbClear;	// player가 방의 몬스터를 모두 처치했을 경우 true
		bool mbLock;	// 열쇠가 필요한 방(상점, 보물방), player가 방의 문을 열쇠로 열었을 경우 false

		int mMonsterCount;	// 방에 남은 몬스터 수

		GameObject* mGrid[7][13];	// 방을 구성하는 gameobject. 빈칸일경우 nullptr

		Vector2 mRoomGrid;
		Vector2 mRoomPosition;

		Transform* tr1;
	};
}