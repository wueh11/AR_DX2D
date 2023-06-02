#include "yaMonsterScript.h"

#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaRigidbody.h"
#include "yaTime.h"
#include "yaObject.h"

#include "yaPlayer.h"
#include "yaPlayerScript.h"

#include "yaMonster.h"
#include "yaPlayerTear.h"

namespace ya
{
	MonsterScript::MonsterScript()
		: Script()
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
	}
	void MonsterScript::Update()
	{
	}
	void MonsterScript::FixedUpdate()
	{
	}
	void MonsterScript::Render()
	{
	}

	void MonsterScript::OnCollisionEnter(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();

		PlayerTear* tear = dynamic_cast<PlayerTear*>(other);

		if (mbDeath)
			return;

		if (tear != nullptr) 
		{
			Player* player = dynamic_cast<Player*>(tear->GetTearOwner());
			if (player != nullptr)
			{
				// 몬스터 피격
				Monster* monster = dynamic_cast<Monster*>(GetOwner());
				monster->AddHp(-player->GetStatus().attack);

				// 눈물에 의한 밀림
				mRigidbody->AddForce(tear->GetDirection() * 100.0f);
			}
		}

		Player* player = dynamic_cast<Player*>(other);
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

			Vector3 dist = Vector3(ownerCollider->GetSize().x * ownerTr->GetScale().x / 2.0f + collider->GetSize().x * otherTr->GetScale().x / 2.0f
				, ownerCollider->GetSize().y * ownerTr->GetScale().y / 2.0f + collider->GetSize().y * otherTr->GetScale().y / 2.0f
				, 0.0f);

			if (otherPos.x >= ownerCollider->GetPosition().x + dist.x - 0.1f
				|| otherPos.x <= ownerCollider->GetPosition().x - dist.x + 0.1f)
			{
				if (collider->GetPosition().x > ownerCollider->GetPosition().x)
					otherPos.x = ownerCollider->GetPosition().x + dist.x + 0.001f;
				else
					otherPos.x = ownerCollider->GetPosition().x - dist.x - 0.001f;
			}

			if (otherPos.y >= ownerCollider->GetPosition().y + dist.y - 0.1f
				|| otherPos.y <= ownerCollider->GetPosition().y - dist.y + 0.1f)
			{
				if (collider->GetPosition().y > ownerCollider->GetPosition().y)
					otherPos.y = ownerCollider->GetPosition().y + dist.y + 0.001f;
				else
					otherPos.y = ownerCollider->GetPosition().y - dist.y - 0.001f;
			}

			otherTr->SetPosition(otherPos);

			Rigidbody* otherRigidbody = other->GetComponent<Rigidbody>();
			if (otherRigidbody != nullptr)
			{
				mCollideVelocity = otherRigidbody->GetVelocity();
				otherRigidbody->SetVelocity(Vector3::Zero);
			}
		}
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
			rigidbody->AddForce(mCollideVelocity * 20.0f);
		}
	}
	void MonsterScript::OnCollisionExit(Collider2D* collider)
	{
		mCollideVelocity = Vector3::Zero;
	}
	void MonsterScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void MonsterScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void MonsterScript::OnTriggerExit(Collider2D* collider)
	{
	}
	void MonsterScript::Death()
	{
		GetOwner()->Death();
	}
}