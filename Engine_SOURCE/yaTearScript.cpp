#include "yaTearScript.h"

#include "yaInput.h"
#include "yaTime.h"
#include "yaResources.h"

#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaRigidbody.h"

#include "yaObject.h"
#include "yaGameObject.h"

#include "yaTear.h"
#include "Commons.h"

namespace ya
{
	TearScript::TearScript()
		: Script()
		, mTransform(nullptr)
		, mAnimator(nullptr)
		, mRigidbody(nullptr)
		, mDistance(0.0f)
		, mbDead(false)
		, mState(eState::None)
		, mFriction(0.0f)
	{
	}
	TearScript::~TearScript()
	{
	}
	void TearScript::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
		mAnimator = GetOwner()->AddComponent<Animator>();
		mRigidbody = GetOwner()->GetComponent<Rigidbody>();

		Collider2D* collider = GetOwner()->GetComponent<Collider2D>();
		Vector3 scale = mTransform->GetScale();
		collider->SetSize(Vector2(scale.x / 5.0f, scale.y / 5.0f));

		Shadow(Vector3::Zero, Vector3(0.3f, 0.1f, 1.0f));
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
			mDistance += status.tearSpeed * Time::DeltaTime();
			if (tear->IsParabola())
			{
				mRigidbody->AddForce(status.tearSpeed * dir * 10.0f);
				mRigidbody->AddHeightForce(status.range);
			}
			else
			{
				mRigidbody->AddForce(status.tearSpeed * dir * 100.0f);
				if (mDistance > status.range)
					mRigidbody->SetHeightGround(false);
			}

			if (mTransform->GetHeight() < 0.0f)
				mState = eState::Death;
		}
			break;
		case ya::TearScript::eState::Death:
			if (mbDead == false)
			{
				GetOwner()->GetComponent<Collider2D>()->Active(false);
				mRigidbody->UseHeight(false);
				mAnimator->Play(L"Destroy", false);
				mbDead = true;
				if (mShadow != nullptr)
					mShadow->Pause();
			}
			break;
		default:
			break;
		}

		if (mTransform->GetHeight() > 2.0f)
		{
			Collider2D* collider = GetOwner()->GetComponent<Collider2D>();
			collider->Disable(true);
		}
		else
		{
			Collider2D* collider = GetOwner()->GetComponent<Collider2D>();
			collider->Disable(false);
		}

		Script::Update();
	}
	void TearScript::FixedUpdate()
	{
		Vector3 pos = mTransform->GetPosition();
		mTransform->SetPosition(Vector3(pos.x, pos.y, PositionZ(pos.y)));

		Script::FixedUpdate();
	}
	void TearScript::Render()
	{
		Script::Render();
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