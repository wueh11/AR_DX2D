#include "yaRageCreepScript.h"
#include "yaRageCreep.h"

#include "yaObject.h"
#include "yaGameObject.h"

#include "yaResources.h"

#include "yaTransform.h"
#include "yaRigidbody.h"

#include "yaSpriteRenderer.h"
#include "yaTime.h"

#include "yaSceneManager.h"
#include "yaStageScene.h"

#include "yaPlayer.h"

#include "yaTear.h"
#include "yaMonsterTearScript.h"

namespace ya
{
	RageCreepScript::RageCreepScript()
		: MonsterScript()
		, mState(eState::Attack)
		, mTimerMax{ 1.0f, 1.0f, 0.35f, 0.1f }
		, mTimer{ 0.0f }
		, mEffect(nullptr)
	{
	}
	RageCreepScript::~RageCreepScript()
	{
	}
	void RageCreepScript::Initialize()
	{
		MonsterScript::Initialize();

		Monster* monster = dynamic_cast<Monster*>(GetOwner());
		monster->SetStatus(10.0f, 1.0f, 6.0f, 1.0f);

		mTransform = GetOwner()->GetComponent<Transform>();
		mTransform->SetScale(Vector3(0.66f, 0.66f, 1.0f));

		float speed = monster->GetStatus().speed;
		mRigidbody = GetOwner()->GetComponent<Rigidbody>();
		mRigidbody->SetLimitVelocity(Vector3(speed, speed, 0.0f));

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		std::shared_ptr<Material> material = Resources::Find<Material>(L"ragecreepMaterial");
		std::shared_ptr<Texture> texture = material->GetTexture();

		SpriteRenderer* mMr = GetOwner()->AddComponent<SpriteRenderer>();
		mMr->SetMesh(mesh);
		mMr->SetMaterial(material);

		mAnimator = GetOwner()->AddComponent<Animator>();
		mAnimator->Create(L"None", texture, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"Idle", texture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"Move", texture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		mAnimator->Create(L"Attack", texture, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		mAnimator->Play(L"Idle", true);

		for (size_t i = 0; i < (UINT)eState::End; i++)
			mTimer[i] = mTimerMax[i];
	}

	void RageCreepScript::Update()
	{
		Monster* monster = dynamic_cast<Monster*>(GetOwner());
		if (monster->GetState() != GameObject::eState::Active)
			return;

		if (!mbDeath && monster->GetHp() <= 0.0f)
		{
			mbDeath = true;
			mState = eState::Die;
		}

		switch (mState)
		{
		case ya::RageCreepScript::eState::Idle:
			Idle();
			break;
		case ya::RageCreepScript::eState::Move:
			Move();
			break;
		case ya::RageCreepScript::eState::Attack:
			Attack();
			break;
		case ya::RageCreepScript::eState::Die:
			Die();
			break;
		default:
			break;
		}

		MonsterScript::Update();
	}
	void RageCreepScript::FixedUpdate()
	{
		MonsterScript::FixedUpdate();
	}
	void RageCreepScript::Render()
	{
		MonsterScript::Render();
	}

	void RageCreepScript::OnCollisionEnter(Collider2D* collider)
	{
		MonsterScript::OnCollisionEnter(collider);
	}
	void RageCreepScript::OnCollisionStay(Collider2D* collider)
	{
		MonsterScript::OnCollisionStay(collider);
	}
	void RageCreepScript::OnCollisionExit(Collider2D* collider)
	{
		MonsterScript::OnCollisionExit(collider);
	}
	void RageCreepScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void RageCreepScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void RageCreepScript::OnTriggerExit(Collider2D* collider)
	{
	}

	void RageCreepScript::Idle()
	{
		mTimer[(UINT)eState::Idle] -= Time::DeltaTime();

		if (mTimer[(UINT)eState::Idle] < 0.0f)
		{
			mTimer[(UINT)eState::Idle] = mTimerMax[(UINT)eState::Idle];
			mState = eState::Move;
			mAnimator->Play(L"Move");
		}
	}

	void RageCreepScript::Move()
	{
		Player* player = SceneManager::GetActiveScene()->GetPlayer();
		Vector3 playerPos = player->GetRelativePosition();
		Collider2D* playerCollider = player->GetComponent<Collider2D>();

		RageCreep* rageCreep = dynamic_cast<RageCreep*>(GetOwner());
		eDirection dir = rageCreep->GetDirection();

		Vector3 rageCreepPos = rageCreep->GetComponent<Transform>()->GetPosition();

		float speed = 20.0f;
		if(dir == eDirection::UP || dir == eDirection::DOWN)
		{
			if(rageCreepPos.x > playerPos.x)
				mRigidbody->AddForce(Vector3(speed, 0.0f, 0.0f));
			else
				mRigidbody->AddForce(Vector3(-speed, 0.0f, 0.0f));

			if (rageCreepPos.x > playerPos.x - playerCollider->GetSize().x && rageCreepPos.x < playerPos.x + playerCollider->GetSize().x)
			{
				mState = eState::Attack;
				mAnimator->Play(L"Attack");
			}
		}
		else if (dir == eDirection::LEFT || dir == eDirection::RIGHT)
		{
			if (rageCreepPos.y > playerPos.y)
				mRigidbody->AddForce(Vector3(0.0f, -speed, 0.0f));
			else
				mRigidbody->AddForce(Vector3(0.0f, speed, 0.0f));

			if (rageCreepPos.y > playerPos.y - playerCollider->GetSize().y / 2.0f && rageCreepPos.y < playerPos.y - 0.2f + playerCollider->GetSize().y / 2.0f)
			{
				mState = eState::Attack;
				mAnimator->Play(L"Attack");
			}
		}
	}

	void RageCreepScript::Attack()
	{
		Vector3 tearDir = Vector3::Zero;

		RageCreep* rageCreep = dynamic_cast<RageCreep*>(GetOwner());
		eDirection dir = rageCreep->GetDirection();
		if (dir == eDirection::UP)
			tearDir.y = 1.0f;
		else if(dir == eDirection::DOWN)
			tearDir.y = -1.0f;
		else if (dir == eDirection::LEFT)
			tearDir.x = 1.0f;
		else if  (dir == eDirection::RIGHT)
			tearDir.x = -1.0f;

		mTimer[(UINT)eState::Tear] -= Time::DeltaTime();
		mTimer[(UINT)eState::Attack] -= Time::DeltaTime();

		if (mTimer[(UINT)eState::Tear] < 0.0f)
		{
			StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());
			Tear* tear = object::Instantiate<Tear>(eLayerType::Projectile, scene->GetCurrentRoom());
			tear->AddComponent<MonsterTearScript>();
			tear->InitTear(GetOwner(), tearDir);
			mTimer[(UINT)eState::Tear] = mTimerMax[(UINT)eState::Tear];
		}

		if (mTimer[(UINT)eState::Attack] < 0.0f)
		{
			mTimer[(UINT)eState::Tear] = mTimerMax[(UINT)eState::Tear];
			mTimer[(UINT)eState::Attack] = mTimerMax[(UINT)eState::Attack];
			mState = eState::Idle;
			mAnimator->Play(L"Idle");
		}
	}

	void RageCreepScript::Die()
	{
		GetOwner()->Pause();
		StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());
		if(scene != nullptr)
		{
			mEffect = object::Instantiate<GameObject>(eLayerType::Effect, scene->GetCurrentRoom());
			mEffect->SetName(L"bloodpoof");

			SpriteRenderer* rd = mEffect->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			rd->SetMesh(mesh);
			std::shared_ptr<Material> material = Resources::Find<Material>(L"bloodpoofMaterial");
			rd->SetMaterial(material);
			std::shared_ptr<Texture> texture = material->GetTexture();

			Animator* animator = mEffect->AddComponent<Animator>();
			animator->Create(L"none", texture, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"bloodpoof", texture, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 12, 0.05f, 3, 4);
			animator->GetCompleteEvent(L"bloodpoof") = std::bind(&RageCreepScript::Destroy, this);
			animator->Play(L"bloodpoof", false);

			Transform* tr = mEffect->GetComponent<Transform>();
			tr->SetPosition(mTransform->GetPosition());
		}

		mState = eState::None;
	}

	void RageCreepScript::Destroy()
	{
		Animator* animator = mEffect->AddComponent<Animator>();
		animator->Play(L"none", false);
		mEffect->Death();

		Death();
	}

	void RageCreepScript::SetDirection(isaac::eDirection dir)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Collider2D* collider = GetOwner()->GetComponent<Collider2D>();

		float dist = 0.3f;

		if (dir == eDirection::UP)
		{
			tr->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
			tr->SetPosition(tr->GetPosition() + Vector3(0.0f, -dist, 0.0f));
		}
		else if (dir == eDirection::DOWN)
		{
			tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2 * 2));
			tr->SetPosition(tr->GetPosition() + Vector3(0.0f, dist, 0.0f));
		}
		else if (dir == eDirection::LEFT)
		{
			tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
			tr->SetPosition(tr->GetPosition() + Vector3(dist, 0.0f, 0.0f));
		}
		else if (dir == eDirection::RIGHT)
		{
			tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2 * 3));
			tr->SetPosition(tr->GetPosition() + Vector3(-dist, 0.0f, 0.0f));
		}
	}
}