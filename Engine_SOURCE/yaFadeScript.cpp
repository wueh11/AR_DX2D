#include "yaFadeScript.h"

#include "yaResources.h"
#include "yaTime.h"
#include "yaInput.h"

#include "yaMeshRenderer.h"
#include "yaMaterial.h"

#include "yaGameObject.h"

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
		MeshRenderer* mr = GetOwner()->AddComponent<MeshRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(L"bgblackMaterial");
		mr->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->SetMesh(mesh);
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

		MeshRenderer* mr = GetOwner()->GetComponent<MeshRenderer>();
		std::shared_ptr<Material> material = mr->GetMaterial();
		//material->SetData(eGPUParam::Float, &mAlpha);
		mr->SetAlpha(mAlpha);
	}

	void FadeScript::FixedUpdate()
	{
	}

	void FadeScript::Render()
	{
	}
}