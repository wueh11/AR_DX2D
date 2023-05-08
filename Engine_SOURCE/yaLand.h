#pragma once
#include "yaGameObject.h"
#include "yaIsaacEnums.h"

namespace ya
{
	class Land : public GameObject
	{
	public:
		struct RoomGridInfo
		{
			class Room* room;
			Vector2 gridPos;
		};
	public:
		Land();
		virtual ~Land();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		void SetRoom(class Room* room) { mRoomGridInfo.room = room; }
		void SetGridPos(Vector2 pos) { mRoomGridInfo.gridPos = pos; }

	private:
		RoomGridInfo mRoomGridInfo;
	};
}
