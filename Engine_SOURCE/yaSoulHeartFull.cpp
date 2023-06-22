#include "yaSoulHeartFull.h"
#include "yaHeartScript.h"

namespace ya
{
	SoulHeartFull::SoulHeartFull()
		: Pickup(isaac::eItemType::SoulHeartFull)
	{
		HeartScript* heartScript = AddComponent<HeartScript>();
	}
	SoulHeartFull::~SoulHeartFull()
	{
	}
	void SoulHeartFull::Initialize()
	{
		Pickup::Initialize();
	}
	void SoulHeartFull::Update()
	{
		Pickup::Update();
	}
	void SoulHeartFull::FixedUpdate()
	{
		Pickup::FixedUpdate();
	}
	void SoulHeartFull::Render()
	{
		Pickup::Render();
	}
}