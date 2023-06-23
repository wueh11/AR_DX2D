#pragma once
#include "yaEngine.h"
#include "yaScene.h"
#include "yaIsaacEnums.h"
#include "yaItemObject.h"

namespace ya
{
	using namespace isaac;
	class ItemManager
	{
	public:
		static void Initialize();

	public:
		static std::vector<ItemObject*> GetItemObjects(eItemType itemType);

	private:
		// pill
		static void HealthUp();
		static void HealthDown();
		static void RangeUp();
		static void RangeDown();
		static void TearsUp();
		static void TearsDown();
		static void SpeedUp();
		static void SpeedDown();

		//card
		static void TheFool();
		static void TheLovers();
		static void Club2();
		static void Diamonds2();
		static void Spades2();

		//Trinkets
		static void FishHead();
		static void PinkyEye();
		static void GoatHoof();
		
		//Actives
		static void TheBible();
		static void TammysHead();
		static void YumHeart();

		//Passives
		static void CricketHead();
		static void Lunch();
		static void GrowthHormones();

	private:
		static std::vector<ItemObject*> mPills;
		static std::vector<ItemObject*> mCards;
		static std::vector<ItemObject*> mTrinkets;
		static std::vector<ItemObject*> mActives;
		static std::vector<ItemObject*> mPassives;
	};
}

