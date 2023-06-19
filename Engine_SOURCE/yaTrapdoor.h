#pragma once
#include "yaLand.h"

namespace ya
{
	class Trapdoor : public Land
	{
	public:
		Trapdoor();
		virtual ~Trapdoor();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
	};
}