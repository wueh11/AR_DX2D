#include "yaMonsterScript.h"

#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaRigidbody.h"
#include "yaTime.h"
#include "yaObject.h"

#include "yaStageScene.h"

#include "yaPlayer.h"
#include "yaPlayerScript.h"

#include "yaMonster.h"
#include "yaTear.h"
#include "Commons.h"
#include "yaBaseRenderer.h"

namespace ya
{
	MonsterScript::MonsterScript()
		: Script()
		, mbHit(false)
		, mHitTimer(0.1f)
		, mbDeath(false)
		, mCollideVelocity(Vector3::Zero)
		, mTransform(nullptr)
		, mRigidbody(nullptr)
	{
		//mRigidbody = GetOwner()->GetComponent<Rigidbody>();
	}
	MonsterScript::~MonsterScript()
	{
	}

	void MonsterScript::Initialize()
	{
		Script::Initialize();
	}
	void MonsterScript::Update()
	{
		if (mbDeath)
			return;

		if (mbHit)
		{
			mHitTimer -= Time::DeltaTime();
			if (mHitTimer < 0.0f)
			{
				mbHit = false;
				mHitTimer = 0.1f;
			}
		}

		Script::Update();
	}
	void MonsterScript::FixedUpdate()
	{
		Vector3 pos = mTransform->GetPosition();
		mTransform->SetPosition(Vector3(pos.x, pos.y, PositionZ(pos.y)));

		Script::FixedUpdate();
	}
	void MonsterScript::Render()
	{
		if (mbDeath)
			return;

		BaseRenderer* rd = GetOwner()->GetComponent<BaseRenderer>();
		if(mbHit)
		{
			rd->SetColorType(2);
			rd->SetColor(Vector4(1.0f, -1.0f, -1.0f, 0.3f));
		}
		else
		{
			rd->SetColorType(0);
		}

		Script::Render();
	}

	void MonsterScript::OnCollisionEnter(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();

		Tear* tear = dynamic_cast<Tear*>(other);
		Player* player = dynamic_cast<Player*>(other);

		if (mbDeath)
			return;

		if(tear != nullptr)
		{
			Player* tearOwner = dynamic_cast<Player*>(tear->GetTearOwner());
			if (tearOwner != nullptr)
			{
				// 몬스터 피격
				Monster* monster = dynamic_cast<Monster*>(GetOwner());
				monster->AddHp(-tearOwner->GetStatus().attack);

				// 눈물에 의한 밀림
				mRigidbody->AddForce(tear->GetDirection() * 100.0f);

				mbHit = true;
			}
		}

		if (player != nullptr)
		{
			// 플레이어 피격
			PlayerScript* playerScript = player->GetScript<PlayerScript>();
			playerScript->Hurt();

			// 플레이어 충돌
			Transform* otherTr = other->GetComponent<Transform>();
			Vector3 otherPos = collider->GetPosition();

			Collider2D* ownerCollider = GetOwner()->GetComponent<Collider2D>();
			Transform* ownerTr = GetOwner()->GetComponent<Transform>();
			Vector3 ownerPos = ownerCollider->GetPosition();

			Vector3 dist = Vector3(
				ownerCollider->GetSize().x * ownerTr->GetScale().x / 2.0f + collider->GetSize().x * otherTr->GetScale().x / 2.0f
				, ownerCollider->GetSize().y * ownerTr->GetScale().y / 2.0f + collider->GetSize().y * otherTr->GetScale().y / 2.0f
				, 0.0f);

			Rigidbody* otherRigidbody = other->GetComponent<Rigidbody>();
			Vector3 vel = otherRigidbody->GetVelocity();
			vel.Normalize();
			mColliderPosition = otherTr->GetPosition() - (vel * 0.01f);

			otherTr->SetPosition(mColliderPosition);

			if (otherRigidbody != nullptr)
				otherRigidbody->SetVelocity(Vector3::Zero);

		}

		Script::OnCollisionEnter(collider);
	}

	void MonsterScript::OnCollisionStay(Collider2D* collider)
	{
		if (mbDeath)
			return;

		GameObject* other = collider->GetOwner();
		Player* player = dynamic_cast<Player*>(other);
		if (player != nullptr)
		{
			Rigidbody* rigidbody = GetOwner()->GetComponent<Rigidbody>();
			rigidbody->AddForce(mCollideVelocity * 5.0f);

			Transform* otherTr = other->GetComponent<Transform>();
			Vector3 otherPos = collider->GetPosition();

			Collider2D* ownerCollider = GetOwner()->GetComponent<Collider2D>();
			Transform* ownerTr = GetOwner()->GetComponent<Transform>();
			Vector3 ownerPos = ownerCollider->GetPosition();
		}

		Script::OnCollisionStay(collider);
	}
	void MonsterScript::OnCollisionExit(Collider2D* collider)
	{
		mCollideVelocity = Vector3::Zero;

		Script::OnCollisionExit(collider);
	}
	void MonsterScript::OnTriggerEnter(Collider2D* collider)
	{
		Script::OnTriggerEnter(collider);
	}
	void MonsterScript::OnTriggerStay(Collider2D* collider)
	{
		Script::OnTriggerStay(collider);
	}
	void MonsterScript::OnTriggerExit(Collider2D* collider)
	{
		Script::OnTriggerExit(collider);
	}
	void MonsterScript::Death()
	{
		StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());

		Monster* monster = dynamic_cast<Monster*>(GetOwner());
		//Room* room = dynamic_cast<Room*>(monster->GetParent());
		Room* room = monster->GetRoom();
		if(room != nullptr)
			room->AddMonsterCount(-1);

		GetOwner()->Death();
	}
}