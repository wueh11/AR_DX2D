#pragma once
#include "yaItem.h"
#include "yaIsaacEnums.h"

namespace ya
{
	using namespace isaac;
	class PassiveItem : public Item
	{
	public:
		PassiveItem();
		virtual ~PassiveItem();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		isaac::ePassiveItem GetPassiveItemType() { return mType; }
		void SetPassiveItemType(isaac::ePassiveItem type);

	private:
		isaac::ePassiveItem mType;
	};
}
