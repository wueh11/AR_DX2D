#pragma once
#include "yaPickup.h"

namespace ya
{
	class HeartHalf : public Pickup
	{
	public:
		HeartHalf();
		virtual ~HeartHalf();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}
