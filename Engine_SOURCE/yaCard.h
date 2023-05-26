#pragma once
#include "yaGameObject.h"
#include "yaPickup.h"

namespace ya
{
	class Card : public Pickup
	{
	public:
		Card();
		virtual ~Card();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		void SetCardType(eCards card);
		eCards GetCardType() { return mCard; }

	private:
		eCards mCard;
	};
}
