#include "yaMonstroScript.h"
#include "yaMonstro.h"

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
	MonstroScript::MonstroScript()
		: MonsterScript()
		, mState(eState::Idle)
		, mTimerMax{ 1.0f, 1.0f, 1.0f, 1.0f, 0.1f, /**/ 0.3f, 0.3f, 0.4f, 1.0f, 0.6f}
		, mTimer{ 0.0f }
		, mEffect(nullptr)
		, mTargetPos(Vector3::Zero)
	{
	}
	MonstroScript::~MonstroScript()
	{
	}
	void MonstroScript::Initialize()
	{
		MonsterScript::Initialize();

		Monster* monster = dynamic_cast<Monster*>(GetOwner());
		monster->SetStatus(100.0f, 0.3f, 6.0f, 2.0f);

		mTransform = GetOwner()->GetComponent<Transform>();
		mTransform->SetScale(Vector3(1.5f, 2.0f, 1.0f));

		float speed = monster->GetStatus().speed;
		mRigidbody = GetOwner()->GetComponent<Rigidbody>();
		mRigidbody->SetHeightGround(true);
		mRigidbody->SetLimitVelocity(Vector3(speed, speed, 0.0f));
		mRigidbody->SetHeightLimitVelocity(500.0f);

		Collider2D* collider = monster->GetComponent<Collider2D>();
		collider->SetSize(Vector2(0.8f, 0.4f));
		collider->SetCenter(Vector2(0.0f, -0.5f));

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		std::shared_ptr<Material> material = Resources::Find<Material>(L"monstroMaterial");
		std::shared_ptr<Texture> texture = material->GetTexture();

		SpriteRenderer* rd = GetOwner()->AddComponent<SpriteRenderer>();
		rd->SetMesh(mesh);
		rd->SetMaterial(material);

		mAnimator = GetOwner()->AddComponent<Animator>();
		mAnimator->Create(L"None", texture, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"Idle", texture, Vector2(160.0f, 0.0f), Vector2(80.0f, 112.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"Ready", texture, Vector2(80.0f, 0.0f), Vector2(80.0f, 112.0f), Vector2::Zero, 1, 0.1f);

		mAnimator->Create(L"JumpUp", texture, Vector2(80.0f, 112.0f), Vector2(80.0f, 112.0f), Vector2::Zero, 1, 0.3f);

		mAnimator->Create(L"JumpDown", texture, Vector2(320.0f, 0.0f), Vector2(80.0f, 112.0f), Vector2::Zero, 1, 0.5f);
		mAnimator->Create(L"JumpDown2", texture, Vector2(0.0f, 112.0f), Vector2(80.0f, 112.0f), Vector2::Zero, 1, 0.3f);
		mAnimator->Add(L"JumpDown2", texture, Vector2(80.0f, 0.0f), Vector2(80.0f, 112.0f), Vector2::Zero, 2, 0.2f);
		//mAnimator->Add(L"JumpDown", texture, Vector2(320.0f, 112.0f), Vector2(80.0f, 112.0f), Vector2::Zero, 1, 0.1f);

		mAnimator->Create(L"JumpMove", texture, Vector2(80.0f, 112.0f), Vector2(80.0f, 112.0f), Vector2::Zero, 1, 0.2f);
		mAnimator->Add(L"JumpMove", texture, Vector2(160.0f, 112.0f), Vector2(80.0f, 112.0f), Vector2::Zero, 1, 0.7f);
		mAnimator->Add(L"JumpMove", texture, Vector2(320.0f, 0.0f), Vector2(80.0f, 112.0f), Vector2::Zero, 1, 0.2f);
		mAnimator->Add(L"JumpMove", texture, Vector2(0.0f, 112.0f), Vector2(80.0f, 112.0f), Vector2::Zero, 1, 0.2);
		//mAnimator->Add(L"JumpMove", texture, Vector2(240.0f, 112.0f), Vector2(80.0f, 112.0f), Vector2::Zero, 1, 0.1f);

		mAnimator->Create(L"Spit", texture, Vector2(240.0f, 0.0f), Vector2(80.0f, 112.0f), Vector2::Zero, 1, 2.0f);

		mAnimator->Create(L"After", texture, Vector2(240.0f, 112.0f), Vector2(80.0f, 112.0f), Vector2::Zero, 1, 0.1f);

		mAnimator->Play(L"Idle", true);

		for (size_t i = 0; i < (UINT)eState::End; i++)
			mTimer[i] = mTimerMax[i];

		//{ // effect
		//	mEffect = object::Instantiate<GameObject>(eLayerType::Effect, GetOwner());

		//	std::shared_ptr<Material> effectMaterial = Resources::Find<Material>(L"bloodpoofMaterial");
		//	std::shared_ptr<Texture> effectTexture = material->GetTexture();

		//	SpriteRenderer* effectMr = mEffect->AddComponent<SpriteRenderer>();
		//	effectMr->SetMesh(mesh);
		//	effectMr->SetMaterial(material);

		//	Animator* animator = mEffect->AddComponent<Animator>();
		//	animator->Create(L"None", effectTexture, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2::Zero, 1, 0.1f);
		//	animator->Create(L"Normal", effectTexture, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 12, 0.1f, 3, 4);
		//	animator->Play(L"None", false);
		//	animator->GetCompleteEvent(L"Normal") = std::bind(&MonstroScript::Destroy, this);
		//}

		Shadow(Vector3(0.0f, -0.45f, 0.0f), Vector3(0.8f, 0.2f, 0.0f));
	}

	void MonstroScript::Update()
	{
		Monster* monster = dynamic_cast<Monster*>(GetOwner());
		if (monster->GetState() != GameObject::eState::Active)
			return;

		if (monster->GetHp() <= 0.0f)
			mState = eState::Die;

		switch (mState)
		{
		case ya::MonstroScript::eState::None:
			break;
		case ya::MonstroScript::eState::Idle:
			Idle();
			break;
		case ya::MonstroScript::eState::Ready:
			Ready();
			break;
		case ya::MonstroScript::eState::JumpMove:
			JumpMove();
			break;
		case ya::MonstroScript::eState::JumpUp:
			JumpUp();
			break;
		case ya::MonstroScript::eState::JumpDown:
			JumpDown();
			break;
		case ya::MonstroScript::eState::SpitAttack:
			SpitAttack(); 
			break;
		case ya::MonstroScript::eState::SpreadAttack:
			SpreadAttack();
			break;
		case ya::MonstroScript::eState::Die:
			Die();
			break;
		case ya::MonstroScript::eState::After:
			After();
			break;
		default:
			break;
		}
		
		/*headTr->SetRotation(Vector3(0.0f, XM_PI, 0.0f));
		bodyTr->SetRotation(Vector3(0.0f, XM_PI, 0.0f));*/

		MonsterScript::Update();
	}
	void MonstroScript::FixedUpdate()
	{
		MonsterScript::FixedUpdate();
	}
	void MonstroScript::Render()
	{
		MonsterScript::Render();
	}

	void MonstroScript::OnCollisionEnter(Collider2D* collider)
	{
		MonsterScript::OnCollisionEnter(collider);
	}
	void MonstroScript::OnCollisionStay(Collider2D* collider)
	{
		MonsterScript::OnCollisionStay(collider);
	}
	void MonstroScript::OnCollisionExit(Collider2D* collider)
	{
		MonsterScript::OnCollisionExit(collider);
	}
	void MonstroScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void MonstroScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void MonstroScript::OnTriggerExit(Collider2D* collider)
	{
	}

	void MonstroScript::Idle()
	{
		mTimer[(UINT)eState::Idle] -= Time::DeltaTime();

		if (mTimer[(UINT)eState::Idle] < 0.0f)
		{
			mTimer[(UINT)eState::Idle] = mTimerMax[(UINT)eState::Idle];
			mState = eState::Ready;
			mAnimator->Play(L"Ready");
		}
	}

	void MonstroScript::Ready()
	{
		mTimer[(UINT)eState::Ready] -= Time::DeltaTime();

		if (mTimer[(UINT)eState::Ready] < 0.0f)
		{
			mTimer[(UINT)eState::Ready] = mTimerMax[(UINT)eState::Ready];

			Player* player = SceneManager::GetActiveScene()->GetPlayer();
			mTargetPos = player->GetRelativePosition();

			Vector3 pos = mTransform->GetPosition();
				
			float dist = (mTargetPos - pos).Length();

			//int ran = Random(0, 2);
			int ran = 2;
			if (ran == 0)
			{
				mState = eState::JumpMove;
				mAnimator->Play(L"JumpMove", false);
				mRigidbody->SetHeightGround(false);
				mRigidbody->AddHeightForce(1000.0f);
			}
			else if (ran == 1)
			{
				mState = eState::SpitAttack;
				mAnimator->Play(L"Spit", false);
			}
			else if (ran == 2)
			{
				mState = eState::JumpUp;
				mAnimator->Play(L"JumpUp", false);
				mRigidbody->SetHeightGround(false);
			}
		}
	}

	void MonstroScript::JumpMove()
	{
		mTimer[(UINT)eState::JumpMove] -= Time::DeltaTime();
		if (mTimer[(UINT)eState::JumpMove] < 0.0f)
		{
			mTimer[(UINT)eState::JumpMove] = mTimerMax[(UINT)eState::JumpMove];
			mState = eState::After;
			mAnimator->Play(L"After", false);
		}
		else
		{
			Vector3 dir = mTargetPos - mTransform->GetPosition() + Vector3(0.0f, 0.4f, 0.0f);
			dir.Normalize();

			Monster* monster = dynamic_cast<Monster*>(GetOwner());
			mRigidbody->AddForce(dir * monster->GetStatus().speed * 10.0f);

			if (mTimer[(UINT)eState::JumpMove] > 0.9f)
			{
				mRigidbody->AddHeightForce(10.0f);
			}
		}
	}

	void MonstroScript::JumpUp()
	{
		mTimer[(UINT)eState::JumpUp] -= Time::DeltaTime();
		if (mTimer[(UINT)eState::JumpUp] < 0.0f)
		{
			mTimer[(UINT)eState::JumpUp] = mTimerMax[(UINT)eState::JumpUp];
			mState = eState::JumpDown;
			mAnimator->Play(L"JumpDown", false);

			Player* player = SceneManager::GetActiveScene()->GetPlayer();
			mTargetPos = player->GetRelativePosition();
		}
		else
		{
			mRigidbody->AddHeightForce(200.0f);
		}
	}

	void MonstroScript::JumpDown()
	{
		mTimer[(UINT)eState::JumpDown] -= Time::DeltaTime();
		if (mTimer[(UINT)eState::JumpDown] < 0.0f)
		{
			mTimer[(UINT)eState::JumpDown] = mTimerMax[(UINT)eState::JumpDown];
			if (mTransform->GetHeight() <= 0.0f)
			{
				mState = eState::SpreadAttack;
				mAnimator->Play(L"JumpDown2", false);
				mRigidbody->SetHeightGround(true);
			}
		}
		else if (mTimer[(UINT)eState::JumpDown] > 0.2f)
		{
			mTransform->SetPosition(mTargetPos - Vector3(0.0f, -0.4f, 0.0f));
			mTransform->SetHeight(8.0f);
			mRigidbody->SetHeightVelocity(0.0f);
		}
	}

	void MonstroScript::SpitAttack()
	{
		mTimer[(UINT)eState::SpitAttack] -= Time::DeltaTime();
		if (mTimer[(UINT)eState::SpitAttack] < 0.0f)
		{
			mTimer[(UINT)eState::SpitAttack] = mTimerMax[(UINT)eState::SpitAttack];
			mState = eState::After;
			mAnimator->Play(L"After", false);
		}
		else
		{
			if(Random(0, 15) < 1)
			{
				StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());
				for (size_t i = 0; i < 2; i++)
				{
					Tear* tear = object::Instantiate<Tear>(eLayerType::Projectile, scene->GetCurrentRoom());
					tear->Parabola(true);
					tear->InitTear(GetOwner(), Vector3((float)(Random(10, 5))/ 10.0f, (float)(Random(-4,4))/10.0f, 0.0f));
					Rigidbody* rigidbody = tear->GetComponent<Rigidbody>();
					rigidbody->SetHeightGravity(-4.0f);
					rigidbody->AddForce(Vector3((float)Random(-100, 100), 0.0f, 0.0f));
					rigidbody->AddHeightForce((float)Random(5, 400));
					tear->AddComponent<MonsterTearScript>();
				}
			}
		}
	}

	void MonstroScript::SpreadAttack()
	{
		mTimer[(UINT)eState::SpreadAttack] -= Time::DeltaTime();
		if (mTimer[(UINT)eState::SpreadAttack] < 0.0f)
		{
			mTimer[(UINT)eState::SpreadAttack] = mTimerMax[(UINT)eState::SpreadAttack];
			mState = eState::After;
			mAnimator->Play(L"After", false);
		}
		else
		{
			if (Random(0, 20) < 1)
			{
				StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());
				for (size_t i = 0; i < 2; i++)
				{
					Tear* tear = object::Instantiate<Tear>(eLayerType::Projectile, scene->GetCurrentRoom());
					tear->Parabola(true);
					tear->InitTear(GetOwner(), Vector3((float)(Random(-10, 10)) / 10.0f, (float)(Random(-10, 10)) / 10.0f, 0.0f));
					Rigidbody* rigidbody = tear->GetComponent<Rigidbody>();
					rigidbody->SetHeightGravity(-4.0f);
					rigidbody->AddForce(Vector3((float)Random(-100, 100), 0.0f, 0.0f));
					rigidbody->AddHeightForce((float)Random(5, 400));
					tear->AddComponent<MonsterTearScript>();
				}
			}
		}
	}

	void MonstroScript::Die()
	{
		//Animator* effectmEffect = mEffect->GetComponent<Animator>();
		//effectmEffect->Play(L"Normal",false);
		mAnimator->Play(L"After", false);
	}

	void MonstroScript::Destroy()
	{
		//mEffect->Death();
		//Death();
	}

	void MonstroScript::After()
	{
		mTimer[(UINT)eState::After] -= Time::DeltaTime();
		if (mTimer[(UINT)eState::After] < 0.0f)
		{
			mTimer[(UINT)eState::After] = mTimerMax[(UINT)eState::After];
			mState = eState::Idle;
			mAnimator->Play(L"Idle");
		}
	}
}