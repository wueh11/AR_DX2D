#include "yaPlayerScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaAnimator.h"

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
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetStartEvent(L"MoveDown") = std::bind(&PlayerScript::Start, this);
		animator->GetCompleteEvent(L"Idle") = std::bind(&PlayerScript::Action, this);
		animator->GetEndEvent(L"Idle") = std::bind(&PlayerScript::End, this);
		animator->GetEvent(L"Idle", 1) = std::bind(&PlayerScript::End, this);
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

		Animator* animator = GetOwner()->GetComponent<Animator>();
		if (Input::GetKey(eKeyCode::N_1))
		{
			animator->Play(L"MoveDown");
		}
	}
	void PlayerScript::FixedUpdate()
	{
	}
	void PlayerScript::Render()
	{
	}

	void PlayerScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void PlayerScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void PlayerScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void PlayerScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void PlayerScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void PlayerScript::OnTriggerExit(Collider2D* collider)
	{
	}
	void PlayerScript::Start()
	{
	}
	void PlayerScript::Action()
	{
	}
	void PlayerScript::End()
	{
	}
}