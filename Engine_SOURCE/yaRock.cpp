#include "yaRock.h"
#include "yaRockScript.h"

namespace ya
{
	Rock::Rock()
		: Land()
		, mRockType(eRockType::None)
	{
		AddComponent<RockScript>();
	}
	Rock::~Rock()
	{
	}
	void Rock::Initialize()
	{
		Land::Initialize();
	}
	void Rock::Update()
	{
		Land::Update();
	}
	void Rock::FixedUpdate()
	{
		Land::FixedUpdate();
	}
	void Rock::Render()
	{
		Land::Render();
	}
	void Rock::SetRockType(eRockType rockType)
	{
		mRockType = rockType;
		RockScript* rockScript = GetScript<RockScript>();
		rockScript->SetRockType(rockType);
	}
}