#include "yaItem.h"
#include "yaItemScript.h"

namespace ya
{
	Item::Item(eItemType itemType)
		: GameObject()
	{
		ItemScript* itemScript = AddComponent<ItemScript>();
		itemScript->SetItemType(itemType);
		itemScript->Initialize();
	}
	Item::~Item()
	{
	}
	void Item::Initialize()
	{
		GameObject::Initialize();
	}
	void Item::Update()
	{
		GameObject::Update();
	}
	void Item::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Item::Render()
	{
		GameObject::Render();
	}
}