#include "yaEffectScript.h"

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
	EffectScript::EffectScript()
		: Script()
		, mAliveTime(0.1f)
		, mbUseAliveTime(false)
	{
	}
	EffectScript::~EffectScript()
	{
	}

	void EffectScript::Initialize()
	{
	}

	void EffectScript::Update()
	{
		if(mbUseAliveTime)
		{
			if (mAliveTime > 0.0f)
				mAliveTime -= Time::DeltaTime();
			else
				GetOwner()->Death();
		}
	}

	void EffectScript::FixedUpdate()
	{
	}
	void EffectScript::Render()
	{
	}
	void EffectScript::OnCollisionEnter(Collider2D* collider)
	{
	}

	void EffectScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void EffectScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void EffectScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void EffectScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void EffectScript::OnTriggerExit(Collider2D* collider)
	{
	}
	void EffectScript::Destroy()
	{
		GetOwner()->Death();
	}
	void EffectScript::SetAutoDestroy(std::wstring name)
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();

		if (animator->FindAnimation(name) == nullptr)
			return;

		animator->GetCompleteEvent(name) = std::bind(&EffectScript::Destroy, this);
	}
	void EffectScript::SetAliveTime(float time)
	{
		mbUseAliveTime = true;
		mAliveTime = time;
	}
}