#pragma once
#include "yaLand.h"

namespace ya
{
	class Pit : public Land
	{
	public:

	public:
		Pit();
		virtual ~Pit();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}
