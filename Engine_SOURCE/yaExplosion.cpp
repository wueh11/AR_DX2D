#include "yaExplosion.h"
#include "yaExplosionScript.h"
#include "yaTransform.h"
#include "yaRigidbody.h"

namespace ya
{
	Explosion::Explosion()
		: GameObject()
	{
		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetSize(Vector2(0.5f, 0.5f));
		collider->SetColliderType(eColliderType::Rect);

		AddComponent<ExplosionScript>();
	}
	Explosion::~Explosion()
	{
	}
	void Explosion::Initialize()
	{
		GameObject::Initialize();
	}
	void Explosion::Update()
	{
		GameObject::Update();
	}
	void Explosion::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Explosion::Render()
	{
		GameObject::Render();
	}
}