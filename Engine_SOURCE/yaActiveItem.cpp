#include "yaActiveItem.h"

namespace ya
{
	ActiveItem::ActiveItem()
		: Item()
	{
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