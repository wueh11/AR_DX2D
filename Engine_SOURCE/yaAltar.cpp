#include "yaAltar.h"
#include "yaRigidbody.h"
#include "yaAltarScript.h"

namespace ya
{
	Altar::Altar()
		: Land()
	{
		Collider2D* collider = GetComponent<Collider2D>();
		collider->SetSize(Vector2(0.32f, 0.32f));
		collider->SetColliderType(eColliderType::Rect);

		AddComponent<Rigidbody>();

		AddComponent<AltarScript>();
	}
	Altar::~Altar()
	{
	}
	void Altar::Initialize()
	{
		GameObject::Initialize();
	}
	void Altar::Update()
	{
		GameObject::Update();
	}
	void Altar::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Altar::Render()
	{
		GameObject::Render();
	}
	void Altar::SetItem(Item* item)
	{
		AltarScript* script = GetScript<AltarScript>();
		if(script != nullptr)
			script->SetItem(item);
	}
}