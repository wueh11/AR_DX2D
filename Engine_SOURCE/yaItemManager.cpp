#include "yaItemManager.h"

#include "yaSceneManager.h"
#include "yaScene.h"

#include "yaPlayer.h"

#include "yaPill.h"
#include "yaCard.h"

namespace ya
{
	std::vector<ItemManager::Events*> ItemManager::mPillEvents = {};
	std::vector<ItemManager::Events*> ItemManager::mCardEvents = {};
	std::vector<ItemManager::Events*> ItemManager::mActiveEvents = {};

	void ItemManager::Initialize()
	{
		{ // Pills
			mPillEvents.resize((UINT)ePills::End);

			for (size_t i = 0; i < (UINT)ePills::End; i++)
				mPillEvents[i] = new Events();

			mPillEvents[(UINT)ePills::HealthUp]->mEvents = std::bind(&ItemManager::HealthUp);
			mPillEvents[(UINT)ePills::HealthDown]->mEvents = std::bind(&ItemManager::HealthDown);
			mPillEvents[(UINT)ePills::RangeUp]->mEvents = std::bind(&ItemManager::RangeUp);
			mPillEvents[(UINT)ePills::RangeDown]->mEvents = std::bind(&ItemManager::RangeDown);
			mPillEvents[(UINT)ePills::TearsUp]->mEvents = std::bind(&ItemManager::TearsUp);
			mPillEvents[(UINT)ePills::TearsDown]->mEvents = std::bind(&ItemManager::TearsDown);
			mPillEvents[(UINT)ePills::SpeedUp]->mEvents = std::bind(&ItemManager::SpeedUp);
			mPillEvents[(UINT)ePills::SpeedDown]->mEvents = std::bind(&ItemManager::SpeedDown);
		}

		{ // Cards
			mCardEvents.resize((UINT)eCards::End);

			for (size_t i = 0; i < (UINT)eCards::End; i++)
				mCardEvents[i] = new Events();

			mCardEvents[(UINT)eCards::TheFool]->mEvents = std::bind(&ItemManager::TheFool);
			mCardEvents[(UINT)eCards::TheLovers]->mEvents = std::bind(&ItemManager::TheLovers);
			mCardEvents[(UINT)eCards::Club2]->mEvents = std::bind(&ItemManager::Club2);
			mCardEvents[(UINT)eCards::Diamonds2]->mEvents = std::bind(&ItemManager::Diamonds2);
			mCardEvents[(UINT)eCards::Spades2]->mEvents = std::bind(&ItemManager::Spades2);
		}

		{ // ActiveItem
			mActiveEvents.resize((UINT)eActiveItem::End);

			for (size_t i = 0; i < (UINT)eActiveItem::End; i++)
				mActiveEvents[i] = new Events();

		}

	}

	Pill* ItemManager::CreatePill(ePills pillType)
	{
		Pill* pill = new Pill(pillType);
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(eLayerType::Item);
		layer.AddGameObject(pill);

		return pill;
	}

	Card* ItemManager::CreateCard(eCards cardType)
	{
		Card* card = new Card(cardType);
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(eLayerType::Item);
		layer.AddGameObject(card);

		return card;
	}

	std::vector<ItemManager::Events*> ItemManager::GetEvent(eItemType itemType)
	{
		if (itemType == eItemType::ActiveItem)
		{ 
			return mActiveEvents;
		}
		else if (itemType == eItemType::PassiveItem)
		{

		}
		else if (itemType == eItemType::Pill)
		{
			return mPillEvents;
		}
		else if (itemType == eItemType::Card)
		{
			return mCardEvents;
		}
	}

	void ItemManager::InitPill()
	{
	}

	void ItemManager::HealthUp()
	{
		Scene* scene = SceneManager::GetActiveScene();
		Player* player = scene->GetPlayer();

		if (player == nullptr)
			return;

		player->AddMaxHeart(2);
	}
	void ItemManager::HealthDown()
	{
		Scene* scene = SceneManager::GetActiveScene();
		Player* player = scene->GetPlayer();

		if (player == nullptr)
			return;

		player->AddMaxHeart(-2);
	}
	void ItemManager::RangeUp()
	{
		Scene* scene = SceneManager::GetActiveScene();
		Player* player = scene->GetPlayer();

		if (player == nullptr)
			return;

		player->AddRange(2.0f);
	}
	void ItemManager::RangeDown()
	{
		Scene* scene = SceneManager::GetActiveScene();
		Player* player = scene->GetPlayer();

		if (player == nullptr)
			return;

		player->AddRange(-2.0f);
	}
	void ItemManager::TearsUp()
	{
		Scene* scene = SceneManager::GetActiveScene();
		Player* player = scene->GetPlayer();

		if (player == nullptr)
			return;

		player->AddAttackSpeed(0.35f);
	}
	void ItemManager::TearsDown()
	{
		Scene* scene = SceneManager::GetActiveScene();
		Player* player = scene->GetPlayer();

		if (player == nullptr)
			return;

		player->AddAttackSpeed(-0.28f);
	}
	void ItemManager::SpeedUp()
	{
		Scene* scene = SceneManager::GetActiveScene();
		Player* player = scene->GetPlayer();

		if (player == nullptr)
			return;

		player->AddSpeed(-0.15f);
	}
	void ItemManager::SpeedDown()
	{
		Scene* scene = SceneManager::GetActiveScene();
		Player* player = scene->GetPlayer();

		if (player == nullptr)
			return;

		player->AddSpeed(-0.12f);
	}
	void ItemManager::InitCard()
	{
	}
	void ItemManager::TheFool()
	{
	}
	void ItemManager::TheLovers()
	{
	}
	/// <summary>
	/// 현재폭탄 x2, 0개일때 +2
	/// </summary>
	void ItemManager::Club2()
	{
		Scene* scene = SceneManager::GetActiveScene();
		Player* player = scene->GetPlayer();

		if (player == nullptr)
			return;

		int bomb = player->GetPickup().bomb;
		if (0 < bomb)
			player->AddBomb(bomb);
		else
			player->AddBomb(2);
	}
	/// <summary>
	/// 현재동전 x2, 0개일때 +2
	/// </summary>
	void ItemManager::Diamonds2()
	{
		Scene* scene = SceneManager::GetActiveScene();
		Player* player = scene->GetPlayer();

		if (player == nullptr)
			return;

		int coin = player->GetPickup().coin;
		if (0 < coin)
			player->AddCoin(coin);
		else
			player->AddCoin(2);
	}
	/// <summary>
	/// 현재열쇠 x2, 0개일때 +2
	/// </summary>
	void ItemManager::Spades2()
	{
		Scene* scene = SceneManager::GetActiveScene();
		Player* player = scene->GetPlayer();

		if (player == nullptr)
			return;

		int key = player->GetPickup().key;
		if (0 < key)
			player->AddKey(key);
		else
			player->AddKey(2);
	}
}