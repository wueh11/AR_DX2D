#pragma once
#include "yaItem.h"
#include "yaIsaacEnums.h"

namespace ya
{
	class Trinket : public Item
	{
	public:
		Trinket();
		virtual ~Trinket();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		isaac::eTrinkets GetTrinketType() { return mType; }
		void SetTrinketType(isaac::eTrinkets type);

	private:
		isaac::eTrinkets mType;
	};
}
