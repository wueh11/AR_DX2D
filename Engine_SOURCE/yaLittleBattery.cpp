#include "yaLittleBattery.h"
#include "yaLittleBatteryScript.h"
#include "yaTransform.h"

namespace ya
{
	LittleBattery::LittleBattery()
		: Pickup(eItemType::LittleBattery)
	{
		LittleBatteryScript* script = AddComponent<LittleBatteryScript>();
	}
	LittleBattery::~LittleBattery()
	{
	}
	void LittleBattery::Initialize()
	{
		GameObject::Initialize();
	}
	void LittleBattery::Update()
	{
		GameObject::Update();
	}
	void LittleBattery::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void LittleBattery::Render()
	{
		GameObject::Render();
	}
}