#include "yaItemManager.h"

#include "yaSceneManager.h"
#include "yaScene.h"
#include "yaPlayer.h"
#include "yaPill.h"
#include "yaCard.h"
#include "yaActiveItem.h"

namespace ya
{
	std::vector<ItemObject*> ItemManager::mPills = {};
	std::vector<ItemObject*> ItemManager::mCards = {};
	std::vector<ItemObject*> ItemManager::mTrinkets = {};
	std::vector<ItemObject*> ItemManager::mActives = {};

	void ItemManager::Initialize()
	{
		{ // Pills
			mPills.resize((UINT)ePills::End);
			mPills[(UINT)ePills::HealthUp] = new ItemObject(eItemType::Pill, (UINT)ePills::HealthUp, L"Health Up", std::bind(&ItemManager::HealthUp));
			mPills[(UINT)ePills::HealthDown] = new ItemObject(eItemType::Pill, (UINT)ePills::HealthDown, L"Health Down", std::bind(&ItemManager::HealthDown));
			mPills[(UINT)ePills::RangeUp] = new ItemObject(eItemType::Pill, (UINT)ePills::RangeUp, L"Range Up", std::bind(&ItemManager::RangeUp));
			mPills[(UINT)ePills::RangeDown] = new ItemObject(eItemType::Pill, (UINT)ePills::RangeDown, L"Range Down", std::bind(&ItemManager::RangeDown));
			mPills[(UINT)ePills::TearsUp] = new ItemObject(eItemType::Pill, (UINT)ePills::TearsUp, L"Tears Up", std::bind(&ItemManager::TearsUp));
			mPills[(UINT)ePills::TearsDown] = new ItemObject(eItemType::Pill, (UINT)ePills::TearsDown, L"Tears Down", std::bind(&ItemManager::TearsDown));
			mPills[(UINT)ePills::SpeedUp] = new ItemObject(eItemType::Pill, (UINT)ePills::SpeedUp, L"Speed Up", std::bind(&ItemManager::SpeedUp));
			mPills[(UINT)ePills::SpeedDown] = new ItemObject(eItemType::Pill, (UINT)ePills::SpeedDown, L"Speed Down", std::bind(&ItemManager::SpeedDown));
		}

		{ // Cards
			mCards.resize((UINT)eCards::End);
			mCards[(UINT)eCards::TheFool] = new ItemObject(eItemType::Card, (UINT)eCards::TheFool, L"The Fool", std::bind(&ItemManager::TheFool));
			mCards[(UINT)eCards::TheLovers] = new ItemObject(eItemType::Card, (UINT)eCards::TheLovers, L"The Lovers", std::bind(&ItemManager::TheLovers));
			mCards[(UINT)eCards::Club2] = new ItemObject(eItemType::Card, (UINT)eCards::Club2, L"2 of Clubs", std::bind(&ItemManager::Club2));
			mCards[(UINT)eCards::Diamonds2] = new ItemObject(eItemType::Card, (UINT)eCards::Diamonds2, L"2 of Diamonds", std::bind(&ItemManager::Diamonds2));
			mCards[(UINT)eCards::Spades2] = new ItemObject(eItemType::Card, (UINT)eCards::Spades2, L"2 of Spades", std::bind(&ItemManager::Spades2));
		}

		{ // Trinket
			mTrinkets.resize((UINT)eTrinkets::End);
			mTrinkets[(UINT)eTrinkets::FishHead] = new ItemObject(eItemType::Trinket, (UINT)eTrinkets::FishHead, L"Fish Head", std::bind(&ItemManager::FishHead));
			mTrinkets[(UINT)eTrinkets::PinkyEye] = new ItemObject(eItemType::Trinket, (UINT)eTrinkets::PinkyEye, L"Pinky Eye", std::bind(&ItemManager::PinkyEye));
		}

		{ // ActiveItem
			mActives.resize((UINT)eActiveItem::End);

			mActives[(UINT)eActiveItem::TheBible] = new ItemObject(eItemType::ActiveItem, (UINT)eActiveItem::TheBible, L"The Bible", 4, std::bind(&ItemManager::TheBible));
			mActives[(UINT)eActiveItem::TammysHead] = new ItemObject(eItemType::ActiveItem, (UINT)eActiveItem::TammysHead, L"Tammy's Head", 1, std::bind(&ItemManager::TammysHead));
			mActives[(UINT)eActiveItem::YumHeart] = new ItemObject(eItemType::ActiveItem, (UINT)eActiveItem::YumHeart, L"Yum Heart", 4, std::bind(&ItemManager::YumHeart));
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

	ActiveItem* ItemManager::CreateActiveItem(eActiveItem activeType)
	{
		ActiveItem* active = new ActiveItem(activeType);
		Scene * scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(eLayerType::Item);
		layer.AddGameObject(active);

		return active;
	}

	/*std::vector<ItemManager::Events*> ItemManager::GetEvent(eItemType itemType)
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
	}*/

	std::vector<ItemObject*> ItemManager::GetItemObjects(eItemType itemType)
	{
		if(itemType == eItemType::ActiveItem)
		{
			return mActives;
		}
		else if (itemType == eItemType::PassiveItem)
		{

		}
		else if (itemType == eItemType::Pill)
		{
			return mPills;
		}
		else if (itemType == eItemType::Card)
		{
			return mCards;
		}
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

	void ItemManager::TheFool()
	{
		// TODO : 시작 지점으로 텔레포트
	}
	void ItemManager::TheLovers()
	{
		// TODO: 빨간하트 2개 생성
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

	void ItemManager::FishHead()
	{
	}

	void ItemManager::PinkyEye()
	{
	}

	void ItemManager::TheBible()
	{
	}

	/// <summary>
	/// 눈물 여덟갈래로 발사
	/// </summary>
	void ItemManager::TammysHead()
	{
	}

	void ItemManager::YumHeart()
	{
		Scene* scene = SceneManager::GetActiveScene();
		Player* player = scene->GetPlayer();

		if (player == nullptr)
			return;

		player->AddHeart(2);
	}
}