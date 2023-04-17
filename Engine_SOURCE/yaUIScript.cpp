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

namespace ya
{
	UIScript::UIScript()
		: Script()
		, mPlayer(nullptr)
		, mHearts{}
		, mActiveItem(nullptr)
		, mConsumable(nullptr)
		, Trinket(nullptr)
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
				GameObject* ui_hearts = object::Instantiate<GameObject>(eLayerType::Background);
				Transform* ui_heartsTr = ui_hearts->GetComponent<Transform>();
				ui_heartsTr->SetPosition(Vector3(-3.7f + (0.25f * i), 2.48f, 1.0f));
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
			coinTr->SetPosition(Vector3(-4.64f, 1.9f, 0.0f));
			coinTr->SetScale(Vector3(0.32f, 0.32f, 1.0f));

			ImageRenderer* coinMr = coin->AddComponent<ImageRenderer>();
			coinMr->SetMesh(mesh);
			coinMr->SetMaterial(material);
			coinMr->SetImageSize(hudpickupsTexture, Vector2(0.0f, 0.0f), Vector2(16.0f, 16.0f));
		}
		
		{ // bomb
			GameObject* bomb = object::Instantiate<GameObject>(eLayerType::UI);
			Transform* bombTr = bomb->GetComponent<Transform>();
			bombTr->SetPosition(Vector3(-4.64f, 1.64f, 0.0f));
			bombTr->SetScale(Vector3(0.32f, 0.32f, 1.0f));

			ImageRenderer* bombMr = bomb->AddComponent<ImageRenderer>();
			bombMr->SetMesh(mesh);
			bombMr->SetMaterial(material);
			bombMr->SetImageSize(hudpickupsTexture, Vector2(0.0f, 16.0f), Vector2(16.0f, 16.0f));
		}

		{ // key
			GameObject* key = object::Instantiate<GameObject>(eLayerType::UI);
			Transform* keyTr = key->GetComponent<Transform>();
			keyTr->SetPosition(Vector3(-4.64f, 1.38f, 0.0f));
			keyTr->SetScale(Vector3(0.32f, 0.32f, 1.0f));

			ImageRenderer* keyMr = key->AddComponent<ImageRenderer>();
			keyMr->SetMesh(mesh);
			keyMr->SetMaterial(material);
			keyMr->SetImageSize(hudpickupsTexture, Vector2(16.0f, 0.0f), Vector2(16.0f, 16.0f));
		}

		{ // pill
			mConsumable = object::Instantiate<GameObject>(eLayerType::UI);
			Transform* ui_cardspillsTr = mConsumable->GetComponent<Transform>();
			ui_cardspillsTr->SetPosition(Vector3(4.5f, -2.5f, 0.0f));
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

			animator->Create(L"card_1", ui_cardfrontsTexture, Vector2(0.0f, 0.0f), Vector2(16.0f, 24.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"card_2", ui_cardfrontsTexture, Vector2(32.0f, 0.0f), Vector2(16.0f, 24.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"card_3", ui_cardfrontsTexture, Vector2(80.0f, 48.0f), Vector2(16.0f, 24.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"card_4", ui_cardfrontsTexture, Vector2(80.0f, 72.0f), Vector2(16.0f, 24.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"card_5", ui_cardfrontsTexture, Vector2(80.0f, 24.0f), Vector2(16.0f, 24.0f), Vector2::Zero, 1, 0.1f);
			animator->Play(L"None", false);
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


		// Consumble
		{
			Animator* animator = mConsumable->GetComponent<Animator>();
			Transform* transform = mConsumable->GetComponent<Transform>();

			Player::Items items = mPlayer->GetItem();
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
	}

	void UIScript::FixedUpdate()
	{
	}

	void UIScript::Render()
	{
	}
}