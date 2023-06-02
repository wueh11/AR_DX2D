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
		GameObject::Initialize();
	}
	void RageCreep::Update()
	{
		GameObject::Update();
	}
	void RageCreep::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void RageCreep::Render()
	{
		GameObject::Render();
	}
	void RageCreep::SetDirection(eDirection direction)
	{
		mDirection = direction;

		RageCreepScript* script = GetScript<RageCreepScript>();
		script->SetDirection(direction);
	}
}