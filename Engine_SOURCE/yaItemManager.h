#pragma once
#include "yaEngine.h"
#include "yaScene.h"
#include "IsaacItems.h"

namespace ya
{
	using namespace isaac;
	class ItemManager
	{
	public:
		struct Events
		{
			struct Event
			{
				void operator=(std::function<void()> func)
				{
					mEvent = std::move(func);
				}
				void operator()()
				{
					if (mEvent)
						mEvent();
				}

				std::function<void()> mEvent;
			};
			
			Event mEvents;
		};

		struct Consumable
		{
			eItemType itemtype;
			Texture texture;
		};

	public:
		static void Initialize();

	public:
		static class Pill* CreatePill(ePills pillType);
		static class Card* CreateCard(eCards cardType);

	public:
		static std::vector<Events*> GetEvent(eItemType itemType);

	private:
		// pill
		static void InitPill();

		static void HealthUp();
		static void HealthDown();
		static void RangeUp();
		static void RangeDown();
		static void TearsUp();
		static void TearsDown();
		static void SpeedUp();
		static void SpeedDown();

		//card
		static void InitCard();

		static void TheFool();
		static void TheLovers();
		static void Club2();
		static void Diamonds2();
		static void Spades2();

	private:
		static std::vector<ItemManager::Events*> mPillEvents;
		static std::vector<ItemManager::Events*> mCardEvents;
		static std::vector<ItemManager::Events*> mActiveEvents;
		//std::map<UINT, Events*> mPassiveEvents;
	};
}

