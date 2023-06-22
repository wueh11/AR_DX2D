#include "yaHeartHalf.h"
#include "yaHeartScript.h"

namespace ya
{
	HeartHalf::HeartHalf()
		: Pickup(isaac::eItemType::HeartHalf)
	{
		HeartScript* heartScript = AddComponent<HeartScript>();
	}
	HeartHalf::~HeartHalf()
	{
	}
	void HeartHalf::Initialize()
	{
		Pickup::Initialize();
	}
	void HeartHalf::Update()
	{
		Pickup::Update();
	}
	void HeartHalf::FixedUpdate()
	{
		Pickup::FixedUpdate();
	}
	void HeartHalf::Render()
	{
		Pickup::Render();
	}
}