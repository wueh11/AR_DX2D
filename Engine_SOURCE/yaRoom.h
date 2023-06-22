#pragma once
#include "yaGameObject.h"
#include "yaDoor.h"

namespace ya
{
	using namespace isaac;
	class Item;
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
		void EnterRoom();
		void ExitRoom();

	public:
		void InitDoor();
		void CreateDoor(Room* targetRoom, eDirection doorDirection);
		Door* GetDoor(eDirection doorDirection) { return mDoors[(UINT)doorDirection]; }

		void AddRoomObject(GameObject* roomObj, int x = -1, int y = -1, float z = 0.0f);

		void SetRoomGrid(Vector2 roomGrid);
		void SetRoomPosition(Vector2 roomGrid);

		Vector2 GetRoomPosition() { return mRoomPosition; }
		Vector2 GetRoomGrid() { return mRoomGrid; }

		eRoomType GetRoomType() { return mRoomType; }
		//void SetRoomType(eRoomType type);

		void SetLock(bool lock) { mbLock = lock; }
		bool IsLock() { return mbLock; }
		
		bool IsVisit() { return mbVisit; }
		void Visit(bool visit) { mbVisit = visit; }
		bool IsClear() { return mbClear; }

		void AddMonsterCount(int count);
		std::vector<Item*> GetItems() { return mItems; }
		void EraseItem(Item* item);

		void Compensation();
		void SetCompensation(GameObject* compensation, int x = 4, int y = 7);

	private:
		eRoomType mRoomType;

		bool mbVisit;
		bool mbClear;	// player�� ���� ���͸� ��� óġ���� ��� true
		bool mbLock;	// ���谡 �ʿ��� ��(����, ������), player�� ���� ���� ����� ������ ��� false

		int mMonsterCount;	// �濡 ���� ���� ��

		GameObject* mGrid[9][15];	// ���� �����ϴ� gameobject. ��ĭ�ϰ�� nullptr
		std::vector<Item*> mItems;

		Vector2 mRoomGrid;
		Vector2 mRoomPosition;

		Door* mDoors[(UINT)eDirection::End];

		GameObject* mCompensation;
		Vector2 mCompensationGrid;
		
	};
}