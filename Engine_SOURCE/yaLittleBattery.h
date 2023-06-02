#pragma once
#include "yaGameObject.h"
#include "yaPickup.h"

namespace ya
{
	class LittleBattery : public Pickup
	{
	public:
		LittleBattery();
		virtual ~LittleBattery();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}
