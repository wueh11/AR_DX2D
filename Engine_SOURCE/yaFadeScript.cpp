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
		, mCamera(nullptr)
		, mAlpha(0.0f)
		, mState(eState::None)
	{
	}

	FadeScript::~FadeScript()
	{
	}

	void FadeScript::Initialize()
	{
		mCamera = renderer::cameras[0];
	}

	void FadeScript::Update()
	{
		if (mCamera == nullptr)
			return;

		GameObject* gameObj = mCamera->GetOwner();
		Transform* tr = gameObj->GetComponent<Transform>();

		Vector3 cameraPos = tr->GetPosition();
		Vector4 position = Vector4(cameraPos.x, cameraPos.y, cameraPos.z, 1.0f);

		float scale = mCamera->GetScale();

		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);
		float width = winRect.right - winRect.left;
		float height = winRect.bottom - winRect.top;
		Vector2 resolution(width, height);

		//constant buffer
		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Grid];
		renderer::GridCB data;
		data.cameraPosition = position;
		data.cameraScale = Vector2(scale, scale);
		data.resolution = resolution;

		cb->Bind(&data);
		cb->SetPipeline(eShaderStage::VS);
		cb->SetPipeline(eShaderStage::PS);
	
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