#pragma once
#include "yaItem.h"

namespace ya
{
	class HeartFull : public Item
	{
	public:
		HeartFull();
		virtual ~HeartFull();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}
