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
		void AddRoom(Room* room, UINT x = -1, UINT y = -1);

		void Active(bool active) { mbActive = active; }
		bool IsActive() { return mbActive; }

	private:
		bool mbActive;

	private:
		std::vector<std::vector<Room*>> mRooms;
		Room mCurrentRoom;
	};
}

