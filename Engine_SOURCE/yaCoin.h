#pragma once
#include "yaGameObject.h"
#include "yaPickup.h"

namespace ya
{
	class Coin : public Pickup
	{
	public:
		Coin();
		virtual ~Coin();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}
