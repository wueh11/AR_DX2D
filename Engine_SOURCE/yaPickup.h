#pragma once
#include "yaItem.h"
#include "yaIsaacEnums.h"

using namespace ya::isaac;
namespace ya
{
	class Pickup : public Item
	{
	public:
		Pickup(eItemType itemType);
		virtual ~Pickup();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		void Take();

	public:
		eItemType GetItemType() { return mItemType; }

	protected:
		eItemType mItemType;
		float mTimer;
	};
}
