#include "yaPassiveItem.h"
#include "yaPassiveItemScript.h"

namespace ya
{
	PassiveItem::PassiveItem()
		: Item()
		, mType(isaac::ePassiveItem::None)
	{
		AddComponent<PassiveItemScript>();
	}
	PassiveItem::~PassiveItem()
	{
	}
	void PassiveItem::Initialize()
	{
		GameObject::Initialize();
	}
	void PassiveItem::Update()
	{
		GameObject::Update();
	}
	void PassiveItem::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void PassiveItem::Render()
	{
		GameObject::Render();
	}
	void PassiveItem::SetPassiveItemType(isaac::ePassiveItem type)
	{
		mType = type;
		PassiveItemScript* passiveItemScript = GetScript<PassiveItemScript>();
		passiveItemScript->SetPassiveItem(type);
	}
}