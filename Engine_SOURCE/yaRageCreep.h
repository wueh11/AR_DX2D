#pragma once
#include "yaMonster.h"

namespace ya
{
	class RageCreep : public Monster
	{
	public:
		RageCreep();
		virtual ~RageCreep();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		eDirection GetDirection() { return mDirection; }
		void SetDirection(eDirection direction);

	private:
		eDirection mDirection;
	};
}
