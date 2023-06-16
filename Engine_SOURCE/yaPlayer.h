#pragma once
#include "yaIsaacObject.h"
#include "yaIsaacEnums.h"

namespace ya
{
	using namespace isaac;
	class Player : public IsaacObject
	{
	public:
		struct Info
		{
			int heartMax;
			int heart;
			int soulHeart;

			Info()
				: heartMax(6)
				, heart(3)
				, soulHeart(2)
			{}
		};

		struct Pickup
		{
			int coin;
			int bomb;
			int key;

			Pickup()
				: coin(6)
				, bomb(50)
				, key(10)
			{}
		};

		struct Items
		{
			eActiveItem activeItem;
			std::vector<int> passiveItems; // 패시브 아이템
			ePills pill;
			eCards card;
			eTrinkets trinket; //장신구

			Items()
				: activeItem(eActiveItem::TammysHead)
				, passiveItems{}
				, pill(ePills::None)
				, card(eCards::None)
				, trinket(eTrinkets::None)
			{}
		};

	public:
		Player();
		virtual ~Player();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		Info GetInfo() { return mInfo; }
		Items GetItem() { return mItem; }
		Pickup GetPickup() { return mPickup; }

		void SetHeart(int heart) { mInfo.heart = heart; }
		void AddHeart(int heart) 
		{ 
			mInfo.heart += heart; 
			if (mInfo.heart < 0)
				mInfo.heart = 0;

			if (mInfo.heartMax < mInfo.heart) 
				mInfo.heart = mInfo.heartMax; 
		}

		void AddSoulHeart(int heart)
		{ 
			mInfo.soulHeart += heart; 
			if (mInfo.heartMax + mInfo.soulHeart > 24)
				mInfo.soulHeart = 24 - mInfo.heartMax;
		}

		void AddMaxHeart(int heart)
		{ 
			mInfo.heartMax += heart; 
			if (mInfo.heartMax > 24)
				mInfo.heartMax = 24;
		}

		void AddCoin(int coin) { mPickup.coin += coin; }
		void AddBomb(int bomb) { mPickup.bomb += bomb; }
		void AddKey(int key) { mPickup.key += key; }

		void SetPill(ePills pill) { mItem.pill = pill; }
		void SetCard(eCards card) { mItem.card = card; }
		void SetActiveItem(eActiveItem item) { mItem.activeItem = item; }
		void SetTrinket(eTrinkets trinket) { mItem.trinket = trinket; }

		void AddPassiveItem(ePassiveItem item) { mItem.passiveItems.push_back((UINT)item); }

		Vector3 GetRelativePosition();

	private:
		Info mInfo;
		Items mItem;
		Pickup mPickup;
	};
}

