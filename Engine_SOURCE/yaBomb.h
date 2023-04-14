#pragma once
#include "yaGameObject.h"
#include "yaPickup.h"

namespace ya
{
	class Bomb : public Pickup
	{
	public:
		Bomb();
		virtual ~Bomb();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}
