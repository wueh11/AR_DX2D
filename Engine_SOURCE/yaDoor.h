#pragma once
#include "yaLand.h"

namespace ya
{
	using namespace isaac;

	class Room;
	class Door : public Land
	{
	public:
		Door();
		virtual ~Door();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		eDirection GetDirection() { return mDirection; }
		void SetDirection(eDirection dir);

		eRoomType GetDoorType() { return mDoorType; }
		void SetDoorType(eRoomType type);

		bool IsOpen() { return mbOpen; }
		bool IsDamaged() { return mbDamaged; }
		bool IsLock() { return mbLock; }

		void SetOpen(bool open);
		void SetDamaged(bool damaged);
		void SetLock(bool lock);

	private:
		eDirection mDirection;
		eRoomType mDoorType;
		
		bool mbOpen;
		bool mbLock;
		bool mbDamaged;
	};
}
