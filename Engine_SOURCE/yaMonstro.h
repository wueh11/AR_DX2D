#pragma once
#include "yaMonster.h"

namespace ya
{
	class Monstro : public Monster
	{
	public:
		Monstro();
		virtual ~Monstro();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
	};
}
