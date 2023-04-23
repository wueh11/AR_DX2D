#pragma once
#include "yaGameObject.h"
#include "Isaac.h"

using namespace ya::isaac;
namespace ya
{
	class Pickup : public GameObject
	{
	public:
		Pickup(ePickupType itemType);
		virtual ~Pickup();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		void Take();

	public:
		ePickupType GetItemType() { return mItemType; }

	protected:
		ePickupType mItemType;
		float mTimer;
	};
}
