#include "yaActiveItem.h"
#include "yaActiveItemScript.h"

namespace ya
{
	ActiveItem::ActiveItem(isaac::eActiveItem type)
		: Item()
		, mType(type)
	{
		ActiveItemScript* activeItemScript = AddComponent<ActiveItemScript>();
		activeItemScript->SetActiveItem(type);
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
}