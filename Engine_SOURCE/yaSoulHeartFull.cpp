#include "yaSoulHeartFull.h"
#include "yaHeartScript.h"

namespace ya
{
	SoulHeartFull::SoulHeartFull()
		: Pickup(isaac::ePickupType::SoulHeartFull)
	{
		HeartScript* heartScript = AddComponent<HeartScript>();
	}
	SoulHeartFull::~SoulHeartFull()
	{
	}
	void SoulHeartFull::Initialize()
	{
		GameObject::Initialize();
	}
	void SoulHeartFull::Update()
	{
		GameObject::Update();
	}
	void SoulHeartFull::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void SoulHeartFull::Render()
	{
		GameObject::Render();
	}
}