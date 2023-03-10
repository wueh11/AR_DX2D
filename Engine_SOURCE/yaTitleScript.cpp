#include "yaTitleScript.h"

#include "yaTitleScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"

namespace ya
{
	TitleScript::TitleScript()
		: Script()
		, mState(eState::None)
		, mPage(ePage::Titlemenu)
		, mSpeed(40.0f)
	{
	}
	TitleScript::~TitleScript()
	{
	}
	void TitleScript::Initialize()
	{
	}
	void TitleScript::Update()
	{
		switch (mPage)
		{
		case ya::TitleScript::ePage::Titlemenu:
			Title();
			break;
		case ya::TitleScript::ePage::Gamemenu:
			GameMenu();
			break;
		case ya::TitleScript::ePage::Charactermenu:
			CharacterMenu();
			break;
		default:
			break;
		}

		if (mState == eState::PageUp)
			PageUp();
		else if (mState == eState::PageDown)
			PageDown();
	}

	void TitleScript::FixedUpdate()
	{
	}

	void TitleScript::Render()
	{
	}

	void TitleScript::PageUp()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		if (mSpeed < 1.0f)
			mSpeed = 1.0f;
		else
			mSpeed -= 50.0f * Time::DeltaTime();

		pos += mSpeed * tr->Up() * Time::DeltaTime();

		switch (mPage)
		{
		case ya::TitleScript::ePage::Titlemenu:
		break;
		case ya::TitleScript::ePage::Gamemenu:
		{
			if (pos.y > -0.02f)
			{
				mState = eState::None;
				mPage = ePage::Titlemenu;
				mSpeed = 40.0f;
			}
		}
		break;
		case ya::TitleScript::ePage::Charactermenu:
		{
			if (pos.y > -1.125f)
			{
				mState = eState::None;
				mPage = ePage::Gamemenu;
				mSpeed = 40.0f;
			}
		}
			break;
		default:
			break;
		}

		tr->SetPosition(pos);
	}

	void TitleScript::PageDown()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		if (mSpeed < 5.0f)
			mSpeed = 5.0f;
		else
			mSpeed -= 50.0f * Time::DeltaTime();

		pos -= mSpeed * tr->Up() * Time::DeltaTime();

		switch (mPage)
		{
		case ya::TitleScript::ePage::Titlemenu:
		{
			if (pos.y < -5.6f)
			{
				mState = eState::None;
				mPage = ePage::Gamemenu;
				mSpeed = 30.0f;
			}
		}
			break;
		case ya::TitleScript::ePage::Gamemenu:
		{
			if (pos.y < -2.27f)
			{
				mState = eState::None;
				mPage = ePage::Charactermenu;
				mSpeed = 10.0f;
			}
		}
			break;
		case ya::TitleScript::ePage::Charactermenu:
			break;
		default:
			break;
		}

		tr->SetPosition(pos);
	}

	void TitleScript::Title()
	{
		if (Input::GetKeyState(eKeyCode::ENTER) == eKeyState::PRESSED)
			mState = eState::PageDown;
	}

	void TitleScript::GameMenu()
	{
		if (Input::GetKeyState(eKeyCode::ENTER) == eKeyState::PRESSED)
			mState = eState::PageDown;
		else if (Input::GetKeyState(eKeyCode::ESC) == eKeyState::PRESSED)
			mState = eState::PageUp;

		// menu select
		if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::PRESSED)
		{
			//new run
			//continue
			//options -> tool
		}
	}

	void TitleScript::CharacterMenu()
	{
		if (Input::GetKeyState(eKeyCode::ESC) == eKeyState::PRESSED)
			mState = eState::PageUp;

		// character select
		// isaac
		// 
	}

}