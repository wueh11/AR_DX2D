#include "yaPlayerScript.h"
#include "yaPlayer.h"

#include "yaObject.h"
#include "yaGameObject.h"

#include "yaResources.h"
#include "yaInput.h"
#include "yaTime.h"

#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaRigidbody.h"

#include "yaSpriteRenderer.h"
#include "yaImageRenderer.h"

#include "yaTear.h"
#include "yaPlayerTearScript.h"

#include "yaItemManager.h"
#include "yaItem.h"
#include "yaActiveItem.h"
#include "yaPickup.h"
#include "yaDropBomb.h"
#include "yaPill.h"
#include "yaCard.h"
#include "yaTrinket.h"

#include "yaSceneManager.h"
#include "yaStageScene.h"
#include "yaScene.h"

#include "Commons.h"

#include "yaFmod.h"
#include "yaAudioClip.h"

namespace ya
{
	PlayerScript::PlayerScript()
		: Script()
		, mTransform(nullptr)
		, mRigidbody(nullptr)
		, mHead(nullptr)
		, mBody(nullptr)
		, mWhole(nullptr)
		, mStarflash(nullptr)
		, mGainItem(nullptr)

		, mInvincibleTime(0.0f)
		, mInvincibleTimeMax(1.5f)
		, mbInvincible(false)
		, mItemActionTime(0.0f)
		, mItemActionTimeMax(1.0f)
		, mbItemAction(false)
		, mDropTime(0.0f)
		, mDropTimeMax(2.0f)
		, mGainItemTime(0.0f)
		, mGainItemTimeMax(1.0f)
		, mbGainItem(true)
		, mAttackSpeed(0.0f)
		, mAttackAble(true)
	{
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Initialize()
	{
		//Transform* playerTr = GetOwner()->GetComponent<Transform>();
		//playerTr->SetScale(Vector3(0.64f, 0.64f, 1.0f));

		mTransform = GetOwner()->GetComponent<Transform>();
		mRigidbody = GetOwner()->GetComponent<Rigidbody>();

		Collider2D* collider = GetOwner()->GetComponent<Collider2D>();
		collider->SetSize(Vector2(0.3f, 0.4f));
		collider->SetCenter(Vector2(0.0f, -0.05f));
		collider->SetColliderType(eColliderType::Rect);

		Player* player = dynamic_cast<Player*>(GetOwner());
		isaac::Status status = player->GetStatus();

		player->SetSpeed();

		SpriteRenderer* rd = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		rd->SetMesh(mesh);
		std::shared_ptr<Material> material = Resources::Find<Material>(L"isaacMaterial");
		rd->SetMaterial(material);
		std::shared_ptr<Texture> texture = material->GetTexture();

		{ // whole
			mWhole = object::Instantiate<GameObject>(eLayerType::Player, mTransform);

			mWhole->GetComponent<Transform>()->SetScale(Vector3(1.32f, 1.32f, 1.0f));

			SpriteRenderer* mMr = mWhole->AddComponent<SpriteRenderer>();
			mMr->SetMesh(mesh);
			mMr->SetMaterial(material);

			Animator* wholeAnimator = mWhole->AddComponent<Animator>();
			wholeAnimator->Create(L"None", texture, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2::Zero, 1, 0.1f);
			wholeAnimator->Create(L"Hurt", texture, Vector2(128.0f, 192.0f), Vector2(64.0f, 64.0f), Vector2(0.0f, -0.025f), 1, 0.1f);
			wholeAnimator->Create(L"Die", texture, Vector2(0.0f, 128.0f), Vector2(64.0f, 64.0f), Vector2(0.0f, -0.025f), 1, 0.2f);
			wholeAnimator->Add(L"Die", texture, Vector2(128.0f, 192.0f), Vector2(64.0f, 64.0f), Vector2(0.0f, -0.025f), 1, 0.2f);
			wholeAnimator->Add(L"Die", texture, Vector2(192.0f, 128.0f), Vector2(64.0f, 64.0f), Vector2(0.0f, -0.025f), 1, 0.3f);
			wholeAnimator->Play(L"None", false);
		}

		{ // body
			mBody = object::Instantiate<GameObject>(eLayerType::Player, mTransform);

			mBody->GetComponent<Transform>()->SetScale(Vector3(0.64f, 0.64f, 1.0f));

			SpriteRenderer* mMr = mBody->AddComponent<SpriteRenderer>();
			mMr->SetMesh(mesh);
			mMr->SetMaterial(material);

			Animator* bodyAnimator = mBody->AddComponent<Animator>();
			bodyAnimator->Create(L"None", texture, Vector2(0.0f, 480.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			bodyAnimator->Create(L"FrontIdle", texture, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			bodyAnimator->Create(L"FrontWalk", texture, Vector2(192.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 2, 0.1f);
			bodyAnimator->Add(L"FrontWalk", texture, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 8, 0.1f);
			bodyAnimator->Create(L"SideIdle", texture, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			bodyAnimator->Create(L"SideWalk", texture, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 8, 0.1f);
			bodyAnimator->Create(L"ItemIdle", texture, Vector2(448.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			bodyAnimator->Create(L"ItemWalk", texture, Vector2(448.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 2, 0.1f);
			bodyAnimator->Add(L"ItemWalk", texture, Vector2(256.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 18, 0.1f, 8, 3);
			bodyAnimator->Play(L"FrontIdle", true);
		}

		{ // head
			mHead = object::Instantiate<GameObject>(eLayerType::Player, mTransform);

			mHead->GetComponent<Transform>()->SetScale(Vector3(0.64f, 0.64f, 1.0f));

			SpriteRenderer* mMr = mHead->AddComponent<SpriteRenderer>();
			mMr->SetMesh(mesh);
			mMr->SetMaterial(material);

			Animator* headAnimator = mHead->AddComponent<Animator>();
			headAnimator->Create(L"None", texture, Vector2(0.0f, 480.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			headAnimator->Create(L"FrontIdle", texture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			headAnimator->Create(L"FrontAttack", texture, Vector2(32.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			headAnimator->Create(L"SideIdle", texture, Vector2(64.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			headAnimator->Create(L"SideAttack", texture, Vector2(96.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			headAnimator->Create(L"BackIdle", texture, Vector2(128.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			headAnimator->Create(L"BackAttack", texture, Vector2(160.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			headAnimator->Create(L"ItemIdle", texture, Vector2(256.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			
			headAnimator->Play(L"FrontIdle", true);
		}

		Transform* headTr = mHead->GetComponent<Transform>();
		headTr->SetPosition(Vector3(0.0f, 0.1f, 0.0f));
		Transform* bodyTr = mBody->GetComponent<Transform>();
		bodyTr->SetPosition(Vector3(0.0f, -0.1f, 0.0f));

		{ // starflash
			mStarflash = object::Instantiate<GameObject>(eLayerType::Player, mTransform);

			std::shared_ptr<Material> starflashMaterial = Resources::Find<Material>(L"starflashMaterial");
			std::shared_ptr<Texture> starflashTexture = starflashMaterial->GetTexture();
			
			SpriteRenderer* starflashMr = mStarflash->AddComponent<SpriteRenderer>();
			starflashMr->SetMesh(mesh);
			starflashMr->SetMaterial(starflashMaterial);

			Animator* starflashAnimator = mStarflash->AddComponent<Animator>();
			starflashAnimator->Create(L"starflash", starflashTexture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 12, 0.1f, 4, 3);
			starflashAnimator->Play(L"starflash", true);

			Transform* starflashTr = mStarflash->GetComponent<Transform>();
			starflashTr->SetPosition(Vector3(0.0f, 0.7f, 1.0f));
			//starflashTr->SetScale(Vector3(0.64f, 0.64f, 1.0f));
			mStarflash->Pause();
		}

		{
			mGainItem = object::Instantiate<GameObject>(eLayerType::Player, mTransform);

			std::shared_ptr<Material> gainItemMaterial = Resources::Find<Material>(L"gainItemMaterial");
			ImageRenderer* gainItemMr = mGainItem->AddComponent<ImageRenderer>();
			gainItemMr->SetMesh(mesh);
			gainItemMr->SetMaterial(gainItemMaterial);

			Transform* gainItemTr = mGainItem->GetComponent<Transform>();
			gainItemTr->SetPosition(Vector3(0.0f, 0.7f, 1.0f));
			gainItemTr->SetScale(Vector3(0.64f, 0.64f, 1.0f));
			mGainItem->Pause();
		}

		Shadow(Vector3(0.0f, -0.24f, 0.0f), Vector3(0.4f, 0.16f, 0.0f));

		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"Issac\\sfx\\hurt_grunt.wav");
			Resources::Insert<AudioClip>(L"hurt", clip);
		}
	}

	void PlayerScript::Update()
	{
		Player* player = dynamic_cast<Player*>(GetOwner());
		
		Player::Info info = player->GetInfo();
		if (info.heart < 0)
			player->SetHeart(0);

		Player::Items items = player->GetItem();

		Vector3 pos = mTransform->GetPosition();

		if (mbInvincible)
		{
			if (mInvincibleTime > 0.0f)
			{
				mInvincibleTime -= Time::DeltaTime();

				BaseRenderer* rd = GetOwner()->GetComponent<BaseRenderer>();
				if (SinByTime(0.05f, 1.0f) > -0.5f)
					rd->SetAlpha(0.01f);
				else
					rd->SetAlpha(1.0f);
			}
			else
			{
				mbInvincible = false;
				Idle();
			}
		}

		if (mbItemAction)
		{
			if (mItemActionTime > 0.0f)
			{
				mItemActionTime -= Time::DeltaTime();
			}
			else
			{
				mbItemAction = false;
				mStarflash->Pause();
				mGainItem->Pause();
				Idle();
			}
		}

		if (!mbGainItem)
		{
			if (mGainItemTime > 0.0f)
				mGainItemTime -= Time::DeltaTime();
			else
				mbGainItem = true;
		}

		Move();
		Attack();

		// 폭탄
		if (Input::GetKeyDown(eKeyCode::E))
		{
			if (player->GetPickup().bomb > 0)
			{
				DropBomb* bomb = new DropBomb(pos);
				Scene* scene = SceneManager::GetActiveScene();
				Layer& layer = scene->GetLayer(eLayerType::Item);
				layer.AddGameObject(bomb);

				player->AddBomb(-1);
			}
		}

		// 액티브 아이템 사용
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			if(items.activeItem != eActiveItem::None)
			{
				ItemObject* itemObject = ItemManager::GetItemObjects(eItemType::ActiveItem)[(UINT)items.activeItem];
				if (itemObject->GetCharge() == itemObject->GetGauge())
				{
					itemObject->PlayEvent();
					itemObject->resetCharge();
				}
			}
		}

		// 픽업 아이템 사용 
		if (Input::GetKeyDown(eKeyCode::Q))
		{
			UseConsumable();
		}

		// 장신구, 소모품 드랍
		if (Input::GetKey(eKeyCode::LCTRL))
		{
			//3초간 누르면 아이템 drop
			if (mDropTime > 0.0f)
			{
				mDropTime -= Time::DeltaTime();
			}
			else
			{
				mGainItemTime = mGainItemTimeMax;
				mbGainItem = false;
				ThrowConsumable();
				ThrowTrinket();
			}
		}
		else if (Input::GetKeyDown(eKeyCode::LCTRL))
		{
			mDropTime = mDropTimeMax;
		}
		else if (Input::GetKeyUp(eKeyCode::LCTRL))
		{
			mDropTime = mDropTimeMax;
		}



		if (Input::GetKeyDown(eKeyCode::N_9))
		{
			Hurt();
		}
		if (Input::GetKeyDown(eKeyCode::N_0))
		{
			Die();
		}
		if (Input::GetKeyDown(eKeyCode::N_1))
		{
			player->AddHeart(1);
		}
		if (Input::GetKeyDown(eKeyCode::N_2))
		{
			player->AddSoulHeart(1);
		}
		if (Input::GetKeyDown(eKeyCode::N_3))
		{
			player->AddMaxHeart(2);
		}
		if (Input::GetKeyDown(eKeyCode::N_4))
		{
			player->AddMaxHeart(-2);
		}

		if (Input::GetKeyDown(eKeyCode::N_8))
		{
			if (items.activeItem != eActiveItem::None)
			{
				ItemObject* itemObject = ItemManager::GetItemObjects(eItemType::ActiveItem)[(UINT)items.activeItem];
				itemObject->AddCharge(1);
			}
		}

		Script::Update();
	}

	void PlayerScript::FixedUpdate()
	{
		StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());
		if (scene == nullptr)
			return;

		Vector3 pos = mTransform->GetPosition();
		Room* currentRoom = scene->GetCurrentRoom();
		if(currentRoom != nullptr)
		{
			Vector3 roomPos = currentRoom->GetComponent<Transform>()->GetPosition();
			mTransform->SetPosition(Vector3(pos.x, pos.y, PositionZ(pos.y - roomPos.y) + roomPos.z));
		}

		Script::FixedUpdate();
	}
	void PlayerScript::Render()
	{
		Script::Render();
	}

	void PlayerScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void PlayerScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void PlayerScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void PlayerScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void PlayerScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void PlayerScript::OnTriggerExit(Collider2D* collider)
	{
	}

	void PlayerScript::Idle()
	{
		Animator* wholeAnimator = mWhole->GetComponent<Animator>();
		Animator* headAnimator = mHead->GetComponent<Animator>();
		Animator* bodyAnimator = mBody->GetComponent<Animator>();

		wholeAnimator->Play(L"None", false);
		headAnimator->Play(L"FrontIdle", false);
		bodyAnimator->Play(L"FrontIdle", false);
		//mTransform->SetScale(Vector3(0.66f, 0.66f, 1.0f));
	}

	void PlayerScript::Move()
	{
		Player* player = dynamic_cast<Player*>(GetOwner());
		isaac::Status status = player->GetStatus();
		float speed = 1.8f + status.speed;
		Rigidbody* rigidbody = player->GetComponent<Rigidbody>();

		//TODO: set speed 
		rigidbody->SetLimitVelocity(Vector3(speed, speed, 0.0f));

		float s = 20.0f;

		/// 이동
		if (Input::GetKey(eKeyCode::W))
			mRigidbody->AddForce(Vector3(0.0f, s, 0.0f));
		else if (Input::GetKey(eKeyCode::S))
			mRigidbody->AddForce(Vector3(0.0f, -s, 0.0f));
		
		if (Input::GetKey(eKeyCode::A))
			mRigidbody->AddForce(Vector3(-s, 0.0f, 0.0f));
		else if (Input::GetKey(eKeyCode::D))
			mRigidbody->AddForce(Vector3(s, 0.0f, 0.0f));


		Animator* headAnimator = mHead->GetComponent<Animator>();
		Animator* bodyAnimator = mBody->GetComponent<Animator>();

		if (!mbInvincible)
		{
			// 애니메이션
			if (!mbItemAction)
			{
				if (Input::GetKeyDown(eKeyCode::W))
				{
					Idle();
					headAnimator->Play(L"BackIdle", true);
					bodyAnimator->Play(L"FrontWalk", true);
				}
				else if (Input::GetKeyDown(eKeyCode::S))
				{
					Idle();
					headAnimator->Play(L"FrontIdle", true);
					bodyAnimator->Play(L"FrontWalk", true);
				}
				else if (Input::GetKeyDown(eKeyCode::A))
				{
					Idle();
					headAnimator->Play(L"SideIdle", true);
					bodyAnimator->Play(L"SideWalk", true);
				}
				else if (Input::GetKeyDown(eKeyCode::D))
				{
					Idle();
					headAnimator->Play(L"SideIdle", true);
					bodyAnimator->Play(L"SideWalk", true);
				}

				if (Input::GetKeyNone(eKeyCode::W) && Input::GetKeyNone(eKeyCode::A) && Input::GetKeyNone(eKeyCode::S) && Input::GetKeyNone(eKeyCode::D))
				{
					bodyAnimator->Play(L"FrontIdle", true);
				}

				Transform* headTr = mHead->GetComponent<Transform>();
				Transform* bodyTr = mBody->GetComponent<Transform>();

				if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyDown(eKeyCode::A))
				{
					headTr->SetRotation(Vector3(0.0f, XM_PI, 0.0f));
					bodyTr->SetRotation(Vector3(0.0f, XM_PI, 0.0f));
				}
				else if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKeyDown(eKeyCode::D))
				{
					headTr->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
					bodyTr->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
				}
			}
			else
			{
				if (Input::GetKeyDown(eKeyCode::W) || Input::GetKeyDown(eKeyCode::S) || Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
					bodyAnimator->Play(L"ItemWalk", true);
	
				if (Input::GetKeyUp(eKeyCode::W) || Input::GetKeyUp(eKeyCode::S) || Input::GetKeyUp(eKeyCode::A) || Input::GetKeyUp(eKeyCode::D))
					bodyAnimator->Play(L"ItemIdle", true);
			}
		}
	}

	void PlayerScript::Attack()
	{
		Animator* wholeAnimator = mWhole->GetComponent<Animator>();
		Animator* headAnimator = mHead->GetComponent<Animator>();
		Animator* bodyAnimator = mBody->GetComponent<Animator>();

		if (Input::GetKeyUp(eKeyCode::UP))
		{
			headAnimator->Play(L"BackIdle", true);
		}
		else if (Input::GetKeyUp(eKeyCode::DOWN))
		{
			headAnimator->Play(L"FrontIdle", true);
		}
		else if (Input::GetKeyUp(eKeyCode::LEFT))
		{
			headAnimator->Play(L"SideIdle", true);
		}
		else if (Input::GetKeyUp(eKeyCode::RIGHT))
		{
			headAnimator->Play(L"SideIdle", true);
		}

		if (mAttackSpeed <= 0.0f)
		{
			mAttackAble = true;
			mAttackSpeed = dynamic_cast<Player*>(GetOwner())->GetStatus().attackSpeed;
		}

		if (!mAttackAble)
		{
			mAttackSpeed -= 10.0f * Time::DeltaTime();
			return;
		}

		// 눈물 발사
		if (Input::GetKey(eKeyCode::UP))
		{
			Idle();
			headAnimator->Play(L"BackAttack", true);
			Tear* tear = object::Instantiate<Tear>(eLayerType::Projectile);
			tear->InitTear(GetOwner(), Vector3(0.0f, 1.0f, 0.0f));
			tear->AddComponent<PlayerTearScript>();
			mAttackAble = false;
		}
		else if (Input::GetKey(eKeyCode::DOWN))
		{
			Idle();
			headAnimator->Play(L"FrontAttack", true);
			Tear* tear = object::Instantiate<Tear>(eLayerType::Projectile);
			tear->InitTear(GetOwner(), Vector3(0.0f, -1.0f, 0.0f));
			tear->AddComponent<PlayerTearScript>();
			mAttackAble = false;
		}
		else if (Input::GetKey(eKeyCode::LEFT))
		{
			Idle();
			headAnimator->Play(L"SideAttack", true);
			Tear* tear = object::Instantiate<Tear>(eLayerType::Projectile);
			tear->InitTear(GetOwner(), Vector3(-1.0f, 0.0f, 0.0f));
			tear->AddComponent<PlayerTearScript>();
			mAttackAble = false;
		}
		else if (Input::GetKey(eKeyCode::RIGHT))
		{
			Idle();
			headAnimator->Play(L"SideAttack", true);
			Tear* tear = object::Instantiate<Tear>(eLayerType::Projectile);
			tear->InitTear(GetOwner(), Vector3(1.0f, 0.0f, 0.0f));
			tear->AddComponent<PlayerTearScript>();
			mAttackAble = false;
		}
	}

	void PlayerScript::ItemAction()
	{
		mItemActionTime = mItemActionTimeMax;
		mbItemAction = true;

		Animator* headAnimator = mHead->GetComponent<Animator>();
		Animator* bodyAnimator = mBody->GetComponent<Animator>();

		headAnimator->Play(L"ItemIdle", false);
		bodyAnimator->Play(L"ItemIdle", false);

		//mTransform->SetScale(Vector3(0.66f, 0.66f, 1.0f));

		mStarflash->SetActive();
		mGainItem->SetActive();

		mGainItemTime = mGainItemTimeMax;
		mbGainItem = false;
	}

	void PlayerScript::Hurt()
	{
		if (mbInvincible)
			return;

		Animator* wholeAnimator = mWhole->GetComponent<Animator>();
		Animator* headAnimator = mHead->GetComponent<Animator>();
		Animator* bodyAnimator = mBody->GetComponent<Animator>();

		headAnimator->Play(L"None", false);
		bodyAnimator->Play(L"None", false);
		wholeAnimator->Play(L"Hurt", false);

		//mTransform->SetScale(Vector3(1.32f, 1.32f, 1.0f));

		Player* player = dynamic_cast<Player*>(GetOwner());
		Player::Info info = player->GetInfo();
		if (info.soulHeart > 0)
			player->AddSoulHeart(-1);
		else 
			player->AddHeart(-1);

		Invincible();

		std::shared_ptr<AudioClip> clip = Resources::Find<AudioClip>(L"hurt");
		clip->Play();
	}

	void PlayerScript::Die()
	{
		Animator* wholeAnimator = mWhole->GetComponent<Animator>();
		Animator* headAnimator = mHead->GetComponent<Animator>();
		Animator* bodyAnimator = mBody->GetComponent<Animator>();

		headAnimator->Play(L"None", false);
		bodyAnimator->Play(L"None", false);
		wholeAnimator->Play(L"Die", false);

		//mTransform->SetScale(Vector3(1.32f, 1.32f, 1.0f));
	}

	/// <summary>
	/// 무적 시간
	/// </summary>
	void PlayerScript::Invincible()
	{
		mInvincibleTime = mInvincibleTimeMax;
		mbInvincible = true;
	}

	void PlayerScript::gainActiveItem(ActiveItem* item)
	{
		Player* player = dynamic_cast<Player*>(GetOwner());
		
		eActiveItem active = item->GetActveItemType();
		player->SetActiveItem(active);
		ItemAction();

		SetGainItem(item->GetComponent<Animator>());
	}

	void PlayerScript::gainConsumable(Pickup* pickup)
	{
		Player* player = dynamic_cast<Player*>(GetOwner());
		Player::Items item = player->GetItem();

		eItemType type = pickup->GetItemType();

		if (type == eItemType::Pill)
		{
			Pill* pill = dynamic_cast<Pill*>(pickup);
			ePills type = pill->GetPillType();

			if (item.pill != ePills::None)
			{
				ThrowConsumable();
			}
			else if (item.card != eCards::None)
			{
				ThrowConsumable();
			}

			player->SetPill(type);

		}
		else if (type == eItemType::Card)
		{
			Card* card = dynamic_cast<Card*>(pickup);
			eCards type = card->GetCardType();

			if (item.card != eCards::None)
			{
				ThrowConsumable();
			}
			else if (item.pill != ePills::None)
			{
				ThrowConsumable();
			}

			player->SetCard(type);
		}

		ItemAction();
		SetGainItem(pickup->GetComponent<Animator>());
	}

	void PlayerScript::gainTrinket(Trinket* item)
	{
		Player* player = dynamic_cast<Player*>(GetOwner());
		ThrowTrinket();

		eTrinkets trinket = item->GetTrinketType();
		player->SetTrinket(trinket);
		ItemAction();
		SetGainItem(item->GetComponent<Animator>());
	}
	
	void PlayerScript::UseActiveItem()
	{
		Player* player = dynamic_cast<Player*>(GetOwner());
		Player::Items item = player->GetItem();
		ItemManager::GetItemObjects(eItemType::ActiveItem)[(UINT)item.activeItem]->PlayEvent();
	}

	void PlayerScript::UseConsumable()
	{
		Player* player = dynamic_cast<Player*>(GetOwner());
		Player::Items item = player->GetItem();
		
		if (item.pill != ePills::None)
		{
			ItemManager::GetItemObjects(eItemType::Pill)[(UINT)item.pill]->PlayEvent();
			player->SetPill(ePills::None);


			StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());
			Pill* gainPill = object::Instantiate<Pill>(eLayerType::Item, scene->GetCurrentRoom());
			gainPill->SetPillType(item.pill);

			SetGainItem(gainPill->GetComponent<Animator>());
			gainPill->Death();

			ItemAction();
		}
		else if (item.card != eCards::None)
		{
			ItemManager::GetItemObjects(eItemType::Card)[(UINT)item.card]->PlayEvent();
			player->SetCard(eCards::None);

			StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());
			//Card* gainCard = ItemManager::CreateCard(item.card);
			Card* gainCard = object::Instantiate<Card>(eLayerType::Item, scene->GetCurrentRoom());
			gainCard->SetCardType(item.card);
			SetGainItem(gainCard->GetComponent<Animator>());
			gainCard->Death();

			ItemAction();
		}	
	}

	void PlayerScript::ThrowConsumable()
	{
		Player* player = dynamic_cast<Player*>(GetOwner());
		Player::Items item = player->GetItem();

		if (item.pill != ePills::None)
		{
			player->SetPill(ePills::None);

			StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());
			Pill* pill = object::Instantiate<Pill>(eLayerType::Item, scene->GetCurrentRoom());
			pill->SetPillType(item.pill);

			pill->GetComponent<Transform>()->SetPosition(player->GetComponent<Transform>()->GetPosition());
		}

		if (item.card != eCards::None)
		{
			player->SetCard(eCards::None);
			StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());
			Card* card = object::Instantiate<Card>(eLayerType::Item, scene->GetCurrentRoom());
			card->SetCardType(item.card);

			card->GetComponent<Transform>()->SetPosition(player->GetComponent<Transform>()->GetPosition());
		}
	}
	void PlayerScript::ThrowTrinket()
	{
		Player* player = dynamic_cast<Player*>(GetOwner());
		Player::Items item = player->GetItem();

		if (item.trinket != eTrinkets::None)
		{
			player->SetTrinket(eTrinkets::None);

			StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());
			Trinket* trinket = object::Instantiate<Trinket>(eLayerType::Item, scene->GetCurrentRoom());
			trinket->SetTrinketType(item.trinket);

			trinket->GetComponent<Transform>()->SetPosition(player->GetComponent<Transform>()->GetPosition());
		}
	}

	void PlayerScript::SetGainItem(Animator* animator)
	{
		ImageRenderer* gainItemRenderer = mGainItem->GetComponent<ImageRenderer>();
		if (animator != nullptr)
		{
			std::shared_ptr<Texture> texture = animator->GetActiveAnimation()->GetAtlas();
			Animation::Sprite sprite = animator->GetActiveAnimation()->GetSprite();
			gainItemRenderer->SetSprite(texture, sprite.leftTop, sprite.size, sprite.atlasSize);
		}
	}
}