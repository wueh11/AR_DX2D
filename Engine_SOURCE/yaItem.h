#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Room;
	class Item : public GameObject
	{
	public:
		Item();
		virtual ~Item();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		void SetRoom(Room* room) { mRoom = room; }
		Room* GetRoom() { return mRoom; }

	private:
		Room* mRoom = nullptr;
	};
}
