#pragma once
#include "yaTear.h"

namespace ya
{
	class MonsterTear : public Tear
	{
	public:
		MonsterTear();
		virtual ~MonsterTear();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
	};
}
