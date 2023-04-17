
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
		, mSpeed(60.0f)
		, mFriction(0.0f)
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

		if (mFriction > mSpeed - 5.0f)
			mFriction = mSpeed - 5.0f;
		else
			mFriction += 0.08f;

		pos += (mSpeed - mFriction) * tr->Up() * Time::DeltaTime();

		switch (mPage)
		{
		case ya::TitleScript::ePage::Titlemenu:
		break;
		case ya::TitleScript::ePage::Gamemenu:
		{
			if (pos.y > -0.0f)
			{
				mState = eState::None;
				mPage = ePage::Titlemenu;
				mFriction = 0.0f;
			}
		}
		break;
		case ya::TitleScript::ePage::Charactermenu:
		{
			if (pos.y > -5.3f)
			{
				mState = eState::None;
				mPage = ePage::Gamemenu;
				mFriction = 0.0f;
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

		if (mFriction > mSpeed - 5.0f)
			mFriction = mSpeed - 5.0f;
		else
			mFriction += 0.08f;

		pos -= (mSpeed - mFriction) * tr->Up() * Time::DeltaTime();

		switch (mPage)
		{
		case ya::TitleScript::ePage::Titlemenu:
		{
			if (pos.y < -5.3f)
			{
				mState = eState::None;
				mPage = ePage::Gamemenu;
				mFriction = 0.0f;
			}
		}
			break;
		case ya::TitleScript::ePage::Gamemenu:
		{
			if (pos.y < -10.7f)
			{
				mState = eState::None;
				mPage = ePage::Charactermenu;
				mFriction = 0.0f;
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