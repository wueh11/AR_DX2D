#include "yaClottyScript.h"
#include "yaMonster.h"

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
#include "Commons.h"

namespace ya
{
	ClottyScript::ClottyScript()
		: MonsterScript()
		, mState(eState::Idle)
		, mTimerMax{ 1.0f, 0.4f, 1.0f, 0.1f }
		, mTimer{ 0.0f }
		, mEffect(nullptr)
		, mMoveDir(Vector3::Zero)
	{
	}
	ClottyScript::~ClottyScript()
	{
	}
	void ClottyScript::Initialize()
	{
		MonsterScript::Initialize();

		Monster* monster = dynamic_cast<Monster*>(GetOwner());
		monster->SetStatus(10.0f, 1.0f, 6.0f, 1.0f);

		mTransform = GetOwner()->GetComponent<Transform>();
		mTransform->SetScale(Vector3(1.2f, 1.2f, 1.0f));

		Collider2D* collider = GetOwner()->GetComponent<Collider2D>();
		collider->SetSize(Vector2(0.4f, 0.3f));
		collider->SetCenter(Vector2(0.0f, -0.2f));

		float speed = monster->GetStatus().speed;
		mRigidbody = GetOwner()->GetComponent<Rigidbody>();
		mRigidbody->SetLimitVelocity(Vector3(speed, speed, 0.0f));

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		std::shared_ptr<Material> material = Resources::Find<Material>(L"clottyMaterial");
		std::shared_ptr<Texture> texture = material->GetTexture();

		SpriteRenderer* mMr = GetOwner()->AddComponent<SpriteRenderer>();
		mMr->SetMesh(mesh);
		mMr->SetMaterial(material);

		mAnimator = GetOwner()->AddComponent<Animator>();
		mAnimator->Create(L"None", texture, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"Idle", texture, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 8, 0.1f, 2, 4);
		mAnimator->Add(L"Idle", texture, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 8, 0.1f, 2, 4);
		mAnimator->Create(L"Attack", texture, Vector2(0.0f, 128.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 3, 0.1f);
		mAnimator->Add(L"Attack", texture, Vector2(0.0f, 128.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Play(L"Idle", true);

		mAnimator->GetCompleteEvent(L"Idle") = std::bind(&ClottyScript::Attack, this);
		mAnimator->GetCompleteEvent(L"Attack") = std::bind(&ClottyScript::Reset, this);

		for (size_t i = 0; i < (UINT)eState::End; i++)
			mTimer[i] = mTimerMax[i];
	}

	void ClottyScript::Update()
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
		case ya::ClottyScript::eState::Idle:
			Idle();
			break;
		case ya::ClottyScript::eState::Move:
			Move();
			break;
		case ya::ClottyScript::eState::Attack:
			Attack();
			break;
		case ya::ClottyScript::eState::Die:
			Die();
			break;
		default:
			break;
		}

		MonsterScript::Update();
	}
	void ClottyScript::FixedUpdate()
	{
		MonsterScript::FixedUpdate();
	}
	void ClottyScript::Render()
	{
		MonsterScript::Render();
	}

	void ClottyScript::OnCollisionEnter(Collider2D* collider)
	{
		MonsterScript::OnCollisionEnter(collider);
	}
	void ClottyScript::OnCollisionStay(Collider2D* collider)
	{
		MonsterScript::OnCollisionStay(collider);
	}
	void ClottyScript::OnCollisionExit(Collider2D* collider)
	{
		MonsterScript::OnCollisionExit(collider);
	}
	void ClottyScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void ClottyScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void ClottyScript::OnTriggerExit(Collider2D* collider)
	{
	}

	void ClottyScript::Idle()
	{
		mTimer[(UINT)eState::Idle] -= Time::DeltaTime();

		if (mTimer[(UINT)eState::Idle] < 0.0f)
		{
			mTimer[(UINT)eState::Idle] = mTimerMax[(UINT)eState::Idle];
			mState = eState::Move;

			mMoveDir = Vector3((float)Random(-1, 1), (float)Random(-1, 1), 0.0f);
		}
	}

	void ClottyScript::Move()
	{
		mTimer[(UINT)eState::Move] -= Time::DeltaTime();

		if (mTimer[(UINT)eState::Move] < 0.0f)
		{
			mTimer[(UINT)eState::Move] = mTimerMax[(UINT)eState::Move];
			mState = eState::Idle;
		}

		Monster* monster = dynamic_cast<Monster*>(GetOwner());
		float speed = monster->GetStatus().speed;
		mRigidbody->AddForce(mMoveDir * 30.0f);
	}

	void ClottyScript::Attack()
	{
		mAnimator->Play(L"Attack", false);

		StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());
		Room* room = scene->GetCurrentRoom();
		Transform* roomTr = room->GetComponent<Transform>();

		Tear* tear1 = object::Instantiate<Tear>(eLayerType::Projectile, room);
		tear1->AddComponent<MonsterTearScript>();
		tear1->InitTear(GetOwner(), Vector3(1.0f, 0.0f, 0.0f));

		Tear* tear2 = object::Instantiate<Tear>(eLayerType::Projectile, room);
		tear2->AddComponent<MonsterTearScript>();
		tear2->InitTear(GetOwner(), Vector3(-1.0f, 0.0f, 0.0f));

		Tear* tear3 = object::Instantiate<Tear>(eLayerType::Projectile, room);
		tear3->AddComponent<MonsterTearScript>();
		tear3->InitTear(GetOwner(), Vector3(0.0f, 1.0f, 0.0f));

		Tear* tear4 = object::Instantiate<Tear>(eLayerType::Projectile, room);
		tear4->AddComponent<MonsterTearScript>();
		tear4->InitTear(GetOwner(), Vector3(0.0f, -1.0f, 0.0f));

	}

	void ClottyScript::Reset()
	{
		mAnimator->Play(L"Idle");
		mState = eState::Idle;
	}

	void ClottyScript::Die()
	{
		GetOwner()->Pause();
		StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());
		if (scene != nullptr)
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
			animator->GetCompleteEvent(L"bloodpoof") = std::bind(&ClottyScript::Destroy, this);
			animator->Play(L"bloodpoof", false);

			Transform* tr = mEffect->GetComponent<Transform>();
			tr->SetPosition(mTransform->GetPosition());
		}

		mState = eState::None;
	}

	void ClottyScript::Destroy()
	{
		Animator* animator = mEffect->AddComponent<Animator>();
		animator->Play(L"none", false);
		mEffect->Death();

		Death();
	}
}