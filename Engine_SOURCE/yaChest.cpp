#include "yaChest.h"
#include "yaChest.h"
#include "yaRigidbody.h"
#include "yaChestScript.h"

namespace ya
{
	Chest::Chest()
		: GameObject()
		, mItems{}
		, mChestType(eChestType::Normal)
	{
		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetSize(Vector2(0.32f, 0.32f));
		collider->SetColliderType(eColliderType::Rect);

		AddComponent<Rigidbody>();

		AddComponent<ChestScript>();
	}
	Chest::~Chest()
	{
	}
	void Chest::Initialize()
	{
		GameObject::Initialize();
	}
	void Chest::Update()
	{
		GameObject::Update();
	}
	void Chest::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Chest::Render()
	{
		GameObject::Render();
	}
	void Chest::SetChestType(eChestType type)
	{
		mChestType = type;

		ChestScript* script = GetScript<ChestScript>();
		script->SetChestType(type);
	}
}