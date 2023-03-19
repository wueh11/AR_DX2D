#pragma once
#include "yaScript.h"

namespace ya
{
	class TitleScript : public Script
	{
	public:
		enum class eState
		{
			None,
			PageUp,
			PageDown,
		};

		enum class ePage
		{
			Titlemenu,
			Gamemenu,
			Charactermenu,
		};

	public:
		TitleScript();
		virtual ~TitleScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	private:
		void PageUp();
		void PageDown();

		void Title();
		void GameMenu();
		void CharacterMenu();
		
	private:
		eState mState;
		ePage mPage;
		float mSpeed;
		float mFriction;
	};
}
