#pragma once
#include "yaLand.h"

namespace ya
{
	class Spike : public Land
	{
	public:

	public:
		Spike();
		virtual ~Spike();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}
