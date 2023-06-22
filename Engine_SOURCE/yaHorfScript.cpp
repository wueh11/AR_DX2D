#include "yaHorfScript.h"
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
	HorfScript::HorfScript()
		: MonsterScript()
		, mState(eState::Idle)
		, mTimerMax{ 1.0f, 1.0f, 0.35f, 0.1f }
		, mTimer{ 0.0f }
		, mEffect(nullptr)
	{
	}
	HorfScript::~HorfScript()
	{
	}
	void HorfScript::Initialize()
	{
		MonsterScript::Initialize();

		Monster* monster = dynamic_cast<Monster*>(GetOwner());
		monster->SetStatus(10.0f, 3.0f, 5.0f, 1.0f);

		mTransform = GetOwner()->GetComponent<Transform>();
		mTransform->SetScale(Vector3(0.66f, 0.66f, 1.0f));

		float speed = monster->GetStatus().speed;
		mRigidbody = GetOwner()->GetComponent<Rigidbody>();
		mRigidbody->SetLimitVelocity(Vector3(speed, speed, 0.0f));

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		std::shared_ptr<Material> material = Resources::Find<Material>(L"horfMaterial");
		std::shared_ptr<Texture> texture = material->GetTexture();

		SpriteRenderer* mMr = GetOwner()->AddComponent<SpriteRenderer>();
		mMr->SetMesh(mesh);
		mMr->SetMaterial(material);

		mAnimator = GetOwner()->AddComponent<Animator>();
		mAnimator->Create(L"None", texture, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"Idle", texture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"Attack", texture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 3, 0.1f, 2, 2);
		mAnimator->Add(L"Attack", texture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Play(L"Idle", false);

		for (size_t i = 0; i < (UINT)eState::End; i++)
			mTimer[i] = mTimerMax[i];
	}

	void HorfScript::Update()
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
		case ya::HorfScript::eState::Idle:
			Idle();
			break;
		case ya::HorfScript::eState::Attack:
			Attack();
			break;
		case ya::HorfScript::eState::Die:
			Die();
			break;
		default:
			break;
		}

		MonsterScript::Update();
	}
	void HorfScript::FixedUpdate()
	{
		MonsterScript::FixedUpdate();
	}
	void HorfScript::Render()
	{
		MonsterScript::Render();
	}

	void HorfScript::OnCollisionEnter(Collider2D* collider)
	{
		MonsterScript::OnCollisionEnter(collider);
	}
	void HorfScript::OnCollisionStay(Collider2D* collider)
	{
		MonsterScript::OnCollisionStay(collider);
	}
	void HorfScript::OnCollisionExit(Collider2D* collider)
	{
		MonsterScript::OnCollisionExit(collider);
	}
	void HorfScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void HorfScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void HorfScript::OnTriggerExit(Collider2D* collider)
	{
	}

	void HorfScript::Idle()
	{
		mTimer[(UINT)eState::Idle] -= Time::DeltaTime();

		if (mTimer[(UINT)eState::Idle] < 0.0f)
		{
			mTimer[(UINT)eState::Idle] = mTimerMax[(UINT)eState::Idle];

			Player* player = SceneManager::GetActiveScene()->GetPlayer();
			mTargetPos = player->GetRelativePosition();

			Monster* horf = dynamic_cast<Monster*>(GetOwner());
			Vector3 horfPos = horf->GetComponent<Transform>()->GetPosition();

			Vector3 dir = mTargetPos - mTransform->GetPosition();

			float  leng = dir.Length();
			if (leng < 2.0f)
			{
				mState = eState::Attack;
				mAnimator->Play(L"Attack", false);

				Vector3 dir = mTargetPos - mTransform->GetPosition();
				dir.Normalize();

				StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());
				Tear* tear = object::Instantiate<Tear>(eLayerType::Projectile, scene->GetCurrentRoom()->GetComponent<Transform>());
				tear->InitTear(GetOwner(), dir);
				tear->AddComponent<MonsterTearScript>();
			}
		}

		Vector3 pos = mTransform->GetPosition();
		mTransform->SetPosition(pos + Vector3(SinByTime(0.05f, 0.002f), 0.0f, 0.0f));
	}

	void HorfScript::Attack()
	{
		mTimer[(UINT)eState::Idle] -= Time::DeltaTime();

		if (mTimer[(UINT)eState::Idle] < 0.0f)
		{
			mTimer[(UINT)eState::Idle] = mTimerMax[(UINT)eState::Idle];
			mState = eState::Idle;
			mAnimator->Play(L"Idle");
		}
	}

	void HorfScript::Die()
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
			animator->GetCompleteEvent(L"bloodpoof") = std::bind(&HorfScript::Destroy, this);
			animator->Play(L"bloodpoof", false);

			Transform* tr = mEffect->GetComponent<Transform>();
			tr->SetPosition(mTransform->GetPosition());
		}

		mState = eState::None;
	}

	void HorfScript::Destroy()
	{
		Animator* animator = mEffect->AddComponent<Animator>();
		animator->Play(L"none", false);
		mEffect->Death();

		Death();
	}
}