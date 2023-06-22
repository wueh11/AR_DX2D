#pragma once
#include "yaScript.h"
#include "yaGameObject.h"

namespace ya
{
	class Player;
	class Room;
	class MinimapScript : public Script
	{
	public:
		MinimapScript();
		virtual ~MinimapScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	public:
		void InitMinimap();
		void UpdateMinimap();
		void UpdateMinimapSideRoom(Room* room);

		void SetPlayer(Player* player) { mPlayer = player; }

	private:
		Player* mPlayer;

		GameObject* mMinimapBg;
		GameObject* mMinimapSpace;

		std::vector<std::vector<GameObject*>> mRooms;
		std::vector<std::vector<GameObject*>> mRoomIcons;
		GameObject* mCurrentRoom;
	};
}
