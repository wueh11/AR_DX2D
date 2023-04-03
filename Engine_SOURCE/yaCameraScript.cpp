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

		float speed = 50.0f;

		if (Input::GetKeyState(eKeyCode::I) == eKeyState::PRESSED)
		{
			pos += speed * tr->Up() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::K) == eKeyState::PRESSED)
		{
			pos -= speed * tr->Up() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::J) == eKeyState::PRESSED)
		{
			pos -= speed * tr->Right() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::L) == eKeyState::PRESSED)
		{
			pos += speed * tr->Right() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::U) == eKeyState::PRESSED)
		{
			pos -= speed * tr->Forward() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::O) == eKeyState::PRESSED)
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