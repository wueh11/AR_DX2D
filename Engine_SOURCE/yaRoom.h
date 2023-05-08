#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Room : public GameObject
	{
	public:
		struct RoomObjectData
		{
			GameObject* object;
			Vector3 position;
		};

	public:
		Room();
		virtual ~Room();
	
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		void AddRoomData(RoomObjectData roomDatas) { mRoomDatas.push_back(roomDatas); }

		void Active(bool active) { mbActive = active; }
		bool IsActive() { return mbActive; }

	private:
		bool mbActive;
		int mMonsterCount;
		bool mbClear;

		std::vector<RoomObjectData> mRoomDatas;
	};
}