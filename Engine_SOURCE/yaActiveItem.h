#pragma once
#include "yaItem.h"
#include "Isaac.h"

namespace ya
{
	class ActiveItem : public Item
	{
	public:
		ActiveItem(isaac::eActiveItem type);
		virtual ~ActiveItem();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		isaac::eActiveItem mType;
	};
}
