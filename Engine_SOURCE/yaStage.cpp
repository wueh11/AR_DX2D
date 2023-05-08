#include "yaStage.h"
#include "isaac.h"

namespace ya
{
	Stage::Stage()
		: mRooms{}
	{
	}
	Stage::~Stage()
	{
	}

	void Stage::Initialize()
	{
		mRooms.resize(ya::isaac::ROOM_MAX_ROW);
		for (size_t i = 0; i < ya::isaac::ROOM_MAX_ROW; i++)
		{
			mRooms[i].resize(ya::isaac::ROOM_MAX_COLUMN);
		}
	}
	void Stage::Update()
	{
	}
	void Stage::FixedUpdate()
	{
	}
	void Stage::Render()
	{
	}
}
