#include "yaChest.h"
#include "yaChestScript.h"

namespace ya
{
	Chest::Chest()
		: Item()
		, mItems{}
		, mChestType(eItemType::ChestNormal)
	{
		AddComponent<ChestScript>();
	}
	Chest::~Chest()
	{
	}
	void Chest::Initialize()
	{
		GameObject::Initialize();
	}
	void Chest::Update()
	{
		GameObject::Update();
	}
	void Chest::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Chest::Render()
	{
		GameObject::Render();
	}
	void Chest::SetChestType(eItemType type)
	{
		mChestType = type;

		ChestScript* script = GetScript<ChestScript>();
		script->SetChestType(type);
	}
}