#include "yaPit.h"
#include "yaPitScript.h"

namespace ya
{
	Pit::Pit()
		: Land()
	{
		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetSize(Vector2(0.5f, 0.5f));
		collider->SetColliderType(eColliderType::Rect);

		AddComponent<PitScript>();
	}
	Pit::~Pit()
	{
	}
	void Pit::Initialize()
	{
		GameObject::Initialize();
	}
	void Pit::Update()
	{
		GameObject::Update();
	}
	void Pit::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Pit::Render()
	{
		GameObject::Render();
	}
}