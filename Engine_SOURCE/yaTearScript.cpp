#include "yaTearScript.h"

#include "yaInput.h"
#include "yaTime.h"
#include "yaResources.h"

#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaSpriteRenderer.h"

#include "yaObject.h"
#include "yaGameObject.h"

#include "yaTear.h"
#include "yaPlayer.h"
#include "yaMonster.h"

namespace ya
{
	TearScript::TearScript()
		: Script()
		, mTransform(nullptr)
		, mAnimator(nullptr)
		, mDistance(0.0f)
		, mbDead(false)
		, mState(eState::None)
		, mFriction(0.0f)
		, mGravity(0.0f)
	{
	}
	TearScript::~TearScript()
	{
	}
	void TearScript::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
		mAnimator = GetOwner()->AddComponent<Animator>();

		Collider2D* collider = GetOwner()->GetComponent<Collider2D>();
		Vector3 scale = mTransform->GetScale();
		collider->SetSize(Vector2(scale.x / 3.0f, scale.y / 3.0f));
	}

	void TearScript::Update()
	{
		Tear* tear = dynamic_cast<Tear*>(GetOwner());
		GameObject* tearOnwer = tear->GetTearOwner();
		if (tearOnwer == nullptr)
			return;

		Vector3 pos = mTransform->GetPosition();

		Vector3 dir = tear->GetDirection();
		dir.Normalize();

		isaac::Status status = tear->GetStatus();

		switch (mState)
		{
		case ya::TearScript::eState::None:
		{
			if (mDistance < status.range)
			{
				mDistance += status.tearSpeed * Time::DeltaTime();
				pos.x += status.tearSpeed * dir.x * Time::DeltaTime();
				pos.y += status.tearSpeed * dir.y * Time::DeltaTime();
			}
			else
			{
				float height = mTransform->GetHeight();
				if (height > 0.0f)
				{
					pos.x += (status.tearSpeed - mFriction) * dir.x * Time::DeltaTime();
					height -= mGravity * Time::DeltaTime();
					mTransform->SetHeight(height);
					mFriction += 0.01f;
					mGravity += 0.04f;
				}
				else
				{
					mState = eState::Death;
				}
			}
		}
			break;
		case ya::TearScript::eState::Death:
			if (mbDead == false)
			{
				mAnimator->Play(L"Destroy", false);
				mbDead = true;
			}
			break;
		default:
			break;
		}

		mTransform->SetPosition(pos);
	}
	void TearScript::FixedUpdate()
	{
	}
	void TearScript::Render()
	{
	}

	void TearScript::OnCollisionEnter(Collider2D* collider)
	{
		mState = eState::Death;
	}
	void TearScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void TearScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void TearScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void TearScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void TearScript::OnTriggerExit(Collider2D* collider)
	{
	}

	void TearScript::Destroy()
	{
		GetOwner()->Death();
	}
}