#include "yaDoor.h"
#include "yaDoorScript.h"

namespace ya
{
	Door::Door()
		: Land()
		, mDirection(eDirection::None)
		, mbOpen(true)
		, mbDamaged(false)
		, mbLock(false)
	{
		SetName(L"Door " + std::to_wstring((int)mDirection));
		Pause();
		AddComponent<DoorScript>();
	}
	Door::~Door()
	{
	}
	void Door::Initialize()
	{
		Land::Initialize();
	}
	void Door::Update()
	{
		Land::Update();
	}
	void Door::FixedUpdate()
	{
		Land::FixedUpdate();
	}
	void Door::Render()
	{
		Land::Render();
	}
	void Door::SetDirection(eDirection dir)
	{
		mDirection = dir;
		DoorScript* doorScript = GetScript<DoorScript>();
		doorScript->SetDoorDirection(dir);
	}
	void Door::SetOpen(bool open)
	{
		mbOpen = open;
	}
	void Door::SetDamaged(bool damaged)
	{
		mbDamaged = damaged;
	}
	void Door::SetLock(bool lock)
	{
		mbLock = lock;
	}
}