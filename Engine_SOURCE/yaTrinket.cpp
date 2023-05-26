#include "yaTrinket.h"
#include "yaTrinketScript.h"

namespace ya
{
	Trinket::Trinket()
		: Item()
		, mType(isaac::eTrinkets::None)
	{
		AddComponent<TrinketScript>();
	}
	Trinket::~Trinket()
	{
	}
	void Trinket::Initialize()
	{
		GameObject::Initialize();
	}
	void Trinket::Update()
	{
		GameObject::Update();
	}
	void Trinket::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Trinket::Render()
	{
		GameObject::Render();
	}
	void Trinket::SetTrinketType(isaac::eTrinkets type)
	{
		mType = type;

		TrinketScript* trinketScript = GetScript<TrinketScript>();
		trinketScript->SetTrinket(type);
	}
}