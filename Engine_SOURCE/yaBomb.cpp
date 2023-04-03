#include "yaBomb.h"
#include "yaBombScript.h"
#include "yaTransform.h"

namespace ya
{
	Bomb::Bomb(Vector3 pos)
		: GameObject()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPosition(pos + Vector3(0.0f, -0.1f, 0.0f));

		BombScript* bombScript = AddComponent<BombScript>();
	}
	Bomb::~Bomb()
	{
	}
	void Bomb::Initialize()
	{
		GameObject::Initialize();
	}
	void Bomb::Update()
	{
		GameObject::Update();
	}
	void Bomb::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Bomb::Render()
	{
		GameObject::Render();
	}
}