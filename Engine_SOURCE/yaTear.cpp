#include "yaTear.h"
#include "yaTearScript.h"
#include "yaTransform.h"

namespace ya
{
	Tear::Tear(GameObject* owner, Vector3 direction)
		: GameObject()
		, mProjectileOwner(owner)
		, mDirection(direction)
	{
		TearScript* tearScript = AddComponent<TearScript>();
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