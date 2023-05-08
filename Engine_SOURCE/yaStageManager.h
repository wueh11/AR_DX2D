#pragma once
#include "yaEngine.h"
#include "yaScene.h"
#include "yaIsaacEnums.h"
#include "yaItemObject.h"
#include "yaRoom.h"

namespace ya
{
	using namespace isaac;
	class StageManager
	{
	public:
		static void Initialize();
		static void Release();

	public:
		static Room* CreateRoom(int x, int y);

	};
}

