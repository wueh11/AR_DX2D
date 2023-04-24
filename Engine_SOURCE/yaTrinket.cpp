#include "yaTrinket.h"
#include "yaTrinketScript.h"

namespace ya
{
	Trinket::Trinket(isaac::eTrinkets type)
		: Item()
		, mType(type)
	{
		TrinketScript* trinketScript = AddComponent<TrinketScript>();
		trinketScript->SetTrinket(type);
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
}