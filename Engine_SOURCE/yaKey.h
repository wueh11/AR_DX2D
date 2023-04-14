#pragma once
#include "yaGameObject.h"
#include "yaPickup.h"

namespace ya
{
	class Key : public Pickup
	{
	public:
		Key();
		virtual ~Key();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}
