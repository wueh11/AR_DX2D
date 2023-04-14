#pragma once
#include "yaPickup.h"
#include "yaPickup.h"

namespace ya
{
	class HeartFull : public Pickup
	{
	public:
		HeartFull();
		virtual ~HeartFull();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}
