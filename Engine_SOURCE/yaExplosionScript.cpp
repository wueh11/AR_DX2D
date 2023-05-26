#include "yaExplosionScript.h"

#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaSpriteRenderer.h"
#include "yaImageRenderer.h"
#include "yaObject.h"

#include "yaPlayer.h"
#include "yaPlayerScript.h"

namespace ya
{
	ExplosionScript::ExplosionScript()
		: Script()
		, mAliveTime(0.1f)
	{
	}
	ExplosionScript::~ExplosionScript()
	{
	}

	void ExplosionScript::Initialize()
	{
		Collider2D* collider = GetOwner()->GetComponent<Collider2D>();
		collider->SetColliderType(eColliderType::Rect);
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3(1.5f, 1.5f, 1.5f));
		collider->SetPosition(tr->GetPosition());
		//collider->SetSize(Vector2(1.0f, 1.0f));
	}

	void ExplosionScript::Update()
	{
		if (mAliveTime > 0.0f)
			mAliveTime -= Time::DeltaTime();
		else
			GetOwner()->Death();
	}

	void ExplosionScript::FixedUpdate()
	{
	}
	void ExplosionScript::Render()
	{
	}
	void ExplosionScript::OnCollisionEnter(Collider2D* collider)
	{
	}

	void ExplosionScript::OnCollisionStay(Collider2D* collider)
	{
		GameObject* gameObject = collider->GetOwner();

		Player* player = dynamic_cast<Player*>(gameObject);
		if (player != nullptr)
		{
			std::vector<Script*> scripts = player->GetScripts();
			for (Script* script : scripts)
			{
				PlayerScript* playerScript = dynamic_cast<PlayerScript*>(script);
				if(playerScript != nullptr)
					playerScript->Hurt();
			}
		}
	}
	void ExplosionScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void ExplosionScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void ExplosionScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void ExplosionScript::OnTriggerExit(Collider2D* collider)
	{
	}
}