#include "yaActiveItem.h"
#include "yaActiveItemScript.h"

namespace ya
{
	ActiveItem::ActiveItem()
		: Item()
		, mType(isaac::eActiveItem::None)
	{
		AddComponent<ActiveItemScript>();
	}
	ActiveItem::~ActiveItem()
	{
	}
	void ActiveItem::Initialize()
	{
		GameObject::Initialize();
	}
	void ActiveItem::Update()
	{
		GameObject::Update();
	}
	void ActiveItem::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void ActiveItem::Render()
	{
		GameObject::Render();
	}
	void ActiveItem::SetActiveItemType(isaac::eActiveItem type)
	{
		mType = type;
		ActiveItemScript* activeItemScript = GetScript<ActiveItemScript>();
		activeItemScript->SetActiveItem(type);
	}
}