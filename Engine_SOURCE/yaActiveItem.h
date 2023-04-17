#pragma once
#include "yaItem.h"

namespace ya
{
	class ActiveItem : public Item
	{
	public:
		ActiveItem();
		virtual ~ActiveItem();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
	};
}
