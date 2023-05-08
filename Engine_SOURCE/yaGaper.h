#pragma once
#include "yaMonster.h"
#include "yaIsaacEnums.h"

namespace ya
{
	using namespace isaac;
	class Gaper : public Monster
	{
	public:
		Gaper();
		virtual ~Gaper();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}
