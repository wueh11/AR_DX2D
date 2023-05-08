#include "yaStage.h"
#include "yaIsaacEnums.h"
#include "yaObject.h"
#include "Commons.h"

namespace ya
{
	Stage::Stage()
		: mRooms{}
		, mbActive(false)
	{
	}
	Stage::~Stage()
	{
	}

	void Stage::Initialize()
	{
		GameObject::Initialize();

		mRooms.resize(ya::isaac::ROOM_MAX_ROW);
		for (size_t i = 0; i < ya::isaac::ROOM_MAX_ROW; i++)
		{
			mRooms[i].resize(ya::isaac::ROOM_MAX_COLUMN);
		}

		//Transform* tr = GetComponent<Transform>();
	}
	void Stage::Update()
	{
		GameObject::Update();
	}
	void Stage::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Stage::Render()
	{
		GameObject::Render();
	}
	void Stage::AddRoom(Room* room, int x, int y)
	{
		if (x < 0 || y < 0)
			return;

		room->SetStage(this);
		room->SetRoomPos(Vector2(x, y));
		
		mRooms[x][y] = room;
	}
	void Stage::SetCurrentRoom(Room* room)
	{
		mCurrentRoom = room;
	}
}
