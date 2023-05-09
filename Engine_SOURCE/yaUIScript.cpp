#include "yaUIScript.h"

#include "yaUIScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaObject.h"
#include "yaImageRenderer.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaPlayer.h"
#include "yaNumberScript.h"

#include "yaPill.h"
#include "yaCard.h"

#include "yaItemManager.h"

namespace ya
{
	UIScript::UIScript()
		: Script()
		, mPlayer(nullptr)
		, mHearts{}
		, mActiveItem(nullptr)
		, mChargeBar(nullptr)
		, mConsumable(nullptr)
		, mTrinket(nullptr)
		, mKeyCount(nullptr)
		, mBombCount(nullptr)
		, mCoinCount(nullptr)
	{
	}
	UIScript::~UIScript()
	{
	}
	void UIScript::Initialize()
	{
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> material = Resources::Find<Material>(L"SpriteMaterial");

		{ // ui_hearts
			std::shared_ptr<Texture> ui_heartsTexture = Resources::Find<Texture>(L"ui_hearts");

			for (size_t i = 0; i < 12; i++)
			{
				GameObject* ui_hearts = object::Instantiate<GameObject>(eLayerType::UI);
				Transform* ui_heartsTr = ui_hearts->GetComponent<Transform>();
				ui_heartsTr->SetPosition(Vector3(-3.7f + (0.25f * i), 2.48f, -10.0f));
				ui_heartsTr->SetScale(Vector3(0.32f, 0.32f, 1.0f));

				SpriteRenderer* ui_heartsMr = ui_hearts->AddComponent<SpriteRenderer>();
				ui_heartsMr->SetMesh(mesh);
				ui_heartsMr->SetMaterial(material);

				Animator* animator = ui_hearts->AddComponent<Animator>();

				animator->Create(L"None", ui_heartsTexture, Vector2(96.0f, 48.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 1, 0.1f);
				animator->Create(L"heartFull", ui_heartsTexture, Vector2(0.0f, 0.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 1, 0.1f);
				animator->Create(L"heartHalf", ui_heartsTexture, Vector2(16.0f, 0.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 1, 0.1f);
				animator->Create(L"heartEmpty", ui_heartsTexture, Vector2(32.0f, 0.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 1, 0.1f);
				animator->Create(L"soulFull", ui_heartsTexture, Vector2(0.0f, 16.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 1, 0.1f);
				animator->Create(L"soulHalf", ui_heartsTexture, Vector2(16.0f, 16.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 1, 0.1f);
				animator->Play(L"None", false);

				mHearts.push_back(ui_hearts);
			}
		}

		std::shared_ptr<Texture> hudpickupsTexture = Resources::Find<Texture>(L"hudpickups");

		{ // coin
			GameObject* coin = object::Instantiate<GameObject>(eLayerType::UI);
			Transform* coinTr = coin->GetComponent<Transform>();
			coinTr->SetPosition(Vector3(-4.64f, 1.9f, -10.0f));
			coinTr->SetScale(Vector3(0.32f, 0.32f, 1.0f));

			 ImageRenderer* coinMr = coin->AddComponent<ImageRenderer>();
			coinMr->SetMesh(mesh);
			coinMr->SetMaterial(material);
			coinMr->SetImageSize(hudpickupsTexture, Vector2(0.0f, 0.0f), Vector2(16.0f, 16.0f));
		}
		
		{ // bomb
			GameObject* bomb = object::Instantiate<GameObject>(eLayerType::UI);
			Transform* bombTr = bomb->GetComponent<Transform>();
			bombTr->SetPosition(Vector3(-4.64f, 1.64f, -10.0f));
			bombTr->SetScale(Vector3(0.32f, 0.32f, 1.0f));

			ImageRenderer* bombMr = bomb->AddComponent<ImageRenderer>();
			bombMr->SetMesh(mesh);
			bombMr->SetMaterial(material);
			bombMr->SetImageSize(hudpickupsTexture, Vector2(0.0f, 16.0f), Vector2(16.0f, 16.0f));
		}

		{ // key
			GameObject* key = object::Instantiate<GameObject>(eLayerType::UI);
			Transform* keyTr = key->GetComponent<Transform>();
			keyTr->SetPosition(Vector3(-4.64f, 1.38f, -10.0f));
			keyTr->SetScale(Vector3(0.32f, 0.32f, 1.0f));

			ImageRenderer* keyMr = key->AddComponent<ImageRenderer>();
			keyMr->SetMesh(mesh);
			keyMr->SetMaterial(material);
			keyMr->SetImageSize(hudpickupsTexture, Vector2(16.0f, 0.0f), Vector2(16.0f, 16.0f));
		}

		{ // consumable
			mConsumable = object::Instantiate<GameObject>(eLayerType::UI);
			Transform* ui_cardspillsTr = mConsumable->GetComponent<Transform>();
			ui_cardspillsTr->SetPosition(Vector3(4.5f, -2.5f, -10.0f));
			ui_cardspillsTr->SetScale(Vector3(0.64f, 0.64f, 1.0f));

			std::shared_ptr<Material> ui_cardspillsMaterial = Resources::Find<Material>(L"ui_cardspillsMaterial");
			std::shared_ptr<Texture> ui_cardspillsTexture = ui_cardspillsMaterial->GetTexture();
			std::shared_ptr<Material> ui_cardfrontsMaterial = Resources::Find<Material>(L"ui_cardfrontsMaterial");
			std::shared_ptr<Texture> ui_cardfrontsTexture = ui_cardfrontsMaterial->GetTexture();

			SpriteRenderer* ui_heartsMr = mConsumable->AddComponent<SpriteRenderer>();
			ui_heartsMr->SetMesh(mesh);
			ui_heartsMr->SetMaterial(material);

			Animator* animator = mConsumable->AddComponent<Animator>();
			animator->Create(L"None", ui_cardspillsTexture, Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"pill_1", ui_cardspillsTexture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"pill_2", ui_cardspillsTexture, Vector2(32.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"pill_3", ui_cardspillsTexture, Vector2(64.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"pill_4", ui_cardspillsTexture, Vector2(160.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"pill_5", ui_cardspillsTexture, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"pill_6", ui_cardspillsTexture, Vector2(32.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"pill_7", ui_cardspillsTexture, Vector2(64.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"pill_8", ui_cardspillsTexture, Vector2(160.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"pill_9", ui_cardspillsTexture, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"pill_10", ui_cardspillsTexture, Vector2(32.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"pill_11", ui_cardspillsTexture, Vector2(64.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"pill_12", ui_cardspillsTexture, Vector2(160.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"pill_13", ui_cardspillsTexture, Vector2(160.0f, 96.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);

			animator->Create(L"card_" + std::to_wstring((UINT)eCards::TheFool), ui_cardfrontsTexture, Vector2(0.0f, 0.0f), Vector2(16.0f, 24.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"card_" + std::to_wstring((UINT)eCards::TheLovers), ui_cardfrontsTexture, Vector2(32.0f, 0.0f), Vector2(16.0f, 24.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"card_" + std::to_wstring((UINT)eCards::Club2), ui_cardfrontsTexture, Vector2(64.0f, 48.0f), Vector2(16.0f, 24.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"card_" + std::to_wstring((UINT)eCards::Diamonds2), ui_cardfrontsTexture, Vector2(64.0f, 72.0f), Vector2(16.0f, 24.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"card_" + std::to_wstring((UINT)eCards::Spades2), ui_cardfrontsTexture, Vector2(64.0f, 24.0f), Vector2(16.0f, 24.0f), Vector2::Zero, 1, 0.1f);
			animator->Play(L"None", false);
		}

		{ // Trinket
			mTrinket = object::Instantiate<GameObject>(eLayerType::UI);
			Transform* ui_trinketTr = mTrinket->GetComponent<Transform>();
			ui_trinketTr->SetPosition(Vector3(-4.2f, -2.4f, -10.0f));
			ui_trinketTr->SetScale(Vector3(0.64f, 0.64f, 1.0f));

			SpriteRenderer* ui_trinketMr = mTrinket->AddComponent<SpriteRenderer>();
			ui_trinketMr->SetMesh(mesh);
			ui_trinketMr->SetMaterial(material);

			Animator* animator = mTrinket->AddComponent<Animator>();
			animator->Create(L"None", Resources::Find<Texture>(L"transparent"), Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"trinket_" + std::to_wstring((UINT)eTrinkets::FishHead), Resources::Find<Texture>(L"fishhead"), Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"trinket_" + std::to_wstring((UINT)eTrinkets::PinkyEye), Resources::Find<Texture>(L"pinkyeye"), Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			animator->Play(L"None", false);
		}

		{ // ActiveItem
			mActiveItem = object::Instantiate<GameObject>(eLayerType::UI);
			Transform* activeitemTr = mActiveItem->GetComponent<Transform>();
			activeitemTr->SetPosition(Vector3(-4.45f, 2.35f, -10.0f));
			activeitemTr->SetScale(Vector3(0.64f, 0.64f, 1.0f));

			SpriteRenderer* ui_activeMr = mActiveItem->AddComponent<SpriteRenderer>();
			ui_activeMr->SetMesh(mesh);
			ui_activeMr->SetMaterial(material);

			Animator* animator = mActiveItem->AddComponent<Animator>();
			animator->Create(L"None", Resources::Find<Texture>(L"transparent"), Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"active_" + std::to_wstring((UINT)eActiveItem::TheBible), Resources::Find<Texture>(L"thebible"), Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"active_" + std::to_wstring((UINT)eActiveItem::TammysHead), Resources::Find<Texture>(L"tammyshead"), Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"active_" + std::to_wstring((UINT)eActiveItem::YumHeart), Resources::Find<Texture>(L"yumheart"), Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			animator->Play(L"None", false);
		}

		{ // active Charge
			std::shared_ptr<Material> chargeBarMaterial = Resources::Find<Material>(L"ui_chargebarMaterial");
			std::shared_ptr<Texture> chargeBarTexture = chargeBarMaterial->GetTexture();

			{ // active gauge background
				mChargeBarBackground = object::Instantiate<GameObject>(eLayerType::UI);
				Transform* chargeBarBackgroundTr = mChargeBarBackground->GetComponent<Transform>();
				chargeBarBackgroundTr->SetPosition(Vector3(-4.1f, 2.32f, -10.0f));
				chargeBarBackgroundTr->SetScale(Vector3(0.32f, 0.60f, 1.0f));

				ImageRenderer* chargeBarBackgroundRenderer = mChargeBarBackground->AddComponent<ImageRenderer>();
				chargeBarBackgroundRenderer->SetMesh(mesh);
				chargeBarBackgroundRenderer->SetMaterial(chargeBarMaterial);

				chargeBarBackgroundRenderer->SetImageSize(chargeBarTexture, Vector2(0.0f, 0.0f), Vector2(16.0f, 32.0f));

				mChargeBarBackground->Pause();
			}

			{ // gauge color
				mChargeGauge = object::Instantiate<GameObject>(eLayerType::UI);
				Transform* chargeBarGaugeTr = mChargeGauge->GetComponent<Transform>();
				chargeBarGaugeTr->SetPosition(Vector3(-4.1f, 2.32f, -10.0f));
				chargeBarGaugeTr->SetScale(Vector3(0.32f, 0.60f, 1.0f));

				ImageRenderer* chargeBarGaugeRenderer = mChargeGauge->AddComponent<ImageRenderer>();
				chargeBarGaugeRenderer->SetMesh(mesh);
				std::shared_ptr<Material> chargebar_gaugeMaterial = Resources::Find<Material>(L"ui_chargebar_gaugeMaterial");
				chargeBarGaugeRenderer->SetMaterial(chargebar_gaugeMaterial);

				chargeBarGaugeRenderer->SetImageSize(chargeBarTexture, Vector2(16.0f, 0.0f), Vector2(16.0f, 32.0f));

				mChargeGauge->Pause();
			}

			{	// charge row
				mChargeBar = object::Instantiate<GameObject>(eLayerType::UI);

				Transform* chargeBarTr = mChargeBar->GetComponent<Transform>();
				chargeBarTr->SetPosition(Vector3(-4.1f, 2.32f, -10.0f));
				chargeBarTr->SetScale(Vector3(0.32f, 0.60f, 1.0f));

				SpriteRenderer* chargeBarRenderer = mChargeBar->AddComponent<SpriteRenderer>();
				chargeBarRenderer->SetMesh(mesh);
				chargeBarRenderer->SetMaterial(chargeBarMaterial);

				Animator* animator = mChargeBar->AddComponent<Animator>();
				animator->Create(L"None", chargeBarTexture, Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), Vector2::Zero, 1, 0.1f);
				animator->Create(L"charge_12", chargeBarTexture, Vector2(32.0f, 0.0f), Vector2(16.0f, 32.0f), Vector2::Zero, 1, 0.1f);
				animator->Create(L"charge_6", chargeBarTexture, Vector2(48.0f, 0.0f), Vector2(16.0f, 32.0f), Vector2::Zero, 1, 0.1f);
				animator->Create(L"charge_4", chargeBarTexture, Vector2(0.0f, 32.0f), Vector2(16.0f, 32.0f), Vector2::Zero, 1, 0.1f);
				animator->Create(L"charge_3", chargeBarTexture, Vector2(16.0f, 32.0f), Vector2(16.0f, 32.0f), Vector2::Zero, 1, 0.1f);
				animator->Create(L"charge_2", chargeBarTexture, Vector2(32.0f, 32.0f), Vector2(16.0f, 32.0f), Vector2::Zero, 1, 0.1f);
				animator->Create(L"charge_1", chargeBarTexture, Vector2(48.0f, 32.0f), Vector2(16.0f, 32.0f), Vector2::Zero, 1, 0.1f);
				animator->Play(L"None", false);

				mChargeBar->Pause();
			}
		}

		Scene* scene = SceneManager::GetActiveScene();
		mPlayer = scene->GetPlayer();

		if (mPlayer != nullptr)
		{
			Player::Pickup pickup = mPlayer->GetPickup();

			{ // coin count
				GameObject* coinCount = object::Instantiate<GameObject>(eLayerType::UI);
				Transform* coinTr = coinCount->GetComponent<Transform>();
				coinTr->SetPosition(Vector3(-4.42f, 1.9f, 0.0f));
				coinTr->SetScale(Vector3(0.15f, 0.15f, 1.0f));
				mCoinCount = coinCount->AddComponent<NumberScript>();
				mCoinCount->SetNumber(pickup.coin);
			}

			{ // bomb count
				GameObject* bombCount = object::Instantiate<GameObject>(eLayerType::UI);
				Transform* bombTr = bombCount->GetComponent<Transform>();
				bombTr->SetPosition(Vector3(-4.42f, 1.64f, 0.0f));
				bombTr->SetScale(Vector3(0.15f, 0.15f, 1.0f));
				mBombCount = bombCount->AddComponent<NumberScript>();
				mBombCount->SetNumber(pickup.bomb);
			}

			{ // key count
				GameObject* keyCount = object::Instantiate<GameObject>(eLayerType::UI);
				Transform* keyTr = keyCount->GetComponent<Transform>();
				keyTr->SetPosition(Vector3(-4.42f, 1.38f, 0.0f));
				keyTr->SetScale(Vector3(0.15f, 0.15f, 1.0f));
				mKeyCount = keyCount->AddComponent<NumberScript>();
				mKeyCount->SetNumber(pickup.key);
			}
		}
	}

	void UIScript::Update()
	{
		Player::Info info = mPlayer->GetInfo();

		int heartmax = info.heartMax / 2;
		int heartfull = info.heart / 2;
		int hearthalf = info.heart % 2;
		int soulheart = info.soulHeart / 2;
		int soulhearthalf = info.soulHeart % 2;

		int pos = 0;
		for (size_t i = 0; i < heartmax; i++, pos++)
		{
			GameObject* obj = mHearts[pos];
			Animator* anim = obj->GetComponent<Animator>();

			if (i < heartfull)
			{
				anim->Play(L"heartFull");
			}
			else if (i == heartfull)
			{
				if (hearthalf == 1)
					anim->Play(L"heartHalf");
				else
					anim->Play(L"heartEmpty");
			}
			else
			{
				anim->Play(L"heartEmpty");
			}
		}

		for (size_t i = 0; i < soulheart; i++, pos++)
		{
			GameObject* obj = mHearts[pos];
			Animator* anim = obj->GetComponent<Animator>();

			anim->Play(L"soulFull");
		}

		if (soulhearthalf == 1)
		{
			GameObject* obj = mHearts[pos];
			Animator* anim = obj->GetComponent<Animator>();

			anim->Play(L"soulHalf");
			pos++;
		}

		for (size_t i = pos; i < mHearts.size(); i++, pos++)
		{
			GameObject* obj = mHearts[pos];
			Animator* anim = obj->GetComponent<Animator>();

			anim->Play(L"None");
		}

		Player::Pickup pickup = mPlayer->GetPickup();
		mCoinCount->SetNumber(pickup.coin);
		mBombCount->SetNumber(pickup.bomb);
		mKeyCount->SetNumber(pickup.key);

		Player::Items items = mPlayer->GetItem();

		// Consumble
		{
			Animator* animator = mConsumable->GetComponent<Animator>();
			Transform* transform = mConsumable->GetComponent<Transform>();

			if (items.pill != ePills::None)
			{
				std::wstring name = L"pill_" + std::to_wstring((UINT)items.pill);
				Animation* animation = animator->FindAnimation(name);
				transform->SetScale(Vector3(0.64f, 0.64f, 1.0f));

				if(animation != nullptr)
					animator->Play(name);
			}
			else if (items.card != eCards::None)
			{
				std::wstring name = L"card_" + std::to_wstring((UINT)items.card);
				Animation* animation = animator->FindAnimation(name);
				transform->SetScale(Vector3(0.32f, 0.48f, 1.0f));

				if (animation != nullptr)
					animator->Play(name);
			}
			else
			{
				animator->Play(L"None");
			}
		}

		// trinket
		{
			Animator* animator = mTrinket->GetComponent<Animator>();
			Transform* transform = mTrinket->GetComponent<Transform>();

			if (items.trinket != eTrinkets::None)
			{
				std::wstring name = L"trinket_" + std::to_wstring((UINT)items.trinket);
				Animation* animation = animator->FindAnimation(name);
				transform->SetScale(Vector3(0.64f, 0.64f, 1.0f));

				if (animation != nullptr)
					animator->Play(name);
			}
			else
			{
				animator->Play(L"None");
			}
		}
		
		// active item
		{
			eActiveItem activeItem = items.activeItem;

			Animator* activeItemAnim = mActiveItem->GetComponent<Animator>();
			Animator* chargeBarAnim = mChargeBar->GetComponent<Animator>();
			if (activeItem != eActiveItem::None)
			{
				activeItemAnim->Play(L"active_" + std::to_wstring((UINT)activeItem));

				ItemObject* obj = ItemManager::GetItemObjects(eItemType::ActiveItem)[(UINT)activeItem];
				int gauge = obj->GetGauge();
				int charge = obj->GetCharge();

				Animation* an = chargeBarAnim->FindAnimation(L"charge_" + std::to_wstring(gauge));
				if(an != nullptr)
					chargeBarAnim->Play(L"charge_" + std::to_wstring(gauge));

				ImageRenderer* mr = mChargeGauge->GetComponent<ImageRenderer>();
				std::shared_ptr<Material> material = mr->GetMaterial();
				Vector4 data = Vector4(0.0f, 0.85f - (0.8f * ((float)charge / (float)gauge)), 1.0f, 1.0f);
				material->SetData(eGPUParam::Vector4, &data);

				ActiveActiveItem(true);
			}
			else
			{
				activeItemAnim->Play(L"None");
				chargeBarAnim->Play(L"None");

				ActiveActiveItem(false);
			}
		}
		
	}

	void UIScript::FixedUpdate()
	{
	}

	void UIScript::Render()
	{
	}

	void UIScript::ActiveActiveItem(bool active)
	{
		if (active)
		{
			mActiveItem->SetActive();
			mChargeGauge->SetActive();
			mChargeBar->SetActive();
			mChargeBarBackground->SetActive();
		}
		else
		{
			mActiveItem->Pause();
			mChargeGauge->Pause();
			mChargeBar->Pause();
			mChargeBarBackground->Pause();
		}
	}
}