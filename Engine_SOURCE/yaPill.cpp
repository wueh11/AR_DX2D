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
		GameObject::Initialize();
	}
	void Pill::Update()
	{
		GameObject::Update();
	}
	void Pill::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Pill::Render()
	{
		GameObject::Render();
	}
	void Pill::SetPillType(ePills type)
	{
		mPill = type;
		PillScript* pillScript = GetScript<PillScript>();
		pillScript->SetPill(type);
	}
}