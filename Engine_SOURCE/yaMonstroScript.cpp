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
#include "yaEffectScript.h"

#include "yaUIScript.h"

#include "Commons.h"

namespace ya
{
	MonstroScript::MonstroScript()
		: MonsterScript()
		, mState(eState::Idle)
		, mTimerMax{ 1.0f, 1.0f, 1.0f, 1.0f, 0.1f, /**/ 0.3f, 0.3f, 0.4f, 1.0f, 2.0f}
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
		monster->SetStatus(10.0f, 0.1f, 6.0f, 2.0f);

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

		mAnimator->Create(L"JumpMove", texture, Vector2(80.0f, 112.0f), Vector2(80.0f, 112.0f), Vector2::Zero, 1, 0.2f);
		mAnimator->Add(L"JumpMove", texture, Vector2(160.0f, 112.0f), Vector2(80.0f, 112.0f), Vector2::Zero, 1, 0.7f);
		mAnimator->Add(L"JumpMove", texture, Vector2(320.0f, 0.0f), Vector2(80.0f, 112.0f), Vector2::Zero, 1, 0.2f);
		mAnimator->Add(L"JumpMove", texture, Vector2(0.0f, 112.0f), Vector2(80.0f, 112.0f), Vector2::Zero, 1, 0.2);

		mAnimator->Create(L"Spit", texture, Vector2(240.0f, 0.0f), Vector2(80.0f, 112.0f), Vector2::Zero, 1, 2.0f);

		mAnimator->Create(L"After", texture, Vector2(240.0f, 112.0f), Vector2(80.0f, 112.0f), Vector2::Zero, 1, 0.1f);

		mAnimator->Play(L"Idle", true);

		for (size_t i = 0; i < (UINT)eState::End; i++)
			mTimer[i] = mTimerMax[i];

		Shadow(Vector3(0.0f, -0.45f, 0.0f), Vector3(0.8f, 0.2f, 0.0f));
	}

	void MonstroScript::Update()
	{
		Monster* monster = dynamic_cast<Monster*>(GetOwner());
		if (monster->GetState() != GameObject::eState::Active)
			return;

		if (monster->GetHp() <= 0.0f && mState != eState::Die && mState != eState::None)
		{
			mState = eState::Die; 
			mAnimator->Play(L"After", false);
			Collider2D* collider = GetOwner()->GetComponent<Collider2D>();
			collider->Disable(true);
			{
				StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());
				Room* room = scene->GetCurrentRoom();
				if (room != nullptr)
				{
					GameObject* bloodpoof = object::Instantiate<GameObject>(eLayerType::Player, room);
					bloodpoof->SetName(L"bloodpoof");

					SpriteRenderer* rd = bloodpoof->AddComponent<SpriteRenderer>();
					std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
					rd->SetMesh(mesh);
					std::shared_ptr<Material> material = Resources::Find<Material>(L"bloodpoofMaterial");
					rd->SetMaterial(material);
					std::shared_ptr<Texture> texture = material->GetTexture();

					Transform* tr = bloodpoof->GetComponent<Transform>();
					tr->SetPosition(mTransform->GetPosition() + Vector3(0.0f, -0.4f, -0.01f));
					tr->SetScale(Vector3(1.0f, 1.0f, 0.0f));

					Animator* animator = bloodpoof->AddComponent<Animator>();
					animator->Create(L"poof", texture, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 12, 0.1f, 3, 4);
					animator->Play(L"poof", false);

					EffectScript* effectScript = bloodpoof->AddComponent<EffectScript>();
					effectScript->SetAutoDestroy(L"poof");
				}
			}
		}

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
				
			int ran = Random(0, 2);
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

			if (mTargetPos.x > pos.x)
				mTransform->SetRotation(Vector3(0.0f, XM_PI, 0.0f));
			else
				mTransform->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
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

			Vector3 scale = mTransform->GetScale();
			float val = Time::DeltaTime() * 10.0f;

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
			if (mTransform->GetHeight() <= 0.0f)
			{
				mTimer[(UINT)eState::JumpDown] = mTimerMax[(UINT)eState::JumpDown];

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
			if(Random(0, 10) < 1)
			{
				StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());

				Vector3 dir = mTargetPos - mTransform->GetPosition();
				dir.Normalize();

				if (mTimer[(UINT)eState::JumpMove] > 0.9f)
				{
					mRigidbody->AddHeightForce(10.0f);
				}

				Tear* tear = object::Instantiate<Tear>(eLayerType::Projectile, scene->GetCurrentRoom());
				tear->Parabola(true);
				tear->InitTear(GetOwner(), dir + Vector3((float)(Random(-4, 4)) / 10.0f, (float)(Random(-4, 4)) / 10.0f, 0.0f));
				Rigidbody* rigidbody = tear->GetComponent<Rigidbody>();
				rigidbody->AddForce(dir * Vector3((float)Random(600, 2000), 1000.0f, 0.0f));
				rigidbody->AddHeightForce((float)Random(5, 600));
				tear->AddComponent<MonsterTearScript>();
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
			if (Random(0, 8) < 1)
			{
				StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());
				{
					Tear* tear = object::Instantiate<Tear>(eLayerType::Projectile, scene->GetCurrentRoom());
					tear->Parabola(true);
					tear->InitTear(GetOwner(), Vector3((float)(Random(-10, 10)) / 10.0f, (float)(Random(-10, 10)) / 10.0f, 0.0f));
					Rigidbody* rigidbody = tear->GetComponent<Rigidbody>();
					rigidbody->AddForce(Vector3((float)Random(-2000, 2000), 0.0f, 0.0f));
					rigidbody->AddHeightForce((float)Random(5, 600));
					tear->AddComponent<MonsterTearScript>();
				}
			}
		}
	}

	void MonstroScript::Die()
	{
		mTimer[(UINT)eState::Die] -= Time::DeltaTime();
		if (mTimer[(UINT)eState::Die] < 0.0f)
		{
			mTimer[(UINT)eState::Die] = mTimerMax[(UINT)eState::Die];
			mTransform->SetHeight(0.0f);
			mState = eState::None;

			{
				StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());
				{
					GameObject* largebloodexplosion = object::Instantiate<GameObject>(eLayerType::Effect, scene->GetCurrentRoom());
					largebloodexplosion->SetName(L"largebloodexplosion");

					SpriteRenderer* rd = largebloodexplosion->AddComponent<SpriteRenderer>();
					std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
					rd->SetMesh(mesh);
					std::shared_ptr<Material> material = Resources::Find<Material>(L"largebloodexplosionMaterial");
					rd->SetMaterial(material);
					std::shared_ptr<Texture> texture = material->GetTexture();

					Transform* tr = largebloodexplosion->GetComponent<Transform>();
					tr->SetPosition(mTransform->GetPosition() + Vector3(0.0f, -0.2f, -0.01f));
					tr->SetScale(Vector3(2.0f, 1.6, 1.0f));

					Animator* animator = largebloodexplosion->AddComponent<Animator>();
					animator->Create(L"largebloodexplosion", texture, Vector2(0.0f, 100.0f), Vector2(146.0f, 110.0f), Vector2::Zero, 7, 0.1f, 3, 3);
					animator->Play(L"largebloodexplosion", false);

					EffectScript* effectScript = largebloodexplosion->AddComponent<EffectScript>();
					effectScript->SetAutoDestroy(L"largebloodexplosion");
				}
			}

			Destroy();
		}
		else
		{
			Vector3 pos = mTransform->GetPosition();
			mTransform->SetPosition(Vector3(pos.x + SinByTime(0.7f, 0.05f), pos.y, pos.z));

			if (Random(0, 50) < 1)
			{
				StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());
				{
					GameObject* bloodpoof_small = object::Instantiate<GameObject>(eLayerType::Effect, scene->GetCurrentRoom());
					bloodpoof_small->SetName(L"bloodpoof_small");

					SpriteRenderer* rd = bloodpoof_small->AddComponent<SpriteRenderer>();
					std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
					rd->SetMesh(mesh);
					std::shared_ptr<Material> material = Resources::Find<Material>(L"bloodpoof_smallMaterial");
					rd->SetMaterial(material);
					std::shared_ptr<Texture> texture = material->GetTexture();

					Transform* tr = bloodpoof_small->GetComponent<Transform>();
					tr->SetPosition(mTransform->GetPosition() + Vector3((float)Random(-5, 5) * 0.1f, -0.2f + (float)Random(-5, 5) * 0.1f, -0.01f));
					tr->SetScale(Vector3(0.32f, 0.32f, 1.0f));

					Animator* animator = bloodpoof_small->AddComponent<Animator>();
					animator->Create(L"bloodpoof_small", texture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 12, 0.1f, 3, 4);
					animator->Play(L"bloodpoof_small", false);

					EffectScript* effectScript = bloodpoof_small->AddComponent<EffectScript>();
					effectScript->SetAutoDestroy(L"bloodpoof_small");
				}
			}
		}
	}

	void MonstroScript::Destroy()
	{
		//mEffect->Death();
		StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());
		scene->StageClear(true);
		UIScript* ui = scene->GetUI();
		ui->UseBossHealth(false);
		Death();
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