#include "yaPill.h"
#include "yaPillScript.h"
#include "yaTransform.h"

namespace ya
{
	Pill::Pill(ePills type)
		: Pickup(eItemType::Pill)
		, mPill(type)
	{
		PillScript* pillScript = AddComponent<PillScript>();
		pillScript->SetPill(type);
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
}