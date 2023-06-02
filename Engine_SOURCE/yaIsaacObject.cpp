#include "yaIsaacObject.h"
#include "yaRigidbody.h"

namespace ya
{
	IsaacObject::IsaacObject()
		: GameObject()
	{
		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetSize(Vector2(0.5f, 0.5f));
		collider->SetColliderType(eColliderType::Rect);

		AddComponent<Rigidbody>();
	}
	IsaacObject::~IsaacObject()
	{
	}
	void IsaacObject::Initialize()
	{
		GameObject::Initialize();
	}
	void IsaacObject::Update()
	{
		GameObject::Update();
	}
	void IsaacObject::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void IsaacObject::Render()
	{
		GameObject::Render();
	}
	void IsaacObject::SetSpeed()
	{
		Rigidbody* rigidbody = GetComponent<Rigidbody>();
		if (rigidbody != nullptr)
			rigidbody->SetLimitVelocity(Vector3(1.0f + mStatus.speed, 1.0f + mStatus.speed, 0.0f));
	}
}