#include "yaItem.h"

namespace ya
{
	Item::Item()
		: GameObject()
	{
		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetSize(Vector2(0.5f, 0.5f));
		collider->SetColliderType(eColliderType::Rect);
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