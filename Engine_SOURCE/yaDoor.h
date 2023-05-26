#pragma once
#include "yaLand.h"

namespace ya
{
	class Door : public Land
	{
	public:
		enum class eDirection
		{
			None,
			UP,
			DOWN,
			LEFT,
			RIGHT,
		};

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

		bool IsOpen() { return mbOpen; }
		bool IsDamaged() { return mbDamaged; }
		bool IsLock() { return mbLock; }

		void SetOpen(bool open);
		void SetDamaged(bool damaged);
		void SetLock(bool lock);

	private:
		eDirection mDirection;
		bool mbOpen;
		bool mbLock;
		bool mbDamaged;
	};
}
