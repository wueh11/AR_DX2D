#include "yaFadeScript.h"
#include "yaFadeScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaApplication.h"
#include "yaConstantBuffer.h"
#include "yaRenderer.h"
#include "yaMeshRenderer.h"
#include "yaMaterial.h"
#include "yaTime.h"
#include "yaInput.h"

extern ya::Application application;
namespace ya
{
	FadeScript::FadeScript()
		: Script()
		, mAlpha(0.0f)
		, mState(eState::None)
	{
	}

	FadeScript::~FadeScript()
	{
	}

	void FadeScript::Initialize()
	{
	}

	void FadeScript::Update()
	{
		switch (mState)
		{
		case ya::FadeScript::eState::None:
			if (Input::GetKeyState(eKeyCode::P) == eKeyState::UP)
				mState = eState::FadeIn;
			break;
		case ya::FadeScript::eState::FadeIn:
			{
				mAlpha += 1.0f * Time::DeltaTime();
				if (mAlpha > 1.0f)
				{
					mAlpha = 1.0f;
					mState = eState::Full;
				}
			}
			break;
		case ya::FadeScript::eState::FadeOut:
			{
				mAlpha -= 1.0f * Time::DeltaTime();
				if (mAlpha <= 0.0f)
				{
					mAlpha = 0.0f;
					mState = eState::None;
				}
			}
			break;
		case ya::FadeScript::eState::Full:
			if (Input::GetKeyState(eKeyCode::P) == eKeyState::UP)
				mState = eState::FadeOut;
			break;
		default:
			break;
		}

		// material constant buffer setting
		MeshRenderer* mr = GetOwner()->GetComponent<MeshRenderer>();
		Material* fadeMaterial = mr->GetMaterial().get();
		fadeMaterial->SetData(eGPUParam::Float, &mAlpha);
	}

	void FadeScript::FixedUpdate()
	{
	}

	void FadeScript::Render()
	{
	}
}