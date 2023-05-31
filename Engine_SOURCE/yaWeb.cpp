#include "yaWeb.h"
#include "yaWebScript.h"

namespace ya
{
	Web::Web()
		: GameObject()
	{
		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetSize(Vector2(0.5f, 0.5f));
		collider->SetColliderType(eColliderType::Rect);

		AddComponent<WebScript>();
	}
	Web::~Web()
	{
	}
	void Web::Initialize()
	{
		GameObject::Initialize();
	}
	void Web::Update()
	{
		GameObject::Update();
	}
	void Web::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Web::Render()
	{
		GameObject::Render();
	}
}