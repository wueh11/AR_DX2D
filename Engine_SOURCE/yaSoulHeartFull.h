#pragma once
#include "yaPickup.h"

namespace ya
{
	class SoulHeartFull : public Pickup
	{
	public:
		SoulHeartFull();
		virtual ~SoulHeartFull();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}
