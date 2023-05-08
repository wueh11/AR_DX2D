#pragma once
#include "yaEngine.h"
#include "yaScene.h"
#include "Isaac.h"
#include "yaItemObject.h"
#include "yaStage.h"
#include "yaRoom.h"

namespace ya
{
	using namespace isaac;
	class StageManager
	{
	public:
		static void Initialize();

	public:
		Stage* GetCurrentStage() { return mCurrentStage; }

	private:
		static Stage* mCurrentStage;
		std::vector<Stage*> mStages;
		
	};
}

