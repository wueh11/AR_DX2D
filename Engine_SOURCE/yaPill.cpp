#include "yaPill.h"
#include "yaPillScript.h"
#include "yaTransform.h"

namespace ya
{
	Pill::Pill()
		: Pickup(eItemType::Pill)
		, mPill(ePills::None)
	{
		AddComponent<PillScript>();
	}
	Pill::~Pill()
	{
	}
	void Pill::Initialize()
	{
		Pickup::Initialize();
	}
	void Pill::Update()
	{
		Pickup::Update();
	}
	void Pill::FixedUpdate()
	{
		Pickup::FixedUpdate();
	}
	void Pill::Render()
	{
		Pickup::Render();
	}
	void Pill::SetPillType(ePills type)
	{
		mPill = type;
		PillScript* pillScript = GetScript<PillScript>();
		pillScript->SetPill(type);
	}
}