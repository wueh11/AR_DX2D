#pragma once
#include "yaLand.h"

namespace ya
{
	class Door : public Land
	{
	public:
		enum class eDirection
		{
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
		bool IsOpen() { return mbOpen; }
		bool IsDamaged() { return mbDamaged; }

		void SetOpen(bool open) { mbOpen = open; }
		void SetDamaged(bool damaged) { mbDamaged = damaged; }

	private:
		eDirection mDirection;
		bool mbOpen;
		bool mbDamaged;
	};
}
