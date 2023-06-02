#pragma once
#include "yaTear.h"

namespace ya
{
	class PlayerTear : public Tear
	{
	public:
		PlayerTear();
		virtual ~PlayerTear();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
	};
}
