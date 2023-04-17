#pragma once
#include "yaGameObject.h"
#include "yaPickup.h"

namespace ya
{
	class Card : public Pickup
	{
	public:
		Card(eCards type);
		virtual ~Card();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		eCards mCard;
	};
}
