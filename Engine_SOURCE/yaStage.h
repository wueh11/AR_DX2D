#pragma once
#include "yaGameObject.h"
#include "yaRoom.h"

namespace ya
{
	class Stage : public GameObject
	{
	public:
		Stage();
		virtual ~Stage();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		std::vector<std::vector<Room*>> GetRooms() { return mRooms; }
		Room* GetRoom(int x, int y) { if (x < 0 || y < 0) return nullptr; else return mRooms[x][y]; }

		void AddRoom(Room* room, int x, int y);

		void Active(bool active) { mbActive = active; }
		bool IsActive() { return mbActive; }

		void SetCurrentRoom(Room* room);

	private:
		bool mbActive;

	private:
		std::vector<std::vector<Room*>> mRooms;
		Room* mCurrentRoom;
	};
}

