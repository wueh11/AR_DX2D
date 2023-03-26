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

		struct Item
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
		Item GetItem() { return mItem; }

	private:
		Info mInfo;
		Status mStatus;
		Item mItem;
	};
}

