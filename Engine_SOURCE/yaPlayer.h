#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Player : public GameObject
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
				, soulHeart(0)
			{}
		};

		struct Status
		{
			float attack;
			float attackSpeed;
			float tearSpeed;
			float range;
			int speed;
			int luck;

			Status()
				: attack(3.5f)
				, attackSpeed(2.73f)
				, tearSpeed(1.0f)
				, range(6.5f)
				, speed(1.0f)
				, luck(0.0f)
			{}
		};

		struct Pickup
		{
			int coin;
			int bomb;
			int key;

			Pickup()
				: coin(0)
				, bomb(1)
				, key(0)
			{}
		};

		struct Items
		{
			std::vector<int> collectibles; // 패시브 아이템
			int pickups; //알약,카드
			int trinkets; //장신구
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
		Status GetStatus() { return mStatus; }
		Items GetItem() { return mItem; }
		Pickup GetPickup() { return mPickup; }

		void SetHeart(int heart) { mInfo.heart = heart; }
		void AddHeart(int heart) 
		{ 
			mInfo.heart += heart; 
			if (mInfo.heartMax < mInfo.heart) 
				mInfo.heart = mInfo.heartMax; 
		}

		void AddSoulHeart(int heart) { mInfo.soulHeart += heart; }

		void AddCoin(int coin) { mPickup.coin += coin; }
		void AddBomb(int bomb) { mPickup.bomb += bomb; }
		void AddKey(int key) { mPickup.key += key; }

	private:
		Info mInfo;
		Status mStatus;
		Items mItem;
		Pickup mPickup;
	};
}

