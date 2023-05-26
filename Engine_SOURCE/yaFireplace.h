#pragma once
#include "yaLand.h"

namespace ya
{
	class Fireplace : public Land
	{
	public:

	public:
		Fireplace();
		virtual ~Fireplace();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}
