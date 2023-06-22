#include "yaHeartFull.h"
#include "yaHeartScript.h"

namespace ya
{
	HeartFull::HeartFull()
		: Pickup(isaac::eItemType::HeartFull)
	{
		HeartScript* heartScript = AddComponent<HeartScript>();
	}
	HeartFull::~HeartFull()
	{
	}
	void HeartFull::Initialize()
	{
		Pickup::Initialize();
	}
	void HeartFull::Update()
	{
		Pickup::Update();
	}
	void HeartFull::FixedUpdate()
	{
		Pickup::FixedUpdate();
	}
	void HeartFull::Render()
	{
		Pickup::Render();
	}
}