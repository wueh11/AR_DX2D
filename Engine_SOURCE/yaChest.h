#pragma once
#include "yaGameObject.h"
#include "yaItem.h"
#include "yaIsaacEnums.h"

namespace ya
{
	using namespace isaac;
	class Chest : public GameObject
	{
	public:
		Chest();
		virtual ~Chest();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		void AddItem(Item* item) 
		{
			item->Pause();
			mItems.push_back(item); 
		}
		std::vector<Item*> GetItems() { return mItems; }
		
		void SetChestType(eChestType type);

	private:
		std::vector<Item*> mItems;
		eChestType mChestType;
	};
}