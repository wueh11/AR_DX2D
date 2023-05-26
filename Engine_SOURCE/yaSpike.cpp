#include "yaSpike.h"
#include "yaSpikeScript.h"

namespace ya
{
	Spike::Spike()
		: Land()
	{
		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetSize(Vector2(0.5f, 0.5f));
		collider->SetColliderType(eColliderType::Rect);

		AddComponent<SpikeScript>();
	}
	Spike::~Spike()
	{
	}
	void Spike::Initialize()
	{
		GameObject::Initialize();
	}
	void Spike::Update()
	{
		GameObject::Update();
	}
	void Spike::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Spike::Render()
	{
		GameObject::Render();
	}
}