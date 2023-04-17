#include "yaPlayerScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaAnimator.h"
#include "yaRigidbody.h"
#include "yaResources.h"
#include "yaSpriteRenderer.h"
#include "yaObject.h"

#include "yaItemManager.h"
#include "yaTear.h"
#include "yaDropBomb.h"
#include "yaPickup.h"
#include "yaPlayer.h"

#include "yaItem.h"
#include "yaPill.h"
#include "yaCard.h"

namespace ya
{
	PlayerScript::PlayerScript()
		: Script()
		, mTransform(nullptr)
		, mRigidbody(nullptr)
		, mHead(nullptr)
		, mBody(nullptr)
		, invincibleTime(0.0f)
		, mbInvincible(false)
		, mbDie(false)
		, mbKeyInput(false)
	{
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
		mRigidbody = GetOwner()->AddComponent<Rigidbody>();

		Player* player = dynamic_cast<Player*>(GetOwner());
		Player::Status status = player->GetStatus();

		mRigidbody->SetLimitVelocity(Vector3(1.0f + status.speed, 1.0f + status.speed, 0.0f));

		SpriteRenderer* rd = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		rd->SetMesh(mesh);
		std::shared_ptr<Material> material = Resources::Find<Material>(L"isaacMaterial");
		rd->SetMaterial(material);
		std::shared_ptr<Texture> texture = material->GetTexture();

		Animator* animator = GetOwner()->AddComponent<Animator>();
		animator->Create(L"None", texture, Vector2(0.0f, 480.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"Hurt", texture, Vector2(128.0f, 192.0f), Vector2(64.0f, 64.0f), Vector2(0.0f, -0.025f), 1, 0.1f);
		animator->Create(L"Die", texture, Vector2(0.0f, 128.0f), Vector2(64.0f, 64.0f), Vector2(0.0f, -0.025f), 1, 0.2f);
		animator->Add(L"Die", texture, Vector2(128.0f, 192.0f), Vector2(64.0f, 64.0f), Vector2(0.0f, -0.025f), 1, 0.2f);
		animator->Add(L"Die", texture, Vector2(192.0f, 128.0f), Vector2(64.0f, 64.0f), Vector2(0.0f, -0.025f), 1, 0.3f);
		animator->Play(L"None", true);

		//animator->GetCompleteEvent(L"hurt") = std::bind(&PlayerScript::Idle, this);

		{ // body
			mBody = object::Instantiate<GameObject>(eLayerType::Player, mTransform);

			SpriteRenderer* mMr = mBody->AddComponent<SpriteRenderer>();
			mMr->SetMesh(mesh);
			mMr->SetMaterial(material);

			Animator* bodyAnimator = mBody->AddComponent<Animator>();
			bodyAnimator->Create(L"None", texture, Vector2(0.0f, 480.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			bodyAnimator->Create(L"FrontIdle", texture, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			bodyAnimator->Create(L"FrontWalk", texture, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 8, 0.1f);
			bodyAnimator->Create(L"SideIdle", texture, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			bodyAnimator->Create(L"SideWalk", texture, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 8, 0.1f);
			bodyAnimator->Play(L"FrontIdle", true);
		}

		{ // head
			mHead = object::Instantiate<GameObject>(eLayerType::Player, mTransform);

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
			headAnimator->Play(L"FrontIdle", true);
		}

		Transform* headTr = mHead->GetComponent<Transform>();
		headTr->SetPosition(Vector3(0.0f, 0.15f, 0.0f));
		Transform* bodyTr = mBody->GetComponent<Transform>();
		bodyTr->SetPosition(Vector3(0.0f, -0.15f, 0.0f));
	}

	void PlayerScript::Update()
	{
		Player* player = dynamic_cast<Player*>(GetOwner());
		
		Player::Info info = player->GetInfo();
		if (info.heart < 0)
			player->SetHeart(0);

		Vector3 pos = mTransform->GetPosition();

		if (mbInvincible)
		{
			if (invincibleTime > 0.0f)
			{
				invincibleTime -= Time::DeltaTime();
			}
			else
			{
				mbInvincible = false;
				Idle();
			}
		}

		Move();
		Attack();

		// ��ź
		if (Input::GetKeyDown(eKeyCode::E))
		{
			//if (player->GetPickup().bomb > 0)
			{
				DropBomb* bomb = new DropBomb(pos);
				Scene* scene = SceneManager::GetActiveScene();
				Layer& layer = scene->GetLayer(eLayerType::Item);
				layer.AddGameObject(bomb);

				//player->AddBomb(-1);
			}
		}

		// ��Ƽ�� ������ ���
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
		}

		// �Ⱦ� ������ ��� 
		if (Input::GetKeyDown(eKeyCode::Q))
		{
			UseConsumable();
		}

		// ��ű�, �Ҹ�ǰ ���
		if (Input::GetKeyDown(eKeyCode::LCTRL))
		{
			//3�ʰ� ������ ������ drop
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
		if (Input::GetKeyDown(eKeyCode::N_5))
		{
			UseConsumable();
		}
	}

	void PlayerScript::FixedUpdate()
	{
	}
	void PlayerScript::Render()
	{
	}

	void PlayerScript::OnCollisionEnter(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();

		Item* item = dynamic_cast<Item*>(other);
		if (item != nullptr)
		{
		}

		Pill* pill = dynamic_cast<Pill*>(other);
		if (pill != nullptr)
		{
			//pill->GetItemType
		}
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
		Animator* animator = GetOwner()->GetComponent<Animator>();
		Animator* headAnimator = mHead->GetComponent<Animator>();
		Animator* bodyAnimator = mBody->GetComponent<Animator>();

		animator->Play(L"None", false);
		headAnimator->Play(L"FrontIdle", false);
		bodyAnimator->Play(L"FrontIdle", false);
		mTransform->SetScale(Vector3(0.66f, 0.66f, 1.0f));
	}

	void PlayerScript::Move()
	{
		Player* player = dynamic_cast<Player*>(GetOwner());
		Player::Status status = player->GetStatus();
		float speed = 10.0f * status.speed;

		/// �̵�
		if (Input::GetKey(eKeyCode::W))
			mRigidbody->AddForce(Vector3(0.0f, speed, 0.0f));
		else if (Input::GetKey(eKeyCode::S))
			mRigidbody->AddForce(Vector3(0.0f, -speed, 0.0f));
		
		if (Input::GetKey(eKeyCode::A))
			mRigidbody->AddForce(Vector3(-speed, 0.0f, 0.0f));
		else if (Input::GetKey(eKeyCode::D))
			mRigidbody->AddForce(Vector3(speed, 0.0f, 0.0f));


		Animator* headAnimator = mHead->GetComponent<Animator>();
		Animator* bodyAnimator = mBody->GetComponent<Animator>();

		if (!mbInvincible)
		{
			// �ִϸ��̼�
			if (Input::GetKeyDown(eKeyCode::W))
			{
				headAnimator->Play(L"BackIdle", true);
				bodyAnimator->Play(L"FrontWalk", true);
			}
			else if (Input::GetKeyDown(eKeyCode::S))
			{
				headAnimator->Play(L"FrontIdle", true);
				bodyAnimator->Play(L"FrontWalk", true);
			}
			else if (Input::GetKeyDown(eKeyCode::A))
			{
				headAnimator->Play(L"SideIdle", true);
				bodyAnimator->Play(L"SideWalk", true);
			}
			else if (Input::GetKeyDown(eKeyCode::D))
			{
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
	}

	void PlayerScript::Attack()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		Animator* headAnimator = mHead->GetComponent<Animator>();
		Animator* bodyAnimator = mBody->GetComponent<Animator>();

		// ���� �߻�
		if (Input::GetKeyDown(eKeyCode::UP))
		{
			headAnimator->Play(L"BackAttack", true);
			Tears(Vector3(0.0f, 1.0f, 0.0f));
		}
		else if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			headAnimator->Play(L"FrontAttack", true);
			Tears(Vector3(0.0f, -1.0f, 0.0f));
		}
		else if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			headAnimator->Play(L"SideAttack", true);
			Tears(Vector3(-1.0f, 0.0f, 0.0f));
		}
		else if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			headAnimator->Play(L"SideAttack", true);
			Tears(Vector3(1.0f, 0.0f, 0.0f));
		}

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

		/*if (Input::GetKeyNone(eKeyCode::UP) && Input::GetKeyNone(eKeyCode::DOWN) && Input::GetKeyNone(eKeyCode::LEFT) && Input::GetKeyNone(eKeyCode::RIGHT))
		{
			headAnimator->Play(L"FrontIdle", true);
		}*/
	}

	void PlayerScript::Tears(Vector3 direction)
	{
		Tear* tear = new Tear(GetOwner(), direction);
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(eLayerType::Projectile);
		layer.AddGameObject(tear);
	}

	void PlayerScript::Hurt()
	{
		if (mbInvincible)
			return;

		Animator* animator = GetOwner()->GetComponent<Animator>();
		Animator* headAnimator = mHead->GetComponent<Animator>();
		Animator* bodyAnimator = mBody->GetComponent<Animator>();

		headAnimator->Play(L"None", false);
		bodyAnimator->Play(L"None", false);
		animator->Play(L"Hurt", false);

		mTransform->SetScale(Vector3(1.32f, 1.32f, 1.0f));

		Player* player = dynamic_cast<Player*>(GetOwner());
		Player::Info info = player->GetInfo();
		if (info.soulHeart > 0)
			player->AddSoulHeart(-1);
		else 
			player->AddHeart(-1);

		Invincible();
	}

	void PlayerScript::Die()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		Animator* headAnimator = mHead->GetComponent<Animator>();
		Animator* bodyAnimator = mBody->GetComponent<Animator>();

		headAnimator->Play(L"None", false);
		bodyAnimator->Play(L"None", false);
		animator->Play(L"Die", false);

		mTransform->SetScale(Vector3(1.32f, 1.32f, 1.0f));
	}

	/// <summary>
	/// ���� �ð�
	/// </summary>
	void PlayerScript::Invincible()
	{
		invincibleTime = 1.2f;
		mbInvincible = true;
	}

	void PlayerScript::gainActiveItem(eActiveItem active)
	{
		Player* player = dynamic_cast<Player*>(GetOwner());
		Player::Items item = player->GetItem();

		if (item.ActiveItem != eActiveItem::None)
		{
			// TODO: ������ ��ü
		}

		player->SetActiveItem(active);
	}

	void PlayerScript::gainConsumable(eItemType type, UINT num)
	{
		Player* player = dynamic_cast<Player*>(GetOwner());
		Player::Items item = player->GetItem();

		if (type == eItemType::Pill)
		{
			if (item.pill != ePills::None)
			{
				// TODO: ������ ��ü
			}
			else if (item.card != eCards::None)
			{
				// TODO: ������ ��ü
				player->SetCard(eCards::None);
			}

			player->SetPill((ePills)num);
			
		}
		else if (type == eItemType::Card)
		{
			if (item.card != eCards::None)
			{
				// TODO: ������ ��ü
			}
			else if (item.pill != ePills::None)
			{
				// TODO: ������ ��ü
				player->SetPill(ePills::None);
			}

			player->SetCard((eCards)num);
		}
	}

	void PlayerScript::UseActiveItem()
	{
		Player* player = dynamic_cast<Player*>(GetOwner());
		Player::Items item = player->GetItem();
		ItemManager::GetEvent(eItemType::ActiveItem)[(UINT)item.pill]->mEvents();
	}

	void PlayerScript::UseConsumable()
	{
		Player* player = dynamic_cast<Player*>(GetOwner());
		Player::Items item = player->GetItem();
		
		if (item.pill != ePills::None)
		{
			ItemManager::GetEvent(eItemType::Pill)[(UINT)item.pill]->mEvents();
			item.pill = ePills::None;
		}
		else if (item.card != eCards::None)
		{
			ItemManager::GetEvent(eItemType::Card)[(UINT)item.card]->mEvents();
			item.card = eCards::None;
		}
	}

	void PlayerScript::ThrowItem()
	{
		Player* player = dynamic_cast<Player*>(GetOwner());
		Player::Items item = player->GetItem();

		if (item.trinkets != eTrinkets::None)
		{
			//TODO: trinket ������ ����
			
			player->SetTrinket(eTrinkets::None);
		}

		if (item.pill != ePills::None)
		{
			//TODO: consumable ������ ����
			player->SetPill(ePills::None);
		}

		if (item.card != eCards::None)
		{
			player->SetCard(eCards::None);
		}
	}
}