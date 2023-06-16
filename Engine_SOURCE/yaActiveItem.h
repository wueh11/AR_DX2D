#pragma once
#include "yaItem.h"
#include "yaIsaacEnums.h"

namespace ya
{
	using namespace isaac;
	class ActiveItem : public Item
	{
	public:
		ActiveItem();
		virtual ~ActiveItem();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		isaac::eActiveItem GetActveItemType() { return mType; }
		void SetActiveItemType(isaac::eActiveItem type);

	private:
		isaac::eActiveItem mType;
	};
}
