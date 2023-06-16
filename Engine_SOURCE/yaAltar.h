#pragma once
#include "yaLand.h"

namespace ya
{
	class Item;
	class Altar : public Land
	{
	public:
		Altar();
		virtual ~Altar();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		void SetItem(Item* item);
	};
}