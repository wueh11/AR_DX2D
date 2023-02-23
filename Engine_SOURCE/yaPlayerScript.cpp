#include "yaPlayerScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"

namespace ya
{
	PlayerScript::PlayerScript()
		: Script()
	{
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Initialize()
	{
	}
	void PlayerScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		float speed = 2.0f;

		Vector3 pos = tr->GetPosition();
		/// 이동
		if (Input::GetKeyState(eKeyCode::UP) == eKeyState::PRESSED)
		{
			pos.y += speed * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::PRESSED)
		{
			pos.y -= speed * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::PRESSED)
		{
			pos.x -= speed * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::PRESSED)
		{
			pos.x += speed * Time::DeltaTime();
		}
		tr->SetPosition(pos);

		/// 회전
		Vector3 rot = tr->GetRotation();
		if (Input::GetKeyState(eKeyCode::M) == eKeyState::PRESSED)
		{
			rot.z += speed * Time::DeltaTime();
		}
		tr->SetRotation(rot);
	}
	void PlayerScript::FixedUpdate()
	{
	}
	void PlayerScript::Render()
	{
	}
}