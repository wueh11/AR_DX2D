#pragma once
#include "yaGameObject.h"
#include "IsaacItems.h"

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
		ePickupType GetItemType() { return mItemType; }

	protected:
		ePickupType mItemType;
	};
}
