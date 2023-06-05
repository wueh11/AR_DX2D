#include "yaRageCreep.h"
#include "yaRageCreepScript.h"

namespace ya
{
	RageCreep::RageCreep()
		: Monster()
		, mDirection(eDirection::UP)
	{
		mType = eMonsterType::RageCreep;
		AddComponent<RageCreepScript>();
	}
	RageCreep::~RageCreep()
	{
	}
	void RageCreep::Initialize()
	{
		Monster::Initialize();
	}
	void RageCreep::Update()
	{
		Monster::Update();
	}
	void RageCreep::FixedUpdate()
	{
		Monster::FixedUpdate();
	}
	void RageCreep::Render()
	{
		Monster::Render();
	}
	void RageCreep::SetDirection(eDirection direction)
	{
		mDirection = direction;

		RageCreepScript* script = GetScript<RageCreepScript>();
		script->SetDirection(direction);
	}
}