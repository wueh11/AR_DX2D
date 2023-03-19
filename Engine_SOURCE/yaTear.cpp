#include "yaTear.h"
#include "yaTearScript.h"

namespace ya
{
	Tear::Tear(GameObject* owner, Vector3 direction)
		: GameObject()
		, mOwner(owner)
		, mDirection(direction)
	{
		TearScript* tearScript = AddComponent<TearScript>();
		tearScript->SetProjectileOwner(owner);
		tearScript->Initialize();
	}
	Tear::~Tear()
	{
	}
	void Tear::Initialize()
	{
		GameObject::Initialize();
	}
	void Tear::Update()
	{
		GameObject::Update();
	}
	void Tear::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Tear::Render()
	{
		GameObject::Render();
	}
}