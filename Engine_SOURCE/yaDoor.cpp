#include "yaDoor.h"
#include "yaDoorScript.h"

namespace ya
{
	Door::Door()
		: Land()
		, mDoorType(eRoomType::Normal)
		, mDirection(eDirection::None)
		, mbOpen(true)
		, mbDamaged(false)
		, mbLock(false)
	{
		Pause();
		AddComponent<DoorScript>();
	}
	Door::~Door()
	{
	}
	void Door::Initialize()
	{
		SetName(L"Door " + std::to_wstring((int)mDirection));

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
	void Door::SetDoorType(eRoomType type)
	{
		mDoorType = type;
		DoorScript* doorScript = GetScript<DoorScript>();
		doorScript->SetDoorType(type);
	}
	void Door::SetOpen(bool open)
	{
		mbOpen = open;
		DoorScript* doorScript = GetScript<DoorScript>();
		doorScript->SetOpen(open);
	}
	void Door::SetDamaged(bool damaged)
	{
		mbDamaged = damaged;
		DoorScript* doorScript = GetScript<DoorScript>();
		doorScript->SetDamaged(damaged);
	}
	void Door::SetLock(bool lock)
	{
		mbLock = lock;
		DoorScript* doorScript = GetScript<DoorScript>();
		doorScript->SetLock(lock);
	}
}