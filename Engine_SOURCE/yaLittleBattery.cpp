#include "yaLittleBattery.h"
#include "yaLittleBatteryScript.h"
#include "yaTransform.h"

namespace ya
{
	LittleBattery::LittleBattery()
		: Pickup(eItemType::LittleBattery)
	{
		AddComponent<LittleBatteryScript>();
	}
	LittleBattery::~LittleBattery()
	{
	}
	void LittleBattery::Initialize()
	{
		Pickup::Initialize();
	}
	void LittleBattery::Update()
	{
		Pickup::Update();
	}
	void LittleBattery::FixedUpdate()
	{
		Pickup::FixedUpdate();
	}
	void LittleBattery::Render()
	{
		Pickup::Render();
	}
}