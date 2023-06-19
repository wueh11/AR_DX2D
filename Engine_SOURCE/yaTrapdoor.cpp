#include "yaTrapdoor.h"
#include "yaRigidbody.h"
#include "yaTrapdoorScript.h"

namespace ya
{
	Trapdoor::Trapdoor()
		: Land()
	{
		Collider2D* collider = GetComponent<Collider2D>();
		collider->SetSize(Vector2(0.32f, 0.32f));
		collider->SetColliderType(eColliderType::Rect);

		AddComponent<TrapdoorScript>();
	}
	Trapdoor::~Trapdoor()
	{
	}
	void Trapdoor::Initialize()
	{
		GameObject::Initialize();
	}
	void Trapdoor::Update()
	{
		GameObject::Update();
	}
	void Trapdoor::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Trapdoor::Render()
	{
		GameObject::Render();
	}
}