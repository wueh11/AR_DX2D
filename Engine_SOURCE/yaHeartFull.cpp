#include "yaHeartFull.h"
#include "yaHeartScript.h"

namespace ya
{
	HeartFull::HeartFull()
		: Pickup(isaac::ePickupType::HeartFull)
	{
		HeartScript* heartScript = AddComponent<HeartScript>();
	}
	HeartFull::~HeartFull()
	{
	}
	void HeartFull::Initialize()
	{
		GameObject::Initialize();
	}
	void HeartFull::Update()
	{
		GameObject::Update();
	}
	void HeartFull::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void HeartFull::Render()
	{
		GameObject::Render();
	}
}