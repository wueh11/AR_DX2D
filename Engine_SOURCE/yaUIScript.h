#pragma once
#include "yaScript.h"

namespace ya
{
	class GameObject;
	class Player;
	class NumberScript;
	class UIScript : public Script
	{
	public:
		UIScript();
		virtual ~UIScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	public:
		void SetPlayer(Player* player) { mPlayer = player; }

	private:
		Player* mPlayer;
		std::vector<GameObject*> mHearts;

		GameObject* mActiveItem;
		GameObject* mConsumable;
		GameObject* Trinket;
		
		NumberScript* mCoinCount;
		NumberScript* mBombCount;
		NumberScript* mKeyCount;
	};
}
