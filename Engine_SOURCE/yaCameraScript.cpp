#include "yaCameraScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"

namespace ya
{
	CameraScript::CameraScript()
		: Script()
	{
	}
	CameraScript::~CameraScript()
	{
	}
	void CameraScript::Initialize()
	{
	}
	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 pos = tr->GetPosition();

		float speed = 2.0f;

		if (Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED)
		{
			pos += speed * tr->Up() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::S) == eKeyState::PRESSED)
		{
			pos -= speed * tr->Up() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::A) == eKeyState::PRESSED)
		{
			pos -= speed * tr->Right() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::D) == eKeyState::PRESSED)
		{
			pos += speed * tr->Right() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::Q) == eKeyState::PRESSED)
		{
			pos -= speed * tr->Forward() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::E) == eKeyState::PRESSED)
		{
			pos += speed * tr->Forward() * Time::DeltaTime();
		}

		tr->SetPosition(pos);
	}
	void CameraScript::FixedUpdate()
	{
	}
	void CameraScript::Render()
	{
	}
}