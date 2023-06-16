#include "yaShopItem.h"
#include "yaRigidbody.h"
#include "yaShopItemScript.h"

namespace ya
{
	ShopItem::ShopItem()
		: GameObject()
	{
		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetSize(Vector2(0.32f, 0.32f));
		collider->SetColliderType(eColliderType::Rect);

		AddComponent<Rigidbody>();

		AddComponent<ShopItemScript>();
	}
	ShopItem::~ShopItem()
	{
	}
	void ShopItem::Initialize()
	{
		GameObject::Initialize();
	}
	void ShopItem::Update()
	{
		GameObject::Update();
	}
	void ShopItem::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void ShopItem::Render()
	{
		GameObject::Render();
	}
	void ShopItem::SetItem(Item* item, int price)
	{
		ShopItemScript* script = GetScript<ShopItemScript>();
		if(script != nullptr)
			script->SetItem(item, price);
	}
}