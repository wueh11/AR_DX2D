#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Item;
	class ShopItem : public GameObject
	{
	public:
		ShopItem();
		virtual ~ShopItem();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		void SetItem(Item* item, int price = 5);
	};
}