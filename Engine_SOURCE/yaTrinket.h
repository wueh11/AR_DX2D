#pragma once
#include "yaItem.h"
#include "yaIsaacEnums.h"

namespace ya
{
	class Trinket : public Item
	{
	public:
		Trinket(isaac::eTrinkets type);
		virtual ~Trinket();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		isaac::eTrinkets GetTrinketType() { return mType; }

	private:
		isaac::eTrinkets mType;
	};
}
