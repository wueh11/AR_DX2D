#pragma once
#include "yaGameObject.h"
#include "yaPickup.h"

namespace ya
{
	class Pill : public Pickup
	{
	public:
		Pill();
		virtual ~Pill();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		ePills GetPillType() { return mPill; }
		void SetPillType(ePills type);

	private:
		ePills mPill;
	};
}
