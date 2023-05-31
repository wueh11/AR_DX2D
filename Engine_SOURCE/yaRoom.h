#pragma once
#include "yaGameObject.h"
#include "yaDoor.h"

namespace ya
{
	using namespace isaac;
	class Room : public GameObject
	{
	public:
		Room(int x, int y, eRoomType type = eRoomType::Normal);
		virtual ~Room();
	
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		void InitDoor();
		void CreateDoor(Room* targetRoom, Door::eDirection doorDirection);
		Door* GetDoor(Door::eDirection doorDirection) { return mDoors[(UINT)doorDirection]; }

		void AddRoomObject(GameObject* roomObj, int x = -1, int y = -1);

		void SetRoomGrid(Vector2 roomGrid);
		void SetRoomPosition(Vector2 roomGrid);

		Vector2 GetRoomPosition() { return mRoomPosition; }
		Vector2 GetRoomGrid() { return mRoomGrid; }

		eRoomType GetRoomType() { return mRoomType; }
		//void SetRoomType(eRoomType type);

		void SetLock(bool lock) { mbLock = lock; }
		bool IsLock() { return mbLock; }

		bool IsClear() { return mbClear; }

	private:
		eRoomType mRoomType;

		bool mbClear;	// player가 방의 몬스터를 모두 처치했을 경우 true
		bool mbLock;	// 열쇠가 필요한 방(상점, 보물방), player가 방의 문을 열쇠로 열었을 경우 false

		int mMonsterCount;	// 방에 남은 몬스터 수

		GameObject* mGrid[7][13];	// 방을 구성하는 gameobject. 빈칸일경우 nullptr

		Vector2 mRoomGrid;
		Vector2 mRoomPosition;

		Door* mDoors[(UINT)Door::eDirection::End];
		
	};
}